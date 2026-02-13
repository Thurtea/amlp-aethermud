/*
 * wiz_tools.c - Implementation of wizard customization tools
 * 
 * Three core wizard tools:
 * 1. Staff of Demotion - Character demotion and reset
 * 2. RP-Wiz Skill Tool - O.C.C. and skill assignment
 * 3. Tattoo-Gun - Apply beneficial magical tattoos
 */

#include "wiz_tools.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "session_internal.h"
#include "vm.h"
#include "efun.h"
#include "driver.h"

/* Forward declarations for driver helpers used here (defined in driver.c) */
extern PlayerSession* find_player_by_name(const char *name);
extern void room_add_player(Room *room, PlayerSession *player);
extern void room_remove_player(Room *room, PlayerSession *player);
extern Room* room_get_by_path(const char *lpc_path);
extern Room* room_get_by_id(int id);
extern void room_broadcast(Room *room, const char *message, PlayerSession *exclude);
extern void cmd_look(PlayerSession *sess, const char *args);
extern int save_character(PlayerSession *sess);
extern void broadcast_message(const char *message, PlayerSession *exclude);
extern void send_to_player(PlayerSession *sess, const char *fmt, ...);
extern VMValue execute_command(PlayerSession *session, const char *command);
extern PlayerSession *sessions[];
extern VirtualMachine *global_vm;

/* Simple wizard action logger */
static void wiz_log(const char *fmt, ...) {
    FILE *f = fopen("logs/wizard.log", "a");
    if (!f) return;
    time_t now = time(NULL);
    char tbuf[32];
    struct tm *tm = localtime(&now);
    strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", tm);
    fprintf(f, "[%s] ", tbuf);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
    fprintf(f, "\n");
    fclose(f);
}

/* ------------------------------------------------------------------ */
/* Wizard/admin helper functions (wrap common driver admin actions) */

/* Teleport the wizard themselves to a room (by LPC path or numeric id) */
int wiz_goto(PlayerSession *sess, const char *room_arg) {
    /* Level 3 required for movement/visibility wizard actions */
    if (!sess || sess->privilege_level < 3 || !room_arg) return 0;
    Room *target = NULL;
    if (room_arg[0] == '/') {
        target = room_get_by_path(room_arg);
        if (!target) return 0;
    } else {
        int id = atoi(room_arg);
        target = room_get_by_id(id);
        if (!target) return 0;
    }

    if (sess->current_room) {
        room_remove_player(sess->current_room, sess);
        char leave_msg[256];
        snprintf(leave_msg, sizeof(leave_msg), "%s vanishes in a puff of smoke.\r\n", sess->username);
        room_broadcast(sess->current_room, leave_msg, NULL);
    }

    sess->current_room = target;
    room_add_player(target, sess);

    char arrive_msg[256];
    snprintf(arrive_msg, sizeof(arrive_msg), "%s appears in a puff of smoke.\r\n", sess->username);
    room_broadcast(target, arrive_msg, sess);

    cmd_look(sess, "");
    wiz_log("%s used goto -> %s", sess->username ? sess->username : "<unknown>", room_arg);
    return 1;
}

/* Summon another player into the wizard's current room */
int wiz_summon(PlayerSession *sess, const char *player_name) {
    /* Level 3 required for summon */
    if (!sess || sess->privilege_level < 3 || !player_name) return 0;
    if (!sess->current_room) return 0;
    PlayerSession *target = find_player_by_name(player_name);
    if (!target || target == sess) return 0;

    if (target->current_room) {
        char leave_msg[256];
        snprintf(leave_msg, sizeof(leave_msg), "%s vanishes in a flash of light.\r\n", target->username);
        room_broadcast(target->current_room, leave_msg, target);
        room_remove_player(target->current_room, target);
    }

    target->current_room = sess->current_room;
    room_add_player(sess->current_room, target);

    char arrive_msg[256];
    snprintf(arrive_msg, sizeof(arrive_msg), "%s appears in a flash of light.\r\n", target->username);
    room_broadcast(sess->current_room, arrive_msg, target);

    send_to_player(target, "You have been summoned by %s!\r\n", sess->username);
    cmd_look(target, "");
    wiz_log("%s summoned %s to room id=%d", sess->username ? sess->username : "<unknown>", target->username, sess->current_room ? sess->current_room->id : -1);
    return 1;
}

/* Teleport a player to a specified room (by path or id) */
int wiz_teleport(PlayerSession *sess, const char *player_name, const char *room_arg) {
    /* Level 4 required for player manipulation (teleport others) */
    if (!sess || sess->privilege_level < 4 || !player_name || !room_arg) return 0;
    PlayerSession *target = find_player_by_name(player_name);
    if (!target) return 0;

    Room *dest = NULL;
    if (room_arg[0] == '/') {
        dest = room_get_by_path(room_arg);
        if (!dest) return 0;
    } else {
        int id = atoi(room_arg);
        dest = room_get_by_id(id);
        if (!dest) return 0;
    }

    if (target->current_room) {
        char leave_msg[256];
        snprintf(leave_msg, sizeof(leave_msg), "%s vanishes in a flash of light.\r\n", target->username);
        room_broadcast(target->current_room, leave_msg, target);
        room_remove_player(target->current_room, target);
    }

    target->current_room = dest;
    room_add_player(dest, target);

    char arrive_msg[256];
    snprintf(arrive_msg, sizeof(arrive_msg), "%s appears in a flash of light.\r\n", target->username);
    room_broadcast(dest, arrive_msg, target);
    send_to_player(target, "You have been teleported by %s!\r\n", sess->username);
    cmd_look(target, "");
    wiz_log("%s teleported %s -> %s", sess->username ? sess->username : "<unknown>", target->username, room_arg);
    return 1;
}

/* Force a player to execute a command (admin-only) */
int wiz_force(PlayerSession *sess, const char *target_name, const char *command) {
    /* Level 4 required for forcing commands */
    if (!sess || sess->privilege_level < 4 || !target_name || !command) return 0;
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) return 0;
    if (target == sess) return 0;

    send_to_player(target, "%s forces you to: %s\r\n", sess->username, command);
    /* Execute command through existing driver path */
    VMValue res = execute_command(target, command);
    /* Release VM return value if any */
    if (res.type != VALUE_NULL) vm_value_release(&res);
    wiz_log("%s forced %s to: %s", sess->username ? sess->username : "<unknown>", target->username, command);
    return 1;
}

/* Initiate graceful server shutdown (admin-only). If delay_seconds > 0, announce it. */
int wiz_shutdown(PlayerSession *sess, int delay_seconds) {
    /* Level 5 required for destructive/dangerous ops */
    if (!sess || sess->privilege_level < 5) return 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i] && sessions[i]->state == STATE_PLAYING) {
            save_character(sessions[i]);
        }
    }

    char msg[256];
    if (delay_seconds > 0) {
        snprintf(msg, sizeof(msg), "[SYSTEM] Admin %s is shutting down the server in %d seconds. All characters saved.\r\n", sess->username, delay_seconds);
    } else {
        snprintf(msg, sizeof(msg), "[SYSTEM] Admin %s is shutting down the server NOW. All characters saved.\r\n", sess->username);
    }
    broadcast_message(msg, NULL);

    fprintf(stderr, "[Server] Shutdown initiated by %s\n", sess->username);
    server_running = 0;
    wiz_log("%s initiated shutdown (delay=%d)", sess->username ? sess->username : "<unknown>", delay_seconds);
    return 1;
}

/* Reload an LPC object or daemon via efun load_object */
int wiz_reload(PlayerSession *sess, const char *lpc_path) {
    /* Level 2: read-only / testing reloads */
    if (!sess || sess->privilege_level < 2 || !lpc_path) return 0;
    VMValue path_val = vm_value_create_string(lpc_path);
    VMValue res = efun_load_object(global_vm, &path_val, 1);
    vm_value_release(&path_val);
    /* If result is an object, consider successful; basic check: not null */
    if (res.type != VALUE_NULL) {
        vm_value_release(&res);
        wiz_log("%s reloaded %s", sess->username ? sess->username : "<unknown>", lpc_path);
        return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------ */

/* ============================================================================
 * O.C.C. SKILL CONFIGURATIONS (from Palladium Rifts)
 * ============================================================================ */

/* SOLDIER - Military Combat Specialist */
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
    .occ_related_max = 8,
    .secondary_max = 4,
};

/* MIND MELTER - Psychic Master */
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

/* LEY LINE WALKER - Mage */
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

/* ROGUE - Thief/Assassin */
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

/* WILDERNESS SCOUT - Ranger */
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

/* SCHOLAR - Academic/Researcher */
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

/* MERCHANT - Trader/Negotiator */
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

/* MYSTIC - Spiritual Practitioner */
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

/* DRAGON HATCHLING - Young Dragon Rider */
static OCCSkillConfig dragon_hatchling_config = {
    .occ_name = "Dragon Hatchling RCC",
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

/* OCC skill configuration lookup table */
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
    {"Dragon Hatchling RCC", &dragon_hatchling_config},
    {NULL, NULL}  /* Sentinel */
};

/* OCC pool skills - available for OCC-related and secondary selection */
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

/* ============================================================================
 * INITIALIZATION & DISCOVERY
 * ============================================================================ */

/**
 * skill_tool_init()
 * Initialize skill system configuration
 */
void skill_tool_init(void) {
    /* Load all OCC skill configs from wiz_tools.c */
    /* Currently static-loaded; could be expanded to load from data files */
}

/* ============================================================================
 * SKILL ASSIGNMENT TOOL (RP-WIZ SKILL TOOL)
 * ============================================================================ */

/**
 * cmd_skill_assign()
 * Assign an O.C.C. and initiate skill selection for a character
 * 
 * Syntax: rp-skill-assign <player> to <occ>
 * 
 * Steps:
 * 1. Find player character
 * 2. Verify O.C.C. exists and is valid
 * 3. Assign O.C.C. and primary skills
 * 4. Create skill assignment session for wizard guidance
 */
int cmd_skill_assign(PlayerSession *sess, const char *player_name, const char *occ_name) {
    if (!sess || !player_name || !occ_name) {
        return 0;
    }
    
    /* TODO: Implement player lookup */
    /* TODO: Implement OCC verification */
    /* TODO: Implement primary skill assignment */
    /* TODO: Create skill assignment request for tracking */
    
    return 1;
}

/* ============================================================================
 * STAFF OF DEMOTION (DEMOTION TOOL)
 * ============================================================================ */

/**
 * cmd_demotion()
 * Demote a character, optionally resetting O.C.C. and skills
 * 
 * Syntax: staff-of-demotion <player> level <n>
 * Syntax: staff-of-demotion <player> strip-occ
 * Syntax: staff-of-demotion <player> reset-skills
 * 
 * Actions:
 * - lower level: Reduces character level and adjusts HP/spell points
 * - strip-occ: Resets O.C.C. to "Awaiting Wizard Assignment"
 * - reset-skills: Resets character skills to base values
 */
int cmd_demotion(PlayerSession *sess, const char *player_name, const char *action, int value) {
    if (!sess || !player_name || !action) {
        return 0;
    }
    
    /* TODO: Implement player lookup */
    /* TODO: Implement level demotion */
    /* TODO: Implement OCC stripping */
    /* TODO: Implement skill reset */
    /* TODO: Log demotion action */
    
    return 1;
}

/* ============================================================================
 * TATTOO-GUN (MAGICAL TATTOO TOOL)
 * ============================================================================ */

/**
 * cmd_tattoo_gun()
 * Apply or remove magical tattoos to characters
 * 
 * Syntax: tattoo-gun show <player>     - Display current tattoos
 * Syntax: tattoo-gun list              - List available tattoos
 * Syntax: tattoo-gun apply <player> <tattoo> - Apply a tattoo
 * Syntax: tattoo-gun remove <player> <tattoo> - Remove a tattoo
 * 
 * Current tattoo types (FOUNDATION - EXPAND):
 * - Atlantean Dragon: +15% to all combat skills, +2 STR
 * - Ley Line Mark: +10% spell casting, +10% PPE pool
 * - Shifter Seal: +5% physical skills, shape-shifting affinity
 * - Mystic Rune: +5% all magic, +15% PPE pool
 */
int cmd_tattoo_gun(PlayerSession *sess, const char *action, 
                   const char *player_name, const char *tattoo_name) {
    if (!sess || !action) {
        return 0;
    }
    
    if (strcmp(action, "list") == 0) {
        /* Tattoo list would be displayed via output system */
        return 1;
    }
    
    /* TODO: Implement show tattoos */
    /* TODO: Implement apply tattoo */
    /* TODO: Implement remove tattoo */
    /* TODO: Validate tattoo applicability to O.C.C. */
    /* TODO: Log tattoo applications */
    
    return 1;
}

/* ============================================================================
 * SKILL CONFIGURATION UTILITIES
 * ============================================================================ */

/**
 * get_occ_skill_config()
 * Retrieve the skill configuration for a given O.C.C.
 * Returns NULL if not found
 */
OCCSkillConfig *get_occ_skill_config(const char *occ_name) {
    if (!occ_name) return NULL;
    
    for (int i = 0; skill_configs[i].occ_name != NULL; i++) {
        if (strcmp(skill_configs[i].occ_name, occ_name) == 0) {
            return skill_configs[i].config;
        }
    }
    
    return NULL;
}

/**
 * get_skill_definition()
 * Look up a skill in the OCC pool
 */
const SkillDef *get_skill_definition(const char *skill_name) {
    if (!skill_name) return NULL;
    
    for (int i = 0; occ_pool_skills[i].skill_name != NULL; i++) {
        if (strcmp(occ_pool_skills[i].skill_name, skill_name) == 0) {
            return &occ_pool_skills[i];
        }
    }
    
    return NULL;
}

/**
 * validate_skill_assignment()
 * Check if a skill assignment is valid for the O.C.C.
 * - Validates OCC has slots available
 * - Validates skill exists
 * - Validates percentage is in valid range
 */
int validate_skill_assignment(const char *occ_name, const char *skill_name, 
                              int skill_type, int count_used) {
    OCCSkillConfig *config = get_occ_skill_config(occ_name);
    if (!config) {
        return 0;  /* Invalid O.C.C. */
    }
    
    /* Check against maximum allowed */
    if (skill_type == 'O' && count_used >= config->occ_related_max) {
        return 0;  /* OCC-related skill quota exceeded */
    }
    
    if (skill_type == 'S' && count_used >= config->secondary_max) {
        return 0;  /* Secondary skill quota exceeded */
    }
    
    /* Verify skill exists */
    if (!get_skill_definition(skill_name)) {
        return 0;  /* Skill not found */
    }
    
    return 1;  /* Valid */
}

/**
 * assign_primary_skills()
 * Assign all primary skills for an O.C.C.
 * These are mandatory and don't require wizard selection
 */
int assign_primary_skills(Character *player, const char *occ_name) {
    OCCSkillConfig *config = get_occ_skill_config(occ_name);
    if (!config) {
        return 0;
    }
    
    /* TODO: Actually assign skills to player object */
    /* For now, just verify structure works */
    
    return config->primary_count;
}

/* ============================================================================
 * DEBUG & UTILITY FUNCTIONS
 * ============================================================================ */

/**
 * display_occ_skills()
 * Show all skills for an O.C.C. (for wizard reference)
 */
void display_occ_skills(PlayerSession *sess, const char *occ_name) {
    OCCSkillConfig *config = get_occ_skill_config(occ_name);
    
    if (!config) {
        return;
    }
    
    /* Output would be sent through the session/output system */
    /* TODO: Implement output via session system */
}

