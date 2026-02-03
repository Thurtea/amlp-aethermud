#ifndef SESSION_H
#define SESSION_H

/* session.h - Session API for efuns to access current player object */

/* Forward declaration */
typedef struct PlayerSession PlayerSession;

/* Return the current player object for the executing VM context, or NULL. */
void *get_current_player_object(void);

/* Set the current session for the VM context (opaque pointer). */
void set_current_session(void *session);

/* Find the session for a given player object */
PlayerSession* find_session_for_player(void *player_obj);

/* Send a message to a player's session */
void send_message_to_player_session(void *player_obj, const char *message);

#endif /* SESSION_H */
