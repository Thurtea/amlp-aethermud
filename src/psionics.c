#include "psionics.h"
#include "chargen.h"
#include "session_internal.h"
#include "room.h"
#include "npc.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Forward declaration */
void send_to_player(PlayerSession *session, const char *format, ...);

/* =============== PSIONIC POWERS DATABASE =============== */

PsionicPower PSION_POWERS[26] = {
    /* SUPER PSIONIC POWERS (0-5) */
    {
        .id = 0, .name = "Mind Block", .description = "Shield mind from psychic attacks",
        .isp_cost = 10, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_SUPER,
        .is_combat_usable = true, .is_passive = true, .keywords = "defense protect shield"
    },
    {
        .id = 1, .name = "Meditation", .description = "Restore 1d6 ISP per round of focus",
        .isp_cost = 5, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 1, .damage_sides = 6, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_SUPER,
        .is_combat_usable = false, .is_passive = false, .keywords = "recovery heal restore"
    },
    {
        .id = 2, .name = "Mental Acceleration", .description = "+3 initiative, +20% dodge for combat",
        .isp_cost = 2, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_SUPER,
        .is_combat_usable = true, .is_passive = false, .keywords = "speed combat initiative"
    },
    {
        .id = 3, .name = "Telemechanics", .description = "Operate devices remotely, up to 30 feet",
        .isp_cost = 3, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 30, .area_effect_feet = 0, .category = PSION_TELEPATHY,
        .is_combat_usable = false, .is_passive = false, .keywords = "tech device control"
    },
    {
        .id = 4, .name = "Telepathy", .description = "Mind-to-mind communication",
        .isp_cost = 1, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 300, .area_effect_feet = 0, .category = PSION_TELEPATHY,
        .is_combat_usable = false, .is_passive = false, .keywords = "communication mind link"
    },
    {
        .id = 5, .name = "Psychometry", .description = "Read history and impressions from objects",
        .isp_cost = 5, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_TELEPATHY,
        .is_combat_usable = false, .is_passive = false, .keywords = "sense knowledge history"
    },

    /* HEALING PSIONIC POWERS (6-11) */
    {
        .id = 6, .name = "Bio-Regeneration", .description = "Restore 2d6 HP + 1d4 per occurrence",
        .isp_cost = 6, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 2, .damage_sides = 6, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_HEALING,
        .is_combat_usable = true, .is_passive = false, .keywords = "heal restore health"
    },
    {
        .id = 7, .name = "Psychic Healing", .description = "Heal 1d6+2 HP in self or target",
        .isp_cost = 4, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 1, .damage_sides = 6, .is_mega_damage = false,
        .range_feet = 30, .area_effect_feet = 0, .category = PSION_HEALING,
        .is_combat_usable = true, .is_passive = false, .keywords = "heal restore recovery"
    },
    {
        .id = 8, .name = "Disease Immunity", .description = "Cure disease from self or target",
        .isp_cost = 5, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 30, .area_effect_feet = 0, .category = PSION_HEALING,
        .is_combat_usable = false, .is_passive = false, .keywords = "cure disease heal poison"
    },
    {
        .id = 9, .name = "Poison Immunity", .description = "Cure poison from self or target",
        .isp_cost = 4, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 30, .area_effect_feet = 0, .category = PSION_HEALING,
        .is_combat_usable = false, .is_passive = false, .keywords = "cure poison toxin heal"
    },
    {
        .id = 10, .name = "Mental Surge", .description = "+10 temporary SDC, lasts 3 rounds",
        .isp_cost = 3, .isp_cost_per_round = 0, .duration_rounds = 3,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_HEALING,
        .is_combat_usable = true, .is_passive = false, .keywords = "defense protect boost"
    },
    {
        .id = 11, .name = "Restoration", .description = "Restore lost limb (expensive, rare)",
        .isp_cost = 8, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_HEALING,
        .is_combat_usable = false, .is_passive = false, .keywords = "heal restore limb"
    },

    /* PHYSICAL PSIONIC POWERS (12-16) */
    {
        .id = 12, .name = "Telekinesis", .description = "Move objects up to 10 lbs/IQ level",
        .isp_cost = 2, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 50, .area_effect_feet = 0, .category = PSION_PHYSICAL,
        .is_combat_usable = true, .is_passive = false, .keywords = "move lift kinetic"
    },
    {
        .id = 13, .name = "Electrokinesis", .description = "Control electricity, 2d6 MD damage",
        .isp_cost = 3, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 2, .damage_sides = 6, .is_mega_damage = true,
        .range_feet = 100, .area_effect_feet = 0, .category = PSION_PHYSICAL,
        .is_combat_usable = true, .is_passive = false, .keywords = "damage lightning electric"
    },
    {
        .id = 14, .name = "Pyrokinesis", .description = "Control fire, 3d6 SD damage",
        .isp_cost = 3, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 3, .damage_sides = 6, .is_mega_damage = false,
        .range_feet = 80, .area_effect_feet = 0, .category = PSION_PHYSICAL,
        .is_combat_usable = true, .is_passive = false, .keywords = "damage fire burn"
    },
    {
        .id = 15, .name = "Hydrokinesis", .description = "Control water, shape and move it",
        .isp_cost = 2, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 60, .area_effect_feet = 0, .category = PSION_PHYSICAL,
        .is_combat_usable = true, .is_passive = false, .keywords = "water control move"
    },
    {
        .id = 16, .name = "Levitation", .description = "Fly at 10 mph, carry 200 lbs",
        .isp_cost = 1, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_PHYSICAL,
        .is_combat_usable = true, .is_passive = false, .keywords = "fly hover movement"
    },

    /* SENSITIVE PSIONIC POWERS (17-23) */
    {
        .id = 17, .name = "Sixth Sense", .description = "Sense danger, +2 parry/dodge",
        .isp_cost = 1, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_SENSITIVE,
        .is_combat_usable = true, .is_passive = true, .keywords = "sense danger awareness"
    },
    {
        .id = 18, .name = "Object Read", .description = "Know history and properties of item",
        .isp_cost = 4, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 5, .area_effect_feet = 0, .category = PSION_SENSITIVE,
        .is_combat_usable = false, .is_passive = false, .keywords = "sense knowledge object"
    },
    {
        .id = 19, .name = "Presence Sense", .description = "Sense living beings within 1 mile",
        .isp_cost = 2, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 5280, .area_effect_feet = 0, .category = PSION_SENSITIVE,
        .is_combat_usable = true, .is_passive = true, .keywords = "sense detect life"
    },
    {
        .id = 20, .name = "Combat Sense", .description = "See attacks coming, +1 dodge",
        .isp_cost = 1, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_SENSITIVE,
        .is_combat_usable = true, .is_passive = true, .keywords = "sense combat awareness"
    },
    {
        .id = 21, .name = "Clairvoyance", .description = "See remote location up to 1 mile away",
        .isp_cost = 4, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 5280, .area_effect_feet = 0, .category = PSION_SENSITIVE,
        .is_combat_usable = false, .is_passive = false, .keywords = "sense vision remote"
    },
    {
        .id = 22, .name = "E-Sense", .description = "Detect energy and electricity sources",
        .isp_cost = 2, .isp_cost_per_round = 1, .duration_rounds = -1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 300, .area_effect_feet = 0, .category = PSION_SENSITIVE,
        .is_combat_usable = true, .is_passive = true, .keywords = "sense detect energy"
    },
    {
        .id = 23, .name = "Danger Sense", .description = "Immediate danger detection, +2 init",
        .isp_cost = 2, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 0, .area_effect_feet = 0, .category = PSION_SENSITIVE,
        .is_combat_usable = true, .is_passive = false, .keywords = "sense danger defense"
    },

    /* TELEPATHY SCHOOL POWER (24) */
    {
        .id = 24, .name = "Telepathic Probe", .description = "Extract information from unwilling mind",
        .isp_cost = 6, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false,
        .range_feet = 30, .area_effect_feet = 0, .category = PSION_TELEPATHY,
        .is_combat_usable = false, .is_passive = false, .keywords = "telepathy probe mind"
    },

    /* SUPER PSIONIC COMBAT POWER (25) */
    {
        .id = 25, .name = "Mind Bolt", .description = "2d6 MD psionic force blast, bypasses armor",
        .isp_cost = 8, .isp_cost_per_round = 0, .duration_rounds = 1,
        .base_damage = 0, .damage_dice = 2, .damage_sides = 6, .is_mega_damage = true,
        .range_feet = 150, .area_effect_feet = 0, .category = PSION_SUPER,
        .is_combat_usable = true, .is_passive = false, .keywords = "damage mind psionic combat bolt"
    }
};

int PSIONICS_POWER_COUNT = 26;

/* =============== INITIALIZATION =============== */

void psionics_init(void) {
    /* Verify power database is loaded */
    if (PSIONICS_POWER_COUNT != 26) {
        fprintf(stderr, "WARNING: Psionics database count mismatch! Expected 26, got %d\n",
                PSIONICS_POWER_COUNT);
    }
}

/* =============== POWER LOOKUP =============== */

PsionicPower* psionics_find_power_by_id(int power_id) {
    if (power_id < 0 || power_id >= PSIONICS_POWER_COUNT) {
        return NULL;
    }
    return &PSION_POWERS[power_id];
}

PsionicPower* psionics_find_power_by_name(const char *name) {
    if (!name) return NULL;
    
    for (int i = 0; i < PSIONICS_POWER_COUNT; i++) {
        if (strcasecmp(PSION_POWERS[i].name, name) == 0) {
            return &PSION_POWERS[i];
        }
    }
    return NULL;
}

KnownPower* psionics_find_known_power(Character *ch, int power_id) {
    if (!ch || !ch->psionics.powers) return NULL;
    
    for (int i = 0; i < ch->psionics.power_count; i++) {
        if (ch->psionics.powers[i].power_id == power_id) {
            return &ch->psionics.powers[i];
        }
    }
    return NULL;
}

/* =============== ABILITY MANAGEMENT =============== */

void psionics_init_abilities(struct Character *ch) {
    if (!ch) return;
    
    ch->psionics.powers = NULL;
    ch->psionics.power_count = 0;
    
    /* Calculate ISP based on IQ and PP */
    ch->psionics.isp_base = ch->stats.iq + (ch->level * 2) + (ch->stats.pp * 2);
    ch->psionics.isp_max = ch->psionics.isp_base;
    ch->psionics.isp_current = ch->psionics.isp_max;
    ch->psionics.isp_recovery_rate = (ch->stats.iq / 10) + 1;
    
    ch->psionics.is_meditating = false;
    ch->psionics.meditation_rounds_active = 0;
}

void psionics_free_abilities(struct Character *ch) {
    if (!ch) return;
    
    if (ch->psionics.powers) {
        free(ch->psionics.powers);
        ch->psionics.powers = NULL;
    }
    ch->psionics.power_count = 0;
}

void psionics_learn_power(struct Character *ch, int power_id) {
    if (!ch) return;
    
    /* Check if already knows power */
    if (psionics_find_known_power(ch, power_id)) {
        return;  /* Already knows this power */
    }
    
    /* Expand powers array */
    ch->psionics.power_count++;
    ch->psionics.powers = realloc(ch->psionics.powers, 
                                   sizeof(KnownPower) * ch->psionics.power_count);
    
    /* Add new power at rank 1 */
    KnownPower *new_power = &ch->psionics.powers[ch->psionics.power_count - 1];
    new_power->power_id = power_id;
    new_power->rank = 1;
    new_power->total_uses = 0;
    new_power->last_activated = time(NULL);
}

void psionics_add_starting_powers(struct Character *ch, const char *occ_name) {
    if (!ch || !occ_name) return;
    
    if (strcasecmp(occ_name, "Psychic") == 0) {
        psionics_learn_power(ch, 0);   /* Mind Block */
        psionics_learn_power(ch, 17);  /* Sixth Sense */
        psionics_learn_power(ch, 19);  /* Presence Sense */
        ch->psionics.isp_max = 35;
        ch->psionics.isp_current = 35;
    }
    else if (strcasecmp(occ_name, "Cyber-Psychic") == 0) {
        psionics_learn_power(ch, 0);   /* Mind Block */
        psionics_learn_power(ch, 3);   /* Telemechanics */
        psionics_learn_power(ch, 17);  /* Sixth Sense */
        ch->psionics.isp_max = 40;
        ch->psionics.isp_current = 40;
    }
    else if (strcasecmp(occ_name, "Sensitive") == 0) {
        psionics_learn_power(ch, 17);  /* Sixth Sense */
        psionics_learn_power(ch, 21);  /* Clairvoyance */
        psionics_learn_power(ch, 18);  /* Object Read */
        psionics_learn_power(ch, 22);  /* E-Sense */
        ch->psionics.isp_max = 38;
        ch->psionics.isp_current = 38;
    }
    else if (strcasecmp(occ_name, "Healer") == 0) {
        psionics_learn_power(ch, 6);   /* Bio-Regeneration */
        psionics_learn_power(ch, 7);   /* Psychic Healing */
        psionics_learn_power(ch, 10);  /* Mental Surge */
        psionics_learn_power(ch, 8);   /* Disease Immunity */
        ch->psionics.isp_max = 42;
        ch->psionics.isp_current = 42;
    }
    else if (strcasecmp(occ_name, "Physical") == 0) {
        psionics_learn_power(ch, 12);  /* Telekinesis */
        psionics_learn_power(ch, 14);  /* Pyrokinesis */
        psionics_learn_power(ch, 2);   /* Mental Acceleration */
        psionics_learn_power(ch, 16);  /* Levitation */
        ch->psionics.isp_max = 44;
        ch->psionics.isp_current = 44;
    }
    else if (strcasecmp(occ_name, "Cyber-Knight") == 0) {
        psionics_learn_power(ch, 0);   /* Mind Block */
        psionics_learn_power(ch, 17);  /* Sixth Sense */
        ch->psionics.isp_max = 30;
        ch->psionics.isp_current = 30;
    }
    else if (strcasecmp(occ_name, "Mind Melter") == 0) {
        psionics_learn_power(ch, 0);   /* Mind Block */
        psionics_learn_power(ch, 12);  /* Telekinesis */
        psionics_learn_power(ch, 17);  /* Sixth Sense */
        psionics_learn_power(ch, 21);  /* Clairvoyance */
        psionics_learn_power(ch, 14);  /* Pyrokinesis */
        psionics_learn_power(ch, 25);  /* Mind Bolt */
        ch->psionics.isp_max = 50;
        ch->psionics.isp_current = 50;
    }
    else if (strcasecmp(occ_name, "Burster") == 0) {
        psionics_learn_power(ch, 14);  /* Pyrokinesis */
        psionics_learn_power(ch, 0);   /* Mind Block */
        psionics_learn_power(ch, 17);  /* Sixth Sense */
        ch->psionics.isp_max = 40;
        ch->psionics.isp_current = 40;
    }
    /* Headhunter, Vagabond, and other non-psionic classes: no starting powers */
}

/* =============== ISP MANAGEMENT =============== */

int psionics_get_isp_max(Character *ch) {
    if (!ch) return 0;
    return ch->psionics.isp_max;
}

int psionics_get_isp_current(Character *ch) {
    if (!ch) return 0;
    return ch->psionics.isp_current;
}

void psionics_set_isp_current(struct Character *ch, int amount) {
    if (!ch) return;
    if (amount < 0) amount = 0;
    if (amount > ch->psionics.isp_max) amount = ch->psionics.isp_max;
    ch->psionics.isp_current = amount;
}

void psionics_recover_isp(struct Character *ch, int amount) {
    if (!ch) return;
    ch->psionics.isp_current += amount;
    if (ch->psionics.isp_current > ch->psionics.isp_max) {
        ch->psionics.isp_current = ch->psionics.isp_max;
    }
}

void psionics_spend_isp(struct Character *ch, int amount) {
    if (!ch) return;
    ch->psionics.isp_current -= amount;
    if (ch->psionics.isp_current < 0) {
        ch->psionics.isp_current = 0;
    }
}

bool psionics_can_use_power(Character *ch, int power_id) {
    if (!ch) return false;
    
    PsionicPower *power = psionics_find_power_by_id(power_id);
    if (!power) return false;
    
    /* Check if knows power */
    if (!psionics_find_known_power(ch, power_id)) {
        return false;
    }
    
    /* Check ISP cost */
    if (ch->psionics.isp_current < power->isp_cost) {
        return false;
    }
    
    return true;
}

/* =============== POWER ACTIVATION =============== */

/* External declarations */
extern PlayerSession* find_player_by_name(const char *name);
extern void room_broadcast(Room *room, const char *message, PlayerSession *exclude);

bool psionics_activate_power(PlayerSession *sess, struct Character *ch,
                             int power_id, const char *target_name) {
    if (!sess || !ch) return false;

    if (!psionics_can_use_power(ch, power_id)) {
        send_to_player(sess, "You don't have enough ISP to use that power.\n");
        return false;
    }

    PsionicPower *power = psionics_find_power_by_id(power_id);
    if (!power) return false;

    /* Spend ISP */
    psionics_spend_isp(ch, power->isp_cost);
    psionics_record_power_use(ch, power_id);

    /* Apply effects based on power category and properties */
    switch (power->category) {
        case PSION_HEALING: {
            /* Healing powers: restore HP based on damage_dice/sides */
            if (power->damage_dice > 0 && power->damage_sides > 0) {
                int heal = 0;
                for (int d = 0; d < power->damage_dice; d++)
                    heal += 1 + (rand() % power->damage_sides);
                /* Bio-Regeneration (id 6) gets +1d4 bonus */
                if (power_id == 6) heal += 1 + (rand() % 4);
                /* Psychic Healing (id 7) gets +2 bonus */
                if (power_id == 7) heal += 2;

                int old_hp = ch->hp;
                ch->hp += heal;
                if (ch->hp > ch->max_hp) ch->hp = ch->max_hp;
                int actual = ch->hp - old_hp;
                send_to_player(sess, "You use %s and restore %d HP! (HP: %d/%d, ISP: %d/%d)\n",
                    power->name, actual, ch->hp, ch->max_hp,
                    ch->psionics.isp_current, ch->psionics.isp_max);
            } else {
                /* Non-healing healing powers (Disease Immunity, Poison Immunity, etc.) */
                send_to_player(sess, "You use %s! (ISP: %d/%d)\n",
                    power->name, ch->psionics.isp_current, ch->psionics.isp_max);
            }
            break;
        }

        case PSION_PHYSICAL: {
            /* Damage powers: Electrokinesis, Pyrokinesis */
            if (power->damage_dice > 0 && power->damage_sides > 0 && target_name && *target_name) {
                PlayerSession *target = find_player_by_name(target_name);
                if (!target) {
                    send_to_player(sess, "You unleash %s but there's no '%s' here.\n",
                        power->name, target_name);
                    /* ISP already spent - power fires into nothing */
                    break;
                }
                int dmg = 0;
                for (int d = 0; d < power->damage_dice; d++)
                    dmg += 1 + (rand() % power->damage_sides);

                Character *tch = &target->character;
                const char *dmg_type = power->is_mega_damage ? "MD" : "SD";

                if (power->is_mega_damage && tch->health_type == MDC_ONLY) {
                    tch->mdc -= dmg;
                    if (tch->mdc < 0) tch->mdc = 0;
                    send_to_player(sess, "You blast %s with %s for %d %s! (ISP: %d/%d)\n",
                        target->username, power->name, dmg, dmg_type,
                        ch->psionics.isp_current, ch->psionics.isp_max);
                    send_to_player(target, "%s blasts you with %s for %d %s! (MDC: %d/%d)\n",
                        sess->username, power->name, dmg, dmg_type,
                        tch->mdc, tch->max_mdc);
                } else {
                    /* Apply to SDC first, then HP */
                    int remaining = dmg;
                    if (tch->sdc > 0) {
                        int sdc_dmg = (remaining > tch->sdc) ? tch->sdc : remaining;
                        tch->sdc -= sdc_dmg;
                        remaining -= sdc_dmg;
                    }
                    if (remaining > 0) {
                        tch->hp -= remaining;
                    }
                    send_to_player(sess, "You blast %s with %s for %d %s! (ISP: %d/%d)\n",
                        target->username, power->name, dmg, dmg_type,
                        ch->psionics.isp_current, ch->psionics.isp_max);
                    send_to_player(target, "%s blasts you with %s for %d %s! (HP: %d/%d SDC: %d/%d)\n",
                        sess->username, power->name, dmg, dmg_type,
                        tch->hp, tch->max_hp, tch->sdc, tch->max_sdc);
                }
            } else if (power->damage_dice > 0 && power->damage_sides > 0) {
                /* Damage power but no target specified */
                send_to_player(sess, "Use: manifest %s <target>\n", power->name);
            } else {
                /* Non-damage physical powers (Telekinesis, Hydrokinesis, Levitation) */
                send_to_player(sess, "You activate %s! (ISP: %d/%d)\n",
                    power->name, ch->psionics.isp_current, ch->psionics.isp_max);
            }
            break;
        }

        case PSION_SUPER: {
            if (power_id == 25) {
                /* Mind Bolt: 2d6 MD psionic attack vs. player or NPC target */
                if (!target_name || !*target_name) {
                    send_to_player(sess, "Use: manifest mind bolt <target>\n");
                    break;
                }
                Room *room = sess->current_room;
                if (!room) {
                    send_to_player(sess, "You need to be in a room to use Mind Bolt.\n");
                    break;
                }
                PlayerSession *bolt_player = NULL;
                NPC *bolt_npc = NULL;
                int res = resolve_target(room, target_name, sess, &bolt_player, &bolt_npc);
                if (res == 0) {
                    send_to_player(sess, "You don't see '%s' here.\n", target_name);
                    break;
                }

                int dmg = 0;
                for (int d = 0; d < power->damage_dice; d++)
                    dmg += 1 + (rand() % power->damage_sides);

                if (res == 2 && bolt_npc) {
                    /* NPC target */
                    char display[64];
                    snprintf(display, sizeof(display), "%s", bolt_npc->name);
                    display[0] = (char)toupper((unsigned char)display[0]);

                    send_to_player(sess,
                        "You hurl a bolt of pure psionic force at %s for %d M.D.! "
                        "(ISP: %d/%d)\n",
                        display, dmg,
                        ch->psionics.isp_current, ch->psionics.isp_max);

                    /* Bypasses armor — apply directly to MDC/HP */
                    if (bolt_npc->character.health_type == MDC_ONLY) {
                        bolt_npc->character.mdc -= dmg;
                        if (bolt_npc->character.mdc < 0) bolt_npc->character.mdc = 0;
                        if (bolt_npc->character.mdc == 0)
                            npc_handle_death(bolt_npc, sess);
                    } else {
                        int sdc_eq = dmg * 100;
                        if (sdc_eq >= bolt_npc->character.sdc) {
                            sdc_eq -= bolt_npc->character.sdc;
                            bolt_npc->character.sdc = 0;
                            bolt_npc->character.hp -= sdc_eq;
                            if (bolt_npc->character.hp < 0) bolt_npc->character.hp = 0;
                        } else {
                            bolt_npc->character.sdc -= sdc_eq;
                        }
                        if (bolt_npc->character.hp <= 0)
                            npc_handle_death(bolt_npc, sess);
                    }
                } else if (res == 1 && bolt_player) {
                    /* Player target */
                    if (bolt_player->is_godmode) {
                        send_to_player(sess,
                            "Your Mind Bolt fizzles against %s's divine protection!\n",
                            bolt_player->username);
                        break;
                    }
                    send_to_player(sess,
                        "You hurl a bolt of pure psionic force at %s for %d M.D.! "
                        "(ISP: %d/%d)\n",
                        bolt_player->username, dmg,
                        ch->psionics.isp_current, ch->psionics.isp_max);
                    send_to_player(bolt_player,
                        "%s strikes you with a Mind Bolt for %d M.D.!\n",
                        sess->username, dmg);

                    Character *tch = &bolt_player->character;
                    if (tch->health_type == MDC_ONLY) {
                        tch->mdc -= dmg;
                        if (tch->mdc < 0) tch->mdc = 0;
                    } else {
                        int sdc_eq = dmg * 100;
                        if (sdc_eq >= tch->sdc) {
                            sdc_eq -= tch->sdc;
                            tch->sdc = 0;
                            tch->hp -= sdc_eq;
                            if (tch->hp < 0) tch->hp = 0;
                        } else {
                            tch->sdc -= sdc_eq;
                        }
                    }
                    if (tch->hp <= 0 || tch->mdc <= 0)
                        handle_player_death(bolt_player, sess, NULL);
                }
            } else if (power_id == 2) {
                /* Mental Acceleration: +3 init, +20% dodge feedback */
                send_to_player(sess,
                    "You activate Mental Acceleration! Your reflexes sharpen. "
                    "(ISP: %d/%d)\n",
                    ch->psionics.isp_current, ch->psionics.isp_max);
            } else {
                send_to_player(sess, "You activate %s! (ISP: %d/%d)\n",
                    power->name, ch->psionics.isp_current, ch->psionics.isp_max);
            }
            break;
        }

        case PSION_SENSITIVE:
        case PSION_TELEPATHY:
        default:
            send_to_player(sess, "You use %s! (ISP: %d/%d)\n",
                power->name, ch->psionics.isp_current, ch->psionics.isp_max);
            break;
    }

    /* Broadcast to room */
    if (sess->current_room) {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s uses %s.\r\n", sess->username, power->name);
        room_broadcast(sess->current_room, msg, sess);
    }

    return true;
}

void psionics_power_tick(struct Character *ch) {
    if (!ch) return;
    
    /* Recover ISP naturally each round */
    psionics_recover_isp(ch, ch->psionics.isp_recovery_rate);
}

void psionics_meditate_tick(struct Character *ch) {
    if (!ch) return;

    if (ch->psionics.is_meditating && ch->psionics.meditation_rounds_active > 0) {
        /* Recover +1d6 ISP per meditation round */
        int recover = 1 + (rand() % 6);  /* 1d6 */
        psionics_recover_isp(ch, recover);
        ch->psionics.meditation_rounds_active--;

        if (ch->psionics.meditation_rounds_active <= 0) {
            ch->psionics.is_meditating = false;
        }
    }
}

/* =============== DISPLAY =============== */

void psionics_display_powers(PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    
    send_to_player(sess, "=== PSIONIC POWERS ===\n");
    
    if (ch->psionics.power_count == 0) {
        send_to_player(sess, "You have no psionic powers.\n");
        return;
    }
    
    for (int i = 0; i < ch->psionics.power_count; i++) {
        KnownPower *kp = &ch->psionics.powers[i];
        PsionicPower *power = psionics_find_power_by_id(kp->power_id);
        
        if (power) {
            send_to_player(sess, "%d. %s (%d ISP) [RANK %d]\n   %s\n",
                           i + 1, power->name, power->isp_cost, kp->rank,
                           power->description);
        }
    }
    
    send_to_player(sess, "\n");
}

void psionics_display_isp(PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    int recovery = ch->psionics.isp_recovery_rate;
    
    send_to_player(sess, "ISP: %d/%d (%d%%) - +%d per round\n",
                   ch->psionics.isp_current, ch->psionics.isp_max,
                   (ch->psionics.isp_current * 100) / ch->psionics.isp_max,
                   recovery);
}

/* =============== ADVANCEMENT =============== */

void psionics_record_power_use(struct Character *ch, int power_id) {
    if (!ch) return;
    
    KnownPower *kp = psionics_find_known_power(ch, power_id);
    if (!kp) return;
    
    kp->total_uses++;
    kp->last_activated = time(NULL);
    
    psionics_check_power_rank_advance(ch, power_id);
}

void psionics_check_power_rank_advance(struct Character *ch, int power_id) {
    if (!ch) return;
    
    KnownPower *kp = psionics_find_known_power(ch, power_id);
    if (!kp) return;
    
    /* Advancement table: 50, 75, 100, 120, 140, 160, 180, 200, 220 uses */
    int advancement_table[] = {0, 50, 75, 100, 120, 140, 160, 180, 200, 220};
    
    for (int rank = 1; rank < 10; rank++) {
        if (kp->rank == rank && kp->total_uses >= advancement_table[rank + 1]) {
            kp->rank++;
            return;
        }
    }
}
