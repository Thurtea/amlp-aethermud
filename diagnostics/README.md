# Diagnostics: ANSI Color Output Debugging (2026-02-18)

## Issue
- `send_ansi()` integration caused room look() crashes and raw `\033[1;34m` color codes to persist after warmboot.
- Suspected issues: efun not exported, or driver/LPC mismatch.

## Temporary Fixes
1. **lib/secure/master.lpc**: Patched with `nomask string efun_send_ansi(string s) { return s; }` (passthrough, disables C-level conversion).
2. **lib/std/room.lpc**: Patched `look()` to use `write(query_long() + "\033[0m")` directly (bypasses send_ansi).
3. **src/server.c**: No `register_efun` for `send_ansi` found—driver may not export it as an efun.

## Test
- Use: `eval write("\033[1;34mTEST\033[0m")` in-game. If output is blue, ANSI is working.
- If not, driver or client may not support ANSI, or further C/LPC integration is needed.

## Next Steps
- Re-enable C-level `send_ansi` only after confirming efun export and driver support.
- Remove passthrough and restore integration once stable.

---
2026-02-18
