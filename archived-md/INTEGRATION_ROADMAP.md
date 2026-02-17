# AetherMUD Integration Roadmap

Prioritized plan for connecting LPC infrastructure to the C driver, based on `LPC_INFRASTRUCTURE_MAP.md` analysis and C source code audit.

Generated: 2026-02-15

---

## Priority 1: Quick Wins

These features have all the pieces built but just aren't wired together. Each is 10-50 lines of C code.

---

### 1.1 Wire magic_spell_tick() into combat heartbeat

**Problem:** `magic_spell_tick()` exists in `src/magic.c:725-745` but is **never called**. Multi-round casting countdown, PPE recovery, and spell completion all do nothing.

**Fix:** Add call in `src/combat.c` `combat_tick()` (line ~465):

```c
// In combat_tick() after combat processing
for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i] && sessions[i]->state == STATE_PLAYING) {
        magic_spell_tick(sessions[i]);
    }
}
```

**Files to modify:**
- `src/combat.c:465` - Add `magic_spell_tick()` call in `combat_tick()`
- `src/magic.h` - Ensure `magic_spell_tick(PlayerSession *sess)` is declared

**Effect:** Enables multi-round spell casting (casting_rounds_remaining countdown), PPE natural recovery, and `magic_complete_cast()` which already calls LPC `/daemon/spells` via `obj_call_method()`.

**Effort:** ~5 lines

---

### 1.2 Wire psionics_power_tick() into combat heartbeat

**Problem:** `psionics_power_tick()` exists in `src/psionics.c:437-442` but is **never called**. ISP recovery does nothing.

**Fix:** Same pattern as magic:

```c
// In combat_tick() alongside magic tick
psionics_power_tick(sessions[i]);
```

**Files to modify:**
- `src/combat.c:465` - Add `psionics_power_tick()` call in `combat_tick()`
- `src/psionics.h` - Ensure `psionics_power_tick(PlayerSession *sess)` is declared

**Effect:** Enables natural ISP recovery each combat round.

**Effort:** ~5 lines

---

### 1.3 Wire meditation ticks

**Problem:** `magic_meditate_tick()` (`src/magic.c:747-756`) and `psionics_meditate_tick()` (`src/psionics.c:444-453`) exist but are **never called**. The `meditate` command sets `is_meditating = true` but nothing happens.

**Fix:** Add to the same combat_tick loop:

```c
if (sessions[i]->character.magic.is_meditating)
    magic_meditate_tick(sessions[i]);
if (sessions[i]->character.psionics.is_meditating)
    psionics_meditate_tick(sessions[i]);
```

**Files to modify:**
- `src/combat.c:465` - Add meditation tick calls

**Effect:** Meditation actually recovers PPE/ISP at accelerated rate.

**Effort:** ~8 lines

---

### 1.4 Add psionic power effects (currently stubs)

**Problem:** `psionics_activate_power()` (`src/psionics.c:414-435`) deducts ISP and prints a message but **applies no actual effect**. Compare with magic which calls LPC daemon.

**Fix:** Add effect switch in `psionics_activate_power()` after ISP deduction:

```c
switch (power_id) {
    case 6:  // Bio-Regeneration
        ch->hp = (ch->hp + 2 * 6 > ch->max_hp) ? ch->max_hp : ch->hp + 12;
        send_to_player(sess, "Warm energy flows through you, healing wounds.\n");
        break;
    case 7:  // Psychic Healing
        // Heal target if specified, else self
        break;
    case 0:  // Mind Block
        // Toggle mental defense flag
        break;
    // ... etc
}
```

**Files to modify:**
- `src/psionics.c:414-435` - Add effect switch after ISP deduction

**Reference:** LPC power definitions in `lib/psionics/healing/healing_touch.lpc` (2d6 HP), `lib/psionics/super/mind_block.lpc` (toggle defense), `lib/psionics/physical/psi_sword.lpc` (3d6 MDC blade)

**Effort:** ~80 lines (switch cases for 25 powers)

---

### 1.5 Add `swim` command for water rooms

**Problem:** Swimming skill exists in C (`src/skills.c` skill ID 2, `SWIMMING` macro line 156), base 35%. But there's no `swim` command and no water room mechanic. LPC `lake_shore.lpc` has a full swimming system with PE*5 checks.

**Fix:** Add to `src/driver.c` command dispatch:

```c
if (strcmp(cmd, "swim") == 0) {
    // Check if current room has water exit
    // Roll skill_check(swimming_percentage) or use PE*5 fallback
    // Success: move to water destination room
    // Failure: 1d5 SDC damage, stay put
    cmd_swim(session, args ? args : "");
    result.type = VALUE_NULL;
    return result;
}
```

**Files to modify:**
- `src/driver.c` - Add `swim` command in dispatch (~line 1832)
- `src/room.c` or `src/chargen.c` - Implement `cmd_swim()` function
- `src/room.h` - Add water exit flag to room data

**Reference:** LPC implementation in `lib/domains/start/lake_shore.lpc` uses `skill - 40` difficulty, 1-5 SDC damage on failure, `swim_as_a_fish` property bypasses checks.

**Effort:** ~40 lines

---

### 1.6 Add `manifest` as alias for `use` command

**Problem:** LPC uses `manifest` for psionics (`lib/cmds/manifest.lpc`), C uses `use`. Players familiar with LPC MUDs will type `manifest`.

**Fix:** One line in `src/driver.c` command dispatch:

```c
if (strcmp(cmd, "use") == 0 || strcmp(cmd, "manifest") == 0) {
```

**Files to modify:**
- `src/driver.c:1907` - Add `manifest` to the strcmp

**Effort:** 1 line

---

### 1.7 Add `score` as alias for `stats`

**Problem:** LPC has `score.lpc` which aliases to `stats`. C only has `stats`.

**Fix:** One line in command dispatch:

```c
if (strcmp(cmd, "stats") == 0 || strcmp(cmd, "score") == 0) {
```

**Files to modify:**
- `src/driver.c` - Find `stats` handler, add `score` alias

**Effort:** 1 line

---

### 1.8 Add `examine` detail for equipped/carried items

**Problem:** `examine` exists in C but may not show item properties. LPC `examine.lpc` shows detailed object inspection including armor rating, damage, weight, properties.

**Fix:** Enhance existing `cmd_examine` to show item stats:

```c
// After basic item description
if (item->armor_rating > 0)
    send_to_player(sess, "Armor Rating: %d\n", item->armor_rating);
if (item->damage_dice > 0)
    send_to_player(sess, "Damage: %dd%d+%d\n", item->damage_dice, item->damage_sides, item->damage_bonus);
```

**Files to modify:**
- `src/driver.c` or wherever `examine` is implemented

**Effort:** ~15 lines

---

## Priority 2: Medium Effort

Systems that need moderate C code additions (50-200 lines each) to connect existing LPC data.

---

### 2.1 Spell effect system via LPC daemon

**Current State:**
- C `magic_start_casting()` (`src/magic.c:542-562`) begins multi-round casting
- C `magic_complete_cast()` (`src/magic.c:571-643`) calls LPC `/daemon/spells` via `obj_call_method()`
- LPC `lib/daemon/spells.lpc` has `cast_spell(spell_id, caster, target)` which calls `apply_effect()` on spell objects
- LPC has 19 spell objects with full `apply_effect()` implementations
- **But** `magic_spell_tick()` is never called (see Quick Win 1.1), so `magic_complete_cast()` never fires

**Fix sequence:**
1. Wire `magic_spell_tick()` (Quick Win 1.1) - enables casting countdown
2. Verify `magic_complete_cast()` LPC call works - test with `cast fireball`
3. Add target resolution in `magic_start_casting()` - currently ignores target_name
4. Map C spell IDs (0-33) to LPC spell IDs (by name) for effect delegation
5. Handle spell effect results back in C (damage application, buff tracking)

**Files to modify:**
- `src/magic.c:542-562` - Add target resolution via `find_player_by_name()`
- `src/magic.c:571-643` - Verify/fix LPC daemon call, add result handling
- `src/combat.c` - Wire magic_spell_tick() (prerequisite)

**LPC files involved:**
- `lib/daemon/spells.lpc:cast_spell()` - Central spell execution
- `lib/spells/level3/fireball.lpc:apply_effect()` - Example: 4d6 damage
- `lib/spells/level1/armor_of_ithan.lpc:apply_effect()` - Example: +100 SDC buff
- `lib/spells/level5/heal_wounds.lpc:apply_effect()` - Example: healing

**ID Mapping needed:**
| C Spell (magic.c) | C ID | LPC Spell (lib/spells/) | Match? |
|-------------------|------|------------------------|--------|
| Magic Armor | 0 | armor_of_ithan (level1) | Similar |
| Fireball | 8 | fireball (level3) | Match |
| Lightning Bolt | 9 | lightning_bolt (level6) | Match |
| Heal Wounds | 14 | heal_wounds (level5) | Match |

**Effort:** ~100 lines C + testing

---

### 2.2 Skill check integration for gameplay

**Current State:**
- C has `skill_check(int percentage)` (`src/skills.c:885-888`) - simple d100 roll
- C has 16 skills defined with base percentages and stat modifiers
- LPC has 10 skill files with detailed mechanics (`lib/skills/`)
- LPC daemon `lib/daemon/skills.lpc` has `attempt_skill()` with critical failure (96+)
- **No gameplay uses skill_check()** - it exists but nothing calls it

**Integrations to add:**
1. **Swimming** (see Quick Win 1.5) - first skill check use case
2. **First Aid** - `use first_aid` heals 1d6 SDC / 1d4 HP on skill success
3. **Climbing** - for vertical room transitions
4. **Tracking** - find hidden players/NPCs
5. **WP bonuses in combat** - WP skills give strike/parry bonuses

**Implementation:**

```c
// Generic skill use command
void cmd_use_skill(PlayerSession *sess, const char *skill_name) {
    int skill_id = skill_get_id_by_name(skill_name);
    if (skill_id < 0) { /* not found */ return; }

    // Find in player's skills
    PlayerSkill *ps = find_player_skill(sess, skill_id);
    if (!ps) { /* don't know this skill */ return; }

    int roll = (rand() % 100) + 1;
    if (roll >= 96) {
        // Critical failure
        send_to_player(sess, "Critical failure!\n");
    } else if (roll <= ps->percentage) {
        // Success - apply skill-specific effect
        apply_skill_effect(sess, skill_id, ps);
    } else {
        send_to_player(sess, "You fail the %s check.\n", skill_get_name(skill_id));
    }
    ps->uses++;
}
```

**Files to modify:**
- `src/skills.c` - Add `cmd_use_skill()`, `apply_skill_effect()`, `find_player_skill()`
- `src/skills.h` - Declare new functions
- `src/driver.c` - Add command routing for skill-specific commands
- `src/combat.c` - Wire WP bonuses into attack/parry calculations

**LPC reference:**
- `lib/std/skill.lpc:attempt()` - d100 with 96+ critical failure
- `lib/skills/medical/first_aid.lpc` - 1d6 SDC / 1d4 HP healing
- `lib/skills/weapons/wp_knife.lpc` - `query_strike_bonus(level)`, `query_parry_bonus(level)`

**Effort:** ~150 lines

---

### 2.3 Connect Staff Castle rooms to navigation

**Current State:**
- 16 LPC rooms in `lib/domains/staff_castle/room/` fully defined with exits
- New Camelot (36 rooms) connected via flex-exit system
- Staff Castle has **no C-side flex-exits** connecting it

**Fix:** Add flex-exits from existing C rooms to Staff Castle:

```c
// In room.c flex-exit definitions
// From New Camelot or starter area, add exit to staff castle
{"castle", "/domains/staff_castle/room/courtyard"}
```

**Files to modify:**
- `src/room.c` - Add flex-exit entries pointing to Staff Castle LPC paths
- `src/room.h` - If new room IDs needed for transition rooms

**LPC files involved:**
- `lib/domains/staff_castle/room/courtyard.lpc` - Entry point
- All 16 rooms have their own internal exit definitions

**Effort:** ~30 lines (exit definitions)

---

### 2.4 WP combat bonuses

**Current State:**
- C skills include WP Sword (ID 7), WP Rifle (ID 8), WP Pistol (ID 9)
- LPC `wp_knife.lpc` defines `query_strike_bonus(level)` = 1 + level/3
- C `combat_attack_melee()` (`src/combat.c:563-677`) does NOT check WP skills
- C combat uses flat modifiers, not skill-derived bonuses

**Fix:** In combat attack functions, check for WP skills and apply bonuses:

```c
// In combat_attack_melee() after calculating base to-hit
int wp_bonus = 0;
for (int i = 0; i < ch->num_skills; i++) {
    if (ch->skills[i].skill_id == WP_SWORD) {  // or appropriate WP
        wp_bonus = 1 + (ch->level / 3);  // matches LPC formula
        break;
    }
}
to_hit += wp_bonus;
```

**Files to modify:**
- `src/combat.c:563-677` - `combat_attack_melee()` add WP strike bonus
- `src/combat.c` - Parry function: add WP parry bonus
- `src/skills.h` - Add WP_ macros if not present

**LPC reference:** `lib/skills/weapons/wp_knife.lpc` formulas:
- Strike: `1 + level/3`
- Parry: `1 + level/4`
- Throw: `level/2`

**Effort:** ~40 lines

---

### 2.5 Help system - add missing topics

**Current State:**
- C help system fully works (`src/driver.c:1456-1587`)
- Reads `.txt` files from `lib/help/` subdirectories
- 25 help files exist covering basics, systems, meta, occs, social

**Missing topics to add:**
- `lib/help/basics/swimming.txt` - Swim mechanic (after 1.5)
- `lib/help/basics/meditation.txt` - Meditation for PPE/ISP recovery
- `lib/help/systems/casting.txt` - How spell casting works (multi-round)
- `lib/help/basics/introduction.txt` - Introduction/remember system

**Files to create:** 4 new `.txt` files in `lib/help/`

**Effort:** ~40 lines of help text per file

---

## Priority 3: Major Projects

Complex integrations requiring significant architecture changes (200+ lines, multi-file).

---

### 3.1 LPC/C unified command routing

**Current State:**
- C driver: 787-line strcmp chain in `execute_command()` (`src/driver.c:1243-4030`)
- LPC: 65+ commands in `lib/cmds/` with `/daemon/command.lpc` dispatcher (296 lines)
- Some commands exist in **both** (say, look, attack, who, etc.)
- C handles all input first; LPC commands only fire if C doesn't match AND VM routes it

**Architecture:**

```
Player Input
    |
    v
C execute_command()
    |
    +-- Movement (n/s/e/w) -> C room system (KEEP in C - performance)
    +-- Combat (attack/flee) -> C combat system (KEEP in C - real-time)
    +-- Core (look/say/emote) -> C handlers (KEEP in C - intro system)
    +-- Admin (promote/set/heal) -> C handlers (KEEP in C - security)
    |
    +-- FALLBACK: Try LPC command dispatcher
        |
        v
    LPC /daemon/command.lpc
        +-- cast -> /cmds/cast.lpc -> /daemon/spells.lpc
        +-- manifest -> /cmds/manifest.lpc -> /daemon/psionics.lpc
        +-- buy/sell -> /cmds/buy.lpc -> /std/shop.lpc
        +-- ... 65+ LPC commands
```

**Implementation:**

Replace the "Unknown command" handler at `src/driver.c:4024-4029`:

```c
/* Before "Unknown command" error, try LPC command dispatcher */
if (global_vm) {
    LPCObject *cmd_daemon = vm_find_object(global_vm, "/daemon/command");
    if (cmd_daemon) {
        VMValue args[2] = {
            vm_value_create_string(cmd),
            vm_value_create_string(args ? args : "")
        };
        VMValue result = obj_call_method(global_vm, cmd_daemon, "dispatch", args, 2);
        if (result.type == VALUE_INT && result.data.int_val == 1) {
            return vm_value_create_null();  // LPC handled it
        }
    }
}
/* If we get here, truly unknown */
```

**Files to modify:**
- `src/driver.c:4024-4029` - Add LPC fallback before error message
- `lib/daemon/command.lpc` - Ensure `dispatch(verb, args)` function exists and works

**Considerations:**
- C commands take priority (security, performance)
- LPC commands handle extended gameplay features
- Errors from LPC need to propagate back to player
- Session/player context needs to be available to LPC

**Effort:** ~100 lines C + extensive testing

---

### 3.2 Dynamic spell loading from LPC files

**Current State:**
- C has 34 hardcoded spells in `MAGIC_SPELLS[]` (`src/magic.c:16-332`)
- LPC has 19 spell files in `lib/spells/level1-6/` with `apply_effect()` methods
- C `magic_complete_cast()` already calls LPC daemon (partially working)
- Spell IDs don't match between C and LPC

**Goal:** Load spell definitions (name, PPE cost, level, casting time) from LPC files at boot, replacing or supplementing the hardcoded C array.

**Architecture:**

```
Boot sequence:
1. C driver starts, initializes VM
2. VM compiles /daemon/spells.lpc
3. Call spells daemon load_all_spells()
4. For each LPC spell, register in C-side spell table:
   - Read: spell_id, spell_name, ppe_cost, spell_level, casting_time
   - Store in dynamic MAGIC_SPELLS[] or parallel array
5. Runtime: cmd_cast -> C finds spell -> delegates to LPC apply_effect()
```

**Implementation approach:**

```c
// New function in magic.c
void magic_load_from_lpc(VirtualMachine *vm) {
    LPCObject *daemon = vm_find_object(vm, "/daemon/spells");
    if (!daemon) return;

    // Call daemon->query_all_spell_ids() to get list
    VMValue ids = obj_call_method(vm, daemon, "query_all_spell_ids", NULL, 0);

    // For each spell ID, query properties
    for (int i = 0; i < ids.array_size; i++) {
        const char *sid = ids.data.array[i].data.string;
        // Get spell object, read properties
        // Register in C spell table
    }
}
```

**Files to modify:**
- `src/magic.c` - Add `magic_load_from_lpc()`, modify `magic_init()`
- `src/magic.h` - Declare new function
- `src/driver.c` - Call `magic_load_from_lpc()` after VM initialization
- `lib/daemon/spells.lpc` - Verify `query_all_spell_ids()` and per-spell queries work

**Prerequisite:** VM must reliably compile and execute LPC daemon methods at boot.

**Effort:** ~200 lines C + LPC testing

---

### 3.3 Dynamic psionic loading from LPC files

**Identical pattern to 3.2 but for psionics.**

**Current State:**
- C has 25 hardcoded powers in `PSION_POWERS[]` (`src/psionics.c:13-198`)
- LPC has 14 power files in `lib/psionics/` with `apply_effect()` methods
- C `psionics_activate_power()` is a stub (no effects)

**Files to modify:**
- `src/psionics.c` - Add `psionics_load_from_lpc()`, add effect delegation to LPC
- `src/psionics.h` - Declare new function
- `src/driver.c` - Call after VM initialization

**Effort:** ~200 lines C + LPC testing

---

### 3.4 NPC system bridge

**Current State:**
- LPC NPCs (Moxim, Grok, Spike, test_goblin) have full behavior: `add_action()`, `heart_beat()`, dialogue, combat stats
- C rooms can reference LPC room files but NPCs don't spawn or interact
- No C-side NPC heartbeat system exists

**Goal:** Allow LPC-defined NPCs to exist in rooms, respond to player commands, and run heartbeats.

**Architecture:**

```
C Room with LPC path
    |
    +-- On room load: scan LPC room for NPC spawns (create() calls clone_object())
    +-- Store NPC references in room's item list
    +-- On player command: check NPC add_actions before "unknown command"
    +-- On heartbeat: call NPC heart_beat() every N seconds
```

**Files to modify:**
- `src/room.c` - NPC spawn on room entry, NPC interaction hooks
- `src/driver.c` - Route commands through NPC `add_action` handlers
- `src/combat.c` - NPC combat integration (already has mob support?)

**LPC files involved:**
- `lib/domains/start/npc/moxim.lpc` - Rift travel NPC
- `lib/domains/start/npcs/grok_merchant.lpc` - Merchant with shop
- `lib/domains/start/npc/test_goblin.lpc` - Combat test mob

**Effort:** ~400 lines (significant VM integration work)

---

### 3.5 Shop system activation

**Current State:**
- LPC shop system: `/std/shop.lpc` base class, `buy`/`sell`/`list` commands
- `lib/domains/start/shop_general.lpc` inherits shop with weapons, armor, supplies
- `lib/cmds/buy.lpc`, `lib/cmds/sell.lpc` exist
- C has `credits` system (1000 starting, persists in save/load)
- **No buy/sell commands in C driver**

**Prerequisite:** NPC system (3.4) or simplified approach.

**Simplified approach** (no NPC needed):

```c
// Add buy/sell commands that check if current room is a shop
if (strcmp(cmd, "buy") == 0 || strcmp(cmd, "sell") == 0 || strcmp(cmd, "list") == 0) {
    // Check room has "shop" property or is designated shop room
    // Load shop inventory from LPC shop file or C-defined item templates
    // Handle credit transactions
}
```

**Files to modify:**
- `src/driver.c` - Add buy/sell/list commands
- `src/item.c` - Item creation from shop inventory
- `src/room.c` or `src/room.h` - Shop room flag

**Effort:** ~200 lines

---

## Implementation Order

Recommended sequence respecting dependencies:

```
Week 1: Quick Wins (all independent, can be done in parallel)
  [1.1] Wire magic_spell_tick()        ~5 lines
  [1.2] Wire psionics_power_tick()     ~5 lines
  [1.3] Wire meditation ticks          ~8 lines
  [1.6] Add "manifest" alias           ~1 line
  [1.7] Add "score" alias              ~1 line

Week 2: Quick Wins (gameplay features)
  [1.4] Psionic power effects          ~80 lines
  [1.5] Swim command                   ~40 lines
  [1.8] Enhanced examine               ~15 lines

Week 3: Medium Effort
  [2.1] Spell effect system via LPC    ~100 lines
  [2.4] WP combat bonuses              ~40 lines

Week 4: Medium Effort
  [2.2] Skill check integration        ~150 lines
  [2.3] Staff Castle room connections  ~30 lines
  [2.5] Help topics                    ~160 lines text

Week 5+: Major Projects (sequential)
  [3.1] LPC/C command routing          ~100 lines + testing
  [3.2] Dynamic spell loading          ~200 lines
  [3.3] Dynamic psionic loading        ~200 lines
  [3.5] Shop system                    ~200 lines
  [3.4] NPC system bridge              ~400 lines (last - most complex)
```

---

## File Reference

### C Source Files (modify)

| File | Functions to Add/Modify |
|------|------------------------|
| `src/combat.c:465` | Add magic/psionics/meditation tick calls |
| `src/driver.c:1243-4030` | Add command aliases, swim, LPC fallback |
| `src/driver.c:4024` | Add LPC command dispatcher fallback |
| `src/magic.c:542` | Target resolution in start_casting |
| `src/magic.c:725` | magic_spell_tick() - already exists, just wire it |
| `src/magic.c` | New: magic_load_from_lpc() |
| `src/psionics.c:414` | Add effect switch in activate_power |
| `src/psionics.c:437` | psionics_power_tick() - already exists, just wire it |
| `src/skills.c:885` | skill_check() exists, add cmd_use_skill() |
| `src/room.c` | Flex-exits for Staff Castle, swim room flags |

### LPC Files (reference/verify)

| File | Integration Point |
|------|------------------|
| `lib/daemon/spells.lpc` | C calls cast_spell() via obj_call_method() |
| `lib/daemon/psionics.lpc` | C calls activate_power() for effect delegation |
| `lib/daemon/skills.lpc` | C references skill formulas |
| `lib/daemon/command.lpc` | C fallback dispatcher target |
| `lib/spells/level*/` | 19 spell effect implementations |
| `lib/psionics/*/` | 14 power effect implementations |
| `lib/skills/*/` | 10 skill mechanic definitions |
| `lib/domains/staff_castle/room/` | 16 rooms to connect |
| `lib/domains/start/lake_shore.lpc` | Swimming mechanic reference |
| `lib/help/` | 25 help topics (add 4 more) |

### Key Function Signatures

```c
// Already exist - just need wiring:
void magic_spell_tick(PlayerSession *sess);           // magic.c:725
void magic_meditate_tick(PlayerSession *sess);        // magic.c:747
void psionics_power_tick(PlayerSession *sess);        // psionics.c:437
void psionics_meditate_tick(PlayerSession *sess);     // psionics.c:444
int  skill_check(int skill_percentage);               // skills.c:885
void magic_complete_cast(PlayerSession *sess);        // magic.c:571

// Need to create:
void cmd_swim(PlayerSession *sess, const char *args);
void cmd_use_skill(PlayerSession *sess, const char *args);
void apply_skill_effect(PlayerSession *sess, int skill_id, PlayerSkill *ps);
void magic_load_from_lpc(VirtualMachine *vm);
void psionics_load_from_lpc(VirtualMachine *vm);
```
