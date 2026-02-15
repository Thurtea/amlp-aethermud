# AetherMUD LPC Infrastructure Map

Comprehensive reference document mapping the entire `lib/` directory structure, all LPC subsystems, and their integration points with the custom C driver.

Generated: 2026-02-15

---

## Table of Contents

1. [Directory Overview](#1-directory-overview)
2. [Wizard Tools System](#2-wizard-tools-system)
3. [Domain Rooms (Castle, Start, New Camelot)](#3-domain-rooms)
4. [Spell System](#4-spell-system)
5. [Psionic System](#5-psionic-system)
6. [Skills System](#6-skills-system)
7. [Command System](#7-command-system)
8. [Base Classes (lib/std/)](#8-base-classes)
9. [Daemons (lib/daemon/)](#9-daemons)
10. [Race Files](#10-race-files)
11. [Language System](#11-language-system)
12. [Help System](#12-help-system)
13. [Special Objects](#13-special-objects)
14. [Expected vs Actual State](#14-expected-vs-actual)
15. [Integration Recommendations](#15-integration-recommendations)

---

## 1. Directory Overview

```
lib/
  cmds/           # 65 player commands + admin/ (11) + creator/ (17) + dragon/ (1)
  daemon/         # 8 central daemons (command, login, chargen, skills, languages, psionics, spells, combat)
  domains/        # Game world areas
    castle/       # 3 files (entry, spike, hawk)
    staff_castle/ # 16 rooms + 1 NPC
    start/        # 7 rooms + 3 NPCs + 1 object + 1 shop
    new_camelot/  # 36 files (garden grid, connectors, town buildings)
    wizard/       # Empty (workrooms generated dynamically)
  help/           # 25 help text files (basics/, social/, systems/, meta/, occs/)
  include/        # Header files (globals.h defines paths)
  languages/      # 12 language definition files
  obj/            # Cloneable objects
    wiztools/     # 6 wizard tool files + rift.lpc
  psionics/       # 14 psionic powers across 4 categories
  races/          # 52 race definition files
  save/           # Player save data (binary)
  secure/         # master.lpc, simul_efun.lpc, install.lpc
  skills/         # 10 skill files across 5 categories
  spells/         # 19 spells across levels 1-6
  std/            # 18 base class files (object, living, player, room, etc.)
  log/            # Server and game logs
```

**Total LPC Files:** ~337

---

## 2. Wizard Tools System

### File Locations

| File | Lines | Purpose |
|------|-------|---------|
| `lib/std/wiztool.lpc` | ~640 | Main wiztool command processor (attached to wizards) |
| `lib/obj/wiztools/base_wiztool.lpc` | 46 | Base class for specialized tools |
| `lib/obj/wiztools/chest.lpc` | 21 | Container that clones starter tools |
| `lib/obj/wiztools/crystal.lpc` | 28 | Viewing crystal (monitoring reference) |
| `lib/obj/wiztools/handbook.lpc` | 57 | Wizard's handbook (command reference) |
| `lib/obj/wiztools/staff.lpc` | 30 | Wizard's staff (command reference) |
| `lib/obj/wiztools/staff_of_demotion.lpc` | 194 | Admin tool for privilege management |
| `lib/obj/rift.lpc` | 94 | Temporary inter-room portal |

### Object Hierarchy

```
/std/object.lpc
  +-- /obj/wiztools/staff.lpc
  +-- /obj/wiztools/crystal.lpc
  +-- /obj/wiztools/handbook.lpc
  +-- /obj/rift.lpc
  +-- /std/container.lpc
        +-- /obj/wiztools/chest.lpc

/obj/wiztools/base_wiztool.lpc (inherits /std/object)
  +-- /obj/wiztools/staff_of_demotion.lpc
```

### Key Architecture

**Main Wiztool** (`/std/wiztool.lpc`):
- Attached via `attach_wiztool()` in `/std/player.lpc:226`
- Cloned from `/std/wiztool` on wizard promotion
- Provides: `cd`, `ls`, `pwd`, `cat`, `more`, `mkdir`, `rm`, `grep`, `find`, `head`, `tail`, `clone`, `dest`, `update`, `load`, `eval`, `call`, `goto`, `trace`, `errors`
- State: maintains `cwd` (working directory) per wizard

**Wiztool Attachment** (`/std/player.lpc`):
```lpc
void attach_wiztool(object wt) {  // line 226
    if (wiztool) return;
    if (!wt) wt = clone_object("/std/wiztool");
    wiztool = wt;
    wiztool->attach(this_object());
}
```

**Staff of Demotion** (`/obj/wiztools/staff_of_demotion.lpc`):
- Admin-only (requires `query_wiz_level() >= 2`)
- Commands: `promote <player> <level>`, `demote <player>`, `check <player>`
- Logs all changes to `/log/promotions.log`

**Global Constants** (`lib/include/globals.h`):
```lpc
#define WIZTOOL         "/std/wiztool"    // line 23
#define STD_WIZTOOL     "/std/wiztool"    // line 103
```

### Expected vs Actual

- **Expected**: Wizard tools are functional in-game objects with commands
- **Actual**: Tools are mostly decorative/reference items. The real wiztool is `/std/wiztool.lpc` which provides the actual commands. The `chest.lpc`, `crystal.lpc`, `handbook.lpc`, and `staff.lpc` are workroom flavor items that describe commands in their examine text but don't execute them directly
- **C driver overlap**: C driver has its own `goto`, `promote`, `brief`, `here`, `more` commands that duplicate some LPC wiztool functionality

---

## 3. Domain Rooms

### Castle Domain (`lib/domains/castle/`)

| File | Type | Description |
|------|------|-------------|
| `entry.lpc` | Room | Castle entry hall, spawns Spike + Hawk |
| `spike.lpc` | NPC | Dog Boy guard, level 5, 45 HP, 60 SDC |
| `hawk.lpc` | NPC | Hawk companion, inherits `/std/companion`, voice commands |

### Staff Castle Domain (`lib/domains/staff_castle/`)

**16 rooms** forming a complete castle:

| Room | Key Features |
|------|-------------|
| `courtyard.lpc` | Entry point, phoenix fountain, spawns spike NPC |
| `main_hall.lpc` | Great Hall with tapestry |
| `throne_room.lpc` | Ebony throne, examine interaction |
| `library.lpc` | 3-story library with book examination |
| `war_room.lpc` | Strategy room with battle maps |
| `dining_hall.lpc` | Grand dining with fireplace |
| `kitchen.lpc` | Prep areas |
| `stables.lpc` | Horses and tack |
| `garden.lpc` | Flowers and roses |
| `observatory.lpc` | Tower with telescope |
| `upper_hall.lpc` | Upper level, restricted area |
| `stairs.lpc` | Grand staircase between levels |
| `hedge_maze.lpc` | Main maze room, 4 exits |
| `maze_east.lpc` | Eastern path |
| `maze_west.lpc` | Western path |
| `maze_center.lpc` | Central fountain |

**NPC**: `npc/spike.lpc` - Guard dog (no_kill, tracking 70, dodge 50, bite 60)

### Start Domain (`lib/domains/start/`)

| File | Type | Description |
|------|------|-------------|
| `room/welcome.lpc` | Room | Welcome hall with project philosophy |
| `room/documentation.lpc` | Room | Technical reference |
| `room/void.lpc` | Room | Testing blank canvas |
| `room/combat_arena.lpc` | Room | Combat practice, spawns goblins |
| `village_center.lpc` | Room | Hub: N=castle, S=lake, E=shop, W=training |
| `shop_general.lpc` | Shop | Inherits `/std/shop`, weapons/armor/supplies |
| `lake_shore.lpc` | Room | Crystal Lake, swimming system (PE*5 check) |
| `lake_far_shore.lpc` | Room | Far shore, spawns techno-wizard hilt |
| `npc/test_goblin.lpc` | NPC | Goblin Raider (L3, 25 HP, 30 SDC) |
| `npc/moxim.lpc` | NPC | Rift Master (L20, opens rifts via LPC) |
| `npcs/grok_merchant.lpc` | NPC | Merchant (L5, 50 HP, random emotes) |
| `objects/technowizard_hilt.lpc` | Object | TW Flaming Sword Hilt (PPE charging) |

### New Camelot Domain (`lib/domains/new_camelot/`)

**36 files** - largest domain area:

**Town Buildings** (7):
- `town_square.lpc` - Central hub
- `gate.lpc` - Town entrance
- `tavern.lpc` - Social area
- `chapel.lpc` - Healing/faith
- `stables.lpc` - Mounts
- `training_grounds.lpc` - Combat practice
- `blacksmith_forge.lpc` - Equipment/crafting

**Garden Grid** (24 rooms):
- `garden/fountain.lpc` - Central fountain
- `garden/north_path_1.lpc` through `north_path_5.lpc` - North corridor
- `garden/east_X_Y.lpc` - 4x4 garden grid (16 rooms)
- `garden/obj/fountain.lpc` - Fountain object
- `garden/npc/magic_bush.lpc` - NPC encounter
- `garden/seed_spawn.lpc` - Spawner

**Connectors** (4):
- `connect/connector_north_1.lpc` - Links to north areas
- `connect/connector_south.lpc` - Links to south areas
- `connect/connector_west_1.lpc`, `connector_west_2.lpc` - Western links

### Key Objects

**Techno-Wizard Flaming Sword Hilt** (`lib/domains/start/objects/technowizard_hilt.lpc`):
```
- Commands: charge hilt with ppe, activate hilt, deactivate hilt
- Max PPE storage: 20
- Activation cost: 10 PPE minimum
- Active damage: 3d6+6 Mega Damage
- PPE drain: 1 PPE/minute while active
- Properties: is_mega_damage, damage_dice/sides/bonus, strike_bonus
```

**Rift Portal** (`lib/obj/rift.lpc`):
```
- Time-limited: ~10 seconds before collapse
- Warning messages at 7s and 9s
- Commands: enter, go
- Validates destination exists before allowing entry
```

---

## 4. Spell System

### Structure

```
lib/spells/
  level1/   # 6 spells: armor_of_ithan, blinding_flash, globe_of_daylight,
            #           see_the_invisible, sense_evil, sense_magic
  level2/   # 4 spells: chameleon, fear, levitation, swim_as_a_fish
  level3/   # 5 spells: energy_bolt, fireball, invisibility_simple, read_aura, telekinesis
  level5/   # 1 spell:  heal_wounds
  level6/   # 3 spells: lightning_bolt, magic_shield, tongues
```

**Total: 19 spells** across 5 spell levels (level4 empty)

### Base Class: `/std/spell.lpc` (196 lines)

**Properties:**
- `spell_id`, `spell_name`, `spell_level` (1-15)
- `ppe_cost` - PPE cost to cast
- `duration_type`: 0=instant, 1=per minute, 2=per level
- `range_type`: 0=self, 1=touch, 2=ranged
- `requires_verbal`, `requires_somatic`, `components`
- `casting_time` (in melee actions)

**Key Methods:**
- `can_cast(caster)` - Returns 1/0/-1 (can/cannot/insufficient PPE)
- `cast(caster, target)` - Deducts PPE, calls `apply_effect()`
- `apply_effect(caster, target)` - Override in subclasses

### Daemon: `/daemon/spells.lpc` (208 lines)

- `load_all_spells()` - Lazy-loads from level1-15 subdirectories
- `query_spell(spell_id)` - Retrieve spell by ID
- `calculate_starting_ppe(living, is_primary)` - PE + 3d6 (primary) or PE + 1d6 (secondary)
- `cast_spell(spell_id, caster, target)` - Execute with PPE checks

### Command: `/cmds/cast.lpc` (146 lines)

Usage: `cast` (list), `cast <spell>` (self), `cast <spell> <target>`, `cast info <spell>`

### Notable Spells

| Spell | Level | PPE | Effect |
|-------|-------|-----|--------|
| Armor of Ithan | 1 | 10 | +100 SDC magical armor, 5 min/level |
| Fireball | 3 | 10 | 4d6 damage, 90ft range, combat |
| Swim as a Fish | 2 | 6 | Perfect swimming + underwater breathing |
| Lightning Bolt | 6 | 15 | Heavy damage, ranged |
| Heal Wounds | 5 | 10 | Healing spell |

---

## 5. Psionic System

### Structure

```
lib/psionics/
  healing/    # 3 powers: bio_regeneration, deaden_pain, healing_touch
  physical/   # 3 powers: levitation, psi_sword, telekinesis
  sensitive/  # 6 powers: empathy, mind_block, presence_sense,
              #           read_aura_psi, sixth_sense, telepathy
  super/      # 2 powers: mind_block, psi_sword
```

**Total: 14 psionic power files** (some duplicated across categories)

### Base Class: `/std/psionic.lpc` (162 lines)

**Properties:**
- `power_id`, `power_name`, `power_category` (physical/sensitive/healing/super)
- `isp_cost` - ISP cost to activate
- `duration_type`: 0=instant, 1=per minute, 2=per melee round
- `range_type`: 0=self, 1=touch, 2=ranged
- `required_stats`, `required_values` - Stat minimums

**Key Methods:**
- `can_activate(living)` - Returns 1/0/-1
- `activate(user, target)` - Deducts ISP, calls `apply_effect()`
- `meets_requirements(living)` - Validates stat requirements

### Daemon: `/daemon/psionics.lpc` (206 lines)

- `load_all_powers()` - Loads from all 4 category subdirectories
- `calculate_starting_isp()`:
  - Minor: ME + 1d6
  - Major: ME x2 + 2d6
  - Master: ME x4 + 3d6
- `activate_power(power_id, user, target)` - Execute with ISP checks

### Command: `/cmds/manifest.lpc` (148 lines)

Usage: `manifest` (list), `manifest <power>`, `manifest <power> <target>`, `manifest info <power>`

### Notable Powers

| Power | Category | ISP | Effect |
|-------|----------|-----|--------|
| Psi-Sword | Super | 10+2/min | 3d6 MDC energy blade, maintained |
| Healing Touch | Healing | 6 | 2d6 HP/SDC healing, touch |
| Telepathy | Sensitive | 4 | Read surface thoughts, blocked by Mind Block |
| Mind Block | Super | 4 | Toggle mental defense, blocks other psionics while active |
| Sixth Sense | Sensitive | 2 | Danger warning |

---

## 6. Skills System

### Structure

```
lib/skills/
  medical/    # 1 skill:  first_aid
  physical/   # 2 skills: climbing, swimming
  pilot/      # 1 skill:  pilot_automobile
  technical/  # 1 skill:  literacy
  weapons/    # 1 skill:  wp_knife
  # Standalone (root level):
  pilot_aircraft.lpc
  pilot_power_armor.lpc
  pilot_robot.lpc
  pilot_spacecraft.lpc
```

**Total: 10 skill files**

### Base Class: `/std/skill.lpc` (197 lines)

**Properties:**
- `skill_id`, `skill_name`, `skill_category`
- `base_percentage` - Starting %
- `level_bonus` - Bonus per level
- `max_percentage` - Usually 98%
- `related_skills[]` / `related_bonuses[]` - Synergy bonuses
- `is_primary_only` - OCC-restricted flag

**Key Methods:**
- `calculate_percentage(living, level)` - Skill % at given level (includes IQ bonus for technical/medical)
- `attempt(living)` - d100 roll: critical failure 96-100, success if roll <= %

### Daemon: `/daemon/skills.lpc` (244 lines)

- `load_all_skills()` - Loads from all category subdirectories
- `attempt_skill(skill_id, living)` - d100 vs skill (96+ = critical failure)
- `can_learn_skill(skill_id, living, is_primary)` - Checks requirements

### Command: `/cmds/skills.lpc` (65 lines)

Usage: `skills` (list all by category), `skills <skill>` (detailed info)

### Notable Skills

| Skill | Category | Base% | Per-Level | Notes |
|-------|----------|-------|-----------|-------|
| Swimming | Physical | 50% | +5% | +5% synergy from scuba |
| First Aid | Medical | 45% | +5% | Heals 1d6 SDC / 1d4 HP |
| WP Knife | Weapons | 0% | 0% | Provides strike/parry/throw bonuses instead |
| Pilot Auto | Pilot | 60% | +2% | +5% from automotive_mechanics |
| Literacy | Technical | 30% | +5% | IQ bonus applies |

---

## 7. Command System

### Architecture

**Dispatcher**: `/daemon/command.lpc` (296 lines)

5-priority dispatch system:
1. Wiztool objects (wizard priority)
2. `add_action` registered commands (room/NPC actions)
3. Player local commands (abilities)
4. Environment commands (room-specific)
5. Global command registry (hardcoded map) -> Path search fallback (`/cmds/`, `/cmds/admin/`, `/cmds/wizard/`)

### Player Commands (65 files in `/cmds/`)

**Communication:**
`say`, `shout`, `tell`, `whisper`, `chat`, `emote`

**Looking/Navigation:**
`look`, `examine`, `exits`, `go`, `enter`

**Combat:**
`attack`, `kill`, `flee`, `stop`

**Equipment:**
`wield`, `unwield`, `wear`, `remove`, `get`/`take`, `drop`, `put`, `give`, `inventory`, `equipment`, `repair`

**Magic/Abilities:**
`cast`, `manifest`, `skills`, `languages`, `tattoos`, `metamorph`

**Economy:**
`buy`, `sell`, `credits`, `balance`, `money`

**Character:**
`stats`/`score`, `position`, `surname`, `vstatus`

**Social:**
`introduce`, `remember`, `forget`, `who`, `users`

**System:**
`quit`, `help`, `prompt`, `start`

**Specialized:**
`pilot`, `drive`, `dragon/breath`

### Admin Commands (11 files in `/cmds/admin/`)

| Command | Purpose | Access |
|---------|---------|--------|
| `promote.lpc` | Grant wizard/admin privileges | Wizard+ |
| `demote.lpc` | Remove privileges | Admin |
| `setocc.lpc` | Assign OCC to players | Wizard+ |
| `grantskill.lpc` | Grant skills to players | Wizard+ |
| `tattoogun.lpc` | Grant magical tattoos (Atlanteans) | Wizard+ |
| `stat.lpc` | Show object statistics | Wizard+ |
| `goto.lpc` | Teleport to room | Wizard+ |
| `shutdown.lpc` | Shutdown server | Admin |
| `testskill.lpc` | Test skill check mechanics | Wizard+ |
| `wiz.lpc` | Shorthand wiztool access | Wizard+ |
| `wiztool.lpc` | Load/manage wiztool | Wizard+ |

### Creator Commands (17 files in `/cmds/creator/`)

`cd`, `ls`, `pwd`, `cat`, `head`, `tail`, `grep`, `find`, `mkdir`, `ed`, `eval`, `clone`, `load`, `update`, `destruct`, `force`, `mkroom`, `mkobject`

### Command Pattern

All commands follow:
```lpc
#include <globals.h>

int main(string args) {
    object user = previous_object();
    // ... command logic ...
    return 1;
}

string query_help() {
    return "COMMAND - Description\n\nUsage:\n...";
}
```

---

## 8. Base Classes (`lib/std/`)

| File | Lines | Purpose |
|------|-------|---------|
| `object.lpc` | ~306 | Base for all objects (ids, descriptions, weight, properties, armor) |
| `living.lpc` | - | Base for all living things (stats, combat, movement) |
| `player.lpc` | ~856+ | Player object (login, wiztool, introduction, saving) |
| `room.lpc` | - | Base for rooms (exits, items, descriptions, climate, light) |
| `container.lpc` | ~40 | Holds other objects (inventory, weight limits) |
| `skill.lpc` | ~197 | Skill definition base (percentage, requirements, synergies) |
| `spell.lpc` | ~196 | Spell definition base (PPE cost, duration, range, effects) |
| `psionic.lpc` | ~162 | Psionic power base (ISP cost, categories, requirements) |
| `race.lpc` | - | Race definition base (stat bonuses, abilities, health type) |
| `occ.lpc` | - | OCC definition base (skill packages, abilities) |
| `language.lpc` | - | Language definition base (garbling, comprehension) |
| `shop.lpc` | - | Shop base (buy/sell, inventory, pricing) |
| `companion.lpc` | - | NPC companion base (voice commands, follow) |
| `vehicle.lpc` | - | Vehicle base (piloting, damage) |
| `vehicle_room.lpc` | - | Interior room of vehicles |
| `corpse.lpc` | - | Dead body object |
| `daemon.lpc` | - | Daemon base class |
| `wiztool.lpc` | ~640 | Wizard command processor |

### Key Inheritance Chain

```
/std/object.lpc
  +-- /std/living.lpc
  |     +-- /std/player.lpc
  +-- /std/container.lpc
  +-- /std/room.lpc
  +-- /std/shop.lpc (inherits room)
  +-- /std/vehicle.lpc
  +-- /std/companion.lpc (inherits living)
```

---

## 9. Daemons (`lib/daemon/`)

| Daemon | Lines | Purpose |
|--------|-------|---------|
| `command.lpc` | 296 | Central command dispatcher with 5-priority routing |
| `login.lpc` | - | Login/character creation flow |
| `chargen.lpc` | - | Character generation daemon |
| `skills.lpc` | 244 | Skill registry, calculation, attempt rolls |
| `spells.lpc` | 208 | Spell registry, PPE calculation, casting |
| `psionics.lpc` | 206 | Psionic registry, ISP calculation, activation |
| `languages.lpc` | - | Language registry, garbling, comprehension |
| `combat.lpc` | - | LPC-side combat integration |

### Daemon Pattern

All daemons follow:
1. Lazy-load objects on first access
2. Cache in internal mappings
3. Provide query/lookup functions
4. Provide calculation utilities
5. Provide formatted display functions

Loaded at boot by `/secure/master.lpc` (7 core daemons).

---

## 10. Race Files

**Location:** `lib/races/` - **52 race files**

Each inherits `/std/race` and defines:
- Stat bonuses/penalties
- Health type (HP/SDC vs MDC)
- Natural weapons
- Innate abilities (psionics, magic, flight)
- Languages
- Size category
- Attacks per round

**Dragon Races:** `dragon_hatchling`, `adult_dragon`, `ancient_dragon`, `great_horned_dragon`, `thorny_dragon`, `dragon_juicer`

**Human Variants:** `human`, `true_atlantean`

**D-Bee Races:** `wolfen`, `simvan`, `trimadore`, `eandroth`, `uteni`, `noli`, `promethean`, `brodkil`, `dog_boy`

**Supernatural:** `vampire`, `werewolf`, `demon`, `deevil`, `godling`, `cosmo_knight`, `nightbane`, `gargoyle`

**Psychic RCCs:** `mind_melter`, `mind_bleeder`, `burster`, `psi_stalker`, `psi_healer`, `psi_ghost`

**Juicers:** `titan_juicer`, `mega_juicer`, `quick_flex`

**Others:** `elf`, `dwarf`, `gnome`, `halfling`, `ogre`, `orc`, `troll`, `goblin`, `hobgoblin`, `minotaur`, `changeling`, `mutant_animal`, `cat_girl`, `splugorth`, `splugorth_minion`, `splynn_slave`, `minion`

---

## 11. Language System

**Location:** `lib/languages/` - **12 language files**

| Language | File |
|----------|------|
| American | `american.lpc` |
| Atlantean | `atlantean.lpc` |
| Demonic | `demonic.lpc` |
| Dragonese | `dragonese.lpc` |
| Dwarven | `dwarven.lpc` |
| Elven | `elven.lpc` |
| Euro | `euro.lpc` |
| Faerie | `faerie.lpc` |
| Goblin | `goblin.lpc` |
| Japanese | `japanese.lpc` |
| Spanish | `spanish.lpc` |
| Techno-Can | `techno_can.lpc` |

Each inherits `/std/language` and defines substitution tables for garbling speech when the listener doesn't know the language.

**Daemon:** `/daemon/languages.lpc` manages registration and comprehension checks.

**Commands:** `languages` (list known), `language <name>` / C driver `speak` command (switch active language)

---

## 12. Help System

**Location:** `lib/help/` - **25 help text files**

```
help/
  basics/     # commands, movement, combat, equipment, stats, experience,
              # death, credits, look
  social/     # communication, interaction, clans
  systems/    # magic, psionics, skills, languages
  meta/       # wizard, admin, rules, newbie
  occs/       # vagabond, cyber-knight, ley-line-walker,
              # dragon-hatchling, sunaj-assassin
```

**Command:** `/cmds/help.lpc` searches these directories and displays matching files.

---

## 13. Special Objects

### Techno-Wizard Flaming Sword Hilt

**File:** `lib/domains/start/objects/technowizard_hilt.lpc` (299 lines)

PPE-powered weapon with charge/activate/deactivate cycle:
- `charge hilt with [amount] ppe` - Transfer PPE from player to hilt (max 20)
- `activate hilt` - Ignite blade (requires 10 PPE), sets 3d6+6 MD weapon properties
- `deactivate hilt` - Dismiss blade, conserves remaining PPE
- Auto-drain: `drain_ppe()` called every 60s, blade dies when PPE depleted
- Sets properties: `damage_dice=3`, `damage_sides=6`, `damage_bonus=6`, `is_mega_damage=1`

### Rift Portal

**File:** `lib/obj/rift.lpc` (94 lines)

Temporary portal object:
- `set_destination(path)` / `query_destination()`
- `cmd_enter(what)` - Handles `enter`/`go` commands
- Auto-collapses: warning at 7s ("edges fraying"), 9s ("begins collapsing"), destroyed at 10s
- Created by Moxim NPC (`lib/domains/start/npc/moxim.lpc`)

---

## 14. Expected vs Actual State

### LPC Rooms vs C Driver Rooms

| Aspect | Expected | Actual |
|--------|----------|--------|
| Room loading | LPC rooms loaded dynamically | 24 C-hardcoded rooms + LPC rooms for domains |
| New Camelot | Full LPC room grid | 36 LPC files exist, integrated via C flex-exits |
| Staff Castle | Wizard area | 16 LPC rooms, fully defined but integration TBD |
| Start Domain | Tutorial area | 7 rooms + NPCs + objects, partially connected |

### LPC Commands vs C Driver Commands

| Feature | C Driver | LPC | Status |
|---------|----------|-----|--------|
| Movement (n/s/e/w) | C handles directly | LPC wrappers exist | C primary |
| say/emote | C handles with intro checks | LPC versions also exist | Parallel |
| look | C handles room display | LPC `/cmds/look.lpc` exists | Both active |
| goto | C handles (player + room) | LPC `/cmds/admin/goto.lpc` | Both active |
| promote/demote | C driver internal | LPC admin commands + staff_of_demotion | Both active |
| cast/manifest | Not in C driver | LPC only | LPC only |
| Skills | C driver has skill arrays | LPC has skill daemon + command | Both store data |
| Combat | C driver `combat.c` | LPC `/daemon/combat.lpc` exists | C primary |
| Save/Load | C driver binary format | LPC `save_me()` exists in player.lpc | C primary |

### Spell/Psionic/Skill Coverage

| System | Defined in LPC | Used by C Driver | Gap |
|--------|---------------|------------------|-----|
| Spells | 19 spells (levels 1-6) | C stores spell_id + rank | LPC defines effects, C stores data |
| Psionics | 14 powers (4 categories) | C stores power_id + rank | LPC defines effects, C stores data |
| Skills | 10 skills (5 categories) | C stores skill_id + % + uses | LPC defines mechanics, C stores data |
| Races | 52 race files | C loads via race_loader.c | Integrated - C reads LPC files |

---

## 15. Integration Recommendations

### High Priority

1. **Unify command dispatch**: Many commands exist in both C driver and LPC. Consider routing all non-movement commands through LPC command dispatcher to avoid duplication.

2. **Connect LPC spell/psionic effects to C combat**: The LPC spell and psionic systems define `apply_effect()` methods with damage values, durations, and properties. The C combat system could call these during combat ticks.

3. **Bridge LPC rooms to C navigation**: New Camelot (36 rooms) and Staff Castle (16 rooms) are fully defined in LPC but may not be accessible from C room navigation. The flex-exit system started for New Camelot should be extended.

### Medium Priority

4. **Consolidate privilege management**: Both C driver promote/demote and LPC staff_of_demotion.lpc manage wizard levels. Choose one as authoritative.

5. **Activate NPC behaviors**: NPCs like Moxim (rift opening), Grok (merchant), and Spike (guard) have full LPC implementations with `add_action()` commands, heartbeats, and dialogue. These need the LPC VM to execute.

6. **Enable LPC shop system**: `shop_general.lpc` inherits `/std/shop` with buy/sell/list commands. Currently non-functional without LPC execution.

### Lower Priority

7. **Expand skill coverage**: Only 10 skills defined vs. the Palladium system's 200+. Priority: combat skills (WP Sword, WP Energy Pistol), survival skills (Wilderness Survival, Land Navigation).

8. **Fill spell gaps**: Level 4 is empty. Levels 7-15 have no spells. Priority: common combat spells and utility spells.

9. **Activate TW hilt in C**: The techno-wizard hilt has a complete PPE charging system in LPC. This could be adapted as a C-side item template with special commands.

10. **Help system**: 25 help files exist but `/cmds/help.lpc` may not be connected to C driver's help command. Consider bridging or using C to serve help text files directly.
