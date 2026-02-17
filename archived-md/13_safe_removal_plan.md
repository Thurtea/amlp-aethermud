Safe Removal Plan (dry-run)

Date: 2026-02-16

Summary
- Script run: ./scripts/remove_safe_duplicates.sh (dry-run mode)
- Result: No files are currently listed as safe to remove in the script, so nothing will be deleted.

1) Files the script will remove
- None. The SAFE_FILES array in scripts/remove_safe_duplicates.sh is empty, so the dry-run reports "No safe duplicate files listed. Nothing to remove." If you want to remove specific safe duplicates, add their paths to the SAFE_FILES array in the script.

2) Verification that none are referenced in Makefile or active code
- No files are scheduled for removal, so no reference checks were required.
- If you add files to SAFE_FILES, run these checks before applying removal:

  grep -R --line-number -- "path/to/file.lpc" Makefile src lib || true
  rg --hidden --no-ignore -n "path/to/file.lpc" || true

3) Estimated disk space freed
- 0 bytes (no files selected).

4) Backup location / safety
- Current scripts/remove_safe_duplicates.sh does not create backups. It simply deletes files when run with --apply.
- Recommendation: before applying removals, either:
  - Move files to an archived directory such as archived-md/archived-duplicates/ (recommended), or
  - Create a tarball backup: tar -czf /tmp/safe-duplicates-backup-$(date +%F_%H%M%S).tar.gz <list-of-files>

Next steps
1. Populate SAFE_FILES in scripts/remove_safe_duplicates.sh with the confirmed, identical files you want to remove.
2. For each candidate file, run quick reference checks (grep or rg) across the repo and in Makefile.
3. Create a backup tarball or move files to an archive directory.
4. Re-run the script with --apply to perform removals.
