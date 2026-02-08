# AMLP Mudlib Development - Complete TODOs and Placeholders

## MISSION
Review and complete all TODOs, placeholders, stub implementations, and incomplete features in the AMLP mudlib at `/home/thurtea/amlp-aethermud/lib/`. Use the working Dead Souls 3.8.2 mudlib as a reference for implementation patterns and best practices.

## CURRENT STATE

### Working Systems
✅ **AMLP Driver**: Custom C-based LPC driver running on ports 6668 (telnet) / 6669 (websocket)
✅ **Dead Souls 3.8.2**: Reference mudlib running on port 6666
✅ **Both operational**: Can connect and test features in real-time

### AMLP Mudlib Structure
```
/home/thurtea/amlp-aethermud/lib/
├── clone/          - Cloneable objects
├── cmds/           - 84 player commands
├── daemon/         - System daemons
├── data/           - Game data files
├── domains/        - Game world areas
├── include/        - Header files
├── languages/      - Language definitions
├── log/            - Runtime logs
├── objects/        - Item definitions
├── occs/           - 36 occupation/class files
├── psionics/       - 14 psionic powers
├── races/          - 87 race definitions
├── save/           - Player save files
├── secure/         - Master object, simul_efun
├── single/         - Singleton objects
├── skills/         - Skill system
├── spells/         - 19 spell definitions
├── std/            - Standard inherited objects
├── test/           - Test files
└── tools/          - Development tools
```

### Reference Mudlib (Dead Souls 3.8.2)
```
/home/thurtea/amlp-aethermud/mud-references/deadsouls/ds3.8.2/lib/
├── cmds/           - Command implementations
├── daemon/         - Daemons (login, combat, etc.)
├── domains/        - Game areas
├── include/        - Header files
├── obj/            - Objects
├── std/            - Standard objects
├── secure/         - Master, simul_efun
└── verbs/          - Verb system
```

## YOUR TASKS

### Task 1: Comprehensive Code Audit

Scan all `.lpc` and `.c` files in `/home/thurtea/amlp-aethermud/lib/` for:

**Search Patterns:**
```bash
# TODOs and placeholders
grep -r "TODO\|FIXME\|XXX\|HACK\|PLACEHOLDER" lib/ --include="*.lpc" --include="*.c"

# Stub functions (empty or minimal implementations)
grep -r "return 0;\|return \"\";\|return ({\});\|// stub" lib/ --include="*.lpc" --include="*.c"

# Incomplete error handling
grep -r "// error\|/* error\|NEEDS IMPLEMENTATION" lib/ --include="*.lpc" --include="*.c"

# Commented out code that might need completion
grep -r "^[[:space:]]*//.*function\|^[[:space:]]*/\*.*function" lib/ --include="*.lpc" --include="*.c"
```

**Categorize findings by:**
1. Critical (blocks core functionality)
2. High (affects major features)
3. Medium (missing convenience features)
4. Low (nice-to-have enhancements)

### Task 2: Compare with Dead Souls Reference

For each major subsystem, compare AMLP implementation with Dead Souls:

**Key Areas to Compare:**
```bash
# Commands - check implementation completeness
diff -r lib/cmds/ mud-references/deadsouls/ds3.8.2/lib/cmds/ | grep "Only in"

# Daemons - ensure all critical daemons exist
diff -r lib/daemon/ mud-references/deadsouls/ds3.8.2/lib/daemon/ | grep "Only in"

# Standard objects - verify base object functionality
diff lib/std/ mud-references/deadsouls/ds3.8.2/lib/std/ | grep "Only in"

# Master object - check for missing functions
diff lib/secure/master.lpc mud-references/deadsouls/ds3.8.2/lib/secure/master.c
```

**For each difference, determine:**
- Is the Dead Souls feature needed in AMLP?
- Is there an AMLP equivalent?
- Should it be implemented?

### Task 3: Verify Critical Systems

Test and complete these core systems:

#### A. Master Object (`lib/secure/master.lpc`)
**Required Functions (verify all exist and work):**
- `create()` - Initialization
- `connect()` - Handle new connections
- `compile_object()` - Compile LPC files
- `log_error()` - Error logging
- `get_root_uid()` - Security
- `valid_read()` / `valid_write()` - File security
- `object_destroyed()` - Cleanup
- `preload()` - Preload critical objects

**Test:**
```bash
# Connect and verify login works
telnet localhost 6668
# Should see login prompt
```

#### B. Login Daemon (`lib/daemon/login_d.lpc`)
**Verify:**
- Character creation flow
- Password handling (encryption)
- Race selection
- Class/occupation selection
- Starting equipment
- Initial room placement

**Test in-game:**
```
# Create new character
# Check all prompts work
# Verify character saves properly
```

#### C. Player Object (`lib/std/player.lpc`)
**Required Functionality:**
- HP/MP/SP management
- Inventory system
- Combat participation
- Skill usage
- Spell casting
- Experience/leveling
- Save/restore

**Test commands:**
```
look
inventory
stats
skills
who
```

#### D. Living Object (`lib/std/living.lpc`)
**Must support:**
- HP/damage system
- Combat actions (attack, defend)
- Movement
- Communication (say, tell, emote)
- Status effects

#### E. Room Object (`lib/std/room.lpc`)
**Must support:**
- Descriptions (long/short)
- Exits
- Items in room
- NPCs in room
- Environmental effects
- Light levels

**Test:**
```
look
exits
north/south/east/west (movement)
```

### Task 4: Complete Command Implementations

Review all 84 commands in `lib/cmds/` and ensure they:

**Essential Commands (Priority 1):**
- `look.lpc` - Full room/object descriptions
- `inventory.lpc` (or `i.lpc`) - Show inventory
- `get.lpc` / `take.lpc` - Pick up items
- `drop.lpc` - Drop items
- `say.lpc` - Communication
- `tell.lpc` - Private messages
- `who.lpc` - Player list
- `save.lpc` - Save character
- `quit.lpc` - Exit game
- `help.lpc` - Help system

**Combat Commands (Priority 2):**
- `kill.lpc` - Initiate combat
- `flee.lpc` - Escape combat
- `cast.lpc` - Cast spells
- `use.lpc` - Use skills/items

**Social Commands (Priority 3):**
- `emote.lpc` - Custom actions
- `shout.lpc` - Global communication
- `whisper.lpc` - Quiet communication

**For each command:**
1. Check if it has a working implementation
2. Verify error handling
3. Test with actual use
4. Compare with Dead Souls equivalent if needed

### Task 5: Complete Race Implementations

Review all 87 races in `lib/races/` and ensure each has:

**Required Properties:**
```lpc
// In each race file
string query_race_name();         // e.g., "human", "elf"
mapping query_base_stats();       // Starting stats
string *query_languages();        // Known languages
int query_body_type();            // Body configuration
mapping query_resistance();       // Damage resistances
string query_description();       // Race description
```

**Test:**
- Create character with each major race
- Verify stats are applied correctly
- Check special abilities work

### Task 6: Complete Occupation/Class System

Review all 36 classes in `lib/occs/` and ensure:

**Required Functions:**
```lpc
string query_occupation_name();   // Class name
string *query_skills();           // Available skills
string *query_spells();           // Available spells (if caster)
int query_hp_bonus();             // HP per level
int query_mp_bonus();             // MP per level
mapping query_stat_requirements();// Minimum stats
```

**Test:**
- Create characters with different classes
- Verify class-specific abilities
- Check skill/spell progression

### Task 7: Complete Spell System

Review 19 spells in `lib/spells/` and ensure:

**Each spell needs:**
```lpc
void create();                    // Initialize
int cast(object caster, mixed target);
string query_spell_name();
int query_mp_cost();
int query_spell_level();
string query_description();
```

**Test:**
- Cast each spell type
- Verify MP costs
- Check targeting works
- Confirm effects apply

### Task 8: Complete Psionic System

Review 14 psionics in `lib/psionics/` similarly to spells.

### Task 9: Fill Placeholder Content

**Common Placeholder Patterns to Replace:**

```lpc
// BEFORE (placeholder)
string query_description() {
    return "TODO: Add description";
}

// AFTER (proper implementation)
string query_description() {
    return "A detailed and evocative description of the object/place/creature.";
}
```

**Areas likely to have placeholders:**
- Room descriptions in `lib/domains/`
- Object descriptions in `lib/objects/`
- Race descriptions in `lib/races/`
- Help text in commands

### Task 10: Dead Souls Reference Analysis

**For uncertain implementations, check Dead Souls:**

```bash
# Example: How does Dead Souls implement combat?
grep -r "combat" mud-references/deadsouls/ds3.8.2/lib/daemon/ -A 10

# Example: How are spells cast?
grep -r "cast_spell\|do_cast" mud-references/deadsouls/ds3.8.2/lib/ -A 5

# Example: How does movement work?
grep -r "cmd_move\|do_move" mud-references/deadsouls/ds3.8.2/lib/cmds/ -A 10
```

**Key Dead Souls files to study:**
- `mud-references/deadsouls/ds3.8.2/lib/secure/master.c` - Master object
- `mud-references/deadsouls/ds3.8.2/lib/std/body/` - Body system
- `mud-references/deadsouls/ds3.8.2/lib/daemon/command_d.c` - Command daemon
- `mud-references/deadsouls/ds3.8.2/lib/daemon/login_d.c` - Login flow

### Task 11: Testing Checklist

**After completing implementations, test:**

```bash
# Connect to AMLP
telnet localhost 6668

# Test flow:
1. Create new character
2. Choose race (try different races)
3. Choose class (try different classes)
4. Enter game
5. Test movement (n, s, e, w, up, down)
6. Test look, inventory, stats
7. Test get/drop items
8. Test combat (if NPCs available)
9. Test spells/psionics
10. Test social commands (say, tell, who)
11. Test save
12. Test quit and reconnect
13. Verify character restored correctly
```

### Task 12: Documentation

**For each completed system, document:**

```markdown
# System: [Name]
## Status: ✅ Complete / ⚠️ Partial / ❌ Incomplete

## Files Modified:
- lib/path/to/file.lpc

## Changes Made:
- Implemented [feature]
- Fixed [bug]
- Added [functionality]

## Testing:
- ✅ Tested: [what you tested]
- Result: [pass/fail]

## Known Issues:
- [any remaining issues]

## Reference Used:
- Dead Souls file: [path if applicable]
```

## DELIVERABLES

### 1. Audit Report
Create: `/home/thurtea/amlp-aethermud/docs/MUDLIB_AUDIT_REPORT.md`

**Contents:**
- Summary of all TODOs/placeholders found
- Categorization by priority
- Comparison with Dead Souls
- Missing critical features
- Recommended implementation order

### 2. Implementation Log
Create: `/home/thurtea/amlp-aethermud/docs/IMPLEMENTATION_LOG.md`

**Track:**
- What was completed
- Files modified
- Testing results
- Issues encountered
- Dead Souls references used

### 3. Testing Report
Create: `/home/thurtea/amlp-aethermud/docs/TESTING_REPORT.md`

**Include:**
- Feature test results
- Command verification
- Race/class testing
- Combat system status
- Spell/psionic functionality
- Any bugs found

### 4. Updated Code
- All placeholder implementations completed
- TODOs resolved or documented as future work
- Stub functions filled in
- Missing features added

## GUIDELINES

### Code Style
Match existing AMLP style:
```lpc
// Function headers
void create() {
    ::create();
    // implementation
}

// Comments
// Single line comments for brief explanations
/* Multi-line comments for
   complex explanations */

// Naming
query_*     // Getters
set_*       // Setters
do_*        // Actions
cmd_*       // Commands
```

### Testing Approach
1. Test each change in-game immediately
2. Keep both MUDs running (Dead Souls for reference)
3. Document any driver-specific issues
4. Note incompatibilities with standard LPC

### Dead Souls Reference Usage
- Use Dead Souls as a **guide**, not copy-paste
- Adapt patterns to AMLP's architecture
- Respect that AMLP uses custom driver (not FluffOS)
- Note differences in efuns/systems

### Priority Order
1. **Critical**: Master object, login, player, living, room
2. **High**: Essential commands, combat, movement
3. **Medium**: Spells, psionics, full command set
4. **Low**: Polish, descriptions, edge cases

## IMPORTANT NOTES

### Driver Differences
AMLP uses a **custom driver**, not FluffOS:
- Some efuns may differ
- Check driver source in `/home/thurtea/amlp-aethermud/src/` for available efuns
- Test all efun calls in-game
- Document any missing efuns

### Don't Break Working Features
- Test before and after changes
- Keep backups of working files
- If something works, understand why before changing

### Live Testing
You have **two running MUDs** for testing:
```bash
# Test in AMLP
telnet localhost 6668

# Compare with Dead Souls
telnet localhost 6666

# Check process status
ps aux | grep driver

# View logs
tail -f /home/thurtea/amlp-aethermud/lib/log/*.log
```

## SUCCESS CRITERIA

The mudlib is complete when:

1. ✅ No critical TODOs remaining
2. ✅ All essential commands work
3. ✅ Character creation fully functional
4. ✅ Combat system operational
5. ✅ Spell system operational
6. ✅ Movement and rooms work
7. ✅ All races functional
8. ✅ All classes functional
9. ✅ Save/restore working
10. ✅ No placeholder content in core systems
11. ✅ Testing report shows all critical features pass
12. ✅ Documentation complete

## WORKFLOW SUGGESTION

```bash
# 1. Start with audit
cd /home/thurtea/amlp-aethermud
grep -r "TODO" lib/ --include="*.lpc" > docs/todos.txt

# 2. Test current state
telnet localhost 6668
# Try all basic commands, note what breaks

# 3. Fix critical issues first
# Start with master.lpc, login_d.lpc, player.lpc

# 4. Test after each fix
# Reconnect and verify the fix works

# 5. Move to next priority
# Commands → Combat → Spells → etc.

# 6. Document everything
# Keep implementation log updated

# 7. Final testing
# Complete test checklist
# Create testing report
```

## EXAMPLE TASK

**Example: Complete the "look" command**

```bash
# 1. Find the file
cat lib/cmds/look.lpc

# 2. Check Dead Souls implementation
cat mud-references/deadsouls/ds3.8.2/lib/cmds/look.c

# 3. Identify missing features
# Compare AMLP vs Dead Souls

# 4. Implement missing parts
vim lib/cmds/look.lpc

# 5. Test in-game
telnet localhost 6668
# Login and test: look, look at object, look player

# 6. Document
echo "- Completed look command" >> docs/IMPLEMENTATION_LOG.md
```

---

**Begin with Task 1 (Comprehensive Code Audit) and work through systematically. Test frequently. Document everything. Use Dead Souls as a reference but adapt to AMLP's architecture.**

**Current State**: Both MUDs operational, ready for development
**Target**: Production-ready AMLP mudlib with all core features complete
