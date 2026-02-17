#ifndef CHARGEN_H
#define CHARGEN_H

#include <stddef.h>
#include "item.h"
#include "psionics.h"
#include "magic.h"

/* Forward declare from session_internal.h */
typedef struct PlayerSession PlayerSession;

/* Forward declare skill structures */
typedef struct {
    int skill_id;
    int percentage;
    int uses;
} PlayerSkill;

/* Character generation states */
typedef enum {
    CHARGEN_RACE_SELECT,
    CHARGEN_STATS_ROLL,
    CHARGEN_STATS_CONFIRM,
    CHARGEN_ALIGNMENT_SELECT,
    CHARGEN_ZONE_SELECT,
    CHARGEN_SECONDARY_SKILLS,
    CHARGEN_COMPLETE
} ChargenState;

/* Character stats (Palladium RPG) */
typedef struct {
    int iq;   /* Intelligence Quotient */
    int me;   /* Mental Endurance */
    int ma;   /* Mental Affinity */
    int ps;   /* Physical Strength */
    int pp;   /* Physical Prowess */
    int pe;   /* Physical Endurance */
    int pb;   /* Physical Beauty */
    int spd;  /* Speed */
} CharacterStats;

/* Character data */
/* Phase 1: Extended health / energy systems */
typedef enum {
    HP_SDC = 0,   /* Standard HP + SDC model */
    MDC_ONLY,     /* Use MDC values only (mega-damage creatures) */
    HP_ONLY       /* Only HP (no SDC) */
} HealthType;

/* Lives and scars (death system) */
#define MAX_SCARS 5
typedef struct Scar {
    char location[64];
    char description[128];
    int death_number;
} Scar;

typedef struct Character {
    char *race;
    char *occ;
    int level;
    int xp;
    int hp;
    int max_hp;
    int sdc;
    int max_sdc;
    CharacterStats stats;
    
    /* Skills system (Phase 2) */
    PlayerSkill skills[20];     /* Max 20 skills per character */
    int num_skills;             /* Number of skills learned */
    
    /* Equipment & Inventory system (Phase 4) */
    Inventory inventory;        /* Carried items */
    EquipmentSlots equipment;   /* Equipped items */
    
    /* Psionics system (Phase 5) */
    PsionicAbilities psionics;  /* Psionic powers and ISP pool */
    
    /* Magic system (Phase 5) */
    MagicAbilities magic;       /* Magic spells and PPE pool */
    
    HealthType health_type;    /* Which health model this character uses */
    int mdc;                   /* Current mega-damage capacity */
    int max_mdc;               /* Max mega-damage capacity */

    int isp;                   /* Current ISP (alternate to psionics.isp_current) */
    int max_isp;               /* Max ISP */

    int ppe;                   /* Current PPE (alternate to magic.ppe_current) */
    int max_ppe;               /* Max PPE */

    /* Natural weapons for creatures (claws, bite, etc.) */
    char *natural_weapons[8];
    int natural_weapon_count;

    /* Tracks which players this character has been introduced to */
    char *introduced_to[32];
    int introduced_count;

    /* Real-time combat attributes (loaded from race files) */
    int attacks_per_round;     /* Total attacks per melee round (base 2 for most) */
    int parries_per_round;     /* Total parries per melee round */
    int racial_auto_parry;     /* Race grants auto-parry (from LPC file) */
    int racial_auto_dodge;     /* Race grants auto-dodge (from LPC file) */
    int auto_parry_enabled;    /* Player toggle: 1=on, 0=off (default on) */
    int auto_dodge_enabled;    /* Player toggle: 1=on, 0=off (default on) */
    int wimpy_threshold;       /* Auto-flee at this % of max HP (0=disabled) */
    int credits;               /* Universal credits (currency) */
    char *clan;                /* Clan membership (e.g., "aerihman" for Sunaj) */
    char *alignment;           /* Character alignment (e.g., "Principled") */

    /* Language system */
    char *languages[16];       /* Known languages (max 16) */
    int num_languages;         /* Number of known languages */
    char *current_language;    /* Default language for say command */
        /* Lives and scars (death system) */
    
        int lives_remaining;      /* Remaining lives (starts at 5) */
        /* scars array and Scar type are defined above the Character struct */
        Scar scars[MAX_SCARS];
        int scar_count;
    char *description;            /* Player-written character description */
    char *position;               /* Custom position text (default: "is standing around") */

    /* Metamorphosis (session-only, not saved) */
    char *true_race;              /* Original race before metamorph (NULL = not metamorphed) */
    int metamorph_active;         /* 1 if currently shape-shifted */

    /* Pre-promotion backup (for demotion) */
    char *original_race;          /* Race before becoming wizard */
    char *original_occ;           /* O.C.C. before becoming wizard */
    int original_hp_max;          /* HP before wizard transformation */
    int original_mdc_max;         /* MDC before wizard transformation */
} Character;

/* Chargen initialization */
void chargen_init(PlayerSession *sess);

/* Create admin character (skip chargen for first player) */
void chargen_create_admin(PlayerSession *sess);

/* Death handler (implemented in src/death.c) */
void handle_player_death(struct PlayerSession *sess, struct PlayerSession *killer);

/* Chargen state machine */
void chargen_process_input(PlayerSession *sess, const char *input);

/* Helper functions */
int roll_3d6(void);
int roll_1d6(void);
void chargen_roll_stats(PlayerSession *sess);
void chargen_display_stats(PlayerSession *sess);
void chargen_complete(PlayerSession *sess);

/* Commands */
void cmd_stats(PlayerSession *sess, const char *args);
void cmd_skills(PlayerSession *sess, const char *args);
void cmd_attack(PlayerSession *sess, const char *args);
void cmd_strike(PlayerSession *sess, const char *args);
void cmd_shoot(PlayerSession *sess, const char *args);
void cmd_dodge(PlayerSession *sess, const char *args);
void cmd_flee(PlayerSession *sess, const char *args);

/* Item commands (Phase 4) */
void cmd_inventory(PlayerSession *sess, const char *args);
void cmd_equip(PlayerSession *sess, const char *args);
void cmd_unequip(PlayerSession *sess, const char *args);
void cmd_worn(PlayerSession *sess, const char *args);
void cmd_get(PlayerSession *sess, const char *args);
void cmd_drop(PlayerSession *sess, const char *args);

/* Psionics commands (Phase 5) */
void cmd_use_power(PlayerSession *sess, const char *args);
void cmd_powers(PlayerSession *sess, const char *args);
void cmd_isp(PlayerSession *sess, const char *args);

/* Clan command */
void cmd_clan(PlayerSession *sess, const char *args);

/* Swim command */
void cmd_swim(PlayerSession *sess, const char *args);

/* Metamorph command (dragon shapeshifting) */
void cmd_metamorph(PlayerSession *sess, const char *args);

/* Language commands */
void cmd_speak(PlayerSession *sess, const char *args);
void cmd_languages(PlayerSession *sess, const char *args);

/* Wizard grant/revoke commands */
void cmd_grant(PlayerSession *sess, const char *args);
void cmd_revoke(PlayerSession *sess, const char *args);

/* Magic commands (Phase 5) */
void cmd_cast(PlayerSession *sess, const char *args);
void cmd_spells(PlayerSession *sess, const char *args);
void cmd_ppe(PlayerSession *sess, const char *args);
void cmd_meditate(PlayerSession *sess, const char *args);

/* Character persistence */
int save_character(PlayerSession *sess);
int load_character(PlayerSession *sess, const char *username);
int character_exists(const char *username, char *found_name, size_t found_size);
int any_saved_players(void);

#endif /* CHARGEN_H */

