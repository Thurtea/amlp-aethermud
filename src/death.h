#ifndef DEATH_H
#define DEATH_H

#include "session_internal.h"

void set_death_room(PlayerSession *sess, const char *path);
const char *get_death_room(PlayerSession *sess);

void add_death_scar(Character *ch);
void create_player_corpse(PlayerSession *sess);

void handle_player_death(PlayerSession *sess, PlayerSession *killer,
                         const char *npc_killer_name);

void corpse_tick(void);

int corpse_reclaim_for_player(PlayerSession *sess);

#endif
