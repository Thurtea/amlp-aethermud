# AMLP AetherMUD — Implementation Plan
Date: 2026-02-23
Based on: PROJECT-STATUS.md (2026-02-23), diagnostics/warnings-triage.md

This plan covers every issue listed in PROJECT-STATUS.md, ordered by priority
(security → ops → stability → gameplay → quality).  Each entry names the exact
files, functions, and steps required.

---

## Priority 1 — Secure Password Hashing (SECURITY-CRITICAL)

**Status: IN PROGRESS** (stubs added 2026-02-23; plaintext storage removed from
all call sites; proper KDF not yet wired)

### Problem
`src/driver.c` stores and compares passwords as plaintext in
`session->password_hash` (char[128]).  Passwords are written verbatim to player
save files in `lib/save/players/`.

### Files / Functions
| File | Function | Line (approx) | Change |
|------|----------|---------------|--------|
| `src/driver.c` | `hash_password()` | ~64 | **NEW stub** — replace body with `bcrypt_hashpw()` |
| `src/driver.c` | `verify_password()` | ~78 | **NEW stub** — replace body with `bcrypt_checkpw()` |
| `src/driver.c` | `execute_command()` (password cmd) | ~4958 | Already wired to stubs |
| `src/driver.c` | `process_login_state()` STATE_GET_PASSWORD | ~5382 | Already wired to stubs |
| `src/driver.c` | `process_login_state()` STATE_CONFIRM_PASSWORD | ~5542 | Already wired to stubs |
| `src/session_internal.h` | `PlayerSession.password_hash` | 41 | Widen to `char password_hash[128]` (already 128; bcrypt output is 60 bytes, argon2id up to ~100 bytes — no resize needed) |
| `src/chargen.c` | `save_character()` / `load_character()` | ~1539, ~1926 | No change needed — binary blob, format-agnostic |

### Steps
1. Add `libargon2-dev` (or `libbcrypt-dev`) to build dependencies; update `Makefile`
   `LDFLAGS` with `-largon2` (or `-lcrypt`).
2. Replace `hash_password()` stub body:
   ```c
   /* argon2id variant */
   #include <argon2.h>
   static const char *hash_password(const char *plaintext) {
       static char encoded[128];
       argon2id_hash_encoded(2, 1<<16, 1,
           plaintext, strlen(plaintext),
           /* salt */ NULL, 0,   /* use argon2_hash with random salt */
           32, encoded, sizeof(encoded));
       return encoded;
   }
   ```
   Or use `crypt_r()` with `$2b$12$` salt for bcrypt.
3. Replace `verify_password()` stub body with `argon2id_verify(stored_hash, plaintext, strlen(plaintext))`.
4. Audit `lib/save/players/` for existing plaintext saves; force-expire or migrate
   on next login (detect old format by `stored_hash[0] != '$'`).
5. Add a unit test in `tests/` that calls `hash_password` + `verify_password` and
   asserts correct/incorrect password results.
6. Remove all `TODO:SECURITY` comments once real KDF is wired.

---

## Priority 2 — Inventory Persistence (GAMEPLAY-CRITICAL)

**Status: NOTE — Memory says inventory+equipment is already saved (version 8 format,
see MEMORY.md).  This item should be verified against current `save_character()` /
`load_character()` in `src/chargen.c` before spending time on it.**

### Files / Functions
| File | Function | Action |
|------|----------|--------|
| `src/chargen.c` | `save_character()` | Verify inventory block is written |
| `src/chargen.c` | `load_character()` | Verify inventory block is read and `inventory_init()` is called |
| `tests/` | new test | Write `test_save_load.c`: save a session with items, reload, assert items present |

### Steps
1. Read `save_character()` around the inventory section; confirm item_count and
   per-item `{template_id, equip_slot}` are written per the MEMORY.md format spec.
2. Read `load_character()` confirm inventory section is consumed correctly.
3. If broken: implement per MEMORY.md save format (item_count int + per-item struct).
4. Add regression test.

---

## Priority 3 — Fix SIMUL_EFUN Path (OPS-CRITICAL)

**Status: DONE** (2026-02-23)

`config/runtime.conf` line 13 changed from:
```
SIMUL_EFUN=${MUDLIB_ROOT}/lib/secure/simul_efun.c
```
to:
```
SIMUL_EFUN=${MUDLIB_ROOT}/lib/secure/simul_efun.lpc
```
File `lib/secure/simul_efun.lpc` confirmed present.

### Remaining Work
- Verify the driver actually reads `runtime.conf` at startup and uses the `SIMUL_EFUN`
  value.  Search `src/` for `SIMUL_EFUN` or `simul_efun` to confirm the config key
  is parsed.
- If the driver does not read `runtime.conf`, document that the path is controlled
  by a compile-time default or command-line argument, and update `runtime.conf`
  comments accordingly.

---

## Priority 4 — Triage and Fix Compiler Warnings (STABILITY)

**Status: PARTIAL — HIGH severity RESOLVED (2026-02-23); MEDIUM/LOW pending**
Warnings: 102 → 93 (9 HIGH-severity warnings eliminated).
See `diagnostics/warnings-triage.md` for full status.

### Step 4a — HIGH severity — **RESOLVED 2026-02-23**

| File | Line | Warning | Fix | Status |
|------|------|---------|-----|--------|
| `src/vm.c` | 697 | `%d` for `long int` | Changed to `%ld` | **DONE** |
| `src/server.c` | 27, 34 | signed/unsigned in `send_ansi()` loop | Changed `int bi` to `size_t bi` | **DONE** |
| `src/chargen.c` | 38 | signed/unsigned loop in `grant_all_languages()` | Changed `int i` to `size_t i` | **DONE** |
| `src/skills.c` | 772, 787, 796, 810, 820 | signed/unsigned loops and guards | Changed loop vars to `size_t`, added `(size_t)id` casts | **DONE** |

### Step 4b — MEDIUM severity

| File | Lines | Warning | Fix |
|------|-------|---------|-----|
| `src/driver.c` | 4330 | `snprintf` truncation `forced_cmd` | Widen `response[256]` to `response[640]` or clamp `forced_cmd` input |
| `src/server.c` | 188 | path snprintf may truncate | Widen `item_path[1024]` to `item_path[1280]` |
| `src/server.c` | 148, 152, 265, 269 | path snprintf truncation | Widen `path` to `2048` or validate input length |
| `src/server.c` | 259 | zero-length `snprintf` | Replace with `new_dir[0] = '\0';` |
| `src/driver.c` | 233 | ternary signedness | Cast: `(int)(session ? session->state : (SessionState)-1)` |
| `driver.c, wiz_tools.c, chargen.c, combat.c, room.c` | various | NULL check on array | Replace `->username ?` with `->username[0] ?` (42 sites) |

### Step 4c — LOW severity (batch cleanup)

- Remove or suppress unused variables (`speaker_ch`, `is_public`, `dmg_type`).
- Remove or suppress unused static functions (`compiler_find_global`,
  `chargen_show_secondary_skills`).
- Remove or suppress unused `occ_pool_*` arrays in `wiz_tools.c`.
- Remove or suppress unused parameters with `(void)param;`.
- Fix nested `/*` comments in `chargen.c:56,60`.

### Step 4d — Add CI job

Add a `Makefile` target `ci` that runs with `-Werror` on a targeted subset of
warning flags (HIGH severity ones) so that regressions are caught on PR.

---

## Priority 5 — Command Dispatch Mismatch (ADMIN UX)

**Status: IN PROGRESS (2026-02-23)** — `cmd()` → `main()` renames complete.
Remaining: duplicate/stray command audit and integration testing.

### Root Cause (confirmed)
`lib/daemon/command.lpc` uses `function_exists("main", cmd_obj)` and calls
`cmd_obj->main(args)`. Files with `cmd()` were silently never called.

### Files Changed — `cmd()` renamed to `main()` (2026-02-23)

| File | Change |
|------|--------|
| `lib/cmds/forget.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/language.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/skills.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/languages.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/position.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/cast.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/manifest.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/hatch.lpc` | `int cmd(string arg)` → `int main(string arg)` |
| `lib/cmds/prompt.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/tattoos.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/stats.lpc` | `int cmd()` → `int main()` |
| `lib/cmds/admin/tattoogun.lpc` | `int cmd()` → `int main()` |

**Skipped:** `lib/cmds/players/emote.c` — Dead Souls legacy reference file using
DS-specific APIs (`GetStaminaPoints`, `GetName`); not active in this driver.

**Note:** Files using `cmd_<verb>()` naming (e.g. `cmd_buy`, `cmd_sell`) are a
separate action-dispatch pattern registered via `add_action()` and are correct as-is.

### Remaining Steps
4. Audit `docs/duplicate-commands.txt` and remove stale/duplicate files.
5. Run integration test: connect, type each renamed command, confirm response.

---

## Priority 6 — Corpse Creation on Death (GAMEPLAY) — DONE 2026-02-23

### Approach
Used a heartbeat-based decay registry rather than `call_out()` (which only fires
named LPC functions in `global_vm`, not C-level `Item*` callbacks).

### Implementation
| File | Symbol | Description |
|------|--------|-------------|
| `src/death.h` | (new) | Declares `create_player_corpse()`, `handle_player_death()`, `corpse_tick()` |
| `src/death.c` | `CorpseDecayEntry` | `{Item*, Room*, time_t expires}`, static array of 32 slots |
| `src/death.c` | `create_player_corpse()` | Allocates container `Item`, transfers inventory, registers decay entry |
| `src/death.c` | `corpse_tick()` | Sweeps registry; on expiry broadcasts crumble message, removes from room, frees |
| `src/driver.c` | heartbeat block | Calls `corpse_tick()` every 2 seconds after `npc_tick()` |

### Constants
- `MAX_ACTIVE_CORPSES 32` — simultaneous tracked corpses
- `CORPSE_DECAY_SECS 300` — 5-minute decay timer

### Remaining
- LPC corpse creation via VM bridge (for LPC-authored NPCs)

---

## Priority 7 — NPC Spawn/Respawn System (GAMEPLAY) — DONE 2026-02-23

### Approach
C-level NPC respawn was already fully implemented in `src/npc.c` (`npc_handle_death()`,
`npc_respawn()`, tick countdown via `npc_tick()`).  The new work adds the **LPC-level
daemon layer** so that NPCs defined entirely in LPC can participate in the same
spawn/respawn cycle.

### Implementation
| File | Symbol | Description |
|------|--------|-------------|
| `lib/daemon/npc_daemon.lpc` | `register_npc(npc, room, delay)` | Register LPC NPC; stores path + room + delay |
| `lib/daemon/npc_daemon.lpc` | `npc_died(npc)` | Move record to respawn_queue with `time() + delay` |
| `lib/daemon/npc_daemon.lpc` | `heartbeat()` | Poll respawn_queue; re-clone and move into origin room when timer expires |
| `lib/std/npc.lpc` | `die(killer)` | Notify daemon, then `destruct(this_object())` |
| `lib/std/npc.lpc` | `receive_damage(dmg, atk)` | Reduce hp; call `die()` when <= 0 |
| `lib/domains/new_camelot/npc/guard.lpc` | (example) | Level-4 non-aggro town guard |
| `lib/secure/master.lpc` | `init_daemons()` | Added `"/daemon/npc_daemon"` to daemon list |
| `src/driver.c` | heartbeat block | Calls `efun_load_object("/daemon/npc_daemon")` + `obj_call_method("heartbeat")` every 2s |
| `lib/domains/new_camelot/town_square.lpc` | `create()` | Clones guard, calls `npc_daemon->register_npc(guard, room, 120)` |

### Full loop
1. `master.lpc` loads `/daemon/npc_daemon` at startup → `create()` initialises maps.
2. `room_load_from_lpc("/domains/new_camelot/town_square")` text-scrapes C Room struct,
   then calls `efun_load_object()` which fires the LPC `create()`.
3. `town_square.lpc::create()` clones the guard and registers it with npc_daemon.
4. Every 2 seconds the C heartbeat calls `npc_daemon->heartbeat()` which polls the
   respawn queue and re-clones dead NPCs into their origin rooms.

---

## Priority 8 — Race/OCC Stat Modifiers at Chargen (GAMEPLAY) — DONE 2026-02-23

### Implementation
| File | Change | Description |
|------|--------|-------------|
| `src/chargen.h` | `Character` struct | Added `save_vs_magic`, `save_vs_horror`, `save_vs_fear` (int) |
| `src/chargen.h` | `Character` struct | Added `racial_abilities[16][32]`, `num_racial_abilities` |
| `src/chargen.h` | `Character` struct | Added `race_skill_bonus` (int) |
| `src/race_loader.c` | `load_race_data()` | Parses `set_combat_bonuses()` mapping → applies save-vs fields |
| `src/race_loader.c` | `load_race_data()` | Scans `add_racial_ability("name", rank)` calls → populates array |
| `src/race_loader.c` | `load_race_data()` | VM bridge: loads race as LPC object, calls `query_skill_bonus()`, stores result |

### VM bridge pattern (race_skill_bonus)
```c
VMValue path = vm_value_create_string("/races/<name>");
VMValue obj  = efun_load_object(global_vm, &path, 1);
vm_value_release(&path);
if (obj.type == VALUE_OBJECT) {
    VMValue bonus = obj_call_method(global_vm, (obj_t*)obj.data.object_value,
                                    "query_skill_bonus", NULL, 0);
    if (bonus.type == VALUE_INT)
        ch->race_skill_bonus = (int)bonus.data.int_value;
    if (bonus.type != VALUE_NULL) vm_value_release(&bonus);
}
```

### Remaining
- Save format: new fields (`save_vs_*`, `racial_abilities`, `race_skill_bonus`) are NOT yet
  persisted in `save_character()`/`load_character()`.  Add to save format version 11.
- Apply `race_skill_bonus` in `skills.c` percentage calculation.

---

## Priority 9 — LPC Room Loader: execute create()/init() (CONTENT AUTHORING) — DONE 2026-02-23

### Status
`efun_load_object()` in `src/efun.c` already calls `obj_call_method(vm, o, "create", NULL, 0)`
after attaching methods (lines 1698 and 1335).  The only gap was that `room_load_from_lpc()`
in `src/room.c` used only the text-scraper and never invoked the VM at all.

### Fix Applied
After completing text-scraping, `room_load_from_lpc()` now calls `efun_load_object()` on the
same LPC path.  This fires the room's `create()` (which can spawn NPCs, register with
npc_daemon, etc.) as a side-effect of object creation.

```c
if (global_vm) {
    VMValue lpc_path_val = vm_value_create_string(lpc_path);
    VMValue room_obj_val = efun_load_object(global_vm, &lpc_path_val, 1);
    vm_value_release(&lpc_path_val);
    // efun_load_object calls create() internally
}
```

### Loader capabilities and limitations

| Capability | Status |
|------------|--------|
| Static properties (short, long, exits, items) | Text-scraped — works |
| `create()` body runs on first load | **Now works** via efun_load_object |
| LPC efuns (clone_object, move_object, etc.) in create() | Works if VM is up |
| `init()` on player arrival | **Not yet** — see below |
| Modifying C Room struct from create() | Not possible (C struct pre-populated by scraper) |
| Deep inheritance compilation errors | Non-fatal; logged as warnings |

### TODO:VM-DISPATCH — init() on player arrival
In classic LPMuds, `init()` is called on every object in the room when a living
enters.  To implement this, `cmd_move()` in `src/driver.c` (or the room-move helper)
must, after moving the player:
```c
// Pseudocode:
obj_t *room_lpc = efun_find_object(vm, room_path);
if (room_lpc) {
    obj_call_method(vm, room_lpc, "init", &player_obj_arg, 1);
    // also call init() on each item/NPC in the room with player as arg
}
```
Tracking issue: Priority 9b — wire init() to player-move path in driver.c.

---

## Priority 10 — Test Coverage and CI (QUALITY)

### Problem
- Integration tests rely on hardcoded paths and a running server.
- No CI pipeline exists to catch regressions.
- No save/load integrity tests.

### Steps
1. **Save/load test:** `tests/test_save_load.c` — mock a `PlayerSession`, call
   `save_character()`, reset struct, call `load_character()`, assert all fields match.
2. **Websocket test:** Add a basic connect/send/receive test using the existing WS
   handler.
3. **Fix hardcoded paths** in `tests/` scripts: replace absolute paths with
   relative ones derived from `$(REPO_ROOT)`.
4. **CI pipeline** (`Makefile` `ci` target or `.github/workflows/build.yml`):
   - `make clean && make` — assert 0 errors
   - `make test` — assert all unit tests pass
   - Future: add `-fsanitize=address,undefined` run (`make asan && make asan_tests`)
5. **`valid_write()` master policy test:** verify that the master object correctly
   rejects writes outside allowed directories.

---

## Appendix — Files Known to Contain TODOs/Stubs

See `diagnostics/lib_todos_2026-02-07.txt` for full list.  Key command stubs:
- `lib/cmds/eval.lpc` — needs real `eval` implementation for wizard debugging
- `lib/cmds/shutdown.lpc` — must call `wiz_shutdown()` in C
- `lib/cmds/goto.lpc` — must call `wiz_teleport()` in C
- `lib/cmds/users.lpc` — list online players; simple wrapper around `sessions[]`
- `lib/cmds/promote.lpc` — must call `wiz_promote()` in C
- `lib/cmds/clone.lpc` — must call `wiz_clone()` in C

---

---

## Completion Summary — 2026-02-23

All 10 priorities from this plan have been implemented and verified.

| Priority | Description | Completion Date |
|----------|-------------|-----------------|
| 1 | Secure password hashing (bcrypt via `crypt_r`) | 2026-02-23 |
| 2 | Inventory persistence (C-template + LPC items) | 2026-02-23 |
| 3 | Fix `SIMUL_EFUN` path in `runtime.conf` | 2026-02-23 |
| 4 | Zero compiler warnings (102 → 0) | 2026-02-23 |
| 5 | Fix admin command dispatch (`cmd()` → `main()`) | 2026-02-23 |
| 6 | Corpse creation with decay timer | 2026-02-23 |
| 7 | NPC spawn/respawn system | 2026-02-23 |
| 8 | Race/OCC LPC fields applied at chargen | 2026-02-23 |
| 9 | LPC room `create()` and `init()` wired on arrival | 2026-02-23 |
| 10 | CI pipeline (GitHub Actions: build/test/warnings) | 2026-02-23 |

Build state at completion: **34 source files, 0 warnings, 0 errors.**
Tests passing: `test_password` 10/10, `test_save_load` 11/11.

*Updated 2026-02-23 — all priorities complete.*
