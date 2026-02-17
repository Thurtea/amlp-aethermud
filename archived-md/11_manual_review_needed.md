# Manual Review Needed

Files with differing content or larger-than-driver lib versions.

The following pairs require manual review. For each pair run:

```bash
diff -u <pathA> <pathB>
```

Then decide which file is canonical, merge differences, and update the cleanup script accordingly.

---

## wiztool.lpc
- lib/cmds/admin/wiztool.lpc
  - size: 2415 bytes
  - mtime: 1770312569.5677838
- lib/std/wiztool.lpc
  - size: 17187 bytes
  - mtime: 1770387606.470757

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/admin/wiztool.lpc lib/std/wiztool.lpc`

## cat.lpc
- lib/cmds/cat.lpc
  - size: 2511 bytes
  - mtime: 1770410286.0050385
- lib/cmds/creator/cat.lpc
  - size: 1451 bytes
  - mtime: 1770916084.15023

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/cat.lpc lib/cmds/creator/cat.lpc`

## cd.lpc
- lib/cmds/cd.lpc
  - size: 267 bytes
  - mtime: 1770825700.493615
- lib/cmds/creator/cd.lpc
  - size: 1145 bytes
  - mtime: 1770312569.5677838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/cd.lpc lib/cmds/creator/cd.lpc`

## clone.lpc
- lib/cmds/clone.lpc
  - size: 254 bytes
  - mtime: 1770825700.493615
- lib/cmds/creator/clone.lpc
  - size: 1406 bytes
  - mtime: 1770410252.6690469

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/clone.lpc lib/cmds/creator/clone.lpc`

## eval.lpc
- lib/cmds/eval.lpc
  - size: 262 bytes
  - mtime: 1770825700.493615
- lib/cmds/creator/eval.lpc
  - size: 1985 bytes
  - mtime: 1770312569.5677838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/eval.lpc lib/cmds/creator/eval.lpc`

## goto.lpc
- lib/cmds/goto.lpc
  - size: 249 bytes
  - mtime: 1770825700.493615
- lib/cmds/admin/goto.lpc
  - size: 685 bytes
  - mtime: 1770312569.5677838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/goto.lpc lib/cmds/admin/goto.lpc`

## language.lpc
- lib/cmds/language.lpc
  - size: 1668 bytes
  - mtime: 1770312569.5717838
- lib/std/language.lpc
  - size: 5522 bytes
  - mtime: 1770312569.579784

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/language.lpc lib/std/language.lpc`

## ls.lpc
- lib/cmds/ls.lpc
  - size: 4200 bytes
  - mtime: 1770737158.8227348
- lib/cmds/creator/ls.lpc
  - size: 4478 bytes
  - mtime: 1770741692.9106524

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/ls.lpc lib/cmds/creator/ls.lpc`

## promote.lpc
- lib/cmds/promote.lpc
  - size: 278 bytes
  - mtime: 1770825700.493615
- lib/cmds/admin/promote.lpc
  - size: 4014 bytes
  - mtime: 1770312569.5677838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/promote.lpc lib/cmds/admin/promote.lpc`

## pwd.lpc
- lib/cmds/pwd.lpc
  - size: 276 bytes
  - mtime: 1770825700.493615
- lib/cmds/creator/pwd.lpc
  - size: 353 bytes
  - mtime: 1770312569.5717838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/pwd.lpc lib/cmds/creator/pwd.lpc`

## shutdown.lpc
- lib/cmds/shutdown.lpc
  - size: 254 bytes
  - mtime: 1770825700.493615
- lib/cmds/admin/shutdown.lpc
  - size: 283 bytes
  - mtime: 1770312569.5677838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/cmds/shutdown.lpc lib/cmds/admin/shutdown.lpc`

## languages.lpc
- lib/daemon/languages.lpc
  - size: 4618 bytes
  - mtime: 1770312569.5717838
- lib/cmds/languages.lpc
  - size: 1768 bytes
  - mtime: 1770312569.5717838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/daemon/languages.lpc lib/cmds/languages.lpc`

## login.lpc
- lib/daemon/login.lpc
  - size: 177 bytes
  - mtime: 1770312569.5717838
- lib/clone/login.lpc
  - size: 8491 bytes
  - mtime: 1770934456.3583112

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/daemon/login.lpc lib/clone/login.lpc`

## skills.lpc
- lib/daemon/skills.lpc
  - size: 6840 bytes
  - mtime: 1770312569.5717838
- lib/cmds/skills.lpc
  - size: 1947 bytes
  - mtime: 1770312569.5717838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/daemon/skills.lpc lib/cmds/skills.lpc`

## spike.lpc
- lib/domains/castle/spike.lpc
  - size: 2682 bytes
  - mtime: 1770312569.5717838
- lib/domains/staff_castle/npc/spike.lpc
  - size: 5148 bytes
  - mtime: 1770312569.5717838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/domains/castle/spike.lpc lib/domains/staff_castle/npc/spike.lpc`

## void.lpc
- lib/domains/forest/rooms/void.lpc
  - size: 0 bytes
  - mtime: 1770312569.5717838
- lib/domains/start/room/void.lpc
  - size: 531 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/domains/forest/rooms/void.lpc lib/domains/start/room/void.lpc`

## fountain.lpc
- lib/domains/new_camelot/garden/fountain.lpc
  - size: 815 bytes
  - mtime: 1771105437.8045204
- lib/domains/new_camelot/garden/obj/fountain.lpc
  - size: 277 bytes
  - mtime: 1771105473.8045163

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/domains/new_camelot/garden/fountain.lpc lib/domains/new_camelot/garden/obj/fountain.lpc`

## stables.lpc
- lib/domains/new_camelot/stables.lpc
  - size: 524 bytes
  - mtime: 1771123269.3936753
- lib/domains/staff_castle/room/stables.lpc
  - size: 1786 bytes
  - mtime: 1770312569.5717838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/domains/new_camelot/stables.lpc lib/domains/staff_castle/room/stables.lpc`

## start.lpc
- lib/domains/tutorial/rooms/start.lpc
  - size: 345 bytes
  - mtime: 1770934456.3583112
- lib/cmds/start.lpc
  - size: 1519 bytes
  - mtime: 1770312569.5717838

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/domains/tutorial/rooms/start.lpc lib/cmds/start.lpc`

## master.lpc
- lib/master.lpc
  - size: 1203 bytes
  - mtime: 1770312569.5757837
- lib/secure/master.lpc
  - size: 4664 bytes
  - mtime: 1770387586.4947622

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/master.lpc lib/secure/master.lpc`

## levitation.lpc
- lib/psionics/physical/levitation.lpc
  - size: 2848 bytes
  - mtime: 1770312569.5757837
- lib/spells/level2/levitation.lpc
  - size: 2112 bytes
  - mtime: 1770312569.579784

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/psionics/physical/levitation.lpc lib/spells/level2/levitation.lpc`

## telekinesis.lpc
- lib/psionics/physical/telekinesis.lpc
  - size: 1873 bytes
  - mtime: 1770312569.5757837
- lib/spells/level3/telekinesis.lpc
  - size: 3236 bytes
  - mtime: 1770312569.579784

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/psionics/physical/telekinesis.lpc lib/spells/level3/telekinesis.lpc`

## mind_block.lpc
- lib/psionics/super/mind_block.lpc
  - size: 1395 bytes
  - mtime: 1770312569.5757837
- lib/psionics/sensitive/mind_block.lpc
  - size: 2062 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/psionics/super/mind_block.lpc lib/psionics/sensitive/mind_block.lpc`

## psi_sword.lpc
- lib/psionics/super/psi_sword.lpc
  - size: 4404 bytes
  - mtime: 1770312569.5757837
- lib/psionics/physical/psi_sword.lpc
  - size: 4064 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/psionics/super/psi_sword.lpc lib/psionics/physical/psi_sword.lpc`

## atlantean.lpc
- lib/races/atlantean.lpc
  - size: 4034 bytes
  - mtime: 1770855013.774998
- lib/languages/atlantean.lpc
  - size: 736 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/races/atlantean.lpc lib/languages/atlantean.lpc`

## burster.lpc
- lib/races/burster.lpc
  - size: 3926 bytes
  - mtime: 1770387812.5347075
- lib/occs/burster.lpc
  - size: 1887 bytes
  - mtime: 1770851190.8072343

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/races/burster.lpc lib/occs/burster.lpc`

## cosmo_knight.lpc
- lib/races/cosmo_knight.lpc
  - size: 3099 bytes
  - mtime: 1770387795.1107118
- lib/occs/cosmo_knight.lpc
  - size: 1985 bytes
  - mtime: 1770941541.4739

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/races/cosmo_knight.lpc lib/occs/cosmo_knight.lpc`

## goblin.lpc
- lib/races/goblin.lpc
  - size: 4719 bytes
  - mtime: 1770387758.7947195
- lib/languages/goblin.lpc
  - size: 695 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/races/goblin.lpc lib/languages/goblin.lpc`

## mind_melter.lpc
- lib/races/mind_melter.lpc
  - size: 3581 bytes
  - mtime: 1770387753.7747207
- lib/occs/mind_melter.lpc
  - size: 1833 bytes
  - mtime: 1770844598.8636403

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/races/mind_melter.lpc lib/occs/mind_melter.lpc`

## psi_healer.lpc
- lib/races/psi_healer.lpc
  - size: 3770 bytes
  - mtime: 1770387782.7467134
- lib/occs/psi_healer.lpc
  - size: 1982 bytes
  - mtime: 1770941541.4739

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/races/psi_healer.lpc lib/occs/psi_healer.lpc`

## psi_stalker.lpc
- lib/races/psi_stalker.lpc
  - size: 6095 bytes
  - mtime: 1770312569.579784
- lib/occs/psi_stalker.lpc
  - size: 2020 bytes
  - mtime: 1770940760.2899473

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/races/psi_stalker.lpc lib/occs/psi_stalker.lpc`

## rations.lpc
- lib/single/rations.lpc
  - size: 580 bytes
  - mtime: 1770312569.579784
- lib/objects/supplies/rations.lpc
  - size: 513 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/single/rations.lpc lib/objects/supplies/rations.lpc`

## shield.lpc
- lib/single/shield.lpc
  - size: 687 bytes
  - mtime: 1770312569.579784
- lib/objects/armor/shield.lpc
  - size: 313 bytes
  - mtime: 1770394819.5808349

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/single/shield.lpc lib/objects/armor/shield.lpc`

## sword.lpc
- lib/single/sword.lpc
  - size: 660 bytes
  - mtime: 1770312569.579784
- lib/objects/weapons/sword.lpc
  - size: 317 bytes
  - mtime: 1770394819.5808349

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/single/sword.lpc lib/objects/weapons/sword.lpc`

## vibro_blade.lpc
- lib/single/vibro_blade.lpc
  - size: 981 bytes
  - mtime: 1770312569.579784
- lib/objects/weapons/vibro_blade.lpc
  - size: 750 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u lib/single/vibro_blade.lpc lib/objects/weapons/vibro_blade.lpc`

## combat.h
- src/combat.h
  - size: 4740 bytes
  - mtime: 1771213056.1038613
- lib/include/combat.h
  - size: 7332 bytes
  - mtime: 1770312569.5757837

Recommendation: MANUAL REVIEW - choose canonical file and merge or remove.

Command to diff: `diff -u src/combat.h lib/include/combat.h`
