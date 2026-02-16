#ifndef ROOM_H
#define ROOM_H

#include <stddef.h>
#include <stdbool.h>
#include "item.h"

/* Forward declare from session_internal.h */
typedef struct PlayerSession PlayerSession;
typedef struct NPC NPC;

#define MAX_NPCS_PER_ROOM 8

/* Flexible exit: supports any direction name + LPC path destinations */
typedef struct {
    char *direction;    /* "north", "out", "arena", etc. */
    char *target_path;  /* LPC path: "/domains/start/room/void" */
} RoomExit;

/* Examinable room detail from set_items() */
typedef struct {
    char *keyword;      /* "fountain", "sand", etc. */
    char *description;  /* Description shown on examine */
} RoomDetail;

/* Room structure */
typedef struct Room {
    int id;
    char *name;
    char *description;
    char *lpc_path;     /* Source LPC file path (NULL for C bootstrap rooms) */
    struct {
        int north;
        int south;
        int east;
        int west;
        int up;
        int down;
    } exits;
    /* Flexible exits (LPC rooms use these instead of cardinal exits) */
    RoomExit *flex_exits;
    int num_flex_exits;
    /* Examinable details from set_items() */
    RoomDetail *details;
    int num_details;
    Item *items;  /* Linked list of items on the ground */
    PlayerSession **players;  /* Array of players in room */
    int num_players;
    int max_players;
    NPC *npcs[MAX_NPCS_PER_ROOM];  /* NPCs currently in room */
    int num_npcs;
    /* Room properties parsed from LPC set_property() calls */
    int light_level;     /* 0=dark,1=dim,2=normal(lit),3=bright */
    bool is_indoors;     /* true if indoors */
    bool no_magic;       /* true if magic is blocked */
    bool no_combat;      /* true if combat is blocked */
} Room;

/* World management */
void room_init_world(void);
void room_cleanup_world(void);
Room* room_get_by_id(int id);
Room* room_get_start(void);
Room* room_get_by_path(const char *lpc_path);  /* Load-on-demand LPC room */
Room* room_reload_lpc(const char *lpc_path);   /* Reload LPC room from disk */

/* Room operations */
void room_add_player(Room *room, PlayerSession *player);
void room_remove_player(Room *room, PlayerSession *player);
void room_add_item(Room *room, Item *item);
Item* room_find_item(Room *room, const char *name);
void room_remove_item(Room *room, Item *item);
void room_broadcast(Room *room, const char *message, PlayerSession *exclude);
void room_add_npc(Room *room, NPC *npc);
void room_remove_npc(Room *room, NPC *npc);
const char* room_find_detail(Room *room, const char *keyword);

/* Room commands */
void cmd_look(PlayerSession *sess, const char *args);
void cmd_move(PlayerSession *sess, const char *direction);
void cmd_rift(PlayerSession *sess, const char *args);

#endif /* ROOM_H */
