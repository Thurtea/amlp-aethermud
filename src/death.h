/* death.h - Death system: corpse creation, decay, and death handling */

#ifndef DEATH_H
#define DEATH_H

#include "session_internal.h"

/* Create a container corpse in the player's room and transfer inventory. */
void create_player_corpse(PlayerSession *sess);

/* Full death handler: lose a life, create corpse, teleport to recovery room. */
void handle_player_death(PlayerSession *sess, PlayerSession *killer,
                         const char *npc_killer_name);

/* Called every 2-second heartbeat: sweep expired corpses out of their rooms. */
void corpse_tick(void);

/* Reclaim player's corpse items into their inventory.
 * Returns 1 on success (items transferred), 0 if corpse already decayed. */
int corpse_reclaim_for_player(PlayerSession *sess);

#endif /* DEATH_H */
