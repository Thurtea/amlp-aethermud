# PROJECT STATUS — AMLP AetherMUD

Date: 2026-02-23

Executive summary
- The codebase builds and contains a working C driver and a large LPC mudlib. Core systems (VM, object model, basic commands, chargen, movement, combat framework, and spell framework) are present and partially functional. Several high-impact gaps remain: insecure password handling, missing inventory persistence, incomplete NPC/mob support, brittle LPC room loader behavior, and multiple TODOs and stubs in `src/` and `lib/` that block full gameplay and safe operations. The repo contains diagnostics and per-directory reports (see `docs/project-report.md` and per-directory `project-report.md` files).

What is working
- Driver compiles and links (example build successful).
- VM, lexer, parser, codegen pipeline present and largely functional.
- LPC mudlib `lib/` present with `std/`, `cmds/`, `daemon/`, `spells/`, and `skills/` scaffolding.
- Chargen UI flows are implemented; movement/`look`/flex exits operate for LPC-parsed rooms and C cardinal rooms.
- Magic core (multi-round casting, PPE checks) and basic wizard tools exist.
- Tests exist for lexer/parser/VM/containers and a set of integration scripts (some require a running server).

What is broken
- Password handling: plaintext password storage flagged in `src/driver.c` (security-critical).
- Inventory persistence: items are not serialized on save/load (players lose items on logout).
- Admin command dispatch mismatches: some LPC commands use `cmd()` while the dispatcher expects `main()`; duplicate/stray command files and missing registrations cause silent failures.
- Several C TODOs/stubs (corpse creation, call_outs, some efuns, wizard output wiring) remain and impact runtime correctness.
- `runtime.conf` `SIMUL_EFUN` path misconfigured (points to `.c`), risking runtime load errors.

What is incomplete
- NPC / mob system: template and spawn/respawn logic is not implemented; NPCs are minimal or absent.
- Race/OCC data application: LPC race/occ files exist, but chargen often ignores LPC-declared stat modifiers and bonuses (attr-based skill modifiers and racial abilities not applied).
- Spell targets & sustained spells: target resolution and sustained-cost accounting are deferred.
- Some lib commands are implemented as stubs and many top-level `lib/cmds` files are unregistered or duplicate.
- LPC room loader: text-scraping works for static setters but does not run `create()`/`init()` or spawn behavior.

What is missing entirely
- Robust NPC combat population and automated respawn system.
- Secure password hashing (bcrypt/argon2) implementation in code and tests.
- Inventory persistence tests and implementation.
- CI pipeline that runs unit tests, builds driver, and detects regressions/warnings on PRs.
- Runtime configuration for production (dedicated `RUN_AS_USER`, `LOG_DIR`, TLS options for websocket, and path validation).

Priority fix list (highest → lowest)
1. [DONE — 2026-02-23] Replace plaintext password handling with bcrypt. (Security-critical)
   - Extracted `hash_password()` and `verify_password()` to `src/password.c` / `src/password.h`.
   - Uses `crypt_r()` with `$2b$10$` prefix; 16 bytes of salt from `/dev/urandom`; bcrypt-base64 encoded.
   - `src/driver.c` stubs removed; real functions linked via `-lcrypt` (added to Makefile LDFLAGS).
   - `tests/test_password.c`: 10 tests covering hash prefix, verify match/mismatch, unique salts, NULL/empty edge cases — all PASS.
   - Build: 64 warnings, 0 errors.
2. [DONE — 2026-02-23] Implement inventory serialization for LPC-sourced items; add test. (Gameplay-critical)
   - Extracted inventory I/O to `inventory_write_to_file()` / `inventory_read_from_file()` in `src/item.c`.
   - Format extended: C-template items unchanged (template_id ≥0 + equip_slot); LPC items use sentinel -2 + uint16 path_len + path + equip_slot + delta_count=0.
   - Added `char *lpc_path` field to `Item` struct; `item_free()` frees it; `item_create()` zeros it.
   - `chargen.c` save/load delegated to item.c helpers (TODO:INCOMPLETE comments resolved).
   - `tests/test_save_load.c`: 11 tests — empty round-trip, 2 C-template items with equip slot, LPC sentinel written + graceful load without VM — all PASS.
   - TODO:VM-BRIDGE: property delta replay not yet implemented (delta_count always 0).
3. [DONE — 2026-02-23] Fix `runtime.conf` `SIMUL_EFUN` path and validate master/simul efun load behavior. (Ops-critical)
   - Changed `SIMUL_EFUN` from `.c` to `.lpc`; `lib/secure/simul_efun.lpc` confirmed present.
4. [IN PROGRESS — 2026-02-23] Triage and fix critical compiler warnings. (Stability)
   - Warnings: 102 → 93 (HIGH) → 69 (MEDIUM fixes 2026-02-23) → 63 → **64** (2026-02-23, +1 from password.c), 0 errors.
   - **RESOLVED HIGH**: vm.c:697 format mismatch; server.c signed/unsigned; chargen.c language loop; skills.c 5 comparisons.
   - **RESOLVED MEDIUM**: 22 snprintf truncation; server.c zero-length format; driver.c ternary signedness.
   - **RESOLVED LOW**: 11 chargen.c unused-parameter (void-cast); 4 strncpy truncation (→snprintf); 1 unused static function (attribute unused).
   - Raw output: `diagnostics/build-warnings.txt` | Triage: `diagnostics/warnings-triage.md`
   - Remaining: ~40 dead NULL checks on array members (MEDIUM), 2 -Wcomment in chargen.c (LOW).
5. [IN PROGRESS — 2026-02-23] Fix admin command dispatch inconsistencies. (Admin UX)
   - Root cause confirmed: `lib/daemon/command.lpc` calls `cmd_obj->main(args)` — files with `cmd()` were silently ignored.
   - **12 files renamed** `cmd()` → `main()`: forget, language, skills, languages, position, cast, manifest, hatch, prompt, tattoos, stats, admin/tattoogun.
   - Skipped: `lib/cmds/players/emote.c` (Dead Souls legacy, DS-specific APIs, not active).
   - `cmd_<verb>()` functions in other files are `add_action()` style dispatch — correct as-is.
   - Remaining: audit `docs/duplicate-commands.txt`, integration testing.
6. [DONE — 2026-02-23] Implement corpse creation flow with decay timer. (Gameplay)
   - `create_player_corpse()` creates a container `Item`, transfers inventory, places in room.
   - `corpse_tick()` added to `src/death.c`: global `CorpseDecayEntry` registry (32 slots), sweeps expired corpses every 2-second heartbeat; broadcasts crumble message; removes and frees corpse + contents.
   - Wired into `src/driver.c` heartbeat alongside `npc_tick()`; `src/death.h` created.
   - LPC corpse creation via VM bridge is a future task.
7. [DONE — 2026-02-23] Implement NPC spawn/respawn system (LPC daemon layer). (Gameplay)
   - C-level NPC respawn fully functional (npc_tick/npc_handle_death/npc_respawn).
   - `lib/daemon/npc_daemon.lpc`: register_npc(), npc_died(), heartbeat() API.
   - `lib/std/npc.lpc` + `lib/domains/new_camelot/npc/guard.lpc` — base NPC + example guard.
   - **NEW (2026-02-23)**: C heartbeat wires `efun_load_object("/daemon/npc_daemon")` + `obj_call_method("heartbeat")` every 2 seconds in `src/driver.c`.
   - **NEW (2026-02-23)**: `lib/domains/new_camelot/town_square.lpc` `create()` clones the guard and calls `npc_daemon->register_npc(guard, room, 120)` for 2-minute respawn.
   - Remaining: other domain rooms can follow the same `register_npc()` pattern in their `create()`.
8. [DONE — 2026-02-23] Apply race/OCC LPC fields at chargen (stat modifiers, OCC bonuses, racial abilities, skill bonus). (Gameplay)
   - `save_vs_magic/horror/fear`, `racial_abilities[16][32]`, `race_skill_bonus` added to `Character` (chargen.h).
   - `load_race_data()` parses `set_combat_bonuses()` and `add_racial_ability()` calls.
   - **NEW (2026-02-23)**: VM bridge wired — `load_race_data()` loads race LPC object via `efun_load_object()` and calls `query_skill_bonus()` to populate `race_skill_bonus`.
   - Remaining: `race_skill_bonus` not yet applied in skills.c; new fields not yet in save format (version 11 needed).
9. [DONE — 2026-02-23] Wire LPC room `create()` and `init()` on player arrival. (Content authoring)
   - **Root cause**: `room_load_from_lpc()` in `src/room.c` text-scraped but never called the VM.
   - **create() fix**: After text-scraping, `room_load_from_lpc()` calls `efun_load_object(global_vm, lpc_path)`, which fires the room's `create()` as a side-effect.
   - **init() fix (Priority 9b — NEW 2026-02-23)**: `cmd_move()` in `src/room.c` now calls `efun_find_object()` on the destination room's LPC path after `room_add_player()`, then dispatches `obj_call_method("init", player_arg)`. Guard: only if `global_vm && next_room->lpc_path && sess->player_object`. No-ops silently if room doesn't define `init()`.
   - Added `#include "session.h"` to `src/room.c` for `set_current_session()` prototype.
10. Add/repair tests for session manager, websocket handling, save/load integrity, and master `valid_write()` policies; remove hardcoded paths in test scripts and tools. (Quality)

Directory status table (directory — status — key notes)
- `/` — Partial/Healthy — Build scripts, `mud.sh`, `Makefile`, and top-level docs present; unify control script references in docs.
- `config/` — Improved — `runtime.conf` `SIMUL_EFUN` path fixed (2026-02-23); still lacks production settings (RUN_AS_USER, LOG_DIR, TLS).
- `docs/` — Good — detailed audits and per-directory reports exist; `docs/project-report.md` synthesized recent analysis.
- `diagnostics/` — Good — `build-warnings.txt` (69 warnings) and `warnings-triage.md` updated; HIGH + MEDIUM items resolved.
- `lib/` — Partial — rich mudlib exists (std, daemons, cmds) but many command stubs and some admin commands are incomplete; simul_efun is feature-rich but ANSI usage should be audited.
- `src/` — Partial/Critical issues — engine and VM present; TODOs in `driver.c` (passwords, destruct lifecycle), `death.c`, `wiz_tools.c` need attention; many warnings reported.
- `tests/` — Partial — robust unit tests for lexer/parser/VM/containers exist; integration/network tests rely on a running server and some tests/scripts use hardcoded paths and need stabilization for CI.
- `tools/` — Useful — dev tooling and proxies present; some scripts use absolute paths and duplicate scripts in `scripts/` and `tools/` should be consolidated.
- `lpc-extension/` — Good — VSCode grammar/snippets present and valid; suggestions: add more snippets, split huge efun regex.
- `build/` — Build artifacts present when built; no status file in repo — ensure `build.log` and rotation/cleanup policies are in place.

Suggested next actions (short list)
- Immediately: fix `SIMUL_EFUN` path in `config/runtime.conf`, and remove any plaintext password writes in `src/driver.c` (create a branch and patch with bcrypt placeholder and tests).
- Near term (1–2 sprints): inventory persistence, corpse integration, command dispatch fixes, NPC spawn foundation, and triaging high-severity warnings.
- Medium term: implement CI with ASAN/UBSAN for unit tests, stabilize integration tests, and migrate critical hardcoded C rooms to LPC or add C flex-exits for connectors.

Where this file is saved
- PROJECT-STATUS.md (repo root)

If you'd like, I can now:
- open a PR that implements the `runtime.conf` `SIMUL_EFUN` fix and a safe bcrypt scaffold in `src/driver.c`, or
- run a quick pass to capture `make` warnings into `diagnostics/build-warnings.txt` so we can triage the 117 warnings.
