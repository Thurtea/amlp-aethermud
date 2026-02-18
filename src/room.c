#include "room.h"
#include "npc.h"
#include "item.h"
#include <string.h>
#include <ctype.h>

/* Helper: format item display name to lowercase while preserving
 * acronyms (ALLCAPS) and obvious proper-nouns with apostrophes
 * (e.g. Wilk's). Writes result into `out` (must be at least out_sz).
 */
void format_item_name(const char *iname, char *out, size_t out_sz) {
    if (!iname || !iname[0]) {
        if (out_sz > 0) out[0] = '\0';
        return;
    }
    char tmp[256];
    strncpy(tmp, iname, sizeof(tmp)-1);
    tmp[sizeof(tmp)-1] = '\0';

    /* Split on spaces and process words */
    char *words[64];
    int wc = 0;
    char *p = strtok(tmp, " ");
    while (p && wc < 64) {
        words[wc++] = p;
        p = strtok(NULL, " ");
    }

    char buf[512] = "";
    for (int i = 0; i < wc; i++) {
        char *w = words[i];
        int len = (int)strlen(w);
        int all_upper = 1;
        for (int j = 0; j < len; j++) {
            if (!isupper((unsigned char)w[j])) { all_upper = 0; break; }
        }

        /* Preserve ALLCAPS acronyms */
        if (all_upper && len > 1) {
            if (buf[0]) strncat(buf, " ", sizeof(buf)-strlen(buf)-1);
            strncat(buf, w, sizeof(buf)-strlen(buf)-1);
            continue;
        }

        /* Preserve proper nouns like "Wilk's" (capital first letter and apostrophe)
         */
        if (len > 1 && isupper((unsigned char)w[0])) {
            /* If contains apostrophe, keep as-is */
            if (strchr(w, '\'') ) {
                if (buf[0]) strncat(buf, " ", sizeof(buf)-strlen(buf)-1);
                strncat(buf, w, sizeof(buf)-strlen(buf)-1);
                continue;
            }
        }

        /* Default: lowercase the word */
        char lw[128];
        for (int j = 0; j < len && j < (int)sizeof(lw)-1; j++) lw[j] = tolower((unsigned char)w[j]);
        lw[len] = '\0';
        if (buf[0]) strncat(buf, " ", sizeof(buf)-strlen(buf)-1);
        strncat(buf, lw, sizeof(buf)-strlen(buf)-1);
    }

    strncpy(out, buf, out_sz-1);
    out[out_sz-1] = '\0';
}
#include "session_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

#define MAX_ROOMS 100
#define LPC_ROOM_ID_BASE 1000

/* World data - bootstrap C rooms */
static Room world_rooms[MAX_ROOMS];
static int num_rooms = 0;

/* Dynamic LPC room pool */
static Room **lpc_rooms = NULL;
static int num_lpc_rooms = 0;
static int max_lpc_rooms = 0;
static int next_lpc_room_id = LPC_ROOM_ID_BASE;

/* Path lookup table for LPC rooms */
typedef struct {
    char *path;
    Room *room;
} RoomPathEntry;
static RoomPathEntry *path_table = NULL;
static int num_path_entries = 0;
static int max_path_entries = 0;

/* External function from session.c */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* ========== LPC TEXT-SCRAPING HELPERS ========== */

/* Preprocess LPC source: resolve DIR_DOMAINS and DIR_STD macros.
 * Copies 'in' to 'out', replacing DIR_DOMAINS + " with "/domains
 * and DIR_STD + " with "/std so the parser sees plain quoted strings. */
static void preprocess_lpc_macros(char *out, const char *in, size_t max_out) {
    size_t olen = 0;
    while (*in && olen < max_out - 1) {
        if (strncmp(in, "DIR_DOMAINS", 11) == 0) {
            const char *p = in + 11;
            while (*p == ' ' || *p == '+') p++;
            if (*p == '"') {
                /* Output: "/domains  (replaces DIR_DOMAINS + ") */
                out[olen++] = '"';
                const char *pfx = "/domains";
                while (*pfx && olen < max_out - 1) out[olen++] = *pfx++;
                in = p + 1;  /* skip past the opening " */
                continue;
            }
        }
        if (strncmp(in, "DIR_STD", 7) == 0) {
            const char *p = in + 7;
            while (*p == ' ' || *p == '+') p++;
            if (*p == '"') {
                out[olen++] = '"';
                const char *pfx = "/std";
                while (*pfx && olen < max_out - 1) out[olen++] = *pfx++;
                in = p + 1;
                continue;
            }
        }
        out[olen++] = *in++;
    }
    out[olen] = '\0';
}

/* Extract and concatenate all quoted strings from a setter call.
 * Handles multiline string concatenation with + or adjacent strings.
 * Example: set_short("Town Square") or set_long("line1\n" + "line2\n")
 * Returns malloc'd string or NULL. */
static char* room_extract_string(const char *buf, const char *setter_name) {
    const char *p = strstr(buf, setter_name);
    if (!p) return NULL;

    p += strlen(setter_name);

    /* Find opening paren */
    while (*p && *p != '(') p++;
    if (!*p) return NULL;
    p++;

    /* Track parenthesis nesting so we stop at the matching ) */
    int depth = 1;
    char result[16384];
    size_t rlen = 0;

    while (*p && depth > 0) {
        if (*p == '(') {
            depth++;
            p++;
        } else if (*p == ')') {
            depth--;
            if (depth == 0) break;
            p++;
        } else if (*p == '"') {
            p++;  /* skip opening quote */
            while (*p && !(*p == '"' && *(p - 1) != '\\')) {
                if (*p == '\\' && p[1]) {
                    switch (p[1]) {
                        case 'n':  if (rlen < sizeof(result)-1) result[rlen++] = '\n'; break;
                        case 't':  if (rlen < sizeof(result)-1) result[rlen++] = '\t'; break;
                        case '\\': if (rlen < sizeof(result)-1) result[rlen++] = '\\'; break;
                        case '"':  if (rlen < sizeof(result)-1) result[rlen++] = '"'; break;
                        default:
                            if (rlen < sizeof(result)-2) {
                                result[rlen++] = '\\';
                                result[rlen++] = p[1];
                            }
                            break;
                    }
                    p += 2;
                } else {
                    if (rlen < sizeof(result)-1) result[rlen++] = *p;
                    p++;
                }
            }
            if (*p == '"') p++;  /* skip closing quote */
        } else {
            p++;  /* skip whitespace, +, newlines, etc. */
        }
    }

    result[rlen] = '\0';
    return rlen > 0 ? strdup(result) : NULL;
}

/* Parse all add_exit("direction", "path") calls from LPC source.
 * Populates exits_out array, returns count. */
static int room_parse_add_exits(const char *buf, RoomExit **exits_out) {
    int count = 0;
    int capacity = 8;
    RoomExit *exits = malloc(sizeof(RoomExit) * capacity);

    const char *p = buf;
    while ((p = strstr(p, "add_exit(")) != NULL) {
        p += 9;  /* skip "add_exit(" */

        /* First quoted string: direction */
        const char *q = strchr(p, '"');
        if (!q) break;
        q++;
        const char *end = strchr(q, '"');
        if (!end) break;

        size_t dlen = end - q;
        char *direction = malloc(dlen + 1);
        memcpy(direction, q, dlen);
        direction[dlen] = '\0';

        /* Second quoted string: path */
        q = strchr(end + 1, '"');
        if (!q) { free(direction); break; }
        q++;
        end = strchr(q, '"');
        if (!end) { free(direction); break; }

        size_t plen = end - q;
        char *path = malloc(plen + 1);
        memcpy(path, q, plen);
        path[plen] = '\0';

        if (count >= capacity) {
            capacity *= 2;
            exits = realloc(exits, sizeof(RoomExit) * capacity);
        }
        exits[count].direction = direction;
        exits[count].target_path = path;
        count++;

        p = end + 1;
    }

    *exits_out = count > 0 ? exits : NULL;
    if (count == 0) free(exits);
    return count;
}

/* Parse set_exits(([ "dir": "path", ... ])) mapping from LPC source.
 * Populates exits_out array, returns count. */
static int room_parse_set_exits(const char *buf, RoomExit **exits_out) {
    const char *p = strstr(buf, "set_exits(");
    if (!p) { *exits_out = NULL; return 0; }

    p = strstr(p, "([");
    if (!p) { *exits_out = NULL; return 0; }
    p += 2;

    const char *map_end = strstr(p, "])");
    if (!map_end) { *exits_out = NULL; return 0; }

    int count = 0;
    int capacity = 8;
    RoomExit *exits = malloc(sizeof(RoomExit) * capacity);

    while (p < map_end) {
        /* Find "key" */
        const char *q = strchr(p, '"');
        if (!q || q >= map_end) break;
        q++;
        const char *ke = strchr(q, '"');
        if (!ke || ke >= map_end) break;

        size_t klen = ke - q;
        char *key = malloc(klen + 1);
        memcpy(key, q, klen);
        key[klen] = '\0';

        /* Find : separator */
        p = strchr(ke + 1, ':');
        if (!p || p >= map_end) { free(key); break; }
        p++;

        /* Find "value" */
        q = strchr(p, '"');
        if (!q || q >= map_end) { free(key); break; }
        q++;
        const char *ve = strchr(q, '"');
        if (!ve || ve >= map_end) { free(key); break; }

        size_t vlen = ve - q;
        char *value = malloc(vlen + 1);
        memcpy(value, q, vlen);
        value[vlen] = '\0';

        if (count >= capacity) {
            capacity *= 2;
            exits = realloc(exits, sizeof(RoomExit) * capacity);
        }
        exits[count].direction = key;
        exits[count].target_path = value;
        count++;

        p = ve + 1;
    }

    *exits_out = count > 0 ? exits : NULL;
    if (count == 0) free(exits);
    return count;
}

/* Parse set_items(([ "keyword": "description", ... ])) from LPC source.
 * Populates details_out array, returns count. */
static int room_parse_set_items(const char *buf, RoomDetail **details_out) {
    const char *p = strstr(buf, "set_items(");
    if (!p) { *details_out = NULL; return 0; }

    p = strstr(p, "([");
    if (!p) { *details_out = NULL; return 0; }
    p += 2;

    const char *map_end = strstr(p, "])");
    if (!map_end) { *details_out = NULL; return 0; }

    int count = 0;
    int capacity = 8;
    RoomDetail *details = malloc(sizeof(RoomDetail) * capacity);

    while (p < map_end) {
        const char *q = strchr(p, '"');
        if (!q || q >= map_end) break;
        q++;
        const char *ke = strchr(q, '"');
        if (!ke || ke >= map_end) break;

        size_t klen = ke - q;
        char *keyword = malloc(klen + 1);
        memcpy(keyword, q, klen);
        keyword[klen] = '\0';

        p = strchr(ke + 1, ':');
        if (!p || p >= map_end) { free(keyword); break; }
        p++;

        q = strchr(p, '"');
        if (!q || q >= map_end) { free(keyword); break; }
        q++;
        const char *ve = strchr(q, '"');
        if (!ve || ve >= map_end) { free(keyword); break; }

        size_t vlen = ve - q;
        char *desc = malloc(vlen + 1);
        memcpy(desc, q, vlen);
        desc[vlen] = '\0';

        if (count >= capacity) {
            capacity *= 2;
            details = realloc(details, sizeof(RoomDetail) * capacity);
        }
        details[count].keyword = keyword;
        details[count].description = desc;
        count++;

        p = ve + 1;
    }

    *details_out = count > 0 ? details : NULL;
    if (count == 0) free(details);
    return count;
}

/* Parse set_property("key", value) occurrences and set simple flags on Room.
 * Supported keys: "light" (int), "indoors" (0/1), "no_magic" (0/1), "no_combat" (0/1)
 */
static void room_parse_properties(const char *buf, Room *room) {
    const char *p = buf;
    while ((p = strstr(p, "set_property(")) != NULL) {
        p += strlen("set_property(");

        /* Skip whitespace */
        while (*p && (*p == ' ' || *p == '\t' || *p == '\n')) p++;

        /* Expect first argument: quoted key */
        const char *q = strchr(p, '"');
        if (!q) break;
        q++;
        const char *qe = strchr(q, '"');
        if (!qe) break;
        size_t klen = qe - q;
        char key[64];
        if (klen >= sizeof(key)) klen = sizeof(key)-1;
        memcpy(key, q, klen);
        key[klen] = '\0';

        /* Find comma after key */
        const char *comma = strchr(qe, ',');
        if (!comma) { p = qe + 1; continue; }
        p = comma + 1;

        /* Skip whitespace */
        while (*p && (*p == ' ' || *p == '\t' || *p == '\n')) p++;

        /* Read numeric value (or quoted number) */
        int val = 0;
        if (*p == '"') {
            p++;
            const char *ve = strchr(p, '"');
            if (ve) {
                char vbuf[32];
                size_t vlen = ve - p;
                if (vlen >= sizeof(vbuf)) vlen = sizeof(vbuf)-1;
                memcpy(vbuf, p, vlen); vbuf[vlen] = '\0';
                val = atoi(vbuf);
            }
        } else {
            val = atoi(p);
        }

        /* Apply recognized properties */
        if (strcasecmp(key, "light") == 0) {
            if (val < 0) val = 0;
            if (val > 3) val = 3;
            room->light_level = val;
        } else if (strcasecmp(key, "indoors") == 0) {
            room->is_indoors = (val != 0);
        } else if (strcasecmp(key, "no_magic") == 0) {
            room->no_magic = (val != 0);
        } else if (strcasecmp(key, "no_combat") == 0) {
            room->no_combat = (val != 0);
        }

        p = qe + 1;
    }
}

/* ========== LPC ROOM LOADING ========== */

/* Load a room from an LPC file by text-scraping its setter calls.
 * Assigns an auto-incrementing ID and registers in the path table.
 * Documentation: docs/lpc-room-system.md
 * Note: this loader uses static text parsing of common setter calls
 * and does NOT execute LPC code. See the documentation for limitations.
 */
static Room* room_load_from_lpc(const char *lpc_path) {
    /* Resolve LPC path to filesystem path */
    char fs_path[512];
    if (lpc_path[0] == '/') {
        snprintf(fs_path, sizeof(fs_path), "lib%s.lpc", lpc_path);
    } else {
        snprintf(fs_path, sizeof(fs_path), "lib/%s.lpc", lpc_path);
    }

    /* Also try without .lpc extension (already has it) */
    if (access(fs_path, R_OK) != 0) {
        /* Try as-is (maybe path already includes lib/ or .lpc) */
        size_t plen = strlen(lpc_path);
        if (plen > 4 && strcmp(lpc_path + plen - 4, ".lpc") == 0) {
            if (lpc_path[0] == '/') {
                snprintf(fs_path, sizeof(fs_path), "lib%s", lpc_path);
            } else {
                snprintf(fs_path, sizeof(fs_path), "lib/%s", lpc_path);
            }
        }
    }

    FILE *f = fopen(fs_path, "r");
    if (!f) {
        fprintf(stderr, "[Room] Failed to open LPC room '%s' (%s): %s\n",
                lpc_path, fs_path, strerror(errno));
        return NULL;
    }

    /* Read entire file */
    char raw[16384];
    size_t n = fread(raw, 1, sizeof(raw) - 1, f);
    fclose(f);
    raw[n] = '\0';

    /* Preprocess macros (DIR_DOMAINS, DIR_STD) */
    char buf[16384];
    preprocess_lpc_macros(buf, raw, sizeof(buf));

    /* Allocate room */
    Room *room = calloc(1, sizeof(Room));
    if (!room) return NULL;

    room->id = next_lpc_room_id++;
    room->lpc_path = strdup(lpc_path);
    /* Default room properties */
    room->light_level = 2; /* normal/lit */
    room->is_indoors = false;
    room->no_magic = false;
    room->no_combat = false;

    /* Initialize cardinal exits to -1 (unused for LPC rooms) */
    room->exits.north = -1;
    room->exits.south = -1;
    room->exits.east = -1;
    room->exits.west = -1;
    room->exits.up = -1;
    room->exits.down = -1;

    /* Extract properties via text-scraping */
    room->name = room_extract_string(buf, "set_short");
    if (!room->name) room->name = strdup("An LPC Room");

    room->description = room_extract_string(buf, "set_long");
    if (!room->description) room->description = strdup("An empty room.");

    /* Parse exits: try add_exit() calls first, then set_exits() mapping */
    RoomExit *exits = NULL;
    int exit_count = room_parse_add_exits(buf, &exits);
    if (exit_count == 0) {
        exit_count = room_parse_set_exits(buf, &exits);
    }
    room->flex_exits = exits;
    room->num_flex_exits = exit_count;

    /* Parse examinable details from set_items() */
    room->details = NULL;
    room->num_details = room_parse_set_items(buf, &room->details);

    /* Parse set_property(...) calls for light/indoors/no_magic/no_combat */
    room_parse_properties(buf, room);

    /* Initialize player tracking */
    room->players = calloc(10, sizeof(PlayerSession*));
    room->num_players = 0;
    room->max_players = 10;
    room->items = NULL;

    /* Register in LPC room pool */
    if (num_lpc_rooms >= max_lpc_rooms) {
        max_lpc_rooms = max_lpc_rooms == 0 ? 32 : max_lpc_rooms * 2;
        lpc_rooms = realloc(lpc_rooms, sizeof(Room*) * max_lpc_rooms);
    }
    lpc_rooms[num_lpc_rooms++] = room;

    /* Register in path lookup table */
    if (num_path_entries >= max_path_entries) {
        max_path_entries = max_path_entries == 0 ? 64 : max_path_entries * 2;
        path_table = realloc(path_table, sizeof(RoomPathEntry) * max_path_entries);
    }
    path_table[num_path_entries].path = strdup(lpc_path);
    path_table[num_path_entries].room = room;
    num_path_entries++;

    fprintf(stderr, "[Room] Loaded LPC room '%s' (id=%d, %d exits, %d details) from %s\n",
            room->name, room->id, room->num_flex_exits, room->num_details, fs_path);

    /* Auto-spawn items for specific LPC rooms */
    if (strcmp(lpc_path, "/domains/start/lake_far_shore") == 0) {
        Item *hilt = item_create(50);  /* Techno-Wizard Hilt */
        if (hilt) {
            room_add_item(room, hilt);
            fprintf(stderr, "[Room] Spawned Techno-Wizard Hilt in lake_far_shore\n");
        }
    }

    return room;
}

/* Look up an LPC room by path, loading it on-demand if not cached. */
Room* room_get_by_path(const char *lpc_path) {
    if (!lpc_path) return NULL;

    /* Check path table for already-loaded room */
    for (int i = 0; i < num_path_entries; i++) {
        if (strcmp(path_table[i].path, lpc_path) == 0) {
            return path_table[i].room;
        }
    }

    /* Not cached - load on demand */
    return room_load_from_lpc(lpc_path);
}

/* Reload an LPC room from disk, updating the cached Room in place.
 * Players in the room stay; only description/exits/details refresh. */
Room* room_reload_lpc(const char *lpc_path) {
    if (!lpc_path) return NULL;

    /* Find existing cached room */
    Room *old_room = NULL;
    int cache_idx = -1;
    for (int i = 0; i < num_path_entries; i++) {
        if (strcmp(path_table[i].path, lpc_path) == 0) {
            old_room = path_table[i].room;
            cache_idx = i;
            break;
        }
    }

    if (!old_room) {
        /* Not cached yet, just load fresh */
        return room_load_from_lpc(lpc_path);
    }

    /* Load the new version into a temporary room */
    /* Temporarily remove from cache so room_load_from_lpc creates a new entry */
    /* Instead, load the file directly and update the existing room in place */

    /* Resolve path */
    char fs_path[512];
    if (lpc_path[0] == '/') {
        snprintf(fs_path, sizeof(fs_path), "lib%s.lpc", lpc_path);
    } else {
        snprintf(fs_path, sizeof(fs_path), "lib/%s.lpc", lpc_path);
    }
    if (access(fs_path, R_OK) != 0) {
        size_t plen = strlen(lpc_path);
        if (plen > 4 && strcmp(lpc_path + plen - 4, ".lpc") == 0) {
            if (lpc_path[0] == '/') {
                snprintf(fs_path, sizeof(fs_path), "lib%s", lpc_path);
            } else {
                snprintf(fs_path, sizeof(fs_path), "lib/%s", lpc_path);
            }
        }
    }

    FILE *f = fopen(fs_path, "r");
    if (!f) {
        fprintf(stderr, "[Room] reload failed: cannot open '%s'\n", fs_path);
        return NULL;
    }

    char raw[16384];
    size_t len = fread(raw, 1, sizeof(raw) - 1, f);
    fclose(f);
    raw[len] = '\0';

    /* Free old description data (keep players, keep id) */
    if (old_room->name) free(old_room->name);
    if (old_room->description) free(old_room->description);
    for (int i = 0; i < old_room->num_flex_exits; i++) {
        if (old_room->flex_exits[i].direction) free(old_room->flex_exits[i].direction);
        if (old_room->flex_exits[i].target_path) free(old_room->flex_exits[i].target_path);
    }
    free(old_room->flex_exits);
    old_room->flex_exits = NULL;
    old_room->num_flex_exits = 0;
    for (int i = 0; i < old_room->num_details; i++) {
        if (old_room->details[i].keyword) free(old_room->details[i].keyword);
        if (old_room->details[i].description) free(old_room->details[i].description);
    }
    free(old_room->details);
    old_room->details = NULL;
    old_room->num_details = 0;

    /* Re-parse set_short */
    old_room->name = strdup("Reloaded Room");
    char *short_start = strstr(raw, "set_short(");
    if (short_start) {
        char *q1 = strchr(short_start, '"');
        if (q1) {
            char *q2 = strchr(q1 + 1, '"');
            if (q2) {
                free(old_room->name);
                int slen = (int)(q2 - q1 - 1);
                old_room->name = strndup(q1 + 1, slen);
            }
        }
    }

    /* Re-parse set_long */
    old_room->description = strdup("");
    char *long_start = strstr(raw, "set_long(");
    if (long_start) {
        /* Collect all quoted string fragments between set_long( and ); */
        char desc_buf[4096] = "";
        int desc_pos = 0;
        char *p = long_start + 9;
        while (*p && !(p[0] == ')' && p[1] == ';')) {
            if (*p == '"') {
                p++;
                while (*p && *p != '"') {
                    if (*p == '\\' && p[1] == 'n') {
                        if (desc_pos < (int)sizeof(desc_buf) - 2) desc_buf[desc_pos++] = '\n';
                        p += 2;
                    } else {
                        if (desc_pos < (int)sizeof(desc_buf) - 1) desc_buf[desc_pos++] = *p;
                        p++;
                    }
                }
                if (*p == '"') p++;
            } else {
                p++;
            }
        }
        desc_buf[desc_pos] = '\0';
        free(old_room->description);
        old_room->description = strdup(desc_buf);
    }

    /* Re-parse add_exit */
    {
        int max_exits = 16;
        old_room->flex_exits = calloc(max_exits, sizeof(RoomExit));
        old_room->num_flex_exits = 0;

        char *pos = raw;
        while ((pos = strstr(pos, "add_exit(")) != NULL) {
            char *q1 = strchr(pos, '"');
            if (!q1) break;
            char *q2 = strchr(q1 + 1, '"');
            if (!q2) break;
            char *q3 = strchr(q2 + 1, '"');
            if (!q3) break;
            char *q4 = strchr(q3 + 1, '"');
            if (!q4) break;

            int dlen = (int)(q2 - q1 - 1);
            int plen2 = (int)(q4 - q3 - 1);

            if (old_room->num_flex_exits < max_exits) {
                old_room->flex_exits[old_room->num_flex_exits].direction = strndup(q1 + 1, dlen);
                old_room->flex_exits[old_room->num_flex_exits].target_path = strndup(q3 + 1, plen2);
                old_room->num_flex_exits++;
            }
            pos = q4 + 1;
        }
    }

    /* Re-parse set_property */
    old_room->light_level = 2;
    old_room->is_indoors = 0;
    old_room->no_magic = 0;
    old_room->no_combat = 0;
    {
        char *pos = raw;
        while ((pos = strstr(pos, "set_property(")) != NULL) {
            char *q1 = strchr(pos, '"');
            if (!q1) break;
            char *q2 = strchr(q1 + 1, '"');
            if (!q2) break;
            int klen = (int)(q2 - q1 - 1);
            char key[64];
            if (klen >= (int)sizeof(key)) klen = sizeof(key) - 1;
            memcpy(key, q1 + 1, klen);
            key[klen] = '\0';

            /* Find the value after the comma */
            char *comma = strchr(q2, ',');
            int val = 0;
            if (comma) {
                val = atoi(comma + 1);
            }

            if (strcmp(key, "light") == 0) old_room->light_level = val;
            else if (strcmp(key, "indoors") == 0) old_room->is_indoors = val;
            else if (strcmp(key, "no_magic") == 0) old_room->no_magic = val;
            else if (strcmp(key, "no_fight") == 0 || strcmp(key, "no_combat") == 0) old_room->no_combat = val;

            pos = q2 + 1;
        }
    }

    fprintf(stderr, "[Room] Reloaded LPC room '%s' from %s\n", old_room->name, fs_path);
    return old_room;
}

/* Find an examinable detail in a room by keyword (case-insensitive). */
const char* room_find_detail(Room *room, const char *keyword) {
    if (!room || !keyword) return NULL;
    for (int i = 0; i < room->num_details; i++) {
        if (strcasecmp(room->details[i].keyword, keyword) == 0) {
            return room->details[i].description;
        }
    }
    return NULL;
}

/* Check if input matches a flex exit direction (with cardinal abbreviations). */
static int direction_matches(const char *input, const char *exit_dir) {
    if (strcasecmp(input, exit_dir) == 0) return 1;
    if (strlen(input) == 1) {
        char c = tolower((unsigned char)input[0]);
        if (c == 'n' && strcasecmp(exit_dir, "north") == 0) return 1;
        if (c == 's' && strcasecmp(exit_dir, "south") == 0) return 1;
        if (c == 'e' && strcasecmp(exit_dir, "east") == 0) return 1;
        if (c == 'w' && strcasecmp(exit_dir, "west") == 0) return 1;
        if (c == 'u' && strcasecmp(exit_dir, "up") == 0) return 1;
        if (c == 'd' && strcasecmp(exit_dir, "down") == 0) return 1;
    }
    return 0;
}

/* Helper to initialize a room */
static void init_room(int id, const char *name, const char *desc,
                      int n, int s, int e, int w, int u, int d) {
    Room *r = &world_rooms[id];
    r->id = id;
    r->name = strdup(name);
    r->description = strdup(desc);
    r->exits.north = n;
    r->exits.south = s;
    r->exits.east = e;
    r->exits.west = w;
    r->exits.up = u;
    r->exits.down = d;
    r->items = NULL;
    r->players = calloc(10, sizeof(PlayerSession*));
    r->num_players = 0;
    r->max_players = 10;
    /* Default C room properties */
    r->light_level = 2;
    r->is_indoors = false;
    r->no_magic = false;
    r->no_combat = false;
}

/* Initialize the game world */
void room_init_world(void) {
    /* Room 0: The Void (starting room) */
    Room *void_room = &world_rooms[0];
    void_room->id = 0;
    void_room->name = strdup("The Void");
    void_room->description = strdup(
        "You stand in an endless expanse of swirling energy and mist.\n"
        "This liminal space exists between worlds, a nexus of possibilities.\n"
        "To the north, you sense the pull of civilization."
    );
    void_room->exits.north = 1;
    void_room->exits.south = -1;
    void_room->exits.east = -1;
    void_room->exits.west = -1;
    void_room->exits.up = -1;
    void_room->exits.down = -1;
    void_room->items = NULL;
    void_room->players = calloc(10, sizeof(PlayerSession*));
    void_room->num_players = 0;
    void_room->max_players = 10;
    
    /* Room 1: Town Plaza */
    Room *plaza = &world_rooms[1];
    plaza->id = 1;
    plaza->name = strdup("Chi-Town Plaza");
    plaza->description = strdup(
        "A bustling town square in the heart of Chi-Town. Coalition troops patrol\n"
        "the perimeter while traders hawk their wares from makeshift stalls.\n"
        "The towering spires of Coalition headquarters rise to the east.\n"
        "To the west lies the merchant district, and south returns to the void."
    );
    plaza->exits.north = 18;
    plaza->exits.south = 0;
    plaza->exits.east = 2;
    plaza->exits.west = 3;
    plaza->exits.up = -1;
    plaza->exits.down = -1;
    plaza->items = NULL;
    plaza->players = calloc(10, sizeof(PlayerSession*));
    plaza->num_players = 0;
    plaza->max_players = 10;
    
    /* Room 2: Coalition HQ Entrance */
    Room *hq = &world_rooms[2];
    hq->id = 2;
    hq->name = strdup("Coalition Headquarters - Entrance");
    hq->description = strdup(
        "Massive adamantium doors loom before you, flanked by heavily armed\n"
        "SAMAS power armor suits. This is the nerve center of Coalition authority.\n"
        "Only the plaza to the west offers escape."
    );
    hq->exits.north = -1;
    hq->exits.south = -1;
    hq->exits.east = -1;
    hq->exits.west = 1;
    hq->exits.up = -1;
    hq->exits.down = -1;
    hq->items = NULL;
    hq->players = calloc(10, sizeof(PlayerSession*));
    hq->num_players = 0;
    hq->max_players = 10;
    
    /* Room 3: Merchant District */
    Room *market = &world_rooms[3];
    market->id = 3;
    market->name = strdup("Merchant District");
    market->description = strdup(
        "A narrow street lined with shops selling everything from energy weapons\n"
        "to magical trinkets. The air smells of oil and ozone. Merchants call out,\n"
        "trying to attract customers. The plaza lies to the east."
    );
    market->exits.north = -1;
    market->exits.south = -1;
    market->exits.east = 1;
    market->exits.west = -1;
    market->exits.up = -1;
    market->exits.down = -1;
    market->items = NULL;
    market->players = calloc(10, sizeof(PlayerSession*));
    market->num_players = 0;
    market->max_players = 10;
    
    /* ============================================================ */
    /* NEW CAMELOT (Rooms 4-10) - LPC-backed stubs                  */
    /* Actual room data loaded on-demand from lib/domains/new_camelot/ */
    /* ============================================================ */
    init_room(4, "New Camelot - Town Square", "", -1, -1, -1, -1, -1, -1);
    init_room(5, "The Silver Unicorn Tavern", "", -1, -1, -1, -1, -1, -1);
    init_room(6, "Training Grounds", "", -1, -1, -1, -1, -1, -1);
    init_room(7, "Blacksmith's Forge", "", -1, -1, -1, -1, -1, -1);
    init_room(8, "Chapel of Light", "", -1, -1, -1, -1, -1, -1);
    init_room(9, "Stables", "", -1, -1, -1, -1, -1, -1);
    init_room(10, "New Camelot Gate", "", -1, -1, -1, -1, -1, -1);

    /* ============================================================ */
    /* SPLYNN (Rooms 11-17)                                         */
    /* Layout:                                                      */
    /* [17: Temple]--[15: Bazaar]--[11: Market]--[13: Bio-Wizard]   */
    /*                    |             |                            */
    /*                [16: Docks]  [12: Slaves]--[14: Arena]        */
    /* ============================================================ */

    init_room(11, "Splynn - Market Center",
        "The heart of Splynn, a dimensional market city ruled by the\n"
        "Splugorth. Alien beings of every description crowd the streets.\n"
        "The air crackles with residual magical energy and the babble of\n"
        "a hundred languages fills the air. A shimmering Moxim figure\n"
        "stands in the center of the chaos, offering passage elsewhere.",
        12, -1, 13, 15, -1, -1);

    init_room(12, "Slave Market",
        "Rows of cages and pens hold beings of every species. Slavers\n"
        "call out prices while buyers inspect the merchandise with cold\n"
        "eyes. Kittani overseers watch the proceedings with whips coiled\n"
        "at their sides. The market center is to the south.",
        -1, 11, 14, -1, -1, -1);

    init_room(13, "Bio-Wizard Shop",
        "Shelves of living organisms and bio-magical creations line the\n"
        "walls. Jars of glowing fluid hold specimens that twitch and pulse.\n"
        "The proprietor, a Kittani bio-wizard, tends to writhing specimens\n"
        "on a stone table. The market center is to the west.",
        -1, -1, -1, 11, -1, -1);

    init_room(14, "Arena Entrance",
        "The gates to Splynn's gladiatorial arena. The roar of the crowd\n"
        "echoes from within as combatants fight for survival and glory.\n"
        "Blood stains mark the stone floor. Bookmakers take wagers near\n"
        "the entrance. The slave market is to the west.",
        -1, -1, -1, 12, -1, -1);

    init_room(15, "Dimensional Bazaar",
        "Merchants from a hundred dimensions hawk exotic wares from stalls\n"
        "that seem to shift and change. Portal energy crackles in the air.\n"
        "Strange artifacts, alien weapons, and magical items of unknown\n"
        "origin fill every surface. The market is east, docks south.",
        -1, 16, 11, 17, -1, -1);

    init_room(16, "Splynn Docks",
        "Wooden docks extend over dark waters that seem to swirl with\n"
        "unnatural currents. Strange ships from other dimensions bob at\n"
        "anchor. Longshoremen of various alien species load and unload\n"
        "cargo. The dimensional bazaar lies to the north.",
        15, -1, -1, -1, -1, -1);

    init_room(17, "Temple of the Splugorth",
        "A towering structure of alien architecture that defies geometry.\n"
        "The walls seem to breathe and the floor pulses with a slow rhythm.\n"
        "The oppressive presence of the Splugorth intelligence weighs on\n"
        "your mind. Few come here willingly. The bazaar is to the east.",
        -1, -1, 15, -1, -1, -1);

    /* ============================================================ */
    /* CHI-TOWN EXPANSION (Rooms 18-23)                             */
    /* Layout:                                                      */
    /*                [23: Transit Hub (Moxim)]                     */
    /*                    |                                          */
    /*                [22: Medical Center]                           */
    /*                    |                                          */
    /* [20: Underground]--[21: Residential]                          */
    /*                    |                                          */
    /*                [19: Recruitment]                              */
    /*                    |                                          */
    /*                [18: Barracks]                                 */
    /*                    |                                          */
    /*                [1: Plaza] (existing)                          */
    /* ============================================================ */

    init_room(18, "Chi-Town Barracks",
        "Coalition military barracks. Rows of bunks line the walls and\n"
        "soldiers clean their weapons and gear. The smell of gun oil\n"
        "and boot polish fills the air. Discipline is strict here and\n"
        "conversation is kept to low murmurs. The plaza is to the south.",
        19, 1, -1, -1, -1, -1);

    init_room(19, "Recruitment Center",
        "A Coalition recruitment office. Posters on the walls encourage\n"
        "citizens to join the fight against supernatural threats. A bored\n"
        "sergeant sits behind a desk piled with paperwork. Eager young\n"
        "recruits wait on benches along the wall.",
        21, 18, -1, -1, -1, -1);

    init_room(20, "Underground Market",
        "A dimly lit black market hidden beneath the streets of Chi-Town.\n"
        "Goods the Coalition would consider contraband change hands here\n"
        "in whispered deals. Magic items, alien artifacts, and illegal\n"
        "weapons can be found if you know who to ask.",
        -1, -1, 21, -1, -1, -1);

    init_room(21, "Residential Block",
        "A residential area of Chi-Town. Families go about their daily\n"
        "lives in cramped but orderly apartments. Children play in the\n"
        "corridors under the watchful eye of Coalition security cameras.\n"
        "The recruitment center is south, medical center north.",
        22, 19, -1, 20, -1, -1);

    init_room(22, "Medical Center",
        "A Coalition medical facility with white walls and harsh lighting.\n"
        "Nurses and doctors tend to the sick and wounded. The smell of\n"
        "antiseptic hangs heavy in the air. Gurneys line the corridors\n"
        "and medical equipment hums quietly.",
        23, 21, -1, -1, -1, -1);

    init_room(23, "Chi-Town Transit Hub",
        "A large transit hub with arrivals and departures boards displaying\n"
        "routes across the Coalition States. The constant flow of travelers\n"
        "and soldiers creates a steady hum of activity. A shimmering Moxim\n"
        "figure stands near the main platform, offering passage to distant\n"
        "lands. The medical center is to the south.",
        -1, 22, -1, -1, -1, -1);

    num_rooms = 24;

    fprintf(stderr, "[Room] Initialized %d rooms\n", num_rooms);
}

/* Cleanup world */
void room_cleanup_world(void) {
    /* Free bootstrap rooms */
    for (int i = 0; i < num_rooms; i++) {
        if (world_rooms[i].name) free(world_rooms[i].name);
        if (world_rooms[i].description) free(world_rooms[i].description);
        if (world_rooms[i].players) free(world_rooms[i].players);
    }

    /* Free LPC rooms */
    for (int i = 0; i < num_lpc_rooms; i++) {
        Room *r = lpc_rooms[i];
        if (!r) continue;
        if (r->name) free(r->name);
        if (r->description) free(r->description);
        if (r->lpc_path) free(r->lpc_path);
        if (r->players) free(r->players);
        for (int j = 0; j < r->num_flex_exits; j++) {
            free(r->flex_exits[j].direction);
            free(r->flex_exits[j].target_path);
        }
        free(r->flex_exits);
        for (int j = 0; j < r->num_details; j++) {
            free(r->details[j].keyword);
            free(r->details[j].description);
        }
        free(r->details);
        /* Free ground items */
        Item *item = r->items;
        while (item) {
            Item *next = item->next;
            item_free(item);
            item = next;
        }
        free(r);
    }
    free(lpc_rooms);
    lpc_rooms = NULL;
    num_lpc_rooms = 0;
    max_lpc_rooms = 0;

    /* Free path table */
    for (int i = 0; i < num_path_entries; i++) {
        free(path_table[i].path);
    }
    free(path_table);
    path_table = NULL;
    num_path_entries = 0;
    max_path_entries = 0;
}

/* Room ID -> LPC path redirect table.
 * When a stub room ID is requested, the driver loads and returns
 * the LPC room instead of the empty C stub. */
static struct {
    int id;
    const char *lpc_path;
} lpc_room_redirects[] = {
    { 4,  "/domains/new_camelot/town_square" },
    { 5,  "/domains/new_camelot/tavern" },
    { 6,  "/domains/new_camelot/training_grounds" },
    { 7,  "/domains/new_camelot/blacksmith_forge" },
    { 8,  "/domains/new_camelot/chapel" },
    { 9,  "/domains/new_camelot/stables" },
    { 10, "/domains/new_camelot/gate" },
};
#define NUM_LPC_REDIRECTS (sizeof(lpc_room_redirects) / sizeof(lpc_room_redirects[0]))

/* Get room by ID (checks LPC redirects, then bootstrap rooms, then LPC pool) */
Room* room_get_by_id(int id) {
    /* Check LPC redirects first (migrated rooms) */
    for (int i = 0; i < (int)NUM_LPC_REDIRECTS; i++) {
        if (lpc_room_redirects[i].id == id) {
            Room *r = room_get_by_path(lpc_room_redirects[i].lpc_path);
            if (r) return r;
            break;  /* fall through to bootstrap stub */
        }
    }

    /* Bootstrap rooms: IDs 0 .. num_rooms-1 */
    if (id >= 0 && id < num_rooms) return &world_rooms[id];

    /* LPC rooms: IDs >= LPC_ROOM_ID_BASE */
    for (int i = 0; i < num_lpc_rooms; i++) {
        if (lpc_rooms[i]->id == id) return lpc_rooms[i];
    }

    return NULL;
}

/* Get starting room */
Room* room_get_start(void) {
    return &world_rooms[0];
}

/* Add player to room */
void room_add_player(Room *room, PlayerSession *player) {
    if (!room || !player) return;
    
    /* Expand array if needed */
    if (room->num_players >= room->max_players) {
        room->max_players *= 2;
        room->players = realloc(room->players, room->max_players * sizeof(PlayerSession*));
    }
    
    room->players[room->num_players++] = player;
}

/* Remove player from room */
void room_remove_player(Room *room, PlayerSession *player) {
    if (!room || !player) return;
    
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] == player) {
            /* Shift remaining players */
            for (int j = i; j < room->num_players - 1; j++) {
                room->players[j] = room->players[j + 1];
            }
            room->num_players--;
            return;
        }
    }
}

/* Add NPC to room */
void room_add_npc(Room *room, NPC *npc) {
    if (!room || !npc) return;
    if (room->num_npcs >= MAX_NPCS_PER_ROOM) return;
    room->npcs[room->num_npcs++] = npc;
}

/* Remove NPC from room */
void room_remove_npc(Room *room, NPC *npc) {
    if (!room || !npc) return;
    for (int i = 0; i < room->num_npcs; i++) {
        if (room->npcs[i] == npc) {
            for (int j = i; j < room->num_npcs - 1; j++) {
                room->npcs[j] = room->npcs[j + 1];
            }
            room->num_npcs--;
            return;
        }
    }
}

/* Add item to room's ground list */
void room_add_item(Room *room, Item *item) {
    if (!room || !item) return;
    item->next = room->items;
    room->items = item;
}

/* Find item in room by name. First try exact (case-insensitive) match,
 * then fall back to substring/keyword match (case-insensitive). */
Item* room_find_item(Room *room, const char *name) {
    if (!room || !name) return NULL;
    Item *curr = room->items;

    /* Exact match first */
    while (curr) {
        if (curr->name && strcasecmp(curr->name, name) == 0) return curr;
        curr = curr->next;
    }

    /* Substring/keyword match (first match wins) */
    curr = room->items;
    while (curr) {
        if (curr->name && strcasestr(curr->name, name) != NULL) return curr;
        curr = curr->next;
    }

    return NULL;
}

/* Remove item from room's ground list (does not free it) */
void room_remove_item(Room *room, Item *item) {
    if (!room || !item) return;
    Item *prev = NULL;
    Item *curr = room->items;
    while (curr) {
        if (curr == item) {
            if (prev) prev->next = curr->next;
            else room->items = curr->next;
            curr->next = NULL;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

/* Broadcast message to all players in room (optionally excluding one) */
void room_broadcast(Room *room, const char *message, PlayerSession *exclude) {
    if (!room || !message) return;
    
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] != exclude && room->players[i]->username) {
            send_to_player(room->players[i], "%s", message);
        }
    }
}

/* Look command */
/* Helper: display a player's examine info to the looker. */
static void look_at_player(PlayerSession *sess, PlayerSession *target) {
    if (target == sess) {
        /* Look at self -> show a brief self-description instead of full sheet */
        send_to_player(sess, "You look at yourself.\n");
        send_to_player(sess, "Name: %s\n", sess->username);
        if (sess->character.description) {
            send_to_player(sess, "%s\n", sess->character.description);
        }
        send_to_player(sess, "Race: %s  O.C.C.: %s\n",
                   sess->character.race ? sess->character.race : "Unknown",
                   sess->character.occ ? sess->character.occ : "Pending");

        /* Health hint (reuse same logic as for others) */
        Character *tch = &sess->character;
        int hp_pct = tch->max_hp > 0 ? (tch->hp * 100 / tch->max_hp) : 100;
        if (hp_pct >= 90)
            send_to_player(sess, "You feel in excellent health.\n");
        else if (hp_pct >= 50)
            send_to_player(sess, "You feel a bit roughed up.\n");
        else if (hp_pct >= 25)
            send_to_player(sess, "You feel seriously wounded.\n");
        else
            send_to_player(sess, "You are barely standing.\n");

        /* Inventory summary */
        int inv_count = sess->character.inventory.item_count;
        if (inv_count == 0) {
            send_to_player(sess, "You are carrying: nothing.\n");
        } else {
            send_to_player(sess, "You are carrying %d item%s. Use 'inventory' to view.\n",
                           inv_count, inv_count == 1 ? "" : "s");
        }

        return;
    }

    /* Check if should show name: wizard targets/viewers always, or if introduced */
    Character *lch = &sess->character;
    int show_name = 0;
    if (target->privilege_level >= 1) show_name = 1;  /* Target is wizard */
    if (sess->privilege_level >= 1) show_name = 1;    /* Viewer is wizard */
    if (!show_name) {
        for (int j = 0; j < lch->introduced_count; j++) {
            if (lch->introduced_to[j] &&
                strcasecmp(lch->introduced_to[j], target->username) == 0) {
                show_name = 1;
                break;
            }
        }
    }

    if (show_name) {
        send_to_player(sess, "You look at %s.\n", target->username);
        if (target->character.description) {
            send_to_player(sess, "%s\n", target->character.description);
        }
        send_to_player(sess, "Race: %s  O.C.C.: %s\n",
                   target->character.race ? target->character.race : "Unknown",
                   target->character.occ ? target->character.occ : "Pending");
    } else {
        const char *race = target->character.race ? target->character.race : "someone";
        char lower_race[128];
        int ri;
        for (ri = 0; race[ri] && ri < 127; ri++)
            lower_race[ri] = tolower((unsigned char)race[ri]);
        lower_race[ri] = '\0';

        int vowel = (lower_race[0] == 'a' || lower_race[0] == 'e' ||
                     lower_race[0] == 'i' || lower_race[0] == 'o' ||
                     lower_race[0] == 'u');
        send_to_player(sess, "You see %s %s.\n",
                      vowel ? "an" : "a", lower_race);
        send_to_player(sess, "Use 'introduce' to learn their identity.\n");
    }

    /* Health hint */
    Character *tch = &target->character;
    int hp_pct = tch->max_hp > 0 ? (tch->hp * 100 / tch->max_hp) : 100;
    if (hp_pct >= 90)
        send_to_player(sess, "They appear to be in good health.\n");
    else if (hp_pct >= 50)
        send_to_player(sess, "They look a bit roughed up.\n");
    else if (hp_pct >= 25)
        send_to_player(sess, "They look seriously wounded.\n");
    else
        send_to_player(sess, "They are barely standing.\n");
}

/* Helper: display item details to looker. */
/* Display the contents of a container item. */
static void look_at_container(PlayerSession *sess, Item *box) {
    /* Header: capitalise name */
    char header[256];
    snprintf(header, sizeof(header), "%s", box->name ? box->name : "container");
    header[0] = (char)toupper((unsigned char)header[0]);
    send_to_player(sess, "%s\n", header);
    if (box->description && box->description[0])
        send_to_player(sess, "%s\n", box->description);

    if (!box->contents) {
        send_to_player(sess, "It is empty.\n");
        return;
    }

    send_to_player(sess, "It contains:\n");
    Item *curr = box->contents;
    int n = 1;
    while (curr) {
        const char *iname = curr->name && curr->name[0] ? curr->name : "something";
        char fmt[256];
        format_item_name(iname, fmt, sizeof(fmt));
        char lc = tolower((unsigned char)fmt[0]);
        int vowel = (lc == 'a' || lc == 'e' || lc == 'i' || lc == 'o' || lc == 'u');
        send_to_player(sess, "  %d. %s %s. (%.1f lbs)\n",
                       n++, vowel ? "An" : "A", fmt, (float)curr->weight);
        curr = curr->next;
    }
    send_to_player(sess, "Type 'get <item> from %s' to retrieve an item.\n",
                   box->name ? box->name : "it");
}

static void look_at_item(PlayerSession *sess, Item *item) {
    send_to_player(sess, "%s (%s)\n", item->name, item_type_to_string(item->type));
    send_to_player(sess, "%s\n", item->description);
    if (item->type == ITEM_WEAPON_MELEE || item->type == ITEM_WEAPON_RANGED) {
        send_to_player(sess, "Damage: %dd%d %s  Weight: %d lbs  Value: %d cr\n",
            item->stats.damage_dice, item->stats.damage_sides,
            item->stats.is_mega_damage ? "MD" : "SDC",
            item->weight, item->value);
    } else if (item->type == ITEM_ARMOR) {
        send_to_player(sess, "AR: %d  MDC/SDC: %d/%d  Weight: %d lbs  Value: %d cr\n",
            item->stats.ar, item->current_durability, item->stats.sdc_mdc,
            item->weight, item->value);
    } else {
        send_to_player(sess, "Weight: %d lbs  Value: %d cr\n",
            item->weight, item->value);
    }
}

void cmd_look(PlayerSession *sess, const char *args) {
    if (!sess || !sess->current_room) {
        send_to_player(sess, "You are nowhere.\n");
        return;
    }

    Room *room = sess->current_room;

    /* ---- LOOK AT TARGET ---- */
    if (args && *args) {
        const char *target = args;

        /* Strip leading "at " if present */
        if (strncasecmp(target, "at ", 3) == 0) {
            target = target + 3;
            while (*target == ' ') target++;
        }

        if (!*target) goto show_room;  /* "look at" with nothing after */

        /* 1. "me" / "self" -> own character sheet */
        if (strcasecmp(target, "me") == 0 || strcasecmp(target, "self") == 0 ||
            strcasecmp(target, "myself") == 0) {
            look_at_player(sess, sess);
            return;
        }

        /* 2. Exact player name match in room */
        for (int i = 0; i < room->num_players; i++) {
            PlayerSession *p = room->players[i];
            if (p && strcasecmp(p->username, target) == 0) {
                look_at_player(sess, p);
                return;
            }
        }

        /* 3. Partial player name match in room */
        {
            int tlen = (int)strlen(target);
            for (int i = 0; i < room->num_players; i++) {
                PlayerSession *p = room->players[i];
                if (p && p != sess && strncasecmp(p->username, target, tlen) == 0) {
                    look_at_player(sess, p);
                    return;
                }
            }
        }

        /* 4. Race name match (for unintroduced players) */
        for (int i = 0; i < room->num_players; i++) {
            PlayerSession *p = room->players[i];
            if (p && p != sess && p->character.race) {
                if (strcasestr(p->character.race, target) != NULL) {
                    look_at_player(sess, p);
                    return;
                }
            }
        }

        /* 5. NPC keyword match */
        {
            NPC *n = npc_find_in_room(room, target);
            if (n) {
                char display[64];
                snprintf(display, sizeof(display), "%s", n->name);
                display[0] = (char)toupper((unsigned char)display[0]);
                send_to_player(sess, "%s\n", display);
                Character *nch = &n->character;
                if (nch->health_type == MDC_ONLY) {
                    send_to_player(sess, "Level %d  MDC: %d/%d\n",
                                   nch->level, nch->mdc, nch->max_mdc);
                } else {
                    send_to_player(sess, "Level %d  HP: %d/%d  SDC: %d/%d\n",
                                   nch->level, nch->hp, nch->max_hp, nch->sdc, nch->max_sdc);
                }
                int hp_pct;
                if (nch->health_type == MDC_ONLY)
                    hp_pct = nch->max_mdc > 0 ? (nch->mdc * 100 / nch->max_mdc) : 100;
                else
                    hp_pct = nch->max_hp > 0 ? (nch->hp * 100 / nch->max_hp) : 100;
                if (hp_pct >= 90)
                    send_to_player(sess, "It appears to be in good health.\n");
                else if (hp_pct >= 50)
                    send_to_player(sess, "It looks a bit roughed up.\n");
                else if (hp_pct >= 25)
                    send_to_player(sess, "It looks seriously wounded.\n");
                else
                    send_to_player(sess, "It is barely standing.\n");
                return;
            }
        }

        /* 6. Room items */
        Item *ritem = room_find_item(room, target);
        if (ritem) {
            if (ritem->is_container)
                look_at_container(sess, ritem);
            else
                look_at_item(sess, ritem);
            return;
        }

        /* 7. Inventory items */
        Item *iitem = inventory_find(&sess->character.inventory, target);
        if (iitem) {
            look_at_item(sess, iitem);
            return;
        }

        /* 8. Room details (examinable scenery from LPC set_items) */
        const char *detail = room_find_detail(room, target);
        if (detail) {
            send_to_player(sess, "%s\n", detail);
            return;
        }

        send_to_player(sess, "You don't see '%s' here.\n", target);
        return;
    }

    /* ---- LOOK AT ROOM (no args) ---- */
show_room:

    if (sess->is_brief) {
        /* Brief mode: room name only */
        send_to_player(sess, "\n%s\n", room->name);
    } else {
        /* Verbose mode: full description only (no room name) */
        send_to_player(sess, "\n%s\n", room->description);
    }
    /* Show light level hints */
    if (room->light_level == 0) {
        send_to_player(sess, "[It is dark here.]\n");
    } else if (room->light_level == 1) {
        send_to_player(sess, "[A dim glow illuminates the area.]\n");
    } else if (room->light_level == 3) {
        send_to_player(sess, "[Bright light fills the room.]\n");
    }
    /* Collect exit directions from both flex exits and cardinal exits */
    int exit_count = 0;
    const char *exit_dirs[32];

    /* Flex exits (LPC rooms) */
    for (int i = 0; i < room->num_flex_exits && exit_count < 32; i++) {
        exit_dirs[exit_count++] = room->flex_exits[i].direction;
    }

    /* Cardinal exits (C bootstrap rooms) - only if no flex exits */
    if (exit_count == 0) {
        if (room->exits.north >= 0) exit_dirs[exit_count++] = "north";
        if (room->exits.south >= 0) exit_dirs[exit_count++] = "south";
        if (room->exits.east >= 0) exit_dirs[exit_count++] = "east";
        if (room->exits.west >= 0) exit_dirs[exit_count++] = "west";
        if (room->exits.up >= 0) exit_dirs[exit_count++] = "up";
        if (room->exits.down >= 0) exit_dirs[exit_count++] = "down";
    }

    if (exit_count == 0) {
        send_to_player(sess, "There are no exits.\n");
    } else if (exit_count == 1) {
        send_to_player(sess, "\033[1;32mThere is one exit: %s\033[0m\n", exit_dirs[0]);
    } else {
        send_to_player(sess, "\033[1;32mThere are %d exits: ", exit_count);
        for (int i = 0; i < exit_count; i++) {
            send_to_player(sess, "%s", exit_dirs[i]);
            if (i < exit_count - 1) {
                send_to_player(sess, ", ");
            }
        }
        send_to_player(sess, "\033[0m\n");
    }

    /* List items on the ground */
    if (room->items) {
        Item *curr = room->items;
        while (curr) {
            char outbuf[256];
            const char *iname = curr->name && curr->name[0] ? curr->name : "something";

            /* Format item name to lowercase except acronyms/proper nouns */
            char fmt_name[256];
            format_item_name(iname, fmt_name, sizeof(fmt_name));

            /* Check for existing article (a/an/the) on the original name */
            char first[32] = "";
            sscanf(iname, "%31s", first);
            int has_article = 0;
            if (first[0]) {
                if (strcasecmp(first, "a") == 0 || strcasecmp(first, "an") == 0 || strcasecmp(first, "the") == 0) {
                    has_article = 1;
                }
            }

            if (!has_article) {
                /* Choose a/an by vowel rule on formatted name, then capitalize */
                char lc = tolower((unsigned char)fmt_name[0]);
                int vowel = (lc == 'a' || lc == 'e' || lc == 'i' || lc == 'o' || lc == 'u');
                snprintf(outbuf, sizeof(outbuf), "%s %s", vowel ? "an" : "a", fmt_name);
                outbuf[0] = (char)toupper((unsigned char)outbuf[0]);
            } else {
                /* Use original short but normalize capitalization of first char */
                snprintf(outbuf, sizeof(outbuf), "%s", iname);
                outbuf[0] = (char)toupper((unsigned char)outbuf[0]);
            }

            /* Ensure trailing punctuation */
            size_t olen = strlen(outbuf);
            if (olen > 0 && outbuf[olen-1] != '.' && outbuf[olen-1] != '!') {
                if (olen + 1 < sizeof(outbuf)) outbuf[olen] = '.', outbuf[olen+1] = '\0';
            }

            send_to_player(sess, "%s\n", outbuf);
            curr = curr->next;
        }
    }

    /* List other players (race if not introduced, name if introduced) */
    if (room->num_players > 1) {
        for (int i = 0; i < room->num_players; i++) {
            PlayerSession *other = room->players[i];
            if (!other || other == sess) continue;

            /* Wizards/admins always show name; also if viewer is wiz or if introduced */
            int show_name = 0;
            if (other->privilege_level >= 1) show_name = 1;  /* Target is wizard */
            if (sess->privilege_level >= 1) show_name = 1;   /* Viewer is wizard */
            if (!show_name) {
                for (int j = 0; j < sess->character.introduced_count; j++) {
                    if (sess->character.introduced_to[j] &&
                        strcasecmp(sess->character.introduced_to[j], other->username) == 0) {
                        show_name = 1;
                        break;
                    }
                }
            }

            const char *position = other->character.position ?
                other->character.position : "is standing around";

            if (show_name) {
                send_to_player(sess, "%s %s.\n", other->username, position);
            } else {
                const char *race = other->character.race;
                if (!race) race = "someone";

                char lower_race[128];
                int j;
                for (j = 0; race[j] && j < 127; j++)
                    lower_race[j] = tolower((unsigned char)race[j]);
                lower_race[j] = '\0';

                int vowel = (lower_race[0] == 'a' || lower_race[0] == 'e' ||
                             lower_race[0] == 'i' || lower_race[0] == 'o' ||
                             lower_race[0] == 'u');
                send_to_player(sess, "%s %s %s.\n",
                              vowel ? "An" : "A", lower_race, position);
            }
        }
    }

    /* List NPCs in room */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive) {
            char display[64];
            snprintf(display, sizeof(display), "%s", n->name);
            display[0] = (char)toupper((unsigned char)display[0]);
            const NpcTemplate *nt = &NPC_TEMPLATES[n->template_id];
            const char *pos = (nt->position_text && nt->position_text[0])
                              ? nt->position_text : "is standing around.";
            send_to_player(sess, "%s %s\n", display, pos);
        }
    }
}

/* Move command - checks flex exits (LPC) first, then cardinal exits (C) */
void cmd_move(PlayerSession *sess, const char *direction) {
    if (!sess || !sess->current_room || !direction) {
        send_to_player(sess, "You can't move.\n");
        return;
    }

    Room *current = sess->current_room;
    Room *next_room = NULL;

    /* Check flexible exits first (LPC rooms) */
    for (int i = 0; i < current->num_flex_exits; i++) {
        if (direction_matches(direction, current->flex_exits[i].direction)) {
            next_room = room_get_by_path(current->flex_exits[i].target_path);
            if (!next_room) {
                send_to_player(sess, "That way seems blocked.\n");
                return;
            }
            break;
        }
    }

    /* Fall back to cardinal exits (C bootstrap rooms) */
    if (!next_room) {
        int next_room_id = -1;
        if (strcmp(direction, "north") == 0 || strcmp(direction, "n") == 0) {
            next_room_id = current->exits.north;
        } else if (strcmp(direction, "south") == 0 || strcmp(direction, "s") == 0) {
            next_room_id = current->exits.south;
        } else if (strcmp(direction, "east") == 0 || strcmp(direction, "e") == 0) {
            next_room_id = current->exits.east;
        } else if (strcmp(direction, "west") == 0 || strcmp(direction, "w") == 0) {
            next_room_id = current->exits.west;
        } else if (strcmp(direction, "up") == 0 || strcmp(direction, "u") == 0) {
            next_room_id = current->exits.up;
        } else if (strcmp(direction, "down") == 0 || strcmp(direction, "d") == 0) {
            next_room_id = current->exits.down;
        }

        if (next_room_id >= 0) {
            next_room = room_get_by_id(next_room_id);
        }
    }

    if (!next_room) {
        send_to_player(sess, "You can't go that way.\n");
        return;
    }

    /* Notify room of departure */
    for (int i = 0; i < current->num_players; i++) {
        if (current->players[i] != sess) {
            if (sess->leave_msg[0]) {
                send_to_player(current->players[i], "%s\n", sess->leave_msg);
            } else {
                send_to_player(current->players[i], "%s leaves %s.\n",
                              sess->username, direction);
            }
        }
    }

    /* Move player */
    room_remove_player(current, sess);
    room_add_player(next_room, sess);
    sess->current_room = next_room;

    /* Notify new room of arrival */
    for (int i = 0; i < next_room->num_players; i++) {
        if (next_room->players[i] != sess) {
            if (sess->enter_msg[0]) {
                send_to_player(next_room->players[i], "%s\n", sess->enter_msg);
            } else {
                send_to_player(next_room->players[i], "%s arrives.\n", sess->username);
            }
        }
    }

    /* Auto-look */
    cmd_look(sess, "");
}

/* Moxim Rift Travel destinations */
/* Moxim NPCs exist in rooms 4 (New Camelot), 11 (Splynn), 23 (Chi-Town) */
#define RIFT_COST 500
#define NUM_RIFT_DESTINATIONS 3

static struct {
    int room_id;
    const char *name;
    const char *keyword;
} rift_destinations[NUM_RIFT_DESTINATIONS] = {
    { 4,  "New Camelot",      "camelot" },
    { 11, "Splynn",           "splynn"  },
    { 23, "Chi-Town Transit", "chitown" },
};

/* Check if a room has a living Moxim NPC */
static int room_has_moxim(int room_id) {
    Room *room = room_get_by_id(room_id);
    if (!room) return 0;
    NPC *moxim = npc_find_in_room(room, "moxim");
    return (moxim != NULL);
}

/* Rift travel command */
void cmd_rift(PlayerSession *sess, const char *args) {
    if (!sess || !sess->current_room) {
        send_to_player(sess, "You are nowhere.\n");
        return;
    }

    int current_id = sess->current_room->id;

    /* Check if a Moxim is present */
    if (!room_has_moxim(current_id)) {
        send_to_player(sess, "There is no Moxim here to open a rift.\n");
        return;
    }

    /* No argument: list destinations */
    if (!args || !args[0]) {
        send_to_player(sess, "\nThe Moxim shimmers and speaks:\n");
        send_to_player(sess, "\"I can open a rift to the following destinations.\"\n");
        send_to_player(sess, "\"Each passage costs %d credits.\"\n\n", RIFT_COST);
        for (int i = 0; i < NUM_RIFT_DESTINATIONS; i++) {
            if (rift_destinations[i].room_id == current_id) continue;
            send_to_player(sess, "  rift %-10s - %s\n",
                rift_destinations[i].keyword, rift_destinations[i].name);
        }
        send_to_player(sess, "\nYou have %d credits.\n", sess->character.credits);
        return;
    }

    /* Find matching destination */
    int dest_idx = -1;
    for (int i = 0; i < NUM_RIFT_DESTINATIONS; i++) {
        if (rift_destinations[i].room_id == current_id) continue;
        if (strcasecmp(args, rift_destinations[i].keyword) == 0 ||
            strcasecmp(args, rift_destinations[i].name) == 0) {
            dest_idx = i;
            break;
        }
    }

    if (dest_idx < 0) {
        send_to_player(sess, "The Moxim says, \"I don't know that destination.\"\n");
        send_to_player(sess, "Type 'rift' to see available destinations.\n");
        return;
    }

    /* Check credits */
    if (sess->character.credits < RIFT_COST) {
        send_to_player(sess, "The Moxim says, \"You need %d credits. You only have %d.\"\n",
            RIFT_COST, sess->character.credits);
        return;
    }

    /* Deduct credits and open the rift — player must "enter rift" to travel */
    sess->character.credits -= RIFT_COST;
    sess->rift_pending = 1;
    sess->rift_dest_id = dest_idx;

    send_to_player(sess, "\nThe Moxim begins weaving dimensional energy...\n");
    send_to_player(sess, "A shimmering rift tears open before you, swirling with light.\n");
    send_to_player(sess, "Destination: %s  (%d credits deducted)\n",
        rift_destinations[dest_idx].name, RIFT_COST);
    send_to_player(sess, "Type 'enter rift' to step through.\n");

    /* Notify others in the departure room */
    Room *current = sess->current_room;
    for (int i = 0; i < current->num_players; i++) {
        if (current->players[i] != sess) {
            send_to_player(current->players[i],
                "The Moxim tears open a shimmering rift. A destination glows within.\n");
        }
    }
}

/* Complete rift travel — called by "enter rift" command */
void cmd_enter_rift(PlayerSession *sess) {
    if (!sess || !sess->rift_pending) {
        send_to_player(sess, "There is no open rift here.\n");
        return;
    }

    int dest_idx = sess->rift_dest_id;
    sess->rift_pending = 0;
    sess->rift_dest_id = -1;

    Room *dest = room_get_by_id(rift_destinations[dest_idx].room_id);
    if (!dest) {
        send_to_player(sess, "The rift flickers and collapses. Something went wrong.\n");
        sess->character.credits += RIFT_COST; /* refund */
        return;
    }

    Room *current = sess->current_room;
    for (int i = 0; i < current->num_players; i++) {
        if (current->players[i] != sess) {
            send_to_player(current->players[i],
                "%s steps into the shimmering rift and vanishes.\n", sess->username);
        }
    }

    room_remove_player(current, sess);
    room_add_player(dest, sess);
    sess->current_room = dest;

    send_to_player(sess, "\nYou step through the rift into blinding light...\n\n");
    send_to_player(sess, "You have %d credits remaining.\n\n", sess->character.credits);

    for (int i = 0; i < dest->num_players; i++) {
        if (dest->players[i] != sess) {
            send_to_player(dest->players[i],
                "A shimmering rift tears open and %s steps through.\n", sess->username);
        }
    }

    cmd_look(sess, "");
}
