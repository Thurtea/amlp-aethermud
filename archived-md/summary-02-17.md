2026-02-17 — Development Summary

Short summary of work completed and next steps.

- Changes applied:
  - Normalized room/item formatting in `src/room.c` to use lowercase articles and preserve acronyms/proper nouns.
  - Added item name formatter for C-bootstrap rooms.
  - Normalized NPC template name for Moxim in `src/npc.c` so spawns and logs use the canonical name.

- Build & deploy:
  - Driver built successfully (`make driver`): 33 files compiled, 113 warnings, 0 errors.
  - Changes committed and pushed to remote (commit: 2026-02-17: Normalize room/item formatting; normalize NPC template name; update room listing).
  - Player saves were wiped per instructions during the test run; server restarted and confirmed spawning NPCs.

- Pending (user-priority order):
  1) Remove blue "[Staff]" coloring → plain white text.
  2) Chargen: change O.C.C.: None → O.C.C.: Pending.
  3) Add pskills / sskills commands.
  4) Expand update command permissions to wizards.
  5) WHO format: prefix role label (e.g., [Admin] Thurtea).

- Next actions suggested:
  - Implement pending item (1) and rebuild/restart to verify.
  - Iterate through items 2–5 in order, rebuilding and testing after each change.
  - Once finished, finalize this archive and mark todos complete.

Recorded by automation on 2026-02-17.