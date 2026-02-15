#include "chargen.h"
#include "session_internal.h"
#include "room.h"
#include "skills.h"
#include "combat.h"
#include "race_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>
#include "debug.h"
#include "ui_frames.h"
#include <stdint.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

/* External function from session.c */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* External from driver.c - find a player session by name */
extern PlayerSession* find_player_by_name(const char *name);

/* External from room.c - movement command */
extern void cmd_move(PlayerSession *sess, const char *direction);

/* ========== RACE DATABASE - dynamically loaded from lib/races/*.lpc ========== */
/* loaded_races[] and num_loaded_races are populated by race_loader_scan_races()
 * at startup.  See race_loader.c for the scanning logic. */

/* MERGED OCC DATABASE - Rifts + AetherMUD (65 Total) */
const RaceOCCInfo ALL_OCCS[] = {
    /* Atlantean Specialists */
    {"Atlantean Nomad", "Wandering Atlantean explorer"},
    {"Atlantean Slave", "Enslaved Atlantean survivor"},
    
    /* Combat & Military OCCs */
    {"Cyber-Knight", "Techno-warrior with psionic powers"},
    {"Juicer", "Chemical-enhanced super soldier"},
    {"Ninja Juicer", "Stealth-enhanced juicer assassin"},
    {"Delphi Juicer", "Intelligence-boosted juicer variant"},
    {"Hyperion Juicer", "Enhanced strength juicer type"},
    {"Crazy", "Augmented insane super soldier"},
    {"Headhunter", "Bounty hunter, armor specialist"},
    {"Glitter Boy Pilot", "Elite powered armor operator"},
    {"Full Conversion Borg", "Complete cyborg conversion"},
    {"Special Forces", "Elite military operative (Merc)"},
    
    /* Coalition States Military */
    {"CS Grunt", "Coalition infantry soldier"},
    {"CS Ranger", "Coalition wilderness specialist"},
    {"CS Military Specialist", "Coalition technical expert"},
    {"CS SAMAS RPA Pilot", "Coalition flying armor pilot"},
    {"CS Technical Officer", "Coalition tech specialist"},
    
    /* Magic Users */
    {"Ley Line Walker", "Master of magical energies"},
    {"Line Walker", "Ley line manipulator"},
    {"Warlock", "Elemental pact magic user"},
    {"Air Warlock", "Air elemental magic specialist"},
    {"Mystic", "Spiritual magic user"},
    {"Techno-Wizard", "Blend of magic and technology"},
    {"Battle Magus", "Combat mage, magic and weapons"},
    {"Biomancer", "Life magic specialist"},
    {"Necromancer", "Death magic practitioner"},
    {"Stone Master", "Earth and stone magic user"},
    {"Temporal Wizard", "Time magic specialist"},
    {"Shifter", "Dimensional magic specialist"},
    {"Elemental Fusionist", "Combines elemental magic"},
    {"Tattooed Man", "Tattoo magic warrior"},
    
    /* Psychics */
    {"Mind Melter", "Master psychic disciplines"},
    {"Burster", "Pyrokinetic psychic warrior"},
    {"Psi-Healer", "Psychic healing specialist"},
    {"Psi-Stalker", "Anti-magic psionic hunter"},
    {"Nega-Psychic", "Psychic nullifier"},
    
    /* Technical & Medical */
    {"Body Fixer", "Cybernetic doctor and surgeon"},
    {"Cyber-Doc", "Advanced cybernetics specialist"},
    {"Operator", "Mechanical genius, vehicle expert"},
    {"Rogue Scientist", "Tech expert and inventor"},
    {"Rogue Scholar", "Knowledge seeker, multi-skilled"},
    {"Kittani Field Mechanic", "Alien tech specialist"},
    {"NGR Mechanic", "New German Republic technician"},
    
    /* Wilderness & Survival */
    {"Wilderness Scout", "Tracker and survivalist"},
    {"Vagabond", "Jack-of-all-trades wanderer"},
    {"City Rat", "Urban survivor, street smart"},
    
    /* Specialized Soldiers */
    {"Bounty Hunter", "Professional manhunter"},
    {"Master Assassin", "Elite silent killer"},
    {"Kittani Warrior", "Alien combat specialist"},
    {"NGR Soldier", "New German Republic trooper"},
    {"Knight", "European noble warrior"},
    {"Royal Knight", "Elite European knight"},
    
    /* Criminal & Underworld */
    {"Professional Thief", "Master burglar and pickpocket"},
    {"Forger", "Document and art counterfeiter"},
    {"Smuggler", "Black market transporter"},
    {"Freelance Spy", "Independent intelligence agent"},
    
    /* ISS (Iron Star Security) */
    {"ISS Peacekeeper", "Iron Star law enforcer"},
    {"ISS Specter", "Iron Star covert operative"},
    {"NTSET Protector", "NTSET security specialist"},
    
    /* Naval & Piracy */
    {"Pirate", "South American sea raider"},
    {"Sailor", "South American seaman"},
    
    /* Special & Unique */
    {"Gifted Gypsy", "Fortune-telling wanderer"},
    {"Sunaj Assassin", "Elite Atlantean assassin (Limited)"},
    {"Maxi-Man", "Bio-enhanced super soldier (Limited)"},
    {"Cosmo-Knight", "Cosmic power armor knight"},
    {"Power Armor Pilot", "Elite mech pilot"},
    {"Robot Pilot", "Giant robot operator"},
    {"Sea Titan", "Ocean-based warrior"},
    {"Dragon Hatchling RCC", "Young dragon racial class"},
    {"Anarchist", "Anti-establishment rebel"},
    {"Horror Factor", "Fear-inducing specialist"},
    {"Mercenary", "Professional soldier for hire"},
    {"Palmer", "Dimensional traveler"}
};

#define NUM_RACES_VAR num_loaded_races
#define NUM_OCCS (sizeof(ALL_OCCS) / sizeof(RaceOCCInfo))
#define ITEMS_PER_PAGE 10

/* Dice rolling */
int roll_3d6(void) {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    return (rand() % 6 + 1) + (rand() % 6 + 1) + (rand() % 6 + 1);
}

int roll_1d6(void) {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    return (rand() % 6 + 1);
}

/* Add a language to character (returns 1 if added, 0 if already known or full) */
static int character_add_language(Character *ch, const char *lang) {
    if (!ch || !lang) return 0;
    /* Check if already known */
    for (int i = 0; i < ch->num_languages; i++) {
        if (ch->languages[i] && strcasecmp(ch->languages[i], lang) == 0)
            return 0;
    }
    if (ch->num_languages >= 16) return 0;
    ch->languages[ch->num_languages] = strdup(lang);
    ch->num_languages++;
    if (!ch->current_language) {
        ch->current_language = strdup(lang);
    }
    return 1;
}

/* Assign starting languages based on race */
static void assign_starting_languages(Character *ch) {
    if (!ch || !ch->race) return;
    const char *race = ch->race;

    /* Dragons get dragonese + american */
    if (strcasestr(race, "Dragon") != NULL) {
        character_add_language(ch, "dragonese");
        character_add_language(ch, "american");
    }
    /* Elves get elven + american */
    else if (strcasecmp(race, "Elf") == 0 || strcasestr(race, "Night-Elves") != NULL) {
        character_add_language(ch, "elven");
        character_add_language(ch, "american");
    }
    /* Dwarves get dwarven + american */
    else if (strcasecmp(race, "Dwarf") == 0) {
        character_add_language(ch, "dwarven");
        character_add_language(ch, "american");
    }
    /* Faerie types get faerie + american */
    else if (strcasestr(race, "Faerie") != NULL || strcasestr(race, "Pixie") != NULL ||
             strcasestr(race, "Sprite") != NULL || strcasestr(race, "Brownie") != NULL ||
             strcasestr(race, "Bogie") != NULL) {
        character_add_language(ch, "faerie");
        character_add_language(ch, "american");
    }
    /* Goblins get gobblely + american */
    else if (strcasestr(race, "Goblin") != NULL || strcasestr(race, "Hobgoblin") != NULL ||
             strcasestr(race, "Ogre") != NULL || strcasestr(race, "Troll") != NULL) {
        character_add_language(ch, "gobblely");
        character_add_language(ch, "american");
    }
    /* Atlantean types get american + euro */
    else if (strcasestr(race, "Atlantean") != NULL) {
        character_add_language(ch, "american");
        character_add_language(ch, "euro");
    }
    /* Demons/Deevils get demonic + american */
    else if (strcasestr(race, "Demon") != NULL || strcasestr(race, "Deevil") != NULL) {
        character_add_language(ch, "demonic");
        character_add_language(ch, "american");
    }
    /* Splugorth get demonic + american */
    else if (strcasestr(race, "Splugorth") != NULL || strcasestr(race, "Splynn") != NULL) {
        character_add_language(ch, "demonic");
        character_add_language(ch, "american");
    }
    /* Default: american */
    else {
        character_add_language(ch, "american");
    }
}

/* Create the wizard workroom LPC file on disk if it doesn't exist.
 * Returns 1 on success (or already exists), 0 on failure. */
static int create_wizard_workroom(const char *username) {
    if (!username || !username[0]) return 0;

    /* Build lowercase username for path */
    char lower_name[64];
    for (int i = 0; username[i] && i < 63; i++)
        lower_name[i] = tolower((unsigned char)username[i]);
    lower_name[strlen(username) < 63 ? strlen(username) : 63] = '\0';

    /* Create directory: lib/domains/wizard/<username>/ */
    char dir_path[512];
    snprintf(dir_path, sizeof(dir_path), "lib/domains/wizard/%s", lower_name);

    struct stat st;
    if (stat(dir_path, &st) != 0) {
        /* Create lib/domains/wizard/ first if needed */
        char parent[512];
        snprintf(parent, sizeof(parent), "lib/domains/wizard");
        mkdir(parent, 0755);
        if (mkdir(dir_path, 0755) != 0 && errno != EEXIST) {
            fprintf(stderr, "[Chargen] Failed to create wizard dir '%s': %s\n",
                    dir_path, strerror(errno));
            return 0;
        }
    }

    /* Create workroom.lpc */
    char file_path[512];
    snprintf(file_path, sizeof(file_path), "%s/workroom.lpc", dir_path);

    if (stat(file_path, &st) == 0) {
        return 1; /* Already exists */
    }

    FILE *f = fopen(file_path, "w");
    if (!f) {
        fprintf(stderr, "[Chargen] Failed to create workroom '%s': %s\n",
                file_path, strerror(errno));
        return 0;
    }

    fprintf(f,
        "// %s's Wizard Workroom\n"
        "inherit \"/lib/std/room.lpc\";\n"
        "\n"
        "void create() {\n"
        "    ::create();\n"
        "    set_short(\"%s's Workroom\");\n"
        "    set_long(\n"
        "        \"A private wizard's workroom. Arcane symbols cover the walls\\n\"\n"
        "        \"and a large desk sits in the center, covered in scrolls and\\n\"\n"
        "        \"strange devices. A wooden chest sits in the corner, marked\\n\"\n"
        "        \"with arcane symbols. A shimmering portal leads back to the world.\"\n"
        "    );\n"
        "    add_exit(\"out\", \"/domains/new_camelot/town_square\");\n"
        "    set_property(\"light\", 2);\n"
        "    set_property(\"indoors\", 1);\n"
        "}\n",
        username, username);

    fclose(f);
    fprintf(stderr, "[Chargen] Created wizard workroom: %s\n", file_path);
    return 1;
}

/* Create admin character, skipping chargen entirely */
void chargen_create_admin(PlayerSession *sess) {
    if (!sess) return;

    Character *ch = &sess->character;

    /* Set race only - no OCC for admin (assign later via 'set') */
    ch->race = strdup("Human");
    ch->occ = NULL;

    /* Solid baseline stats (all 15) */
    ch->stats.iq = 15;
    ch->stats.me = 15;
    ch->stats.ma = 15;
    ch->stats.ps = 15;
    ch->stats.pp = 15;
    ch->stats.pe = 15;
    ch->stats.pb = 15;
    ch->stats.spd = 15;

    /* Derived pools */
    ch->level = 1;
    ch->xp = 0;
    ch->hp = ch->stats.pe + roll_1d6();
    ch->max_hp = ch->hp;
    ch->sdc = 20;
    ch->max_sdc = 20;
    ch->health_type = HP_SDC;
    ch->mdc = 0;
    ch->max_mdc = 0;
    ch->isp = 0;
    ch->max_isp = 0;
    ch->ppe = 0;
    ch->max_ppe = 0;
    ch->credits = 1000;
    ch->alignment = strdup("Scrupulous");
    ch->clan = NULL;

    /* Lives */
    ch->lives_remaining = 5;
    ch->scar_count = 0;

    /* Combat defaults */
    ch->attacks_per_round = 2;
    ch->parries_per_round = 2;
    ch->racial_auto_parry = 0;
    ch->racial_auto_dodge = 0;
    ch->auto_parry_enabled = 1;
    ch->auto_dodge_enabled = 1;
    ch->wimpy_threshold = 0;

    /* Natural weapons */
    ch->natural_weapon_count = 0;

    /* Introduced list */
    ch->introduced_count = 0;

    /* No skills for admin - assign via OCC later */
    ch->num_skills = 0;

    /* Initialize inventory and equipment */
    inventory_init(&ch->inventory, ch->stats.ps);
    equipment_init(&ch->equipment);

    /* Initialize psionics and magic (empty pools) */
    psionics_init_abilities(ch);
    magic_init_abilities(ch);

    /* Starting language */
    assign_starting_languages(ch);

    /* No starting gear for admin */

    /* Create wizard workroom and place admin there */
    char lower_name[64];
    for (int i = 0; sess->username[i] && i < 63; i++)
        lower_name[i] = tolower((unsigned char)sess->username[i]);
    lower_name[strlen(sess->username) < 63 ? strlen(sess->username) : 63] = '\0';

    char workroom_path[256];
    snprintf(workroom_path, sizeof(workroom_path),
             "/domains/wizard/%s/workroom", lower_name);

    if (create_wizard_workroom(sess->username)) {
        Room *workroom = room_get_by_path(workroom_path);
        if (workroom) {
            sess->current_room = workroom;
            room_add_player(workroom, sess);

            /* Place wiz-tool items in workroom */
            /* Chest (non-pickable container) */
            Item *chest = (Item*)calloc(1, sizeof(Item));
            chest->id = -1;
            chest->name = strdup("wizard's chest");
            chest->description = strdup(
                "A sturdy oak chest with arcane symbols carved into its lid.\n"
                "The symbols pulse faintly with residual magical energy.\n"
                "Type 'look in chest' or 'examine chest' to see its contents.");
            chest->type = ITEM_MISC;
            chest->weight = 999;  /* Too heavy to pick up */
            chest->value = 0;
            room_add_item(workroom, chest);

            /* Staff */
            Item *staff = (Item*)calloc(1, sizeof(Item));
            staff->id = -2;
            staff->name = strdup("wizard's staff");
            staff->description = strdup(
                "A gnarled wooden staff crackling with arcane power.\n"
                "Runes etched along its length glow faintly.\n"
                "\n"
                "+---------- WIZARD COMMANDS ----------+\n"
                "| goto <player|room>  Teleport        |\n"
                "| set <player> <stat> Set player stat  |\n"
                "| heal <player>       Restore HP/pools |\n"
                "| clone <object>      Clone an object  |\n"
                "| eval <expr>         Evaluate LPC     |\n"
                "| update <file>       Reload LPC file  |\n"
                "+--------------------------------------+");
            staff->type = ITEM_TOOL;
            staff->weight = 999;
            staff->value = 0;
            room_add_item(workroom, staff);

            /* Handbook */
            Item *handbook = (Item*)calloc(1, sizeof(Item));
            handbook->id = -3;
            handbook->name = strdup("wizard's handbook");
            handbook->description = strdup(
                "A leather-bound book with gold-leaf lettering:\n"
                "'The AetherMUD Wizard's Handbook'\n"
                "Type 'read handbook' for the wizard guide.");
            handbook->type = ITEM_MISC;
            handbook->weight = 999;
            handbook->value = 0;
            room_add_item(workroom, handbook);

            /* Crystal */
            Item *crystal = (Item*)calloc(1, sizeof(Item));
            crystal->id = -4;
            crystal->name = strdup("viewing crystal");
            crystal->description = strdup(
                "A swirling crystal orb resting on a silver stand.\n"
                "Shadows of distant places shift within its depths.\n"
                "\n"
                "+-------- MONITORING COMMANDS --------+\n"
                "| who                List all online  |\n"
                "| finger <player>    Player details   |\n"
                "| snoop <player>     Watch a session  |\n"
                "| users              Connection info  |\n"
                "+-------------------------------------+");
            crystal->type = ITEM_TOOL;
            crystal->weight = 999;
            crystal->value = 0;
            room_add_item(workroom, crystal);
        } else {
            /* Fallback to start room if LPC load fails */
            fprintf(stderr, "[Chargen] Workroom LPC load failed, using start room\n");
            Room *start = room_get_start();
            if (start) {
                sess->current_room = start;
                room_add_player(start, sess);
            }
        }
    } else {
        Room *start = room_get_start();
        if (start) {
            sess->current_room = start;
            room_add_player(start, sess);
        }
    }

    /* Mark chargen as complete */
    sess->chargen_state = CHARGEN_COMPLETE;
    sess->state = STATE_PLAYING;

    /* Welcome message */
    send_to_player(sess, "\n");
    send_to_player(sess, "=========================================\n");
    send_to_player(sess, "  Welcome, Administrator!\n");
    send_to_player(sess, "=========================================\n");
    send_to_player(sess, "\n");
    send_to_player(sess, "Your admin character has been auto-created.\n");
    send_to_player(sess, "You are standing in your private workroom.\n");
    send_to_player(sess, "\n");
    send_to_player(sess, "Your workroom contains a chest with wiz-tools for your role.\n");
    send_to_player(sess, "Use 'home' command to return to your workroom anytime.\n");
    send_to_player(sess, "\n");
    send_to_player(sess, "Admin commands: promote, goto, set, users, force, eval\n");
    send_to_player(sess, "Type 'help' for the full command reference.\n");
    send_to_player(sess, "\n");

    /* Auto-save */
    if (save_character(sess)) {
        send_to_player(sess, "Character saved.\n\n");
    } else {
        send_to_player(sess, "Warning: Failed to save character.\n\n");
    }

    /* Show starting room */
    cmd_look(sess, "");
    send_to_player(sess, "\n> ");
}

/* Init car generation */
void chargen_init(PlayerSession *sess) {
    if (!sess) return;
    
    sess->chargen_state = CHARGEN_RACE_SELECT;
    sess->chargen_page = 0;
    sess->chargen_temp_choice = 0;
    
    send_to_player(sess, "\n");
    send_to_player(sess, "=========================================\n");
    send_to_player(sess, "      CHARACTER CREATION SYSTEM\n");
    send_to_player(sess, "        AetherMUD - 109 P.A.\n");
    send_to_player(sess, "=========================================\n");
    send_to_player(sess, "\n");
    
    /* Ensure races are scanned from disk */
    if (num_loaded_races == 0) race_loader_scan_races();

    /* Display first page of races */
    int total_pages = (num_loaded_races + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    send_to_player(sess, "=== SELECT YOUR RACE (Page %d/%d) ===\n\n",
                   sess->chargen_page + 1, total_pages);

    int start = sess->chargen_page * ITEMS_PER_PAGE;
    int end = start + ITEMS_PER_PAGE;
    if (end > num_loaded_races) end = num_loaded_races;

    for (int i = start; i < end; i++) {
        send_to_player(sess, "  %2d. %s - %s\n",
                      i + 1, loaded_races[i].name, loaded_races[i].desc);
    }

    send_to_player(sess, "\n");
    if (sess->chargen_page > 0) {
        send_to_player(sess, "  Type 'p' for previous page\n");
    }
    if (end < num_loaded_races) {
        send_to_player(sess, "  Type 'n' for next page\n");
    }
    send_to_player(sess, "\nEnter choice (1-%d): ", num_loaded_races);
}

/* Roll character stats */
void chargen_roll_stats(PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    int i;
    
    ch->stats.iq = roll_3d6();
    ch->stats.me = roll_3d6();
    ch->stats.ma = roll_3d6();
    ch->stats.ps = roll_3d6();
    ch->stats.pp = roll_3d6();
    ch->stats.pe = roll_3d6();
    ch->stats.pb = roll_3d6();
    ch->stats.spd = roll_3d6();
    
    /* Set basic stats based on race/OCC */
    ch->level = 1;
    ch->xp = 0;
    
    /* HP = PE + 1d6 */
    ch->hp = ch->stats.pe + roll_1d6();
    ch->max_hp = ch->hp;
    
    /* SDC = 20 + bonuses */
    ch->sdc = 20;
    ch->max_sdc = 20;
    
    /* Phase 1 defaults for extended health/energy */
    ch->health_type = HP_SDC;
    ch->mdc = 0;
    ch->max_mdc = 0;

    ch->isp = 0;
    ch->max_isp = 0;

    ch->ppe = 0;
    ch->max_ppe = 0;

    ch->natural_weapon_count = 0;
    for (i = 0; i < 8; i++) ch->natural_weapons[i] = NULL;
    /* Default combat and death settings */
    ch->attacks_per_round = 2;   /* Default 2 attacks per round */
    ch->lives_remaining = 5;     /* Start with 5 lives */
    ch->scar_count = 0;

    ch->introduced_count = 0;
    for (i = 0; i < 32; i++) ch->introduced_to[i] = NULL;

    ch->clan = NULL;
    ch->alignment = NULL;

    /* Initialize languages */
    ch->num_languages = 0;
    for (i = 0; i < 16; i++) ch->languages[i] = NULL;
    ch->current_language = NULL;

    /* ISP/PPE will be calculated in psionics_init_abilities() and magic_init_abilities() */
    /* These are called in chargen_complete() */

    /* Apply race / O.C.C. derived bonuses */
    apply_race_and_occ(sess);
}

/* Display character stats */
void chargen_display_stats(PlayerSession *sess) {
    if (!sess) return;

    Character *ch = &sess->character;
    int w = FRAME_WIDTH;
    int i;
    char buf[256];

    send_to_player(sess, "\r\n");
    frame_top(sess, w);
    frame_title(sess, "CHARACTER SHEET", w);
    frame_sep(sess, w);

    snprintf(buf, sizeof(buf), "Name: %s", sess->username);
    frame_line(sess, buf, w);
    snprintf(buf, sizeof(buf), "Race: %-20s O.C.C.: %s",
             ch->race ? ch->race : "None", ch->occ ? ch->occ : "None");
    frame_line(sess, buf, w);
    if (ch->alignment) {
        snprintf(buf, sizeof(buf), "Alignment: %s", ch->alignment);
        frame_line(sess, buf, w);
    }

    frame_header(sess, "ATTRIBUTES", w);
    snprintf(buf, sizeof(buf), "IQ: %-3d   ME: %-3d   MA: %-3d   PS: %-3d",
             ch->stats.iq, ch->stats.me, ch->stats.ma, ch->stats.ps);
    frame_line(sess, buf, w);
    snprintf(buf, sizeof(buf), "PP: %-3d   PE: %-3d   PB: %-3d   SPD: %-3d",
             ch->stats.pp, ch->stats.pe, ch->stats.pb, ch->stats.spd);
    frame_line(sess, buf, w);

    frame_header(sess, "RESOURCES", w);
    if (ch->health_type == MDC_ONLY) {
        snprintf(buf, sizeof(buf), "MDC: %d/%d", ch->mdc, ch->max_mdc);
        frame_line(sess, buf, w);
    } else if (ch->health_type == HP_ONLY) {
        snprintf(buf, sizeof(buf), "HP: %d/%d", ch->hp, ch->max_hp);
        frame_line(sess, buf, w);
    } else {
        snprintf(buf, sizeof(buf), "HP: %d/%d    S.D.C.: %d/%d",
                 ch->hp, ch->max_hp, ch->sdc, ch->max_sdc);
        frame_line(sess, buf, w);
    }

    if (ch->max_isp > 0) {
        snprintf(buf, sizeof(buf), "I.S.P.: %d/%d  (Psionic Energy)",
                 ch->isp, ch->max_isp);
        frame_line(sess, buf, w);
    } else if (ch->psionics.isp_max > 0) {
        snprintf(buf, sizeof(buf), "I.S.P.: %d/%d  (Psionic Energy)",
                 ch->psionics.isp_current, ch->psionics.isp_max);
        frame_line(sess, buf, w);
    }

    if (ch->max_ppe > 0) {
        snprintf(buf, sizeof(buf), "P.P.E.: %d/%d  (Magical Energy)",
                 ch->ppe, ch->max_ppe);
        frame_line(sess, buf, w);
    } else if (ch->magic.ppe_max > 0) {
        snprintf(buf, sizeof(buf), "P.P.E.: %d/%d  (Magical Energy)",
                 ch->magic.ppe_current, ch->magic.ppe_max);
        frame_line(sess, buf, w);
    }

    snprintf(buf, sizeof(buf), "Credits: %d", ch->credits);
    frame_line(sess, buf, w);

    /* Show lives and scars (death system) */
    snprintf(buf, sizeof(buf), "Lives remaining: %d/5", ch->lives_remaining);
    frame_line(sess, buf, w);
    if (ch->scar_count <= 0) {
        frame_line(sess, "Scars: None", w);
    } else {
        frame_line(sess, "Scars:", w);
        for (i = 0; i < ch->scar_count && i < MAX_SCARS; i++) {
            char sline[256];
            const char *loc = ch->scars[i].location[0] ? ch->scars[i].location : "unknown";
            const char *desc = ch->scars[i].description[0] ? ch->scars[i].description : "(no description)";
            snprintf(sline, sizeof(sline), " - %s: %s (death %d)", loc, desc, ch->scars[i].death_number);
            frame_line(sess, sline, w);
        }
    }

    frame_bottom(sess, w);
}

/* Display alignment choices */
static void chargen_show_alignments(PlayerSession *sess) {
    send_to_player(sess, "\n=== SELECT YOUR ALIGNMENT ===\n\n");
    send_to_player(sess, "  1. Principled    (Good)    - Honest, trustworthy, fights evil\n");
    send_to_player(sess, "  2. Scrupulous    (Good)    - Moral but pragmatic, fights injustice\n");
    send_to_player(sess, "  3. Unprincipled  (Selfish) - Looks out for #1, has some scruples\n");
    send_to_player(sess, "  4. Anarchist     (Selfish) - Free spirit, rebels against authority\n");
    send_to_player(sess, "  5. Miscreant     (Evil)    - Untrustworthy, self-serving villain\n");
    send_to_player(sess, "  6. Aberrant      (Evil)    - Has a personal code, but ruthless\n");
    send_to_player(sess, "  7. Diabolic      (Evil)    - Pure evil, cruel and sadistic\n");
    send_to_player(sess, "\nEnter choice (1-7): ");
}

/* Display starting zone choices */
static void chargen_show_zones(PlayerSession *sess) {
    send_to_player(sess, "\n=== SELECT YOUR STARTING ZONE ===\n\n");
    send_to_player(sess, "  1. New Camelot  - A haven of chivalry and honor in the\n");
    send_to_player(sess, "                    northern wilderness. Town Square.\n");
    send_to_player(sess, "  2. Splynn       - The infamous dimensional market of\n");
    send_to_player(sess, "                    Atlantis. Market Center.\n");
    send_to_player(sess, "  3. Chi-Town     - The Coalition States' fortress city.\n");
    send_to_player(sess, "                    Transit Hub.\n");
    send_to_player(sess, "  4. Welcome Area (LPC) - Beginner tutorial and help rooms.\n");
    send_to_player(sess, "  5. Castle Entry (LPC) - A noble castle's entry courtyard.\n");
    send_to_player(sess, "\nEnter choice (1-5): ");
}

/* Display available secondary skills for selection */
static void chargen_show_secondary_skills(PlayerSession *sess) {
    Character *ch = &sess->character;
    int remaining = 3 - sess->chargen_temp_choice;

    send_to_player(sess, "\n=== SELECT SECONDARY SKILLS (%d remaining) ===\n\n",
        remaining);

    int num = 0;
    for (int si = 0; si < NUM_SKILLS && si < 16; si++) {
        int already_has = 0;
        for (int j = 0; j < ch->num_skills; j++) {
            if (ch->skills[j].skill_id == si) {
                already_has = 1;
                break;
            }
        }
        if (!already_has) {
            SkillDef *skill = skill_get_by_id(si);
            if (skill) {
                num++;
                send_to_player(sess, "  %2d. %-25s (%s) - %s\n",
                    num, skill->name, skill->category, skill->description);
            }
        }
    }
    send_to_player(sess, "\nEnter choice (1-%d): ", num);
}

/* Complete character generation */
void chargen_complete(PlayerSession *sess) {
    if (!sess) return;
    
    sess->chargen_state = CHARGEN_COMPLETE;
    sess->state = STATE_PLAYING;
    
    /* Initialize inventory and equipment (Phase 4) */
    inventory_init(&sess->character.inventory, sess->character.stats.ps);
    equipment_init(&sess->character.equipment);
    
    /* Initialize real-time combat defaults (before race loading overrides) */
    sess->character.attacks_per_round = 2;
    sess->character.parries_per_round = 2;
    sess->character.racial_auto_parry = 0;
    sess->character.racial_auto_dodge = 0;
    sess->character.auto_parry_enabled = 1;
    sess->character.auto_dodge_enabled = 1;
    sess->character.wimpy_threshold = 0;

    /* Initialize psionics and magic (Phase 5) */
    psionics_init_abilities(&sess->character);
    magic_init_abilities(&sess->character);
    
    /* Add starting powers and spells based on OCC */
    psionics_add_starting_powers(&sess->character, sess->character.occ);
    magic_add_starting_spells(&sess->character, sess->character.occ);

    /* Assign starting languages based on race */
    assign_starting_languages(&sess->character);
    
    /* Add starting equipment based on OCC */
    /* Dragon RCC: no equipment, natural form only */
    if (strcasestr(sess->character.occ, "Dragon Hatchling")) {
        /* Dragons don't use equipment - they ARE the weapon */
        send_to_player(sess, "As a dragon, you rely on your natural abilities.\n");
        sess->character.credits = 500;
    }
    /* Sunaj Assassin: stealth gear */
    else if (strcasestr(sess->character.occ, "Sunaj Assassin")) {
        Item *weapon = item_create(1); /* Vibro-Blade (shadow weapon) */
        Item *armor = item_create(27); /* Light EBA (shadow suit) */
        if (weapon) {
            inventory_add(&sess->character.inventory, weapon);
            equipment_equip(&sess->character, sess, weapon);
        }
        if (armor) {
            inventory_add(&sess->character.inventory, armor);
            equipment_equip(&sess->character, sess, armor);
        }
        sess->character.credits = 800;
    }
    /* Combat OCCs get weapon + armor */
    else if (strcasestr(sess->character.occ, "Juicer") ||
        strcasestr(sess->character.occ, "Cyber-Knight") ||
        strcasestr(sess->character.occ, "Headhunter") ||
        strcasestr(sess->character.occ, "Glitter Boy") ||
        strcasestr(sess->character.occ, "CS ") ||
        strcasestr(sess->character.occ, "Ranger") ||
        strcasestr(sess->character.occ, "Soldier") ||
        strcasestr(sess->character.occ, "Merc") ||
        strcasestr(sess->character.occ, "Assassin") ||
        strcasestr(sess->character.occ, "Knight") ||
        strcasestr(sess->character.occ, "Bounty")) {
        /* Give Vibro-Blade + Light EBA */
        Item *weapon = item_create(1); /* Vibro-Blade */
        Item *armor = item_create(27); /* Light EBA */
        if (weapon) {
            inventory_add(&sess->character.inventory, weapon);
            equipment_equip(&sess->character, sess, weapon);
        }
        if (armor) {
            inventory_add(&sess->character.inventory, armor);
            equipment_equip(&sess->character, sess, armor);
        }
        sess->character.credits = 1000;
    }
    /* Magic OCCs get staff + healing potion */
    else if (strcasestr(sess->character.occ, "Walker") ||
             strcasestr(sess->character.occ, "Warlock") ||
             strcasestr(sess->character.occ, "Mystic") ||
             strcasestr(sess->character.occ, "Wizard") ||
             strcasestr(sess->character.occ, "Tattooed") ||
             strcasestr(sess->character.occ, "Fusionist") ||
             strcasestr(sess->character.occ, "Necromancer") ||
             strcasestr(sess->character.occ, "Shifter")) {
        Item *staff = item_create(24); /* TW Fire Bolt Staff */
        Item *potion = item_create(40); /* Healing Potion */
        if (staff) {
            inventory_add(&sess->character.inventory, staff);
            equipment_equip(&sess->character, sess, staff);
        }
        if (potion) inventory_add(&sess->character.inventory, potion);
        sess->character.credits = 1000;
    }
    /* Vagabond/unskilled OCCs get a knife */
    else if (strcasestr(sess->character.occ, "Vagabond") ||
             strcasestr(sess->character.occ, "City Rat") ||
             strcasestr(sess->character.occ, "Scout")) {
        Item *knife = item_create(7); /* Steel Knife */
        if (knife) {
            inventory_add(&sess->character.inventory, knife);
            equipment_equip(&sess->character, sess, knife);
        }
        sess->character.credits = 1000;
    }
    /* Default: basic supplies and credits */
    else {
        sess->character.credits = 1000;
    }

    /* Non-dragon characters get basic supplies */
    if (!strcasestr(sess->character.occ, "Dragon Hatchling")) {
        Item *ration = item_create(48); /* Food Ration */
        Item *water = item_create(49); /* Water Canteen */
        if (ration) inventory_add(&sess->character.inventory, ration);
        if (water) inventory_add(&sess->character.inventory, water);
    }

    /* Place player in starting room (use zone-selected room if set, else default) */
    if (sess->current_room) {
        room_add_player(sess->current_room, sess);
    } else {
        Room *start = room_get_start();
        if (start) {
            sess->current_room = start;
            room_add_player(start, sess);
        }
    }
    
    send_to_player(sess, "\n");
    send_to_player(sess, "Character creation complete!\n");
    send_to_player(sess, "Welcome to AetherMUD, %s!\n", sess->username);
    
    /* Auto-save new character */
    send_to_player(sess, "\nSaving your character...\n");
    if (save_character(sess)) {
        send_to_player(sess, "Character saved.\n");
    } else {
        send_to_player(sess, " Warning: Failed to save character.\n");
    }
    
    send_to_player(sess, "\n");
    
    /* Auto-look at starting room */
    cmd_look(sess, "");
    send_to_player(sess, "\n> ");
}

/* Process chargen input */
void chargen_process_input(PlayerSession *sess, const char *input) {
    if (!sess || !input) return;
    
    Character *ch = &sess->character;
    int choice = atoi(input);
    
    switch (sess->chargen_state) {
        case CHARGEN_RACE_SELECT:
            /* Handle pagination */
            if (input[0] == 'n' || input[0] == 'N') {
                int total_pages = (num_loaded_races + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
                if (sess->chargen_page < total_pages - 1) {
                    sess->chargen_page++;
                    /* Redisplay */
                    send_to_player(sess, "\n=== SELECT YOUR RACE (Page %d/%d) ===\n\n",
                                   sess->chargen_page + 1, total_pages);

                    int start = sess->chargen_page * ITEMS_PER_PAGE;
                    int end = start + ITEMS_PER_PAGE;
                    if (end > num_loaded_races) end = num_loaded_races;

                    for (int i = start; i < end; i++) {
                        send_to_player(sess, "  %2d. %s - %s\n",
                                      i + 1, loaded_races[i].name, loaded_races[i].desc);
                    }

                    send_to_player(sess, "\n");
                    if (sess->chargen_page > 0) {
                        send_to_player(sess, "  Type 'p' for previous page\n");
                    }
                    if (end < num_loaded_races) {
                        send_to_player(sess, "  Type 'n' for next page\n");
                    }
                    send_to_player(sess, "\nEnter choice (1-%d): ", num_loaded_races);
                } else {
                    send_to_player(sess, "Already on last page.\nEnter choice (1-%d): ", num_loaded_races);
                }
                return;
            }
            
            if (input[0] == 'p' || input[0] == 'P') {
                if (sess->chargen_page > 0) {
                    sess->chargen_page--;
                    /* Redisplay */
                    int total_pages = (num_loaded_races + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
                    send_to_player(sess, "\n=== SELECT YOUR RACE (Page %d/%d) ===\n\n",
                                   sess->chargen_page + 1, total_pages);

                    int start = sess->chargen_page * ITEMS_PER_PAGE;
                    int end = start + ITEMS_PER_PAGE;
                    if (end > num_loaded_races) end = num_loaded_races;

                    for (int i = start; i < end; i++) {
                        send_to_player(sess, "  %2d. %s - %s\n",
                                      i + 1, loaded_races[i].name, loaded_races[i].desc);
                    }

                    send_to_player(sess, "\n");
                    if (sess->chargen_page > 0) {
                        send_to_player(sess, "  Type 'p' for previous page\n");
                    }
                    if (end < num_loaded_races) {
                        send_to_player(sess, "  Type 'n' for next page\n");
                    }
                    send_to_player(sess, "\nEnter choice (1-%d): ", num_loaded_races);
                } else {
                    send_to_player(sess, "Already on first page.\nEnter choice (1-%d): ", num_loaded_races);
                }
                return;
            }
            
            /* Handle selection */
            if (choice >= 1 && choice <= num_loaded_races) {
                ch->race = strdup(loaded_races[choice - 1].name);

                send_to_player(sess, "\nYou selected: %s\n\n", ch->race);

                /* Dragon races auto-assign Dragon Hatchling RCC */
                if (strcasestr(ch->race, "Dragon") != NULL) {
                    ch->occ = strdup("Dragon Hatchling RCC");
                    send_to_player(sess, "As a %s, your O.C.C. is Dragon Hatchling RCC.\n", ch->race);
                    send_to_player(sess, "Dragons are a Racial Character Class with innate abilities.\n\n");
                } else {
                    /* Default OCC: Vagabond (wizard can reassign via 'set <player> occ <name>') */
                    ch->occ = strdup("Vagabond");
                    send_to_player(sess, "Your starting O.C.C. is Vagabond (jack of all trades).\n");
                    send_to_player(sess, "A wizard can assign a specialized O.C.C. later.\n\n");
                }

                send_to_player(sess, "Rolling your attributes...\n");
                chargen_roll_stats(sess);
                chargen_display_stats(sess);

                sess->chargen_state = CHARGEN_STATS_CONFIRM;
                send_to_player(sess, "\n");
                send_to_player(sess, "Accept these stats? (yes/reroll): ");
            } else {
                send_to_player(sess, "Invalid choice. Please enter 1-%d: ", NUM_RACES);
            }
            break;

        case CHARGEN_OCC_SELECT:
            /* OCC selection is handled post-chargen by wizards via 'set <player> occ <name>' */
            send_to_player(sess, "O.C.C. selection is handled by game administrators.\n");
            send_to_player(sess, "Please contact a wizard for your O.C.C. assignment.\n");
            break;
            
        case CHARGEN_STATS_CONFIRM:
            if (strncasecmp(input, "yes", 3) == 0 || strncasecmp(input, "y", 1) == 0) {
                /* Auto-assign OCC primary skills, except for dragon RCCs which use racial skills */
                if (ch->occ && strcasestr(ch->occ, "Dragon Hatchling") != NULL) {
                    send_to_player(sess, "\nAs a dragon, your racial abilities apply instead of OCC primary skills.\n");
                    send_to_player(sess, "You will select secondary skills next.\n");
                } else {
                    occ_assign_skills(sess, ch->occ);
                    send_to_player(sess, "\nYour primary skills have been assigned based on your O.C.C.\n");
                    skill_display_list(sess);
                }

                /* Transition to alignment selection */
                sess->chargen_state = CHARGEN_ALIGNMENT_SELECT;
                chargen_show_alignments(sess);
            } else if (strncasecmp(input, "reroll", 6) == 0 || strncasecmp(input, "r", 1) == 0) {
                send_to_player(sess, "\nRerolling stats...\n");
                chargen_roll_stats(sess);
                chargen_display_stats(sess);
                send_to_player(sess, "\n");
                send_to_player(sess, "Accept these stats? (yes/reroll): ");
            } else {
                send_to_player(sess, "Please answer 'yes' or 'reroll': ");
            }
            break;

        case CHARGEN_ALIGNMENT_SELECT:
            {
                static const char *alignment_names[] = {
                    "Principled", "Scrupulous", "Unprincipled", "Anarchist",
                    "Miscreant", "Aberrant", "Diabolic"
                };
                if (choice >= 1 && choice <= 7) {
                    if (ch->alignment) free(ch->alignment);
                    ch->alignment = strdup(alignment_names[choice - 1]);
                    send_to_player(sess, "\nAlignment set to: %s\n", ch->alignment);

                    /* Transition to zone selection */
                    sess->chargen_state = CHARGEN_ZONE_SELECT;
                    chargen_show_zones(sess);
                } else {
                    send_to_player(sess, "Invalid choice. Enter 1-7: ");
                }
            }
            break;

        case CHARGEN_ZONE_SELECT:
            {
                sess->chargen_temp_choice = 0; /* Reset for secondary skill picks */
                /* Hard-coded LPC starting zones (Option A) */
                if (choice >= 1 && choice <= 3) {
                    static const int zone_rooms[] = { 4, 11, 23 };
                    static const char *zone_names[] = { "New Camelot", "Splynn", "Chi-Town" };
                    int selected_room = zone_rooms[choice - 1];
                    send_to_player(sess, "\nStarting zone: %s\n", zone_names[choice - 1]);

                    /* Clear any existing LPC room path */
                    if (sess->current_room_path) { free(sess->current_room_path); sess->current_room_path = NULL; }

                    /* Store selected C bootstrap room */
                    Room *zone_room = room_get_by_id(selected_room);
                    if (zone_room) {
                        sess->current_room = zone_room;
                    }

                    /* Transition to secondary skills */
                    sess->chargen_state = CHARGEN_SECONDARY_SKILLS;
                    chargen_show_secondary_skills(sess);
                } else if (choice == 4 || choice == 5) {
                    /* LPC starting rooms */
                    const char *path = (choice == 4) ? "/domains/start/room/welcome" : "/domains/castle/room/entry";
                    send_to_player(sess, "\nStarting zone: %s (LPC)\n", path);

                    /* Free previous path if any */
                    if (sess->current_room_path) { free(sess->current_room_path); sess->current_room_path = NULL; }
                    sess->current_room_path = strdup(path);

                    /* Load LPC room on-demand */
                    Room *zone_room = room_get_by_path(path);
                    if (zone_room) {
                        sess->current_room = zone_room;
                    } else {
                        send_to_player(sess, "Warning: LPC start room '%s' could not be loaded now; defaulting to starter zone.\n", path);
                        sess->current_room = room_get_start();
                    }

                    /* Transition to secondary skills */
                    sess->chargen_state = CHARGEN_SECONDARY_SKILLS;
                    chargen_show_secondary_skills(sess);
                } else {
                    send_to_player(sess, "Invalid choice. Enter 1-5: ");
                }
            }
            break;

        case CHARGEN_SECONDARY_SKILLS:
            {
                int pick = atoi(input);
                /* Build list of available skills (not already assigned) */
                int available[16];
                int num_available = 0;
                for (int si = 0; si < NUM_SKILLS && si < 16; si++) {
                    int already_has = 0;
                    for (int j = 0; j < ch->num_skills; j++) {
                        if (ch->skills[j].skill_id == si) {
                            already_has = 1;
                            break;
                        }
                    }
                    if (!already_has) {
                        available[num_available++] = si;
                    }
                }
                if (pick >= 1 && pick <= num_available) {
                    int skill_id = available[pick - 1];
                    SkillDef *skill = skill_get_by_id(skill_id);
                    if (skill && ch->num_skills < MAX_PLAYER_SKILLS) {
                        ch->skills[ch->num_skills].skill_id = skill_id;
                        ch->skills[ch->num_skills].percentage = skill->base_percentage;
                        ch->skills[ch->num_skills].uses = 0;
                        ch->num_skills++;
                        sess->chargen_temp_choice++;
                        send_to_player(sess, "Learned: %s (%d%%)\n",
                            skill->name, skill->base_percentage);
                    }
                    if (sess->chargen_temp_choice >= 3) {
                        send_to_player(sess, "\nSecondary skills selection complete.\n");
                        chargen_complete(sess);
                    } else {
                        chargen_show_secondary_skills(sess);
                    }
                } else {
                    send_to_player(sess, "Invalid choice. Enter a number from the list: ");
                }
            }
            break;

        default:
            break;
    }
}

/* Stats command */
void cmd_stats(PlayerSession *sess, const char *args) {
    if (!sess) return;
    
    if (sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }
    
    chargen_display_stats(sess);
}

/* Skills command */
void cmd_skills(PlayerSession *sess, const char *args) {
    if (!sess) return;
    
    if (sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }
    
    skill_display_list(sess);
}

/* ========== COMBAT COMMANDS ========== */

void cmd_attack(PlayerSession *sess, const char *args) {
    if (!sess || sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }

    if (!args || !(*args)) {
        send_to_player(sess, "Attack who?\n");
        return;
    }

    if (sess->in_combat) {
        send_to_player(sess, "You are already in combat! Use 'stop' to disengage.\n");
        return;
    }

    if (sess->is_resting) {
        send_to_player(sess, "You stand up from resting.\n");
        sess->is_resting = 0;
    }

    /* Find target player in room */
    if (!sess->current_room) {
        send_to_player(sess, "You are nowhere.\n");
        return;
    }

    PlayerSession *target = NULL;
    Room *room = sess->current_room;
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] && room->players[i] != sess &&
            room->players[i]->username &&
            strcasecmp(room->players[i]->username, args) == 0) {
            target = room->players[i];
            break;
        }
    }

    if (!target) {
        send_to_player(sess, "You don't see '%s' here.\n", args);
        return;
    }

    if (target == sess) {
        send_to_player(sess, "You can't attack yourself.\n");
        return;
    }

    combat_engage(sess, target);
}

void cmd_strike(PlayerSession *sess, const char *args) {
    (void)args;
    if (!sess) return;
    send_to_player(sess, "Combat is now real-time. Use 'attack <target>' to engage. Attacks fire automatically.\n");
}

void cmd_shoot(PlayerSession *sess, const char *args) {
    (void)args;
    if (!sess) return;
    send_to_player(sess, "Combat is now real-time. Use 'attack <target>' to engage. Attacks fire automatically.\n");
}

void cmd_dodge(PlayerSession *sess, const char *args) {
    (void)args;
    if (!sess) return;
    send_to_player(sess, "Dodging is now automatic. Use 'autododge' to toggle auto-dodge on/off.\n");
}

void cmd_flee(PlayerSession *sess, const char *args) {
    (void)args;
    if (!sess || sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }

    if (!sess->in_combat) {
        send_to_player(sess, "You are not in combat.\n");
        return;
    }

    /* PP check: 1d20 + PP bonus vs 12 */
    int pp = sess->character.stats.pp;
    int pp_bonus = (pp > 10) ? (pp - 10) / 5 : 0;
    int roll = combat_d20();
    int total = roll + pp_bonus;

    if (total >= 12) {
        send_to_player(sess, "You successfully flee from combat!\n");
        combat_disengage(sess);
        /* Try to move in a random direction */
        const char *dirs[] = {"north", "south", "east", "west"};
        cmd_move(sess, dirs[rand() % 4]);
    } else {
        send_to_player(sess, "You fail to escape! (Rolled %d+%d=%d vs 12)\n", roll, pp_bonus, total);
    }
}

/* ========== CHARACTER PERSISTENCE ========== */

/* Check if a character save file exists */
int character_exists(const char *username, char *found_name, size_t found_size) {
    if (!username || !username[0]) return 0;

    DIR *dir = opendir("lib/save/players");
    if (!dir) return 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        /* Match *.dat files only */
        const char *dot = strrchr(entry->d_name, '.');
        if (!dot || strcmp(dot, ".dat") != 0) continue;

        /* Extract name portion (before .dat) */
        size_t name_len = dot - entry->d_name;
        if (name_len == 0 || name_len >= 64) continue;

        char base[64];
        memcpy(base, entry->d_name, name_len);
        base[name_len] = '\0';

        if (strcasecmp(base, username) == 0) {
            /* Found it — return the on-disk capitalization */
            if (found_name && found_size > 0) {
                strncpy(found_name, base, found_size - 1);
                found_name[found_size - 1] = '\0';
            }
            closedir(dir);
            return 1;
        }
    }

    closedir(dir);
    return 0;
}

/* Save character to disk */
int save_character(PlayerSession *sess) {
    if (!sess || !sess->username[0]) {
        ERROR_LOG("Invalid session");
        return 0;
    }
    
    /* Create save directory if it doesn't exist */
    mkdir("lib", 0755);
    mkdir("lib/save", 0755);
    mkdir("lib/save/players", 0755);
    
    /* Build filepath */
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "lib/save/players/%s.dat", sess->username);
    
    /* Create backup of existing save */
    char backup[512];
    snprintf(backup, sizeof(backup), "%s.bak", filepath);
    rename(filepath, backup);  /* Move old save to backup (ignore errors) */
    
    /* Open file for writing */
    FILE *f = fopen(filepath, "wb");
    if (!f) {
        ERROR_LOG("Failed to open %s for writing: %s", 
                filepath, strerror(errno));
        return 0;
    }
    int i;
    
    /* Write magic number (for validation) */
    uint32_t magic = 0x414D4C50;  /* "AMLP" in hex */
    fwrite(&magic, sizeof(uint32_t), 1, f);
    
    /* Write version (for future compatibility)
     * Version history:
     *  1 - original format
     *  3 - added LPC room path persistence (char *room_path) after room_id
     */
    uint16_t version = 4;
    fwrite(&version, sizeof(uint16_t), 1, f);
    
    /* Write username */
    size_t name_len = strlen(sess->username);
    fwrite(&name_len, sizeof(size_t), 1, f);
    fwrite(sess->username, 1, name_len, f);
    
    /* Write privilege level */
    fwrite(&sess->privilege_level, sizeof(int), 1, f);
    
    /* Write password hash (for security) */
    size_t hash_len = strlen(sess->password_hash);
    fwrite(&hash_len, sizeof(size_t), 1, f);
    fwrite(sess->password_hash, 1, hash_len, f);
    
    /* Write character data */
    Character *ch = &sess->character;
    
    /* Write race */
    if (ch->race) {
        size_t race_len = strlen(ch->race);
        fwrite(&race_len, sizeof(size_t), 1, f);
        fwrite(ch->race, 1, race_len, f);
    } else {
        size_t zero = 0;
        fwrite(&zero, sizeof(size_t), 1, f);
    }
    
    /* Write OCC */
    if (ch->occ) {
        size_t occ_len = strlen(ch->occ);
        fwrite(&occ_len, sizeof(size_t), 1, f);
        fwrite(ch->occ, 1, occ_len, f);
    } else {
        size_t zero = 0;
        fwrite(&zero, sizeof(size_t), 1, f);
    }
    
    /* Write stats */
    fwrite(&ch->stats, sizeof(CharacterStats), 1, f);
    
    /* Write numeric values */
    fwrite(&ch->level, sizeof(int), 1, f);
    fwrite(&ch->xp, sizeof(int), 1, f);
    fwrite(&ch->hp, sizeof(int), 1, f);
    fwrite(&ch->max_hp, sizeof(int), 1, f);
    fwrite(&ch->sdc, sizeof(int), 1, f);
    fwrite(&ch->max_sdc, sizeof(int), 1, f);

    /* Phase 1: extended health fields */
    /* health_type as uint8_t */
    uint8_t htype = (uint8_t) ch->health_type;
    fwrite(&htype, sizeof(uint8_t), 1, f);
    fwrite(&ch->mdc, sizeof(int), 1, f);
    fwrite(&ch->max_mdc, sizeof(int), 1, f);

    /* ISP / PPE fields (also stored in psionics/magic structs) */
    fwrite(&ch->isp, sizeof(int), 1, f);
    fwrite(&ch->max_isp, sizeof(int), 1, f);
    fwrite(&ch->ppe, sizeof(int), 1, f);
    fwrite(&ch->max_ppe, sizeof(int), 1, f);

    /* Backwards-compatible: also store psionics/magic pools for older systems */
    fwrite(&ch->psionics.isp_current, sizeof(int), 1, f);
    fwrite(&ch->psionics.isp_max, sizeof(int), 1, f);
    fwrite(&ch->magic.ppe_current, sizeof(int), 1, f);
    fwrite(&ch->magic.ppe_max, sizeof(int), 1, f);
    
    /* Write current room ID */
    int room_id = sess->current_room ? sess->current_room->id : 0;
    fwrite(&room_id, sizeof(int), 1, f);
    /* Write LPC room path (new in version 3). Write size_t length followed by bytes.
     * For C/bootstrap rooms write length 0. */
    if (sess->current_room && sess->current_room->lpc_path) {
        size_t path_len = strlen(sess->current_room->lpc_path);
        fwrite(&path_len, sizeof(size_t), 1, f);
        fwrite(sess->current_room->lpc_path, 1, path_len, f);
    } else {
        size_t zero = 0;
        fwrite(&zero, sizeof(size_t), 1, f);
    }

    /* Write natural weapons */
    int nw = ch->natural_weapon_count;
    if (nw < 0) nw = 0;
    if (nw > 8) nw = 8;
    fwrite(&nw, sizeof(int), 1, f);
    for (i = 0; i < nw; i++) {
        if (ch->natural_weapons[i]) {
            size_t len = strlen(ch->natural_weapons[i]);
            fwrite(&len, sizeof(size_t), 1, f);
            fwrite(ch->natural_weapons[i], 1, len, f);
        } else {
            size_t zero = 0;
            fwrite(&zero, sizeof(size_t), 1, f);
        }
    }

    /* Write introduced_to list */
    int it = ch->introduced_count;
    if (it < 0) it = 0;
    if (it > 32) it = 32;
    fwrite(&it, sizeof(int), 1, f);
    for (i = 0; i < it; i++) {
        if (ch->introduced_to[i]) {
            size_t len = strlen(ch->introduced_to[i]);
            fwrite(&len, sizeof(size_t), 1, f);
            fwrite(ch->introduced_to[i], 1, len, f);
        } else {
            size_t zero = 0;
            fwrite(&zero, sizeof(size_t), 1, f);
        }
    }
    
    /* Write credits */
    fwrite(&ch->credits, sizeof(int), 1, f);

    /* Write skills */
    fwrite(&ch->num_skills, sizeof(int), 1, f);
    for (i = 0; i < ch->num_skills && i < 20; i++) {
        fwrite(&ch->skills[i].skill_id, sizeof(int), 1, f);
        fwrite(&ch->skills[i].percentage, sizeof(int), 1, f);
        fwrite(&ch->skills[i].uses, sizeof(int), 1, f);
    }

    /* Write psionic powers */
    int pc = ch->psionics.power_count;
    fwrite(&pc, sizeof(int), 1, f);
    for (i = 0; i < pc; i++) {
        fwrite(&ch->psionics.powers[i].power_id, sizeof(int), 1, f);
        fwrite(&ch->psionics.powers[i].rank, sizeof(int), 1, f);
    }

    /* Write magic spells */
    int sc = ch->magic.spell_count;
    fwrite(&sc, sizeof(int), 1, f);
    for (i = 0; i < sc; i++) {
        fwrite(&ch->magic.spells[i].spell_id, sizeof(int), 1, f);
        fwrite(&ch->magic.spells[i].rank, sizeof(int), 1, f);
    }

    /* Write timestamp */
    time_t now = time(NULL);
    fwrite(&now, sizeof(time_t), 1, f);

    /* Write clan (appended after timestamp for backwards compatibility) */
    if (ch->clan && ch->clan[0]) {
        size_t clan_len = strlen(ch->clan);
        fwrite(&clan_len, sizeof(size_t), 1, f);
        fwrite(ch->clan, 1, clan_len, f);
    } else {
        size_t zero = 0;
        fwrite(&zero, sizeof(size_t), 1, f);
    }

    /* Write languages (appended after clan for backwards compatibility) */
    int nl = ch->num_languages;
    if (nl < 0) nl = 0;
    if (nl > 16) nl = 16;
    fwrite(&nl, sizeof(int), 1, f);
    for (i = 0; i < nl; i++) {
        if (ch->languages[i]) {
            size_t len = strlen(ch->languages[i]);
            fwrite(&len, sizeof(size_t), 1, f);
            fwrite(ch->languages[i], 1, len, f);
        } else {
            size_t zero = 0;
            fwrite(&zero, sizeof(size_t), 1, f);
        }
    }
    /* Write current_language */
    if (ch->current_language && ch->current_language[0]) {
        size_t cl_len = strlen(ch->current_language);
        fwrite(&cl_len, sizeof(size_t), 1, f);
        fwrite(ch->current_language, 1, cl_len, f);
    } else {
        size_t zero = 0;
        fwrite(&zero, sizeof(size_t), 1, f);
    }

    /* Write alignment (appended after languages for backwards compatibility) */
    if (ch->alignment && ch->alignment[0]) {
        size_t align_len = strlen(ch->alignment);
        fwrite(&align_len, sizeof(size_t), 1, f);
        fwrite(ch->alignment, 1, align_len, f);
    } else {
        size_t zero = 0;
        fwrite(&zero, sizeof(size_t), 1, f);
    }

    /* Write inventory (appended after alignment for backwards compatibility).
     * Format: item_count, then for each item: template_id + equip_slot.
     * equip_slot: 0=not equipped, 1=primary weapon, 2=secondary weapon,
     *             3=armor, 4=accessory1, 5=accessory2, 6=accessory3 */
    {
        int item_count = ch->inventory.item_count;
        fwrite(&item_count, sizeof(int), 1, f);
        Item *curr = ch->inventory.items;
        while (curr) {
            fwrite(&curr->id, sizeof(int), 1, f);
            uint8_t slot = 0;
            if (curr->is_equipped) {
                if (curr == ch->equipment.weapon_primary)   slot = 1;
                else if (curr == ch->equipment.weapon_secondary) slot = 2;
                else if (curr == ch->equipment.armor)        slot = 3;
                else if (curr == ch->equipment.accessory1)   slot = 4;
                else if (curr == ch->equipment.accessory2)   slot = 5;
                else if (curr == ch->equipment.accessory3)   slot = 6;
            }
            fwrite(&slot, sizeof(uint8_t), 1, f);
            curr = curr->next;
        }
    }

    /* Write death/lives/scars (version 4+) */
    int lives = ch->lives_remaining;
    if (lives < 0) lives = 5;
    fwrite(&lives, sizeof(int), 1, f);
    int scarc = ch->scar_count;
    if (scarc < 0 || scarc > MAX_SCARS) scarc = 0;
    fwrite(&scarc, sizeof(int), 1, f);
    for (i = 0; i < scarc; i++) {
        size_t loc_len = strlen(ch->scars[i].location);
        fwrite(&loc_len, sizeof(size_t), 1, f);
        if (loc_len > 0) fwrite(ch->scars[i].location, 1, loc_len, f);

        size_t desc_len = strlen(ch->scars[i].description);
        fwrite(&desc_len, sizeof(size_t), 1, f);
        if (desc_len > 0) fwrite(ch->scars[i].description, 1, desc_len, f);

        fwrite(&ch->scars[i].death_number, sizeof(int), 1, f);
    }

    fclose(f);

    INFO_LOG("Character '%s' saved to %s", sess->username, filepath);
    return 1;
}

/* Load character from disk */
int load_character(PlayerSession *sess, const char *username) {
    if (!sess || !username || !username[0]) {
        ERROR_LOG("Invalid parameters");
        return 0;
    }
    
    /* Build filepath */
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "lib/save/players/%s.dat", username);
    
    /* Check if file exists */
    FILE *f = fopen(filepath, "rb");
    if (!f) {
        DEBUG_LOG("No save file found for '%s'", username);
        return 0;  /* New player, need to create character */
    }
    int i;
    
    /* Read and validate magic number */
    uint32_t magic;
    if (fread(&magic, sizeof(uint32_t), 1, f) != 1 || magic != 0x414D4C50) {
        ERROR_LOG("Invalid save file format for '%s'", username);
        fclose(f);
        return 0;
    }
    
    /* Read version */
    uint16_t version;
    if (fread(&version, sizeof(uint16_t), 1, f) != 1) {
        ERROR_LOG("Failed to read version for '%s'", username);
        fclose(f);
        return 0;
    }
    
    /* Accept save versions between 1 and current supported version (4). */
    if (version < 1 || version > 4) {
        ERROR_LOG("Unsupported save file version %d for '%s'", 
                version, username);
        fclose(f);
        return 0;
    }
    
    /* Read username */
    size_t name_len;
    if (fread(&name_len, sizeof(size_t), 1, f) != 1 || name_len >= sizeof(sess->username)) {
        ERROR_LOG("Invalid username length for '%s'", username);
        fclose(f);
        return 0;
    }
    fread(sess->username, 1, name_len, f);
    sess->username[name_len] = '\0';
    
    /* Read privilege level */
    fread(&sess->privilege_level, sizeof(int), 1, f);
    
    /* Read password hash (for authentication) */
    size_t hash_len = 0;
    fread(&hash_len, sizeof(size_t), 1, f);
    if (hash_len > 0 && hash_len < sizeof(sess->password_hash)) {
        fread(sess->password_hash, 1, hash_len, f);
        sess->password_hash[hash_len] = '\0';
    } else {
        sess->password_hash[0] = '\0';
        if (hash_len > 0) fseek(f, hash_len, SEEK_CUR);  /* Skip invalid data */
    }
    
    /* Read character data */
    Character *ch = &sess->character;
    
    /* Read race */
    size_t race_len;
    fread(&race_len, sizeof(size_t), 1, f);
    if (race_len > 0) {
        char race_buf[256];
        if (race_len < sizeof(race_buf)) {
            fread(race_buf, 1, race_len, f);
            race_buf[race_len] = '\0';
            ch->race = strdup(race_buf);
        } else {
            fseek(f, race_len, SEEK_CUR);  /* Skip invalid data */
        }
    }
    
    /* Read OCC */
    size_t occ_len;
    fread(&occ_len, sizeof(size_t), 1, f);
    if (occ_len > 0) {
        char occ_buf[256];
        if (occ_len < sizeof(occ_buf)) {
            fread(occ_buf, 1, occ_len, f);
            occ_buf[occ_len] = '\0';
            ch->occ = strdup(occ_buf);
        } else {
            fseek(f, occ_len, SEEK_CUR);  /* Skip invalid data */
        }
    }
    
    /* Read stats */
    fread(&ch->stats, sizeof(CharacterStats), 1, f);
    
    /* Read numeric values */
    fread(&ch->level, sizeof(int), 1, f);
    fread(&ch->xp, sizeof(int), 1, f);
    fread(&ch->hp, sizeof(int), 1, f);
    fread(&ch->max_hp, sizeof(int), 1, f);
    fread(&ch->sdc, sizeof(int), 1, f);
    fread(&ch->max_sdc, sizeof(int), 1, f);
    
    /* Phase 1: extended health fields */
    {
        uint8_t htype = 0;
        if (fread(&htype, sizeof(uint8_t), 1, f) == 1) {
            ch->health_type = (HealthType) htype;
        } else {
            ch->health_type = HP_SDC;
        }
        fread(&ch->mdc, sizeof(int), 1, f);
        fread(&ch->max_mdc, sizeof(int), 1, f);

        fread(&ch->isp, sizeof(int), 1, f);
        fread(&ch->max_isp, sizeof(int), 1, f);
        fread(&ch->ppe, sizeof(int), 1, f);
        fread(&ch->max_ppe, sizeof(int), 1, f);

        /* Backwards-compatible: read psionics/magic pools */
        fread(&ch->psionics.isp_current, sizeof(int), 1, f);
        fread(&ch->psionics.isp_max, sizeof(int), 1, f);
        fread(&ch->magic.ppe_current, sizeof(int), 1, f);
        fread(&ch->magic.ppe_max, sizeof(int), 1, f);
    }

    /* Read current room ID */
    int room_id;
    fread(&room_id, sizeof(int), 1, f);
    /* Read LPC room path if save version supports it (version >= 3) */
    sess->current_room_path = NULL;
    if (version >= 3) {
        size_t path_len = 0;
        if (fread(&path_len, sizeof(size_t), 1, f) == 1 && path_len > 0 && path_len < 1024) {
            char *path_buf = malloc(path_len + 1);
            if (path_buf) {
                if (fread(path_buf, 1, path_len, f) == path_len) {
                    path_buf[path_len] = '\0';
                    sess->current_room_path = path_buf;
                } else {
                    free(path_buf);
                }
            }
        } else if (path_len > 0) {
            /* Skip unexpected large length */
            fseek(f, path_len, SEEK_CUR);
        }
    }

    /* Read natural weapons */
    int nw = 0;
    if (fread(&nw, sizeof(int), 1, f) == 1) {
        if (nw < 0) nw = 0;
        if (nw > 8) nw = 8;
        ch->natural_weapon_count = nw;
        for (i = 0; i < nw; i++) {
            size_t len = 0;
            if (fread(&len, sizeof(size_t), 1, f) != 1) { ch->natural_weapons[i] = NULL; continue; }
            if (len > 0 && len < 256) {
                char buf[256];
                fread(buf, 1, len, f);
                buf[len] = '\0';
                ch->natural_weapons[i] = strdup(buf);
            } else {
                if (len > 0) fseek(f, len, SEEK_CUR);
                ch->natural_weapons[i] = NULL;
            }
        }
    } else {
        ch->natural_weapon_count = 0;
    }

    /* Read introduced_to list */
    int it = 0;
    if (fread(&it, sizeof(int), 1, f) == 1) {
        if (it < 0) it = 0;
        if (it > 32) it = 32;
        ch->introduced_count = it;
        for (i = 0; i < it; i++) {
            size_t len = 0;
            if (fread(&len, sizeof(size_t), 1, f) != 1) { ch->introduced_to[i] = NULL; continue; }
            if (len > 0 && len < 256) {
                char buf[256];
                fread(buf, 1, len, f);
                buf[len] = '\0';
                ch->introduced_to[i] = strdup(buf);
            } else {
                if (len > 0) fseek(f, len, SEEK_CUR);
                ch->introduced_to[i] = NULL;
            }
        }
    } else {
        ch->introduced_count = 0;
    }

    /* Read credits (may not exist in older saves) */
    if (fread(&ch->credits, sizeof(int), 1, f) != 1) {
        ch->credits = 0;
    }

    /* Read skills */
    int ns = 0;
    if (fread(&ns, sizeof(int), 1, f) == 1 && ns > 0 && ns <= 20) {
        ch->num_skills = ns;
        for (i = 0; i < ns; i++) {
            fread(&ch->skills[i].skill_id, sizeof(int), 1, f);
            fread(&ch->skills[i].percentage, sizeof(int), 1, f);
            fread(&ch->skills[i].uses, sizeof(int), 1, f);
        }
    }

    /* Read psionic powers */
    int pc = 0;
    if (fread(&pc, sizeof(int), 1, f) == 1 && pc > 0 && pc <= 25) {
        ch->psionics.powers = calloc(pc, sizeof(KnownPower));
        ch->psionics.power_count = pc;
        for (i = 0; i < pc; i++) {
            fread(&ch->psionics.powers[i].power_id, sizeof(int), 1, f);
            fread(&ch->psionics.powers[i].rank, sizeof(int), 1, f);
            ch->psionics.powers[i].total_uses = 0;
            ch->psionics.powers[i].last_activated = 0;
        }
    }

    /* Read magic spells */
    int sc = 0;
    if (fread(&sc, sizeof(int), 1, f) == 1 && sc > 0 && sc <= 34) {
        ch->magic.spells = calloc(sc, sizeof(KnownSpell));
        ch->magic.spell_count = sc;
        for (i = 0; i < sc; i++) {
            fread(&ch->magic.spells[i].spell_id, sizeof(int), 1, f);
            fread(&ch->magic.spells[i].rank, sizeof(int), 1, f);
            ch->magic.spells[i].total_casts = 0;
            ch->magic.spells[i].last_cast = 0;
        }
    }

    /* Read timestamp (for info only) */
    time_t saved_time = 0;
    fread(&saved_time, sizeof(time_t), 1, f);

    /* Read clan (appended after timestamp, may not exist in older saves) */
    ch->clan = NULL;
    {
        size_t clan_len = 0;
        if (fread(&clan_len, sizeof(size_t), 1, f) == 1 && clan_len > 0 && clan_len < 256) {
            char clan_buf[256];
            fread(clan_buf, 1, clan_len, f);
            clan_buf[clan_len] = '\0';
            ch->clan = strdup(clan_buf);
        }
    }

    /* Read languages (appended after clan, may not exist in older saves) */
    ch->num_languages = 0;
    for (i = 0; i < 16; i++) ch->languages[i] = NULL;
    ch->current_language = NULL;
    {
        int nl = 0;
        if (fread(&nl, sizeof(int), 1, f) == 1 && nl > 0 && nl <= 16) {
            ch->num_languages = nl;
            for (i = 0; i < nl; i++) {
                size_t len = 0;
                if (fread(&len, sizeof(size_t), 1, f) != 1) { ch->languages[i] = NULL; continue; }
                if (len > 0 && len < 256) {
                    char buf[256];
                    fread(buf, 1, len, f);
                    buf[len] = '\0';
                    ch->languages[i] = strdup(buf);
                } else {
                    if (len > 0) fseek(f, len, SEEK_CUR);
                    ch->languages[i] = NULL;
                }
            }
            /* Read current_language */
            size_t cl_len = 0;
            if (fread(&cl_len, sizeof(size_t), 1, f) == 1 && cl_len > 0 && cl_len < 256) {
                char cl_buf[256];
                fread(cl_buf, 1, cl_len, f);
                cl_buf[cl_len] = '\0';
                ch->current_language = strdup(cl_buf);
            }
        }
        /* If no languages loaded (old save), assign defaults */
        if (ch->num_languages == 0) {
            assign_starting_languages(ch);
        }
    }

    /* Read alignment (appended after languages, may not exist in older saves) */
    ch->alignment = NULL;
    {
        size_t align_len = 0;
        if (fread(&align_len, sizeof(size_t), 1, f) == 1 && align_len > 0 && align_len < 256) {
            char align_buf[256];
            fread(align_buf, 1, align_len, f);
            align_buf[align_len] = '\0';
            ch->alignment = strdup(align_buf);
        }
    }

    /* Read inventory (appended after alignment, may not exist in older saves).
     * Format: item_count, then for each item: template_id (int) + equip_slot (uint8_t).
     * equip_slot: 0=not equipped, 1=primary, 2=secondary, 3=armor, 4-6=accessories */
    {
        int item_count = 0;
        if (fread(&item_count, sizeof(int), 1, f) == 1 && item_count > 0 && item_count < 200) {
            for (int i = 0; i < item_count; i++) {
                int template_id = -1;
                uint8_t slot = 0;
                if (fread(&template_id, sizeof(int), 1, f) != 1) break;
                if (fread(&slot, sizeof(uint8_t), 1, f) != 1) break;

                Item *item = item_create(template_id);
                if (!item) continue;

                inventory_add(&ch->inventory, item);

                if (slot > 0) {
                    item->is_equipped = true;
                    switch (slot) {
                        case 1: ch->equipment.weapon_primary   = item; break;
                        case 2: ch->equipment.weapon_secondary = item; break;
                        case 3: ch->equipment.armor            = item; break;
                        case 4: ch->equipment.accessory1       = item; break;
                        case 5: ch->equipment.accessory2       = item; break;
                        case 6: ch->equipment.accessory3       = item; break;
                        default: item->is_equipped = false; break;
                    }
                }
            }
        }
    }

    /* Read lives/scars if saved by newer version (version >=4) */
    if (version >= 4) {
        if (fread(&ch->lives_remaining, sizeof(int), 1, f) != 1) {
            ch->lives_remaining = 5;
        }
        if (fread(&ch->scar_count, sizeof(int), 1, f) != 1) {
            ch->scar_count = 0;
        }
        if (ch->scar_count < 0 || ch->scar_count > MAX_SCARS) ch->scar_count = 0;
        for (i = 0; i < ch->scar_count; i++) {
            size_t loc_len = 0;
            if (fread(&loc_len, sizeof(size_t), 1, f) == 1 && loc_len > 0 && loc_len < sizeof(ch->scars[i].location)) {
                char buf_loc[128];
                fread(buf_loc, 1, loc_len, f);
                buf_loc[loc_len] = '\0';
                strncpy(ch->scars[i].location, buf_loc, sizeof(ch->scars[i].location)-1);
                ch->scars[i].location[sizeof(ch->scars[i].location)-1] = '\0';
            } else {
                if (loc_len > 0) fseek(f, loc_len, SEEK_CUR);
                ch->scars[i].location[0] = '\0';
            }

            size_t desc_len = 0;
            if (fread(&desc_len, sizeof(size_t), 1, f) == 1 && desc_len > 0 && desc_len < sizeof(ch->scars[i].description)) {
                char buf_desc[256];
                fread(buf_desc, 1, desc_len, f);
                buf_desc[desc_len] = '\0';
                strncpy(ch->scars[i].description, buf_desc, sizeof(ch->scars[i].description)-1);
                ch->scars[i].description[sizeof(ch->scars[i].description)-1] = '\0';
            } else {
                if (desc_len > 0) fseek(f, desc_len, SEEK_CUR);
                ch->scars[i].description[0] = '\0';
            }

            if (fread(&ch->scars[i].death_number, sizeof(int), 1, f) != 1) ch->scars[i].death_number = i+1;
        }
    } else {
        /* Older saves: give default lives and no scars */
        ch->lives_remaining = 5;
        ch->scar_count = 0;
    }

    fclose(f);

    INFO_LOG("Character '%s' loaded from %s (saved %ld seconds ago)",
            username, filepath, time(NULL) - saved_time);

    /* Set room pointer: prefer LPC path (saved in version >=3), fall back to numeric ID. */
    sess->current_room = NULL;
    if (sess->current_room_path && sess->current_room_path[0]) {
        Room *r = room_get_by_path(sess->current_room_path);
        if (r) {
            sess->current_room = r;
        } else {
            /* Path couldn't be resolved; fall back to numeric ID */
            sess->current_room = room_get_by_id(room_id);
        }
    } else {
        sess->current_room = room_get_by_id(room_id);
    }
    if (!sess->current_room) {
        sess->current_room = room_get_start();  /* Fallback to start room */
    }

    return 1;
}

/* ========== ITEM COMMANDS (Phase 4) ========== */

/* Display inventory */
void cmd_inventory(PlayerSession *sess, const char *args) {
    if (!sess) return;
    inventory_display(sess);
}

/* Equip an item from inventory */
void cmd_equip(PlayerSession *sess, const char *args) {
    if (!sess || !args || !*args) {
        send_to_player(sess, "Equip what? Try 'equip <item name or number>'\n");
        return;
    }

    Character *ch = &sess->character;
    Item *item = inventory_find(&ch->inventory, args);

    if (!item) {
        send_to_player(sess, "You don't have that item. Use 'inventory' to see your items.\n");
        return;
    }

    if (item->is_equipped) {
        send_to_player(sess, "You are already wearing or wielding %s.\n", item->name);
        return;
    }

    /* Attempt to equip via equipment system */
    if (equipment_equip(ch, sess, item)) {
        send_to_player(sess, "You equip %s.\n", item->name);
    } else {
        send_to_player(sess, "You can't equip %s right now.\n", item->name);
    }
}

/* Unequip an item */
void cmd_unequip(PlayerSession *sess, const char *args) {
    if (!sess || !args || !*args) {
        send_to_player(sess, "Unequip what? Try 'unequip <slot>' (weapon, armor, secondary)\n");
        return;
    }
    
    Character *ch = &sess->character;
    Item *item = equipment_unequip(ch, args);
    
    if (item) {
        send_to_player(sess, "You unequip %s.\n", item->name);
    } else {
        send_to_player(sess, "Nothing equipped in that slot.\n");
    }
}

/* Display equipped items */
void cmd_worn(PlayerSession *sess, const char *args) {
    if (!sess) return;
    equipment_display(sess);
}

/* Get/pick up item from room */
void cmd_get(PlayerSession *sess, const char *args) {
    if (!sess || !args || !*args) {
        send_to_player(sess, "Get what? Try 'get <item name>'\n");
        return;
    }

    if (!sess->current_room) {
        send_to_player(sess, "You are nowhere.\n");
        return;
    }

    Item *item = room_find_item(sess->current_room, args);
    if (!item) {
        send_to_player(sess, "There is no '%s' here to pick up.\n", args);
        return;
    }

    if (!inventory_can_carry(&sess->character.inventory, item->weight)) {
        send_to_player(sess, "You can't carry that much weight.\n");
        return;
    }

    room_remove_item(sess->current_room, item);
    inventory_add(&sess->character.inventory, item);
    send_to_player(sess, "You pick up %s.\n", item->name);

    char msg[256];
    snprintf(msg, sizeof(msg), "%s picks up %s.\n", sess->username, item->name);
    room_broadcast(sess->current_room, msg, sess);
}

/* Drop item from inventory to room */
void cmd_drop(PlayerSession *sess, const char *args) {
    if (!sess || !args || !*args) {
        send_to_player(sess, "Drop what? Try 'drop <item name>'\n");
        return;
    }

    if (!sess->current_room) {
        send_to_player(sess, "You are nowhere.\n");
        return;
    }

    /* Unequip first if equipped */
    Item *check = inventory_find(&sess->character.inventory, args);
    if (check && check->is_equipped) {
        send_to_player(sess, "You unequip %s first.\n", check->name);
        equipment_unequip(&sess->character, args);
        check->is_equipped = false;
    }

    Item *item = inventory_remove(&sess->character.inventory, args);
    if (item) {
        room_add_item(sess->current_room, item);
        send_to_player(sess, "You drop %s.\n", item->name);

        char msg[256];
        snprintf(msg, sizeof(msg), "%s drops %s.\n", sess->username, item->name);
        room_broadcast(sess->current_room, msg, sess);
    } else {
        send_to_player(sess, "You don't have that item.\n");
    }
}

/* =============== PHASE 5: PSIONICS & MAGIC COMMANDS =============== */

/* Use a psionic power */
void cmd_use_power(PlayerSession *sess, const char *args) {
    if (!sess) return;
    
    if (!args || !*args) {
        send_to_player(sess, "Use what power? Try 'use <power name>'\n");
        psionics_display_powers(sess);
        return;
    }
    
    Character *ch = &sess->character;
    PsionicPower *power = psionics_find_power_by_name(args);
    
    if (!power) {
        send_to_player(sess, "Unknown psionic power '%s'.\n", args);
        return;
    }
    
    /* Try to activate power */
    psionics_activate_power(sess, ch, power->id, "");
}

/* Display known psionic powers */
void cmd_powers(PlayerSession *sess, const char *args) {
    if (!sess) return;
    psionics_display_powers(sess);
}

/* Display ISP status */
void cmd_isp(PlayerSession *sess, const char *args) {
    if (!sess) return;
    psionics_display_isp(sess);
}

/* Cast a magic spell */
void cmd_cast(PlayerSession *sess, const char *args) {
    if (!sess) return;
    
    if (!args || !*args) {
        send_to_player(sess, "Cast what spell? Try 'cast <spell name>'\n");
        magic_display_spells(sess);
        return;
    }
    
    Character *ch = &sess->character;
    MagicSpell *spell = magic_find_spell_by_name(args);
    
    if (!spell) {
        send_to_player(sess, "Unknown spell '%s'.\n", args);
        return;
    }
    
    /* Try to start casting */
    magic_start_casting(sess, ch, spell->id, "");
}

/* Display known spells */
void cmd_spells(PlayerSession *sess, const char *args) {
    if (!sess) return;
    magic_display_spells(sess);
}

/* Display PPE status */
void cmd_ppe(PlayerSession *sess, const char *args) {
    if (!sess) return;
    magic_display_ppe(sess);
}

/* Meditate to recover ISP/PPE */
void cmd_meditate(PlayerSession *sess, const char *args) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    
    if (ch->psionics.is_meditating || ch->magic.is_meditating) {
        send_to_player(sess, "You're already meditating.\n");
        return;
    }
    
    /* Start meditation for both systems */
    ch->psionics.is_meditating = true;
    ch->psionics.meditation_rounds_active = 1;
    ch->magic.is_meditating = true;
    ch->magic.meditation_rounds_active = 1;
    
    send_to_player(sess, "You begin to meditate, centering yourself...\n");
}

/* ========== CLAN SYSTEM ========== */

void cmd_clan(PlayerSession *sess, const char *args) {
    if (!sess) return;

    if (sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }

    Character *ch = &sess->character;

    /* No argument: show current clan or list available */
    if (!args || !(*args)) {
        if (ch->clan && ch->clan[0]) {
            send_to_player(sess, "You are a member of Clan %s.\n", ch->clan);
        } else {
            send_to_player(sess, "You do not belong to any clan.\n");
        }
        send_to_player(sess, "\nAvailable Clans:\n");
        send_to_player(sess, "  aerihman  - The Aerihman Clan (Atlantean only)\n");
        send_to_player(sess, "              Unlocks: Sunaj Assassin O.C.C.\n");
        send_to_player(sess, "\nUsage: clan <name>\n");
        return;
    }

    /* Already in a clan */
    if (ch->clan && ch->clan[0]) {
        send_to_player(sess, "You are already a member of Clan %s.\n", ch->clan);
        send_to_player(sess, "You cannot change clans.\n");
        return;
    }

    /* Handle "clan aerihman" */
    if (strcasecmp(args, "aerihman") == 0) {
        /* Must be Atlantean */
        if (!ch->race || (strcasecmp(ch->race, "Atlantean") != 0 &&
                          strcasecmp(ch->race, "True Atlantean") != 0)) {
            send_to_player(sess, "Only Atlanteans may join Clan Aerihman.\n");
            return;
        }

        /* Set clan */
        if (ch->clan) free(ch->clan);
        ch->clan = strdup("Aerihman");

        send_to_player(sess, "\n");
        send_to_player(sess, "=========================================\n");
        send_to_player(sess, "  You pledge yourself to Clan Aerihman.\n");
        send_to_player(sess, "=========================================\n");
        send_to_player(sess, "\n");
        send_to_player(sess, "The shadows embrace you. Ancient tattoo magic\n");
        send_to_player(sess, "courses through your veins as the clan's secrets\n");
        send_to_player(sess, "are revealed to you.\n\n");

        /* Reassign OCC to Sunaj Assassin */
        if (ch->occ) free(ch->occ);
        ch->occ = strdup("Sunaj Assassin");

        /* Reassign skills for new OCC */
        occ_assign_skills(sess, ch->occ);

        /* Apply OCC stat bonuses from LPC file */
        load_occ_data(ch->occ, ch);

        /* Boost PPE and ISP for Sunaj tattoo magic */
        if (ch->max_ppe < 30) {
            ch->max_ppe = 30;
            ch->ppe = 30;
        }
        if (ch->max_isp < 20) {
            ch->max_isp = 20;
            ch->isp = 20;
        }

        /* Grant shadow suit armor */
        Item *armor = item_create(27); /* Light EBA as shadow suit */
        if (armor) {
            inventory_add(&ch->inventory, armor);
            equipment_equip(ch, sess, armor);
            send_to_player(sess, "You receive Sunaj Shadow Armor.\n");
        }

        /* Grant vibro-blade as shadow weapon */
        Item *weapon = item_create(1); /* Vibro-Blade */
        if (weapon) {
            inventory_add(&ch->inventory, weapon);
            equipment_equip(ch, sess, weapon);
            send_to_player(sess, "You receive a Shadow Blade.\n");
        }

        send_to_player(sess, "\nYour O.C.C. is now: Sunaj Assassin\n");
        send_to_player(sess, "Your skills have been updated.\n");

        /* Auto-save */
        if (save_character(sess)) {
            send_to_player(sess, "Character saved.\n");
        }
    } else {
        send_to_player(sess, "Unknown clan '%s'. Type 'clan' to see available clans.\n", args);
    }
}

/* ========== LANGUAGE COMMANDS ========== */

/* Switch default speaking language */
void cmd_speak(PlayerSession *sess, const char *args) {
    if (!sess) return;
    Character *ch = &sess->character;

    if (!args || !(*args)) {
        if (ch->current_language) {
            send_to_player(sess, "You are currently speaking %s.\n", ch->current_language);
        } else {
            send_to_player(sess, "You have no language set.\n");
        }
        send_to_player(sess, "Usage: speak <language>\n");
        return;
    }

    /* Check if player knows this language */
    for (int i = 0; i < ch->num_languages; i++) {
        if (ch->languages[i] && strcasecmp(ch->languages[i], args) == 0) {
            if (ch->current_language) free(ch->current_language);
            ch->current_language = strdup(ch->languages[i]);
            send_to_player(sess, "You will now speak in %s.\n", ch->current_language);
            return;
        }
    }
    send_to_player(sess, "You don't know the language '%s'.\n", args);
}

/* List known languages */
void cmd_languages(PlayerSession *sess, const char *args) {
    if (!sess) return;
    Character *ch = &sess->character;
    int w = FRAME_WIDTH;
    char buf[128];

    send_to_player(sess, "\r\n");
    frame_top(sess, w);
    frame_title(sess, "KNOWN LANGUAGES", w);
    frame_sep(sess, w);

    if (ch->num_languages == 0) {
        frame_line(sess, "You don't know any languages.", w);
    } else {
        for (int i = 0; i < ch->num_languages; i++) {
            if (ch->languages[i]) {
                const char *marker = "";
                if (ch->current_language && strcasecmp(ch->languages[i], ch->current_language) == 0)
                    marker = "  (default)";
                snprintf(buf, sizeof(buf), "%s%s", ch->languages[i], marker);
                frame_line(sess, buf, w);
            }
        }
    }

    frame_sep(sess, w);
    frame_line(sess, "Use 'speak <language>' to change default.", w);
    frame_bottom(sess, w);
}

/* ========== WIZARD GRANT/REVOKE COMMANDS ========== */

/* Check if character knows a language */
static int character_knows_language(Character *ch, const char *lang) {
    for (int i = 0; i < ch->num_languages; i++) {
        if (ch->languages[i] && strcasecmp(ch->languages[i], lang) == 0)
            return 1;
    }
    return 0;
}

/* Remove a language from character (returns 1 if removed) */
static int character_remove_language(Character *ch, const char *lang) {
    for (int i = 0; i < ch->num_languages; i++) {
        if (ch->languages[i] && strcasecmp(ch->languages[i], lang) == 0) {
            free(ch->languages[i]);
            for (int j = i; j < ch->num_languages - 1; j++) {
                ch->languages[j] = ch->languages[j + 1];
            }
            ch->languages[ch->num_languages - 1] = NULL;
            ch->num_languages--;

            /* Reset current_language if it was removed */
            if (ch->current_language && strcasecmp(ch->current_language, lang) == 0) {
                free(ch->current_language);
                ch->current_language = (ch->num_languages > 0 && ch->languages[0])
                    ? strdup(ch->languages[0]) : NULL;
            }
            return 1;
        }
    }
    return 0;
}

/* Grant skill/spell/psionic/language to a player */
void cmd_grant(PlayerSession *sess, const char *args) {
    if (!sess) return;

    if (sess->privilege_level < 1) {
        send_to_player(sess, "You don't have permission to use that command.\n");
        return;
    }

    if (!args || !(*args)) {
        send_to_player(sess, "Usage: grant <player> <type> <name>\n");
        send_to_player(sess, "Types: skill, spell, psionic, language\n");
        return;
    }

    char target_name[64];
    char type[32];
    char name[256];

    /* Parse: "player type name with spaces" */
    if (sscanf(args, "%63s %31s %255[^\n]", target_name, type, name) != 3) {
        send_to_player(sess, "Usage: grant <player> <type> <name>\n");
        send_to_player(sess, "Types: skill, spell, psionic, language\n");
        return;
    }

    PlayerSession *target = find_player_by_name(target_name);
    if (!target) {
        send_to_player(sess, "Player '%s' not found.\n", target_name);
        return;
    }

    Character *ch = &target->character;

    if (strcasecmp(type, "skill") == 0) {
        /* Check if already has this skill by name */
        int skill_id = skill_get_id_by_name(name);
        if (skill_id < 0) {
            send_to_player(sess, "Unknown skill '%s'.\n", name);
            return;
        }
        for (int i = 0; i < ch->num_skills; i++) {
            if (ch->skills[i].skill_id == skill_id) {
                send_to_player(sess, "%s already knows skill '%s'.\n", target->username, name);
                return;
            }
        }
        if (ch->num_skills >= 20) {
            send_to_player(sess, "%s has maximum skills (20).\n", target->username);
            return;
        }
        ch->skills[ch->num_skills].skill_id = skill_id;
        ch->skills[ch->num_skills].percentage = 30;  /* Starting percentage */
        ch->skills[ch->num_skills].uses = 0;
        ch->num_skills++;

        send_to_player(sess, "You grant %s the skill: %s\n", target->username, name);
        send_to_player(target, "A wizard has granted you the skill: %s\n", name);
    }
    else if (strcasecmp(type, "spell") == 0) {
        MagicSpell *spell = magic_find_spell_by_name(name);
        if (!spell) {
            send_to_player(sess, "Unknown spell '%s'.\n", name);
            return;
        }
        KnownSpell *known = magic_find_known_spell(ch, spell->id);
        if (known) {
            send_to_player(sess, "%s already knows spell '%s'.\n", target->username, name);
            return;
        }
        magic_learn_spell(ch, spell->id);

        send_to_player(sess, "You grant %s the spell: %s\n", target->username, spell->name);
        send_to_player(target, "A wizard has granted you the spell: %s\n", spell->name);
    }
    else if (strcasecmp(type, "psionic") == 0) {
        PsionicPower *power = psionics_find_power_by_name(name);
        if (!power) {
            send_to_player(sess, "Unknown psionic power '%s'.\n", name);
            return;
        }
        KnownPower *known = psionics_find_known_power(ch, power->id);
        if (known) {
            send_to_player(sess, "%s already knows psionic '%s'.\n", target->username, name);
            return;
        }
        psionics_learn_power(ch, power->id);

        send_to_player(sess, "You grant %s the psionic: %s\n", target->username, power->name);
        send_to_player(target, "A wizard has granted you the psionic: %s\n", power->name);
    }
    else if (strcasecmp(type, "language") == 0) {
        if (character_knows_language(ch, name)) {
            send_to_player(sess, "%s already knows language '%s'.\n", target->username, name);
            return;
        }
        if (!character_add_language(ch, name)) {
            send_to_player(sess, "%s has maximum languages (16).\n", target->username);
            return;
        }
        send_to_player(sess, "You grant %s the language: %s\n", target->username, name);
        send_to_player(target, "A wizard has granted you the language: %s\n", name);
    }
    else {
        send_to_player(sess, "Invalid type '%s'. Use: skill, spell, psionic, language\n", type);
        return;
    }

    /* Auto-save target */
    save_character(target);
}

/* Revoke skill/spell/psionic/language from a player */
void cmd_revoke(PlayerSession *sess, const char *args) {
    if (!sess) return;

    if (sess->privilege_level < 1) {
        send_to_player(sess, "You don't have permission to use that command.\n");
        return;
    }

    if (!args || !(*args)) {
        send_to_player(sess, "Usage: revoke <player> <type> <name>\n");
        send_to_player(sess, "Types: skill, spell, psionic, language\n");
        return;
    }

    char target_name[64];
    char type[32];
    char name[256];

    if (sscanf(args, "%63s %31s %255[^\n]", target_name, type, name) != 3) {
        send_to_player(sess, "Usage: revoke <player> <type> <name>\n");
        send_to_player(sess, "Types: skill, spell, psionic, language\n");
        return;
    }

    PlayerSession *target = find_player_by_name(target_name);
    if (!target) {
        send_to_player(sess, "Player '%s' not found.\n", target_name);
        return;
    }

    Character *ch = &target->character;

    if (strcasecmp(type, "skill") == 0) {
        int skill_id = skill_get_id_by_name(name);
        if (skill_id < 0) {
            send_to_player(sess, "Unknown skill '%s'.\n", name);
            return;
        }
        int found = 0;
        for (int i = 0; i < ch->num_skills; i++) {
            if (ch->skills[i].skill_id == skill_id) {
                for (int j = i; j < ch->num_skills - 1; j++) {
                    ch->skills[j] = ch->skills[j + 1];
                }
                ch->num_skills--;
                found = 1;
                break;
            }
        }
        if (!found) {
            send_to_player(sess, "%s doesn't have skill '%s'.\n", target->username, name);
            return;
        }
        send_to_player(sess, "You revoke %s's skill: %s\n", target->username, name);
        send_to_player(target, "A wizard has revoked your skill: %s\n", name);
    }
    else if (strcasecmp(type, "spell") == 0) {
        MagicSpell *spell = magic_find_spell_by_name(name);
        if (!spell) {
            send_to_player(sess, "Unknown spell '%s'.\n", name);
            return;
        }
        int found = 0;
        for (int i = 0; i < ch->magic.spell_count; i++) {
            if (ch->magic.spells[i].spell_id == spell->id) {
                for (int j = i; j < ch->magic.spell_count - 1; j++) {
                    ch->magic.spells[j] = ch->magic.spells[j + 1];
                }
                ch->magic.spell_count--;
                found = 1;
                break;
            }
        }
        if (!found) {
            send_to_player(sess, "%s doesn't know spell '%s'.\n", target->username, name);
            return;
        }
        send_to_player(sess, "You revoke %s's spell: %s\n", target->username, spell->name);
        send_to_player(target, "A wizard has revoked your spell: %s\n", spell->name);
    }
    else if (strcasecmp(type, "psionic") == 0) {
        PsionicPower *power = psionics_find_power_by_name(name);
        if (!power) {
            send_to_player(sess, "Unknown psionic power '%s'.\n", name);
            return;
        }
        int found = 0;
        for (int i = 0; i < ch->psionics.power_count; i++) {
            if (ch->psionics.powers[i].power_id == power->id) {
                for (int j = i; j < ch->psionics.power_count - 1; j++) {
                    ch->psionics.powers[j] = ch->psionics.powers[j + 1];
                }
                ch->psionics.power_count--;
                found = 1;
                break;
            }
        }
        if (!found) {
            send_to_player(sess, "%s doesn't know psionic '%s'.\n", target->username, name);
            return;
        }
        send_to_player(sess, "You revoke %s's psionic: %s\n", target->username, power->name);
        send_to_player(target, "A wizard has revoked your psionic: %s\n", power->name);
    }
    else if (strcasecmp(type, "language") == 0) {
        if (!character_remove_language(ch, name)) {
            send_to_player(sess, "%s doesn't know language '%s'.\n", target->username, name);
            return;
        }
        send_to_player(sess, "You revoke %s's language: %s\n", target->username, name);
        send_to_player(target, "A wizard has revoked your language: %s\n", name);
    }
    else {
        send_to_player(sess, "Invalid type '%s'. Use: skill, spell, psionic, language\n", type);
        return;
    }

    /* Auto-save target */
    save_character(target);
}
