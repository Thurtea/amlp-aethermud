/* ui_frames.c - Unicode box-drawing UI helpers for AetherMUD */
#include "ui_frames.h"
#include "session_internal.h"
#include <stdio.h>
#include <string.h>

/* External from session.c */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* ASCII box-drawing characters (plain telnet compatible) */
#define BOX_TL "+"
#define BOX_TR "+"
#define BOX_BL "+"
#define BOX_BR "+"
#define BOX_H  "-"
#define BOX_V  "|"
#define BOX_LT "+"
#define BOX_RT "+"

/* Draw a horizontal line of width box-chars */
static void draw_hline(PlayerSession *sess, int width) {
    for (int i = 0; i < width; i++) {
        send_to_player(sess, BOX_H);
    }
}

/* ┌────────────────────────────┐ */
void frame_top(PlayerSession *sess, int width) {
    send_to_player(sess, BOX_TL);
    draw_hline(sess, width);
    send_to_player(sess, BOX_TR "\r\n");
}

/* └────────────────────────────┘ */
void frame_bottom(PlayerSession *sess, int width) {
    send_to_player(sess, BOX_BL);
    draw_hline(sess, width);
    send_to_player(sess, BOX_BR "\r\n");
}

/* ├────────────────────────────┤ */
void frame_sep(PlayerSession *sess, int width) {
    send_to_player(sess, BOX_LT);
    draw_hline(sess, width);
    send_to_player(sess, BOX_RT "\r\n");
}

/* │       CENTERED TITLE       │ */
void frame_title(PlayerSession *sess, const char *title, int width) {
    int tlen = (int)strlen(title);
    int pad_left = (width - tlen) / 2;
    int pad_right = width - tlen - pad_left;
    if (pad_left < 0) pad_left = 0;
    if (pad_right < 0) pad_right = 0;

    send_to_player(sess, BOX_V);
    for (int i = 0; i < pad_left; i++) send_to_player(sess, " ");
    send_to_player(sess, "%s", title);
    for (int i = 0; i < pad_right; i++) send_to_player(sess, " ");
    send_to_player(sess, BOX_V "\r\n");
}

/* │ left-aligned text          │ */
/* Count visible characters in a string, skipping ANSI escape sequences */
static int ansi_visible_len(const char *s) {
    int len = 0;
    while (*s) {
        if (*s == '\033' && *(s+1) == '[') {
            s += 2;
            while (*s && *s != 'm') s++;
            if (*s) s++;
        } else {
            len++;
            s++;
        }
    }
    return len;
}

void frame_line(PlayerSession *sess, const char *text, int width) {
    int tlen = ansi_visible_len(text);
    send_to_player(sess, BOX_V " ");
    send_to_player(sess, "%s", text);
    int remaining = width - 1 - tlen;
    if (remaining < 0) remaining = 0;
    for (int i = 0; i < remaining; i++) send_to_player(sess, " ");
    send_to_player(sess, BOX_V "\r\n");
}

/* │                            │ */
void frame_blank(PlayerSession *sess, int width) {
    send_to_player(sess, BOX_V);
    for (int i = 0; i < width; i++) send_to_player(sess, " ");
    send_to_player(sess, BOX_V "\r\n");
}

/* ├──── HEADER ────────────────┤ */
void frame_header(PlayerSession *sess, const char *label, int width) {
    int llen = (int)strlen(label);
    int dashes_before = 2;
    int dashes_after = width - dashes_before - llen - 2; /* 2 spaces around label */
    if (dashes_after < 2) dashes_after = 2;

    send_to_player(sess, BOX_LT);
    for (int i = 0; i < dashes_before; i++) send_to_player(sess, BOX_H);
    send_to_player(sess, " %s ", label);
    for (int i = 0; i < dashes_after; i++) send_to_player(sess, BOX_H);
    send_to_player(sess, BOX_RT "\r\n");
}

/* Full box: top + title + sep + content lines + bottom */
void frame_box(PlayerSession *sess, const char *title, const char *content, int width) {
    frame_top(sess, width);
    if (title && title[0]) {
        frame_title(sess, title, width);
        frame_sep(sess, width);
    }

    /* Split content on newlines and frame each line */
    if (content && content[0]) {
        const char *p = content;
        char line_buf[256];
        while (*p) {
            const char *nl = strchr(p, '\n');
            int len;
            if (nl) {
                len = (int)(nl - p);
                if (len >= (int)sizeof(line_buf)) len = sizeof(line_buf) - 1;
                memcpy(line_buf, p, len);
                line_buf[len] = '\0';
                p = nl + 1;
            } else {
                len = (int)strlen(p);
                if (len >= (int)sizeof(line_buf)) len = sizeof(line_buf) - 1;
                memcpy(line_buf, p, len);
                line_buf[len] = '\0';
                p += len;
            }
            /* Skip \r if present */
            if (len > 0 && line_buf[len - 1] == '\r') line_buf[--len] = '\0';

            if (len == 0) {
                frame_blank(sess, width);
            } else {
                frame_line(sess, line_buf, width);
            }
        }
    }

    frame_bottom(sess, width);
}
