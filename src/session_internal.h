/* session_internal.h - Internal PlayerSession definition shared by driver and session.c */
#ifndef SESSION_INTERNAL_H
#define SESSION_INTERNAL_H

#include <time.h>
#include <netinet/in.h>
#include "websocket.h"
#include "chargen.h"  /* Character generation system */

/* Forward declarations */
typedef struct Room Room;

#define MAX_CLIENTS 100

#define INPUT_BUFFER_SIZE 2048
#define WS_BUFFER_SIZE 65536

typedef enum {
    STATE_CONNECTING,
    STATE_GET_NAME,
    STATE_GET_PASSWORD,
    STATE_NEW_PASSWORD,
    STATE_CONFIRM_PASSWORD,
    STATE_CHARGEN,      /* New state for character generation */
    STATE_PLAYING,
    STATE_DISCONNECTING
} SessionState;

typedef enum {
    CONN_TELNET,
    CONN_WEBSOCKET
} ConnectionType;

typedef struct PlayerSession {
    int fd;
    SessionState state;
    ConnectionType connection_type;
    WSState ws_state;
    char username[64];
    char password_buffer[128];
    char password_hash[128];      /* Stored password hash for verification */
    char input_buffer[INPUT_BUFFER_SIZE];
    size_t input_length;
    uint8_t ws_buffer[WS_BUFFER_SIZE];
    size_t ws_buffer_length;
    time_t last_activity;
    time_t connect_time;
    void *player_object;
    char ip_address[INET_ADDRSTRLEN];
    int privilege_level;
    char wizard_role[32];    /* Wizard role: "admin", "domain", "code", "roleplay" */
    char *current_dir;       /* Wizard/admin filesystem navigation directory */
    
    /* Character generation and game state */
    ChargenState chargen_state;
    int chargen_page;        /* Current page for paginated menus */
    int chargen_temp_choice; /* Temporary storage for menu selection */
    Character character;
    Room *current_room;
    /* For LPC rooms persistence: store original LPC path (if any).
     * New in save format version 3. NULL when not used. */
    char *current_room_path;

    /* Wizard tools */
    struct PlayerSession *snooping;      /* Session being snooped on */
    struct PlayerSession *snooped_by;    /* Session that is snooping us */
    int is_invisible;                    /* Wizard invisibility flag */
    int is_godmode;                      /* God mode - immune to damage */
    char title[128];                     /* Custom title for who list */
    char enter_msg[128];                 /* Custom room enter message */
    char leave_msg[128];                 /* Custom room leave message */
    char goto_msg[128];                  /* Custom goto arrival message */

    /* Real-time combat state */
    struct PlayerSession *combat_target;  /* Current combat target */
    int in_combat;                        /* 1 if in active combat */

    /* Spell targeting */
    struct PlayerSession *spell_target;   /* Resolved target for current spell */
    struct NPC *spell_target_npc;         /* Resolved NPC target for current spell */

    /* Social/RP state */
    char last_tell_from[64];              /* Username of last tell sender (for reply) */
    int is_brief;                         /* Brief mode: skip long room descriptions */
    int is_color;                         /* ANSI color enabled (default 1) */
    int is_resting;                       /* Resting state (regen bonus) */
    char custom_prompt[128];              /* Custom prompt format string */
    int converse_mode;                    /* 1 = every input becomes "say" */
    /* Terminal geometry (can be overridden by client/efun) */
    int terminal_width;                    /* columns, default set on init */
    int terminal_height;                   /* rows, default set on init */

    /* In-game editor (ed) state */
    int ed_active;                 /* 1 when in interactive ed mode */
    char ed_vpath[512];            /* virtual path seen by player (/domains/...) */
    char ed_fspath[1024];          /* actual filesystem path (lib/...) */
    char **ed_lines;               /* dynamically allocated array of lines */
    int ed_lines_count;            /* number of lines loaded */
    int ed_lines_capacity;         /* allocated capacity for ed_lines */
    int ed_show_numbers;           /* 1 = show numbers when listing */
    int ed_cursor;                 /* current line index for paging (0-based) */
    int ed_input_mode;             /* 0=command, 1=append, 2=insert, 3=change */
    int ed_target_line;            /* target line number for insert/change/delete (1-based) */
} PlayerSession;

#endif /* SESSION_INTERNAL_H */
