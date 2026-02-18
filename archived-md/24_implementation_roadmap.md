## Implementation Roadmap — Summary & Next Steps

Generated: 2026-02-16

## Issues Identified

1. Room Display (19_room_display_fixes.md)
   - Status: Analysis complete
   - Fix complexity: Medium
   - Priority: High (affects UX)

2. Get/Drop All (20_get_drop_all_implementation.md)
   - Status: Already implemented, needs safety improvements
   - Fix complexity: Low
   - Priority: Medium

3. Staff Castle & Spike NPC (21_staff_castle_status.md)
   - Status: Partially broken (force_me issues)
   - Fix complexity: Medium
   - Priority: Medium

4. Promotion Teleport (22_promotion_teleport_plan.md)
   - Status: Not implemented
   - Fix complexity: Low
   - Priority: High (important feature)

5. Editor System (23_editor_and_paths.md)
   - Status: Exists but not exposed as command
   - Fix complexity: Low
   - Priority: Low

## Recommended Implementation Order

Priority 1 (Do First):
- Fix promotion teleport (easy win)
- Fix room display verbose mode

Priority 2 (Next Session):
- Fix Spike NPC `force_me` calls
- Add safety checks to `get all` / `drop all` paths

Priority 3 (Future):
- Expose `ed` command for wizards (or add a safe in-game editor)
- Complete remaining staff castle area sanity checks and polish

## Git Workflow Recommendation

For each fix, follow this process:

1. Create a feature branch
   - Branch naming suggestion: `feature/<issue-short>-YYYYMMDD` (example: `feature/promo-teleport-20260216`).
2. Implement the fix on the feature branch
   - Keep changes focused and minimal.
3. Test locally
   - Rebuild and restart the driver with: `./mud.sh rebuild && ./mud.ctl restart`
   - Exercise the change in-game and review `lib/log/server.log` for errors.
4. Document in the commit message
   - Reference the archived analysis file (e.g., `archived-md/19_room_display_fixes.md`) and describe the behaviour change and any new public-facing text.
5. Push the branch and open a review PR
   - Run a peer review and once verified, merge to `main`.

Notes & Safety
- Do NOT apply changes directly to `main`. Use feature branches and PR reviews to reduce risk.
- Create small, easily testable commits so rollbacks are simple if needed.
- When changing text rendering (room/display), test variations (brief/verbose, living vs non-living items) to avoid regressions.

## Next Actions (suggested immediate steps)

- Implement the promotion teleport patch (Priority 1) on a short-lived feature branch and smoke-test.
- Implement the room-display rendering helper to control introduction lines and article insertion; run interactive tests.

Do NOT execute any changes as part of this roadmap: this document only summarizes findings and prescribes the safe workflow to apply them.

*** End of file
