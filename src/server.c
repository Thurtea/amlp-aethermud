/*
 * server.c - Filesystem Commands for AMLP MUD Driver
 * 
 * Provides ls, cd, pwd, cat commands for wizard/admin users
 */

#define _GNU_SOURCE  /* for strdup() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "session_internal.h"  /* Provides PlayerSession struct definition */

#define BUFFER_SIZE 4096

/* External function to send text to player */
extern void send_to_player(PlayerSession *session, const char *format, ...);

// Utility: convert "\033" to binary ESC (27) in LPC strings for ANSI color support
void send_ansi(PlayerSession *session, const char *text) {
    char buf[4096];
    int bi = 0;
    for (int i = 0; text[i] && bi < sizeof(buf)-1; ) {
        // Look for "\\033["
        if (text[i] == '\\' && text[i+1] == '0' && text[i+2] == '3' && text[i+3] == '3' && text[i+4] == '[') {
            buf[bi++] = 27; // ESC
            buf[bi++] = '[';
            i += 5;
            // Copy the rest of the ANSI sequence (e.g., '1;34m')
            while (text[i] && bi < sizeof(buf)-1) {
                buf[bi++] = text[i];
                if (text[i] == 'm') { i++; break; }
                i++;
            }
        } else {
            buf[bi++] = text[i++];
        }
    }
    buf[bi] = '\0';
    send_to_player(session, "%s", buf);
}

/* ==========================================================================
 * Filesystem Commands for Wizards/Admins
 * ========================================================================== */

/* Return the default home directory for a player based on privilege level.
 * Writes into buf (must be at least 256 bytes). */
static void get_player_home_dir(PlayerSession *session, char *buf, size_t buf_size) {
    if (session->privilege_level >= 1) {
        /* Wizard/Admin: /domains/wizard/<lowercase_username>/ */
        char lower[64];
        const char *name = session->username;
        int i;
        for (i = 0; name[i] && i < 63; i++)
            lower[i] = (name[i] >= 'A' && name[i] <= 'Z') ? name[i] + 32 : name[i];
        lower[i] = '\0';
        snprintf(buf, buf_size, "/domains/wizard/%s", lower);
    } else {
        /* Regular player */
        snprintf(buf, buf_size, "/domains");
    }
}

/* Expand LPC path shorthand aliases.
 * Aliases:
 *   ~          → player home dir  (e.g. /domains/wizard/thurtea)
 *   ~/path     → <home>/path
 *   std        → /std
 *   cmds       → /cmds
 *   dom        → /domains
 *   obj        → /obj
 *   sec        → /secure
 *   daemon     → /daemon
 *   inc        → /include
 * Trailing "/foo" is preserved for all aliases (e.g. dom/start → /domains/start).
 * If no alias matches, the input is copied unchanged. */
void expand_lpc_alias(const char *input, char *output, size_t out_size,
                      PlayerSession *session) {
    if (!input || !output || out_size == 0) return;

    /* ~ or ~/... → home dir */
    if (input[0] == '~') {
        char home[256];
        get_player_home_dir(session, home, sizeof(home));
        if (input[1] == '\0') {
            snprintf(output, out_size, "%s", home);
        } else if (input[1] == '/') {
            snprintf(output, out_size, "%s%s", home, input + 1);
        } else {
            snprintf(output, out_size, "%s", input);  /* ~foo — no expansion */
        }
        return;
    }

    static const struct { const char *alias; const char *expand; } table[] = {
        { "std",    "/std"     },
        { "cmds",   "/cmds"    },
        { "dom",    "/domains" },
        { "obj",    "/obj"     },
        { "sec",    "/secure"  },
        { "daemon", "/daemon"  },
        { "inc",    "/include" },
        { NULL, NULL }
    };

    for (int i = 0; table[i].alias; i++) {
        size_t alen = strlen(table[i].alias);
        if (strncmp(input, table[i].alias, alen) == 0) {
            char next = input[alen];
            if (next == '\0') {
                snprintf(output, out_size, "%s", table[i].expand);
                return;
            }
            if (next == '/') {
                snprintf(output, out_size, "%s%s", table[i].expand, input + alen);
                return;
            }
        }
    }

    /* No alias matched — copy unchanged */
    snprintf(output, out_size, "%s", input);
}

/* ls - List directory contents */
int cmd_ls_filesystem(PlayerSession *session, const char *args) {
    char path[512];
    char full_path[1024];

    /* Expand path aliases (std, cmds, dom, obj, sec, daemon, inc, ~) */
    char alias_buf[512];
    if (args && *args != '\0') {
        expand_lpc_alias(args, alias_buf, sizeof(alias_buf), session);
        args = alias_buf;
    }

    /* Determine path */
    if (args && *args != '\0') {
        if (args[0] == '/') {
            snprintf(path, sizeof(path), "%s", args);
        } else {
            if (session->current_dir && strlen(session->current_dir) > 0) {
                snprintf(path, sizeof(path), "%s/%s", session->current_dir, args);
            } else {
                char home[256];
                get_player_home_dir(session, home, sizeof(home));
                snprintf(path, sizeof(path), "%s/%s", home, args);
            }
        }
    } else {
        if (session->current_dir && strlen(session->current_dir) > 0) {
            snprintf(path, sizeof(path), "%s", session->current_dir);
        } else {
            get_player_home_dir(session, path, sizeof(path));
        }
    }
    
    /* Build full filesystem path. If the user already included a leading
     * "/lib/" prefix (e.g. "/lib/std/player.lpc"), strip the leading
     * slash so we don't end up with "lib/lib/...". Otherwise prefix with
     * "lib" as before. */
    if (strncmp(path, "/lib/", 5) == 0) {
        snprintf(full_path, sizeof(full_path), "%s", path + 1);
    } else {
        snprintf(full_path, sizeof(full_path), "lib%s", path);
    }
    
    DIR *dir = opendir(full_path);
    if (!dir) {
        send_to_player(session, "Cannot open directory: %s\r\n", path);
        return 0;
    }
    
    send_to_player(session, "Directory listing of %s:\r\n", path);
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        /* Skip hidden files */
        if (entry->d_name[0] == '.') continue;
        
        /* Check if directory or file */
        char item_path[1024];
        snprintf(item_path, sizeof(item_path), "%s/%s", full_path, entry->d_name);
        
        struct stat st;
        if (stat(item_path, &st) == 0) {
            char line[256];
            if (S_ISDIR(st.st_mode)) {
                snprintf(line, sizeof(line), "%-30s/\r\n", entry->d_name);
            } else {
                snprintf(line, sizeof(line), "%-30s\r\n", entry->d_name);
            }
            send_to_player(session, "%s", line);
        }
    }
    
    closedir(dir);
    return 1;
}

/* cd - Change directory */
int cmd_cd_filesystem(PlayerSession *session, const char *args) {
    char new_dir[512];
    char full_path[1024];
    
    /* Handle no argument - go to home directory */
    if (!args || *args == '\0') {
        char home[256];
        get_player_home_dir(session, home, sizeof(home));
        if (session->current_dir) {
            free(session->current_dir);
        }
        session->current_dir = strdup(home);
        send_to_player(session, "Changed to: %s\r\n", home);
        return 1;
    }

    /* Expand path aliases (~ std cmds dom obj sec daemon inc).
     * After expansion ~ and ~/foo become absolute /domains/wizard/<name>
     * paths, so the absolute-path branch below handles them correctly. */
    char alias_buf[512];
    expand_lpc_alias(args, alias_buf, sizeof(alias_buf), session);
    args = alias_buf;

    /* Handle ~ alone (kept for safety; expand_lpc_alias already handles it) */
    if (strcmp(args, "~") == 0) {
        char home[256];
        get_player_home_dir(session, home, sizeof(home));
        if (session->current_dir) {
            free(session->current_dir);
        }
        session->current_dir = strdup(home);
        send_to_player(session, "Changed to: %s\r\n", home);
        return 1;
    }

    /* Handle absolute path */
    if (args[0] == '/') {
        snprintf(new_dir, sizeof(new_dir), "%s", args);
    }
    /* Handle .. */
    else if (strcmp(args, "..") == 0) {
        if (!session->current_dir || strlen(session->current_dir) == 0) {
            send_to_player(session, "Already at root directory\r\n");
            return 1;
        }
        
        /* Find last / and truncate */
        strncpy(new_dir, session->current_dir, sizeof(new_dir) - 1);
        char *last_slash = strrchr(new_dir, '/');
        if (last_slash) {
            *last_slash = '\0';
        } else {
            snprintf(new_dir, sizeof(new_dir), "");
        }
    }
    /* Handle relative path */
    else {
        if (session->current_dir && strlen(session->current_dir) > 0) {
            snprintf(new_dir, sizeof(new_dir), "%s/%s", session->current_dir, args);
        } else {
            char home[256];
            get_player_home_dir(session, home, sizeof(home));
            snprintf(new_dir, sizeof(new_dir), "%s/%s", home, args);
        }
    }
    
    /* Verify directory exists */
    if (strncmp(new_dir, "/lib/", 5) == 0) {
        snprintf(full_path, sizeof(full_path), "%s", new_dir + 1);
    } else {
        snprintf(full_path, sizeof(full_path), "lib%s", new_dir);
    }
   
    struct stat st;
    if (stat(full_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        send_to_player(session, "Directory does not exist: %s\r\n", new_dir);
        return 0;
    }
    
    /* Update current directory */
    if (session->current_dir) {
        free(session->current_dir);
    }
    session->current_dir = strdup(new_dir);
    
    send_to_player(session, "Changed to: %s\r\n", new_dir);
    return 1;
}

/* pwd - Print working directory */
int cmd_pwd_filesystem(PlayerSession *session) {
    if (!session->current_dir || strlen(session->current_dir) == 0) {
        char home[256];
        get_player_home_dir(session, home, sizeof(home));
        send_to_player(session, "Current directory: %s\r\n", home);
    } else {
        send_to_player(session, "Current directory: %s\r\n", session->current_dir);
    }
    return 1;
}

/* cat - Display file contents */
int cmd_cat_filesystem(PlayerSession *session, const char *args) {
    if (!args || *args == '\0') {
        send_to_player(session, "Usage: cat <filename>\r\n");
        return 0;
    }
    
    char path[512];
    char full_path[1024];
    
    /* Build path */
    if (args[0] == '/') {
        snprintf(path, sizeof(path), "%s", args);
    } else {
        if (session->current_dir && strlen(session->current_dir) > 0) {
            snprintf(path, sizeof(path), "%s/%s", session->current_dir, args);
        } else {
            char home[256];
            get_player_home_dir(session, home, sizeof(home));
            snprintf(path, sizeof(path), "%s/%s", home, args);
        }
    }
    
    if (strncmp(path, "/lib/", 5) == 0) {
        snprintf(full_path, sizeof(full_path), "%s", path + 1);
    } else {
        snprintf(full_path, sizeof(full_path), "lib%s", path);
    }
    
    FILE *f = fopen(full_path, "r");
    if (!f) {
        send_to_player(session, "Cannot open file: %s\r\n", path);
        return 0;
    }
    
    send_to_player(session, "File: %s\r\n", path);
    send_to_player(session, "----------------------------------------\r\n");
    
    char line[512];
    int line_count = 0;
    while (fgets(line, sizeof(line), f) && line_count < 1000) {
        /* Convert LF to CRLF for telnet */
        char *lf = strchr(line, '\n');
        if (lf) {
            *lf = '\0';
            send_to_player(session, "%s\r\n", line);
        } else {
            send_to_player(session, "%s", line);
        }
        line_count++;
    }
    
    if (line_count >= 1000) {
        send_to_player(session, "\r\n[File truncated at 1000 lines]\r\n");
    }
    
    fclose(f);
    return 1;
}

/* Resolve a relative or absolute path to a full filesystem path.
 * Handles current_dir, home dir fallback, and lib/ prefix. */
static void resolve_path(PlayerSession *session, const char *args,
                         char *vpath, size_t vpath_sz,
                         char *fspath, size_t fspath_sz) {
    if (args[0] == '/') {
        snprintf(vpath, vpath_sz, "%s", args);
    } else {
        if (session->current_dir && strlen(session->current_dir) > 0) {
            snprintf(vpath, vpath_sz, "%s/%s", session->current_dir, args);
        } else {
            char home[256];
            get_player_home_dir(session, home, sizeof(home));
            snprintf(vpath, vpath_sz, "%s/%s", home, args);
        }
    }
    if (strncmp(vpath, "/lib/", 5) == 0) {
        snprintf(fspath, fspath_sz, "%s", vpath + 1);
    } else {
        snprintf(fspath, fspath_sz, "lib%s", vpath);
    }
}

/* more - Paginated file viewer (shows 20 lines at a time) */
int cmd_more_filesystem(PlayerSession *session, const char *args) {
    if (!args || *args == '\0') {
        send_to_player(session, "Usage: more <filename>\r\n");
        return 0;
    }

    char path[512];
    char full_path[1024];
    resolve_path(session, args, path, sizeof(path), full_path, sizeof(full_path));

    /* Also try with .lpc extension */
    FILE *f = fopen(full_path, "r");
    if (!f) {
        char try_lpc[1024];
        snprintf(try_lpc, sizeof(try_lpc), "%s.lpc", full_path);
        f = fopen(try_lpc, "r");
        if (!f) {
            send_to_player(session, "Cannot open file: %s\r\n", path);
            return 0;
        }
    }

    /* Read all lines into memory */
    char lines[1000][512];
    int total = 0;
    while (total < 1000 && fgets(lines[total], sizeof(lines[0]), f)) {
        /* Strip trailing newline */
        char *lf = strchr(lines[total], '\n');
        if (lf) *lf = '\0';
        total++;
    }
    fclose(f);

    if (total == 0) {
        send_to_player(session, "File is empty: %s\r\n", path);
        return 0;
    }

    /* Display first page */
    int page_size = 20;
    send_to_player(session, "File: %s (%d lines)\r\n", path, total);
    send_to_player(session, "----------------------------------------\r\n");

    int shown = 0;
    for (int i = 0; i < total; i++) {
        send_to_player(session, "%3d: %s\r\n", i + 1, lines[i]);
        shown++;
        if (shown >= page_size && i + 1 < total) {
            send_to_player(session, "-- More (%d/%d) -- [Enter for next page, q to quit] --\r\n",
                          i + 1, total);
            /* Note: true pagination requires input state machine changes.
             * For now, show all with line numbers for scrollback. */
        }
    }

    if (total >= 1000) {
        send_to_player(session, "\r\n[File truncated at 1000 lines]\r\n");
    }
    send_to_player(session, "----------------------------------------\r\n");
    send_to_player(session, "[End of %s - %d lines]\r\n", path, total);
    return 1;
}

/* ed - Simple line editor for LPC files */
/* Since we don't have an interactive state machine for ed mode,
 * this implements a single-command interface:
 *   ed <file>           - Open file and show contents
 *   ed <file> a <text>  - Append a line to end of file
 *   ed <file> i <n> <t> - Insert text before line n
 *   ed <file> d <n>     - Delete line n
 *   ed <file> l         - List file with line numbers
 *   ed <file> w         - Write (already on disk - confirm)
 *   ed <file> r <n> <t> - Replace line n with text
 */
int cmd_ed_filesystem(PlayerSession *session, const char *args) {
    if (!args || *args == '\0') {
        send_to_player(session, "Usage: ed <file> [command]\r\n");
        send_to_player(session, "Commands:\r\n");
        send_to_player(session, "  ed <file>              - Show file with line numbers\r\n");
        send_to_player(session, "  ed <file> a <text>     - Append line to end\r\n");
        send_to_player(session, "  ed <file> i <n> <text> - Insert before line n\r\n");
        send_to_player(session, "  ed <file> d <n>        - Delete line n\r\n");
        send_to_player(session, "  ed <file> r <n> <text> - Replace line n\r\n");
        return 0;
    }

    /* Parse: first token is filename, rest is subcommand */
    char file_arg[256];
    char subcmd[512] = "";
    const char *sp = strchr(args, ' ');
    if (sp) {
        int flen = (int)(sp - args);
        if (flen >= (int)sizeof(file_arg)) flen = sizeof(file_arg) - 1;
        memcpy(file_arg, args, flen);
        file_arg[flen] = '\0';
        sp++;
        while (*sp == ' ') sp++;
        strncpy(subcmd, sp, sizeof(subcmd) - 1);
    } else {
        strncpy(file_arg, args, sizeof(file_arg) - 1);
    }

    char vpath[512];
    char full_path[1024];
    resolve_path(session, file_arg, vpath, sizeof(vpath), full_path, sizeof(full_path));

    /* Try with .lpc extension if not found */
    struct stat st;
    char actual_path[1024];
    strncpy(actual_path, full_path, sizeof(actual_path) - 1);
    if (stat(actual_path, &st) != 0) {
        snprintf(actual_path, sizeof(actual_path), "%s.lpc", full_path);
        if (stat(actual_path, &st) != 0) {
            /* File doesn't exist - if subcommand is 'a', create it */
            if (subcmd[0] == 'a' && subcmd[1] == ' ') {
                FILE *nf = fopen(actual_path, "w");
                if (!nf) {
                    /* Try without .lpc */
                    nf = fopen(full_path, "w");
                    if (!nf) {
                        send_to_player(session, "Cannot create file: %s\r\n", vpath);
                        return 0;
                    }
                    strncpy(actual_path, full_path, sizeof(actual_path) - 1);
                }
                fprintf(nf, "%s\n", subcmd + 2);
                fclose(nf);
                send_to_player(session, "Created %s (1 line)\r\n", vpath);
                return 1;
            }
            send_to_player(session, "File not found: %s\r\n", vpath);
            return 0;
        }
    }

    /* Read file into memory */
    FILE *f = fopen(actual_path, "r");
    if (!f) {
        send_to_player(session, "Cannot open file: %s\r\n", vpath);
        return 0;
    }

    char lines[2000][512];
    int total = 0;
    while (total < 2000 && fgets(lines[total], sizeof(lines[0]), f)) {
        char *lf = strchr(lines[total], '\n');
        if (lf) *lf = '\0';
        /* Also strip \r */
        char *cr = strchr(lines[total], '\r');
        if (cr) *cr = '\0';
        total++;
    }
    fclose(f);

    /* No subcommand: list file */
    if (subcmd[0] == '\0' || subcmd[0] == 'l') {
        /* Start an interactive ed session if the caller is a wizard and asked to edit */
        if (session && session->privilege_level >= 1 && subcmd[0] == '\0') {
            /* Initialize interactive editor state on the session */
            /* Free any existing editor state first */
            if (session->ed_active) {
                /* Drop existing editor session */
                session->ed_active = 0;
            }

            /* Copy virtual and filesystem path into session */
            strncpy(session->ed_vpath, vpath, sizeof(session->ed_vpath) - 1);
            strncpy(session->ed_fspath, actual_path, sizeof(session->ed_fspath) - 1);
            /* Load lines into session->ed_lines */
            /* Free prior buffer if any */
            if (session->ed_lines) {
                for (int i = 0; i < session->ed_lines_count; i++) free(session->ed_lines[i]);
                free(session->ed_lines);
                session->ed_lines = NULL;
                session->ed_lines_count = 0;
                session->ed_lines_capacity = 0;
            }

            session->ed_lines_capacity = total > 64 ? total + 64 : 256;
            session->ed_lines = calloc(session->ed_lines_capacity, sizeof(char*));
            for (int i = 0; i < total; i++) {
                session->ed_lines[i] = strdup(lines[i]);
            }
            session->ed_lines_count = total;
            session->ed_show_numbers = 0;
            session->ed_cursor = 0;
            session->ed_input_mode = 0;
            session->ed_target_line = 0;
            session->ed_active = 1;

            /* Show brief header and colon prompt */
            send_to_player(session, "Editing %s (%d lines)\r\n", session->ed_vpath, session->ed_lines_count);
            send_to_player(session, ": ");
            return 1;
        }

        send_to_player(session, "File: %s (%d lines)\r\n", vpath, total);
        for (int i = 0; i < total; i++) {
            send_to_player(session, "%3d: %s\r\n", i + 1, lines[i]);
        }
        return 1;
    }

    /* a <text> - append */
    if (subcmd[0] == 'a' && subcmd[1] == ' ') {
        FILE *wf = fopen(actual_path, "a");
        if (!wf) {
            send_to_player(session, "Cannot write to: %s\r\n", vpath);
            return 0;
        }
        fprintf(wf, "%s\n", subcmd + 2);
        fclose(wf);
        send_to_player(session, "Appended line %d to %s\r\n", total + 1, vpath);
        return 1;
    }

    /* d <n> - delete line */
    if (subcmd[0] == 'd' && (subcmd[1] == ' ' || subcmd[1] == '\0')) {
        int line_num = 0;
        if (subcmd[1] == ' ') line_num = atoi(subcmd + 2);
        if (line_num < 1 || line_num > total) {
            send_to_player(session, "Line %d out of range (1-%d)\r\n", line_num, total);
            return 0;
        }
        /* Write back without that line */
        FILE *wf = fopen(actual_path, "w");
        if (!wf) {
            send_to_player(session, "Cannot write to: %s\r\n", vpath);
            return 0;
        }
        for (int i = 0; i < total; i++) {
            if (i != line_num - 1) {
                fprintf(wf, "%s\n", lines[i]);
            }
        }
        fclose(wf);
        send_to_player(session, "Deleted line %d from %s (%d lines remaining)\r\n",
                      line_num, vpath, total - 1);
        return 1;
    }

    /* i <n> <text> - insert before line n */
    if (subcmd[0] == 'i' && subcmd[1] == ' ') {
        int line_num = atoi(subcmd + 2);
        const char *text = strchr(subcmd + 2, ' ');
        if (!text || line_num < 1 || line_num > total + 1) {
            send_to_player(session, "Usage: ed <file> i <line#> <text>\r\n");
            return 0;
        }
        text++;
        FILE *wf = fopen(actual_path, "w");
        if (!wf) {
            send_to_player(session, "Cannot write to: %s\r\n", vpath);
            return 0;
        }
        for (int i = 0; i < total; i++) {
            if (i == line_num - 1) {
                fprintf(wf, "%s\n", text);
            }
            fprintf(wf, "%s\n", lines[i]);
        }
        if (line_num == total + 1) {
            fprintf(wf, "%s\n", text);
        }
        fclose(wf);
        send_to_player(session, "Inserted at line %d in %s (%d lines total)\r\n",
                      line_num, vpath, total + 1);
        return 1;
    }

    /* r <n> <text> - replace line n */
    if (subcmd[0] == 'r' && subcmd[1] == ' ') {
        int line_num = atoi(subcmd + 2);
        const char *text = strchr(subcmd + 2, ' ');
        if (!text || line_num < 1 || line_num > total) {
            send_to_player(session, "Usage: ed <file> r <line#> <text>\r\n");
            return 0;
        }
        text++;
        FILE *wf = fopen(actual_path, "w");
        if (!wf) {
            send_to_player(session, "Cannot write to: %s\r\n", vpath);
            return 0;
        }
        for (int i = 0; i < total; i++) {
            if (i == line_num - 1) {
                fprintf(wf, "%s\n", text);
            } else {
                fprintf(wf, "%s\n", lines[i]);
            }
        }
        fclose(wf);
        send_to_player(session, "Replaced line %d in %s\r\n", line_num, vpath);
        return 1;
    }

    send_to_player(session, "Unknown ed command: %c\r\n", subcmd[0]);
    send_to_player(session, "Commands: l (list), a (append), i (insert), d (delete), r (replace)\r\n");
    return 0;
}

/* ------------------------------------------------------------------ */
/* Interactive in-session ed handler called from process_playing_state */
/* Returns 1 if input was handled as ed input */
int ed_handle_input(PlayerSession *session, const char *input) {
    if (!session || !session->ed_active) return 0;

    /* If we are in append/insert/change multi-line mode, collect until '.' */
    if (session->ed_input_mode == 1 || session->ed_input_mode == 2 || session->ed_input_mode == 3) {
        if (strcmp(input, ".") == 0) {
            /* End of multi-line input */
            session->ed_input_mode = 0;
            send_to_player(session, ": ");
            return 1;
        }

        /* Append the line to buffer appropriately */
        if (session->ed_input_mode == 1) {
            /* append to end */
            if (session->ed_lines_count + 1 >= session->ed_lines_capacity) {
                session->ed_lines_capacity = session->ed_lines_capacity * 2 + 16;
                session->ed_lines = realloc(session->ed_lines, session->ed_lines_capacity * sizeof(char*));
            }
            session->ed_lines[session->ed_lines_count++] = strdup(input);
        } else if (session->ed_input_mode == 2) {
            /* insert before target line */
            int idx = session->ed_target_line - 1;
            if (idx < 0) idx = 0;
            if (idx > session->ed_lines_count) idx = session->ed_lines_count;
            if (session->ed_lines_count + 1 >= session->ed_lines_capacity) {
                session->ed_lines_capacity = session->ed_lines_capacity * 2 + 16;
                session->ed_lines = realloc(session->ed_lines, session->ed_lines_capacity * sizeof(char*));
            }
            for (int i = session->ed_lines_count; i > idx; i--) session->ed_lines[i] = session->ed_lines[i-1];
            session->ed_lines[idx] = strdup(input);
            session->ed_lines_count++;
        } else if (session->ed_input_mode == 3) {
            /* change: replace target line with this single line */
            int idx = session->ed_target_line - 1;
            if (idx >= 0 && idx < session->ed_lines_count) {
                free(session->ed_lines[idx]);
                session->ed_lines[idx] = strdup(input);
            }
        }

        /* Continue collecting */
        send_to_player(session, "* ");
        return 1;
    }

    /* Interpret simple colon-style commands (user types command without leading colon) */
    /* Trim leading/trailing whitespace */
    const char *s = input;
    while (*s == ' ' || *s == '\t') s++;
    if (*s == '\0') { send_to_player(session, ": "); return 1; }

    /* Numeric prefix (for e.g. '1z') */
    int num = 0;
    const char *p = s;
    while (*p >= '0' && *p <= '9') { num = num * 10 + (*p - '0'); p++; }
    char cmd = *p;

    switch (cmd) {
        case 'n':
            session->ed_show_numbers = !session->ed_show_numbers;
            send_to_player(session, "number %s\r\n", session->ed_show_numbers ? "on" : "off");
            break;

        case 'z': {
            int start = (num > 0) ? num - 1 : session->ed_cursor;
            if (start < 0) start = 0;
            int show = 20;
            for (int i = 0; i < show && start + i < session->ed_lines_count; i++) {
                int ln = start + i + 1;
                if (session->ed_show_numbers)
                    send_to_player(session, "%4d: %s\r\n", ln, session->ed_lines[start + i]);
                else
                    send_to_player(session, "%s\r\n", session->ed_lines[start + i]);
            }
            session->ed_cursor = start + show;
            if (session->ed_cursor >= session->ed_lines_count) session->ed_cursor = session->ed_lines_count - 1;
            if (session->ed_cursor < 0) session->ed_cursor = 0;
            break; }

        case 'a':
            /* Enter append mode; lines until a single '.' are appended */
            session->ed_input_mode = 1;
            send_to_player(session, "* ");
            return 1;

        case 'd': {
            /* delete: d <n> */
            int target = num;
            if (target < 1 || target > session->ed_lines_count) {
                send_to_player(session, "Line %d out of range (1-%d)\r\n", target, session->ed_lines_count);
            } else {
                int idx = target - 1;
                free(session->ed_lines[idx]);
                for (int i = idx; i < session->ed_lines_count - 1; i++) session->ed_lines[i] = session->ed_lines[i+1];
                session->ed_lines_count--;
                send_to_player(session, "Deleted line %d\r\n", target);
            }
            break; }

        case 'g': {
            /* go to line and show a page: g <n> or just g */
            int start = (num > 0) ? num - 1 : 0;
            if (start < 0) start = 0;
            int show = 20;
            for (int i = 0; i < show && start + i < session->ed_lines_count; i++) {
                int ln = start + i + 1;
                if (session->ed_show_numbers)
                    send_to_player(session, "%4d: %s\r\n", ln, session->ed_lines[start + i]);
                else
                    send_to_player(session, "%s\r\n", session->ed_lines[start + i]);
            }
            session->ed_cursor = start + show;
            break; }

        case 'I': {
            /* Insert before line: I <n> */
            int target = num;
            if (target < 1) target = 1;
            if (target > session->ed_lines_count + 1) target = session->ed_lines_count + 1;
            session->ed_target_line = target;
            session->ed_input_mode = 2; /* insert mode */
            send_to_player(session, "* ");
            return 1; }

        case 'c': {
            /* change/replace line: c <n> */
            int target = num;
            if (target < 1 || target > session->ed_lines_count) {
                send_to_player(session, "Line %d out of range\r\n", target);
            } else {
                session->ed_target_line = target;
                session->ed_input_mode = 3; /* change mode */
                send_to_player(session, "* ");
                return 1;
            }
            break; }

        case 'x': {
            /* write file and exit editor */
            FILE *wf = fopen(session->ed_fspath, "w");
            if (!wf) {
                send_to_player(session, "Cannot write to: %s\r\n", session->ed_vpath);
                break;
            }
            for (int i = 0; i < session->ed_lines_count; i++) {
                fprintf(wf, "%s\n", session->ed_lines[i]);
            }
            fclose(wf);
            send_to_player(session, "Wrote %d lines to: %s\r\n", session->ed_lines_count, session->ed_vpath);
            /* Exit editor and free memory */
            for (int i = 0; i < session->ed_lines_count; i++) free(session->ed_lines[i]);
            free(session->ed_lines);
            session->ed_lines = NULL;
            session->ed_lines_count = 0;
            session->ed_lines_capacity = 0;
            session->ed_active = 0;
            send_to_player(session, "Exited editor.\r\n");
            break; }

        case 'q':
            /* Quit without saving */
            for (int i = 0; i < session->ed_lines_count; i++) free(session->ed_lines[i]);
            free(session->ed_lines);
            session->ed_lines = NULL;
            session->ed_lines_count = 0;
            session->ed_lines_capacity = 0;
            session->ed_active = 0;
            send_to_player(session, "Exited editor (no save).\r\n");
            break;

        default:
            send_to_player(session, "Unknown ed command: %s\r\n", s);
    }

    if (session->ed_active) send_to_player(session, ": ");
    return 1;
}
