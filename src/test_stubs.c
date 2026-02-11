/* test_stubs.c - minimal test-time stubs for symbols referenced by core modules
 * These are lightweight no-op implementations used when building unit tests
 * so tests can link without pulling the full driver/network code.
 */

#include <stddef.h>
#include <stdlib.h>

/* No-op: send a message to a player session (test-only stub)
 * Mark weak so the real implementation in `session.c` can override it
 * when linked into the full driver. */
void send_message_to_player_session(void *player_obj, const char *message) __attribute__((weak));
void send_message_to_player_session(void *player_obj, const char *message) {
    (void)player_obj;
    (void)message;
}

/* No-op: return current player object for efuns that call this; tests typically
 * don't rely on a real session, so return NULL. */
void *get_current_player_object(void) __attribute__((weak));
void *get_current_player_object(void) __attribute__((weak));
void *get_current_player_object(void) {
    return NULL;
}

/* No-op session setter used by driver efuns in tests. */
void set_current_session(void *session) __attribute__((weak));
void set_current_session(void *session) __attribute__((weak));
void set_current_session(void *session) {
    (void)session;
}

/* Weak placeholder for websocket/ANSI conversion helpers that may be referenced
 * by test-linked code; provide safe no-op implementations if missing. */
char *ws_convert_ansi(const char *text, int keep_colors) {
    (void)keep_colors;
    if (!text) return NULL;
    /* return a strdup-like allocation to match caller free() expectations */
    size_t n = 0;
    while (text[n]) n++;
    char *copy = (char *)malloc(n + 1);
    if (!copy) return NULL;
    for (size_t i = 0; i <= n; i++) copy[i] = text[i];
    return copy;
}

char *ws_normalize_line_endings(const char *s) {
    if (!s) return NULL;
    size_t n = 0;
    while (s[n]) n++;
    char *copy = (char *)malloc(n + 1);
    if (!copy) return NULL;
    for (size_t i = 0; i <= n; i++) copy[i] = s[i];
    return copy;
}

unsigned char *ws_encode_text(const char *text, size_t *out_len) {
    if (!text || !out_len) return NULL;
    size_t n = 0;
    while (text[n]) n++;
    unsigned char *buf = (unsigned char *)malloc(n);
    if (!buf) return NULL;
    for (size_t i = 0; i < n; i++) buf[i] = (unsigned char)text[i];
    *out_len = n;
    return buf;
}
