# Skill System Implementation Guide
**Date:** February 4, 2026  
**Status:** Framework Complete, Content Needed (6 of 150 skills)

## Overview
AetherMUD requires 150 skills across multiple categories to match Rifts RPG specification. The framework exists in `/lib/skills/` with 5 subdirectories.

## Current Structure
```
lib/skills/
  medical/      - Medical skills (first_aid.lpc exists)
  physical/     - Physical skills (climbing.lpc, swimming.lpc exist)
  pilot/        - Piloting skills (pilot_automobile.lpc exists)
  technical/    - Technical skills (literacy.lpc exists)
  weapons/      - Weapon proficiencies (wp_knife.lpc exists)
```

## Missing Categories (Need to Create)
```
lib/skills/
  communication/ - Languages, radio, performance
  domestic/      - Cooking, fishing, sewing
  electrical/    - Electronics, computers, robotics
  espionage/     - Tracking, disguise, intelligence
  mechanical/    - Mechanics, engineering, locksmith
  military/      - Demolitions, parachuting, tactics
  rogue/         - Streetwise, palming, concealment
  science/       - Mathematics, biology, chemistry
```

## Skill Template (Standard)
```lpc
// /lib/skills/CATEGORY/SKILL_NAME.lpc
// SKILL_NAME skill implementation

inherit "/std/skill";

void create() {
    ::create();
    
    set_skill_name("SKILL DISPLAY NAME");
    set_skill_id("skill_name");
    set_skill_category("CATEGORY");
    
    set_skill_description(
        "Full description of what this skill does and how it's used."
    );
    
    // Base percentage for skill use
    set_base_percent(30);
    
    // Percentage gained per level
    set_percent_per_level(5);
    
    // Related stat (affects skill bonus)
    set_related_stat("iq"); // or me, pp, etc.
    
    // Difficulty level
    set_difficulty("standard"); // easy, standard, hard, very_hard
    
    // OCC bonuses (optional)
    set_occ_bonuses(([
        "operator": 15,
        "rogue_scholar": 10
    ]));
}

// Roll against this skill
int skill_roll(object player, int difficulty_modifier) {
    int skill_percent;
    int roll;
    
    if (!player) return 0;
    
    skill_percent = calculate_skill_percent(player);
    skill_percent -= difficulty_modifier;
    
    roll = random(100) + 1;
    
    if (roll <= skill_percent) {
        // Success
        return 1;
    }
    
    // Failure
    return 0;
}

// Calculate current skill percentage for player
int calculate_skill_percent(object player) {
    int percent, level, stat_bonus;
    string stat;
    
    percent = query_base_percent();
    level = player->query_level();
    
    percent += (level * query_percent_per_level());
    
    // Add stat bonus
    stat = query_related_stat();
    if (stat) {
        stat_bonus = player->query_stat(stat) - 10; // Bonus per point over 10
        percent += stat_bonus;
    }
    
    // Add OCC bonus
    if (query_occ_bonuses()) {
        string occ = player->query_occ();
        if (query_occ_bonuses()[occ]) {
            percent += query_occ_bonuses()[occ];
        }
    }
    
    // Cap at 98%
    if (percent > 98) percent = 98;
    
    return percent;
}

// Use the skill
int use_skill(object player, mixed target, string args) {
    // Implement skill-specific mechanics
    // Return 1 for success, 0 for failure
    
    return skill_roll(player, 0);
}
```

## Priority Skills to Implement

### Medical (8 total needed, 1 exists)
- [x] first_aid.lpc
- [ ] paramedic.lpc
- [ ] pathology.lpc
- [ ] cybernetic_medicine.lpc
- [ ] biology.lpc
- [ ] chemistry.lpc
- [ ] brewing.lpc (drugs/potions)
- [ ] forensics.lpc

### Physical (20 total needed, 2 exist)
- [x] climbing.lpc
- [x] swimming.lpc
- [ ] acrobatics.lpc
- [ ] athletics.lpc
- [ ] body_building.lpc
- [ ] boxing.lpc
- [ ] gymnastics.lpc
- [ ] hand_to_hand_basic.lpc
- [ ] hand_to_hand_expert.lpc
- [ ] hand_to_hand_martial_arts.lpc
- [ ] prowl.lpc (CRITICAL - stealth)
- [ ] running.lpc
- [ ] wrestling.lpc
- [ ] dance.lpc
- [ ] fencing.lpc
- [ ] juggling.lpc

### Weapon Proficiencies (20 total needed, 1 exists)
- [x] wp_knife.lpc
- [ ] wp_sword.lpc (CRITICAL)
- [ ] wp_blunt.lpc
- [ ] wp_axe.lpc
- [ ] wp_spear.lpc
- [ ] wp_chain.lpc
- [ ] wp_energy_pistol.lpc (CRITICAL)
- [ ] wp_energy_rifle.lpc (CRITICAL)
- [ ] wp_heavy_energy.lpc
- [ ] wp_rifle.lpc
- [ ] wp_handgun.lpc
- [ ] wp_archery.lpc
- [ ] wp_targeting.lpc
- [ ] wp_heavy_weapons.lpc
- [ ] wp_paired_weapons.lpc
- [ ] wp_shield.lpc

### Pilot (25 total needed, 1 exists)
- [x] pilot_automobile.lpc
- [ ] pilot_motorcycle.lpc
- [ ] pilot_truck.lpc
- [ ] pilot_hovercraft.lpc
- [ ] pilot_airplane.lpc
- [ ] pilot_helicopter.lpc
- [ ] pilot_jet.lpc
- [ ] pilot_power_armor.lpc (CRITICAL)
- [ ] pilot_robot.lpc (CRITICAL)
- [ ] pilot_spacecraft.lpc
- [ ] pilot_boat.lpc
- [ ] navigation.lpc (CRITICAL)
- [ ] navigation_space.lpc
- [ ] read_sensory_equipment.lpc

### Technical (15 total needed, 1 exists)
- [x] literacy.lpc
- [ ] computer_operation.lpc
- [ ] computer_programming.lpc
- [ ] computer_hacking.lpc
- [ ] art.lpc
- [ ] photography.lpc
- [ ] research.lpc
- [ ] writing.lpc
- [ ] lore_demons.lpc
- [ ] lore_magic.lpc
- [ ] lore_atlantis.lpc

### Communication (12 total needed, 0 exist)
- [ ] language_american.lpc
- [ ] language_spanish.lpc
- [ ] language_chinese.lpc
- [ ] language_dragonese.lpc
- [ ] radio_basic.lpc (CRITICAL)
- [ ] radio_scramblers.lpc
- [ ] cryptography.lpc
- [ ] performance.lpc
- [ ] public_speaking.lpc
- [ ] sign_language.lpc

### Electrical (10 total needed, 0 exist)
- [ ] basic_electronics.lpc
- [ ] electrical_engineer.lpc
- [ ] robot_electronics.lpc
- [ ] computer_repair.lpc

### Espionage (12 total needed, 0 exist)
- [ ] detect_ambush.lpc (CRITICAL)
- [ ] detect_concealment.lpc
- [ ] disguise.lpc
- [ ] escape_artist.lpc
- [ ] forgery.lpc
- [ ] intelligence.lpc
- [ ] pick_locks.lpc (CRITICAL)
- [ ] pick_pockets.lpc
- [ ] sniper.lpc
- [ ] tracking.lpc (CRITICAL)
- [ ] wilderness_survival.lpc (CRITICAL)

### Mechanical (15 total needed, 0 exist)
- [ ] automotive_mechanics.lpc
- [ ] aviation_mechanics.lpc
- [ ] basic_mechanics.lpc (CRITICAL)
- [ ] locksmith.lpc
- [ ] mechanical_engineer.lpc
- [ ] robot_mechanics.lpc
- [ ] weapons_engineer.lpc
- [ ] armorer.lpc

### Military (18 total needed, 0 exist)
- [ ] demolitions.lpc
- [ ] demolitions_disposal.lpc
- [ ] nbc_warfare.lpc
- [ ] parachuting.lpc
- [ ] recognize_weapon_quality.lpc
- [ ] trap_detection.lpc (CRITICAL)
- [ ] scuba.lpc
- [ ] military_tactics.lpc

### Rogue (15 total needed, 0 exist)
- [ ] card_shark.lpc
- [ ] concealment.lpc (CRITICAL)
- [ ] find_contraband.lpc
- [ ] palming.lpc
- [ ] seduction.lpc
- [ ] streetwise.lpc (CRITICAL)

### Science (12 total needed, 0 exist)
- [ ] advanced_mathematics.lpc
- [ ] anthropology.lpc
- [ ] archaeology.lpc
- [ ] astronomy.lpc
- [ ] biology.lpc
- [ ] botany.lpc
- [ ] chemistry.lpc
- [ ] mathematics_basic.lpc

## Implementation Priority

### Phase 1: Combat Skills (Week 1)
1. wp_sword.lpc
2. wp_energy_pistol.lpc
3. wp_energy_rifle.lpc
4. wp_blunt.lpc
5. hand_to_hand_basic.lpc
6. hand_to_hand_expert.lpc
7. hand_to_hand_martial_arts.lpc
8. prowl.lpc
9. detect_ambush.lpc

### Phase 2: Pilot Skills (Week 2)
1. pilot_power_armor.lpc
2. pilot_robot.lpc
3. pilot_motorcycle.lpc
4. navigation.lpc
5. pilot_jet.lpc

### Phase 3: Utility Skills (Week 3)
1. basic_mechanics.lpc
2. radio_basic.lpc
3. tracking.lpc
4. wilderness_survival.lpc
5. pick_locks.lpc
6. streetwise.lpc
7. concealment.lpc
8. trap_detection.lpc

### Phase 4: Technical Skills (Week 4)
1. computer_operation.lpc
2. computer_hacking.lpc
3. basic_electronics.lpc
4. robot_electronics.lpc

### Phase 5: Languages (Week 5)
1. language_american.lpc
2. language_spanish.lpc
3. language_chinese.lpc
4. language_dragonese.lpc

## Standard Skill Object Template Location
Create: `/lib/std/skill.lpc` (if not exists)

This should provide base methods:
- set_skill_name()
- query_skill_name()
- set_skill_id()
- query_skill_id()
- set_base_percent()
- query_base_percent()
- etc.

## Notes
- Each skill should be rollable (d100 system)
- Skills improve with level
- OCCs provide bonuses to related skills
- Stats provide bonuses (IQ for technical, PP for physical, etc.)
- Critical successes/failures (natural 01/100)
- Some skills are passive (always active)
- Some skills require active use

---

**Status:** 6 of 150 complete (4%)  
**Estimated Time:** 60-80 hours for all 144 remaining skills  
**Template Ready:** Yes  
**Next Step:** Implement Phase 1 combat skills
