/* npc.h - NPC/mob system for spawnable creatures */

#ifndef NPC_H
#define NPC_H

#include <stdbool.h>
#include "chargen.h"

/* Forward declarations */
typedef struct PlayerSession PlayerSession;
typedef struct Room Room;
struct CombatParticipant;

#define MAX_NPCS_PER_ROOM 8
#define MAX_NPCS_GLOBAL 64

/* NPC template IDs */
typedef enum {
    NPC_GOBLIN = 0,
    NPC_DOG_BOY,
    NPC_DEAD_BOY,
    NPC_BRODKIL,
    NPC_DRAGON_HATCHLING,
    NPC_MOXIM,
    NPC_TEMPLATE_COUNT
} NpcTemplateId;

/* NPC template (static data) */
typedef struct {
    NpcTemplateId template_id;
    const char *name;           /* Display name: "a goblin" */
    const char *keyword;        /* Targeting keyword: "goblin" */
    int level;
    HealthType health_type;
    int hp, max_hp;
    int sdc, max_sdc;
    int mdc, max_mdc;
    int attacks_per_round;
    int parries_per_round;
    int auto_parry, auto_dodge;
    int iq, me, ma, ps, pp, pe, pb, spd;
    int weapon_dice, weapon_sides;
    const char *weapon_name;    /* "claws", "vibro-blade", etc. */
    int xp_reward;
    int aggro;                  /* 1 = attacks players on sight */
} NpcTemplate;

/* NPC instance (runtime) */
typedef struct NPC {
    int id;                     /* Unique instance ID (0 = unused slot) */
    int template_id;            /* Which template spawned this */
    char name[64];              /* Display name */
    char keyword[32];           /* Targeting keyword */
    Character character;        /* Embedded character data — reused by combat */
    Room *current_room;         /* Room this NPC is in */
    int is_alive;
    int respawn_timer;          /* Ticks until respawn (-1 = no respawn) */
    int respawn_room_id;        /* Room ID to respawn in */
    int aggro;                  /* Auto-attacks players on sight */

    /* Combat state */
    PlayerSession *combat_target_player;
    int in_combat;
} NPC;

/* Initialization and cleanup */
void npc_init(void);
void npc_cleanup(void);

/* Spawning */
NPC* npc_spawn(NpcTemplateId template_id, int room_id);
void npc_despawn(NPC *npc);

/* Tick — AI and respawn (called every 2s from heartbeat) */
void npc_tick(void);

/* Room queries */
NPC* npc_find_in_room(Room *room, const char *keyword);

/* Combat */
void npc_handle_death(NPC *npc, PlayerSession *killer);
NPC* npc_find_by_character(Character *ch);

/* Target resolution: searches room for player or NPC by name.
 * Returns: 0=not found, 1=player found, 2=NPC found.
 * Sets out_player or out_npc accordingly. */
int resolve_target(Room *room, const char *name,
                   PlayerSession *exclude,
                   PlayerSession **out_player,
                   NPC **out_npc);

/* Template access */
extern const NpcTemplate NPC_TEMPLATES[NPC_TEMPLATE_COUNT];

#endif /* NPC_H */
