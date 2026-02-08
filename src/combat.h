#ifndef COMBAT_H
#define COMBAT_H

#include <stdbool.h>
#include "chargen.h"
#include "session_internal.h"

// ============================================================================
// COMBAT SYSTEM - Real-Time Heartbeat-Driven Combat
// ============================================================================

#define MELEE_ROUND_TICKS  8    /* 8 ticks per melee round (16 seconds at 2s/tick) */
#define COMBAT_TICK_SECS   2    /* Heartbeat interval in seconds */

// Combat state machine
typedef enum {
    COMBAT_NONE = 0,        // Not in combat
    COMBAT_ACTIVE,          // Real-time combat in progress
    COMBAT_ENDED            // Combat finished
} CombatState;

// Combat participant (player or NPC)
typedef struct CombatParticipant {
    char *name;                           // Name of participant
    bool is_player;                       // True if player, false if NPC
    PlayerSession *session;               // Player session (NULL for NPCs)
    Character *character;                 // Character data

    // Real-time combat tracking
    int attacks_used_this_round;          // Track attacks used in current melee round
    int parries_used_this_round;          // Track parries used in current melee round

    // Target tracking
    struct CombatParticipant *target;     // Current attack target

    // Linked list within a CombatRound
    struct CombatParticipant *next;
} CombatParticipant;

// Combat round manager
typedef struct CombatRound {
    CombatState state;                    // Current combat state
    CombatParticipant *participants;      // Linked list of combatants
    int round_number;                     // Melee round counter
    int tick_in_round;                    // 0 to MELEE_ROUND_TICKS-1 within current melee round
    int num_participants;                 // Number of active combatants
    struct CombatRound *next;            // Linked list of concurrent combats
} CombatRound;

// Damage result
typedef struct {
    int damage;                           // Total damage dealt
    bool is_critical;                     // Critical hit flag
    bool is_kill;                         // Target killed flag
    bool is_mega_damage;                  // MDC weapon flag
    int sdc_damage;                       // Damage to SDC
    int hp_damage;                        // Damage to HP
} DamageResult;

// ============================================================================
// COMBAT SYSTEM API
// ============================================================================

// Initialization
void combat_init(void);

// Real-time combat heartbeat (called every 2 seconds from main loop)
void combat_tick(void);

// Regen tick for resting players (called every 2 seconds from main loop)
void combat_regen_tick(void);

// Engage/disengage combat
CombatRound* combat_engage(PlayerSession *attacker, PlayerSession *defender);
void combat_disengage(PlayerSession *session);

// Legacy API (still used by slay, peace, etc.)
void combat_end(CombatRound *combat);
CombatRound* combat_get_active(PlayerSession *sess);

// Participant management
CombatParticipant* combat_create_participant(PlayerSession *sess, Character *ch);
void combat_free_participant(CombatParticipant *p);
void combat_add_participant(CombatRound *combat, CombatParticipant *p);
void combat_remove_participant(CombatRound *combat, CombatParticipant *p);
CombatParticipant* combat_find_participant(CombatRound *combat, const char *name);

// Attack system
DamageResult combat_attack_melee(CombatParticipant *attacker, CombatParticipant *defender);
DamageResult combat_attack_ranged(CombatParticipant *attacker, CombatParticipant *defender);
int combat_calculate_strike_bonus(CombatParticipant *p, bool is_melee);
int combat_calculate_damage(int weapon_dice, int weapon_sides, int ps_bonus);

// Defense system
bool combat_defend_parry(CombatParticipant *defender, int attack_roll);
bool combat_defend_dodge(CombatParticipant *defender, int attack_roll);
int combat_calculate_parry_bonus(CombatParticipant *p);
int combat_calculate_dodge_bonus(CombatParticipant *p);

// Damage application
void combat_apply_damage(CombatParticipant *target, DamageResult *dmg);
bool combat_check_death(CombatParticipant *p);
void combat_award_experience(CombatParticipant *winner, CombatParticipant *loser);

// Combat messages
void combat_broadcast(CombatRound *combat, const char *message);
void combat_send_to_participant(CombatParticipant *p, const char *message);

// Utility
int combat_roll_dice(int num_dice, int sides);
int combat_d20(void);

#endif // COMBAT_H
