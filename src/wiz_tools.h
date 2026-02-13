/*
 * wiz_tools.h - Wizard command tools for character customization
 * 
 * Three primary wiz-tools for managing character development:
 * 1. Staff of Demotion - Demote/strip characters, adjust levels and skills
 * 2. RP-Wiz Skill Tool - Assign/modify primary, OCC-related, and secondary skills
 * 3. Tattoo-Gun - Apply magical tattoos (Atlantean clan selection, bonuses)
 */

#ifndef WIZ_TOOLS_H
#define WIZ_TOOLS_H

/* Forward declarations */
typedef struct PlayerSession PlayerSession;

/* ============================================================================
 * SKILL ASSIGNMENT FRAMEWORK
 * ============================================================================
 * 
 * Skills are categorized per Palladium Rifts mechanics:
 * - Primary Skills: 8-15 per OCC, +5-30% bonus, advance +3-5%/level
 * - OCC-Related: 6-12 selectable, +10-20% bonus, +1-2 at levels 3/6/9/12/15
 * - Secondary: 4-8 selectable, base %, +1-2 per level
 */

#define MAX_PRIMARY_SKILLS 15
#define MAX_OCC_RELATED_SKILLS 12
#define MAX_SECONDARY_SKILLS 8

typedef struct {
    char *skill_name;
    int base_percent;      /* Starting skill percentage */
    int level_bonus;       /* Additional % per level */
    int max_occ_slots;     /* How many OCC-related slots this requires */
    int is_mandatory;      /* 1 if all members of OCC must have it */
} WizSkillDef;

typedef struct {
    char *occ_name;
    int primary_count;        /* Number of primary skills */
    WizSkillDef primary_skills[MAX_PRIMARY_SKILLS];
    int occ_related_max;       /* Max selectable OCC-related skills */
    int secondary_max;         /* Max selectable secondary skills */
} OCCSkillConfig;

typedef struct {
    char *skill_name;
    int current_percent;
    int base_percent;
    int level_bonus;
    char skill_type;  /* 'P' = primary, 'O' = OCC-related, 'S' = secondary */
} CharacterSkill;

/* ============================================================================
 * STAFF OF DEMOTION
 * ============================================================================
 */

typedef struct {
    char *target_player;
    int new_level;
    int strip_occ;             /* 1 = demote character to unassigned OCC */
    int reset_skills;          /* 1 = reset to base skill values */
} DemotionRequest;

/*
 * cmd_staff_of_demotion()
 * 
 * Syntax: staff-of-demotion <player> level <#>
 * Syntax: staff-of-demotion <player> strip-occ
 * Syntax: staff-of-demotion <player> reset-skills
 * 
 * Tasks:
 * - Lower character level and adjust hit points/spell points
 * - Optional: Demote back to unassigned OCC
 * - Optional: Reset OCC-based skills to base values
 */

/* ============================================================================
 * RP-WIZ SKILL TOOL
 * ============================================================================
 */

typedef struct {
    char *player_name;
    char *occ_name;                        /* OCC being assigned */
    WizSkillDef selected_skills[MAX_OCC_RELATED_SKILLS];  /* Selected OCC-related */
    int selected_count;                    /* Count of selected */
    WizSkillDef selected_secondary[MAX_SECONDARY_SKILLS]; /* Selected secondary */
    int secondary_count;
} CharacterSkillAssignment;

/*
 * cmd_rp_wiz_skill_tool()
 * 
 * Syntax: rp-skill-assign <player> to <occ>
 * Syntax: rp-skill-tool <player> show
 * Syntax: rp-skill-tool <player> add <skill> [percent]
 * Syntax: rp-skill-tool <player> remove <skill>
 * Syntax: rp-skill-tool <player> commit
 * 
 * Tasks:
 * - Assign primary skills (mandatory per OCC)
 * - Guide wizard through OCC-related skill selection
 * - Guide wizard through secondary skill selection
 * - Validate percentages and constraints
 * - Commit final skill configuration to character
 */

/* ============================================================================
 * TATTOO-GUN
 * ============================================================================
 */

typedef struct {
    char *tattoo_name;
    char *description;
    char applies_to_occ[32];   /* "all", or specific OCC name */
    int bonus_percent;         /* Permanent bonus to a skill */
    int bonus_damage;          /* Combat damage bonus */
    int bonus_attribute;       /* Ability score bonus */
    char target_ability[16];   /* "STR", "DEX", "CON", etc. */
} TattooType;

typedef struct {
    TattooType tattoo;
    char *applied_by_wizard;   /* Wizard who applied */
    long applied_timestamp;
} CharacterTattoo;

/*
 * cmd_tattoo_gun()
 * 
 * Syntax: tattoo-gun show <player>
 * Syntax: tattoo-gun list
 * Syntax: tattoo-gun apply <player> <tattoo-name>
 * Syntax: tattoo-gun remove <player> <tattoo-name>
 * 
 * Current Tattoos (Foundation - expand per game design):
 * - Atlantean Dragon: +15% to combat skills, +2 to STR
 * - Ley Line Mark: +10% to spell casting, +10% to PPE pool
 * - Shifter Seal: +5% to physical skills, shape-shifting affinity
 * - Mystic Rune: +5% to all magic, +15% PPE pool
 */

/* ============================================================================
 * WIZ-TOOL COMMAND DISPATCHER
 * ============================================================================
 */

typedef enum {
    WIZ_TOOL_SKILL_ASSIGN,
    WIZ_TOOL_DEMOTION,
    WIZ_TOOL_TATTOO
} WizToolType;

typedef struct {
    WizToolType tool_type;
    void *request;          /* Pointer to specific tool request struct */
} WizToolCommand;

/* Function declarations */
void skill_tool_init(void);
int cmd_skill_assign(PlayerSession *sess, const char *occ, const char *player);
int cmd_demotion(PlayerSession *sess, const char *player, const char *action, int value);
int cmd_tattoo_gun(PlayerSession *sess, const char *action, const char *player, const char *tattoo);
int cmd_promotion(PlayerSession *sess, const char *player, int new_level);

/* Additional wizard helper prototypes */
int wiz_snoop(PlayerSession *sess, const char *target_name, int enable);
int wiz_invisible(PlayerSession *sess, int enable);
int wiz_set_stat(PlayerSession *sess, const char *target_name, const char *stat, int value);
int wiz_grant_xp(PlayerSession *sess, const char *target_name, int xp_amount);
int wiz_heal(PlayerSession *sess, const char *target_name);
int wiz_clone(PlayerSession *sess, const char *lpc_path, const char *target_name);

/* Skill configuration loader */
OCCSkillConfig *get_occ_skill_config(const char *occ_name);

#endif /* WIZ_TOOLS_H */
