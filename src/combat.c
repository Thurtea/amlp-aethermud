#include "combat.h"
#include "npc.h"
#include "room.h"
#include "skills.h"
#include "item.h"
#include "session_internal.h"
#include "race_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <strings.h>

// External function declarations
extern void send_to_player(PlayerSession *sess, const char *format, ...);
extern void send_prompt(PlayerSession *session);

// Forward declarations
extern void cmd_move(PlayerSession *sess, const char *direction);
extern PlayerSession *sessions[];

// ============================================================================
// GLOBAL COMBAT STATE
// ============================================================================

static CombatRound *active_combats = NULL;  // Linked list of active combats
static bool combat_initialized = false;

// ============================================================================
// INITIALIZATION
// ============================================================================

void combat_init(void) {
    if (combat_initialized) {
        return;
    }

    srand(time(NULL));
    active_combats = NULL;
    combat_initialized = true;

    printf("[COMBAT] Real-time combat system initialized (tick=%ds, round=%d ticks)\n",
           COMBAT_TICK_SECS, MELEE_ROUND_TICKS);
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

int combat_roll_dice(int num_dice, int sides) {
    int total = 0;
    for (int i = 0; i < num_dice; i++) {
        total += (rand() % sides) + 1;
    }
    return total;
}

int combat_d20(void) {
    return combat_roll_dice(1, 20);
}

// ============================================================================
// ATTACK DISTRIBUTION - evenly space attacks across the melee round
// ============================================================================

static int combat_should_attack_this_tick(int attacks_per_round, int tick_in_round) {
    if (attacks_per_round <= 0) return 0;
    if (attacks_per_round >= MELEE_ROUND_TICKS) return 1; /* Every tick */
    /* Evenly distribute: attack when (tick * attacks) / ticks crosses integer boundary */
    int prev = (tick_in_round * attacks_per_round) / MELEE_ROUND_TICKS;
    int curr = ((tick_in_round + 1) * attacks_per_round) / MELEE_ROUND_TICKS;
    return curr > prev;
}

// ============================================================================
// PARTICIPANT MANAGEMENT
// ============================================================================

CombatParticipant* combat_create_participant(PlayerSession *sess, Character *ch) {
    if (!ch) return NULL;

    CombatParticipant *p = malloc(sizeof(CombatParticipant));
    if (!p) return NULL;

    p->name = strdup(sess && sess->username ? sess->username : "Unknown");
    p->is_player = (sess != NULL);
    p->session = sess;
    p->character = ch;

    p->attacks_used_this_round = 0;
    p->parries_used_this_round = 0;

    p->target = NULL;
    p->next = NULL;

    return p;
}

void combat_free_participant(CombatParticipant *p) {
    if (!p) return;

    if (p->name) {
        free(p->name);
    }
    free(p);
}

void combat_add_participant(CombatRound *combat, CombatParticipant *p) {
    if (!combat || !p) return;

    p->next = combat->participants;
    combat->participants = p;
    combat->num_participants++;
}

void combat_remove_participant(CombatRound *combat, CombatParticipant *p) {
    if (!combat || !p) return;

    // Remove from linked list
    if (combat->participants == p) {
        combat->participants = p->next;
    } else {
        CombatParticipant *curr = combat->participants;
        while (curr && curr->next != p) {
            curr = curr->next;
        }
        if (curr) {
            curr->next = p->next;
        }
    }

    combat->num_participants--;

    // Clear target references pointing to removed participant
    for (CombatParticipant *c = combat->participants; c; c = c->next) {
        if (c->target == p) {
            c->target = NULL;
        }
    }
}

CombatParticipant* combat_find_participant(CombatRound *combat, const char *name) {
    if (!combat || !name) return NULL;

    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (strcasecmp(p->name, name) == 0) {
            return p;
        }
    }
    return NULL;
}

// ============================================================================
// COMBAT ENGAGE / DISENGAGE
// ============================================================================

CombatRound* combat_engage(PlayerSession *attacker, PlayerSession *defender) {
    if (!attacker || !defender) return NULL;

    // Check if attacker is already in a combat
    CombatRound *existing = combat_get_active(attacker);
    if (existing) {
        // Just retarget
        CombatParticipant *ap = combat_find_participant(existing, attacker->username);
        CombatParticipant *dp = combat_find_participant(existing, defender->username);
        if (ap && dp) {
            ap->target = dp;
            send_to_player(attacker, "You switch your attack to %s.\n", defender->username);
            return existing;
        }
        // Defender not in same combat - add them
        if (ap && !dp) {
            CombatParticipant *new_p = combat_create_participant(defender, &defender->character);
            if (new_p) {
                combat_add_participant(existing, new_p);
                new_p->target = ap; // Defender auto-targets attacker
                ap->target = new_p;
                defender->in_combat = 1;
                defender->combat_target = attacker;
                send_to_player(defender, "\n%s attacks you!\n", attacker->username);
            }
            return existing;
        }
    }

    // Check if defender is already in a combat - join it
    existing = combat_get_active(defender);
    if (existing) {
        CombatParticipant *dp = combat_find_participant(existing, defender->username);
        CombatParticipant *new_p = combat_create_participant(attacker, &attacker->character);
        if (new_p && dp) {
            combat_add_participant(existing, new_p);
            new_p->target = dp;
            attacker->in_combat = 1;
            attacker->combat_target = defender;
            send_to_player(defender, "\n%s joins the fight against you!\n", attacker->username);
        }
        return existing;
    }

    // Create new combat
    CombatRound *combat = malloc(sizeof(CombatRound));
    if (!combat) return NULL;

    combat->state = COMBAT_ACTIVE;
    combat->participants = NULL;
    combat->round_number = 1;
    combat->tick_in_round = 0;
    combat->num_participants = 0;
    combat->next = NULL;

    CombatParticipant *ap = combat_create_participant(attacker, &attacker->character);
    CombatParticipant *dp = combat_create_participant(defender, &defender->character);

    if (!ap || !dp) {
        if (ap) combat_free_participant(ap);
        if (dp) combat_free_participant(dp);
        free(combat);
        return NULL;
    }

    combat_add_participant(combat, ap);
    combat_add_participant(combat, dp);

    // Set targets
    ap->target = dp;
    dp->target = ap;

    // Update session state
    attacker->in_combat = 1;
    attacker->combat_target = defender;
    attacker->is_resting = 0;  // Stand up if resting
    defender->in_combat = 1;
    defender->combat_target = attacker;
    defender->is_resting = 0;

    // Link to global list
    combat->next = active_combats;
    active_combats = combat;

    // Announce
    char msg[256];
    snprintf(msg, sizeof(msg), "\n>>> COMBAT! %s attacks %s! <<<\n",
             attacker->username, defender->username);
    combat_broadcast(combat, msg);

    // Show attacks per round info
    send_to_player(attacker, "  You have %d attack%s per melee round.\n",
                   attacker->character.attacks_per_round,
                   attacker->character.attacks_per_round == 1 ? "" : "s");

    return combat;
}

CombatRound* combat_engage_npc(PlayerSession *attacker, NPC *npc) {
    if (!attacker || !npc) return NULL;

    /* Check if attacker already in combat */
    CombatRound *existing = combat_get_active(attacker);
    if (existing) {
        send_to_player(attacker, "You are already in combat!\n");
        return existing;
    }

    /* Create new combat */
    CombatRound *combat = malloc(sizeof(CombatRound));
    if (!combat) return NULL;

    combat->state = COMBAT_ACTIVE;
    combat->participants = NULL;
    combat->round_number = 1;
    combat->tick_in_round = 0;
    combat->num_participants = 0;
    combat->next = NULL;

    CombatParticipant *ap = combat_create_participant(attacker, &attacker->character);
    CombatParticipant *dp = malloc(sizeof(CombatParticipant));
    if (!ap || !dp) {
        if (ap) combat_free_participant(ap);
        free(dp);
        free(combat);
        return NULL;
    }

    /* Initialize NPC participant */
    dp->name = strdup(npc->name);
    dp->is_player = false;
    dp->session = NULL;
    dp->character = &npc->character;
    dp->attacks_used_this_round = 0;
    dp->parries_used_this_round = 0;
    dp->target = NULL;
    dp->next = NULL;

    combat_add_participant(combat, ap);
    combat_add_participant(combat, dp);

    ap->target = dp;
    dp->target = ap;

    /* Update state */
    attacker->in_combat = 1;
    attacker->combat_target = NULL;
    attacker->is_resting = 0;
    npc->in_combat = 1;
    npc->combat_target_player = attacker;

    /* Link to global list */
    combat->next = active_combats;
    active_combats = combat;

    /* Announce */
    char display[64];
    snprintf(display, sizeof(display), "%s", npc->name);
    display[0] = (char)toupper((unsigned char)display[0]);

    char msg[256];
    snprintf(msg, sizeof(msg), "\n>>> COMBAT! %s attacks %s! <<<\n",
             attacker->username, display);
    send_to_player(attacker, "%s", msg);

    /* Broadcast to room */
    if (npc->current_room) {
        room_broadcast(npc->current_room, msg, attacker);
    }

    send_to_player(attacker, "  You have %d attack%s per melee round.\n",
                   attacker->character.attacks_per_round,
                   attacker->character.attacks_per_round == 1 ? "" : "s");

    return combat;
}

CombatRound* combat_get_active_by_participant(CombatParticipant *target) {
    if (!target) return NULL;
    for (CombatRound *c = active_combats; c; c = c->next) {
        for (CombatParticipant *p = c->participants; p; p = p->next) {
            if (p == target) return c;
        }
    }
    return NULL;
}

void combat_disengage(PlayerSession *session) {
    if (!session) return;

    CombatRound *combat = combat_get_active(session);
    if (!combat) {
        session->in_combat = 0;
        session->combat_target = NULL;
        return;
    }

    CombatParticipant *p = combat_find_participant(combat, session->username);
    if (p) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s disengages from combat.\n", p->name);
        combat_broadcast(combat, msg);

        combat_remove_participant(combat, p);
        combat_free_participant(p);
    }

    session->in_combat = 0;
    session->combat_target = NULL;

    // End combat if fewer than 2 participants remain
    if (combat->num_participants < 2) {
        // Clear remaining participants' combat state
        for (CombatParticipant *r = combat->participants; r; r = r->next) {
            if (r->session) {
                r->session->in_combat = 0;
                r->session->combat_target = NULL;
            }
        }
        combat_end(combat);
    }
}

// ============================================================================
// COMBAT ROUND MANAGEMENT
// ============================================================================

void combat_end(CombatRound *combat) {
    if (!combat) return;

    combat_broadcast(combat, "\n>>> COMBAT ENDED <<<\n\n");

    // Clear session combat state for all participants
    CombatParticipant *p = combat->participants;
    while (p) {
        CombatParticipant *next = p->next;
        if (p->session) {
            p->session->in_combat = 0;
            p->session->combat_target = NULL;
        }
        combat_free_participant(p);
        p = next;
    }
    combat->participants = NULL;

    // Remove from active combats linked list
    if (active_combats == combat) {
        active_combats = combat->next;
    } else {
        CombatRound *prev = active_combats;
        while (prev && prev->next != combat) {
            prev = prev->next;
        }
        if (prev) {
            prev->next = combat->next;
        }
    }

    combat->state = COMBAT_ENDED;
    free(combat);
}

CombatRound* combat_get_active(PlayerSession *sess) {
    if (!sess) return NULL;

    for (CombatRound *c = active_combats; c; c = c->next) {
        for (CombatParticipant *p = c->participants; p; p = p->next) {
            if (p->session == sess) {
                return c;
            }
        }
    }

    return NULL;
}

// ============================================================================
// REAL-TIME COMBAT TICK
// ============================================================================

/* Auto-defense: attempt parry then dodge against an incoming attack */
static int combat_auto_defend(CombatParticipant *defender, int attack_total) {
    if (!defender || !defender->character) return 0;

    // Auto-parry check
    if (defender->character->auto_parry_enabled &&
        (defender->character->racial_auto_parry || defender->character->parries_per_round > 0) &&
        defender->parries_used_this_round < defender->character->parries_per_round) {

        if (combat_defend_parry(defender, attack_total)) {
            return 1; // Parried
        }
    }

    // Auto-dodge check
    if (defender->character->auto_dodge_enabled &&
        defender->character->racial_auto_dodge) {
        if (combat_defend_dodge(defender, attack_total)) {
            return 1; // Dodged
        }
    }

    return 0; // Not defended
}

/* Auto-attack: fire one melee attack from attacker to target */
static void combat_auto_attack(CombatParticipant *attacker, CombatParticipant *defender) {
    if (!attacker || !defender) return;

    DamageResult result = combat_attack_melee(attacker, defender);
    attacker->attacks_used_this_round++;

    if (result.is_kill) {
        combat_award_experience(attacker, defender);

        // Get the combat — try player session first, fall back to participant search
        CombatRound *combat = NULL;
        if (attacker->session) {
            combat = combat_get_active(attacker->session);
        }
        if (!combat) {
            combat = combat_get_active_by_participant(attacker);
        }

        // Handle NPC defender death
        if (!defender->is_player) {
            NPC *dead_npc = npc_find_by_character(defender->character);
            if (dead_npc) {
                npc_handle_death(dead_npc, attacker->session);
            }
        }

        if (combat) {
            combat_remove_participant(combat, defender);

            // Clear dead player's combat state
            if (defender->session) {
                defender->session->in_combat = 0;
                defender->session->combat_target = NULL;
            }
            combat_free_participant(defender);

            // End combat if only one left
            if (combat->num_participants <= 1) {
                // Clear remaining participants' NPC state
                for (CombatParticipant *r = combat->participants; r; r = r->next) {
                    if (!r->is_player) {
                        NPC *n = npc_find_by_character(r->character);
                        if (n) {
                            n->in_combat = 0;
                            n->combat_target_player = NULL;
                        }
                    }
                }
                combat_end(combat);
                return;
            }

            // Find a new target for attacker if target died
            if (attacker->target == NULL) {
                for (CombatParticipant *c = combat->participants; c; c = c->next) {
                    if (c != attacker) {
                        attacker->target = c;
                        break;
                    }
                }
            }
        }
    }

    // Wimpy check: auto-flee if HP below threshold
    if (defender->session && defender->character && defender->character->wimpy_threshold > 0) {
        int max_hp = defender->character->max_hp;
        if (max_hp > 0) {
            int threshold = (max_hp * defender->character->wimpy_threshold) / 100;
            if (defender->character->hp <= threshold && defender->character->hp > 0) {
                send_to_player(defender->session,
                    "You are badly hurt! WIMPY triggers - you try to flee!\n");
                combat_disengage(defender->session);
                // Attempt to move in a random direction
                const char *dirs[] = {"north", "south", "east", "west"};
                cmd_move(defender->session, dirs[rand() % 4]);
            }
        }
    }
}

/* Process one tick for a single combat */
static void combat_process_tick(CombatRound *combat) {
    if (!combat || combat->state != COMBAT_ACTIVE) return;

    int tick = combat->tick_in_round;

    // Process each participant's attacks for this tick
    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (!p->character || !p->target) continue;
        if (p->character->hp <= 0) continue;

        int apr = p->character->attacks_per_round;
        if (combat_should_attack_this_tick(apr, tick)) {
            combat_auto_attack(p, p->target);
            // Combat may have ended due to death
            if (combat->state != COMBAT_ACTIVE) return;
        }
    }

    // Advance tick
    combat->tick_in_round++;
    if (combat->tick_in_round >= MELEE_ROUND_TICKS) {
        // New melee round
        combat->tick_in_round = 0;
        combat->round_number++;

        // Reset per-round counters
        for (CombatParticipant *p = combat->participants; p; p = p->next) {
            p->attacks_used_this_round = 0;
            p->parries_used_this_round = 0;
        }
    }
}

/* Main heartbeat: called every 2 seconds from the main loop */
void combat_tick(void) {
    CombatRound *combat = active_combats;
    while (combat) {
        CombatRound *next = combat->next;  // Save next in case combat ends
        if (combat->state == COMBAT_ACTIVE) {
            combat_process_tick(combat);
        }
        combat = next;
    }
}

/* Regen tick: restore HP/SDC for resting players */
void combat_regen_tick(void) {
    for (int i = 0; i < 100; i++) {  /* MAX_CLIENTS */
        PlayerSession *sess = sessions[i];
        if (!sess || sess->state != STATE_PLAYING) continue;
        if (!sess->is_resting) continue;
        if (sess->in_combat) continue;

        Character *ch = &sess->character;
        int regen = 0;

        // Resting regen: 2 HP + 2 SDC per tick (4 seconds real-time)
        if (ch->hp < ch->max_hp) {
            int gain = 2;
            if (ch->hp + gain > ch->max_hp) gain = ch->max_hp - ch->hp;
            ch->hp += gain;
            regen += gain;
        }
        if (ch->sdc < ch->max_sdc) {
            int gain = 2;
            if (ch->sdc + gain > ch->max_sdc) gain = ch->max_sdc - ch->sdc;
            ch->sdc += gain;
            regen += gain;
        }

        if (regen > 0) {
            send_to_player(sess, "You rest and recover. HP: %d/%d SDC: %d/%d\n",
                           ch->hp, ch->max_hp, ch->sdc, ch->max_sdc);
        }

        // Check if fully healed
        if (ch->hp >= ch->max_hp && ch->sdc >= ch->max_sdc) {
            send_to_player(sess, "You are fully rested.\n");
            sess->is_resting = 0;
        }
    }
}

// ============================================================================
// ATTACK SYSTEM
// ============================================================================

int combat_calculate_strike_bonus(CombatParticipant *p, bool is_melee) {
    if (!p || !p->character) return 0;

    int bonus = 0;

    // Hand to Hand bonus
    for (int i = 0; i < p->character->num_skills; i++) {
        if (p->character->skills[i].skill_id == 0) {
            bonus += p->character->skills[i].percentage / 20;
            break;
        }
    }

    // Weapon Proficiency bonus
    if (!is_melee) {
        for (int i = 0; i < p->character->num_skills; i++) {
            if (p->character->skills[i].skill_id == 8 ||
                p->character->skills[i].skill_id == 9) {
                bonus += p->character->skills[i].percentage / 20;
                break;
            }
        }
    } else {
        for (int i = 0; i < p->character->num_skills; i++) {
            if (p->character->skills[i].skill_id == 7) {
                bonus += p->character->skills[i].percentage / 20;
                break;
            }
        }
    }

    // PP bonus for strike
    if (p->character->stats.pp > 10) {
        bonus += (p->character->stats.pp - 10) / 5;
    }

    return bonus;
}

int combat_calculate_damage(int weapon_dice, int weapon_sides, int ps_bonus) {
    int damage = combat_roll_dice(weapon_dice, weapon_sides);
    damage += ps_bonus;
    return (damage > 0) ? damage : 1;
}

DamageResult combat_attack_melee(CombatParticipant *attacker, CombatParticipant *defender) {
    DamageResult result = {0, false, false, false, 0, 0};

    if (!attacker || !defender) return result;

    // Roll to hit (1d20 + strike bonus)
    int attack_roll = combat_d20();
    int strike_bonus = combat_calculate_strike_bonus(attacker, true);
    int total_strike = attack_roll + strike_bonus;

    // Critical hit on natural 20
    if (attack_roll == 20) {
        result.is_critical = true;
    }

    // Fumble on natural 1
    if (attack_roll == 1) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s fumbles!\n", attacker->name);
        combat_send_to_participant(attacker, msg);
        combat_send_to_participant(defender, msg);
        return result;
    }

    int target_number = 8;

    // Auto-defense check (replaces manual parry/dodge)
    if (combat_auto_defend(defender, total_strike)) {
        return result;  // Defended
    }

    // Miss check
    if (total_strike < target_number) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s swings at %s but misses! (%d+%d=%d vs %d)\n",
                 attacker->name, defender->name, attack_roll, strike_bonus, total_strike, target_number);
        combat_send_to_participant(attacker, msg);
        combat_send_to_participant(defender, msg);
        return result;
    }

    // Calculate damage
    int damage_dice = 2;
    int damage_sides = 6;
    int weapon_bonus = 0;
    bool is_mega_damage = false;

    if (attacker->character && attacker->character->equipment.weapon_primary) {
        Item *weapon = attacker->character->equipment.weapon_primary;
        if (weapon->type == ITEM_WEAPON_MELEE) {
            damage_dice = weapon->stats.damage_dice;
            damage_sides = weapon->stats.damage_sides;
            weapon_bonus = weapon->stats.damage_bonus;
            is_mega_damage = weapon->stats.is_mega_damage;
        }
    } else if (!attacker->is_player) {
        /* NPC: use template weapon data */
        NPC *npc = npc_find_by_character(attacker->character);
        if (npc && npc->template_id >= 0 && npc->template_id < NPC_TEMPLATE_COUNT) {
            const NpcTemplate *t = &NPC_TEMPLATES[npc->template_id];
            damage_dice = t->weapon_dice;
            damage_sides = t->weapon_sides;
            /* MDC creatures deal mega-damage */
            is_mega_damage = (t->health_type == MDC_ONLY);
        }
    }

    // PS bonus for melee
    int ps_bonus = 0;
    if (attacker->character && attacker->character->stats.ps > 15) {
        ps_bonus = (attacker->character->stats.ps - 15) / 5 + 1;
    }

    result.damage = combat_calculate_damage(damage_dice, damage_sides, ps_bonus + weapon_bonus);
    result.is_mega_damage = is_mega_damage;

    if (result.is_critical) {
        result.damage *= 2;
    }

    combat_apply_damage(defender, &result);

    /* If kill occurred, trigger death handler for player victims */
    if (result.is_kill && defender->session) {
        handle_player_death(defender->session, attacker->session);
    }

    /* Descriptive combat messages (no numeric damage shown) */
    {
        int max_pool = defender->character->max_hp + defender->character->max_sdc + (defender->character->max_mdc * 100);
        if (max_pool <= 0) max_pool = 1;
        int pct = (result.damage * 100) / max_pool;
        const char *severity = "mildly";
        if (pct <= 10) severity = "mildly";
        else if (pct <= 30) severity = "lightly";
        else if (pct <= 60) severity = "severely";
        else severity = result.is_critical ? "critically" : "viciously";

        const char *verb = "hits";
        /* Choose verb by attacker's race or weapon */
        if (attacker->character && attacker->character->race && strcasestr(attacker->character->race, "Dragon")) {
            verb = "claws";
        } else {
            /* If primary weapon is energy/ranged, use ranged verbs */
            if (attacker->character && attacker->character->equipment.weapon_primary) {
                Item *w = attacker->character->equipment.weapon_primary;
                if (w->type == ITEM_WEAPON_RANGED) {
                    verb = "shoots";
                } else {
                    verb = "strikes";
                }
            } else {
                verb = "strikes";
            }
        }

        char bufmsg[256];
        snprintf(bufmsg, sizeof(bufmsg), "%s %s %s %s!\n",
                 attacker->name, verb, defender->name, severity);
        combat_send_to_participant(attacker, bufmsg);
        combat_send_to_participant(defender, bufmsg);
    }

    return result;
}

DamageResult combat_attack_ranged(CombatParticipant *attacker, CombatParticipant *defender) {
    DamageResult result = {0, false, false, false, 0, 0};

    if (!attacker || !defender) return result;

    int attack_roll = combat_d20();
    int strike_bonus = combat_calculate_strike_bonus(attacker, false);
    int total_strike = attack_roll + strike_bonus;

    if (attack_roll == 20) result.is_critical = true;

    if (attack_roll == 1) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s fumbles the shot!\n", attacker->name);
        combat_send_to_participant(attacker, msg);
        combat_send_to_participant(defender, msg);
        return result;
    }

    int target_number = 8;

    // Ranged: dodge only (auto-dodge)
    if (defender->character && defender->character->auto_dodge_enabled &&
        defender->character->racial_auto_dodge) {
        if (combat_defend_dodge(defender, total_strike)) {
            return result;
        }
    }

    if (total_strike < target_number) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s shoots at %s but misses! (%d+%d=%d vs %d)\n",
                 attacker->name, defender->name, attack_roll, strike_bonus, total_strike, target_number);
        combat_send_to_participant(attacker, msg);
        combat_send_to_participant(defender, msg);
        return result;
    }

    int damage_dice = 2;
    int damage_sides = 6;
    int weapon_bonus = 0;
    bool is_mega_damage = false;

    if (attacker->character && attacker->character->equipment.weapon_primary) {
        Item *weapon = attacker->character->equipment.weapon_primary;
        if (weapon->type == ITEM_WEAPON_RANGED) {
            damage_dice = weapon->stats.damage_dice;
            damage_sides = weapon->stats.damage_sides;
            weapon_bonus = weapon->stats.damage_bonus;
            is_mega_damage = weapon->stats.is_mega_damage;
        }
    }

    result.damage = combat_calculate_damage(damage_dice, damage_sides, weapon_bonus);
    result.is_mega_damage = is_mega_damage;

    if (result.is_critical) result.damage *= 2;

    combat_apply_damage(defender, &result);

    /* If kill occurred, trigger death handler for player victims */
    if (result.is_kill && defender->session) {
        handle_player_death(defender->session, attacker->session);
    }

    /* Descriptive ranged messages */
    {
        int max_pool = defender->character->max_hp + defender->character->max_sdc + (defender->character->max_mdc * 100);
        if (max_pool <= 0) max_pool = 1;
        int pct = (result.damage * 100) / max_pool;
        const char *severity = "mildly";
        if (pct <= 10) severity = "mildly";
        else if (pct <= 30) severity = "lightly";
        else if (pct <= 60) severity = "severely";
        else severity = result.is_critical ? "critically" : "devastates";

        const char *verb = "grazes";
        if (attacker->character && attacker->character->equipment.weapon_primary) {
            Item *w = attacker->character->equipment.weapon_primary;
            if (w->weapon_type == WEAPON_ENERGY) verb = "grazes";
            else verb = "hits";
        }

        char bufmsg[256];
        snprintf(bufmsg, sizeof(bufmsg), "%s %s %s %s!\n",
                 attacker->name, verb, defender->name, severity);
        combat_send_to_participant(attacker, bufmsg);
        combat_send_to_participant(defender, bufmsg);
    }

    return result;
}

// ============================================================================
// DEFENSE SYSTEM
// ============================================================================

int combat_calculate_parry_bonus(CombatParticipant *p) {
    if (!p || !p->character) return 0;

    int bonus = 0;

    for (int i = 0; i < p->character->num_skills; i++) {
        if (p->character->skills[i].skill_id == 0) {
            bonus += p->character->skills[i].percentage / 20;
            break;
        }
    }

    if (p->character->stats.pp > 10) {
        bonus += (p->character->stats.pp - 10) / 5;
    }

    return bonus;
}

int combat_calculate_dodge_bonus(CombatParticipant *p) {
    if (!p || !p->character) return 0;

    int bonus = 0;

    for (int i = 0; i < p->character->num_skills; i++) {
        if (p->character->skills[i].skill_id == 1) {
            bonus += p->character->skills[i].percentage / 20;
            break;
        }
    }

    for (int i = 0; i < p->character->num_skills; i++) {
        if (p->character->skills[i].skill_id == 0) {
            bonus += p->character->skills[i].percentage / 20;
            break;
        }
    }

    if (p->character->stats.pp > 10) {
        bonus += (p->character->stats.pp - 10) / 5;
    }

    return bonus;
}

bool combat_defend_parry(CombatParticipant *defender, int attack_roll) {
    if (!defender) return false;

    int parry_roll = combat_d20();
    int parry_bonus = combat_calculate_parry_bonus(defender);
    int total_parry = parry_roll + parry_bonus;

    defender->parries_used_this_round++;

    if (total_parry >= attack_roll) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s parries! (%d+%d=%d vs %d)\n",
                 defender->name, parry_roll, parry_bonus, total_parry, attack_roll);
        combat_send_to_participant(defender, msg);
        return true;
    }

    return false;
}

bool combat_defend_dodge(CombatParticipant *defender, int attack_roll) {
    if (!defender) return false;

    int dodge_roll = combat_d20();
    int dodge_bonus = combat_calculate_dodge_bonus(defender);
    int total_dodge = dodge_roll + dodge_bonus;

    if (total_dodge >= attack_roll) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s dodges! (%d+%d=%d vs %d)\n",
                 defender->name, dodge_roll, dodge_bonus, total_dodge, attack_roll);
        combat_send_to_participant(defender, msg);
        return true;
    }

    return false;
}

// ============================================================================
// DAMAGE & DEATH
// ============================================================================

void combat_apply_damage(CombatParticipant *target, DamageResult *dmg) {
    if (!target || !dmg || !target->character) return;

    /* Godmode check */
    if (target->session && target->session->is_godmode) {
        dmg->damage = 0;
        char msg[128];
        snprintf(msg, sizeof(msg), "%s is in god mode and takes no damage!\n",
                 target->name);
        combat_send_to_participant(target, msg);
        return;
    }

    int damage_remaining = dmg->damage;

    /* MDC-only creatures: apply damage directly to MDC pool */
    if (target->character->health_type == MDC_ONLY) {
        /* MDC weapons do full damage; SDC weapons do 1/100 */
        if (!dmg->is_mega_damage) {
            damage_remaining = damage_remaining / 100;
            if (damage_remaining < 1) damage_remaining = 1;
        }
        if (damage_remaining >= target->character->mdc) {
            target->character->mdc = 0;
        } else {
            target->character->mdc -= damage_remaining;
        }

        if (combat_check_death(target)) {
            dmg->is_kill = true;
        }
        return;
    }

    // Armor absorption (SDC/HP creatures only)
    Item *armor = target->character->equipment.armor;
    if (armor && armor->current_durability > 0) {
        if (damage_remaining >= armor->current_durability) {
            int armor_absorbed = armor->current_durability;
            armor->current_durability = 0;
            damage_remaining -= armor_absorbed;

            char msg[256];
            snprintf(msg, sizeof(msg), "%s's armor is destroyed!\n", target->name);
            combat_send_to_participant(target, msg);
        } else {
            armor->current_durability -= damage_remaining;
            damage_remaining = 0;
        }
    }

    // Apply to SDC first
    if (damage_remaining > 0 && target->character->sdc > 0) {
        if (damage_remaining >= target->character->sdc) {
            dmg->sdc_damage = target->character->sdc;
            damage_remaining -= target->character->sdc;
            target->character->sdc = 0;
        } else {
            dmg->sdc_damage = damage_remaining;
            target->character->sdc -= damage_remaining;
            damage_remaining = 0;
        }
    }

    // Then HP
    if (damage_remaining > 0) {
        if (damage_remaining >= target->character->hp) {
            dmg->hp_damage = target->character->hp;
            target->character->hp = 0;
        } else {
            dmg->hp_damage = damage_remaining;
            target->character->hp -= damage_remaining;
        }
    }

    if (combat_check_death(target)) {
        dmg->is_kill = true;
    }
}

bool combat_check_death(CombatParticipant *p) {
    if (!p || !p->character) return false;

    bool dead = false;

    /* MDC-only creatures die when MDC reaches 0 */
    if (p->character->health_type == MDC_ONLY) {
        dead = (p->character->mdc <= 0);
    } else {
        dead = (p->character->hp <= 0);
    }

    if (dead) {
        char msg[256];
        snprintf(msg, sizeof(msg),
                 "\n>>> %s has been defeated! <<<\n\n",
                 p->name);
        combat_send_to_participant(p, msg);

        /* Find combat via session or participant pointer */
        CombatRound *combat = NULL;
        if (p->session) {
            combat = combat_get_active(p->session);
        }
        if (!combat) {
            combat = combat_get_active_by_participant(p);
        }
        if (combat) {
            combat_broadcast(combat, msg);
        }

        return true;
    }

    return false;
}

void combat_award_experience(CombatParticipant *winner, CombatParticipant *loser) {
    if (!winner || !loser || !winner->character || !loser->character) return;

    int winner_level = winner->character->level;
    int loser_level  = loser->character->level;
    if (winner_level < 1) winner_level = 1;
    if (loser_level  < 1) loser_level  = 1;

    int xp = 50 * loser_level;

    int level_diff = loser_level - winner_level;
    if (level_diff > 0) {
        xp += 25 * level_diff;
    }

    if (level_diff < -2) {
        xp /= 2;
    }

    if (loser->character->health_type == MDC_ONLY) {
        xp = xp * 3 / 2;
    }

    if (xp < 25)   xp = 25;
    if (xp > 2000)  xp = 2000;

    winner->character->xp += xp;

    char msg[256];
    snprintf(msg, sizeof(msg), "You gained %d experience points! (Total: %d XP)\n",
             xp, winner->character->xp);
    combat_send_to_participant(winner, msg);

    if (winner->session) {
        check_and_apply_level_up(winner->session);
    }
}

// ============================================================================
// MESSAGING
// ============================================================================

void combat_broadcast(CombatRound *combat, const char *message) {
    if (!combat || !message) return;

    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        combat_send_to_participant(p, message);
    }
}

void combat_send_to_participant(CombatParticipant *p, const char *message) {
    if (!p || !message) return;

    if (p->is_player && p->session) {
        send_to_player(p->session, "%s", message);
    }
}
