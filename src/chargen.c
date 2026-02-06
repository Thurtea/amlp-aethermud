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
#include "debug.h"
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

/* External function from session.c */
extern void send_to_player(PlayerSession *session, const char *format, ...);

/* ========== COMPLETE RACE AND OCC DATABASE ========== */


/* MERGED RACE DATABASE - Rifts + AetherMUD (72 Total) */
const RaceOCCInfo ALL_RACES[] = {
    /* Core Humanoid Races */
    {"Human", "Baseline race, adaptable and determined"},
    {"Elf", "Graceful and magical, attuned to nature"},
    {"Dwarf", "Stout and resilient, master craftsmen"},
    {"Gnome", "Small magical being, tech-savvy"},
    {"Halfling", "Small folk, lucky and brave"},
    {"Orc", "Savage warrior race"},
    {"Goblin", "Small cunning supernatural creature"},
    {"Hobgoblin", "Larger, fierce goblinoid"},
    {"Ogre", "Large brutish humanoid"},
    {"Troll", "Regenerating savage humanoid"},
    {"Minotaur", "Bull-headed warrior of great strength"},
    
    /* Atlantean Types */
    {"Atlantean", "Dimensional traveler with tattoo magic"},
    {"True Atlantean", "Pure-blood Atlantean lineage"},
    
    /* Giant Races */
    {"Algor Frost Giant", "Ice-dwelling giant of the north"},
    {"Nimro Fire Giant", "Flame-wielding massive warrior"},
    {"Jotan", "Stone giant, master of earth"},
    {"Titan", "Divine giant of legendary power"},
    
    /* Dragons (All Types) */
    {"Fire Dragon", "Ancient wyrm of flame and destruction"},
    {"Ice Dragon", "Frost wyrm of the frozen wastes"},
    {"Great Horned Dragon", "Massive horned draconic lord"},
    {"Thunder Lizard Dragon", "Storm-calling dragon beast"},
    {"Dragon Hatchling", "Young but powerful dragon"},
    {"Adult Dragon", "Mature draconic being"},
    {"Ancient Dragon", "Millenia-old legendary wyrm"},
    {"Thorny Dragon", "Spiked dragon variant"},
    
    /* Fae & Supernatural */
    {"Changeling", "Shapeshifting fae creature"},
    {"Common Faerie", "Tiny winged fae being"},
    {"Common Pixie", "Mischievous tiny fae"},
    {"Frost Pixie", "Ice-aligned pixie variant"},
    {"Green Wood Faerie", "Forest-dwelling fae guardian"},
    {"Night-Elves Faerie", "Dark fae of the shadows"},
    {"Silver Bells Faerie", "Musical enchanting faerie"},
    {"Tree Sprite", "Nature spirit of the woods"},
    {"Water Sprite", "Aquatic elemental spirit"},
    {"Brownie", "Helpful household fae"},
    {"Bogie", "Mischievous shadow fae"},
    
    /* Bestial & Shapeshifters */
    {"Dog Boy", "Canine mutant bred by Coalition"},
    {"Bearman", "Ursine humanoid warrior"},
    {"Kankoran", "Wolf-kin nomadic hunter"},
    {"Rahu-man", "Tiger-folk warrior race"},
    {"Ratling", "Cunning rat-like humanoid"},
    {"Werewolf", "Shapeshifting wolf-human"},
    {"Werebear", "Shapeshifting bear-human"},
    {"Weretiger", "Shapeshifting tiger-human"},
    {"Wolfen", "Noble lupine warrior race"},
    {"Cat Girl", "Feline humanoid, agile and curious"},
    {"Mutant Animal", "Uplifted animal with intelligence"},
    
    /* Avian & Exotic */
    {"Gargoyle", "Stone-skinned supernatural guardian"},
    {"Gurgoyle", "Aquatic gargoyle variant"},
    {"Hawrke Duhk", "Hawk-folk aerial warrior"},
    {"Hawrk-ka", "Elite hawk-rider variant"},
    {"Equinoid", "Horse-kin centauroid race"},
    
    /* Psychic & Psionic RCCs */
    {"Burster", "Pyrokinetic psychic warrior"},
    {"Mind Melter", "Master psychic, multiple disciplines"},
    {"Conservator", "Psionic defender of nature"},
    {"Psi-Stalker", "Anti-magic psionic hunter (CS)"},
    {"Wild Psi-Stalker", "Feral psionic hunter"},
    {"Psi-Ghost", "Psychic entity, telekinetic mastery"},
    {"Psi-Healer", "Psychic healing specialist"},
    {"Mind Bleeder", "Psychic vampire, drains ISP"},
    
    /* Supernatural & Undead */
    {"Vampire", "Undead blood drinker"},
    {"Secondary Vampire", "Lesser vampire spawn"},
    {"Wild Vampire", "Feral uncontrolled vampire"},
    {"Demon", "Powerful supernatural evil entity"},
    {"Deevil", "Lesser demon from dark dimensions"},
    {"Basilisk", "Serpentine gaze-weapon creature"},
    {"Nightbane", "Shape-shifter between human/monster"},
    {"Godling", "Offspring of divine beings"},
    
    /* Dimensional & Alien */
    {"D-Bee", "Dimensional being from another reality"},
    {"Coyle", "Alien symbiote shapeshifter"},
    {"Noli", "Four-armed alien symbiote race"},
    {"Eandroth", "Insectoid alien warrior race"},
    {"Quick-Flex", "Incredibly fast alien species"},
    {"Trimadore", "Crystalline energy being"},
    {"Uteni", "Fur-covered peaceful alien"},
    {"Promethean", "Artificial life seeking humanity"},
    
    /* Specialized & Unique */
    {"Brodkill", "Demon-cursed mutant super-soldier"},
    {"Cosmo-Knight", "Cosmic guardian with stellar powers"},
    {"Dragon Juicer", "Dragon blood-enhanced soldier"},
    {"Mega-Juicer", "Ultra-enhanced combat juicer"},
    {"Titan Juicer", "Massive juicer, extended lifespan"},
    {"Pogtal - Dragon Slayer", "Anti-dragon specialist race"},
    
    /* Splugorth Slaves & Minions */
    {"Splugorth", "Ancient evil intelligence"},
    {"Splugorth Minion", "Enslaved warrior of Splugorth"},
    {"Splynn Slave", "Enslaved from dimensional market"},
    {"Minion", "Bio-wizard creation, enslaved"},
    
    /* Special */
    {"Simvan", "Monster-riding nomadic warrior"}
};

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

#define NUM_RACES (sizeof(ALL_RACES) / sizeof(RaceOCCInfo))
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

/* Init car generation */
void chargen_init(PlayerSession *sess) {
    if (!sess) return;
    
    sess->chargen_state = CHARGEN_RACE_SELECT;
    sess->chargen_page = 0;
    sess->chargen_temp_choice = 0;
    
    send_to_player(sess, "\n");
    send_to_player(sess, "=========================================\n");
    send_to_player(sess, "      CHARACTER CREATION SYSTEM\n");
    send_to_player(sess, "        Rifts Earth - 109 P.A.\n");
    send_to_player(sess, "=========================================\n");
    send_to_player(sess, "\n");
    
    /* Display first page of races */
    int total_pages = (NUM_RACES + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    send_to_player(sess, "=== SELECT YOUR RACE (Page %d/%d) ===\n\n", 
                   sess->chargen_page + 1, total_pages);
    
    int start = sess->chargen_page * ITEMS_PER_PAGE;
    int end = start + ITEMS_PER_PAGE;
    if (end > NUM_RACES) end = NUM_RACES;
    
    for (int i = start; i < end; i++) {
        send_to_player(sess, "  %2d. %s - %s\n", 
                      i + 1, ALL_RACES[i].name, ALL_RACES[i].desc);
    }
    
    send_to_player(sess, "\n");
    if (sess->chargen_page > 0) {
        send_to_player(sess, "  Type 'p' for previous page\n");
    }
    if (end < NUM_RACES) {
        send_to_player(sess, "  Type 'n' for next page\n");
    }
    send_to_player(sess, "\nEnter choice (1-%d): ", NUM_RACES);
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

    ch->introduced_count = 0;
    for (i = 0; i < 32; i++) ch->introduced_to[i] = NULL;
    
    /* ISP/PPE will be calculated in psionics_init_abilities() and magic_init_abilities() */
    /* These are called in chargen_complete() */

    /* Apply race / O.C.C. derived bonuses */
    apply_race_and_occ(sess);
}

/* Display character stats */
void chargen_display_stats(PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    
    send_to_player(sess, "\n");
    send_to_player(sess, "=======================================================\n");
    send_to_player(sess, "              YOUR CHARACTER SHEET\n");
    send_to_player(sess, "-------------------------------------------------------\n");
    send_to_player(sess, "  Name: %s\n", sess->username);
    send_to_player(sess, "  Race: %-20s  O.C.C.: %s\n", ch->race, ch->occ);
    send_to_player(sess, "-------------------------------------------------------\n");
    send_to_player(sess, "  ATTRIBUTES\n");
    send_to_player(sess, "  IQ: %-3d   ME: %-3d   MA: %-3d   PS: %-3d\n",
                  ch->stats.iq, ch->stats.me, ch->stats.ma, ch->stats.ps);
    send_to_player(sess, "  PP: %-3d   PE: %-3d   PB: %-3d   SPD: %-3d\n",
                  ch->stats.pp, ch->stats.pe, ch->stats.pb, ch->stats.spd);
    send_to_player(sess, "-------------------------------------------------------\n");
    if (ch->health_type == MDC_ONLY) {
        send_to_player(sess, "  MDC: %-3d/%-3d\n", ch->mdc, ch->max_mdc);
    } else if (ch->health_type == HP_ONLY) {
        send_to_player(sess, "  HP: %-3d/%-3d\n", ch->hp, ch->max_hp);
    } else {
        send_to_player(sess, "  HP: %-3d/%-3d    S.D.C.: %-3d/%-3d\n",
                      ch->hp, ch->max_hp, ch->sdc, ch->max_sdc);
    }

    if (ch->max_isp > 0) {
        send_to_player(sess, "  I.S.P.: %-3d/%-3d (Psionic Energy)\n",
                      ch->isp, ch->max_isp);
    } else if (ch->psionics.isp_max > 0) {
        send_to_player(sess, "  I.S.P.: %-3d/%-3d (Psionic Energy)\n",
                      ch->psionics.isp_current, ch->psionics.isp_max);
    }

    if (ch->max_ppe > 0) {
        send_to_player(sess, "  P.P.E.: %-3d/%-3d (Magical Energy)\n",
                      ch->ppe, ch->max_ppe);
    } else if (ch->magic.ppe_max > 0) {
        send_to_player(sess, "  P.P.E.: %-3d/%-3d (Magical Energy)\n",
                      ch->magic.ppe_current, ch->magic.ppe_max);
    }
    
    send_to_player(sess, "=======================================================\n");
}

/* Complete character generation */
void chargen_complete(PlayerSession *sess) {
    if (!sess) return;
    
    sess->chargen_state = CHARGEN_COMPLETE;
    sess->state = STATE_PLAYING;
    
    /* Initialize inventory and equipment (Phase 4) */
    inventory_init(&sess->character.inventory, sess->character.stats.ps);
    equipment_init(&sess->character.equipment);
    
    /* Initialize psionics and magic (Phase 5) */
    psionics_init_abilities(&sess->character);
    magic_init_abilities(&sess->character);
    
    /* Add starting powers and spells based on OCC */
    psionics_add_starting_powers(&sess->character, sess->character.occ);
    magic_add_starting_spells(&sess->character, sess->character.occ);
    
    /* Add starting equipment based on OCC */
    /* Combat OCCs get weapon + armor */
    if (strcasestr(sess->character.occ, "Juicer") || 
        strcasestr(sess->character.occ, "Cyber-Knight") ||
        strcasestr(sess->character.occ, "CS ") ||
        strcasestr(sess->character.occ, "Ranger") ||
        strcasestr(sess->character.occ, "Soldier") ||
        strcasestr(sess->character.occ, "Merc")) {
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
    }
    /* Magic OCCs get staff + healing potion */
    else if (strcasestr(sess->character.occ, "Walker") ||
             strcasestr(sess->character.occ, "Warlock") ||
             strcasestr(sess->character.occ, "Mystic") ||
             strcasestr(sess->character.occ, "Wizard")) {
        Item *staff = item_create(24); /* TW Fire Bolt Staff */
        Item *potion = item_create(40); /* Healing Potion */
        if (staff) {
            inventory_add(&sess->character.inventory, staff);
            equipment_equip(&sess->character, sess, staff);
        }
        if (potion) inventory_add(&sess->character.inventory, potion);
    }
    /* All characters get basic supplies */
    Item *ration = item_create(48); /* Food Ration */
    Item *water = item_create(49); /* Water Canteen */
    if (ration) inventory_add(&sess->character.inventory, ration);
    if (water) inventory_add(&sess->character.inventory, water);
    
    /* Place player in starting room */
    Room *start = room_get_start();
    if (start) {
        sess->current_room = start;
        room_add_player(start, sess);
    }
    
    send_to_player(sess, "\n");
    send_to_player(sess, "\033[1;32mCharacter creation complete!\033[0m\n");
    send_to_player(sess, "Welcome to Rifts Earth, %s!\n", sess->username);
    
    /* Auto-save new character */
    send_to_player(sess, "\nSaving your character...\n");
    if (save_character(sess)) {
        send_to_player(sess, "✓ Character saved!\n");
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
                int total_pages = (NUM_RACES + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
                if (sess->chargen_page < total_pages - 1) {
                    sess->chargen_page++;
                    /* Redisplay */
                    send_to_player(sess, "\n=== SELECT YOUR RACE (Page %d/%d) ===\n\n", 
                                   sess->chargen_page + 1, total_pages);
                    
                    int start = sess->chargen_page * ITEMS_PER_PAGE;
                    int end = start + ITEMS_PER_PAGE;
                    if (end > NUM_RACES) end = NUM_RACES;
                    
                    for (int i = start; i < end; i++) {
                        send_to_player(sess, "  %2d. %s - %s\n", 
                                      i + 1, ALL_RACES[i].name, ALL_RACES[i].desc);
                    }
                    
                    send_to_player(sess, "\n");
                    if (sess->chargen_page > 0) {
                        send_to_player(sess, "  Type 'p' for previous page\n");
                    }
                    if (end < NUM_RACES) {
                        send_to_player(sess, "  Type 'n' for next page\n");
                    }
                    send_to_player(sess, "\nEnter choice (1-%d): ", NUM_RACES);
                } else {
                    send_to_player(sess, "Already on last page.\nEnter choice (1-%d): ", NUM_RACES);
                }
                return;
            }
            
            if (input[0] == 'p' || input[0] == 'P') {
                if (sess->chargen_page > 0) {
                    sess->chargen_page--;
                    /* Redisplay */
                    int total_pages = (NUM_RACES + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
                    send_to_player(sess, "\n=== SELECT YOUR RACE (Page %d/%d) ===\n\n", 
                                   sess->chargen_page + 1, total_pages);
                    
                    int start = sess->chargen_page * ITEMS_PER_PAGE;
                    int end = start + ITEMS_PER_PAGE;
                    if (end > NUM_RACES) end = NUM_RACES;
                    
                    for (int i = start; i < end; i++) {
                        send_to_player(sess, "  %2d. %s - %s\n", 
                                      i + 1, ALL_RACES[i].name, ALL_RACES[i].desc);
                    }
                    
                    send_to_player(sess, "\n");
                    if (sess->chargen_page > 0) {
                        send_to_player(sess, "  Type 'p' for previous page\n");
                    }
                    if (end < NUM_RACES) {
                        send_to_player(sess, "  Type 'n' for next page\n");
                    }
                    send_to_player(sess, "\nEnter choice (1-%d): ", NUM_RACES);
                } else {
                    send_to_player(sess, "Already on first page.\nEnter choice (1-%d): ", NUM_RACES);
                }
                return;
            }
            
            /* Handle selection */
            if (choice >= 1 && choice <= NUM_RACES) {
                ch->race = strdup(ALL_RACES[choice - 1].name);
                
                send_to_player(sess, "\nYou selected: \033[1;32m%s\033[0m\n\n", ch->race);
                
                /* Set placeholder OCC - will be assigned by wizard */
                ch->occ = strdup("Awaiting Wizard Assignment");
                
                send_to_player(sess, "Your O.C.C. will be assigned by a wizard.\n");
                send_to_player(sess, "Please send a 'tell' to a wizard requesting an O.C.C.\n\n");
                
                send_to_player(sess, "Rolling your attributes...\n");
                
                /* Skip OCC selection - go directly to stats */
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
            /* OCC selection disabled - wizards assign OCCs via wiz-tools instead */
            send_to_player(sess, "O.C.C. selection is handled by game administrators.\n");
            send_to_player(sess, "Please contact a wizard for your O.C.C. assignment.\n");
            break;
            
        case CHARGEN_STATS_CONFIRM:
            if (strncasecmp(input, "yes", 3) == 0 || strncasecmp(input, "y", 1) == 0) {
                chargen_complete(sess);
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
    
    // For Phase 3, we'll implement basic NPC combat
    // For now, demonstrate combat initiation
    send_to_player(sess, "Combat system ready! Use 'strike' or 'shoot' commands.\n");
    send_to_player(sess, "(Full combat with NPCs coming in next iteration)\n");
}

void cmd_strike(PlayerSession *sess, const char *args) {
    if (!sess || sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }
    
    // Check if in combat
    CombatRound *combat = combat_get_active(sess);
    if (!combat) {
        send_to_player(sess, "You are not in combat.\n");
        return;
    }
    
    // Find this player's participant
    CombatParticipant *attacker = NULL;
    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (p->session == sess) {
            attacker = p;
            break;
        }
    }
    
    if (!attacker) {
        send_to_player(sess, "Error: You are not in this combat.\n");
        return;
    }
    
    // Check if it's this player's turn
    if (combat->current != attacker) {
        send_to_player(sess, "It is not your turn.\n");
        return;
    }
    
    // Check if already acted
    if (attacker->actions_remaining <= 0) {
        send_to_player(sess, "You have already acted this round.\n");
        return;
    }
    
    // Find target (for now, just attack the other participant)
    CombatParticipant *target = NULL;
    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (p != attacker) {
            target = p;
            break;
        }
    }
    
    if (!target) {
        send_to_player(sess, "No valid target found.\n");
        return;
    }
    
    // Perform melee attack
    DamageResult result = combat_attack_melee(attacker, target);
    
    // Use up action
    attacker->actions_remaining--;
    
    // Check if target died
    if (result.is_kill) {
        combat_award_experience(attacker, target);
        combat_remove_participant(combat, target);
        
        // End combat if only one participant left
        if (combat->num_participants <= 1) {
            combat_end(combat);
            return;
        }
    }
    
    // Advance to next turn
    combat_next_turn(combat);
}

void cmd_shoot(PlayerSession *sess, const char *args) {
    if (!sess || sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }
    
    // Check if in combat
    CombatRound *combat = combat_get_active(sess);
    if (!combat) {
        send_to_player(sess, "You are not in combat.\n");
        return;
    }
    
    // Find this player's participant
    CombatParticipant *attacker = NULL;
    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (p->session == sess) {
            attacker = p;
            break;
        }
    }
    
    if (!attacker) {
        send_to_player(sess, "Error: You are not in this combat.\n");
        return;
    }
    
    // Check if it's this player's turn
    if (combat->current != attacker) {
        send_to_player(sess, "It is not your turn.\n");
        return;
    }
    
    // Check if already acted
    if (attacker->actions_remaining <= 0) {
        send_to_player(sess, "You have already acted this round.\n");
        return;
    }
    
    // Find target (for now, just attack the other participant)
    CombatParticipant *target = NULL;
    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (p != attacker) {
            target = p;
            break;
        }
    }
    
    if (!target) {
        send_to_player(sess, "No valid target found.\n");
        return;
    }
    
    // Perform ranged attack
    DamageResult result = combat_attack_ranged(attacker, target);
    
    // Use up action
    attacker->actions_remaining--;
    
    // Check if target died
    if (result.is_kill) {
        combat_award_experience(attacker, target);
        combat_remove_participant(combat, target);
        
        // End combat if only one participant left
        if (combat->num_participants <= 1) {
            combat_end(combat);
            return;
        }
    }
    
    // Advance to next turn
    combat_next_turn(combat);
}

void cmd_dodge(PlayerSession *sess, const char *args) {
    if (!sess || sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }
    
    // Check if in combat
    CombatRound *combat = combat_get_active(sess);
    if (!combat) {
        send_to_player(sess, "You are not in combat.\n");
        return;
    }
    
    // Find this player's participant
    CombatParticipant *defender = NULL;
    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (p->session == sess) {
            defender = p;
            break;
        }
    }
    
    if (!defender) {
        send_to_player(sess, "Error: You are not in this combat.\n");
        return;
    }
    
    // Check if it's this player's turn
    if (combat->current != defender) {
        send_to_player(sess, "It is not your turn.\n");
        return;
    }
    
    // Check if already acted
    if (defender->actions_remaining <= 0) {
        send_to_player(sess, "You have already acted this round.\n");
        return;
    }
    
    // Set defending flag
    defender->is_defending = true;
    defender->actions_remaining--;
    
    send_to_player(sess, "You take a defensive stance, ready to dodge incoming attacks.\n");
    
    // Advance to next turn
    combat_next_turn(combat);
}

void cmd_flee(PlayerSession *sess, const char *args) {
    if (!sess || sess->state != STATE_PLAYING) {
        send_to_player(sess, "You must complete character creation first.\n");
        return;
    }
    
    // Check if in combat
    CombatRound *combat = combat_get_active(sess);
    if (!combat) {
        send_to_player(sess, "You are not in combat.\n");
        return;
    }
    
    // Find this player's participant
    CombatParticipant *fleeing = NULL;
    for (CombatParticipant *p = combat->participants; p; p = p->next) {
        if (p->session == sess) {
            fleeing = p;
            break;
        }
    }
    
    if (!fleeing) {
        send_to_player(sess, "Error: You are not in this combat.\n");
        return;
    }
    
    // Roll SPD check (1d20 + SPD vs 15)
    int spd = fleeing->character->stats.spd;
    int roll = combat_d20();
    int total = roll + spd;
    
    if (total >= 15) {
        // Successful flee
        send_to_player(sess, "You successfully flee from combat!\n");
        
        char msg[256];
        snprintf(msg, sizeof(msg), "%s flees from combat!\n", fleeing->name);
        combat_broadcast(combat, msg);
        
        combat_remove_participant(combat, fleeing);
        
        // End combat if only one participant left
        if (combat->num_participants <= 1) {
            combat_end(combat);
        }
    } else {
        // Failed flee
        char msg[256];
        snprintf(msg, sizeof(msg), "You fail to escape! (Rolled %d+%d=%d vs 15)\n", roll, spd, total);
        send_to_player(sess, msg);
        fleeing->actions_remaining--;
        
        // Advance to next turn
        combat_next_turn(combat);
    }
}

/* ========== CHARACTER PERSISTENCE ========== */

/* Check if a character save file exists */
int character_exists(const char *username) {
    if (!username || !username[0]) return 0;
    
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "lib/save/players/%s.dat", username);
    
    struct stat st;
    return (stat(filepath, &st) == 0);
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
    
    /* Write version (for future compatibility) */
    uint16_t version = 1;
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
    
    /* Write timestamp */
    time_t now = time(NULL);
    fwrite(&now, sizeof(time_t), 1, f);
    
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
    
    if (version != 1) {
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
    fread(&ch->psionics.isp_current, sizeof(int), 1, f);
    fread(&ch->psionics.isp_max, sizeof(int), 1, f);
    fread(&ch->magic.ppe_current, sizeof(int), 1, f);
    fread(&ch->magic.ppe_max, sizeof(int), 1, f);
    
    /* Read current room ID */
    int room_id;
    fread(&room_id, sizeof(int), 1, f);
    
    /* Read timestamp (for info only) */
    time_t saved_time;
    fread(&saved_time, sizeof(time_t), 1, f);
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

    fclose(f);

    INFO_LOG("Character '%s' loaded from %s (saved %ld seconds ago)", 
            username, filepath, time(NULL) - saved_time);

    /* Set room pointer */
    sess->current_room = room_get_by_id(room_id);
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
        send_to_player(sess, "Equip what? Try 'equip <item name>'\n");
        return;
    }
    
    Character *ch = &sess->character;
    Item *item = inventory_find(&ch->inventory, args);
    
    if (!item) {
        send_to_player(sess, "You don't have that item in your inventory.\n");
        return;
    }
    
    if (item->is_equipped) {
        send_to_player(sess, "You are already wearing/wielding that item.\n");
        return;
    }
    
    if (equipment_equip(ch, sess, item)) {
        send_to_player(sess, "You equip %s.\n", item->name);
    } else {
        send_to_player(sess, "You can't equip that right now.\n");
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

/* Get/pick up item (stub - would need room items) */
void cmd_get(PlayerSession *sess, const char *args) {
    if (!sess || !args || !*args) {
        send_to_player(sess, "Get what? Try 'get <item name>'\n");
        return;
    }
    
    send_to_player(sess, "There is no '%s' here to pick up.\n", args);
    /* TODO: Implement room items in future phase */
}

/* Drop item (stub - would need room items) */
void cmd_drop(PlayerSession *sess, const char *args) {
    if (!sess || !args || !*args) {
        send_to_player(sess, "Drop what? Try 'drop <item name>'\n");
        return;
    }
    
    Character *ch = &sess->character;
    Item *item = inventory_remove(&ch->inventory, args);
    
    if (item) {
        send_to_player(sess, "You drop %s.\n", item->name);
        item_free(item); /* For now, just destroy it */
        /* TODO: Add to room items in future phase */
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
