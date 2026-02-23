# AMLP-AetherMUD — diagnostics/ Project Report

Date: 2026-02-23

## Directory Purpose

`diagnostics/` holds developer-facing reports and scan outputs used to collect issues found during static scans, development debugging, and troubleshooting (e.g., TODO inventories, ANSI/debugging notes).

## File Inventory

- `README.md` — notes about ANSI color/`send_ansi()` integration, temporary patches applied, and recommended follow-ups.
- `lib_todos_2026-02-07.txt` — a generated list of TODO / FIXME / STUB comments found across `lib/` on 2026-02-07. Contains many per-file annotations (races, occs, command stubs, and tool TODOs).

## Warnings / Issues Found (in these files)

- Compiler warnings: I did not find a compiler warning log or file containing the "117 warnings" inside `diagnostics/`. If the build emitted 117 warnings, the raw build output (e.g., console, `build.log`, or a redirected file) is not present here. To capture and analyze those warnings, run the build with stderr redirected into `diagnostics/build-warnings.txt` (example commands in Next Steps).

- The available diagnostics content does include a comprehensive TODO inventory. High-level categories from `lib_todos_2026-02-07.txt`:
  - Race/OCC content stubs: Many files under `lib/races/` and `lib/occs/` contain "TODO: Add full ..." and related configuration TODOs (descriptions, stat modifiers, abilities, equipment).
  - Command stubs: Multiple `lib/cmds/` entries flagged with TODOs (e.g., `eval.lpc`, `shutdown.lpc`, `goto.lpc`, `users.lpc`, `pwd.lpc`, `promote.lpc`, `ls.lpc`, `clone.lpc`, `cd.lpc`).
  - Tooling TODOs: `lib/tools/generate_stubs.sh` contains generation TODOs and markers for missing content.

Below are representative excerpts (not exhaustive):

- `lib/races/*.lpc`: repeated "TODO: Add full race description" and placeholders for physical characteristics, stat modifiers, racial abilities, OCC restrictions, starting resources.
- `lib/occs/*.lpc`: repeated "TODO: Add full O.C.C. description" and placeholders for stat requirements, bonuses, skills, starting equipment.
- `lib/cmds/*.lpc`: several commands are explicit stubs with comments "TODO: Implement ..." and `write("Stub: ... not implemented")` behavior.

## Categorization: Critical vs Cosmetic

- Critical (should triage and fix sooner):
  - Command-functionality TODOs for admin/creator commands (e.g., `clone`, `promote`, `users`, `goto`) — lack of these reduces admin/creator workflows and may block test harnesses and automation.
  - `eval`/`shutdown` stubs — important for developer/admin debugging and safe shutdown/restart.
  - Integration notes in `README.md` about `send_ansi()` and patched passthroughs: these affect runtime rendering and are a stability risk (room `look()` crashes were observed).

- Medium / Cosmetic:
  - Race and OCC description TODOs — mostly content placeholders; important for completeness but do not block engine functionality.
  - Generated stub comments in `lib/tools` — housekeeping items for cleanup and content generation.

## Next Steps (recommended, actionable)

1. Capture the build warnings into diagnostics for analysis:

```sh
# from repo root
make clean && make 2> diagnostics/build-warnings.txt
wc -l diagnostics/build-warnings.txt
```

2. Summarize and categorize warnings (example):

```sh
# High-level grouping by gcc warning text
grep -E "warning:|error:" diagnostics/build-warnings.txt | sed -E 's/^[^:]*:[0-9]+: //' | sort | uniq -c | sort -nr > diagnostics/warning-summary.txt
```

3. Triage critical warning classes first: implicit function declarations, incompatible pointer types, missing prototypes, signed/unsigned mismatches, and use-after-free/UB warnings flagged by sanitizers. These can cause runtime crashes and should be fixed before cosmetic warnings.

4. Re-run the build under AddressSanitizer/UBSan and redirect output to `diagnostics/asan-warnings.txt` to surface memory issues:

```sh
# example build with ASAN (adjust Makefile or compile flags accordingly)
make clean
ASAN_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer' CFLAGS="$ASAN_FLAGS -g -O1" make 2> diagnostics/asan-warnings.txt
```

5. For the `send_ansi()` issue documented in `README.md`: revert passthrough temporary changes and add a small unit test that exercises ANSI conversion in isolation (or add an efun export test) before re-enabling in production. Coordinate with `src/` efun exports.

6. Track TODO resolution: generate a smaller actionable TODO list filtered by critical areas (commands, master policies, runtime integration) and assign owners; consider adding `diagnostics/todo-priority.csv` with filename, issue, priority, and suggested fix.

---
Notes: The diagnostics folder currently contains helpful static-scan artifacts but does not include the raw compiler output that produced "117 warnings" — capture that output into `diagnostics/` and I can parse and categorize the warnings into exact counts and categories.

Saved as `diagnostics/project-report.md`.
