# AMLP-AetherMUD — tests/ Project Report

Date: 2026-02-23

## Directory Purpose

`tests/` contains unit and integration tests for the driver and mudlib subsystems. It mixes C unit tests (compile-and-run), Python integration scripts (networked smoke tests), shell smoke tests, and auxiliary artifacts under `lpc/` for LPC execution tests.

## Test Inventory & What Each Covers

- `test_lexer.c` — C unit tests for the lexical analyzer (tokenization of LPC source).
- `test_parser.c`, `test_parser_stability.c` — parser unit tests and stability/regression checks for AST construction and error recovery.
- `test_compiler.c` — compiler front-end tests (AST → Program representation).
- `test_program.c` — tests Program structures and loaders.
- `test_codegen` (not present explicitly) — (no dedicated codegen-only test file found).
- `test_vm.c` — core VM unit tests for instruction handling and primitives.
- `test_vm_execution.c` — VM integration tests: compile LPC strings, load into VM, check functions and globals, decode bytecode (has a SKIP for entry_point due to parser limitation).
- `test_efun.c`, `test_simul_efun.c` — tests for efuns and simul_efun helper behavior.
- `test_gc.c` — GC-related unit tests (allocation/refcounting behaviors).
- `test_array.c`, `test_mapping.c` — container tests for arrays and mappings.
- `test_object.c` — object model tests (methods, properties, environment behaviors).
- `test_lpc_execution.c`, `lpc/` — LPC-level test cases / fixtures used by execution tests.
- `test_driver_stub.c` — driver-level stub tests (compile/run scaffolding without full runtime).
- `test_combat_system.py` — Python script exercising combat via networked connection (requires running server). Tests character creation, attack command, combat flow, flee, and score.
- `test_complete_systems.sh` — shell script for orchestrating system-level smoke tests (driver + library); likely requires runtime environment.
- `test_currency_shop.sh`, `test_wizard_tools.sh` — shell-based smoke tests for game features (shop/currency, wizard tools).
- `demo_ui.c` — demo UI test (C) for terminal/driver UI code.

## Subsystems with Tests vs None

- Well-covered (unit + integration):
  - Lexer, Parser, Compiler (unit tests present)
  - VM core & bytecode decoding (unit + integration)
  - Containers: arrays and mappings
  - GC (unit tests)
  - Object/program loaders (unit tests / integration)

- Integration / Networked tests present (but require running server):
  - Combat (`test_combat_system.py`), command smoke tests (`test-commands.sh`), equip flows (`test-equip.exp` in `scripts/`) — these are integration tests requiring a running driver and network connectivity.

- Sparse or missing direct tests:
  - Session manager, websocket handling, and terminal UI have no dedicated automated unit tests (proxies exist under `tools/` but not unit tests).
  - Persistent storage & save/load (master/save file semantics) have no explicit automated tests verifying persistence, file permissions, or atomic writes.
  - Security-sensitive areas (password hashing, valid_write policies) lack targeted tests.

## Test Status (passing / failing)

- I did not execute the tests in this environment; status is reported from static inspection only.
- Several tests include explicit skips or notes (e.g., `test_vm_execution.c` marks `entry_point` as SKIPPED due to parser limitation). Many C tests use custom test runners that return non-zero on failure; their pass/fail depends on building `build/driver` and compiling tests with compatible flags.
- Integration/network tests (`test_combat_system.py`, shell telnet scripts) will fail if the driver is not running or if prompts/flows differ from expectations.

Recommendation: run tests locally using a container or dev machine with `make` and prerequisites; example commands below.

Recommended run commands (run from repo root):

```sh
# build the driver (dev flags)
make clean && make

# compile and run a single C test (example)
gcc -I./src -I./src/include tests/test_array.c src/array.c src/gc.c -o build/test_array && ./build/test_array

# run VM execution integration (requires built src/ and link flags)
gcc -I./src tests/test_vm_execution.c src/*.o -o build/test_vm_execution && ./build/test_vm_execution

# run Python integration (requires running driver on localhost:3000)
python3 tests/test_combat_system.py
```

## Critical Gaps in Coverage

- No automated tests for: session management, networking edge cases (partial frames, telnet negotiation), save-file integrity, access-control (master policies), and password hashing behavior.
- Command coverage is partial: many commands in `lib/cmds/` are stubs; tests that exercise command behavior are present but require manual/integration runs — no unit tests for command parsing/dispatch.
- Websocket and browser-facing UI code (`tools/ws_telnet_proxy`, `ws_client.html`) have no automated tests.

## Next Steps (actionable)

1. Create a `Makefile` test target (`make test` or `make unit-tests`) to compile and run all C unit tests with deterministic flags and report TAP-style output.
2. Add CI job (GitHub Actions) that compiles and runs fast unit tests (lexer/parser/array/mapping/vm core) under AddressSanitizer to catch memory errors.
3. Add smoke-test harness that can run integration tests against a headless driver started in a controlled environment (use `--test-parse` or an isolated port), capturing outputs and tearing down cleanly.
4. Add tests for critical missing areas: session manager, save/load permission tests, and master `valid_write()` semantics.
5. Convert brittle telnet-based Python/shell tests to use the websocket proxy (or `pexpect`) with timeouts and clearer parsing so they are reliable in CI.

---
Saved as `tests/project-report.md`.
