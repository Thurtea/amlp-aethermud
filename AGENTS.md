AI Agent Rules for AetherMUD
=================================

These rules are read by AI coding assistants (Copilot, Claude Code, etc.) before making changes.
Follow them strictly.


RULE 1 — NO COLOR CODES
- Do not add ANSI color codes (`\033[`, `\e[`, `\x1b[`) to anything unless explicitly instructed.
- This includes build scripts, `Makefile`, `mud.sh`, server logs, warmboot output, error messages, help text, admin tool output, and all in-game messages.
- The ONLY approved uses of color are:
  - WHO command: staff per rank shown in red for admins, blue for domains and coding, and green for roleplay. creators that are apprentices yet to become any position will be cyan.
  - Room exits: shown in green
  - Player-to-player tells and wizard tells


RULE 2 — src/ vs lib/ separation
- `src/` contains the C driver engine. `lib/` contains all LPC game code.
- All LPC library files use the `.lpc` extension, NOT `.c`. When searching for lib files, always grep for `*.lpc`, not `*.c`.
  Example: `grep -rn 'foo' lib/cmds/*.lpc` not `lib/cmds/*.c`
- New commands and game logic should be written as LPC files in `lib/cmds/` where possible.
- EXCEPTION — C commands are the correct choice when:
  a) The data needed lives only in a C struct (e.g. `ch->alignment`, `ch->privilege_level`, stat arrays) and no efun exposes it to LPC, OR
  b) The operation requires direct session/VM manipulation that cannot be done from LPC.
  In these cases, add a C function in `src/chargen.c` or `src/driver.c`, register it in the command dispatch, and declare it in the appropriate header. Do NOT waste time trying to work around missing efuns in LPC when the data is C-only.
- The long-term goal is to expose more C data via efuns so LPC commands can access it, but do not block a fix on that goal.
- Do not introduce new game logic (combat formulas, world state, skill definitions) into `src/`.


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


RULE 7 — Never remove existing game mechanics
- If a bug report describes unexpected output (e.g. "players show as A <race>"), diagnose WHY before touching the code.
- The system producing that output may be an INTENTIONAL game mechanic (e.g. the introduction system where unintroduced players appear as "A <race>").
- Do NOT remove or gut an existing system just because its output appears in a bug report.
- First ask: "Is this system supposed to exist? Could the bug be upstream (wrong data, missing sync, privilege level bug)?" 
- If you are unsure whether a system is intentional, ASK before changing it.
- Examples of mechanics that must not be removed without explicit instruction:
  - Introduction system (players appear as "A <race>" until introduced)
  - Any command, daemon, or LPC object that was present in the codebase before this session
RULE 8 — Never run git commands
- Do not run git add, git commit, git push, git pull, git rebase, or any other git command.
- The developer handles all version control operations manually.
- You may READ git status or git diff for diagnostic purposes only.

RULE 9 — No server management commands
- Do not run ./mud.sh, start/stop/restart the server, or interact with the running process in any way.
- The developer starts, stops, and tests the server manually using Mudlet.
- Your job is to write and fix code only.


Keep edits concise, reversible, and respectful of the engine/game split described above.


KNOWN VM BUG: sizeof() returns 1 for arrays returned by explode().
DO NOT use explode() + sizeof() pattern anywhere in LPC.
Use strsrch() + substring() for string splitting instead.
See: lib/obj/wiztools/qcs_tool.lpc for working pattern.
