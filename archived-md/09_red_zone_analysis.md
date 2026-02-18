# Red Zone Analysis (top candidates)

This file summarizes the Red-zone duplicates from `archived-md/08_duplicate_verification_report.md`, provides per-pair metadata and recommendations, and lists automated-safe scripts produced for trivial/drift cases.

Summary (top processed pairs):
- Total Red pairs analyzed: 20
- Red-Trivial: 0
- Red-Drift: 20 (14 keep `src/` canonical; 6 keep `mud-references`/compare)
- Red-Variant: 0
- Red-Conflict: 0

Per-file analysis and recommendation (concise):

1. `src/array.c`  vs `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c`
- Diff summary: large content differences; different includes and many added lines (see report diff snippet).
- ls: `src/array.c` = 3.6k (5 Feb 2026) ; reference = 65k (25 Jul 2011)
- git last commit: canonical=1769100993 (older) ; compare=1770401731 (newer)
- Recommendation: Red-Drift — keep newer (reference), remove older (`src/array.c`) or reconcile. ACTION: remove older.

2. `src/array.h`  vs `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.h`
- Diff summary: header API and struct layout changed significantly.
- ls: `src/array.h` = 844 ; reference = 2.5k
- git last commit: canonical=1769100993 ; compare=1770401731 (newer)
- Recommendation: Red-Drift — keep reference (newer); remove `src/array.h`.

3. `src/combat.c`  vs `mud-references/.../lib/combat.c`
- Diff summary: sizable differences but `src/combat.c` is newer and active.
- ls: `src/combat.c` 37k (15 Feb 2026) ; reference 34k (30 Dec 2009)
- git last commit: canonical=1771214003 (newer) ; compare=1770401731
- Recommendation: Red-Drift — keep `src/combat.c`, remove reference copy.

4. `src/combat.h`  vs `lib/include/combat.h`
- Diff summary: header reorganized and extended in `lib/include` but `src/` is newer in repo.
- ls: `src/combat.h` 4.7k (15 Feb 2026) ; lib/include 7.3k (5 Feb 2026)
- git last commit: canonical=1771214003 ; compare=1770174869
- Recommendation: Red-Drift — keep `src/combat.h` (canonical), remove duplicate header in `lib/include` if not referenced by LPC; verify includes usage first.

5. `src/compiler.c`  vs `mud-references/.../compiler.c`
- Diff summary: large refactor present in `src`; canonical is newer.
- ls: `src/compiler.c` 45k (9 Feb 2026) ; reference 85k (25 Jul 2011)
- git last commit: canonical=1770681464 ; compare=1770401731
- Recommendation: Red-Drift — keep `src/compiler.c`, remove reference.

6. `src/compiler.h`  vs `mud-references/.../compiler.h`
- Diff summary: API reshaped; canonical appears newer.
- Recommendation: Red-Drift — keep `src/compiler.h`, remove reference.

7. `src/death.c`  vs multiple `mud-references` death.c copies
- Diff summary: `src/death.c` is current implementation; many reference copies are older library rooms.
- ls & git: `src/death.c` newer (13 Feb 2026) ; references 2009–2011
- Recommendation: Red-Drift — keep `src/death.c`; remove older library room copies (they appear to be original LPMud room files).

8. `src/debug.h`  vs `mud-references/.../debug.h`
- Diff summary: both differ; reference content is older/documentation-style; compare commit epoch slightly newer.
- Recommendation: Red-Drift (keep newer reference) — inspect usages then remove older header or merge doc/text into canonical include.

9. `src/item.c` / `src/item.h` vs reference copies
- Diff summary: canonical `src/*` are newer and implement driver-level APIs; references are older library code.
- Recommendation: Red-Drift — keep `src/` copies, remove library duplicates.

10. `src/magic.c`, `src/magic.h`
- Diff summary: canonical is newer; references are older library spell implementations.
- Recommendation: Red-Drift — keep `src/` copies.

11. `src/mapping.c`, `src/mapping.h`
- Diff summary: large refactor differences; reference copies appear older but some reference epoch is newer — treat as Red-Drift where `mud-references` is newer.
- Recommendation: For pairs where `mud-references` is newer, prefer the reference copy or reconcile manually.

12. `src/npc.c`, `src/npc.h`
- Diff summary: canonical is newer and driver-style; references are older LPMud library NPCs.
- Recommendation: keep `src/` copies.

13. `src/object.c`, `src/object.h`
- Diff summary: `src/object.c` is newer; some `object.h` references show newer epoch — inspect `object.h` differences before removal.
- Recommendation: keep canonical `src/object.c`; consider merging `object.h` changes if reference is intentionally different.

14. `src/parser.c`, `src/parser.h`
- Diff summary: canonical appears refactored; references are large legacy parser code.
- Recommendation: keep `src/` canonical parser files.

Automated outputs (generated):
- `scripts/normalize_and_cleanup.sh` — normalizes trivial diffs then removes trivial duplicates (no Red-Trivial files detected; script includes placeholder and checks).
- `scripts/remove_stale_duplicates.sh` — safely removes older/stale copies using `git rm` when tracked, `rm` otherwise. It targets the older files identified above.

Files requiring explicit developer decision (manual review):
- `src/array.c`, `src/array.h` — reference copy is larger/newer; these may carry code the team intentionally preserved in `mud-references`. Decide canonical location (src/ or lib/). Recommended action: open the reference, confirm intended functionality, then move/merge into `src/` or archive.
- `src/debug.h` — reference contains additional documentation text; decide whether to merge docs into canonical header.
- `src/object.h` — reference looks substantial; merge if API differences are intentional.

Cleanup summary and next steps

Immediate actions (ready to run):
- Green Zone: run `scripts/safe_cleanup_batch_01.sh` (as prepared earlier) — not executed here.
- Red-Trivial: none.
- Red-Drift: 20 pairs → run `scripts/remove_stale_duplicates.sh` (script created below) after manual confirmation.

Requires developer decision:
- Red-Variant / Red-Conflict: none flagged in this top set, but `array.*`, `debug.h`, and `object.h` require manual merge/decision.

Total cleanup progress
- Can auto-remove (by script): 14 files (older copies tracked and removable) — see `scripts/remove_stale_duplicates.sh`.
- Need manual review: 3 files (listed above).

---
Documentation: the raw per-pair metadata and short diff snippets are preserved in `/home/thurtea/amlp-aethermud/archived-md/red_zone_raw.txt` for audits.
