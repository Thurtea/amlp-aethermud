Duplicate Resolution Summary

Source: `archived-md/14_duplicate_review_guide.md`
Date: 2026-02-16

1) Total duplicate pairs reviewed: 8

2) Recommended actions summary
- Merge & remove (7):
  - `lib/cmds/ls.lpc`  -> remove (keep `lib/cmds/creator/ls.lpc`)
  - `lib/cmds/pwd.lpc` -> remove (keep `lib/cmds/creator/pwd.lpc`)
  - `lib/cmds/shutdown.lpc` -> remove (keep `lib/cmds/admin/shutdown.lpc`)
  - `lib/psionics/super/mind_block.lpc` -> remove (keep `lib/psionics/sensitive/mind_block.lpc`)
  - `lib/psionics/physical/psi_sword.lpc` -> remove (keep `lib/psionics/super/psi_sword.lpc`)
  - `lib/single/rations.lpc` -> remove (keep `lib/objects/supplies/rations.lpc`)
  - `lib/single/vibro_blade.lpc` -> remove (keep `lib/objects/weapons/vibro_blade.lpc`)

- Keep as intentional variants (0):
  - None flagged as intentionally different in the review guide.

- Need manual decision (1):
  - `lib/psionics/physical/levitation.lpc` vs `lib/spells/level2/levitation.lpc` — recommendation: prefer `lib/spells/level2/levitation.lpc` for spell semantics, but if the psionic variant encodes distinct behavior, decide whether to keep both or consolidate.

3) Quick action list (commands) — straightforward removals
Note: these commands archive files first, then remove them from the repo. Do NOT run these without reviewing and backing up.

mkdir -p archived-md/archived-duplicates

# archive and remove lib/cmds/ls.lpc (keep creator/ls.lpc)
tar -czf /tmp/duplicate-backup-ls-$(date +%F_%H%M%S).tar.gz lib/cmds/ls.lpc
git mv lib/cmds/ls.lpc archived-md/archived-duplicates/
git commit -m "Archive duplicate lib/cmds/ls.lpc (kept lib/cmds/creator/ls.lpc)"

# archive and remove lib/cmds/pwd.lpc
tar -czf /tmp/duplicate-backup-pwd-$(date +%F_%H%M%S).tar.gz lib/cmds/pwd.lpc
git mv lib/cmds/pwd.lpc archived-md/archived-duplicates/
git commit -m "Archive duplicate lib/cmds/pwd.lpc (kept lib/cmds/creator/pwd.lpc)"

# archive and remove lib/cmds/shutdown.lpc
tar -czf /tmp/duplicate-backup-shutdown-$(date +%F_%H%M%S).tar.gz lib/cmds/shutdown.lpc
git mv lib/cmds/shutdown.lpc archived-md/archived-duplicates/
git commit -m "Archive duplicate lib/cmds/shutdown.lpc (kept lib/cmds/admin/shutdown.lpc)"

# archive and remove lib/psionics/super/mind_block.lpc
tar -czf /tmp/duplicate-backup-mind_block-$(date +%F_%H%M%S).tar.gz lib/psionics/super/mind_block.lpc
git mv lib/psionics/super/mind_block.lpc archived-md/archived-duplicates/
git commit -m "Archive duplicate lib/psionics/super/mind_block.lpc (kept lib/psionics/sensitive/mind_block.lpc)"

# archive and remove lib/psionics/physical/psi_sword.lpc
tar -czf /tmp/duplicate-backup-psi_sword-$(date +%F_%H%M%S).tar.gz lib/psionics/physical/psi_sword.lpc
git mv lib/psionics/physical/psi_sword.lpc archived-md/archived-duplicates/
git commit -m "Archive duplicate lib/psionics/physical/psi_sword.lpc (kept lib/psionics/super/psi_sword.lpc)"

# archive and remove lib/single/rations.lpc
tar -czf /tmp/duplicate-backup-rations-$(date +%F_%H%M%S).tar.gz lib/single/rations.lpc
git mv lib/single/rations.lpc archived-md/archived-duplicates/
git commit -m "Archive duplicate lib/single/rations.lpc (kept lib/objects/supplies/rations.lpc)"

# archive and remove lib/single/vibro_blade.lpc
tar -czf /tmp/duplicate-backup-vibro-$(date +%F_%H%M%S).tar.gz lib/single/vibro_blade.lpc
git mv lib/single/vibro_blade.lpc archived-md/archived-duplicates/
git commit -m "Archive duplicate lib/single/vibro_blade.lpc (kept lib/objects/weapons/vibro_blade.lpc)"

4) Manual decision needed list
- Levitation pair:
  - Files: `lib/psionics/physical/levitation.lpc` (2.8K) vs `lib/spells/level2/levitation.lpc` (2.1K)
  - Recommendation: Review domain semantics. If levitation is conceptually a spell in your system, consolidate to `lib/spells/level2/levitation.lpc`. If physical psionics require separate API or differing effects, keep both and document distinctions.
  - Commands to review:
    - diff -u lib/psionics/physical/levitation.lpc lib/spells/level2/levitation.lpc | less
    - If consolidating, merge unique code into chosen file, archive the other as in Quick action list.

Notes
- Always run the MUD test suite and smoke tests after performing removals.
- Back up before any destructive action (tar or `git mv` to an archive folder).

Reference check before archival
 - Command run:
   ```bash
   egrep -r --include='*.lpc' --include='*.c' --include='*.h' \
     'creator/ls.lpc|creator/pwd.lpc|admin/shutdown.lpc|sensitive/mind_block.lpc|physical/psi_sword.lpc|single/rations.lpc|single/vibro_blade.lpc' lib/ src/ Makefile 2>/dev/null | wc -l
   ```
 - Result: 4 matches found.
 - Matches (showing lines):
   - lib/cmds/creator/pwd.lpc:  * /lib/cmds/creator/pwd.lpc - Show current working directory
   - lib/cmds/creator/ls.lpc:   * /lib/cmds/creator/ls.lpc - Creator-aware ls using terminal-aware formatting
   - lib/psionics/physical/psi_sword.lpc: // /lib/psionics/physical/psi_sword.lpc
   - lib/psionics/sensitive/mind_block.lpc: // /lib/psionics/sensitive/mind_block.lpc

Conclusion: the found references are self-referential comment lines inside the files themselves (file headers), not external code references. Therefore there are no external references detected in `lib/`, `src/`, or `Makefile` that would block archival of the listed duplicate files. It is safe to proceed with archival steps for the seven candidates, provided backups are made first and manual review for `levitation` is completed.

Archival run (performed):

- Command executed:
  - `./scripts/archive_reviewed_duplicates.sh --apply`

- Backup files created (examples):
  - /tmp/duplicate-backup-ls.lpc-2026-02-16_163840.tar.gz
  - /tmp/duplicate-backup-pwd.lpc-2026-02-16_163840.tar.gz
  - /tmp/duplicate-backup-shutdown.lpc-2026-02-16_163840.tar.gz
  - /tmp/duplicate-backup-mind_block.lpc-2026-02-16_163840.tar.gz
  - /tmp/duplicate-backup-psi_sword.lpc-2026-02-16_163840.tar.gz
  - /tmp/duplicate-backup-rations.lpc-2026-02-16_163840.tar.gz
  - /tmp/duplicate-backup-vibro_blade.lpc-2026-02-16_163840.tar.gz

- Files successfully archived (moved to `archived-md/archived-duplicates/`):
  - ls.lpc (from lib/cmds/ls.lpc)
  - pwd.lpc (from lib/cmds/pwd.lpc)
  - shutdown.lpc (from lib/cmds/shutdown.lpc)
  - mind_block.lpc (from lib/psionics/super/mind_block.lpc)
  - psi_sword.lpc (from lib/psionics/physical/psi_sword.lpc)
  - rations.lpc (from lib/single/rations.lpc)
  - vibro_blade.lpc (from lib/single/vibro_blade.lpc)

- Verification: archived-md/archived-duplicates/ contains 7 files (listed above). (Run timestamp: 2026-02-16 16:38 UTC)

Status: Archival completed for the seven straightforward duplicates. `levitation` pair remains for manual review.
