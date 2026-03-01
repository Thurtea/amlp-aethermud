#include "death.h"
#include "chargen.h"
#include "session_internal.h"
#include "room.h"
#include "item.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* Corpse/blood pool creation: handled by LPC lib/std/corpse.lpc */

#define MAX_ACTIVE_CORPSES 32
#define CORPSE_DECAY_SECS  300

typedef struct {
    Item  *corpse;
    Item  *blood_pool;   /* optional blood pool left by this corpse */
    Room  *room;
    time_t expires;
} CorpseDecayEntry;

static CorpseDecayEntry corpse_registry[MAX_ACTIVE_CORPSES];

extern void send_to_player(PlayerSession *session, const char *format, ...);

static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};

void set_death_room(PlayerSession *sess, const char *path) {
    if (!sess) return;
    if (sess->death_room_path) free(sess->death_room_path);
    sess->death_room_path = path ? strdup(path) : NULL;
}

const char *get_death_room(PlayerSession *sess) {
    if (!sess) return NULL;
    return sess->death_room_path;
}

void add_death_scar(Character *ch) {
    if (!ch) return;
    if (ch->scar_count >= MAX_SCARS) return;

    int idx_loc = rand() % (sizeof(scar_locations)/sizeof(scar_locations[0]));
    int idx_desc = rand() % (sizeof(scar_descriptions)/sizeof(scar_descriptions[0]));

    strncpy(ch->scars[ch->scar_count].location, scar_locations[idx_loc], sizeof(ch->scars[ch->scar_count].location)-1);
    ch->scars[ch->scar_count].location[sizeof(ch->scars[ch->scar_count].location)-1] = '\0';

    strncpy(ch->scars[ch->scar_count].description, scar_descriptions[idx_desc], sizeof(ch->scars[ch->scar_count].description)-1);
    ch->scars[ch->scar_count].description[sizeof(ch->scars[ch->scar_count].description)-1] = '\0';

    ch->scars[ch->scar_count].death_number = ch->scar_count + 1;
    ch->scar_count++;
}

void create_player_corpse(PlayerSession *sess) {
    if (!sess) return;
    Room *room = sess->current_room;

    Item *corpse = (Item *)calloc(1, sizeof(Item));
    if (!corpse) {
        INFO_LOG("create_player_corpse: out of memory for %s", sess->username);
        return;
    }

    char corpse_name[96];
    snprintf(corpse_name, sizeof(corpse_name), "the corpse of %s", sess->username);
    char corpse_desc[256];
    snprintf(corpse_desc, sizeof(corpse_desc), "The lifeless body of %s lies here.", sess->username);

    corpse->id = -1;
    corpse->name = strdup(corpse_name);
    corpse->description = strdup(corpse_desc);
    corpse->type = ITEM_MISC;
    corpse->weight = 150;
    corpse->is_container = true;
    corpse->next = NULL;

    Character *ch = &sess->character;
    corpse->contents = ch->inventory.items;
    ch->inventory.items = NULL;
    ch->inventory.item_count = 0;
    ch->inventory.total_weight = 0;

    ch->equipment.weapon_primary = NULL;
    ch->equipment.weapon_secondary = NULL;
    ch->equipment.armor = NULL;
    ch->equipment.accessory1 = NULL;
    ch->equipment.accessory2 = NULL;
    ch->equipment.accessory3 = NULL;

    if (room) {
        room_add_item(room, corpse);
        char msg[128];
        snprintf(msg, sizeof(msg), "%s collapses and their body falls lifeless.\n", sess->username);
        room_broadcast(room, msg, sess);

        /* Create a blood pool item in the same room */
        Item *pool = (Item *)calloc(1, sizeof(Item));
        if (pool) {
            char pool_name[96];
            snprintf(pool_name, sizeof(pool_name), "a pool of blood from %s", sess->username);
            pool->id = -2;
            pool->name = strdup(pool_name);
            pool->description = strdup("A dark, spreading pool of blood glistens here. It is still fresh.");
            pool->type = ITEM_MISC;
            pool->weight = 0;
            pool->lpc_path = strdup("/obj/blood_pool");
            pool->next = NULL;
            room_add_item(room, pool);
        }

        for (int i = 0; i < MAX_ACTIVE_CORPSES; i++) {
            if (!corpse_registry[i].corpse) {
                corpse_registry[i].corpse = corpse;
                corpse_registry[i].blood_pool = pool;
                corpse_registry[i].room = room;
                corpse_registry[i].expires = time(NULL) + CORPSE_DECAY_SECS;
                break;
            }
        }
    } else {
        Item *c = corpse->contents;
        while (c) { Item *nx = c->next; item_free(c); c = nx; }
        free(corpse->name);
        free(corpse->description);
        free(corpse);
    }

    INFO_LOG("Corpse created for %s in room %d", sess->username, room ? room->id : -1);
}

void corpse_tick(void) {
    time_t now = time(NULL);
    for (int i = 0; i < MAX_ACTIVE_CORPSES; i++) {
        CorpseDecayEntry *e = &corpse_registry[i];
        if (!e->corpse) continue;
        if (now < e->expires) continue;

        if (e->room && e->corpse->name) {
            char msg[160];
            snprintf(msg, sizeof(msg), "%s crumbles to dust.\n", e->corpse->name);
            if (msg[0] >= 'a' && msg[0] <= 'z') msg[0] = (char)(msg[0] - 32);
            room_broadcast(e->room, msg, NULL);
        }

        if (e->room) room_remove_item(e->room, e->corpse);
        Item *c = e->corpse->contents;
        while (c) { Item *nx = c->next; item_free(c); c = nx; }
        free(e->corpse->name);
        free(e->corpse->description);
        free(e->corpse);

        /* Also remove the blood pool if it is still present */
        if (e->blood_pool) {
            if (e->room) room_remove_item(e->room, e->blood_pool);
            free(e->blood_pool->name);
            free(e->blood_pool->description);
            if (e->blood_pool->lpc_path) free(e->blood_pool->lpc_path);
            free(e->blood_pool);
            e->blood_pool = NULL;
        }

        e->corpse = NULL;
        e->room = NULL;
        e->expires = 0;
    }
}

int corpse_reclaim_for_player(PlayerSession *sess) {
    if (!sess) return 0;
    sess->is_dead = 0;
    char expected[96];
    snprintf(expected, sizeof(expected), "the corpse of %s", sess->username);

    for (int i = 0; i < MAX_ACTIVE_CORPSES; i++) {
        CorpseDecayEntry *e = &corpse_registry[i];
        if (!e->corpse) continue;
        if (strcmp(e->corpse->name, expected) != 0) continue;

        Item *item = e->corpse->contents;
        int count = 0;
        while (item) {
            Item *next = item->next;
            item->next = NULL;
            item->next = sess->character.inventory.items;
            sess->character.inventory.items = item;
            sess->character.inventory.item_count++;
            sess->character.inventory.total_weight += item->weight;
            count++;
            item = next;
        }
        e->corpse->contents = NULL;

        if (e->room) room_remove_item(e->room, e->corpse);
        free(e->corpse->name);
        free(e->corpse->description);
        free(e->corpse);

        e->corpse = NULL;
        e->blood_pool = NULL;
        e->room = NULL;
        e->expires = 0;

        INFO_LOG("Corpse reclaimed for %s (%d items)", sess->username, count);
        return 1;
    }
    return 0;
}

void handle_player_death(PlayerSession *sess, PlayerSession *killer, const char *npc_killer_name) {
    if (!sess) return;
    if (sess->is_dead) return;
    sess->is_dead = 1;
    
    Character *ch = &sess->character;

    if (ch->lives_remaining <= 0) {
        ch->permanently_dead = 1;
        if (killer && killer->username[0]) {
            snprintf(ch->death_killer, sizeof(ch->death_killer), "%s", killer->username);
        } else if (npc_killer_name && npc_killer_name[0]) {
            snprintf(ch->death_killer, sizeof(ch->death_killer), "%s", npc_killer_name);
            ch->death_killer[0] = (char)toupper((unsigned char)ch->death_killer[0]);
        } else {
            snprintf(ch->death_killer, sizeof(ch->death_killer), "an unknown assailant");
        }
        ch->death_killer[sizeof(ch->death_killer) - 1] = '\0';
        save_character(sess);
        send_to_player(sess, "\n*** Your life force is completely exhausted. ***\nYour soul dissolves into the void... This character is gone.\n\n");
        INFO_LOG("Permanent death: %s (killed by %s)", sess->username, ch->death_killer);
        sess->state = STATE_DISCONNECTING;
        return;
    }

    ch->lives_remaining--;
    add_death_scar(ch);
    create_player_corpse(sess);

    if (killer && killer->username[0]) {
        char msg[128];
        snprintf(msg, sizeof(msg), "You have been slain by %s.\n", killer->username);
        send_to_player(sess, msg);
    }
    
    if (sess->current_room) {
        char msg[128];
        snprintf(msg, sizeof(msg), "%s collapses and dies.\n", sess->username);
        room_broadcast(sess->current_room, msg, NULL);
    }

    Room *death_room = room_get_by_path("/domains/death/recovery_room.lpc");
    if (!death_room) {
        INFO_LOG("Death recovery room not found for %s", sess->username);
        return;
    }

    if (sess->current_room && sess->current_room->lpc_path) {
        set_death_room(sess, sess->current_room->lpc_path);
    }

    if (sess->current_room) {
        room_remove_player(sess->current_room, sess);
    }

    room_add_player(death_room, sess);
    sess->current_room = death_room;

    ch->hp = ch->max_hp;
    ch->sdc = ch->max_sdc;
    ch->ppe = ch->max_ppe;
    ch->isp = ch->max_isp;

    send_to_player(sess, "You awaken in the Recovery Chamber. Lives remaining: %d\n", ch->lives_remaining);
}
