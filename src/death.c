#include "chargen.h"
#include "session_internal.h"
#include "room.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* send_to_player is defined in the UI layer (used across modules) */
extern void send_to_player(PlayerSession *session, const char *format, ...);

static const char *scar_locations[] = {"left cheek", "right forearm", "chest", "back", "scalp"};
static const char *scar_descriptions[] = {"a jagged blade scar", "a burned patch of skin", "a long stitched wound", "a puckered scar", "a crescent-shaped mark"};

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
    /* TODO: hook into LPC corpse creation. For now, log and notify room. */
    Room *room = sess->current_room;
    if (room) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s collapses and their body falls lifeless. A corpse lies here.\n", sess->username);
        room_broadcast(room, msg, sess);
    }
    INFO_LOG("Corpse creation stub for %s", sess->username);
}

void handle_player_death(PlayerSession *sess, PlayerSession *killer,
                         const char *npc_killer_name) {
    if (!sess) return;
    Character *ch = &sess->character;

    if (ch->lives_remaining <= 0) {
        ch->permanently_dead = 1;
        /* Record what killed them for the login screen */
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
        send_to_player(sess,
            "\n*** Your life force is completely exhausted. ***\n"
            "Your soul dissolves into the void... This character is gone.\n\n");
        INFO_LOG("Permanent death: %s (killed by %s)", sess->username, ch->death_killer);
        sess->state = STATE_DISCONNECTING;
        return;
    }

    /* Lose a life and add a scar */
    ch->lives_remaining--;
    add_death_scar(ch);

    /* Create corpse (stub) */
    create_player_corpse(sess);

    /* Death messages */
    send_to_player(sess, "\r\n*** YOU HAVE BEEN SLAIN ***\r\n");
    send_to_player(sess, "Everything fades to black...\r\n\r\n");

    /* Teleport to recovery room */
    Room *death_room = room_get_by_path("/domains/death/recovery_room.lpc");
    if (!death_room) {
        INFO_LOG("Death recovery room not found for %s", sess->username);
        return;
    }

    /* Remove from current room */
    if (sess->current_room) {
        room_remove_player(sess->current_room, sess);
    }

    /* Move player into recovery room */
    room_add_player(death_room, sess);
    sess->current_room = death_room;

    /* Fully restore player pools */
    ch->hp = ch->max_hp;
    ch->sdc = ch->max_sdc;
    ch->ppe = ch->max_ppe;
    ch->isp = ch->max_isp;

    /* Call LPC describe function if available - best-effort by path */
    /* The LPC room has describe_death_recovery(object) to show healer text. */
    /* Because direct LPC calls are not available from C here, we rely on the LPC room's reset to spawn healers and the player to 'talk' to them. */

    /* Notify player with recovery info */
    send_to_player(sess, "You awaken in the Recovery Chamber. Lives remaining: %d\n", ch->lives_remaining);
}
 