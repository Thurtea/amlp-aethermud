AI Agent Rules for AetherMUD
=================================

These rules are read by AI coding assistants (Copilot, Claude Code, etc.) before making changes.
Follow them strictly.

RULE 1 — NO COLOR CODES
- Do not add ANSI color codes (`\033[`, `\e[`, `\x1b[`) to anything unless explicitly instructed.
- This includes build scripts, `Makefile`, `mud.sh`, server logs, warmboot output, error messages, help text, admin tool output, and all in-game messages.
- The ONLY approved uses of color are:
  - WHO command: staff rank shown in red
  - Room exits: shown in green
  - Player-to-player tells and wizard tells

RULE 2 — src/ vs lib/ separation
- `src/` contains C engine code only. No game logic belongs in `src/`.
- `lib/` contains all LPC game code: commands, daemons, rooms, objects, help files.
- Commands currently hardcoded in `src/driver.c` should be migrated over time to `lib/cmds/` as LPC files; do not introduce new game logic into `src/`.

RULE 3 — No automated testing
- Never connect to the running server to test. Never read player save files.
- Never use `nc`, `telnet`, `curl`, or any automated login or scripted interaction against the server.
- Developer testing is done manually in Mudlet; respect that workflow.

RULE 4 — Passwords
- Never read, log, display, copy, or use player password hashes for any reason.

RULE 5 — No unsolicited features
- Do not add features, commands, help text, items, or content that was not explicitly requested.
- Do not rename existing files, public symbols, or functions without explicit approval.

RULE 6 — Report before changing
- For any task that will touch more than 3 files, list exactly what you plan to change and wait for explicit confirmation before making changes.

Keep edits concise, reversible, and respectful of the engine/game split described above.
