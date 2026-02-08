/* race_loader.h - Load and apply race / O.C.C. data to characters */

#ifndef RACE_LOADER_H
#define RACE_LOADER_H

#include "session_internal.h"

/* ---- Parsed mapping for LPC ([ "key": val, ... ]) ---- */
#define PARSED_MAP_MAX 16

typedef struct {
    char keys[PARSED_MAP_MAX][32];
    int  vals[PARSED_MAP_MAX];
    int  count;
} ParsedMapping;

/* XP table (Palladium-inspired, levels 1-15) */
#define MAX_LEVEL 15
extern const int XP_TABLE[MAX_LEVEL + 1];

/* Apply race and O.C.C. effects to the session's character. */
void apply_race_and_occ(PlayerSession *sess);

/* Loaders that parse LPC definitions from disk and apply to Character */
void load_race_data(const char *race_name, Character *ch);
void load_occ_data(const char *occ_name, Character *ch);

/* LPC extraction helpers */
char *lpc_extract_string(const char *buf, const char *snake, const char *pascal);
int lpc_extract_int(const char *buf, const char *snake, const char *pascal, int default_val);

/* Parse LPC mapping: set_func_name(([ "key": val, ... ])) into ParsedMapping */
int lpc_extract_mapping_ints(const char *buf, const char *func_name, ParsedMapping *out);

/* Parse two-int call: set_func(min, max) */
int lpc_extract_two_ints(const char *buf, const char *func_name, int *a, int *b);

/* Level-up system: check XP and apply per-level gains */
void check_and_apply_level_up(PlayerSession *sess);

#endif /* RACE_LOADER_H */
