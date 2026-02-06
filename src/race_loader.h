/* race_loader.h - Load and apply race / O.C.C. data to characters
 *
 * Minimal implementation: provides apply_race_and_occ() which inspects
 * the selected race and O.C.C. on the player's Character and applies
 * a small set of default bonuses. This is intentionally small and
 * data-driven hooks can be added later to parse external LPC files.
 */

#ifndef RACE_LOADER_H
#define RACE_LOADER_H

#include "session_internal.h"

/* Apply race and O.C.C. effects to the session's character.
 * Should be called after stats are rolled and/or when O.C.C. changes.
 */
void apply_race_and_occ(PlayerSession *sess);

/* Loaders that parse LPC definitions from disk and apply to Character */
void load_race_data(const char *race_name, Character *ch);
void load_occ_data(const char *occ_name, Character *ch);

/* LPC extraction helpers (string/int) - implemented here for parsing */
char *lpc_extract_string(const char *buf, const char *snake, const char *pascal);
int lpc_extract_int(const char *buf, const char *snake, const char *pascal, int default_val);

#endif /* RACE_LOADER_H */
