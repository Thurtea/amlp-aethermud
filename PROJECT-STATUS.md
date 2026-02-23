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
1. [IN PROGRESS — 2026-02-23] Replace plaintext password handling with secure hashing and eliminate any code-paths that log or store raw passwords. (Security-critical)
   - Added `hash_password()` and `verify_password()` stubs in `src/driver.c` (~line 64).
   - All plaintext `strcmp`/`strncpy` password sites wired to stubs (STATE_GET_PASSWORD, STATE_CONFIRM_PASSWORD, `password` command).
   - Build: 0 errors, 102 warnings.  Remaining work: wire real bcrypt/argon2 KDF into stub bodies and add `libargon2` dependency.
   - See `docs/implementation-plan.md` Priority 1 for exact steps.
2. [IN PROGRESS — 2026-02-23] Implement inventory serialization in `save_character()`/`load_character()` and add tests to validate persistence. (Gameplay-critical)
   - Audit confirmed: inventory IS already serialized in `src/chargen.c` (save lines ~1719, load lines ~2180).
   - Format: item_count (int) + per-item {template_id (int), equip_slot (uint8_t)}.
   - Added `TODO:INCOMPLETE` comments in both `save_character()` and `load_character()` explaining the LPC item reconstruction gap (`item_create()` only handles C-template items; LPC-sourced items need path + property delta serialisation).
   - Remaining work: add `tests/test_save_load.c` regression test.
3. [DONE — 2026-02-23] Fix `runtime.conf` `SIMUL_EFUN` path and validate master/simul efun load behavior. (Ops-critical)
   - Changed `SIMUL_EFUN` from `.c` to `.lpc`; `lib/secure/simul_efun.lpc` confirmed present.
4. [IN PROGRESS — 2026-02-23] Triage and fix critical compiler warnings. (Stability)
   - Warnings: 102 → 93 (HIGH) → **69** (MEDIUM fixes 2026-02-23), 0 errors.
   - **RESOLVED HIGH**: vm.c:697 format mismatch; server.c signed/unsigned; chargen.c language loop; skills.c 5 comparisons.
   - **RESOLVED MEDIUM**: 22 snprintf truncation (buffers widened in driver.c, server.c, preprocessor.c, room.c, chargen.c, item.c); server.c:259 zero-length format → `new_dir[0] = '\0'`; driver.c:267 ternary signedness cast.
   - Raw output: `diagnostics/build-warnings.txt` | Triage: `diagnostics/warnings-triage.md`
   - Remaining: 42 dead NULL checks on array members (MEDIUM), LOW cleanup items.
5. [IN PROGRESS — 2026-02-23] Fix admin command dispatch inconsistencies. (Admin UX)
   - Root cause confirmed: `lib/daemon/command.lpc` calls `cmd_obj->main(args)` — files with `cmd()` were silently ignored.
   - **12 files renamed** `cmd()` → `main()`: forget, language, skills, languages, position, cast, manifest, hatch, prompt, tattoos, stats, admin/tattoogun.
   - Skipped: `lib/cmds/players/emote.c` (Dead Souls legacy, DS-specific APIs, not active).
   - `cmd_<verb>()` functions in other files are `add_action()` style dispatch — correct as-is.
   - Remaining: audit `docs/duplicate-commands.txt`, integration testing.
6. [IN PROGRESS — 2026-02-23] Implement corpse creation flow and integrate death handling with LPC corpse objects. (Gameplay)
   - `create_player_corpse()` in `src/death.c` now allocates a container `Item`, transfers dead player's full inventory to corpse contents, clears equipment slots, and places corpse in the room via `room_add_item()`.
   - Room broadcast notifies occupants. `lib/obj/corpse.lpc` created as companion LPC template for future LPC-level use.
   - Remaining: decay timer (300s heartbeat/call_out not yet wired); LPC corpse creation via VM bridge.
7. Implement or stabilize NPC spawn/respawn templates and tie into room loader or daemon. (Gameplay)
8. [IN PROGRESS — 2026-02-23] Apply race/OCC LPC fields at chargen (stat modifiers, OCC bonuses, attribute-based skill adjustments, racial abilities). (Gameplay)
   - **Audit confirmed**: `load_race_data()` and `load_occ_data()` already apply `set_stat_modifiers()`, `set_stat_bonus()`, SDC/MDC/ISP/PPE, natural weapons, and HP bonuses.
   - **Bug fixed**: `chargen_complete()` was resetting combat defaults (attacks/parries/auto-defend) AFTER `apply_race_and_occ()` ran. Fixed by adding `apply_race_combat_attributes()` call in `chargen_complete()` to restore race-specific values.
   - **TODO:INTEGRATION stubs added** in `src/race_loader.c`: `set_combat_bonuses()` (save vs magic/horror), `add_racial_ability()` calls, `query_skill_bonus()` LPC function — all require Character struct additions or VM bridge.
   - Remaining: add `save_vs_magic`/`save_vs_horror` fields to Character; wire racial ability tracking; LPC `query_skill_bonus()` via VM.
9. Harden LPC room loader, or provide an explicit `load_object()` path that executes `create()`/`init()` for rooms that need dynamic behavior; document loader limitations. (Content authoring)
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
