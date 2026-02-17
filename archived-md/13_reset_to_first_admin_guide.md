 # Reset to First Admin - AetherMUD

Prerequisites
- Driver built and executable (see `build/driver` or `driver`).
- Scripts executable: `./mud.ctl`, `./mud.sh` (run `chmod +x mud.ctl mud.sh`).
- You have a working shell in the project root.

5-step reset process
1. Stop the server:

```bash
./mud.ctl stop
```

2. Rebuild the driver (clean + build):

```bash
./mud.sh rebuild
```

3. Wipe all data (this deletes all player/wizard/workroom/save files).
- When prompted, type exactly: `WIPE ALL` and press Enter.

```bash
echo "WIPE ALL" | ./mud.sh wipe-all
```

4. Start the server:

```bash
./mud.ctl start
```

5. Connect to the telnet port (default 3000) and complete the first-time setup/wizard.
- Example: `telnet localhost 3000` or `nc localhost 3000`.

Verification checklist
- **Binary exists:** `build/driver` (or `driver`) is executable.
- **PID file created:** `mud.pid` or `logs/driver.pid` appears after start.
- **No save files remain:** `find save lib/save data -name "*.o" -o -name "*.dat"` returns 0.
- **Driver started:** server log contains startup messages and a PID was recorded.
- **First-time wizard:** connect to port 3000 and confirm the character/first-admin creation flow appears. If the driver log does not include an explicit "first setup" string, connect manually and verify the wizard.

Notes
- `./mud.ctl` and `./mud.sh` use different default PID/log locations (see results in archived-md/13_reset_to_first_admin_results.md). Pick one script as your canonical control script or standardize the paths if desired.
