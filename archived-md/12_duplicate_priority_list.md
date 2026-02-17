Duplicate Priority List

Source: `archived-md/11_manual_review_needed.md`

Summary
- Total duplicate candidate pairs: 36
- Identical files (safe to remove): 0
- Minor differences (likely whitespace/comments or small stubs): 8
- Major differences (need manual decision/merge): 28

Notes on methodology
- I used file size ratio as a heuristic: pairs with sizes within ~1.2x were classed as "Minor differences"; larger ratios indicate substantive differences and were classed as "Major differences". This is only an estimate — always run `diff -u` to confirm.

Category A — Identical files (safe to remove)
- None detected in `11_manual_review_needed.md`.

Category B — Minor differences (suggested: keep larger; remove smaller after quick review)
Recommendation: Run `diff -u <keep> <remove>`; if diffs are only comments/whitespace or the smaller file is a thin wrapper, remove the smaller one and update cleanup scripts.

- `lib/cmds/ls.lpc` (4200)  — keep: `lib/cmds/creator/ls.lpc` (4478)  => Recommendation: keep `lib/cmds/creator/ls.lpc`, remove `lib/cmds/ls.lpc` after quick diff
- `lib/cmds/pwd.lpc` (276)  — keep: `lib/cmds/creator/pwd.lpc` (353)
- `lib/cmds/shutdown.lpc` (254)  — keep: `lib/cmds/admin/shutdown.lpc` (283)
- `lib/psionics/physical/levitation.lpc` (2848)  — keep: `lib/spells/level2/levitation.lpc` (2112)  (sizes similar)
- `lib/psionics/super/mind_block.lpc` (1395)  — keep: `lib/psionics/sensitive/mind_block.lpc` (2062)
- `lib/psionics/super/psi_sword.lpc` (4404)  — keep: `lib/psionics/physical/psi_sword.lpc` (4064)
- `lib/single/rations.lpc` (580)  — keep: `lib/objects/supplies/rations.lpc` (513)
- `lib/single/vibro_blade.lpc` (981)  — keep: `lib/objects/weapons/vibro_blade.lpc` (750)

Category C — Major differences (manual review required)
Recommendation: Manually diff each pair (`diff -u pathA pathB`), choose canonical file (prefer the larger or the one in the more appropriate directory), merge where needed, and update cleanup scripts.

- `lib/cmds/admin/wiztool.lpc` (2415)  vs `lib/std/wiztool.lpc` (17187)
- `lib/cmds/cat.lpc` (2511)  vs `lib/cmds/creator/cat.lpc` (1451)
- `lib/cmds/cd.lpc` (267)  vs `lib/cmds/creator/cd.lpc` (1145)
- `lib/cmds/clone.lpc` (254)  vs `lib/cmds/creator/clone.lpc` (1406)
- `lib/cmds/eval.lpc` (262)  vs `lib/cmds/creator/eval.lpc` (1985)
- `lib/cmds/goto.lpc` (249)  vs `lib/cmds/admin/goto.lpc` (685)
- `lib/cmds/language.lpc` (1668)  vs `lib/std/language.lpc` (5522)
- `lib/cmds/promote.lpc` (278)  vs `lib/cmds/admin/promote.lpc` (4014)
- `lib/daemon/languages.lpc` (4618)  vs `lib/cmds/languages.lpc` (1768)
- `lib/daemon/login.lpc` (177)  vs `lib/clone/login.lpc` (8491)
- `lib/daemon/skills.lpc` (6840)  vs `lib/cmds/skills.lpc` (1947)
- `lib/domains/castle/spike.lpc` (2682)  vs `lib/domains/staff_castle/npc/spike.lpc` (5148)
- `lib/domains/forest/rooms/void.lpc` (0)  vs `lib/domains/start/room/void.lpc` (531)
- `lib/domains/new_camelot/garden/fountain.lpc` (815)  vs `lib/domains/new_camelot/garden/obj/fountain.lpc` (277)
- `lib/domains/new_camelot/stables.lpc` (524)  vs `lib/domains/staff_castle/room/stables.lpc` (1786)
- `lib/domains/tutorial/rooms/start.lpc` (345)  vs `lib/cmds/start.lpc` (1519)
- `lib/master.lpc` (1203)  vs `lib/secure/master.lpc` (4664)

Decision for master.lpc
- `lib/secure/master.lpc` is the more complete implementation: it contains initialization routines, daemon loading, directory setup, connection handling, and security helper functions. `lib/master.lpc` appears to be a much smaller/legacy stub.
- `mud.ctl` starts the driver with `lib/secure/master.lpc` (see `mud.ctl` start command), therefore `lib/secure/master.lpc` is the canonical runtime master.

Recommendation: KEEP `lib/secure/master.lpc` as canonical. Manually inspect `lib/master.lpc` for any unique content and either merge needed pieces into `lib/secure/master.lpc` or archive/remove `lib/master.lpc` after verification and tests.
- `lib/psionics/physical/telekinesis.lpc` (1873)  vs `lib/spells/level3/telekinesis.lpc` (3236)
- `lib/psionics/super/psi_sword.lpc` (4404)  vs `lib/psionics/physical/psi_sword.lpc` (4064)  (already in Minor list by size similarity — include here if you prefer stricter manual review)
- `lib/races/atlantean.lpc` (4034)  vs `lib/languages/atlantean.lpc` (736)
- `lib/races/burster.lpc` (3926)  vs `lib/occs/burster.lpc` (1887)
- `lib/races/cosmo_knight.lpc` (3099)  vs `lib/occs/cosmo_knight.lpc` (1985)
- `lib/races/goblin.lpc` (4719)  vs `lib/languages/goblin.lpc` (695)
- `lib/races/mind_melter.lpc` (3581)  vs `lib/occs/mind_melter.lpc` (1833)
- `lib/races/psi_healer.lpc` (3770)  vs `lib/occs/psi_healer.lpc` (1982)
- `lib/races/psi_stalker.lpc` (6095)  vs `lib/occs/psi_stalker.lpc` (2020)
- `lib/single/shield.lpc` (687)  vs `lib/objects/armor/shield.lpc` (313)
- `lib/single/sword.lpc` (660)  vs `lib/objects/weapons/sword.lpc` (317)
- `src/combat.h` (4740)  vs `lib/include/combat.h` (7332)

Estimated automation vs manual
- Potentially auto-removable (after a quick diff confirming only trivial differences): ~8 files (the "Minor differences" category). These could be scripted for removal with a safety confirmation.
- Require manual review/merge: ~28 pairs (major differences). These should be reviewed by a developer familiar with the expected behavior and tested after merging or deletion.

Next actions (recommended)
1. For each file in Category B, run `diff -u` and if diffs are trivial, update cleanup scripts to remove the smaller copy.
2. For Category C, assign owners and perform manual diffs, merges, and functional tests.
3. After decisions are made, update `scripts/` cleanup helpers and run them in a dry-run mode before actual deletion.

*** End of report
