/*
 * Perform a skill check for a player session using Palladium rules.
 * Returns: 2 = crit success, 1 = success, 0 = failure, -1 = crit fail
 */
// System includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Project includes
#include "session_internal.h"
#include "skills.h"
#include "chargen.h"
#include "debug.h"

int perform_skill_check(PlayerSession *sess, const char *skill_name, int difficulty_modifier) {
    if (!sess || !skill_name) return 0;
    int roll = (rand() % 100) + 1;
    int base = 0, char_pct = 0, race_bonus = 0, attr_bonus = 0;
    int total = 0;
    int i;
    SkillDef *skill = skill_get_by_name(skill_name);
    if (!skill) {
        send_to_player(sess, "[SKILL] Unknown skill: %s\n", skill_name);
        return 0;
    }
    base = skill->base_percentage;
    // Find character's learned percentage for this skill
    for (i = 0; i < sess->character.num_skills; i++) {
        int sid = sess->character.skills[i].skill_id;
        SkillDef *sd = skill_get_by_id(sid);
        if (sd && strcasecmp(sd->name, skill_name) == 0) {
            char_pct = sess->character.skills[i].percentage;
            break;
        }
    }
    // Race bonus
    race_bonus = sess->character.race_skill_bonus;
    // Attribute bonus (simple: +1 per 2 points above 10 in relevant stat)
    char stat = skill->modifier_stat;
    int stat_val = 10;
    if (stat == 'P') stat_val = sess->character.stats.pp;
    else if (stat == 'S') stat_val = sess->character.stats.ps;
    else if (stat == 'M') stat_val = sess->character.stats.ma;
    else if (stat == 'E') stat_val = sess->character.stats.me;
    else if (stat == 'I') stat_val = sess->character.stats.iq;
    if (stat_val > 10) attr_bonus = (stat_val - 10) / 2;
    total = base + char_pct + race_bonus + attr_bonus - difficulty_modifier;
    if (total < 0) total = 0;
    if (total > 100) total = 100;
    int result = 0;
    if (roll >= 96) result = -1; // crit fail
    else if (roll <= 5) result = 2; // crit success
    else if (roll <= total) result = 1; // success
    else result = 0; // fail
    // Log only if skill matters (not for display-only checks)
    if (result == 2)
        fprintf(stderr, "[SKILL] %s rolled %s: %d vs %d = CRIT SUCCESS\n", sess->username, skill_name, roll, total);
    else if (result == -1)
        fprintf(stderr, "[SKILL] %s rolled %s: %d vs %d = CRIT FAIL\n", sess->username, skill_name, roll, total);
    else if (result == 1)
        fprintf(stderr, "[SKILL] %s rolled %s: %d vs %d = SUCCESS\n", sess->username, skill_name, roll, total);
    else
        fprintf(stderr, "[SKILL] %s rolled %s: %d vs %d = FAIL\n", sess->username, skill_name, roll, total);
    return result;
}
/* skills.c - Rifts RPG Skill System Implementation */
// ...existing code...

/* External declarations */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* ========== SKILL DATABASE ========== */

/* All available skills - 15 core skills */
static const SkillDef SKILL_DATABASE[] = {
    // ...existing skills...
    // --- Added missing skills from LPC inventory, sorted alphabetically within each category ---
    { .name = "Prowl", .category = "Rogue", .description = "Move silently and avoid detection.", .base_percentage = 25, .modifier_stat = 'P' },
    { .name = "Streetwise", .category = "Rogue", .description = "Navigate and gather information in urban environments.", .base_percentage = 20, .modifier_stat = 'I' },
    { .name = "Safecracking", .category = "Rogue", .description = "Open safes and bypass security locks.", .base_percentage = 15, .modifier_stat = 'I' },
    { .name = "Disguise", .category = "Rogue", .description = "Alter appearance to avoid recognition.", .base_percentage = 25, .modifier_stat = 'I' },
    { .name = "Pick Locks", .category = "Rogue", .description = "Open locks without keys.", .base_percentage = 30, .modifier_stat = 'I' },
    { .name = "Impersonation", .category = "Rogue", .description = "Pretend to be someone else convincingly.", .base_percentage = 25, .modifier_stat = 'I' },
    { .name = "Forgery", .category = "Rogue", .description = "Create fake documents or items.", .base_percentage = 20, .modifier_stat = 'I' },
    { .name = "Pick Pockets", .category = "Rogue", .description = "Steal items from others without being noticed.", .base_percentage = 25, .modifier_stat = 'P' },
    { .name = "Gambling", .category = "Rogue", .description = "Games of chance and probability.", .base_percentage = 30, .modifier_stat = 'I' },
    { .name = "Palming", .category = "Rogue", .description = "Conceal small objects in hand.", .base_percentage = 20, .modifier_stat = 'P' },
    { .name = "Concealment", .category = "Rogue", .description = "Hide objects or oneself from view.", .base_percentage = 20, .modifier_stat = 'P' },
    // ...repeat for all other missing skills from the audit, using the same format...
};

/* Total skills in database */
#define TOTAL_SKILLS (sizeof(SKILL_DATABASE) / sizeof(SkillDef))

/* ========== OCC SKILL PACKAGES ========== */

/* Helper macro for skill packages */
#define SKILL_PACKAGE(name, skills_array, isp, ppe) \
    { .skill_ids = skills_array, .num_skills = sizeof(skills_array)/sizeof(int), .starting_isp = isp, .starting_ppe = ppe }

/* Skill ID mapping for readability */
#define HAND_TO_HAND 0
#define ACROBATICS 1
#define SWIMMING 2
#define COMPUTER_OPS 3
#define MECHANICS 4
#define ELECTRONICS 5
#define LITERACY 6
#define WP_SWORD 7
#define WP_RIFLE 8
#define WP_PISTOL 9
#define FIRST_AID 10
#define PARAMEDIC 11
#define SURVIVAL 12
#define TRACKING 13
#define MAGIC_NOVICE 14
#define PSIONICS_NOVICE 15

/* OCC Skill Packages for all 35 OCCs */
static OCCSkillPackage OCC_SKILL_PACKAGES[] = {
    /* 0: Cyber-Knight - Combat + Psionics + Tech */
    {
        .skill_ids = {HAND_TO_HAND, WP_SWORD, WP_PISTOL, COMPUTER_OPS, PSIONICS_NOVICE},
        .skill_percentages = {65, 70, 55, 45, 40},
        .num_skills = 5,
        .starting_isp = 20,  /* 3d6 psi points */
        .starting_ppe = 5
    },
    
    /* 1: Ley Line Walker - Magic + Knowledge */
    {
        .skill_ids = {HAND_TO_HAND, MAGIC_NOVICE, LITERACY, SURVIVAL, WP_PISTOL},
        .skill_percentages = {30, 80, 70, 45, 35},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 40  /* Heavy PPE */
    },
    
    /* 2: Rogue Scientist - Technical Master */
    {
        .skill_ids = {COMPUTER_OPS, ELECTRONICS, MECHANICS, LITERACY, HAND_TO_HAND},
        .skill_percentages = {75, 70, 65, 80, 35},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 3: Techno-Wizard - Magic + Technology */
    {
        .skill_ids = {MAGIC_NOVICE, COMPUTER_OPS, ELECTRONICS, LITERACY, WP_PISTOL},
        .skill_percentages = {70, 60, 65, 75, 40},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 35
    },
    
    /* 4: Battle Magus - Combat + Magic */
    {
        .skill_ids = {HAND_TO_HAND, MAGIC_NOVICE, WP_SWORD, LITERACY, ACROBATICS},
        .skill_percentages = {60, 70, 70, 60, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 30
    },
    
    /* 5: Biomancer - Medical + Magic */
    {
        .skill_ids = {MAGIC_NOVICE, PARAMEDIC, LITERACY, FIRST_AID, SURVIVAL},
        .skill_percentages = {65, 50, 70, 60, 40},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 35
    },
    
    /* 6: Body Fixer - Medical + Technical */
    {
        .skill_ids = {PARAMEDIC, ELECTRONICS, MECHANICS, FIRST_AID, COMPUTER_OPS},
        .skill_percentages = {70, 60, 55, 70, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 7: Burster - Psychic Warrior */
    {
        .skill_ids = {PSIONICS_NOVICE, HAND_TO_HAND, ACROBATICS, WP_PISTOL, LITERACY},
        .skill_percentages = {70, 60, 50, 50, 40},
        .num_skills = 5,
        .starting_isp = 35,  /* Heavy ISP */
        .starting_ppe = 5
    },
    
    /* 8: City Rat - Urban Rogue */
    {
        .skill_ids = {HAND_TO_HAND, TRACKING, ACROBATICS, COMPUTER_OPS, SURVIVAL},
        .skill_percentages = {50, 55, 60, 50, 40},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 9: Cosmo-Knight - Cosmic Knight */
    {
        .skill_ids = {HAND_TO_HAND, WP_SWORD, PSIONICS_NOVICE, LITERACY, MAGIC_NOVICE},
        .skill_percentages = {65, 70, 55, 60, 40},
        .num_skills = 5,
        .starting_isp = 25,
        .starting_ppe = 20
    },
    
    /* 10: Crazy - Augmented Warrior */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_SWORD, ACROBATICS, TRACKING},
        .skill_percentages = {75, 70, 65, 55, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 11: Dragon Hatchling RCC - Young Dragon */
    {
        .skill_ids = {HAND_TO_HAND, MAGIC_NOVICE, PSIONICS_NOVICE, LITERACY, SURVIVAL},
        .skill_percentages = {55, 50, 50, 50, 40},
        .num_skills = 5,
        .starting_isp = 20,
        .starting_ppe = 40
    },
    
    /* 12: Elemental Fusionist - Elemental Mage */
    {
        .skill_ids = {MAGIC_NOVICE, LITERACY, SURVIVAL, FIRST_AID, ACROBATICS},
        .skill_percentages = {75, 70, 50, 40, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 50
    },
    
    /* 13: Full Conversion Borg - Cyborg */
    {
        .skill_ids = {MECHANICS, ELECTRONICS, COMPUTER_OPS, HAND_TO_HAND, WP_RIFLE},
        .skill_percentages = {65, 60, 50, 70, 65},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 14: Headhunter - Bounty Hunter */
    {
        .skill_ids = {TRACKING, HAND_TO_HAND, WP_PISTOL, WP_RIFLE, ACROBATICS},
        .skill_percentages = {60, 55, 60, 60, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 15: Juicer - Chemical Warrior */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_SWORD, ACROBATICS, TRACKING},
        .skill_percentages = {75, 70, 70, 60, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 16: Line Walker - Ley Line Master */
    {
        .skill_ids = {MAGIC_NOVICE, LITERACY, SURVIVAL, PSIONICS_NOVICE, FIRST_AID},
        .skill_percentages = {70, 75, 50, 40, 40},
        .num_skills = 5,
        .starting_isp = 10,
        .starting_ppe = 45
    },
    
    /* 17: Mercenary - Professional Soldier */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_SWORD, TRACKING, SURVIVAL},
        .skill_percentages = {65, 70, 60, 55, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 18: Mind Melter - Psychic Master */
    {
        .skill_ids = {PSIONICS_NOVICE, LITERACY, ACROBATICS, FIRST_AID, COMPUTER_OPS},
        .skill_percentages = {75, 65, 50, 45, 45},
        .num_skills = 5,
        .starting_isp = 40,
        .starting_ppe = 5
    },
    
    /* 19: Mystic - Spiritual Magic User */
    {
        .skill_ids = {MAGIC_NOVICE, LITERACY, FIRST_AID, SURVIVAL, PSIONICS_NOVICE},
        .skill_percentages = {70, 70, 50, 50, 40},
        .num_skills = 5,
        .starting_isp = 15,
        .starting_ppe = 35
    },
    
    /* 20: Necromancer - Death Magic */
    {
        .skill_ids = {MAGIC_NOVICE, PSIONICS_NOVICE, LITERACY, SURVIVAL, HAND_TO_HAND},
        .skill_percentages = {75, 50, 75, 45, 35},
        .num_skills = 5,
        .starting_isp = 20,
        .starting_ppe = 40
    },
    
    /* 21: Ninja - Silent Warrior */
    {
        .skill_ids = {HAND_TO_HAND, WP_SWORD, ACROBATICS, TRACKING, PSIONICS_NOVICE},
        .skill_percentages = {70, 70, 65, 60, 40},
        .num_skills = 5,
        .starting_isp = 15,
        .starting_ppe = 5
    },
    
    /* 22: Operator - Vehicle Expert */
    {
        .skill_ids = {MECHANICS, COMPUTER_OPS, ELECTRONICS, HAND_TO_HAND, WP_PISTOL},
        .skill_percentages = {70, 60, 55, 40, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 23: Power Armor Pilot - Mecha Warrior */
    {
        .skill_ids = {MECHANICS, WP_RIFLE, HAND_TO_HAND, COMPUTER_OPS, ACROBATICS},
        .skill_percentages = {60, 70, 55, 50, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 24: Psi-Stalker - Psychic Tracker */
    {
        .skill_ids = {PSIONICS_NOVICE, TRACKING, SURVIVAL, HAND_TO_HAND, ACROBATICS},
        .skill_percentages = {60, 70, 60, 55, 50},
        .num_skills = 5,
        .starting_isp = 30,
        .starting_ppe = 5
    },
    
    /* 25: Psychic - Psionic Master */
    {
        .skill_ids = {PSIONICS_NOVICE, LITERACY, FIRST_AID, ACROBATICS, HAND_TO_HAND},
        .skill_percentages = {75, 65, 45, 50, 40},
        .num_skills = 5,
        .starting_isp = 40,
        .starting_ppe = 5
    },
    
    /* 26: Rifter - Dimensional Traveler */
    {
        .skill_ids = {MAGIC_NOVICE, LITERACY, SURVIVAL, COMPUTER_OPS, PSIONICS_NOVICE},
        .skill_percentages = {65, 70, 50, 50, 45},
        .num_skills = 5,
        .starting_isp = 20,
        .starting_ppe = 40
    },
    
    /* 27: Rogue Scholar - Knowledge Master */
    {
        .skill_ids = {LITERACY, COMPUTER_OPS, SURVIVAL, FIRST_AID, MAGIC_NOVICE},
        .skill_percentages = {80, 60, 45, 45, 40},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 20
    },
    
    /* 28: Shifter - Beast Master */
    {
        .skill_ids = {PSIONICS_NOVICE, HAND_TO_HAND, SURVIVAL, TRACKING, ACROBATICS},
        .skill_percentages = {65, 60, 60, 60, 55},
        .num_skills = 5,
        .starting_isp = 35,
        .starting_ppe = 5
    },
    
    /* 29: Temporal Wizard - Time Mage */
    {
        .skill_ids = {MAGIC_NOVICE, PSIONICS_NOVICE, LITERACY, COMPUTER_OPS, ACROBATICS},
        .skill_percentages = {75, 50, 75, 55, 45},
        .num_skills = 5,
        .starting_isp = 15,
        .starting_ppe = 45
    },
    
    /* 30: Undead Slayer - Supernatural Hunter */
    {
        .skill_ids = {HAND_TO_HAND, WP_SWORD, MAGIC_NOVICE, TRACKING, FIRST_AID},
        .skill_percentages = {65, 70, 55, 60, 50},
        .num_skills = 5,
        .starting_isp = 10,
        .starting_ppe = 30
    },
    
    /* 31: Vagabond - Free Wanderer */
    {
        .skill_ids = {SURVIVAL, HAND_TO_HAND, TRACKING, ACROBATICS, LITERACY},
        .skill_percentages = {60, 50, 55, 55, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 32: Warrior Monk - Disciplined Fighter */
    {
        .skill_ids = {HAND_TO_HAND, ACROBATICS, PSIONICS_NOVICE, LITERACY, FIRST_AID},
        .skill_percentages = {75, 65, 45, 55, 50},
        .num_skills = 5,
        .starting_isp = 20,
        .starting_ppe = 5
    },
    
    /* 33: Wilderness Scout - Nature Expert */
    {
        .skill_ids = {SURVIVAL, TRACKING, HAND_TO_HAND, WP_RIFLE, ACROBATICS},
        .skill_percentages = {70, 70, 50, 60, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 34: Zapper - Energy Blaster */
    {
        .skill_ids = {WP_PISTOL, WP_RIFLE, COMPUTER_OPS, ELECTRONICS, ACROBATICS},
        .skill_percentages = {70, 75, 50, 50, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* ========== NEW AETHERMUD OCCs (35-64) ========== */
    
    /* 35: Atlantean Nomad */
    {
        .skill_ids = {HAND_TO_HAND, SURVIVAL, TRACKING, LITERACY, WP_SWORD},
        .skill_percentages = {60, 65, 55, 70, 60},
        .num_skills = 5,
        .starting_isp = 10,
        .starting_ppe = 15
    },
    
    /* 36: Atlantean Slave */
    {
        .skill_ids = {HAND_TO_HAND, SURVIVAL, FIRST_AID, MECHANICS, LITERACY},
        .skill_percentages = {55, 50, 45, 40, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 10
    },
    
    /* 37: Ninja Juicer */
    {
        .skill_ids = {HAND_TO_HAND, ACROBATICS, WP_SWORD, TRACKING, WP_PISTOL},
        .skill_percentages = {80, 75, 70, 60, 65},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 38: Delphi Juicer */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, COMPUTER_OPS, ELECTRONICS, LITERACY},
        .skill_percentages = {70, 70, 60, 55, 65},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 39: Hyperion Juicer */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_SWORD, ACROBATICS, SURVIVAL},
        .skill_percentages = {80, 75, 70, 65, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 40: CS Ranger */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, SURVIVAL, TRACKING, FIRST_AID},
        .skill_percentages = {65, 70, 65, 60, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 41: CS Technical Officer */
    {
        .skill_ids = {COMPUTER_OPS, ELECTRONICS, MECHANICS, LITERACY, WP_PISTOL},
        .skill_percentages = {70, 65, 60, 65, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 42: Air Warlock */
    {
        .skill_ids = {MAGIC_NOVICE, LITERACY, SURVIVAL, WP_PISTOL, HAND_TO_HAND},
        .skill_percentages = {75, 65, 50, 40, 35},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 35
    },
    
    /* 43: Tattooed Man */
    {
        .skill_ids = {HAND_TO_HAND, MAGIC_NOVICE, WP_SWORD, ACROBATICS, SURVIVAL},
        .skill_percentages = {70, 70, 65, 60, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 30
    },
    
    /* 44: Nega-Psychic */
    {
        .skill_ids = {PSIONICS_NOVICE, LITERACY, COMPUTER_OPS, HAND_TO_HAND, WP_PISTOL},
        .skill_percentages = {65, 60, 50, 45, 45},
        .num_skills = 5,
        .starting_isp = 30,
        .starting_ppe = 5
    },
    
    /* 45: Cyber-Doc */
    {
        .skill_ids = {PARAMEDIC, FIRST_AID, COMPUTER_OPS, ELECTRONICS, LITERACY},
        .skill_percentages = {80, 75, 60, 55, 70},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 46: Kittani Field Mechanic */
    {
        .skill_ids = {MECHANICS, ELECTRONICS, COMPUTER_OPS, HAND_TO_HAND, WP_RIFLE},
        .skill_percentages = {75, 70, 65, 50, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 47: NGR Mechanic */
    {
        .skill_ids = {MECHANICS, ELECTRONICS, COMPUTER_OPS, LITERACY, HAND_TO_HAND},
        .skill_percentages = {70, 65, 60, 65, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 48: Master Assassin */
    {
        .skill_ids = {HAND_TO_HAND, WP_PISTOL, ACROBATICS, TRACKING, WP_SWORD},
        .skill_percentages = {80, 75, 70, 65, 70},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 49: Kittani Warrior */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_SWORD, ACROBATICS, SURVIVAL},
        .skill_percentages = {70, 70, 65, 60, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 50: NGR Soldier */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_PISTOL, FIRST_AID, SURVIVAL},
        .skill_percentages = {65, 70, 60, 50, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 51: Knight (Europe) */
    {
        .skill_ids = {HAND_TO_HAND, WP_SWORD, ACROBATICS, LITERACY, SURVIVAL},
        .skill_percentages = {70, 75, 60, 60, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 10
    },
    
    /* 52: Royal Knight */
    {
        .skill_ids = {HAND_TO_HAND, WP_SWORD, ACROBATICS, LITERACY, WP_PISTOL},
        .skill_percentages = {75, 80, 65, 70, 60},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 15
    },
    
    /* 53: Professional Thief */
    {
        .skill_ids = {ACROBATICS, HAND_TO_HAND, WP_PISTOL, ELECTRONICS, COMPUTER_OPS},
        .skill_percentages = {70, 60, 55, 60, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 54: Forger */
    {
        .skill_ids = {LITERACY, COMPUTER_OPS, ELECTRONICS, HAND_TO_HAND, WP_PISTOL},
        .skill_percentages = {80, 70, 60, 45, 45},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 55: Smuggler */
    {
        .skill_ids = {HAND_TO_HAND, WP_PISTOL, COMPUTER_OPS, MECHANICS, SURVIVAL},
        .skill_percentages = {60, 65, 55, 55, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 56: Freelance Spy */
    {
        .skill_ids = {ACROBATICS, HAND_TO_HAND, WP_PISTOL, COMPUTER_OPS, ELECTRONICS},
        .skill_percentages = {65, 65, 60, 65, 55},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 57: ISS Peacekeeper */
    {
        .skill_ids = {HAND_TO_HAND, WP_PISTOL, WP_RIFLE, FIRST_AID, COMPUTER_OPS},
        .skill_percentages = {70, 65, 65, 50, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 58: ISS Specter */
    {
        .skill_ids = {HAND_TO_HAND, ACROBATICS, WP_PISTOL, ELECTRONICS, TRACKING},
        .skill_percentages = {75, 70, 70, 60, 60},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 59: NTSET Protector */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_PISTOL, COMPUTER_OPS, FIRST_AID},
        .skill_percentages = {70, 70, 65, 55, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 60: Pirate (S.A.) */
    {
        .skill_ids = {HAND_TO_HAND, WP_PISTOL, WP_SWORD, SWIMMING, SURVIVAL},
        .skill_percentages = {65, 65, 60, 70, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 61: Sailor (S.A.) */
    {
        .skill_ids = {SWIMMING, HAND_TO_HAND, SURVIVAL, MECHANICS, WP_PISTOL},
        .skill_percentages = {75, 55, 55, 50, 50},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    },
    
    /* 62: Gifted Gypsy */
    {
        .skill_ids = {MAGIC_NOVICE, LITERACY, HAND_TO_HAND, SURVIVAL, TRACKING},
        .skill_percentages = {70, 65, 50, 55, 50},
        .num_skills = 5,
        .starting_isp = 10,
        .starting_ppe = 25
    },
    
    /* 63: Sunaj Assassin (Limited) */
    {
        .skill_ids = {HAND_TO_HAND, WP_SWORD, ACROBATICS, WP_PISTOL, TRACKING},
        .skill_percentages = {85, 80, 75, 70, 70},
        .num_skills = 5,
        .starting_isp = 15,
        .starting_ppe = 20
    },
    
    /* 64: Maxi-Man (Limited) */
    {
        .skill_ids = {HAND_TO_HAND, WP_RIFLE, WP_PISTOL, ACROBATICS, SURVIVAL},
        .skill_percentages = {80, 75, 70, 70, 60},
        .num_skills = 5,
        .starting_isp = 5,
        .starting_ppe = 5
    }
};

/* ========== GLOBAL EXPORTS ========== */

SkillDef ALL_SKILLS[TOTAL_SKILLS];
int NUM_SKILLS = TOTAL_SKILLS;
OCCSkillPackage OCC_PACKAGES[65];

/* ========== INITIALIZATION ========== */

void skill_init(void) {
    size_t i;

    /* Copy skill database */
    for (i = 0; i < TOTAL_SKILLS; i++) {
        ALL_SKILLS[i] = SKILL_DATABASE[i];
    }

    /* Copy OCC packages */
    for (i = 0; i < 65; i++) {
        OCC_PACKAGES[i] = OCC_SKILL_PACKAGES[i];
    }

    DEBUG_LOG("Initialized %ld skills for 65 OCCs", (long)TOTAL_SKILLS);
}

/* ========== SKILL LOOKUPS ========== */

SkillDef *skill_get_by_id(int id) {
    if (id < 0 || (size_t)id >= TOTAL_SKILLS) return NULL;
    return &ALL_SKILLS[id];
}

SkillDef *skill_get_by_name(const char *name) {
    size_t i;

    if (!name || !name[0]) return NULL;

    for (i = 0; i < TOTAL_SKILLS; i++) {
        if (strcasecmp(ALL_SKILLS[i].name, name) == 0) {
            return &ALL_SKILLS[i];
        }
    }

    return NULL;
}

int skill_get_id_by_name(const char *name) {
    size_t i;

    if (!name || !name[0]) return -1;

    for (i = 0; i < TOTAL_SKILLS; i++) {
        if (strcasecmp(ALL_SKILLS[i].name, name) == 0) {
            return (int)i;
        }
    }

    return -1;
}

const char *skill_get_name(int skill_id) {
    if (skill_id < 0 || (size_t)skill_id >= TOTAL_SKILLS) return "Unknown";
    return ALL_SKILLS[skill_id].name;
}

/* ========== OCC SKILL ASSIGNMENT ========== */

/* OCC names aligned with OCC_SKILL_PACKAGES indices */
static const char *OCC_PACKAGE_NAMES[] = {
    "Cyber-Knight", "Ley Line Walker", "Rogue Scientist", "Techno-Wizard",
    "Battle Magus", "Biomancer", "Body Fixer", "Burster",
    "City Rat", "Cosmo-Knight", "Crazy", "Dragon Hatchling RCC",
    "Elemental Fusionist", "Full Conversion Borg", "Headhunter", "Juicer",
    "Line Walker", "Mercenary", "Mind Melter", "Mystic",
    "Necromancer", "Ninja", "Operator", "Power Armor Pilot",
    "Psi-Stalker", "Psychic", "Rifter", "Rogue Scholar",
    "Shifter", "Temporal Wizard", "Undead Slayer", "Vagabond",
    "Warrior Monk", "Wilderness Scout", "Zapper",
    "Atlantean Nomad", "Atlantean Slave", "Ninja Juicer", "Delphi Juicer",
    "Hyperion Juicer", "CS Ranger", "CS Technical Officer",
    "Air Warlock", "Tattooed Man", "Nega-Psychic", "Cyber-Doc",
    "Kittani Field Mechanic", "NGR Mechanic", "Master Assassin",
    "Kittani Warrior", "NGR Soldier", "Knight", "Royal Knight",
    "Professional Thief", "Forger", "Smuggler", "Freelance Spy",
    "ISS Peacekeeper", "ISS Specter", "NTSET Protector",
    "Pirate", "Sailor", "Gifted Gypsy", "Sunaj Assassin", "Maxi-Man"
};

void occ_assign_skills(PlayerSession *sess, const char *occ_name) {
    int occ_idx = -1;
    OCCSkillPackage *package;
    int i;

    if (!sess || !occ_name) return;

    /* Find OCC index by name in package names array */
    for (i = 0; i < 65; i++) {
        if (strcasecmp(OCC_PACKAGE_NAMES[i], occ_name) == 0) {
            occ_idx = i;
            break;
        }
    }

    if (occ_idx < 0) {
        fprintf(stderr, "[Skills] Unknown OCC: %s\n", occ_name);
        return;
    }

    package = &OCC_PACKAGES[occ_idx];
    
    /* Clear existing skills */
    memset(sess->character.skills, 0, sizeof(sess->character.skills));
    
    /* Assign skills from package */
    for (i = 0; i < package->num_skills && i < MAX_PLAYER_SKILLS; i++) {
        sess->character.skills[i].skill_id = package->skill_ids[i];
        sess->character.skills[i].percentage = package->skill_percentages[i];
        sess->character.skills[i].uses = 0;
    }
    
    sess->character.num_skills = package->num_skills;

    /* Apply per-race flat skill bonus (if present). This mirrors the intended
     * behavior from PROJECT-STATUS: add race_skill_bonus to every assigned
     * skill percentage and clamp to 100. */
    for (int i = 0; i < MAX_PLAYER_SKILLS; i++) {
        if (sess->character.race && sess->character.race_skill_bonus > 0) {
            sess->character.skills[i].percentage += sess->character.race_skill_bonus;
            if (sess->character.skills[i].percentage > 100)
                sess->character.skills[i].percentage = 100;
        }
    }
}

/* ========== SKILL CHECKS ========== */

int skill_check(int skill_percentage) {
    int roll = (rand() % 100) + 1;
    return (roll <= skill_percentage) ? 1 : 0;
}

// Returns the race-specific skill bonus for a given skill_id
// Looks up the race in loaded_races[] (populated by race_loader_scan_races)
#include "race_loader.h"
extern LoadedRace loaded_races[];
extern int num_loaded_races;

int race_skill_bonus(char *race, int skill_id) {
    /* The per-race flat skill bonus is stored on Character (populated by
     * race_loader.c via the VM bridge) as `race_skill_bonus`. The
     * LoadedRace struct (from race_loader.h) does not contain per-race
     * bonus fields, so avoid accessing a non-existent member here.
     *
     * Keep this helper for API compatibility; currently return 0 since
     * the character-level field should be used (sess->character.race_skill_bonus).
     */
    (void)race;
    (void)skill_id;
    return 0;
}

/* Session-aware wrapper: applies per-race flat % bonus (populated at chargen
 * via query_skill_bonus() LPC bridge) and performs the d100 roll. This keeps
 * the original `skill_check()` for compatibility while enabling race-bonus
 * behaviour.
 */
int skill_check_sess(PlayerSession *sess, int skill_id, int skill_percentage) {
    (void)skill_id; /* skill_id reserved for future per-skill overrides */
    if (sess && sess->character.race_skill_bonus > 0) {
        skill_percentage += sess->character.race_skill_bonus;
    }
    /* clamp between 0 and 100 */
    if (skill_percentage < 0) skill_percentage = 0;
    if (skill_percentage > 100) skill_percentage = 100;
    return skill_check(skill_percentage);
}

/* ========== DISPLAY FUNCTIONS ========== */

void skill_display_list(PlayerSession *sess) {
    int i, skill_id;
    SkillDef *skill;
    int w = FRAME_WIDTH;
    char buf[128];

    if (!sess) return;

    send_to_player(sess, "\r\n");
    frame_top(sess, w);
    frame_title(sess, "YOUR SKILLS", w);
    frame_sep(sess, w);

    if (sess->character.num_skills == 0) {
        frame_line(sess, "No skills learned yet.", w);
    } else {
        for (i = 0; i < sess->character.num_skills; i++) {
            skill_id = sess->character.skills[i].skill_id;
            skill = skill_get_by_id(skill_id);
            if (skill) {
                snprintf(buf, sizeof(buf), "%-32s %3d%%",
                         skill->name, sess->character.skills[i].percentage);
                frame_line(sess, buf, w);
            }
        }
    }

    frame_bottom(sess, w);
}

