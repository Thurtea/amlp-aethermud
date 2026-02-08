/* race_loader.c - Race / O.C.C. data loading and level progression
 *
 * Parses LPC race and OCC definition files from lib/races/ and lib/occs/,
 * applies stat modifiers, health pools, natural weapons, and handles
 * level-up progression with per-level gains.
 */

#include "race_loader.h"
#include "chargen.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/* External */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* XP table (Palladium-inspired, levels 1-15).  Index 0 unused. */
const int XP_TABLE[MAX_LEVEL + 1] = {
    0,        /* L0 placeholder */
    0,        /* L1 */
    2000,     /* L2 */
    4000,     /* L3 */
    8000,     /* L4 */
    16000,    /* L5 */
    25000,    /* L6 */
    35000,    /* L7 */
    50000,    /* L8 */
    70000,    /* L9 */
    95000,    /* L10 */
    130000,   /* L11 */
    180000,   /* L12 */
    240000,   /* L13 */
    320000,   /* L14 */
    420000    /* L15 */
};

/* ------------------------------------------------------------------ */
/*  Utility helpers                                                    */
/* ------------------------------------------------------------------ */

/* Safely add a natural weapon string to character if room */
static void add_natural_weapon(Character *ch, const char *name) {
    if (!ch || !name) return;
    if (ch->natural_weapon_count < 0) ch->natural_weapon_count = 0;
    if (ch->natural_weapon_count >= 8) return;
    ch->natural_weapons[ch->natural_weapon_count] = strdup(name);
    ch->natural_weapon_count++;
}

/* Build filename from display name: spaces -> '_', lowercase */
static void name_to_filename(const char *name, char *out, size_t out_sz) {
    size_t j = 0;
    for (size_t i = 0; name[i] && j + 1 < out_sz; i++) {
        if (name[i] == ' ' || name[i] == '-')
            out[j++] = '_';
        else
            out[j++] = tolower((unsigned char)name[i]);
    }
    out[j] = '\0';
}

/* Read entire file into buffer, caller must free */
static char *read_file_to_buffer(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);
    char *buf = malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t got = fread(buf, 1, (size_t)sz, f);
    buf[got] = '\0';
    fclose(f);
    return buf;
}

/* ------------------------------------------------------------------ */
/*  LPC extraction helpers                                             */
/* ------------------------------------------------------------------ */

char *lpc_extract_string(const char *buf, const char *snake, const char *pascal) {
    if (!buf) return NULL;
    const char *p = NULL;
    if (snake)  p = strstr(buf, snake);
    if (!p && pascal) p = strstr(buf, pascal);
    if (!p) return NULL;
    const char *q = strchr(p, '(');
    if (!q) return NULL;
    q = strchr(q, '"');
    if (!q) return NULL;
    q++;
    const char *end = strchr(q, '"');
    if (!end) return NULL;
    size_t len = end - q;
    char *out = malloc(len + 1);
    if (!out) return NULL;
    memcpy(out, q, len);
    out[len] = '\0';
    return out;
}

int lpc_extract_int(const char *buf, const char *snake, const char *pascal, int default_val) {
    if (!buf) return default_val;
    const char *p = NULL;
    if (snake)  p = strstr(buf, snake);
    if (!p && pascal) p = strstr(buf, pascal);
    if (!p) return default_val;
    const char *q = strchr(p, '(');
    if (!q) return default_val;
    int v = default_val;
    if (sscanf(q, "(%d", &v) == 1) return v;
    return default_val;
}

/*
 * Parse an LPC mapping:  set_func_name(([ "key": val, "key2": val2 ]))
 * Returns number of entries found (0 if not found).
 */
int lpc_extract_mapping_ints(const char *buf, const char *func_name, ParsedMapping *out) {
    if (!buf || !func_name || !out) return 0;
    memset(out, 0, sizeof(*out));

    const char *p = strstr(buf, func_name);
    if (!p) return 0;

    /* Find the "([ " opening */
    const char *open = strstr(p, "([");
    if (!open) return 0;
    /* Find the matching "])" */
    const char *close = strstr(open, "])");
    if (!close) return 0;

    const char *cur = open + 2; /* skip past "([ " */
    while (cur < close && out->count < PARSED_MAP_MAX) {
        /* find next quoted key */
        const char *qs = strchr(cur, '"');
        if (!qs || qs >= close) break;
        qs++;
        const char *qe = strchr(qs, '"');
        if (!qe || qe >= close) break;

        size_t klen = qe - qs;
        if (klen >= 32) klen = 31;
        memcpy(out->keys[out->count], qs, klen);
        out->keys[out->count][klen] = '\0';

        /* find the ':' then the integer value */
        const char *colon = strchr(qe, ':');
        if (!colon || colon >= close) break;
        int val = 0;
        /* scan past optional whitespace and sign */
        sscanf(colon + 1, " %d", &val);
        out->vals[out->count] = val;
        out->count++;
        cur = colon + 1;
    }
    return out->count;
}

/*
 * Parse two-int function call: set_func(min, max) or set_func(a, b)
 * Returns 1 on success, 0 if not found.
 */
int lpc_extract_two_ints(const char *buf, const char *func_name, int *a, int *b) {
    if (!buf || !func_name) return 0;
    const char *p = strstr(buf, func_name);
    if (!p) return 0;
    const char *q = strchr(p, '(');
    if (!q) return 0;
    int va = 0, vb = 0;
    if (sscanf(q, "(%d , %d", &va, &vb) == 2 ||
        sscanf(q, "(%d,%d", &va, &vb) == 2) {
        if (a) *a = va;
        if (b) *b = vb;
        return 1;
    }
    return 0;
}

/* Look up a stat field pointer by lowercase key name */
static int *stat_field(CharacterStats *s, const char *key) {
    if (!s || !key) return NULL;
    if (strcmp(key, "iq")  == 0) return &s->iq;
    if (strcmp(key, "me")  == 0) return &s->me;
    if (strcmp(key, "ma")  == 0) return &s->ma;
    if (strcmp(key, "ps")  == 0) return &s->ps;
    if (strcmp(key, "pp")  == 0) return &s->pp;
    if (strcmp(key, "pe")  == 0) return &s->pe;
    if (strcmp(key, "pb")  == 0) return &s->pb;
    if (strcmp(key, "spd") == 0) return &s->spd;
    return NULL;
}

/* Apply a ParsedMapping of stat modifiers to character stats */
static void apply_stat_map(Character *ch, const ParsedMapping *m) {
    for (int i = 0; i < m->count; i++) {
        /* lowercase the key for matching */
        char key[32];
        for (int k = 0; k < 31 && m->keys[i][k]; k++) {
            key[k] = tolower((unsigned char)m->keys[i][k]);
            key[k+1] = '\0';
        }
        int *field = stat_field(&ch->stats, key);
        if (field) {
            *field += m->vals[i];
            fprintf(stderr, "DEBUG: stat %s += %d (now %d)\n", key, m->vals[i], *field);
        }
    }
}

/* ------------------------------------------------------------------ */
/*  load_race_data - parse LPC race file and apply to Character        */
/* ------------------------------------------------------------------ */

void load_race_data(const char *race_name, Character *ch) {
    if (!race_name || !ch) return;

    char fname[256], path[512];
    name_to_filename(race_name, fname, sizeof(fname));
    snprintf(path, sizeof(path), "lib/races/%s.lpc", fname);
    fprintf(stderr, "DEBUG: Loading race data for '%s' from %s\n", race_name, path);

    char *buf = read_file_to_buffer(path);
    if (!buf) {
        fprintf(stderr, "DEBUG: Failed to read race file: %s\n", path);
        return;
    }

    /* ---- Stat modifiers: set_stat_modifiers(([ "iq": 2, ... ])) ---- */
    ParsedMapping stat_map;
    if (lpc_extract_mapping_ints(buf, "set_stat_modifiers(", &stat_map) > 0) {
        apply_stat_map(ch, &stat_map);
    }

    /* ---- Per-stat bonus: set_stat_bonus("IQ", 8) (great_horned_dragon style) ---- */
    {
        const char *scan = buf;
        while ((scan = strstr(scan, "set_stat_bonus(")) != NULL) {
            const char *q1 = strchr(scan, '"');
            if (!q1) break;
            q1++;
            const char *q2 = strchr(q1, '"');
            if (!q2) break;
            char sname[32] = {0};
            size_t slen = q2 - q1;
            if (slen >= sizeof(sname)) slen = sizeof(sname) - 1;
            memcpy(sname, q1, slen);
            sname[slen] = '\0';
            /* lowercase for matching */
            for (size_t k = 0; sname[k]; k++)
                sname[k] = tolower((unsigned char)sname[k]);

            int val = 0;
            if (sscanf(q2 + 1, " , %d", &val) == 1 ||
                sscanf(q2 + 1, ",%d", &val) == 1) {
                int *field = stat_field(&ch->stats, sname);
                if (field) {
                    *field += val;
                    fprintf(stderr, "DEBUG: stat_bonus %s += %d\n", sname, val);
                }
            }
            scan = q2 + 1;
        }
    }

    /* ---- SDC: try set_natural_sdc first, then set_base_sdc ---- */
    int nat_sdc = lpc_extract_int(buf, "set_natural_sdc(", NULL, -1);
    if (nat_sdc > 0) {
        ch->max_sdc += nat_sdc;
        ch->sdc += nat_sdc;
        fprintf(stderr, "DEBUG: natural_sdc=%d\n", nat_sdc);
    } else {
        int base_sdc = lpc_extract_int(buf, "set_base_sdc(", NULL, 0);
        if (base_sdc > 0) {
            ch->max_sdc += base_sdc;
            ch->sdc += base_sdc;
            fprintf(stderr, "DEBUG: base_sdc=%d\n", base_sdc);
        }
    }

    /* ---- MDC creature ---- */
    int mdc_creature = lpc_extract_int(buf, "set_mdc_creature(", NULL, -1);
    int base_mdc = lpc_extract_int(buf, "set_base_mdc(", NULL, 0);
    int nat_mdc  = lpc_extract_int(buf, "set_natural_mdc(", NULL, 0);
    int mdc_val = (base_mdc > 0) ? base_mdc : nat_mdc;
    if (mdc_val > 0 || mdc_creature == 1) {
        ch->health_type = MDC_ONLY;
        if (mdc_val > 0) {
            ch->mdc = ch->max_mdc = mdc_val;
        } else {
            ch->mdc = ch->max_mdc = 10; /* fallback */
        }
        fprintf(stderr, "DEBUG: MDC creature, mdc=%d\n", ch->mdc);
    }

    /* ---- ISP: try set_psionic_potential first, then set_base_isp ---- */
    int psi_pot = lpc_extract_int(buf, "set_psionic_potential(", NULL, -1);
    if (psi_pot > 0) {
        ch->max_isp = ch->isp = psi_pot;
        fprintf(stderr, "DEBUG: psionic_potential=%d\n", psi_pot);
    } else {
        int base_isp = lpc_extract_int(buf, "set_base_isp(", NULL, 0);
        if (base_isp > 0) {
            ch->max_isp = ch->isp = base_isp;
            fprintf(stderr, "DEBUG: base_isp=%d\n", base_isp);
        }
    }

    /* ---- PPE: try set_magic_potential first, then set_base_ppe ---- */
    int mag_pot = lpc_extract_int(buf, "set_magic_potential(", NULL, -1);
    if (mag_pot > 0) {
        ch->max_ppe = ch->ppe = mag_pot;
        fprintf(stderr, "DEBUG: magic_potential=%d\n", mag_pot);
    } else {
        int base_ppe = lpc_extract_int(buf, "set_base_ppe(", NULL, 0);
        if (base_ppe > 0) {
            ch->max_ppe = ch->ppe = base_ppe;
            fprintf(stderr, "DEBUG: base_ppe=%d\n", base_ppe);
        }
    }

    /* ---- HP bonus ---- */
    int base_hp = lpc_extract_int(buf, "set_base_hp(", NULL, 0);
    if (base_hp > 0) {
        ch->max_hp += base_hp;
        ch->hp += base_hp;
    }

    /* ---- Natural weapons: add_natural_weapon("name", d, s, bonus) ---- */
    {
        const char *scan = buf;
        while ((scan = strstr(scan, "add_natural_weapon(")) != NULL) {
            const char *p = strchr(scan, '(');
            if (!p) break;
            p++;
            const char *qs = strchr(p, '"');
            if (!qs) { scan = p; continue; }
            qs++;
            const char *qe = strchr(qs, '"');
            if (!qe) { scan = p; continue; }
            char wname[128] = {0};
            size_t wn = qe - qs;
            if (wn >= sizeof(wname)) wn = sizeof(wname) - 1;
            memcpy(wname, qs, wn);
            wname[wn] = '\0';
            fprintf(stderr, "DEBUG: Natural weapon: %s\n", wname);
            add_natural_weapon(ch, wname);
            scan = qe + 1;
        }
    }

    /* ---- Combat attributes: attacks, parries, auto-defense ---- */
    {
        int val = lpc_extract_int(buf, "set_attacks_per_round(", NULL, -1);
        if (val >= 0) {
            ch->attacks_per_round = 1 + val;  /* LPC sets EXTRA attacks, add to base 1 */
            fprintf(stderr, "DEBUG: attacks_per_round=%d\n", ch->attacks_per_round);
        }
        val = lpc_extract_int(buf, "set_parries_per_round(", NULL, -1);
        if (val >= 0) {
            ch->parries_per_round = val;
            fprintf(stderr, "DEBUG: parries_per_round=%d\n", ch->parries_per_round);
        }
        val = lpc_extract_int(buf, "set_auto_parry(", NULL, -1);
        if (val >= 0) {
            ch->racial_auto_parry = val;
            fprintf(stderr, "DEBUG: auto_parry=%d\n", val);
        }
        val = lpc_extract_int(buf, "set_auto_dodge(", NULL, -1);
        if (val >= 0) {
            ch->racial_auto_dodge = val;
            fprintf(stderr, "DEBUG: auto_dodge=%d\n", val);
        }
    }

    fprintf(stderr, "DEBUG: Race data loaded for '%s'\n", race_name);
    free(buf);
}

/* ------------------------------------------------------------------ */
/*  load_occ_data - parse LPC OCC file and apply to Character          */
/* ------------------------------------------------------------------ */

void load_occ_data(const char *occ_name, Character *ch) {
    if (!occ_name || !ch) return;

    char fname[256], path[512];
    name_to_filename(occ_name, fname, sizeof(fname));
    snprintf(path, sizeof(path), "lib/occs/%s.lpc", fname);
    fprintf(stderr, "DEBUG: Loading OCC data for '%s' from %s\n", occ_name, path);

    char *buf = read_file_to_buffer(path);
    if (!buf) {
        fprintf(stderr, "DEBUG: Failed to read OCC file: %s\n", path);
        return;
    }

    /* ---- Stat bonuses mapping: set_stat_bonuses(([ "me": 1, ... ])) ---- */
    ParsedMapping stat_map;
    if (lpc_extract_mapping_ints(buf, "set_stat_bonuses(", &stat_map) > 0) {
        apply_stat_map(ch, &stat_map);
    }

    /* ---- SDC ---- */
    int base_sdc = lpc_extract_int(buf, "set_base_sdc(", NULL, 0);
    if (base_sdc > 0) {
        ch->max_sdc += base_sdc;
        ch->sdc += base_sdc;
        fprintf(stderr, "DEBUG: OCC base_sdc=%d\n", base_sdc);
    }

    /* ---- ISP ---- */
    int base_isp = lpc_extract_int(buf, "set_base_isp(", NULL, 0);
    if (base_isp > 0) {
        ch->max_isp = ch->isp = base_isp;
        fprintf(stderr, "DEBUG: OCC base_isp=%d\n", base_isp);
    }

    /* ---- PPE ---- */
    int base_ppe = lpc_extract_int(buf, "set_base_ppe(", NULL, 0);
    if (base_ppe > 0) {
        ch->max_ppe = ch->ppe = base_ppe;
        fprintf(stderr, "DEBUG: OCC base_ppe=%d\n", base_ppe);
    }

    /* ---- HP bonus ---- */
    int base_hp = lpc_extract_int(buf, "set_base_hp(", NULL, 0);
    if (base_hp > 0) {
        ch->max_hp += base_hp;
        ch->hp += base_hp;
        fprintf(stderr, "DEBUG: OCC base_hp=%d\n", base_hp);
    }

    /* ---- MDC class ---- */
    int mdc_class = lpc_extract_int(buf, "set_mdc_class(", NULL, 0);
    if (mdc_class > 0) {
        ch->health_type = MDC_ONLY;
        ch->mdc = ch->max_mdc = mdc_class;
        fprintf(stderr, "DEBUG: OCC mdc_class=%d\n", mdc_class);
    }

    fprintf(stderr, "DEBUG: OCC data loaded for '%s'\n", occ_name);
    free(buf);
}

/* ------------------------------------------------------------------ */
/*  apply_race_and_occ - data-driven, delegates to LPC file parsers    */
/* ------------------------------------------------------------------ */

void apply_race_and_occ(PlayerSession *sess) {
    if (!sess) return;
    Character *ch = &sess->character;

    /* Defensive defaults */
    if (!ch->race) ch->race = strdup("Human");
    if (!ch->occ)  ch->occ  = strdup("None");

    /* Default health model */
    ch->health_type = HP_SDC;

    /* Load data from LPC files (these set stats, SDC, MDC, ISP, PPE, weapons) */
    load_race_data(ch->race, ch);
    load_occ_data(ch->occ, ch);

    /* Ensure HP/MDC/SDC values are consistent */
    if (ch->health_type == MDC_ONLY) {
        if (ch->mdc <= 0) ch->mdc = ch->max_mdc = 10;
    } else {
        if (ch->max_hp <= 0) ch->max_hp = ch->hp = 5 + ch->stats.pe;
        if (ch->max_sdc <= 0) ch->max_sdc = ch->sdc = 20;
    }

    /* Bounds on ISP/PPE */
    if (ch->max_isp < 0) ch->max_isp = 0;
    if (ch->isp < 0)     ch->isp = 0;
    if (ch->max_ppe < 0) ch->max_ppe = 0;
    if (ch->ppe < 0)     ch->ppe = 0;
}

/* ------------------------------------------------------------------ */
/*  Level-up system                                                    */
/* ------------------------------------------------------------------ */

void check_and_apply_level_up(PlayerSession *sess) {
    if (!sess) return;
    Character *ch = &sess->character;

    while (ch->level < MAX_LEVEL && ch->xp >= XP_TABLE[ch->level + 1]) {
        ch->level++;

        /* Base HP gain: 1d6 */
        int hp_gain = (rand() % 6) + 1;
        ch->hp     += hp_gain;
        ch->max_hp += hp_gain;

        /* Per-level gains from OCC file */
        int sdc_gain = 0, isp_gain = 0, ppe_gain = 0;
        {
            char fname[256], path[512];
            name_to_filename(ch->occ, fname, sizeof(fname));
            snprintf(path, sizeof(path), "lib/occs/%s.lpc", fname);
            char *buf = read_file_to_buffer(path);
            if (buf) {
                sdc_gain = lpc_extract_int(buf, "set_sdc_per_level(", NULL, 0);
                isp_gain = lpc_extract_int(buf, "set_isp_per_level(", NULL, 0);
                ppe_gain = lpc_extract_int(buf, "set_ppe_per_level(", NULL, 0);
                free(buf);
            }
        }
        ch->sdc     += sdc_gain;
        ch->max_sdc += sdc_gain;
        ch->isp     += isp_gain;
        ch->max_isp += isp_gain;
        ch->ppe     += ppe_gain;
        ch->max_ppe += ppe_gain;

        /* MDC per level from race file (for MDC creatures) */
        int mdc_gain = 0;
        if (ch->health_type == MDC_ONLY) {
            char fname[256], path[512];
            name_to_filename(ch->race, fname, sizeof(fname));
            snprintf(path, sizeof(path), "lib/races/%s.lpc", fname);
            char *buf = read_file_to_buffer(path);
            if (buf) {
                mdc_gain = lpc_extract_int(buf, "set_mdc_bonus_per_level(", NULL, 0);
                free(buf);
            }
            ch->mdc     += mdc_gain;
            ch->max_mdc += mdc_gain;
        }

        /* Level-based attack bonuses */
        int atk_bonus = 0;
        if (ch->level == 5 || ch->level == 10 || ch->level == 15) {
            ch->attacks_per_round++;
            atk_bonus = 1;
        }

        /* Announce level-up */
        send_to_player(sess,
            "\n========================================\n"
            "  LEVEL UP! You are now level %d!\n"
            "========================================\n",
            ch->level);
        send_to_player(sess, "  HP:  +%d\n", hp_gain);
        if (atk_bonus > 0) send_to_player(sess, "  Attacks/round: +1 (now %d)\n", ch->attacks_per_round);
        if (sdc_gain > 0) send_to_player(sess, "  SDC: +%d\n", sdc_gain);
        if (isp_gain > 0) send_to_player(sess, "  ISP: +%d\n", isp_gain);
        if (ppe_gain > 0) send_to_player(sess, "  PPE: +%d\n", ppe_gain);
        if (mdc_gain > 0) send_to_player(sess, "  MDC: +%d\n", mdc_gain);
        int next_xp = (ch->level < MAX_LEVEL) ? XP_TABLE[ch->level + 1] : -1;
        if (next_xp > 0)
            send_to_player(sess, "  Next level at %d XP\n", next_xp);
        else
            send_to_player(sess, "  Maximum level reached!\n");
        send_to_player(sess, "\n");

        /* Auto-save */
        save_character(sess);
    }
}
