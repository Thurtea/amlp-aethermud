/**
 * preprocessor.c - LPC Preprocessor Implementation
 *
 * Text-level preprocessing pass that runs BEFORE the lexer.
 * Handles: #include, #define, #undef, #ifdef, #ifndef, #else, #endif
 * Also expands macros in non-directive lines.
 *
 * Design: processes source line-by-line. Directive lines are consumed
 * and replaced with empty lines (preserving line numbers). Regular
 * lines have macros expanded. #include files are processed recursively
 * for their macros but their content is NOT inlined (preserves line numbers
 * in the main file).
 */

#include "preprocessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/* ========== Configuration ========== */

#define PP_MAX_MACROS       512
#define PP_MAX_COND_DEPTH   64
#define PP_MAX_INCLUDE_DEPTH 16
#define PP_MAX_INCLUDES     64
#define PP_NAME_MAX         128
#define PP_VALUE_MAX        2048
#define PP_BUF_INITIAL      8192
#define PP_EXPAND_PASSES    10

/* ========== Dynamic Buffer ========== */

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} PPBuf;

static void ppbuf_init(PPBuf *b) {
    b->cap = PP_BUF_INITIAL;
    b->data = malloc(b->cap);
    b->len = 0;
    b->data[0] = '\0';
}

static void ppbuf_append(PPBuf *b, const char *s, size_t n) {
    while (b->len + n + 1 > b->cap) {
        b->cap *= 2;
        b->data = realloc(b->data, b->cap);
    }
    memcpy(b->data + b->len, s, n);
    b->len += n;
    b->data[b->len] = '\0';
}

static void ppbuf_append_str(PPBuf *b, const char *s) {
    ppbuf_append(b, s, strlen(s));
}

static void ppbuf_append_char(PPBuf *b, char c) {
    ppbuf_append(b, &c, 1);
}

/* ========== Preprocessor State ========== */

typedef struct {
    char name[PP_NAME_MAX];
    char value[PP_VALUE_MAX];
} PPMacro;

typedef struct {
    PPMacro macros[PP_MAX_MACROS];
    int macro_count;

    /* Conditional compilation stack: 1 = active, 0 = skipping */
    int cond_active[PP_MAX_COND_DEPTH];
    int cond_depth;

    /* Include tracking (prevent infinite recursion) */
    char *included_files[PP_MAX_INCLUDES];
    int include_count;
    int include_depth;

    /* Mudlib root path for resolving includes */
    char mudlib_path[PATH_MAX];
} PPState;

/* ========== Macro Table ========== */

static void pp_define(PPState *pp, const char *name, const char *value) {
    if (!name || !name[0]) return;

    /* Update existing macro if found */
    for (int i = 0; i < pp->macro_count; i++) {
        if (strcmp(pp->macros[i].name, name) == 0) {
            strncpy(pp->macros[i].value, value ? value : "",
                    PP_VALUE_MAX - 1);
            pp->macros[i].value[PP_VALUE_MAX - 1] = '\0';
            return;
        }
    }

    /* Add new macro */
    if (pp->macro_count < PP_MAX_MACROS) {
        PPMacro *m = &pp->macros[pp->macro_count++];
        strncpy(m->name, name, PP_NAME_MAX - 1);
        m->name[PP_NAME_MAX - 1] = '\0';
        strncpy(m->value, value ? value : "", PP_VALUE_MAX - 1);
        m->value[PP_VALUE_MAX - 1] = '\0';
    }
}

static const char* pp_lookup(PPState *pp, const char *name) {
    for (int i = 0; i < pp->macro_count; i++) {
        if (strcmp(pp->macros[i].name, name) == 0) {
            return pp->macros[i].value;
        }
    }
    return NULL;
}

static void pp_undef(PPState *pp, const char *name) {
    for (int i = 0; i < pp->macro_count; i++) {
        if (strcmp(pp->macros[i].name, name) == 0) {
            /* Shift remaining entries down */
            for (int j = i; j < pp->macro_count - 1; j++) {
                pp->macros[j] = pp->macros[j + 1];
            }
            pp->macro_count--;
            return;
        }
    }
}

/* ========== Conditional Compilation ========== */

static int pp_is_active(PPState *pp) {
    if (pp->cond_depth == 0) return 1;
    return pp->cond_active[pp->cond_depth];
}

static int pp_parent_active(PPState *pp) {
    if (pp->cond_depth <= 1) return 1;
    return pp->cond_active[pp->cond_depth - 1];
}

/* ========== Macro Expansion ========== */

/**
 * Expand all macros in a line of text.
 * Respects string literals (doesn't expand inside "...").
 * Does multiple passes to handle chained macros.
 * Returns newly allocated string. Caller must free().
 */
static char* pp_expand_macros(PPState *pp, const char *line) {
    char *current = strdup(line);

    for (int pass = 0; pass < PP_EXPAND_PASSES; pass++) {
        int changed = 0;
        PPBuf out;
        ppbuf_init(&out);

        const char *p = current;
        int in_string = 0;
        int in_char = 0;

        while (*p) {
            /* Track string literals - don't expand macros inside them */
            if (!in_char && *p == '"') {
                if (p == current || *(p - 1) != '\\') {
                    in_string = !in_string;
                }
                ppbuf_append_char(&out, *p++);
                continue;
            }
            if (!in_string && *p == '\'') {
                /* Character literal: copy through */
                ppbuf_append_char(&out, *p++);
                /* Copy the character (possibly escaped) */
                if (*p == '\\' && *(p + 1)) {
                    ppbuf_append_char(&out, *p++);
                    ppbuf_append_char(&out, *p++);
                } else if (*p) {
                    ppbuf_append_char(&out, *p++);
                }
                /* Closing quote */
                if (*p == '\'') {
                    ppbuf_append_char(&out, *p++);
                }
                continue;
            }

            if (in_string) {
                /* Inside string: handle escape sequences */
                if (*p == '\\' && *(p + 1)) {
                    ppbuf_append_char(&out, *p++);
                    ppbuf_append_char(&out, *p++);
                } else {
                    ppbuf_append_char(&out, *p++);
                }
                continue;
            }

            /* Skip // line comments entirely */
            if (*p == '/' && *(p + 1) == '/') {
                ppbuf_append_str(&out, p);
                break;
            }

            /* Copy block comments through without expansion */
            if (*p == '/' && *(p + 1) == '*') {
                ppbuf_append_char(&out, *p++); /* / */
                ppbuf_append_char(&out, *p++); /* * */
                while (*p && !(*p == '*' && *(p + 1) == '/')) {
                    ppbuf_append_char(&out, *p++);
                }
                if (*p) {
                    ppbuf_append_char(&out, *p++); /* * */
                    ppbuf_append_char(&out, *p++); /* / */
                }
                continue;
            }

            /* Check for identifier (potential macro) */
            if (isalpha((unsigned char)*p) || *p == '_') {
                const char *id_start = p;
                while (*p && (isalnum((unsigned char)*p) || *p == '_')) p++;
                size_t id_len = (size_t)(p - id_start);

                if (id_len < PP_NAME_MAX) {
                    char id[PP_NAME_MAX];
                    memcpy(id, id_start, id_len);
                    id[id_len] = '\0';

                    const char *value = pp_lookup(pp, id);
                    if (value) {
                        ppbuf_append_str(&out, value);
                        changed = 1;
                        continue;
                    }
                }

                /* Not a macro - copy identifier as-is */
                ppbuf_append(&out, id_start, id_len);
                continue;
            }

            /* Regular character */
            ppbuf_append_char(&out, *p++);
        }

        free(current);
        current = out.data;

        if (!changed) break;
    }

    return current;
}

/* ========== Include Handling ========== */

/* Forward declaration */
static void pp_process(PPState *pp, const char *source,
                       const char *filename, PPBuf *output);

/**
 * Read a file into memory. Returns malloc'd buffer or NULL.
 */
static char* pp_read_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (size < 0) { fclose(f); return NULL; }

    char *buf = malloc((size_t)size + 1);
    if (!buf) { fclose(f); return NULL; }

    size_t nread = fread(buf, 1, (size_t)size, f);
    buf[nread] = '\0';
    fclose(f);
    return buf;
}

/**
 * Check if a file has already been included (for include guards).
 */
static int pp_already_included(PPState *pp, const char *path) {
    for (int i = 0; i < pp->include_count; i++) {
        if (strcmp(pp->included_files[i], path) == 0)
            return 1;
    }
    return 0;
}

/**
 * Process an #include directive.
 * Reads the file and processes it for macros (doesn't inline content).
 */
static void pp_handle_include(PPState *pp, const char *inc_path,
                              const char *current_file) {
    if (pp->include_depth >= PP_MAX_INCLUDE_DEPTH) {
        fprintf(stderr, "[Preprocessor] Include depth exceeded for '%s'\n",
                inc_path);
        return;
    }

    /* Resolve the include path */
    char full_path[PATH_MAX];
    char *content = NULL;

    /* Try mudlib_path/include/inc_path */
    snprintf(full_path, sizeof(full_path), "%s/include/%s",
             pp->mudlib_path, inc_path);
    content = pp_read_file(full_path);

    /* If not found, try relative to current file */
    if (!content && current_file) {
        char dir[PATH_MAX];
        strncpy(dir, current_file, sizeof(dir) - 1);
        dir[sizeof(dir) - 1] = '\0';
        char *slash = strrchr(dir, '/');
        if (slash) {
            *(slash + 1) = '\0';
            snprintf(full_path, sizeof(full_path), "%s%s", dir, inc_path);
            content = pp_read_file(full_path);
        }
    }

    if (!content) {
        fprintf(stderr, "[Preprocessor] Cannot open include file '%s'\n",
                inc_path);
        return;
    }

    /* Check if already included */
    if (pp_already_included(pp, full_path)) {
        free(content);
        return;
    }

    /* Track this include */
    if (pp->include_count < PP_MAX_INCLUDES) {
        pp->included_files[pp->include_count++] = strdup(full_path);
    }

    /* Process included file for its macros (output=NULL: don't inline) */
    pp->include_depth++;
    pp_process(pp, content, full_path, NULL);
    pp->include_depth--;

    free(content);
}

/* ========== Directive Handling ========== */

/**
 * Parse and handle a preprocessor directive line.
 * The line starts with '#' (possibly with leading whitespace).
 * Returns 1 if the line was a directive, 0 otherwise.
 */
static int pp_handle_directive(PPState *pp, const char *line,
                               const char *filename) {
    const char *p = line;

    /* Skip leading whitespace */
    while (*p && isspace((unsigned char)*p)) p++;
    if (*p != '#') return 0;
    p++;

    /* Skip whitespace after # */
    while (*p && isspace((unsigned char)*p)) p++;

    /* Read directive name */
    char directive[64];
    int di = 0;
    while (*p && isalpha((unsigned char)*p) && di < 63) {
        directive[di++] = *p++;
    }
    directive[di] = '\0';

    /* Skip whitespace after directive */
    while (*p && (*p == ' ' || *p == '\t')) p++;

    /* ---- #define NAME VALUE ---- */
    if (strcmp(directive, "define") == 0) {
        if (!pp_is_active(pp)) return 1;

        char name[PP_NAME_MAX];
        int ni = 0;
        while (*p && (isalnum((unsigned char)*p) || *p == '_')
               && ni < PP_NAME_MAX - 1) {
            name[ni++] = *p++;
        }
        name[ni] = '\0';

        /* Skip whitespace between name and value */
        while (*p && (*p == ' ' || *p == '\t')) p++;

        /* Rest of line is the value (trimmed) */
        char value[PP_VALUE_MAX];
        strncpy(value, p, PP_VALUE_MAX - 1);
        value[PP_VALUE_MAX - 1] = '\0';

        /* Trim trailing whitespace/newline */
        int len = (int)strlen(value);
        while (len > 0 && (value[len - 1] == '\n' || value[len - 1] == '\r'
               || value[len - 1] == ' ' || value[len - 1] == '\t')) {
            value[--len] = '\0';
        }

        /* Strip trailing // comment from value */
        {
            int in_str = 0;
            for (int i = 0; value[i]; i++) {
                if (value[i] == '"' && (i == 0 || value[i-1] != '\\'))
                    in_str = !in_str;
                if (!in_str && value[i] == '/' && value[i+1] == '/') {
                    /* Trim from here */
                    while (i > 0 && (value[i-1] == ' ' || value[i-1] == '\t'))
                        i--;
                    value[i] = '\0';
                    break;
                }
            }
        }

        pp_define(pp, name, value);
        return 1;
    }

    /* ---- #undef NAME ---- */
    if (strcmp(directive, "undef") == 0) {
        if (!pp_is_active(pp)) return 1;

        char name[PP_NAME_MAX];
        int ni = 0;
        while (*p && (isalnum((unsigned char)*p) || *p == '_')
               && ni < PP_NAME_MAX - 1) {
            name[ni++] = *p++;
        }
        name[ni] = '\0';

        pp_undef(pp, name);
        return 1;
    }

    /* ---- #include <file.h> or #include "file.h" ---- */
    if (strcmp(directive, "include") == 0) {
        if (!pp_is_active(pp)) return 1;

        char delim_end;
        if (*p == '<') {
            delim_end = '>';
        } else if (*p == '"') {
            delim_end = '"';
        } else {
            fprintf(stderr, "[Preprocessor] Invalid #include syntax: %s\n", line);
            return 1;
        }
        p++;

        char inc_path[PATH_MAX];
        int ii = 0;
        while (*p && *p != delim_end && ii < (int)sizeof(inc_path) - 1) {
            inc_path[ii++] = *p++;
        }
        inc_path[ii] = '\0';

        pp_handle_include(pp, inc_path, filename);
        return 1;
    }

    /* ---- #ifdef NAME ---- */
    if (strcmp(directive, "ifdef") == 0) {
        char name[PP_NAME_MAX];
        int ni = 0;
        while (*p && (isalnum((unsigned char)*p) || *p == '_')
               && ni < PP_NAME_MAX - 1) {
            name[ni++] = *p++;
        }
        name[ni] = '\0';

        pp->cond_depth++;
        if (pp->cond_depth < PP_MAX_COND_DEPTH) {
            pp->cond_active[pp->cond_depth] =
                pp_parent_active(pp) && (pp_lookup(pp, name) != NULL);
        }
        return 1;
    }

    /* ---- #ifndef NAME ---- */
    if (strcmp(directive, "ifndef") == 0) {
        char name[PP_NAME_MAX];
        int ni = 0;
        while (*p && (isalnum((unsigned char)*p) || *p == '_')
               && ni < PP_NAME_MAX - 1) {
            name[ni++] = *p++;
        }
        name[ni] = '\0';

        pp->cond_depth++;
        if (pp->cond_depth < PP_MAX_COND_DEPTH) {
            pp->cond_active[pp->cond_depth] =
                pp_parent_active(pp) && (pp_lookup(pp, name) == NULL);
        }
        return 1;
    }

    /* ---- #else ---- */
    if (strcmp(directive, "else") == 0) {
        if (pp->cond_depth > 0 && pp->cond_depth < PP_MAX_COND_DEPTH) {
            if (pp_parent_active(pp)) {
                pp->cond_active[pp->cond_depth] =
                    !pp->cond_active[pp->cond_depth];
            }
        }
        return 1;
    }

    /* ---- #endif ---- */
    if (strcmp(directive, "endif") == 0) {
        if (pp->cond_depth > 0) {
            pp->cond_depth--;
        }
        return 1;
    }

    /* Unknown directive - skip silently */
    return 1;
}

/* ========== Core Processing ========== */

/**
 * Process source text line by line.
 * If output is non-NULL, append expanded lines to it.
 * Always processes directives and updates the macro table.
 */
static void pp_process(PPState *pp, const char *source,
                       const char *filename, PPBuf *output) {
    const char *p = source;

    while (*p) {
        /* Extract one line (up to newline or end of string) */
        const char *line_start = p;
        while (*p && *p != '\n') p++;
        size_t line_len = (size_t)(p - line_start);
        if (*p == '\n') p++;

        /* Copy line into temporary buffer */
        char *line = malloc(line_len + 1);
        memcpy(line, line_start, line_len);
        line[line_len] = '\0';

        /* Check if it's a directive line */
        const char *lp = line;
        while (*lp && isspace((unsigned char)*lp)) lp++;

        if (*lp == '#') {
            /* Process directive (updates state) */
            pp_handle_directive(pp, line, filename);

            /* Replace directive line with empty line in output */
            if (output) {
                ppbuf_append_char(output, '\n');
            }
        } else {
            /* Regular line */
            if (output) {
                if (pp_is_active(pp)) {
                    /* Expand macros and emit */
                    char *expanded = pp_expand_macros(pp, line);
                    ppbuf_append_str(output, expanded);
                    ppbuf_append_char(output, '\n');
                    free(expanded);
                } else {
                    /* In inactive conditional section - emit empty line */
                    ppbuf_append_char(output, '\n');
                }
            }
        }

        free(line);
    }
}

/* ========== Public API ========== */

char* preprocess_lpc(const char *source, const char *filename) {
    if (!source) return NULL;

    PPState pp;
    memset(&pp, 0, sizeof(pp));

    /* Initialize cond_active[0] = 1 (top level is always active) */
    pp.cond_active[0] = 1;

    /* Determine mudlib path */
    const char *mudlib = getenv("AMLP_MUDLIB");
    if (!mudlib || !*mudlib) mudlib = "./lib";
    strncpy(pp.mudlib_path, mudlib, sizeof(pp.mudlib_path) - 1);

    /* Pre-define built-in macros */
    pp_define(&pp, "catch", "");  /* catch { } -> { } (no-op wrapper) */

    /* Process source */
    PPBuf output;
    ppbuf_init(&output);

    pp_process(&pp, source, filename, &output);

    /* Check for unclosed conditionals */
    if (pp.cond_depth > 0) {
        fprintf(stderr, "[Preprocessor] Warning: %d unclosed #ifdef/#ifndef in '%s'\n",
                pp.cond_depth, filename ? filename : "<unknown>");
    }

    /* Cleanup included file tracking */
    for (int i = 0; i < pp.include_count; i++) {
        free(pp.included_files[i]);
    }

    fprintf(stderr, "[Preprocessor] Processed '%s': %d macros defined\n",
            filename ? filename : "<string>", pp.macro_count);

    return output.data;
}
