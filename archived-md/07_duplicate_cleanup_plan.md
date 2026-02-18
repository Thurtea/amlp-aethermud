# Duplicate Cleanup Plan

This document prioritizes duplicates found by `archived-md/06_duplicate_files_analysis.md` and provides step-by-step guidance and safe Git commands to consolidate the repository.

**Report source:** `archived-md/06_duplicate_files_analysis.md`

## Summary
- Total filename duplicates: 1,095 (from analysis)
- Focus: fix duplicates that break builds or waste space.

## High Priority (Critical Duplicates)
These duplicates require immediate attention because they affect build correctness or are core files.

Table: Name | Canonical Location | Duplicate Paths (to remove) | References to Check
---|---|---|---

<!-- Top 20 C/header duplicates auto-selected from the analysis -->
| array.c | `src/array.c` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c` | `Makefile`, `#include`/compile units, `grep "array.c" -R lib/ src/`
| array.h | `src/array.h` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.h` | header includes, `grep "array.h" -R`
| combat.c | `src/combat.c` | `mud-references/deadsouls/ds3.8.2/lib/lib/combat.c` | `Makefile`, references in `lib/` and `src/`
| combat.h | `src/combat.h` | `lib/include/combat.h` | header includes, `grep "combat.h" -R`
| compiler.c | `src/compiler.c` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.c` | build rules, compiler test files
| compiler.h | `src/compiler.h` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.h` | header includes
| death.c | `src/death.c` | multiple `mud-references/.../death.c` | `grep "death.c" -R`, `lib/std` references
| debug.h | `src/debug.h` | various `mud-references/.../debug.h` | header includes, packages
| item.c | `src/item.c` | `mud-references/deadsouls/ds3.8.2/lib/lib/std/item.c` | `Makefile`, object references in `lib/`
| item.h | `src/item.h` | `mud-references/deadsouls/ds3.8.2/lib/lib/include/item.h` | header includes
| magic.c | `src/magic.c` | `mud-references/deadsouls/ds3.8.2/lib/lib/magic.c` | `Makefile`, `lib/` references
| magic.h | `src/magic.h` | `mud-references/deadsouls/ds3.8.2/lib/include/magic.h` | header includes
| mapping.c | `src/mapping.c` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.c`, `mud-references/.../mapping.c` | linker/compile units
| mapping.h | `src/mapping.h` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.h` | header includes
| npc.c | `src/npc.c` | `mud-references/deadsouls/ds3.8.2/lib/lib/npc.c`, `mud-references/.../obj/npc.c` | `lib/` references
| npc.h | `src/npc.h` | `mud-references/deadsouls/ds3.8.2/lib/lib/include/npc.h` | header includes
| object.c | `src/object.c` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.c`, `mud-references/.../comp/object.c` | `Makefile`, object compile units
| object.h | `src/object.h` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.h`, `mud-references/.../secure/include/object.h` | header includes
| parser.c | `src/parser.c` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.c` | build rules, parser tests
| parser.h | `src/parser.h` | `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.h` | header includes


> **Special high-critical items**
>
>- `lib/master.lpc`: canonical -> `lib/master.lpc` (duplicates found in `lib/secure/master.lpc`) — this is the MUD master object. Verify semantics before merging/removing.
>- `Makefile`: canonical -> project root `Makefile`; `lib/Makefile` and internal Makefiles are usually secondary. Verify build targets before removing.

## Medium Priority (Organizational Issues)
- LPC files found outside `lib/` (move to `lib/`): e.g., `lib/races/*.lpc` duplicates in multiple locations. Fix by moving to `lib/` and updating references.
- Header files not in `lib/include/` or `src/`: consolidate to `lib/include/` for LPC headers and `src/` for C headers.
- Documentation scattered across `mud-references/` and `lib/doc/`: move canonical docs to `docs/` where appropriate.

## Low Priority (Minor Cleanup)
- Small config or data files (<1KB) — review then remove duplicates.
- Test files duplicated in `mud-references/` — safe to ignore unless used by build/test harness.
- Temporary or generated files — add to `.gitignore` if appropriate.

## Per-duplicate action template (use before making changes)
1. Verify differences:

```sh
# Example diff
diff -u src/array.c mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c | head
```

2. Decide canonical location (follow rules: `src/` for C, `lib/` for LPC, headers into `lib/include/` or `src/`).
3. Move or remove duplicates using git (examples below). Keep backups if unsure.
4. Update `Makefile` and include/search paths.
5. Rebuild and run tests: `make && make test` (if available).
6. Commit the change as one focused commit: `git add -A && git commit -m "cleanup: remove duplicate files for <name>"`

## Example Git commands (safe, commented) — top duplicates
See `scripts/cleanup_duplicates.sh` for a commented set of `git mv`/`git rm` commands and dry-run verification.

## Consolidation Guide
Recommended directory mappings:

- `src/` = C driver source
- `lib/` = LPC game library
- `lib/include/` = LPC headers
- `config/` = Configuration files
- `docs/` = Documentation
- `scripts/` = Shell scripts
- `tests/` = Test suites
- `tools/` = Development utilities

Cleanup strategy:
1. Verify with `diff`.
2. Determine canonical location.
3. Move (with `git mv`) or remove duplicate files (with `git rm`).
4. Update `Makefile`, includes, and any hardcoded paths.
5. Run `make` and tests.
6. Commit and push the cleanup in a separate branch/PR.

## Summary Statistics (from analysis)
- Filename duplicates: **1,095**
- Content duplicates: **621**
- Likely duplicates (same name + size): **608**



## Execution
- Verification report: `archived-md/08_duplicate_verification_report.md`
- Safe cleanup script: `scripts/safe_cleanup_batch_01.sh`
- Rollback script: `scripts/rollback_cleanup_batch_01.sh`
- Careful cleanup script for Yellow: `scripts/careful_cleanup_batch_02.sh`
