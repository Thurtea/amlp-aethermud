# Critical Files Deep Dive

## lib/master.lpc
- Lines: 43, Size: 1203
- Status: ⚠️ partial
- First comments: // master.c - Master object for AMLP driver // This is the first object loaded by the driver and handles system-level operations // Initialize the master object
- TODOs: 0


```text
// master.c - Master object for AMLP driver
// This is the first object loaded by the driver and handles system-level operations

void create() {
    // Initialize the master object
}

// Called when a new object is compiled
void compile_object(string file) {
    // Pre-compilation hook
}

// Called to handle runtime errors
void log_error(string file, string message) {
    // Error logging
}

// Returns the simul_efun object path
string epilog(string file) {
    return "/secure/simul_efun";
}

// Allow players to save their own files
int valid_write(string file, object caller, string func) {
    string caller_name, fname;

    if (!caller) return 0;
    if (!function_exists("query_name", caller)) return 0;
    caller_name = (string)caller->query_name();
    if (!caller_name || caller_name == "") return 0;

    // Check /save/players/<name>.o
    if (sscanf(file, "/save/players/%s.o", fname) == 1) {
        if (lower_case(fname) == lower_case(caller_name)) return 1;
    }

    // Check lib/save/players/<name>.o (possible relative path)
    if (sscanf(file, "lib/save/players/%s.o", fname) == 1) {
        if (lower_case(fname) == lower_case(caller_name)) return 1;
    }

    return 0;
}
```

## lib/llm_index.json
- Lines: 3103, Size: 329733
- Status: ✅ complete
- First comments: 
- TODOs: 0


```text
{
  "meta": {
    "source": "/home/thurtea/amlp-aethermud/archived-md/ttrpg-references.json",
    "entries": 156
  },
  "entries": [
    {
      "id": "101",
      "name": "101",
      "slug": "101",
      "section": "rcc",
      "description": "could be reading someone's mind, or mentally manipulate others, or a psychic, and identifies the psychic by code number and photograph.",
      "attribute_requirements": null,
      "occ_skills": null,
      "standard_equipment": null,
      "money": null,
      "cybernetics": null,
      "ppe": "minutes, but must stay within range and concentrate on maintaining                ment of psychic abilities. The remaining Permanent P.P.E. Base\n   the fire. Melee actions are reduced by half and fighting is impossible\n                                                                                     is 2D6.\n   unless he breaks his concentration, causing the fire to disappear.\n   However, any combustible items set ablaze will continue to burn                I.S.P.: To determine the character's initial amount of Inner Strength\n   and the fire will spread until extinguished, even after the fire erup-            Points, take the number of M.E. as the base, roll 3D4 x 10 and add\n   tion is gone.                                                                     it to the base number. The character gets another 10 I.S.P. for each\n      Bonus to Strike: This is a little different than the usual strike              additional level of experience.\n   attack. The burster must learn to judge distances and focus his                       I.S.P. is regained at the rate of 2 per hour of activity, or 12 per\n   thoughts in order to create the eruption exactly where he wants it.               hour of meditation or sleep.\n   So instead of an attack bonus, there is a Base Skill: 48% +4%                         Considered a master psionic, needs a 10 or higher to save versus\n   per level of experience (roll percentile dice). A failed roll means               psionic attack.\n   the eruption happens 2D6 yards/meters off target.",
      "source_range": [
        6306,
        6448
      ],
      "raw_snippet": "101 could be reading someone's mind, or mentally manipulate others, or a psychic, and identifies the psychic by code number and photograph. destroy a person with a thought. Unlike the practitioners of magic, who This can often be an embarrassing situation and many establishments must usually speak a spell or take some noticeable action before they will not allow psychics on the premises. Frequently, government strike, the psychic does not have to make any indication of his true facilities require that a psychic be escorted by a pair of psi- stalkers or nature to attack. He can be sitting down, drinking a cup of coffee, and a dog pack, especially in restricted areas, even if the authorities have kill somebody without so much as blinking, and nobody will be able authorized their access to\u2026",
      "suggested_target": "lib/occs/101.lpc"
    },
    {
      "id": "103",
      "name": "103",
      "slug": "103",
      "section": "rcc",
      "description": "The influence of ley line energy",
      "attribute_requirements": null,
      "occ_skills": null,
      "standard_equipment": [
        "body armor",
        "sleeping bag",
        "back pack",
        "utility/ammo",
        "belt",
        "canteen",
        "sunglasses or tinted goggles",
        "air filter or gas mask",
        "food rations for",
        "a week",
        "and personal items. Weapons will include a knife",
        "one",
        "energy and one non",
        "energy",
        "player's choice.",
        "Vehicle is limited to non",
        "military means of transportation",
        "and",
        "may include hover vehicles or souped",
        "up motorcycle or car."
      ],
      "money": "in saleable black market items.",
      "cybernetics": "natural powers.",
      "ppe": null,
      "source_range": [
        6449,
        6491
      ],
      "raw_snippet": "103 The influence of ley line energy The duration and range of the burster's psychic powers are in- creased by 50% whenever on or near (one mile/1.6 km) a ley line. The duration, range, and damage of the powers are doubled when at or near (one mile/1.6 km) a ley line nexus point! Skills: Like most psychics, the burster has minimal education, having spent much of the time learning and mastering the pyrokinetic pow- ers. The individual has come to rely on those powers, wits, and experience. The typical burster is a cocky, self-confident adventurer who prefers to use his or her powers and courage rather than skills or machines. At first level the psychic can speak American and one other language at 90% proficiency, selects two piloting skills (both with a + 10% bonus), and can select six\u2026",
      "suggested_target": "lib/occs/103.lpc"
    },
    {
      "id": "psi-stalker-r-c-c",
      "name": "Psi-Stalker R.C.C.",
      "slug": "psi-stalker-r-c-c",
      "section": "rcc",
      "description": "The Psi-stalker is a mutant whose psychic sensitive powers enable",
      "attribute_requirements": null,
      "occ_skills": null,
      "standard_equipment": null,
      "money": null,
      "cybernetics": null,
      "ppe": "the use of psychic energy (I.S.P. and P.P.E.) and can follow the distinc-\n      tive energy trail like a bloodhound following a specific scent. Even\n      though all creatures have a certain level of potential psychic energy\n      (P.P.E.), the psi-stalker can tell the subtle differences between normal\n      energies and psychic and magic energies. Some innate instinct draws\n      the stalker to those creatures who are psionic or magic. This same\n      instinct makes the mutant want to kill his prey and drink its P.P.E.\n      (which, for a brief instant, doubles when the victim dies). Fortunately,\n      psi-stalkers can train themselves not to kill, although they prefer to kill\n      and feed, and love the thrill of the hunt!\n         The Coalition States (CS) have trained people with the psi-stalker\n      instincts and abilities to become an elite military police force, special-\n      izing in hunting down psychic and magic criminals, supernatural beings,\n      and paranormal interlopers. In addition to the stalker's natural abilities,\n      the warriors are trained in basic military procedure and combat skills.",
      "source_range": [
        6492,
        6584
      ],
      "raw_snippet": "Psi-Stalker R.C.C. The Psi-stalker is a mutant whose psychic sensitive powers enable him to sense other psychics, psychic energy, and magic. The character can be human, or a D-Bee, or a mutoid. Unlike normal humans, the psi-stalker is a natural predator and P.P.E. vampire! The predator senses the use of psychic energy (I.S.P. and P.P.E.) and can follow the distinc- tive energy trail like a bloodhound following a specific scent. Even though all creatures have a certain level of potential psychic energy (P.P.E.), the psi-stalker can tell the subtle differences between normal energies and psychic and magic energies. Some innate instinct draws the stalker to those creatures who are psionic or magic. This same instinct makes the mutant want to kill his prey and drink its P.P.E. (which, for a\u2026",
      "suggested_target": "lib/occs/psi-stalker-r-c-c.lpc"
    },
    {
      "id": "105",
      "name": "105",
      "slug": "105",
      "section": "rcc",
      "description": "The preferred form of nourishment, even among civilized psi-",
      "attribute_requirements": {
        "roll": 3,
        "number": 5,
        "by": 50,
        "about": 2,
        "at": 70
      },
      "occ_skills": null,
      "standard_equipment": [
        "ing",
        "mega",
        "damage body armor",
        "back pack",
        "a couple sacks",
        "utility/",
        "ammo",
        "belt",
        "sunglasses or tinted goggles",
        "air filter or gas mask",
        "and",
        "personal items."
      ],
      "money": null,
      "cybernetics": null,
      "ppe": "absorb the energy of his kill from as far as 300 yards/meters.\n      No need for normal food or water. The P.P.E. energy vampires\n   have little need to consume solid food or drink water. The mutant\n   does not require more than one pound (0.45 kg) of meat and eight\n   ounces of water a week to remain healthy. Furthermore, the psychic\n   can go without food or water for up to three weeks, if necessary,\n   without ill effect. However, being deprived of the proper P.P.E.\n   energy will inflict physical damage and the character will die of\n   starvation within three weeks.\n7. Other Psionic Powers: Choose six psi-powers from the Sensitive\n   category of powers.\n8. Psionic empathy with animals. Psi-stalkers automatically have\n   an affinity with animals of all kinds. Domesticated animals will\n   always take an immediate liking to a stalker and will do their best\n   to please him; +15% bonus to ride a horse and work with all\n   domestic animals.\n      Wild animals, with the exception of felines and mutant and alien\n   predators, will react to the stalker as if he was a fellow woodland\n   creature, allowing him to walk among them without fear. This\n   ability enables psi-stalkers to operate in the wild without causing\n   animals to react to their presence; birds do not fly away, animals\n   do not run, and therefore do not indicate the approach of an intruder.\n   Even watchdogs will not sound a bark of alarm at the presence of\n   a stalker.\n      Felines and mutant and alien predatory animals seem to see the\n   psi-stalker as a fellow hunter and a danger. Wild cats and mutants\n   will frequently select a psi-stalker as their first target in an attack\n   and will not positively respond to the character at all.\n      NOTE: This affinity with animals means that the character will\n   hunt and eat meat only for food, never for pleasure, and feels\n   sadness whenever he sees an animal in distress.",
      "source_range": [
        6585,
        6652
      ],
      "raw_snippet": "105 The preferred form of nourishment, even among civilized psi- stalkers, is to hunt and kill one's victim. The victim can be a psychic, practitioner of magic, or supernatural being. At the mo- ment of death, the victim's P.P.E. is doubled. The stalker can absorb the energy of his kill from as far as 300 yards/meters. No need for normal food or water. The P.P.E. energy vampires have little need to consume solid food or drink water. The mutant does not require more than one pound (0.45 kg) of meat and eight ounces of water a week to remain healthy. Furthermore, the psychic can go without food or water for up to three weeks, if necessary, without ill effect. However, being deprived of the proper P.P.E. energy will inflict physical damage and the character will die of starvation within\u2026",
      "suggested_target": "lib/occs/105.lpc"
    },
    {
      "id": "106",
      "name": "106",
      "slug": "106",
      "section": "rcc",
      "description": "Weapons will include a couple knives, and four other weapons",
      "attribute_requirements": null,
      "occ_skills": null,
      "standard_equipment": [
        "Coalition \"Dead Boy\" armor",
        "weapons",
        "equipment",
        "money",
        "and                     Star is completely self",
        "sufficient",
        "with both nuclear and fossil fuel",
        "cybernetics are all the same as the Coalition Grunt. Plus a few of the            power and resources",
        "state of the art science and genetics laboratories",
        "Dog Pack special hand to hand weapons such as the neuro",
        "mace",
        "vibro",
        "dating to pre",
        "Rifts earth",
        "and high",
        "tech manufacturing plants of all",
        "knife",
        "and fist spikes.                                                           kinds (55% are currently in full operation",
        "while the remaining still"
      ],
      "money": "experimentation. Only the Chinese continued experimentation on human\n  saleable black market items.\n                                                                                  subjects. Eventually, American \"gene-splicers,\" as they were called,",
      "cybernetics": "natural powers. If cybernetics are used, they are usually sensory or            speech, and physiology.\n  optical enhancements.\n                                                                                     The great controversy that arose from the creation of intelligent mutant\nSkills of a Coalition Psi-stalker                                                 animals was the fear that humans were establishing a new precedent\nOr a Civilized Mercenary Stalker                                                  for slavery. The outcry against slavery was well taken, because the\n   The civilized stalker has undergone some basic military training. The          American government had high hopes for, literally, creating a super\nfollowing Coalition military skills are known.                                    soldier from animal mutants. Soldiers with the predatory instincts, in-\n                                                                                  human abilities, strength, and endurance of an animal, complemented\nRadio: Basic (+10%)                                                               by the intelligence of a human. Fortunately, social outrage stopped the\nPilot Hovercraft (+10%)                                                           creation of a race of mutant soldiers and laborers before it had begun.\nRobot Combat: Basic                                                               Still, the government continued secret research in this area for decades\nRead Sensory Equipment (+ 10%)                                                    to come, just in case the need should arise. In fact, billions were spent\nWeapon Systems (+ 10%)                                                            on the completion of a genetics engineering facility that included a vast\nBody Building                                                                     factory-like plant with full design and manufacturing capabilities.\nClimbing ( + 5%)                                                                  Rumor had it that the secret plant could create hundreds of mutant\nRunning                                                                           animals a month. Of course, the government denied the existence of\nProwl (+10%)                                                                      any such facility, admitting only that minimal genetic research continued\nW.P. Energy Pistol                                                                at the Tex-Am Complex, a top secret military base located in Texas.\nW.P. Energy Rifle\nW.P. two of choice                                                                   While society may have had the presence of mind to stop the re-estab-lishment of slavery in the 21st ce\nHand to Hand: Expert\n                                                                                  crueler and savage period. The Coalition has created and utilized mutant\n   At first level the psychic can select four \"other\" skills, each with a         animals for labor, as soldiers, and for experimentation for years. The\n + 5% bonus, and speaks American and one other language at 96%.                   Lone Star Coalition State is the center for genetic research and develop-\n   character can also select eight (8) Secondary skills without benefit           ment. It is at Lone Star that the majority of the Dog Pack and other\nof bonuses. At fourth and eighth levels an additional two secondary               mutations are created and trained. As one may have guessed, Lone Star\nskills can be selected.                                                           is the Tex Am Complex, which, amazingly, survived the apocalyptic\n   Available skill categories are limited to any: Communication, Domes-           time of the rift explosions mostly unscathed. It was its fabulous genetics,\ntic, Electrical: Basic only, Mechanical: Automotive only, Military,               manufacturing, military security, and other unique capabilities that en-\nMedical: First aid only, Physical (any except acrobatics), Pilot, Pilot           ticed solicitation for its addition as a member of the Coalition States.\nRelated, Science: Math only, Technical, and W.P.                                  The place is barely a city. Instead, Lone Star is a sprawling 20 mile\n                                                                                  (32 km) research and manufacturing complex with half the population",
      "ppe": null,
      "source_range": [
        6653,
        6727
      ],
      "raw_snippet": "106 Weapons will include a couple knives, and four other weapons of choice. May use techno-wizardry weapons too, but not suggested as part of the initial equipment (GM's choice). Dog Pack R.C.C. Vehicle is limited to horse or other animal mount (has an affinity Before the Time of Rifts, the quest for human augmentation naturally with all non-predatory animals, including D-Bees and aliens), or lead to genetic manipulation. North America was by far the leader in non-military vehicle, and may include hover vehicles or souped-up the area of genetic research. They had enjoyed some spectacular results motorcycle or car. May use a techno-wizard vehicle, but not recom- working on laboratory animals. However, genetic manipulation of mended to start (GM's choice). human beings proved to be much\u2026",
      "suggested_target": "lib/occs/106.lpc"
    },
    {
      "id": "107",
      "name": "107",
      "slug": "107",
      "section": "rcc",
      "description": "at Lone Star, the one animal used above all others is the dog. The dog Fourth, as a soldier, the dog offers several advantages. Besides the",
      "attribute_requirements": null,
      "occ_skills": null,
      "standard_equipment": null,
      "money": null,
      "cybernetics": null,
      "ppe": null,
      "source_range": [
        6728,
        6754
      ],
      "raw_snippet": "107 at Lone Star, the one animal used above all others is the dog. The dog Fourth, as a soldier, the dog offers several advantages. Besides the has proven to be the most desirable and reliable of all animals for obvious superiority in physical strength and endurance, dogs possess several reasons. several additional abilities. In general, the dog's sense of smell is a One, they have a long history of cohabitation with human beings. million times more sensitive than a human's and possess a much more Whether there is any real scientific reason for this special relationship sensitive range of hearing. This makes them much more alert and ideal between man and canine is doubtful. However, psychologically, humans for tracking. quickly accepted, trusted, and liked dogs. This leads to an\u2026",
      "suggested_target": "lib/occs/107.lpc"
    },
    {
      "id": "108",
      "name": "108",
      "slug": "108",
      "section": "rcc",
      "description": "base to keep an eye out for, and investigate, any suspicious activity or",
      "attribute_requirements": {
        "usual": 3
      },
      "occ_skills": null,
      "standard_equipment": [
        "the leader.                                                                         Adventurer who is no longer a member of the Dog Pack                   i",
        "May or may not wear clothing or mega",
        "damage body armor (may"
      ],
      "money": "saleable black market items.                                                     skill bonus, fair swimmer: base skill 40%.",
      "cybernetics": "natural powers. If cybernetics are used, they are usually sensory or             but powerful, with a strong neck and powerful leg and back muscles,\n   optical enhancements.                                                            capable of jumping great distances. Mutant Boxers can leap 15\n                                                                                    feet/4.5 m after a short running start. Add +1 to I.Q. attribute,\n      Note: A Dog Boy who has gone AWOL is generally left alone                      + 1D4 to P.E. and P.S. attributes, and 20 to S.D.C. The creature's\n   unless he or she takes action against the CS. However, loyal Dog                 bite is also more powerful than most, inflicting 2D4 S.D.C. damage.\n   Boys view deserters/mercenaries as traitors to the human race and             61-65 Bull Terrier (aka Pit Bull). Reduce size by 10%, but add\n   as such, are low-life-scum, never to be trusted nor treated with                  + 2D6 to P.E. attribute, add 2D4 to P.S. attribute and add 40 to\n   respect.                                                                         S.D.C. Bite inflicts 2D6 S.D.C. damage. -30 to track by smell.",
      "ppe": "comforted by the presence of the loyal and courteous Dog Boys, and                     ifically oriented toward magic, techno-wizardry and wizardry de-\ncooperate with them to the fullest.                                                    vices). The ability is constant and automatic, just like the psi-stalker.\n   In the wilderness, troops of Dog Pack soldiers (or other mutant                     Range: 50 feet (15m).\nanimals) may be dispatched into areas of conflict. Like the US Marines                     Unlike the stalker, the dog has little chance of recognizing that\nof old, the Dog Pack is often the first to be sent into a trouble zone                 specific person's psychic scent again. Base Skill: 8% + 2% per\nfor reconnaissance and/or initial assault. More often, they are sent out               additional level of experience. If the mutant has a bit of hair, skin,\nas scouts and spies in search of covert operators (translation: groups                 blood, or an article of clothing recently (4 hours or less) worn by\nand individuals who practice the arts of magic, consort with non-hu-                   the subject being hunted, the ability to follow the psychic trail enjoys\nmans, or study ancient books/ruins/education). They are also sent out                  a bonus of + 10%.\non regular reconnaissance, intelligence, and seek-and-destroy missions.\nThe Dog Pack soldier may be a soldier in a completely mutant animal                        If a psionic power or magic is being used within the range of\nsquad, a member of a human team, Dog Pack, or an individual on a                       sensitivity, he will sense that too. If the energy is being continually\nsolo assignment.                                                                       expended, like a series of magic or psionic attacks, or a long duration\n                                                                                       effect, he can track it to the source with ease. Base Skill: 40%\n   Individual Dog Boys are frequently sent into the wilderness to pretend               + 5% per level of experience (roll once every melee). It is also\nto be runaways or mercenaries. This subterfuge enables them to observe                 possible that the character will recognize the scent again if encoun-\nthe activities of real mercenaries or wilderness adventurers firsthand.                tered at some other time; 10% +4% per level of experience. Range:\nOf course, some mutant dogs will forsake the Coalition when they                       Sensitivity to a fellow psychic or magic practitioner not using his\ndiscover the freedom that other societies and groups offer. Or are simply              powers is 50 feet (15 m) +5 feet (1.5 m) per each additional level\nenticed to wander the world to personally explore all its marvels. This                of experience. Sensitivity to psionic and magic powers being used\ntoo, is anticipated by the Coalition and is part of an exercise to see                 is a 400 foot (121 m) area +50 (15 m) per level of experience.\nhow many Dog Pack soldiers remain loyal when placed under varying                      When tracking a psychic scent, roll percentile dice every 1000 feet\nconditions of freedom, stress, or danger.                                              (305 m) to see if the hunter is still on the trail. Duration: Automatic\n    Generally, Dog Pack mutants are treated well and with kindness.                    and constant. I.S.P.:None, automatic ability.\nThey are especially loved by their psi-stalker Dog Pack leader. However,            2. Sense supernatural beings: Identical in function to the previous\nthe Coalition and most people in the CS see the mutant animals not as                  ability, except the mutant dog is much more sensitive to the very\nintelligent life forms, and never as equals, but as trained animals. They              distinctive psychic scent of the supernatural. Base Skill: 62% + 2%\n love and care for the mutants just as they might a normal dog, as a pet               per level of experience. The ability to identify the specific type of\nand servant. As such, they are treated like simple-minded children,                    paranormal creature is Base Skill: 62% + 2% per level of experience,\noften referred to in the third person even when present, and believed                  and includes demons, vampires, and dragons.\nto be greatly inferior to human beings.\n                                                                                            The tracking by scent Base Skill is 35% + 5% per level of experi-\n    Since they are seen as specially bred and trained \"animals,\" the                   ence. 70% +3% per level of experience if the supernatural being\n mutant dogs are generally considered to be an expendable commodity.                    is using psionics or magic.\nA human might feel a bit of a loss over the death of a favorite hunting\ndog killed by a wild animal, but one simply discards the dead body                          Range: Sensitivity to the presence of a supernatural being when\n and goes out to purchase a new dog. This is the general attitude of the                it is not using its powers is 100 feet (30.5 m) per level of experience.\n Coalition military and most citizens. The mutant dog soldiers are just                 Sensitivity to supernatural creatures or magic being used is 1000\n big doggies that walk on two legs, sport arms and hands, and talk                      feet (305 m) + 100 feet (30.5 m) per additional level of experience.\n instead of bark. If a job is too dangerous for a human, send in a mutant               Duration: Automatic and constant. I.S.P.: None, automatic.\n animal. If it dies, a new one can always be purchased or bred. An                     NOTE: Close proximity to ley lines and nexus points disrupts the\n attitude that is not shared by the psi-stalkers who act as the team leader            psychic senses.\n of all Dog Packs. In fact, the Coalition's heartless abuse of their animal         3. Psi-Bonuses: As a master psionic, the psi-hound needs to roll a 10\n creations is the one element that could, someday, turn the psi-stalkers                or higher to save versus psionic attack and enjoys a bonus of + 1\n away from them.                                                                        to save vs psionic attack.\n    Oddly, most Dog Pack mutants don't see anything wrong with how                  4. Other Psionic Powers: The Dog Pack character automatically gets\n they are treated and tend to concur that they are expendable, rather                   the following psychic Sensitive powers: sense evil, sense magic,\n than jeopardize a valuable human life (remember the pack mentality).                   sixth sense, and empathy (receiver only, not transmission), plus\n This also means that they rarely feel cheated or abused, and are happy                 choice of one other from the sensitive category.\njust to be part of the human pack.                                                  5. Physical Bonuses: All Dog Boys, regardless of breed, get the follow-\n                                                                                       ing bonus rolls and attribute modifications: + 20 on physical S.D.C.,\n                                                                                        + 2 on initiative roll, +1 to strike, parry, and dodge, +1D4 to\n                                                                                       P.E. attribute, 1D4 to P.S. attribute, +2D6 to speed attribute. Bite\n                                                                                       attack inflicts 1D6 S.D.C. damage. Physical endurance as it applies\n                                                                                       to weight/load and exertion is two times greater than for normal\n                                                                                       humans. Also see optional character tables.\n                                                                              109",
      "source_range": [
        6755,
```

## Makefile
- Lines: 205, Size: 11656
- Status: ✅ complete
- First comments: # Makefile for LPC MUD Driver # Standard C project structure with src/, tests/, build/ directories # Allow users to override CFLAGS, but keep include dirs in CPPFLAGS so
- TODOs: 0


```text
# Makefile for LPC MUD Driver
# Standard C project structure with src/, tests/, build/ directories

CC = gcc
# Allow users to override CFLAGS, but keep include dirs in CPPFLAGS so
# they are not lost when CFLAGS is overridden on the make command line.
# Default CFLAGS (can be overridden by target-specific assignments)
CFLAGS ?= -Wall -Wextra -D_DEFAULT_SOURCE -g -O2 -std=c99
CPPFLAGS += -Isrc
LDFLAGS = -lm

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Common sources needed for all tests (MUST BE BEFORE RULES!)
TEST_COMMON_SOURCES = $(SRC_DIR)/vm.c \
                      $(SRC_DIR)/object.c \
					  tools/vm_trace.c \
                      $(SRC_DIR)/array.c \
                      $(SRC_DIR)/mapping.c \
                      $(SRC_DIR)/gc.c \
					  $(SRC_DIR)/efun.c \
					  $(TEST_DIR)/test_driver_stub.c \
					  $(SRC_DIR)/test_stubs.c \
                      $(SRC_DIR)/compiler.c \
                      $(SRC_DIR)/program_loader.c \
                      $(SRC_DIR)/program.c \
                      $(SRC_DIR)/master_object.c \
                      $(SRC_DIR)/session.c \
                      $(SRC_DIR)/lexer.c \
                      $(SRC_DIR)/parser.c \
                      $(SRC_DIR)/codegen.c \
                      $(SRC_DIR)/preprocessor.c

# Driver source files
DRIVER_SRCS = $(SRC_DIR)/driver.c $(SRC_DIR)/server.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c \
              $(SRC_DIR)/vm.c $(SRC_DIR)/codegen.c $(SRC_DIR)/object.c \
			  tools/vm_trace.c \
              $(SRC_DIR)/gc.c $(SRC_DIR)/efun.c $(SRC_DIR)/array.c \
              $(SRC_DIR)/mapping.c $(SRC_DIR)/compiler.c $(SRC_DIR)/program.c \
              $(SRC_DIR)/simul_efun.c $(SRC_DIR)/program_loader.c \
              $(SRC_DIR)/preprocessor.c \
              $(SRC_DIR)/master_object.c $(SRC_DIR)/terminal_ui.c \
              $(SRC_DIR)/websocket.c $(SRC_DIR)/session.c \
              $(SRC_DIR)/room.c $(SRC_DIR)/chargen.c $(SRC_DIR)/skills.c \
			  $(SRC_DIR)/combat.c $(SRC_DIR)/item.c $(SRC_DIR)/psionics.c \
			  $(SRC_DIR)/magic.c $(SRC_DIR)/wiz_tools.c $(SRC_DIR)/race_loader.c \
			  $(SRC_DIR)/ui_frames.c $(SRC_DIR)/death.c $(SRC_DIR)/npc.c

# Count source files
TOTAL_FILES = $(words $(DRIVER_SRCS))

# Colors: disabled for simpler plain output
C_CYAN =
C_GREEN =
C_YELLOW =
C_RED =
C_RESET =
C_BOLD =

# Default target - just build the driver
.PHONY: all driver tests clean distclean help test debug release asan asan_tests

# Target-specific builds
# Usage: `make debug` or `make release` or `make asan` (builds driver)
# `make asan_tests` builds all tests with ASan/UBSan instrumentation and runs them.
debug: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -g -O0 -std=c99
debug: $(BUILD_DIR)/driver

release: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -O2 -std=c99 -DNDEBUG
release: $(BUILD_DIR)/driver

asan: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -g -O1 -std=c99 -fsanitize=address,undefined -fno-omit-frame-pointer
asan: $(BUILD_DIR)/driver

# Build and run tests under ASan
asan_tests: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -g -O1 -std=c99 -fsanitize=address,undefined -fno-omit-frame-pointer
asan_tests: tests


driver: $(BUILD_DIR)/driver


# Build driver with custom unicode frame and ASCII indicators
$(BUILD_DIR)/driver: $(DRIVER_SRCS)
	@mkdir -p $(BUILD_DIR)
	@echo
	@echo "AMLP MUD DRIVER - BUILD IN PROGRESS"
	@count=0; for src in $(DRIVER_SRCS); do \
		count=$$((count + 1)); \
		name=$$(basename $$src); \
		printf " [*] [%2d/$(TOTAL_FILES)] Compiling %s\\n" $$count "$$name"; \
	done
	@echo
	@echo "[LINK] Creating driver executable..."
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS) 2>$(BUILD_DIR)/.warnings.txt; \
	status=$$?; \
	warns=$$(grep -c "warning:" $(BUILD_DIR)/.warnings.txt 2>/dev/null | head -1 || echo 0); \
	warns=$${warns:-0}; \
	if [ "$$status" -eq 0 ]; then \
		echo "BUILD SUCCESSFUL"; \
		echo "Files compiled: $(TOTAL_FILES)"; \
		echo "Warnings:       $$warns"; \
		echo "Errors:         0"; \
		if [ "$$warns" -gt 0 ]; then \
			echo "Warning details: diagnostics/README.md"; \
			echo "Quick reference: diagnostics/quick-reference.md"; \
		fi; \
	else \
		echo "X BUILD FAILED"; \
		echo "See diagnostics/undeclared-identifier.md for common compilation errors"; \
		cat $(BUILD_DIR)/.warnings.txt; \
		exit 1; \
	fi
	@echo

# Build all tests quietly
tests: $(BUILD_DIR)/test_lexer $(BUILD_DIR)/test_parser $(BUILD_DIR)/test_vm \
       $(BUILD_DIR)/test_object $(BUILD_DIR)/test_gc $(BUILD_DIR)/test_efun \
       $(BUILD_DIR)/test_array $(BUILD_DIR)/test_mapping $(BUILD_DIR)/test_compiler \
       $(BUILD_DIR)/test_program $(BUILD_DIR)/test_simul_efun $(BUILD_DIR)/test_vm_execution \
       $(BUILD_DIR)/test_parser_stability
	@printf "All test binaries built\n"

# Build everything
all: driver tests


# Pattern rule for all test targets (custom frame, ASCII indicators, no emojis)
$(BUILD_DIR)/test_%: $(TEST_DIR)/test_%.c $(TEST_COMMON_SOURCES)
	@mkdir -p $(BUILD_DIR)
	@printf "$(C_CYAN)╔════════════════════════════════════════════════════════════════════════════╗$(C_RESET)\n"
	@printf "$(C_CYAN)║$(C_RESET)%-76s$(C_CYAN)║$(C_RESET)\n" "BUILDING TEST: $@"
	@printf "$(C_CYAN)╠════════════════════════════════════════════════════════════════════════════╣$(C_RESET)\n"
	@printf "$(C_CYAN)║$(C_RESET)%-76s$(C_CYAN)║$(C_RESET)\n" " [*] Compiling test sources..."
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -I$(SRC_DIR) -I$(TEST_DIR) $(LDFLAGS)
	@status=$$?; \
	       if [ "$$status" -eq 0 ]; then \
		       printf "$(C_CYAN)╠════════════════════════════════════════════════════════════════════════════╣$(C_RESET)\n"; \
		       printf "$(C_CYAN)║$(C_RESET)%-76s$(C_CYAN)║$(C_RESET)\n" "  TEST BUILD SUCCESSFUL"; \
		       printf "$(C_CYAN)╚════════════════════════════════════════════════════════════════════════════╝$(C_RESET)\n"; \
	else \
		printf "╠════════════════════════════════════════════════════════════════════════════╣\n"; \
		printf "║                         X TEST BUILD FAILED                             ║\n"; \
		printf "╚════════════════════════════════════════════════════════════════════════════╝\n"; \
		exit 1; \
	fi

# Specific override for test_simul_efun (needs simul_efun.c)
$(BUILD_DIR)/test_simul_efun: $(TEST_DIR)/test_simul_efun.c $(TEST_COMMON_SOURCES) $(SRC_DIR)/simul_efun.c
	@mkdir -p $(BUILD_DIR)
	@printf "$(C_CYAN)╔════════════════════════════════════════════════════════════════════════════╗$(C_RESET)\n"
	@printf "$(C_CYAN)║$(C_RESET)%-76s$(C_CYAN)║$(C_RESET)\n" "BUILDING TEST: $@"
	@printf "$(C_CYAN)╠════════════════════════════════════════════════════════════════════════════╣$(C_RESET)\n"
	@printf "$(C_CYAN)║$(C_RESET)%-76s$(C_CYAN)║$(C_RESET)\n" " [*] Compiling test sources..."
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -I$(SRC_DIR) -I$(TEST_DIR) $(LDFLAGS)
	@status=$$?; \
	       if [ "$$status" -eq 0 ]; then \
		       printf "$(C_CYAN)╠════════════════════════════════════════════════════════════════════════════╣$(C_RESET)\n"; \
		       printf "$(C_CYAN)║$(C_RESET)%-76s$(C_CYAN)║$(C_RESET)\n" "  TEST BUILD SUCCESSFUL"; \
		       printf "$(C_CYAN)╚════════════════════════════════════════════════════════════════════════════╝$(C_RESET)\n"; \
	else \
		printf "╠════════════════════════════════════════════════════════════════════════════╣\n"; \
		printf "║                         X TEST BUILD FAILED                             ║\n"; \
		printf "╚════════════════════════════════════════════════════════════════════════════╝\n"; \
		exit 1; \
	fi

# Run all tests (custom frame, ASCII indicators, no emojis except checkmark)
test: tests
	@printf "\n$(C_CYAN)╔════════════════════════════════════════════════════════════════════════════╗$(C_RESET)\n"
	@printf "$(C_CYAN)║$(C_BOLD)%-76s$(C_CYAN)║$(C_RESET)\n" "RUNNING TESTS"
	@printf "$(C_CYAN)╠════════════════════════════════════════════════════════════════════════════╣$(C_RESET)\n"
	@for t in lexer parser vm object gc efun array mapping compiler program simul_efun vm_execution; do \
		printf "$(C_CYAN)║$(C_RESET) [*] Running %-62s$(C_CYAN)║$(C_RESET)\n" "$$t tests..."; \
		$(BUILD_DIR)/test_$$t 2>&1 | sed 's/^/  /'; \
		printf "$(C_CYAN)║%-76s$(C_CYAN)║\n" ""; \
	done
	@printf "$(C_CYAN)╚════════════════════════════════════════════════════════════════════════════╝$(C_RESET)\n"

# Clean build artifacts
clean:
	@printf "$(C_CYAN)▶$(C_RESET) Cleaning build artifacts...\n"
	@rm -rf $(BUILD_DIR)
	@printf "Clean complete\n"

# Clean everything
distclean: clean
	@printf "$(C_CYAN)▶$(C_RESET) Removing all generated files...\n"
	@printf "Distclean complete\n"

# Display help
help:
	@printf "\n$(C_BOLD)AMLP MUD Driver Build System$(C_RESET)\n\n"
	@printf "$(C_CYAN)Usage:$(C_RESET) make [target]\n\n"
	@printf "$(C_CYAN)Targets:$(C_RESET)\n"
	@printf "  $(C_GREEN)driver$(C_RESET)    - Build the main driver executable (default)\n"
	@printf "  $(C_GREEN)tests$(C_RESET)     - Build all test executables\n"
```

## mud.sh
- Lines: 171, Size: 5345
- Status: ⚠️ partial
- First comments: # MUD Control Script # Clean compressed logs older than 30 days
- TODOs: 0


```text
#!/bin/bash
# MUD Control Script

PID_FILE="logs/driver.pid"
LOG_FILE="logs/driver.log"
DRIVER_BIN="./build/driver"
if [ ! -x "$DRIVER_BIN" ]; then
    if [ -x ./driver ]; then
        DRIVER_BIN="./driver"
    else
        DRIVER_BIN=""
    fi
fi

rotate_logs() {
    echo "Rotating logs..."
    TIMESTAMP=$(date +%Y%m%d_%H%M%S)
    MAX_SIZE=$((10 * 1024 * 1024)) # 10MB

    mkdir -p logs
    for log in logs/*.log lib/log/*.log; do
        if [ -f "$log" ]; then
            SIZE=$(stat -c%s "$log" 2>/dev/null || stat -f%z "$log" 2>/dev/null || echo 0)
            if [ "$SIZE" -gt "$MAX_SIZE" ]; then
                mv "$log" "${log}.${TIMESTAMP}"
                touch "$log"
                gzip -9 "${log}.${TIMESTAMP}" &
                echo "Rotated: $log (${SIZE} bytes)"
            fi
        fi
    done

    # Clean compressed logs older than 30 days
    find logs/ -name "*.log.*.gz" -mtime +30 -delete 2>/dev/null || true
    echo "Log rotation complete"
}

case "$1" in
    start)
        if [ -f "$PID_FILE" ]; then
            echo "MUD already running (PID: $(cat $PID_FILE))"
            exit 1
        fi
        if [ -z "$DRIVER_BIN" ]; then
            echo "Driver binary not found; build first (make driver)"
            exit 1
        fi
        echo "Starting MUD..."
        nohup "$DRIVER_BIN" > "$LOG_FILE" 2>&1 &
        echo $! > "$PID_FILE"
        echo "MUD started (PID: $(cat $PID_FILE))"
        echo "Log: tail -f $LOG_FILE"
        ;;
    stop)
        if [ ! -f "$PID_FILE" ]; then
            echo "MUD not running"
            exit 1
        fi
        PID=$(cat "$PID_FILE")
        echo "Stopping MUD (PID: $PID)..."
        kill $PID || echo "Failed to kill $PID"
        rm "$PID_FILE"
        echo "MUD stopped"
        ;;
    restart)
        $0 stop
        sleep 2
        $0 start
        ;;
    status)
        if [ -f "$PID_FILE" ]; then
            PID=$(cat "$PID_FILE")
            if ps -p $PID > /dev/null; then
                echo "MUD running (PID: $PID)"
            else
                echo "MUD crashed (stale PID file)"
                rm "$PID_FILE"
            fi
        else
            echo "MUD not running"
        fi
        ;;
    tail)
        tail -f "$LOG_FILE"
        ;;
    wipe-players)
        echo "WARNING: This will DELETE all player save files!"
        read -p "Type 'YES' to confirm: " confirm
        if [ "$confirm" = "YES" ]; then
            echo "Wiping player saves..."
            find save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            find lib/save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            echo "Player saves wiped"
        else
            echo "Cancelled"
        fi
        ;;
    wipe-wizards)
        echo "WARNING: This will DELETE all wizard save files!"
        read -p "Type 'YES' to confirm: " confirm
        if [ "$confirm" = "YES" ]; then
            echo "Wiping wizard saves..."
            find save -type f -path "*/wizards/*" \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            find lib/save -type f -path "*/wizards/*" \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            echo "Wizard saves wiped"
        else
            echo "Cancelled"
        fi
        ;;
    wipe-all)
        echo "WARNING: This will DELETE ALL save files (players, wizards, rooms, workrooms)!"
        read -p "Type 'WIPE ALL' to confirm: " confirm
        if [ "$confirm" = "WIPE ALL" ]; then
            echo "Wiping all saves..."
            find save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            find lib/save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            rm -f data/*.dat 2>/dev/null || true
            rm -rf lib/domains/wizard/ 2>/dev/null || true
            echo "All saves wiped"
        else
            echo "Cancelled"
        fi
        ;;
    reload-lib)
        echo "Reloading library (hot reload)..."
        if [ -f "$PID_FILE" ]; then
            kill -USR1 $(cat "$PID_FILE") 2>/dev/null || echo "Signal not supported, use restart"
        else
            echo "MUD not running"
        fi
        ;;
    clean-build)
        echo "Clean rebuild and restart..."
        $0 stop || true
        make clean && make driver
        $0 start
        ;;
    build)
        echo "Building driver..."
        make driver
        ;;
    rebuild)
        echo "Rebuilding driver (clean + build)..."
        make clean && make driver
        ;;
    test-connect)
        echo "Testing telnet connection to localhost:3000..."
        (sleep 1; echo "quit") | telnet localhost 3000 || echo "telnet failed or not installed"
        ;;
    rotate-logs)
        rotate_logs
        ;;
    auto-test)
        echo "Running automated test script..."
        cat > /tmp/amlp_test.exp << 'EXPECT'
#!/usr/bin/expect -f
set timeout 5
spawn telnet localhost 3000
expect "Welcome" { send "help\r" }
expect ">" { send "who\r" }
expect ">" { send "quit\r" }
expect eof
EXPECT
        chmod +x /tmp/amlp_test.exp
        /tmp/amlp_test.exp
        ;;
    *)
        echo "Usage: $0 {start|stop|restart|status|tail|wipe-players|wipe-wizards|wipe-all|reload-lib|clean-build|build|rebuild|test-connect|auto-test|rotate-logs}"
        exit 1
        ;;
esac
```

## mud.ctl
- Lines: 220, Size: 6346
- Status: ✅ complete
- First comments: # AMLP-MUD Control Script # Usage: ./mud.ctl {start|stop|restart|status|reload|log} # Check if the port is already bound by some process (prevent bind() failed)
- TODOs: 0


```text
#!/bin/bash

# AMLP-MUD Control Script
# Usage: ./mud.ctl {start|stop|restart|status|reload|log}

MUDLIB_DIR="$(cd "$(dirname "$0")" && pwd)"
SERVER_BIN="$MUDLIB_DIR/build/driver"
PID_FILE="$MUDLIB_DIR/mud.pid"
LOG_FILE="$MUDLIB_DIR/lib/log/server.log"
DEFAULT_PORT=3000

cd "$MUDLIB_DIR" || exit 1

port_listener_pid() {
    local pid=""
    if command -v lsof >/dev/null 2>&1; then
        pid=$(lsof -tiTCP:"$DEFAULT_PORT" -sTCP:LISTEN 2>/dev/null || true)
    elif command -v ss >/dev/null 2>&1; then
        pid=$(ss -ltnp 2>/dev/null | awk -v port=":$DEFAULT_PORT" '
            $4 ~ port { for(i=1;i<=NF;i++) if($i ~ /pid=/) { gsub("pid=","",$i); split($i,a,","); print a[1]; exit } }')
    else
        pid=""
    fi
    echo "$pid"
}

start_server() {
    if [ -f "$PID_FILE" ]; then
        PID=$(cat "$PID_FILE")
        if kill -0 "$PID" 2>/dev/null; then
            echo "Server already running (PID: $PID)"
            return 1
        else
            echo "Removing stale PID file..."
            rm -f "$PID_FILE"
        fi
    fi
    
    if [ ! -x "$SERVER_BIN" ]; then
        echo "Error: Server binary not found or not executable"
        echo "Run: mkdir -p build && make"
        return 1
    fi
    
    # Check if the port is already bound by some process (prevent bind() failed)
    EXIST_PID=$(port_listener_pid)
    if [ -n "$EXIST_PID" ]; then
        echo "Error: Port $DEFAULT_PORT appears to be in use by PID $EXIST_PID."
        echo "If this is unexpected, run: ./mud.ctl stop && pkill -9 -f 'mud_server|driver'"
        return 1
    fi
    
    mkdir -p "$(dirname "$LOG_FILE")"
    
    echo "Starting AMLP-MUD server on port $DEFAULT_PORT..."
    # Start driver with telnet port, websocket port and explicit master path
    WS_PORT=$((DEFAULT_PORT + 1))
    nohup "$SERVER_BIN" "$DEFAULT_PORT" "$WS_PORT" "lib/secure/master.lpc" >> "$LOG_FILE" 2>&1 &
    SERVER_PID=$!
    # Give the driver a moment to daemonize and bind the port
    sleep 1

    # Prefer the PID of the process actually listening on the port (the real server)
    ACTIVE_PID=$(port_listener_pid)
    if [ -n "$ACTIVE_PID" ]; then
        echo "$ACTIVE_PID" > "$PID_FILE"
        echo "Server started successfully (PID: $ACTIVE_PID)"
        echo "Log file: $LOG_FILE"
        return 0
    fi

    # Fallback to the shell's child PID
    if kill -0 "$SERVER_PID" 2>/dev/null; then
        echo "$SERVER_PID" > "$PID_FILE"
        echo "Server started (PID: $SERVER_PID) — port listener not detected yet" 
        echo "Log file: $LOG_FILE"
        return 0
    fi

    echo "Server failed to start. Check $LOG_FILE"
    rm -f "$PID_FILE"
    return 1
}

stop_server() {
    if [ ! -f "$PID_FILE" ]; then
        echo "Server not running (no PID file)"
        
        # Check for orphaned processes listening on the server port
        ORPHAN=$(port_listener_pid | head -n1)
        if [ -n "$ORPHAN" ]; then
            echo "Found orphaned server process listening on port (PID: $ORPHAN)"
            echo "Killing orphaned process..."
            kill -TERM "$ORPHAN" 2>/dev/null
            sleep 1
            if kill -0 "$ORPHAN" 2>/dev/null; then
                kill -KILL "$ORPHAN" 2>/dev/null
            fi
            echo "Orphaned process terminated"
        fi
        return 0
    fi
    
    PID=$(cat "$PID_FILE")
    if ! kill -0 "$PID" 2>/dev/null; then
        echo "Server not running (stale PID: $PID)"
        rm -f "$PID_FILE"
        # Try to find any process still listening on the port and kill it
        FALLBACK=$(port_listener_pid | head -n1)
        if [ -n "$FALLBACK" ]; then
            echo "Also found listener PID $FALLBACK — killing it." 
            kill -TERM "$FALLBACK" 2>/dev/null || true
            sleep 1
            if kill -0 "$FALLBACK" 2>/dev/null; then
                kill -KILL "$FALLBACK" 2>/dev/null || true
            fi
            echo "Listener process terminated"
        fi
        return 0
    fi
    
    echo "Stopping server (PID: $PID)..."
    kill -TERM "$PID" 2>/dev/null
    
    # Wait up to 10 seconds for graceful shutdown
    for i in {1..10}; do
        if ! kill -0 "$PID" 2>/dev/null; then
            echo "Server stopped"
            rm -f "$PID_FILE"
            return 0
        fi
        sleep 1
    done
    
    echo "Server did not stop gracefully, forcing..."
    kill -KILL "$PID" 2>/dev/null
    rm -f "$PID_FILE"
    echo "Server killed"
    return 0
}

status_server() {
    if [ -f "$PID_FILE" ]; then
        PID=$(cat "$PID_FILE")
        if kill -0 "$PID" 2>/dev/null; then
            echo "Server is running (PID: $PID)"
            echo "Port: $DEFAULT_PORT"
            echo "Uptime: $(ps -p "$PID" -o etime= | tr -d ' ')"
            return 0
        else
            echo "Server not running (stale PID: $PID)"
            return 1
        fi
    else
        echo "Server is not running"
        
        # Check for orphaned processes
        ORPHAN=$(pgrep -f "mud_server.*$DEFAULT_PORT" | head -1)
        if [ -n "$ORPHAN" ]; then
            echo "WARNING: Found orphaned server process (PID: $ORPHAN)"
            echo "Run: ./mud.ctl stop"
        fi
        return 1
    fi
}

restart_server() {
    echo "Restarting server..."
    stop_server
    sleep 2
    start_server
}

reload_server() {
    echo "Reloading server (full restart)..."
    restart_server
}

tail_log() {
    if [ -f "$LOG_FILE" ]; then
        tail -f "$LOG_FILE"
    else
        echo "No log file found at: $LOG_FILE"
        return 1
    fi
}

case "$1" in
    start)
        start_server
        ;;
    stop)
        stop_server
        ;;
    restart)
        restart_server
        ;;
    reload)
        reload_server
        ;;
```
