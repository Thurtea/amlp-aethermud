#ifndef SESSION_H
#define SESSION_H

/* session.h - Session API for efuns to access current player object */

/* Forward declaration */
typedef struct PlayerSession PlayerSession;

/* Return the current player object for the executing VM context, or NULL. */
void *get_current_player_object(void);

/* Set the current session for the VM context (opaque pointer). */
void set_current_session(void *session);

/* Update the resting flag on the current session (0=standing, 1=resting). */
void set_current_session_resting(int val);

/* Find the session for a given player object */
PlayerSession* find_session_for_player(void *player_obj);

/* Death room path helpers */
void set_death_room(PlayerSession *sess, const char *path);
const char *get_death_room(PlayerSession *sess);

/* Send a message to a player's session */
void send_message_to_player_session(void *player_obj, const char *message);

#endif /* SESSION_H */
