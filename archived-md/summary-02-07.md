# AetherMUD Development Summary - February 7, 2026

## What Was Done

### Real-Time Combat System Conversion

Converted the combat system from turn-based (players manually type strike/shoot each turn) to real-time heartbeat-driven (attacks fire automatically every 2 seconds).

#### Timing Model
- **Heartbeat interval:** 2 seconds (fired from main select() loop)
- **Melee round:** 8 heartbeats = 16 seconds (close to Palladium 15-second melee round)
- **Attack distribution:** Attacks evenly spaced across the 8-beat round
  - 2 attacks/round: fire on beats 0,4 (every 8 seconds)
  - 3 attacks/round: fire on beats 0,3,5 (every ~5 seconds)
  - 4 attacks/round: fire on beats 0,2,4,6 (every 4 seconds)
- **Defense:** Auto-parry and auto-dodge fire automatically on each incoming attack
- **Parries per round:** Reset at start of each melee round

### 26 New Player Commands Added

**Combat Commands:**
| Command | Description |
|---------|-------------|
| `kill <target>` | Alias for attack - initiate real-time combat |
| `stop` | Disengage from combat |
| `assist <player>` | Join combat targeting their target |
| `autododge` | Toggle auto-dodge on/off |
| `autoparry` | Toggle auto-parry on/off |
| `wimpy <percent>` | Set auto-flee HP threshold (0=off, max 90) |
| `rest` | Sit down, bonus HP/SDC regen per tick |
| `wake` / `stand` | Stand up from resting |

**Social/RP Commands:**
| Command | Description |
|---------|-------------|
| `reply <msg>` | Reply to last tell sender |
| `pemote <action>` | Possessive emote: "Bob's eyes widen" |
| `converse` | Toggle conversation mode (all input becomes "say", "." to exit) |
| `think <thought>` | Display internal thought bubble |
| `introduce <player>` / `greet` | Introduce yourself to someone in room |
| `forget <player>` | Forget an introduction |
| `remember` | List remembered introductions |

**UI/Settings Commands:**
| Command | Description |
|---------|-------------|
| `brief` | Toggle brief room descriptions |
| `color` / `ansi` | Toggle ANSI color output |
| `password <old> <new>` | Change password |
| `echo <text>` | Echo text back to self |
| `view <target>` | Alias for examine |
| `map` | Show basic ASCII area map |
| `position` | Show current position (standing/resting) |

### Files Modified (6 files + 1 file in chargen)

| File | What Changed |
|------|-------------|
| `src/chargen.h` | Added 7 combat fields to Character struct: `attacks_per_round`, `parries_per_round`, `racial_auto_parry`, `racial_auto_dodge`, `auto_parry_enabled`, `auto_dodge_enabled`, `wimpy_threshold` |
| `src/session_internal.h` | Added 7 session state fields: `combat_target`, `in_combat`, `last_tell_from[64]`, `is_brief`, `is_color`, `is_resting`, `converse_mode` |
| `src/combat.h` | Complete restructure for real-time: removed turn-based fields (initiative, actions_remaining, is_defending, current), added tick-based fields (tick_in_round, attacks/parries_used_this_round), linked list `next` pointer for concurrent combats, new API functions (combat_tick, combat_engage, combat_disengage, combat_regen_tick), defined MELEE_ROUND_TICKS=8 and COMBAT_TICK_SECS=2 |
| `src/combat.c` | Complete rewrite (~600 lines): heartbeat-driven auto-attack with even distribution algorithm, auto-parry/auto-dodge defense system, wimpy auto-flee, HP/SDC regen tick for resting players, concurrent combat support via linked list, combat_engage() handles joining existing combats or creating new ones, combat_disengage() cleans up and ends combat if <2 remain |
| `src/driver.c` | Combat heartbeat timer in main select() loop (2s interval), combat cleanup on player disconnect (free_session), 26 new command handlers in execute_command(), updated help text with all new commands, converse mode interception in process_playing_state(), `sessions[]` changed from static to non-static (extern access from combat.c), `find_player_by_name()` changed from static to non-static, tell command now tracks `last_tell_from` for reply, `is_color` initialized to 1 in init_session() |
| `src/race_loader.c` | Extended `load_race_data()` to parse `set_attacks_per_round()`, `set_parries_per_round()`, `set_auto_parry()`, `set_auto_dodge()` from race LPC files. Added +1 attack bonus at levels 5, 10, 15 in `check_and_apply_level_up()` |
| `src/chargen.c` | Rewrote `cmd_attack()` to find target in room and call `combat_engage()`. Simplified `cmd_strike()`/`cmd_shoot()`/`cmd_dodge()` to inform player combat is automatic. Rewrote `cmd_flee()` with PP check + `combat_disengage()`. Added combat defaults initialization in `chargen_complete()`. Added `#include <strings.h>`, extern declarations for `find_player_by_name()` and `cmd_move()` |

### Build Result
- **29 files compiled, 0 errors, 51 warnings** (down from 52 before)
- Binary: `build/driver` (1.0M ELF)

---

## What's Next

### Testing Priority (needs a running MUD instance)
1. **Real-time combat test:** Connect two players, `attack <player>`, verify auto-attacks fire every 2 seconds, verify attacks per round matches race data
2. **Defense test:** Verify auto-parry and auto-dodge trigger automatically on incoming attacks
3. **Combat commands:** Test `stop`, `flee`, `assist`, `wimpy 20`, `autododge`, `autoparry`
4. **Resting:** Test `rest` -> verify regen messages appear -> `stand` to stop
5. **Social commands:** Test `reply`, `pemote`, `converse`, `think`, `introduce`/`forget`/`remember`
6. **Settings:** Test `brief`, `color`, `map`, `password`
7. **Edge cases:** Player disconnects mid-combat (cleanup), player dies in combat (XP award + combat end), godmode immunity, peace command ends real-time combat

### Known Items Still TODO
- **NPC combat:** Currently only player-vs-player combat works. Need NPC entities that can be attacked
- **Brief mode:** The `is_brief` flag is tracked but `cmd_look()` in room.c doesn't check it yet - needs a small update to skip long descriptions when `session->is_brief == 1`
- **Color stripping:** The `is_color` flag is tracked but `send_to_player()` doesn't strip ANSI codes when color is off - needs a filter pass
- **Save/load combat fields:** The new combat attributes (attacks_per_round, auto_parry_enabled, etc.) are not yet persisted in save files - they get reloaded from race data on login, but player toggles (auto_parry_enabled, wimpy_threshold) are lost on logout
- **Race file combat data:** Most race LPC files don't have `set_attacks_per_round()` etc. yet - defaults (2 attacks, 2 parries) are used. Could add these to key race files
- **Movement during combat:** Players can currently walk away during combat without using flee. Could add a check in `cmd_move()` to require `flee` first
- **Prompt customization:** The plan mentioned `prompt [format]` and `sbar` commands but these weren't implemented (low priority)
- **Score command:** Currently aliased to `stats`. Could be enhanced with more detail (combat stats, attacks/round, etc.)
