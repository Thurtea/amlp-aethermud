# Driver vs Library Duplicate Files (scoped)

Scanned paths: `src/`, `lib/` (explicitly excluded `mud-references/` and other external folders).

Summary: found duplicate basenames within the active `lib/` tree and one cross-tree match between `src/` and `lib/`.

## Duplicates Between `src/` and `lib/`

- **File:** combat.h
  - **Location 1:** src/combat.h
  - **Location 2:** lib/include/combat.h
  - **File Type:** C header (.h)
  - **Category:** Needs review
  - **Recommendation:** Manual review. Likely canonical file is the driver header in `src/`; merge API differences into canonical location, then remove or reconcile the duplicate in `lib/include/`.

## Duplicates Within `src/`

- No multi-location basenames were found that lie entirely inside `src/` (after excluding `mud-references/`).

## Duplicates Within `lib/`

The following basenames appear multiple times in `lib/`. All live in `lib/` (different subpaths). None were byte-for-byte identical across all copies — mark for manual review.

- **atlantean.lpc** — lib/races/atlantean.lpc | lib/languages/atlantean.lpc — Category: Needs review — Recommendation: decide canonical location in `lib/` (likely `races/`) and consolidate.
- **burster.lpc** — lib/races/burster.lpc | lib/occs/burster.lpc — Category: Needs review — Recommendation: review semantics; if duplicate, consolidate.
- **cat.lpc** — lib/cmds/cat.lpc | lib/cmds/creator/cat.lpc — Category: Needs review — Recommendation: prefer `lib/cmds/` for runtime commands; keep creator helper separate only if different.
- **cd.lpc** — lib/cmds/cd.lpc | lib/cmds/creator/cd.lpc — Category: Needs review
- **clone.lpc** — lib/cmds/clone.lpc | lib/cmds/creator/clone.lpc — Category: Needs review
- **cosmo_knight.lpc** — lib/races/cosmo_knight.lpc | lib/occs/cosmo_knight.lpc — Category: Needs review
- **eval.lpc** — lib/cmds/eval.lpc | lib/cmds/creator/eval.lpc — Category: Needs review
- **fountain.lpc** — lib/domains/new_camelot/garden/fountain.lpc | lib/domains/new_camelot/garden/obj/fountain.lpc — Category: Needs review
- **goblin.lpc** — lib/races/goblin.lpc | lib/languages/goblin.lpc — Category: Needs review
- **goto.lpc** — lib/cmds/goto.lpc | lib/cmds/admin/goto.lpc — Category: Needs review
- **language.lpc** — lib/cmds/language.lpc | lib/std/language.lpc — Category: Needs review
- **languages.lpc** — lib/daemon/languages.lpc | lib/cmds/languages.lpc — Category: Needs review
- **levitation.lpc** — lib/psionics/physical/levitation.lpc | lib/spells/level2/levitation.lpc — Category: Needs review
- **login.lpc** — lib/daemon/login.lpc | lib/clone/login.lpc — Category: Needs review
- **ls.lpc** — lib/cmds/ls.lpc | lib/cmds/creator/ls.lpc — Category: Needs review
- **master.lpc** — lib/master.lpc | lib/secure/master.lpc — Category: Needs review — Recommendation: `lib/master.lpc` is likely the canonical public master; reconcile secure/master modifications.
- **mind_block.lpc** — lib/psionics/super/mind_block.lpc | lib/psionics/sensitive/mind_block.lpc — Category: Needs review
- **mind_melter.lpc** — lib/races/mind_melter.lpc | lib/occs/mind_melter.lpc — Category: Needs review
- **promote.lpc** — lib/cmds/promote.lpc | lib/cmds/admin/promote.lpc — Category: Needs review
- **psi_healer.lpc** — lib/races/psi_healer.lpc | lib/occs/psi_healer.lpc — Category: Needs review
- **psi_stalker.lpc** — lib/races/psi_stalker.lpc | lib/occs/psi_stalker.lpc — Category: Needs review
- **psi_sword.lpc** — lib/psionics/super/psi_sword.lpc | lib/psionics/physical/psi_sword.lpc — Category: Needs review
- **pwd.lpc** — lib/cmds/pwd.lpc | lib/cmds/creator/pwd.lpc — Category: Needs review
- **rations.lpc** — lib/single/rations.lpc | lib/objects/supplies/rations.lpc — Category: Needs review
- **shield.lpc** — lib/single/shield.lpc | lib/objects/armor/shield.lpc — Category: Needs review
- **shutdown.lpc** — lib/cmds/shutdown.lpc | lib/cmds/admin/shutdown.lpc — Category: Needs review
- **skills.lpc** — lib/daemon/skills.lpc | lib/cmds/skills.lpc — Category: Needs review
- **spike.lpc** — lib/domains/castle/spike.lpc | lib/domains/staff_castle/npc/spike.lpc — Category: Needs review
- **stables.lpc** — lib/domains/new_camelot/stables.lpc | lib/domains/staff_castle/room/stables.lpc — Category: Needs review
- **start.lpc** — lib/domains/tutorial/rooms/start.lpc | lib/cmds/start.lpc — Category: Needs review
- **sword.lpc** — lib/single/sword.lpc | lib/objects/weapons/sword.lpc — Category: Needs review
- **telekinesis.lpc** — lib/psionics/physical/telekinesis.lpc | lib/spells/level3/telekinesis.lpc — Category: Needs review
- **vibro_blade.lpc** — lib/single/vibro_blade.lpc | lib/objects/weapons/vibro_blade.lpc — Category: Needs review
- **void.lpc** — lib/domains/forest/rooms/void.lpc | lib/domains/start/room/void.lpc — Category: Needs review
- **wiztool.lpc** — lib/cmds/admin/wiztool.lpc | lib/std/wiztool.lpc — Category: Needs review

## Summary Statistics (scoped)

- Total duplicate basenames found (in `src/` or `lib/`): 45
- Cross-tree duplicates (`src/` ↔ `lib/`): 1
- Within-`src/` duplicates: 0
- Within-`lib/` duplicates: 44
- Byte-for-byte identical files: 0 (none safe for automatic removal)

Estimated reclaimable space: 0 bytes (no exact duplicates detected). Manual consolidation required to reclaim space.

Next steps:
- Manually review the `Between src/lib` entry first (`combat.h`).
- For each `lib/` group, pick canonical location and either remove duplicates or merge content (use VCS to keep history).
- If you want, I can generate a `git rm`/`git mv` plan for confirmable entries once you approve canonical choices.
