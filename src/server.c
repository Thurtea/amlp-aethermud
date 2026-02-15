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

/* ls - List directory contents */
int cmd_ls_filesystem(PlayerSession *session, const char *args) {
    char path[512];
    char full_path[1024];
    
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

    /* Handle ~ - go to home directory */
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
