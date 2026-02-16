# AetherMUD QUICKSTART

Reset (clean to first-admin)

```bash
./mud.ctl stop
./mud.sh rebuild
echo "WIPE ALL" | ./mud.sh wipe-all
./mud.ctl start
# then connect: telnet localhost 3000
```

Normal operations
- Start: `./mud.ctl start`
- Stop: `./mud.ctl stop`
- Status: `./mud.ctl status`
- Tail log: `./mud.ctl log` or `tail -f lib/log/server.log`
- Rebuild driver: `./mud.sh rebuild` (or `./mud.sh build` / `make driver`)

Troubleshooting tips
- Orphaned/stale PID:
  - If `./mud.ctl stop` reports no PID but the port is bound, find and kill the listener:

```bash
ss -ltnp | grep :3000
# or
lsof -iTCP:3000 -sTCP:LISTEN
sudo kill -TERM <PID>
```

- Port conflicts:
  - Ensure no other service binds 3000. If occupied, find process and stop it, or change `DEFAULT_PORT` in `mud.ctl`.

- Multiple PID/log files present:
  - `mud.ctl` and `mud.sh` use different defaults (`mud.pid` + `lib/log/server.log` vs `logs/driver.pid` + `logs/driver.log`).
  - Prefer one control script for operations or standardize the paths by editing the scripts.

- Rebuild warnings:
  - Warnings appear during build; check `diagnostics/` for details if failures arise.
