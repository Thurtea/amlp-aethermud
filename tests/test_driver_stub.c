#include "session.h"
#include "session_internal.h"
#include <string.h>

/* Minimal test stub providing a sessions array and find_session_for_player
 * to satisfy link-time references from efuns and other test code. This is
 * only used for unit/test builds and should not be linked into the real
 * driver executable. */

PlayerSession *sessions[MAX_CLIENTS];

PlayerSession* find_session_for_player(void *player_obj) {
    if (!player_obj) return NULL;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i] && sessions[i]->player_object == player_obj) return sessions[i];
    }
    return NULL;
}
