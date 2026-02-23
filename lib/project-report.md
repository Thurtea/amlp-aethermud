# AMLP-AetherMUD — lib/ Project Report

Date: 2026-02-23

## Directory Purpose

`lib/` is the mudlib (LPC game code) layered atop the C driver in `src/`. It contains game objects, standard classes (`std/`), commands (`cmds/`), daemons, help files, game data, domain trees, and user-facing content. The driver loads LPC files from `lib/` via `efun_load_object`/`clone_object` and executes them on the VM.

## Subdirectory Map (top-level)

- `cmds/` — player and admin commands (many implemented; some are currently stubs).
- `daemon/` — background services (combat, command dispatcher, object manager, etc.).
- `std/` — standard inheritable classes (`object`, `living`, `player`, `room`, `corpse`, `wizard`/`wiztool`, `vehicle`, etc.).
- `objects/` and `obj/` — concrete game objects (weapons, armor, NPCs, items, vehicles).
- `secure/` — privileged code (e.g., `secure/simul_efun.lpc`).
- `save/` — player save files and data conventions.
- `help/`, `data/` — help pages and internal data sets.
- `domains/`, `races/`, `occs/`, `psionics/` — domain-specific content, races, occupations, and psionics data.
- `skills/`, `spells/` — game systems support.
- `test/`, `tools/` — helper scripts and tests.

## Status of `master.lpc` and `simul_efun.lpc`

- `master.lpc` (`lib/master.lpc`): Minimal master object present. Key functions implemented:
  - `epilog()` returns the simul_efun path `/secure/simul_efun`.
  - `valid_write()` enforces save file write locations for players.
  - Other hooks (`create`, `compile_object`, `log_error`) are skeletal and mostly placeholders — logging and richer master policies need expansion.

- `simul_efun.lpc` (`lib/secure/simul_efun.lpc`): Broad utility library implemented and loaded as the simul_efun. It provides:
  - notify_fail / query_notify_fail helpers
  - string utilities (`trim`, `strip_ansi`, `capitalize`, `pad_str`, `array_to_list`, etc.)
  - path utilities (`resolve_path`, `safe_path`, `dirname`, `basename_path`)
  - object helpers (`obj_name`, `obj_short`, `find_ob`, `vis_name`, `tell_room`, `shout_all`)
  - ANSI helpers and color mapping (many color codes defined)
  - type coercion and formatting helpers (`to_string`, `to_int`, `format_duration`)
  - array/object utilities and various small helpers used by std/ and commands

  This file is feature-rich and appears to be the central compat/utility layer for mudlib code. Note: it includes many ANSI color codes; per repo rules, color uses should be audited to ensure they follow project rules (AGENTS.md allows only specific color usages in game output).

## Game Systems: Working vs Broken vs Missing

- Working / Implemented (based on static inspection):
  - Core object model: `lib/std/object`, `lib/std/living`, `lib/std/player` exist and are reasonably implemented.
  - Rooms: `lib/std/room` is implemented with `look()`, exits map, and item/render helpers.
  - Object loading & methods: `efun_load_object`/`clone_object` flow in `src/efun.c` ties into `program_loader` and `obj_t` attachments; many objects in `lib/objects` inherit from `std/` and will attach methods when loaded.
  - Combat: `lib/daemon/combat.lpc` implements a real-time daemon with rounds, attack resolution, parry/dodge checks — appears complete conceptually.
  - Many standard efuns and helpers are used by the mudlib via `simul_efun.lpc`.

- Partial / Needs Integration / Risk Areas:
  - Commands: `lib/cmds/` includes many commands; several are explicit stubs (e.g., `cd.lpc`, `clone.lpc`, `goto.lpc`, `users.lpc`, `eval.lpc`, `promote.lpc`). The presence of many stubs indicates command coverage is incomplete.
  - Session integration: commands and efuns (e.g., `write`, `tell_object`) rely on session APIs; `src/` had partial session wiring. `lib/` assumes `this_player()`, `users()` and session-backed messaging; runtime integration must be validated.
  - Save/load: `master.lpc` has minimal `valid_write()` implementation; save file convention is present, but robust permission checks, backup/atomic writes, and password handling require review (driver had plaintext password TODOs).
  - `sscanf` expectations: mudlib code sometimes expects pass-by-reference `sscanf` behavior; `src/efun.c` provides a simplified `sscanf` with `__sscanf_result()` barrier — this can break code relying on reference semantics.

- Broken / Missing or Stubbed:
  - Administrative utilities: `clone`, `promote`, `users`, `goto` commands are stubs.
  - Some high-level features documented in `llm_entries` and notes (e.g., occ loader, some LLM helper scripts) are TODO.
  - Certain gameplay subsystems may rely on features marked TODO in `src/` (password hashing, destruct semantics, room linkage broadcasting). Those dependencies can cause runtime gaps.

## Inheritance Chain & Parent-Call Issues

- Many LPC files use `inherit` to extend `std/` classes (e.g., `inherit "/std/object"` or `inherit "/lib/std/vehicle_room"`). The codebase contains an explicit comment in `lib/std/player.lpc` noting a "scope resolution bug": the parser flags parent calls (`::`) but codegen historically lacked full support, and code contains defensive comments/workarounds.

- `parser.c` recognizes scope-resolution `::` tokens and marks `is_parent_call` on identifier nodes; `parser` and `simul_efun` assume parent-call semantics. However `codegen.c` and VM binding must ensure parent method dispatch and name mangling (e.g., `__parent__` prefixes used in `efun.c` when attaching parent methods) behave consistently. `efun.c` uses a strategy of duplicating parent functions with `__parent__` prefixes when attaching parent methods; this is a pragmatic workaround but creates complexity and potential duplication in VM function tables.

- Practical effect: code that uses `::method()` or `parent::method()` may work if the loader and attachment strategy matched compiled function names, but this area has known fragility and should be tested thoroughly (especially multiple inheritance, overridden methods, and `::` calls from constructors).

## Next Steps (actionable and prioritized)

1. Run static runtime checks and targeted unit tests for core flows (object load, `create()`, `inherit` parent calls, `this_player()` resolution, and `tell_object` behavior) without starting server clients.
2. Triage and implement critical command stubs in `lib/cmds/` used by players (`cd`, `clone` for creators, `users`, `goto` for admins) or clearly document missing commands.
3. Audit and secure save/password handling: replace plaintext storage and ensure `valid_write()`/`master` policies match intended file layout.
4. Test combat daemon end-to-end with NPC and player objects in a headless test harness (simulate players) to verify heartbeat, damage, death, and corpse creation flow (note: `death.c` had TODO to hook into LPC corpse creation).
5. Validate `sscanf` compatibility or update mudlib code to avoid pass-by-ref expectations; provide a compatibility layer or expand `efun_sscanf` implementation.
6. Create small smoke-tests under `test/` that load representative `lib/std/*` classes and assert basic behavior (e.g., `player->setup_player()`, `room->look()`, `combat->start_combat()`), to catch integration regressions early.
7. Audit `simul_efun.lpc` ANSI usage against AGENTS.md color rules and reduce or centralize color emission to permitted cases.

---
Generated by static inspection of `lib/` on 2026-02-23. Saved as `lib/project-report.md`.
