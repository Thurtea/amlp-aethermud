# Content Audit — AMLP AetherMUD
Date: 2026-02-23
Auditor: Claude Sonnet 4.6

---

## Executive Summary

| System | Files Present | Files Needed | % Complete |
|--------|--------------|--------------|------------|
| Spells (LPC, loaded by engine) | 19 | ~75+ | 25% |
| Spells (JSON reference data) | 75 spells in 9/15 level files | 15 level files full | 60% |
| Psionic Powers | 12 | ~52 | 23% |
| Skills | 11 | ~150 | 7% |
| Races | 54 (22 stubs) | 54 | 100% files, ~59% complete |
| OCCs | 41 (10 stubs) | ~47 | 87% files, ~76% complete |

---

## SPELLS

### JSON Reference Files (`lib/spells/level_N.json`)

The JSON files are **reference data only** — `lib/daemon/spells.lpc` does NOT load them.
The daemon loads exclusively from `lib/spells/*.lpc` and `lib/spells/levelN/*.lpc`.

| Level | JSON Spells | LPC Files | Coverage |
|-------|-------------|-----------|----------|
| 1 | 9 (Blinding Flash, Cloud of Smoke, Death Trance, Globe of Daylight, See Aura, See the Invisible, Sense Evil, Sense Magic, Thunderclap) | 6 | Good |
| 2 | 23 (Apparition, Befuddle, Chameleon, Climb, Concealment, Detect Concealment, Fear, Heavy Breathing, Levitation, Mystic Alarm, Turn Dead, Mystic Portal, Call Lightning, Compulsion, Cure Illness, Fire Ball, Impervious to Energy, Memory Bank, Reduce: Self, Teleport: Lesser, Time Slip, Tongues, Words of Truth) | 4 | Partial |
| 3 | 10 (Breathe Without Air, Energy Bolt, Fingers of Wind, Fool's Gold, Impervious to Fire, Impervious to Poison, Invisibility: Simple, Multiple Image, Paralysis: Lesser, Telekinesis) | 5 | Partial |
| 4 | **MISSING** (JSON file empty/absent) | 0 | None |
| 5 | **MISSING** (JSON file empty/absent) | 1 | None |
| 6 | **MISSING** (JSON file empty/absent) | 3 | None |
| 7 | **MISSING** (JSON file empty/absent) | 0 | None |
| 8 | **MISSING** (JSON file empty/absent) | 0 | None |
| 9 | **MISSING** (JSON file empty/absent) | 0 | None |
| 10 | 7 (Banishment, Control/Enslave Entity, Metamorphosis: Superior, Mystic Portal, Summon & Control Rodents, ×2 more) | 0 | None |
| 11 | 6 (Anti-Magic Cloud, Create Mummy, Create Magic Scroll, Remove Curse, Summon and Control Animals, ×1 more) | 0 | None |
| 12 | 7 (Amulet, Calm Storms, Metamorphosis: Mist, Create Zombie, Summon and Control Entity, ×2 more) | 0 | None |
| 13 | 6 (Protection Circle: Superior, Create Golem, Summon and Control Storm, Summon Lesser Being, Sanctum, ×1 more) | 0 | None |
| 14 | 5 (Close Rift, Id Barrier, Impenetrable Wall of Force, Restoration, Transformation) | 0 | None |
| 15 | 2 (Dimensional Portal, Teleport: Superior) | 0 | None |

**Total JSON spells: 75** (in 9 of 15 levels; levels 4-9 have no JSON data)
**Total LPC spell files: 19** (levels 1-3, 5, 6 only)
**Fully implemented vs stubs:** All 19 existing LPC files appear implemented (no TODO markers; `armor_of_ithan.lpc` has full `cast()` logic).

### Gap Analysis — Spells
- Levels 4-9: No JSON reference data AND no LPC files. ~40-60 spells likely missing entirely.
- Levels 10-15: JSON reference data exists but zero LPC files. 33 spells need LPC implementation.
- Levels 1-3: JSON has 42 spells; only 15 LPC files exist → ~27 unimplemented.

**Priority:** Convert all JSON-defined spells to LPC files (levels 1-3 first, then 10-15, then 4-9).

---

## PSIONICS

### Files Present (12 total)

| Category | Files | Powers |
|----------|-------|--------|
| healing/ | bio_regeneration, deaden_pain, healing_touch | 3 |
| physical/ | levitation, telekinesis | 2 |
| sensitive/ | empathy, mind_block, presence_sense, read_aura_psi, sixth_sense, telepathy | 6 |
| super/ | psi_sword | 1 |

### Files Missing (~40 needed)

**Sensitive (need ~12 more):**
- clairvoyance, commune_with_spirits, detect_psionics, hypnotic_suggestion, meditation
- remote_sensing, see_the_invisible, sense_danger, sense_evil, speed_reading, total_recall
- object_read (sometimes classified sensitive)

**Physical (need ~15 more):**
- alter_aura, body_weapon, deadbolt, ectoplasm, electrokinesis
- impervious_to_cold, impervious_to_fire, impervious_to_poison
- increase_attribute, resist_fatigue, telekinetic_leap, telekinetic_punch, telekinetic_push
- telemechanics, pyrokinesis

**Healing (need ~10 more):**
- cure_minor_disorders, increased_healing, induce_sleep, lifespan
- psychic_diagnosis, psychic_purification, psychic_surgery
- reduce_pain, restore_fatigue, suppress_fear

**Super (need ~20 more):**
- astral_projection, bio_manipulation, electrokinesis_major, empathy_superior
- group_mind_block, group_trance, induce_nightmare, insert_memory
- invisible_haze, ley_line_transmission, mask_isp, mind_bolt (C-level only currently)
- mind_bond, mind_wipe, psi_shield, psychic_omni_sight
- pyrokinesis_major, sense_ley_lines, telekinesis_superior, telepathy_superior

**Note:** `mind_bolt` is implemented in `src/psionics.c` (C-level, id=25) but has no LPC counterpart file.

---

## SKILLS

### Files Present (11 total)

| Path | Skill |
|------|-------|
| skills/physical/climbing.lpc | Climbing |
| skills/physical/swimming.lpc | Swimming |
| skills/medical/first_aid.lpc | First Aid |
| skills/technical/literacy.lpc | Literacy |
| skills/pilot/pilot_automobile.lpc | Pilot: Automobile |
| skills/pilot_aircraft.lpc | Pilot: Aircraft (root level — should be in pilot/) |
| skills/pilot_power_armor.lpc | Pilot: Power Armor (root level — should be in pilot/) |
| skills/pilot_robot.lpc | Pilot: Robot (root level — should be in pilot/) |
| skills/pilot_spacecraft.lpc | Pilot: Spacecraft (root level — should be in pilot/) |
| skills/weapons/wp_knife.lpc | W.P. Knife |
| skills/falconry.lpc | Falconry (root level — unusual, but unique enough) |

**Categories with zero files:** communications, domestic, electrical, espionage, mechanical, military, rogue, science, wilderness (complete gaps)

### Skills Needed by Category (~139 missing)

**Communications (7 needed):**
language, radio_basic, radio_scramblers, tv_video, telephone_operation, sign_language, cryptography_comm

**Domestic (7 needed):**
cook, dance, fishing_domestic, play_instrument, sewing, sing, housekeeping

**Electrical (5 needed):**
basic_electronics, computer_repair, electrical_engineer, robot_electronics, weapons_systems_elec

**Espionage (13 needed):**
concealment, disguise, escape_artist, forgery, intelligence, interrogation,
pick_locks, pick_pockets, safecracking, sniper, surveillance, tracking_esp, wilderness_survival_esp

**Mechanical (7 needed):**
aircraft_mechanics, armorer, automotive_mechanics, basic_mechanics, locksmith, mechanical_engineer, weapons_engineer

**Medical (5 needed):**
holistic_medicine, medical_doctor, paramedic, field_surgery, forensics

**Military (12 needed):**
camouflage, combat_driving, demolitions, demolitions_disposal, detect_ambush, detect_concealment,
find_contraband, military_etiquette, naval_tactics, parachuting, recognize_weapon_quality, trap_detection

**Physical (7 new needed — climbing/swimming present):**
acrobatics, athletics, boxing, gymnastics, juggling, running, wrestling

**Pilot (11 new needed — automobile/aircraft/robots/spacecraft present):**
boat_motor, boat_sail, helicopter, horsemanship_general, horsemanship_exotic,
hovercycle, jet_pack, military_basic, motorcycles, tanks_apcs, submersible

**Pilot Related (4 needed):**
navigation, read_sensory_equipment, weapon_systems, detect_concealment_pr

**Rogue (11 needed):**
concealment_rogue, disguise_rogue, forgery_rogue, gambling, impersonation,
palming, pick_locks_rogue, pick_pockets_rogue, prowl, safecracking_rogue, streetwise

**Science (14 needed):**
anthropology, archaeology, astronomy, astrophysics, biology, botany, chemistry,
chemistry_analytical, electrical_engineering, geology, math_basic, math_advanced,
medical_science, xenobiology

**Technical (9 new needed — literacy present):**
computer_operation, computer_programming, computer_hacking, photography,
research, surveillance_systems, tv_video_tech, writing, cryptography

**WP Ancient (11 needed — wp_knife present):**
wp_axe, wp_chain, wp_blunt, wp_forked, wp_paired, wp_pole_arm,
wp_shield, wp_spear, wp_staff, wp_sword, wp_targeting

**WP Modern (9 needed):**
wp_auto_pistol, wp_energy_pistol, wp_energy_rifle, wp_explosives,
wp_heavy_md, wp_shotgun, wp_smg, wp_pistol, wp_rifle

**Wilderness (10 needed):**
fishing_wild, foraging, hunting, land_navigation, mountain_man,
outdoorsmanship, skin_hides, track_trap_animals, tracking_wild, wilderness_survival

---

## RACES

### Completeness Assessment (54 files total)

**Method:** Files with `set_natural_sdc(0)` are likely stubs (forgot to set SDC). Files with content (non-zero SDC or MDC creatures) are more complete.

| Status | Races |
|--------|-------|
| **Appears Complete** (~32) | atlantean, burster, cat_girl, changeling, dog_boy, dragon_hatchling, dwarf, eandroth, elf, goblin, great_horned_dragon, halfling, hobgoblin, minotaur, mutant_animal, nightbane, noli, ogre, orc, promethean, psi_ghost, quick_flex, secondary_vampire, simvan, splugorth, splynn_slave, trimadore, troll, true_atlantean, uteni, wolfen, mind_bleeder |
| **Stubs (zero SDC)** (~22) | adult_dragon, ancient_dragon, brodkil, cosmo_knight, deevil, demon, dragon_juicer, gargoyle, gnome, godling, human, mega_juicer, mind_melter, minion, psi_healer, psi_stalker, splugorth_minion, thorny_dragon, titan_juicer, vampire, werewolf, wild_vampire |

**Note:** `human` having `set_natural_sdc(0)` is arguably correct (humans have 0 natural AR/SDC in Palladium), but the file should have non-zero base SDC from constitution stats. Needs verification.

### Missing Races (notable gaps vs Palladium source books)
No additional race files are missing from the core Rifts RPG book that aren't already present. The 54 existing files cover all major playable races. The stub files need their stat blocks filled in.

---

## OCCS

### Completeness Assessment (41 files total)

**Files with TODO markers (10 stubs):**
- city_rat, cosmo_knight, full_conversion_borg, mystic, power_armor_pilot
- psi_healer, psi_stalker, robot_pilot, wilderness_scout, xiticix_worker

**Files without TODO but possibly incomplete:** Most have `set_base_isp(0)` which is correct for non-psionic OCCs; not a stub indicator.

**Appears Complete (~31):**
battle_magus, biomancer, body_fixer, burster, crazy, cyber_knight, dragon_hatchling_rcc, elemental_fusionist, fury_beetle, glitter_boy_pilot, headhunter, juicer, ley_line_walker, line_walker, mercenary, mind_melter, necromancer, operator, psi-stalker-r-c-c, rogue_scholar, rogue_scientist, sea_titan, shifter, special_forces, stone_master, sunaj_assassin, techno_wizard, temporal_wizard, vagabond, warlock, xiticix_warrior

### Missing Core Rifts OCCs (6 notable gaps)

| OCC | Source | Notes |
|-----|--------|-------|
| Tattooed Man/Warrior | Rifts RPG / Atlantis | Major Atlantean OCC; pairs with atlantean/true_atlantean races |
| Undead Slayer | Rifts Atlantis | Anti-supernatural Atlantean OCC |
| Coalition Grunt | Rifts RPG (Coalition) | Basic CS soldier; different from Special Forces/Headhunter |
| Psi-Mystic | Rifts RPG | Psionic/magic hybrid; mid-tier caster |
| Cyber-Doc | Rifts RPG | Cybernetics specialist; different from Body Fixer |
| Ranger | Rifts RPG | Wilderness/guerrilla combat OCC |

---

## Gap-Fill Actions Taken (2026-02-23)

Following this audit, the following files were generated:

### TASK 1 — Skills
Generated individual `.lpc` stub files for all ~139 missing Palladium Rifts core skills organized into category subdirectories under `lib/skills/`. Each file has: `skill_id`, `skill_name`, `skill_desc` (TODO:CONTENT), `skill_category`, `base_percentage`, `level_bonus`, `max_percentage`, `stat_requirements`, and a `perform()` stub.

### TASK 2 — Psionics
Generated `.lpc` stub files for all ~40 missing psionic powers organized into `lib/psionics/healing/`, `physical/`, `sensitive/`, `super/`. Each file has: `power_id`, `power_name`, `power_desc` (TODO:CONTENT), `power_category`, `isp_cost`, `duration_type`, `range_type`, and an `apply_effect()` stub.

### TASK 3 — Missing OCCs
Generated stub OCC files for 6 missing core Rifts OCCs: `tattooed_man`, `undead_slayer`, `coalition_grunt`, `psi_mystic`, `cyber_doc`, `ranger`.

---

## Recommended Next Steps (Priority Order)

1. **Fill stub races** (22 files) — Set correct SDC/MDC values, stat modifiers, and racial abilities for adult/ancient dragons, vampires, demons, deevilds, etc.
2. **Fix TODO OCCs** (10 files) — Complete city_rat, cosmo_knight, full_conversion_borg, mystic, power_armor_pilot, psi_healer, psi_stalker, robot_pilot, wilderness_scout, xiticix_worker.
3. **Convert JSON spells to LPC** — 75 spells defined in JSON have no LPC implementation. Start with levels 1-3 (most commonly cast).
4. **Implement skill perform() functions** — Connect skills to gameplay actions (climbing checks on room exits, first_aid in combat, etc.).
5. **Implement psionic activate() functions** — Wire the stub powers to actual game effects.
6. **Fill spell JSON gaps** — Levels 4-9 have no JSON data; source from Palladium books.
