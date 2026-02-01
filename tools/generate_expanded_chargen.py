#!/usr/bin/env python3
"""
Generate expanded chargen.c with all 50 races and 35 OCCs
"""

# All 50 Rifts Races
RACES = [
    ("Human", "Baseline race, adaptable and determined"),
    ("Elf", "Graceful and magical, attuned to nature"),
    ("Dwarf", "Stout and resilient, master craftsmen"),
    ("Dragon Hatchling", "Young but powerful, magical beings"),
    ("Adult Dragon", "Massive draconic being of immense power"),
    ("Ancient Dragon", "Millenia-old dragon of legendary might"),
    ("Brodkil", "Demon-cursed mutant with supernatural strength"),
    ("Burster", "Psychic with pyrokinetic abilities"),
    ("Cat Girl", "Feline humanoid, agile and curious"),
    ("Changeling", "Shapeshifting fae creature"),
    ("Cosmo-Knight", "Cosmic guardian with stellar powers"),
    ("D-Bee", "Dimensional being from another reality"),
    ("Deevil", "Lesser demon from dark dimensions"),
    ("Demon", "Powerful supernatural evil entity"),
    ("Dog Boy", "Canine mutant bred by Coalition"),
    ("Dragon Juicer", "Dragon blood-enhanced super soldier"),
    ("Eandroth", "Insectoid alien warrior race"),
    ("Gargoyle", "Stone-skinned supernatural creature"),
    ("Gnome", "Small magical being, tech-savvy"),
    ("Goblin", "Small cunning supernatural creature"),
    ("Godling", "Offspring of divine beings"),
    ("Halfling", "Small folk, lucky and brave"),
    ("Hobgoblin", "Larger, fierce goblinoid"),
    ("Mega-Juicer", "Ultra-enhanced combat juicer"),
    ("Mind Bleeder", "Psychic vampire, drains ISP"),
    ("Mind Melter", "Master psychic, multiple disciplines"),
    ("Minion", "Bio-wizard creation, enslaved"),
    ("Minotaur", "Bull-headed warrior of great strength"),
    ("Mutant Animal", "Uplifted animal with human intelligence"),
    ("Nightbane", "Shape-shifter between human and monster"),
    ("Noli", "Four-armed alien symbiote race"),
    ("Ogre", "Large brutish humanoid"),
    ("Orc", "Savage warrior race"),
    ("Promethean", "Artificial life form, seeking humanity"),
    ("Psi-Ghost", "Psychic entity with telekinetic mastery"),
    ("Psi-Healer", "Psychic specialized in healing"),
    ("Psi-Stalker", "Psychic hunter, magic-sensing mutant"),
    ("Quick-Flex", "Incredibly fast alien species"),
    ("Simvan", "Monster-riding nomadic warrior"),
    ("Splugorth", "Ancient evil intelligence"),
    ("Splugorth Minion", "Enslaved warrior of the Splugorth"),
    ("Splynn Slave", "Enslaved being from dimensional market"),
    ("Thorny Dragon", "Spiked dragon variant"),
    ("Titan Juicer", "Massive juicer with extended lifespan"),
    ("Trimadore", "Crystalline energy being"),
    ("Troll", "Regenerating savage humanoid"),
    ("True Atlantean", "Dimensional traveler, tattoo magic"),
    ("Uteni", "Fur-covered peaceful alien"),
    ("Vampire", "Undead blood drinker"),
    ("Werewolf", "Shapeshifting wolf-human"),
    ("Wolfen", "Noble lupine warrior race")
]

# All 35 Rifts OCCs
OCCS = [
    ("Cyber-Knight", "Techno-warrior with psionic powers"),
    ("Ley Line Walker", "Master of magical energies and ley lines"),
    ("Rogue Scientist", "Tech expert and inventor"),
    ("Techno-Wizard", "Blend of magic and technology"),
    ("Battle Magus", "Combat mage, magic and weapons"),
    ("Biomancer", "Life magic specialist"),
    ("Body Fixer", "Cybernetic doctor and surgeon"),
    ("Burster", "Pyrokinetic psychic warrior"),
    ("City Rat", "Urban survivor, street smart"),
    ("Cosmo-Knight", "Cosmic power armor knight"),
    ("Crazy", "Augmented insane super soldier"),
    ("Dragon Hatchling RCC", "Young dragon racial class"),
    ("Elemental Fusionist", "Combines elemental magic"),
    ("Full Conversion Borg", "Complete cyborg conversion"),
    ("Headhunter", "Bounty hunter, armor specialist"),
    ("Juicer", "Chemical-enhanced super soldier"),
    ("Line Walker", "Ley line manipulator"),
    ("Mercenary", "Professional soldier for hire"),
    ("Mind Melter", "Master psychic disciplines"),
    ("Mystic", "Spiritual magic user"),
    ("Necromancer", "Death magic practitioner"),
    ("Operator", "Mechanical genius, vehicle expert"),
    ("Power Armor Pilot", "Elite mech pilot"),
    ("Psi-Healer", "Psychic healing specialist"),
    ("Psi-Stalker", "Anti-magic psionic hunter"),
    ("Robot Pilot", "Giant robot operator"),
    ("Rogue Scholar", "Knowledge seeker, multi-skilled"),
    ("Sea Titan", "Ocean-based warrior"),
    ("Shifter", "Dimensional magic specialist"),
    ("Special Forces", "Elite military operative"),
    ("Stone Master", "Earth and stone magic user"),
    ("Temporal Wizard", "Time magic specialist"),
    ("Vagabond", "Jack-of-all-trades wanderer"),
    ("Warlock", "Elemental pact magic user"),
    ("Wilderness Scout", "Tracker and survivalist")
]

def generate_race_display(page=0, per_page=10):
    """Generate race selection display for a page"""
    start = page * per_page
    end = min(start + per_page, len(RACES))
    
    code = []
    code.append(f'    send_to_player(sess, "\\n=== SELECT YOUR RACE (Page %d/%d) ===\\n\\n", page + 1, (NUM_RACES + RACES_PER_PAGE - 1) / RACES_PER_PAGE);')
    
    for i in range(start, end):
        idx = i + 1
        name, desc = RACES[i]
        code.append(f'    send_to_player(sess, "  {idx:2d}. {name} - {desc}\\n");')
    
    code.append('')
    code.append('    send_to_player(sess, "\\n");')
    code.append('    if (page > 0) {')
    code.append('        send_to_player(sess, "  [p] Previous page\\n");')
    code.append('    }')
    code.append('    if (end < NUM_RACES) {')
    code.append('        send_to_player(sess, "  [n] Next page\\n");')
    code.append('    }')
    code.append('    send_to_player(sess, "\\nEnter choice (1-%d) or [n]ext/[p]revious: ", NUM_RACES);')
    
    return '\n'.join(code)

print(f"Total races: {len(RACES)}")
print(f"Total OCCs: {len(OCCS)}")
print("\nTo integrate: Copy generated code sections into chargen.c")
