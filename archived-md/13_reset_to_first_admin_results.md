Reset & First-Admin Test Results
Date: 2026-02-16

Commands run (captured output) and status

1) `./mud.ctl status`
Output: Server is not running
Result: ✅ (expected before start)

2) `./mud.ctl stop`
Output: Server not running (no PID file)
Result: ✅ (no server running)

3) `echo "WIPE ALL" | ./mud.sh wipe-all`
Output:
WARNING: This will DELETE ALL save files (players, wizards, rooms, workrooms)!
Wiping all saves...
All saves wiped
Result: ✅ (wipe completed)

4) `find save lib/save data -type f \( -name "*.o" -o -name "*.dat" \) | wc -l`
Output: 0
Result: ✅ (no save files found)

5) `./mud.sh rebuild`
Output (summary): BUILD SUCCESSFUL — Files compiled: 33 — Warnings: 99 — Errors: 0
Result: ✅ (rebuild succeeded; note many warnings: diagnostics/README.md)

6) `./mud.ctl start`
Output: Starting AMLP-MUD server on port 3000...
Server started successfully (PID: 29576)
Log file: /home/thurtea/amlp-aethermud/lib/log/server.log
Result: ✅ (server process started and log path printed)

7) `tail -20 logs/driver.log | grep -i "first.*setup"`
Output: (no matching lines)
Result: ⚠️ — No explicit "first setup" string found in the last 20 lines of `logs/driver.log`.
 - This does not necessarily mean the first-admin wizard won't appear on connect; it means the driver did not write a recognizable "first setup" line to `logs/driver.log` in that tail window. Connect manually to port 3000 to verify the wizard.

Path consistency checks

PID files present:
- `amlp_driver.pid` (modified Feb 6)
- `mud.pid` (modified Feb 16)

Log files found:
- `lib/log/server.log` (2.8M)
- `logs/driver.log` (76K)
- several other logs in `logs/` and `lib/log/`

Driver binary:
- `build/driver` exists and is executable

Master files:
- `lib/master.lpc` present
- `lib/secure/master.lpc` present

Script path analysis
- `./mud.ctl` (script) defaults to:
  - PID: `./mud.pid`
  - Log: `./lib/log/server.log`
  - Server binary: `build/driver`

- `./mud.sh` (script) defaults to:
  - PID: `logs/driver.pid`
  - Log: `logs/driver.log`
  - Server binary: `./build/driver` or fallback `./driver`

Conclusion on paths: mud.ctl and mud.sh use different default PID and log locations (mud.pid + lib/log/server.log vs logs/driver.pid + logs/driver.log). Both reference `build/driver` as the primary binary location (mud.sh allows `./driver` fallback). This explains multiple PID files present and multiple log files — choose one script (or standardize paths) to avoid confusion.

Recommended quick checks after reset
- If start reports success but you do not see expected first-admin prompts, connect with:
  - `telnet localhost 3000` or `nc localhost 3000`
- If server appears started but port is in use or stale, check listeners:
  - `ss -ltnp | grep :3000` or `lsof -iTCP:3000 -sTCP:LISTEN`

Canonical master object
- The canonical master object used for runtime is `lib/secure/master.lpc` (this is the file `mud.ctl` passes to the driver on startup). Keep `lib/master.lpc` present for reference; it appears to be a legacy or lightweight copy used historically by parts of the codebase.

Why two master files exist
- Historically the repository contained both `lib/master.lpc` (a small/legacy file) and `lib/secure/master.lpc` (the fuller, current secure master). This duplication likely persisted during iterative development and refactors. Plan a careful review before removing or consolidating `lib/master.lpc` to avoid losing compatibility or customizations.
