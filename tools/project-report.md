# AMLP-AetherMUD — tools/ Project Report

Date: 2026-02-23

## Directory Purpose

`tools/` contains developer utilities, small scripts, and helper programs used for building, testing, auditing, and integrating the mudlib and driver. These are not part of runtime delivery but assist maintainers during development and cleanup.

## File Inventory and Purpose

- `build_ui.sh` — styled build wrapper that compiles individual `src/*.c` files to `build/*.o`, links `build/driver`, and prints a colored summary. Useful for developer feedback; warns/errors parsed from `gcc` output.
- `check_helpfiles.py` — scans `lib/` for a list of expected helpfile names and writes a `data/helpfile_scan_report.txt` listing found/missing helpfiles.
- `debug_commands.lpc` — LPC helpers (not opened) — likely contains debug-only command implementations or utilities.
- `generate_expanded_chargen.py` — data generation script (not opened) used to expand or normalize chargen data.
- `minimal_stubs.txt`, `stub_inventory.txt`, `stub_json_matches.txt`, `stub_json_expanded_matches.txt`, `stub_summary.txt` — text artifacts produced by stub-detection tooling; used for migration/cleanup.
- `rcc_audit.tsv` — audit output (TSV) for RCC/Racial Character Class checks.
- `test_execution.sh` — basic execution test harness (not opened) to run some tests or launch quick checks.
- `test_library_integration.sh` — integration script that (currently) refers to hardcoded paths (`/home/thurtea/amlp-driver`, `/home/thurtea/amlp-library`) to compile and test driver+library; will fail on other checkouts without path changes.
- `test-commands.sh` — telnet-driven command smoke test (also present in `scripts/`); duplicate functionality across directories.
- `vm_trace.c` — C helper for VM tracing (low-level trace tool; buildable into debug helpers).
- `ws_client.html` — simple browser client for WebSocket telnet proxy — useful for testing the proxy frontend.
- `ws_telnet_proxy/` — small proxy project (Node and Python variants):
  - `index.js` — Node.js WebSocket->Telnet proxy (requires `ws` package); listens on `WS_PORT` env or 3001 and forwards to telnet host/port.
  - `package.json` — Node package manifest (dependency on `ws`).
  - `proxy.py` — Python asyncio WebSocket->Telnet proxy (requires `websockets` package). Prefer this for Python environments.

## Working vs Broken vs Risky

- Working / Useful:
  - `check_helpfiles.py` — self-contained, writes clear report.
  - `build_ui.sh` — works if `gcc` is available and source layout matches `src/`.
  - `ws_telnet_proxy/index.js` and `proxy.py` — both implement functional WS->Telnet proxies; require installing `ws` (npm) or `websockets` (pip).

- Risky / Hardcoded Paths / Requires Fixes:
  - `test_library_integration.sh` uses absolute paths (`/home/thurtea/...`) and references `./build/driver` inside those directories; update to repo-relative paths or environment variables.
  - `build_ui.sh` and other shell scripts embed ANSI color codes and rely on `gcc -std=c99 -Werror` — the build can fail if code has warnings; might be too strict for development builds.
  - Duplicate test scripts exist in `scripts/` and `tools/` (`test-commands.sh`) — consolidate to avoid drift.

- Missing Dependencies:
  - Node proxy requires `npm install` to fetch `ws` (see `package.json`).
  - Python proxy requires `websockets` package.
  - `build_ui.sh` requires `gcc` and POSIX tools (`find`, `ls`).

## Observations / Issues Found

- Several scripts across `scripts/` and `tools/` hardcode user-specific paths (`/home/thurtea/...`) which will fail for other contributors. Prefer deriving `REPO_ROOT` dynamically.
- `build_ui.sh` prints colored output; AGENTS.md prohibits ANSI color codes in certain parts of the game — these are acceptable for developer tools, but avoid injecting colors into runtime logs collected by the server.
- `test_library_integration.sh` claims VM/Executor is not implemented (commented marker), which explains why full runtime testing can't be completed by that script.

## Next Steps / Recommendations

1. Replace absolute paths in `test_library_integration.sh` with repo-relative variables, e.g. `REPO_ROOT=$(cd "$(dirname "$0")/.." && pwd)`.
2. Consolidate duplicate test scripts between `scripts/` and `tools/` into a single `scripts/` location and deprecate duplicates with a README pointer.
3. Document required packages for proxies (`npm install` for Node, `pip install websockets` for Python) in `tools/README.md` and add small `tools/setup.sh` to install optional dev deps.
4. Consider adding `--no-color` or `TERM`-sensitive behavior to `build_ui.sh` so CI logs remain parseable and free of ANSI escapes if needed.
5. Add a linting pass or pre-check that warns on absolute hardcoded paths and environment assumptions before running integration scripts.

---
Saved as `tools/project-report.md`.
