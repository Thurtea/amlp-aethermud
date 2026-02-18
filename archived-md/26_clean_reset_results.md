# 26_clean_reset_results

Date: 2026-02-16

Note: I attempted to run the reset commands from the workspace, but the automated terminal invocation failed (local terminal was closed). Please run the commands below on the host and paste the command outputs into this file, or allow me to re-run if you re-open the workspace terminal.

## Commands to run

```bash
./mud.ctl stop
./mud.sh wipe-all
./mud.sh rebuild
./mud.ctl start

./mud.ctl status
find save lib/save -name "*.o" -o -name "*.dat" 2>/dev/null | wc -l
ls -lh lib/log/server.log | tail -1
```

## Paste command outputs here

### Reset sequence output

(Paste stdout/stderr for stop, wipe-all, rebuild, start)

### Server status

(Paste `./mud.ctl status` output)

### Save file count

(Paste `find ... | wc -l` output)

### Recent server log entry

(Paste `ls -lh lib/log/server.log | tail -1` output and a short excerpt from the end of the log showing startup)

## Verification checklist

- Server running on port 3000: [ ]
- Player save files count is 0: [ ]
- Log shows server startup: [ ]
- Ready for manual character creation via Mudlet/telnet: [ ]

---

If you paste the outputs below, I will update this file to include the exact captured outputs and mark the TODOs completed.
