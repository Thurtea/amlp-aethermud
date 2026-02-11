/* ui_frames.h - Unicode box-drawing UI helpers for AetherMUD */
#ifndef UI_FRAMES_H
#define UI_FRAMES_H

/* Forward declaration */
typedef struct PlayerSession PlayerSession;

/* Default frame width (inner content width, not counting borders) */
/* NOTE: changed from 55 to a wider default; per-session width should be used when available */
#define FRAME_WIDTH 80

/* Box-drawing functions - all output via send_to_player */

/* Draw top border:  ┌──────────────────────────────┐ */
void frame_top(PlayerSession *sess, int width);

/* Draw bottom border: └──────────────────────────────┘ */
void frame_bottom(PlayerSession *sess, int width);

/* Draw separator:   ├──────────────────────────────┤ */
void frame_sep(PlayerSession *sess, int width);

/* Draw a centered title row: │       TITLE HERE       │ */
void frame_title(PlayerSession *sess, const char *title, int width);

/* Draw a left-aligned content line: │ text here              │ */
void frame_line(PlayerSession *sess, const char *text, int width);

/* Draw an empty line: │                              │ */
void frame_blank(PlayerSession *sess, int width);

/* Draw a section header (separator + title): ├──── HEADER ────┤ */
void frame_header(PlayerSession *sess, const char *label, int width);

/* Convenience: full titled box around a single block of text */
/* Splits text on \n and frames each line */
void frame_box(PlayerSession *sess, const char *title, const char *content, int width);

#endif /* UI_FRAMES_H */
