/*
 * skills_config.h - O.C.C.-specific skill configurations
 * 
 * Per Palladium Rifts Ultimate Edition mechanics:
 * - Primary Skills: Mandatory for all members of O.C.C., with +5-30% bonus
 * - O.C.C.-Related: Selectable, +10-20% bonus, additional slots at levels 3/6/9/12/15
 * - Secondary: Freely selectable, base % only, can pick additional every level
 * 
 * FOUNDATION BUILD: Core 8-10 O.C.C.s with complete skill configs
 * Other configs can be added using the same patterns
 */

#ifndef SKILLS_CONFIG_H
#define SKILLS_CONFIG_H

#include "wiz_tools.h"

/* ============================================================================
 * SOLDIER (Military Combat Specialist)
 * ============================================================================
 */

static SkillDef soldier_primary_skills[] = {
    {"Hand to Hand: Basic", 40, 3, 1, 1},
    {"Sword", 60, 3, 1, 1},
    {"Rifle", 50, 3, 1, 1},
    {"Climbing", 30, 2, 1, 1},
    {"Swimming", 40, 2, 1, 1},
    {"Land Navigation", 35, 2, 1, 1},
    {"Weapons Systems", 35, 3, 1, 1},
    {"Military Etiquette", 50, 1, 1, 1},
};

static OCCSkillConfig soldier_config = {
    .occ_name = "Soldier",
    .primary_count = 8,
    .primary_skills = {
        {"Hand to Hand: Basic", 40, 3, 1, 1},
        {"Sword", 60, 3, 1, 1},
        {"Rifle", 50, 3, 1, 1},
        {"Climbing", 30, 2, 1, 1},
        {"Swimming", 40, 2, 1, 1},
        {"Land Navigation", 35, 2, 1, 1},
        {"Weapons Systems", 35, 3, 1, 1},
        {"Military Etiquette", 50, 1, 1, 1},
    },
    .occ_related_max = 8,    /* Can select 8 from pool of OCC-related */
    .secondary_max = 4,
};

/* ============================================================================
 * MIND MELTER (Psychic Master)
 * ============================================================================
 */

static OCCSkillConfig mind_melter_config = {
    .occ_name = "Mind Melter",
    .primary_count = 9,
    .primary_skills = {
        {"Concentration", 50, 2, 1, 1},
        {"Meditation", 55, 2, 1, 1},
        {"Telepathy Basics", 40, 3, 1, 1},
        {"Track/Sense Psionic", 35, 3, 1, 1},
        {"Survive: Wilderness", 35, 2, 1, 1},
        {"Land Navigation", 40, 2, 1, 1},
        {"Lore: Creatures", 30, 2, 1, 1},
        {"Escape Artist", 40, 3, 1, 1},
        {"Lore: Demons & Monsters", 25, 2, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* ============================================================================
 * LEY LINE WALKER (Mage)
 * ============================================================================
 */

static OCCSkillConfig ley_line_walker_config = {
    .occ_name = "Ley Line Walker",
    .primary_count = 10,
    .primary_skills = {
        {"Spell Knowledge", 50, 3, 1, 1},
        {"Meditation", 50, 2, 1, 1},
        {"Lore: Magic", 45, 2, 1, 1},
        {"Lore: Creatures", 35, 3, 1, 1},
        {"Language: Human", 65, 0, 1, 1},
        {"Language: Demongogian", 35, 2, 1, 1},
        {"Climb", 30, 2, 1, 1},
        {"Swim", 35, 2, 1, 1},
        {"Lore: Demons", 40, 3, 1, 1},
        {"Sense Ley Lines", 45, 3, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* ============================================================================
 * ROGUE (Thief/Assassin)
 * ============================================================================
 */

static OCCSkillConfig rogue_config = {
    .occ_name = "Rogue",
    .primary_count = 9,
    .primary_skills = {
        {"Hand to Hand: Basic", 35, 3, 1, 1},
        {"Knife", 50, 3, 1, 1},
        {"Sword", 40, 3, 1, 1},
        {"Lockpicking", 45, 4, 1, 1},
        {"Detect Traps", 40, 3, 1, 1},
        {"Disarm Traps", 45, 3, 1, 1},
        {"Pickpocketing", 40, 4, 1, 1},
        {"Backstab", 50, 2, 1, 1},
        {"Evasion", 45, 3, 1, 1},
    },
    .occ_related_max = 7,
    .secondary_max = 5,
};

/* ============================================================================
 * WILDERNESS SCOUT (Ranger)
 * ============================================================================
 */

static OCCSkillConfig wilderness_scout_config = {
    .occ_name = "Wilderness Scout",
    .primary_count = 10,
    .primary_skills = {
        {"Rifle", 55, 3, 1, 1},
        {"Archery", 50, 3, 1, 1},
        {"Climbing", 40, 3, 1, 1},
        {"Swimming", 50, 2, 1, 1},
        {"Tracking", 50, 4, 1, 1},
        {"Land Navigation", 50, 2, 1, 1},
        {"Hunting", 55, 3, 1, 1},
        {"Fishing", 50, 2, 1, 1},
        {"Botany", 35, 2, 1, 1},
        {"Wilderness Survival", 55, 2, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* ============================================================================
 * SCHOLAR (Academic/Researcher)
 * ============================================================================
 */

static OCCSkillConfig scholar_config = {
    .occ_name = "Scholar",
    .primary_count = 10,
    .primary_skills = {
        {"Language: Human", 60, 1, 1, 1},
        {"Language: Old Kingdom", 40, 1, 1, 1},
        {"Lore: History", 55, 3, 1, 1},
        {"Lore: Legends and Myths", 45, 3, 1, 1},
        {"Lore: Creatures", 40, 2, 1, 1},
        {"Lore: Magic", 40, 2, 1, 1},
        {"Research", 60, 3, 1, 1},
        {"Memorization", 50, 2, 1, 1},
        {"Appraisal", 35, 2, 1, 1},
        {"Literacy", 70, 0, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* ============================================================================
 * MERCHANT (Trader/Negotiator)
 * ============================================================================
 */

static OCCSkillConfig merchant_config = {
    .occ_name = "Merchant",
    .primary_count = 9,
    .primary_skills = {
        {"Appraisal", 50, 3, 1, 1},
        {"Bargain", 60, 3, 1, 1},
        {"Literacy", 70, 0, 1, 1},
        {"Calculation", 50, 2, 1, 1},
        {"Accounting", 45, 2, 1, 1},
        {"Language: Human", 60, 0, 1, 1},
        {"Streetwise", 40, 3, 1, 1},
        {"Detect Lies", 35, 3, 1, 1},
        {"Trade Knowledge", 60, 3, 1, 1},
    },
    .occ_related_max = 7,
    .secondary_max = 5,
};

/* ============================================================================
 * MYSTIC (Spiritual Practitioner)
 * ============================================================================
 */

static OCCSkillConfig mystic_config = {
    .occ_name = "Mystic",
    .primary_count = 10,
    .primary_skills = {
        {"Meditation", 60, 2, 1, 1},
        {"Lore: Magic", 50, 2, 1, 1},
        {"Lore: Creatures", 40, 2, 1, 1},
        {"Lore: Arts & History", 45, 2, 1, 1},
        {"Spell Knowledge", 45, 3, 1, 1},
        {"Sense Magic", 40, 2, 1, 1},
        {"Linguistics", 40, 2, 1, 1},
        {"Philosophy", 50, 2, 1, 1},
        {"Healing", 45, 3, 1, 1},
        {"Lore: Demons", 35, 2, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* ============================================================================
 * DRAGON HATCHLING (Young Dragon Rider)
 * ============================================================================
 */

static OCCSkillConfig dragon_hatchling_config = {
    .occ_name = "Dragon Hatchling",
    .primary_count = 8,
    .primary_skills = {
        {"Hand to Hand: Combat", 45, 3, 1, 1},
        {"Sword", 55, 3, 1, 1},
        {"Mounted Combat", 40, 3, 1, 1},
        {"Animal Handling: Dragon", 55, 3, 1, 1},
        {"Climbing", 35, 2, 1, 1},
        {"Swimming", 40, 2, 1, 1},
        {"Leadership", 40, 2, 1, 1},
        {"Lore: Dragons", 60, 3, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* ============================================================================
 * SKILL CONFIG LOOKUP TABLE
 * ============================================================================
 */

typedef struct {
    const char *occ_name;
    OCCSkillConfig *config;
} SkillConfigEntry;

static const SkillConfigEntry skill_configs[] = {
    {"Soldier", &soldier_config},
    {"Mind Melter", &mind_melter_config},
    {"Ley Line Walker", &ley_line_walker_config},
    {"Rogue", &rogue_config},
    {"Wilderness Scout", &wilderness_scout_config},
    {"Scholar", &scholar_config},
    {"Merchant", &merchant_config},
    {"Mystic", &mystic_config},
    {"Dragon Hatchling", &dragon_hatchling_config},
    {NULL, NULL}  /* Sentinel */
};

/* ============================================================================
 * OCC Pool Skills (Available for OCC-Related and Secondary selection)
 * ============================================================================
 */

static SkillDef occ_pool_skills[] = {
    /* Combat Skills */
    {"Hand to Hand: Boxing", 30, 2, 1, 0},
    {"Hand to Hand: Wrestling", 25, 2, 1, 0},
    {"Axe", 40, 3, 1, 0},
    {"Hammer/Mace", 45, 3, 1, 0},
    {"Crossbow", 40, 3, 1, 0},
    {"Energy Pistol", 45, 3, 1, 0},
    {"Energy Rifle", 50, 3, 1, 0},
    {"Armor Repair", 40, 3, 1, 0},
    {"Weapon Repair", 40, 3, 1, 0},
    
    /* Survival Skills */
    {"Preserve Food", 35, 2, 1, 0},
    {"Animal Husbandry", 40, 2, 1, 0},
    {"Herbal Lore", 40, 3, 1, 0},
    {"Cooking", 45, 1, 1, 0},
    {"Rope Use", 50, 2, 1, 0},
    {"Cryptography", 35, 4, 1, 0},
    
    /* Knowledge Skills */
    {"Lore: Geography", 40, 2, 1, 0},
    {"Lore: Technology", 30, 3, 1, 0},
    {"Heraldry", 35, 2, 1, 0},
    {"Alchemy", 30, 3, 1, 0},
    {"Metallurgy", 35, 3, 1, 0},
    
    /* Social Skills */
    {"Etiquette", 45, 1, 1, 0},
    {"Seduction", 40, 3, 1, 0},
    {"Performance", 40, 2, 1, 0},
    {"Dance", 35, 2, 1, 0},
    {"Play Instrument", 30, 3, 1, 0},
    {NULL, 0, 0, 0, 0}  /* Sentinel */
};

/**
 * get_occ_skill_config()
 * Returns skill configuration for the given O.C.C.
 * Returns NULL if not found
 */
static inline OCCSkillConfig *get_occ_skill_config(const char *occ_name) {
    if (!occ_name) return NULL;
    
    for (int i = 0; skill_configs[i].occ_name != NULL; i++) {
        if (strcmp(skill_configs[i].occ_name, occ_name) == 0) {
            return skill_configs[i].config;
        }
    }
    return NULL;
}

#endif /* SKILLS_CONFIG_H */
