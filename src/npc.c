/* npc.c - NPC/mob spawning, AI, and combat integration */

#include "npc.h"
#include "combat.h"
#include "room.h"
#include "session_internal.h"
#include "race_loader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* External */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* ================================================================ */
/*  NPC Templates                                                    */
/* ================================================================ */

const NpcTemplate NPC_TEMPLATES[NPC_TEMPLATE_COUNT] = {
    /* Goblin: L1, SDC creature */
    {
        .template_id = NPC_GOBLIN,
        .name = "a goblin", .keyword = "goblin",
        .level = 1, .health_type = HP_SDC,
        .hp = 20, .max_hp = 20, .sdc = 30, .max_sdc = 30, .mdc = 0, .max_mdc = 0,
        .attacks_per_round = 2, .parries_per_round = 1,
        .auto_parry = 0, .auto_dodge = 0,
        .iq = 8, .me = 8, .ma = 6, .ps = 10, .pp = 10, .pe = 10, .pb = 4, .spd = 12,
        .weapon_dice = 1, .weapon_sides = 4, .weapon_name = "claws",
        .xp_reward = 50, .aggro = 1
    },
    /* Dog Boy: L3, MDC creature */
    {
        .template_id = NPC_DOG_BOY,
        .name = "a Dog Boy scout", .keyword = "scout",
        .level = 3, .health_type = MDC_ONLY,
        .hp = 50, .max_hp = 50, .sdc = 0, .max_sdc = 0, .mdc = 50, .max_mdc = 50,
        .attacks_per_round = 3, .parries_per_round = 2,
        .auto_parry = 1, .auto_dodge = 0,
        .iq = 10, .me = 12, .ma = 10, .ps = 16, .pp = 14, .pe = 14, .pb = 8, .spd = 18,
        .weapon_dice = 2, .weapon_sides = 6, .weapon_name = "rifle butt",
        .xp_reward = 150, .aggro = 1
    },
    /* Dead Boy: L5, MDC creature */
    {
        .template_id = NPC_DEAD_BOY,
        .name = "a Coalition Dead Boy", .keyword = "dead boy",
        .level = 5, .health_type = MDC_ONLY,
        .hp = 100, .max_hp = 100, .sdc = 0, .max_sdc = 0, .mdc = 100, .max_mdc = 100,
        .attacks_per_round = 4, .parries_per_round = 2,
        .auto_parry = 1, .auto_dodge = 1,
        .iq = 12, .me = 14, .ma = 8, .ps = 18, .pp = 16, .pe = 16, .pb = 10, .spd = 14,
        .weapon_dice = 3, .weapon_sides = 6, .weapon_name = "vibro-blade",
        .xp_reward = 250, .aggro = 1
    },
    /* Brodkil: L7, MDC demon */
    {
        .template_id = NPC_BRODKIL,
        .name = "a Brodkil demon", .keyword = "brodkil",
        .level = 7, .health_type = MDC_ONLY,
        .hp = 200, .max_hp = 200, .sdc = 0, .max_sdc = 0, .mdc = 200, .max_mdc = 200,
        .attacks_per_round = 5, .parries_per_round = 3,
        .auto_parry = 1, .auto_dodge = 1,
        .iq = 10, .me = 16, .ma = 6, .ps = 24, .pp = 18, .pe = 20, .pb = 6, .spd = 16,
        .weapon_dice = 4, .weapon_sides = 6, .weapon_name = "claws",
        .xp_reward = 500, .aggro = 1
    },
    /* Dragon Hatchling: L10, MDC creature */
    {
        .template_id = NPC_DRAGON_HATCHLING,
        .name = "a young dragon hatchling", .keyword = "dragon",
        .level = 10, .health_type = MDC_ONLY,
        .hp = 400, .max_hp = 400, .sdc = 0, .max_sdc = 0, .mdc = 400, .max_mdc = 400,
        .attacks_per_round = 6, .parries_per_round = 4,
        .auto_parry = 1, .auto_dodge = 1,
        .iq = 14, .me = 18, .ma = 12, .ps = 28, .pp = 20, .pe = 22, .pb = 14, .spd = 30,
        .weapon_dice = 5, .weapon_sides = 6, .weapon_name = "claws and bite",
        .xp_reward = 1000, .aggro = 1
    },
    /* Moxim: L15, MDC creature, rift travel NPC — non-aggro, very tough */
    {
        .template_id = NPC_MOXIM,
        .name = "a shimmering Moxim", .keyword = "moxim",
        .level = 15, .health_type = MDC_ONLY,
        .hp = 800, .max_hp = 800, .sdc = 0, .max_sdc = 0, .mdc = 800, .max_mdc = 800,
        .attacks_per_round = 8, .parries_per_round = 6,
        .auto_parry = 1, .auto_dodge = 1,
        .iq = 22, .me = 24, .ma = 20, .ps = 30, .pp = 24, .pe = 26, .pb = 18, .spd = 40,
        .weapon_dice = 6, .weapon_sides = 6, .weapon_name = "rift energy blast",
        .xp_reward = 2000, .aggro = 0
    }
};

/* ================================================================ */
/*  Global NPC Pool                                                  */
/* ================================================================ */

static NPC npc_pool[MAX_NPCS_GLOBAL];
static int npc_next_id = 1;

void npc_init(void) {
    memset(npc_pool, 0, sizeof(npc_pool));
    npc_next_id = 1;
    fprintf(stderr, "[NPC] System initialized (%d slots, %d templates)\n",
            MAX_NPCS_GLOBAL, NPC_TEMPLATE_COUNT);
}

void npc_cleanup(void) {
    for (int i = 0; i < MAX_NPCS_GLOBAL; i++) {
        if (npc_pool[i].id != 0) {
            npc_pool[i].id = 0;
            npc_pool[i].is_alive = 0;
        }
    }
}

/* ================================================================ */
/*  Spawning                                                         */
/* ================================================================ */

NPC* npc_spawn(NpcTemplateId template_id, int room_id) {
    if (template_id < 0 || template_id >= NPC_TEMPLATE_COUNT) return NULL;

    /* Find free pool slot */
    NPC *npc = NULL;
    for (int i = 0; i < MAX_NPCS_GLOBAL; i++) {
        if (npc_pool[i].id == 0) {
            npc = &npc_pool[i];
            break;
        }
    }
    if (!npc) {
        fprintf(stderr, "[NPC] Pool full, cannot spawn template %d\n", template_id);
        return NULL;
    }

    const NpcTemplate *t = &NPC_TEMPLATES[template_id];

    /* Initialize NPC */
    memset(npc, 0, sizeof(NPC));
    npc->id = npc_next_id++;
    npc->template_id = template_id;
    snprintf(npc->name, sizeof(npc->name), "%s", t->name);
    snprintf(npc->keyword, sizeof(npc->keyword), "%s", t->keyword);
    npc->is_alive = 1;
    npc->respawn_timer = -1;
    npc->respawn_room_id = room_id;
    npc->aggro = t->aggro;

    /* Populate Character struct from template */
    Character *ch = &npc->character;
    ch->level = t->level;
    ch->health_type = t->health_type;
    ch->hp = t->hp;
    ch->max_hp = t->max_hp;
    ch->sdc = t->sdc;
    ch->max_sdc = t->max_sdc;
    ch->mdc = t->mdc;
    ch->max_mdc = t->max_mdc;
    ch->attacks_per_round = t->attacks_per_round;
    ch->parries_per_round = t->parries_per_round;
    ch->racial_auto_parry = t->auto_parry;
    ch->racial_auto_dodge = t->auto_dodge;
    ch->auto_parry_enabled = t->auto_parry;
    ch->auto_dodge_enabled = t->auto_dodge;
    ch->stats.iq = t->iq;
    ch->stats.me = t->me;
    ch->stats.ma = t->ma;
    ch->stats.ps = t->ps;
    ch->stats.pp = t->pp;
    ch->stats.pe = t->pe;
    ch->stats.pb = t->pb;
    ch->stats.spd = t->spd;

    /* Place in room */
    Room *room = room_get_by_id(room_id);
    if (room) {
        npc->current_room = room;
        room_add_npc(room, npc);
    } else {
        fprintf(stderr, "[NPC] Warning: room %d not found for spawn\n", room_id);
    }

    fprintf(stderr, "[NPC] Spawned '%s' (id=%d) in room %d\n",
            npc->name, npc->id, room_id);
    return npc;
}

void npc_despawn(NPC *npc) {
    if (!npc) return;
    if (npc->current_room) {
        room_remove_npc(npc->current_room, npc);
    }
    npc->is_alive = 0;
    npc->in_combat = 0;
    npc->combat_target_player = NULL;
    npc->current_room = NULL;
}

/* Internal: respawn a dead NPC at its original room */
static void npc_respawn(NPC *npc) {
    if (!npc || npc->template_id < 0 || npc->template_id >= NPC_TEMPLATE_COUNT) return;

    const NpcTemplate *t = &NPC_TEMPLATES[npc->template_id];
    int room_id = npc->respawn_room_id;

    /* Reset character stats from template */
    Character *ch = &npc->character;
    ch->hp = t->hp;
    ch->max_hp = t->max_hp;
    ch->sdc = t->sdc;
    ch->max_sdc = t->max_sdc;
    ch->mdc = t->mdc;
    ch->max_mdc = t->max_mdc;

    npc->is_alive = 1;
    npc->in_combat = 0;
    npc->combat_target_player = NULL;
    npc->respawn_timer = -1;

    Room *room = room_get_by_id(room_id);
    if (room) {
        npc->current_room = room;
        room_add_npc(room, npc);

        /* Announce to room */
        char msg[128];
        char display[64];
        snprintf(display, sizeof(display), "%s", npc->name);
        display[0] = (char)toupper((unsigned char)display[0]);
        snprintf(msg, sizeof(msg), "%s appears.\r\n", display);
        room_broadcast(room, msg, NULL);
    }
}

/* ================================================================ */
/*  NPC Tick — AI + Respawn                                          */
/* ================================================================ */

void npc_tick(void) {
    for (int i = 0; i < MAX_NPCS_GLOBAL; i++) {
        NPC *npc = &npc_pool[i];
        if (npc->id == 0) continue;

        /* Respawn check for dead NPCs */
        if (!npc->is_alive) {
            if (npc->respawn_timer > 0) {
                npc->respawn_timer--;
                if (npc->respawn_timer <= 0) {
                    npc_respawn(npc);
                }
            }
            continue;
        }

        /* Aggro AI: if not in combat and aggressive, scan for players */
        if (!npc->in_combat && npc->aggro && npc->current_room) {
            Room *room = npc->current_room;
            for (int j = 0; j < room->num_players; j++) {
                PlayerSession *p = room->players[j];
                if (p && p->state == STATE_PLAYING && !p->in_combat && !p->is_godmode) {
                    /* Engage this player */
                    combat_engage_npc(p, npc);
                    break;
                }
            }
        }
    }
}

/* ================================================================ */
/*  Death Handling                                                   */
/* ================================================================ */

void npc_handle_death(NPC *npc, PlayerSession *killer) {
    if (!npc) return;

    /* Mark dead */
    npc->is_alive = 0;
    npc->in_combat = 0;
    npc->combat_target_player = NULL;

    /* Set respawn timer: Moxim respawns fast (10 ticks = 20s), others 30 ticks = 60s */
    npc->respawn_timer = (npc->template_id == NPC_MOXIM) ? 10 : 30;

    /* Remove from room */
    if (npc->current_room) {
        char msg[128];
        char display[64];
        snprintf(display, sizeof(display), "%s", npc->name);
        display[0] = (char)toupper((unsigned char)display[0]);
        snprintf(msg, sizeof(msg), "%s collapses and dies!\r\n", display);
        room_broadcast(npc->current_room, msg, NULL);
        room_remove_npc(npc->current_room, npc);
        npc->current_room = NULL;
    }

    /* Award XP to killer */
    if (killer) {
        const NpcTemplate *t = &NPC_TEMPLATES[npc->template_id];
        int xp = t->xp_reward;
        killer->character.xp += xp;
        send_to_player(killer, "You gain %d experience points!\n", xp);

        /* Check for level up */
        check_and_apply_level_up(killer);
    }
}

/* ================================================================ */
/*  Lookups                                                          */
/* ================================================================ */

/* Check if input matches an NPC's name (case-insensitive substring).
 * Strips leading article ("a ", "an ", "the ") from the NPC name before
 * comparing so "dog boy scout" matches "a Dog Boy scout". */
static int npc_name_matches(NPC *n, const char *input) {
    if (!n || !input || !*input) return 0;

    /* Try substring match against full name */
    if (strcasestr(n->name, input) != NULL) return 1;

    /* Strip leading article from NPC name and try again */
    const char *stripped = n->name;
    if (strncasecmp(stripped, "a ", 2) == 0) stripped += 2;
    else if (strncasecmp(stripped, "an ", 3) == 0) stripped += 3;
    else if (strncasecmp(stripped, "the ", 4) == 0) stripped += 4;

    if (stripped != n->name) {
        if (strcasecmp(stripped, input) == 0) return 2; /* exact sans article */
        if (strcasestr(stripped, input) != NULL) return 1;
    }

    return 0;
}

NPC* npc_find_in_room(Room *room, const char *keyword) {
    if (!room || !keyword) return NULL;

    /* 1. Exact keyword match */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && strcasecmp(n->keyword, keyword) == 0) {
            return n;
        }
    }
    /* 2. Exact name match (sans article) */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && npc_name_matches(n, keyword) == 2) {
            return n;
        }
    }
    /* 3. Partial keyword match */
    int klen = (int)strlen(keyword);
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && strncasecmp(n->keyword, keyword, klen) == 0) {
            return n;
        }
    }
    /* 4. Name substring match */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && npc_name_matches(n, keyword)) {
            return n;
        }
    }
    return NULL;
}

NPC* npc_find_by_character(Character *ch) {
    if (!ch) return NULL;
    for (int i = 0; i < MAX_NPCS_GLOBAL; i++) {
        if (npc_pool[i].id != 0 && &npc_pool[i].character == ch) {
            return &npc_pool[i];
        }
    }
    return NULL;
}

NPC* npc_get_by_id(int id) {
    for (int i = 0; i < MAX_NPCS_GLOBAL; i++) {
        if (npc_pool[i].id == id) return &npc_pool[i];
    }
    return NULL;
}

/* ================================================================ */
/*  Unified Target Resolution                                        */
/* ================================================================ */

int resolve_target(Room *room, const char *name,
                   PlayerSession *exclude,
                   PlayerSession **out_player,
                   NPC **out_npc) {
    if (!room || !name || !*name) return 0;
    if (out_player) *out_player = NULL;
    if (out_npc) *out_npc = NULL;

    int nlen = (int)strlen(name);

    /* 1. Exact player name match */
    for (int i = 0; i < room->num_players; i++) {
        PlayerSession *p = room->players[i];
        if (p && p != exclude &&
            strcasecmp(p->username, name) == 0) {
            if (out_player) *out_player = p;
            return 1;
        }
    }

    /* 2. Exact NPC keyword match */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && strcasecmp(n->keyword, name) == 0) {
            if (out_npc) *out_npc = n;
            return 2;
        }
    }

    /* 3. Exact NPC name match (sans article) */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && npc_name_matches(n, name) == 2) {
            if (out_npc) *out_npc = n;
            return 2;
        }
    }

    /* 4. Partial player name match */
    for (int i = 0; i < room->num_players; i++) {
        PlayerSession *p = room->players[i];
        if (p && p != exclude &&
            strncasecmp(p->username, name, nlen) == 0) {
            if (out_player) *out_player = p;
            return 1;
        }
    }

    /* 5. Partial NPC keyword match */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && strncasecmp(n->keyword, name, nlen) == 0) {
            if (out_npc) *out_npc = n;
            return 2;
        }
    }

    /* 6. NPC name substring match (e.g. "dog" matches "a Dog Boy scout") */
    for (int i = 0; i < room->num_npcs; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && npc_name_matches(n, name)) {
            if (out_npc) *out_npc = n;
            return 2;
        }
    }

    return 0;
}
