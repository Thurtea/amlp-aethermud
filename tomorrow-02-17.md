Where we were
---------------
- Repo: `main` branch, recent commits up to `a6f332f7` pushed.
- Server: built cleanly and started (PID reported), port 3000 listening.
- Player saves: we wiped `lib/save/players` during verification; persistent character data was removed.
- Spike: NPC 'Spike' now spawns from `lib/domains/wizard/castle/dog_spike.lpc` (room id 1004).
- Help/description: help categories and `description` display were fixed; `setwhotitle` alias available.

What we did (today)
---------------------
- Cleaned up `.gitignore` and untracked `archived-md` (kept summary as requested).
- Added `query_available_commands()` to `lib/daemon/command.lpc` to filter visible commands by role.
- Created `scripts/verify_production.sh` and `docs/qcs_guide.md`.
- Patched `src/driver.c` (who output padding + help category fixes) and rebuilt driver.
- Implemented Spike as a real NPC (C-level NPC + room changes) and wired pet/feed/examine behaviors.
- Ran a production rebuild: stopped server, wiped saves, cleaned build, started server; verified logs show rooms/NPCs loaded and telnet/ws listeners.

Progress
---------
- Build: success, 33 files compiled, 0 errors, warnings remain (102 reported).
- Server: running on port 3000; logs show rooms and NPCs loaded (including Spike).
- Save wipe: player saves removed via `./mud.sh wipe-players` (confirmed in terminal logs).
- Help & QCS: help categories limited for players; QCS templates and creator tooling in place.

Next likely steps (priority)
----------------------------
1. Run manual playtest sequence (promote → qcs → falconry → spike pet → help → description) and record failures.
2. Verify `ed`/editor integration and make sure `ed` / `qed` behave as expected (compare to `mud-references/deadsouls/.../lib/lib/editor.c`).
3. Address driver warnings (102) where practical; focus on anything that affects runtime stability.
4. Run `scripts/verify_production.sh` and capture/report outputs.
5. Decide whether to purge `archived-md` from git history (destructive) — prepare `git filter-repo` or BFG plan if desired.

Quick commands to continue tomorrow
----------------------------------
 - Start server/tests:
   ./mud.sh start
   sleep 3
   ./mud.ctl status

 - Run verification tail/log checks:
   tail -20 lib/log/server.log | grep -E "Loaded|Character|Started|Errors" || tail -20 lib/log/server.log

 - Playtest checklist (interactive): promote -> create/deploy QCS -> test falconry -> pet Spike -> `help` topics -> `description` change

Notes
-----
- Save paths: player saves live under `lib/save/players/*.dat` and driver references these when loading characters.
- Repo hygiene: current `.gitignore` is set to ignore `archived-md/` while whitelisting the single `archived-md/summary-02-17.md` when needed.

Files of interest (review next):
- `src/driver.c` — who formatting, help command
- `lib/daemon/command.lpc` — `query_available_commands()`
- `lib/domains/wizard/castle/dog_spike.lpc` and new NPC template files
- `scripts/verify_production.sh`, `docs/qcs_guide.md`

If you want, I can commit this file and push it now. 
