# AMLP-AetherMUD — src/ Project Report

Date: 2026-02-23

## Directory Purpose

`src/` contains the C driver implementation: the lexer, parser, compiler/codegen, bytecode virtual machine, efuns (built-in functions), GC, object system, server and runtime support. This is the engine layer (C) — game logic and LPC files belong in `lib/`.

## File Inventory (top-level files)

- `lexer.c`, `lexer.h` — tokenizes LPC source, supports identifiers, numbers, strings, operators, array/mapping literals, comments and `#` lines.
- `parser.c`, `parser.h`, `parser_state.h` — recursive-descent parser producing an AST (Program/Function/Statement/Expression nodes), basic error recovery and AST printing.
- `preprocessor.c`, `preprocessor.h` — preprocessor to handle includes/defines before lexing.
- `compiler.c`, `compiler.h`, `compile_stubs.c` — compilation front-end and glue used by efun object loaders.
- `codegen.c`, `codegen.h` — AST → VM bytecode emitter, symbol table, labels/patching, and function registration with the VM.
- `vm.c`, `vm.h` — stack-based virtual machine with call frames, local/parameter layout, value model and instruction dispatch.
- `efun.c`, `efun.h` — efun registry and built-in functions bridging LPC calls to C runtime (strings, arrays, mappings, files, objects, debug, etc.).
- `object.c`, `object.h` — C object model (methods, properties, environment, prototype/clone support).
- `program.c`, `program.h`, `program_loader.c` — Program representation and loader that turns Program into VM functions and attaches them to objects.
- `gc.c`, `gc.h` — GC and memory bookkeeping.
- `array.c`, `array.h`, `mapping.c`, `mapping.h` — container implementations used by the VM.
- `driver.c`, `server.c`, `session.c`, `websocket.c`, `terminal_ui.c` — server entrypoint, networking, session management, and terminal UI.
- Gameplay helpers: `wiz_tools.c`, `chargen.c`, `skills.c`, `combat.c`, `item.c`, `psionics.c`, `magic.c`, `room.c`, `npc.c`, `race_loader.c` — high-level systems that integrate engine and lib/ objects.
- `simul_efun.c` — simulated efuns compatibility layer.
- `test_stubs.c` — test helpers.

## Pipeline Architecture

- Preprocess: `preprocessor.c` normalizes includes/defines.
- Lex: `lexer.c` tokenizes the source buffer into tokens (handles `({` array and `([` mapping forms).
- Parse: `parser.c` builds an AST with functions, declarations, statements, expressions, and handles `inherit` paths.
- Codegen: `codegen.c` walks AST and emits VM instructions, manages symbol tables, labels, and compiles functions into `VMFunction` entries registered with the VM.
- VM: `vm.c` executes bytecode, implements the stack, call frames, local/parameter allocation, efun dispatch, and integrates GC and value types.
- Efuns: `efun.c` exposes runtime services (I/O, file access, object management, arrays/mappings, debug helpers) and implements object loading (`load_object`, `clone_object`) by invoking the compiler and `program_loader`.

The design is conventional for a small bytecode VM and matches the expected LPC pipeline: source -> preprocess -> tokens -> AST -> bytecode -> VM execution with efuns providing runtime primitives.

## Subsystems: Status Summary

- Lexer: Working — supports key LPC token forms and array/mapping literal markers.
- Parser: Working for standard constructs (functions, blocks, expressions, foreach, switch). Error recovery is basic but present.
- Preprocessor: Present but limited — assumptions in parser indicate some preprocessor expectations.
- Codegen: Largely functional — emits expected instructions, handles control flow and function registration.
- VM: Working core dispatch and value model; contains diagnostic/debugging instrumentation. VM includes fixes/patches for frame allocation and load/store local bounds checks (comments indicate previously discovered bugs were addressed in code comments).
- Efuns: Broad set implemented and registered; many common efuns (string/array/mapping/object/file/math/debug) available. Several are stubs or simplified (see Missing LPC features).
- Object system & program loader: Implemented; `efun_load_object` / `efun_clone_object` compile LPC into VM functions and attach them to `obj_t` instances. Parent/child inheritance is handled by loading parent programs and attaching methods (with `__parent__` prefix strategy).
- Server/session/websocket: Present but coupling between sessions and efuns (e.g., `this_player`, session messaging) appears partial and requires runtime testing.

## Missing LPC Features, Stubs and Behavioral Gaps

- `find_call_out` returns -1.0 (unimplemented stub).
- `users()` returns an empty array (session tracking not exposed to efuns fully).
- `sscanf` is a simplified implementation that uses a global `__sscanf_result()` accessor rather than true pass-by-reference semantics.
- Some expected LPC efuns are present as limited wrappers (e.g., `printf`, `write` fall back to stdout if no session found) — ergonomics for multi-user sessions may be incomplete.
- Preprocessor macro behaviors and includes might not fully match complex LPC code; the preprocessor implementation should be validated against the mudlib.

## TODOs and FIXMEs (found in source)

- `driver.c`: "TODO: Call destruct on player object when object system ready" — cleanup lifecycle incomplete.
- `driver.c`: "TODO: Shout to adjacent rooms (requires room linkage)" — room linking for broadcasts incomplete.
- `driver.c`: plaintext password storage noted: "TODO: Use proper bcrypt" at two sites (dev placeholder storing plaintext).
- `death.c`: "TODO: hook into LPC corpse creation. For now, log and notify room." — death/corpse behavior not integrated with LPC corpse objects.
- `wiz_tools.c`: "TODO: Implement output via session system" — wizard tools output not fully using session APIs.
- `efun.c`: `efun_find_call_out` explicitly marked "Not implemented: return -1.0".

These TODOs indicate a mix of feature work (room broadcasts, corpse creation), security hardening (password hashing), and integration work (session output wiring).

## Observed Risks and Notes

- Build produced many warnings in example `build.log` (117 warnings). While not fatal, they merit triage (some warnings may indicate type mismatches or platform-dependent behavior).
- VM had historical issues around call-frame allocation and local variable bounds; `vm.c` contains in-source fixes and defensive checks — this area is sensitive and should be covered by targeted tests.
- Efuns performing filesystem access use `resolve_safe_path()` with security checks, but these routines should be audited carefully for path traversal edge cases and permission behavior.
- AGENTS.md prohibits automated runtime testing against a live server in this repo; follow that when creating CI or test harnesses.

## Next Steps (actionable)

1. Run unit/compile tests locally (careful: per AGENTS.md avoid automated server connections). Targets: `make driver`, then `make tests` or selective `build/test_*` binaries to validate current behavior.
2. Triage warnings from `make driver` into critical vs cosmetic and fix high-severity issues (type errors, possible UB, memory problems).
3. Add or run targeted tests for VM frame/local behavior (call frames, param/local allocation, OP_LOAD_LOCAL/OP_STORE_LOCAL) to ensure frame bounds and refcount behavior are correct.
4. Implement or improve efun session wiring: ensure `write`, `tell_object`, `tell_room`, `users()` are consistent with the session manager and `session.c` APIs.
5. Replace plaintext password handling in `driver.c` with secure hashing (bcrypt/argon2), and ensure no password hashes are exposed per AGENTS.md.
6. Expand `sscanf` to a safer and more complete implementation or document limitations clearly for mudlib authors.
7. Document the canonical control path for object loading, and add small examples/tests in `tests/` that compile and run simple LPC files under the VM (without connecting clients).

---
Generated by static inspection of `src/` on 2026-02-23. Saved as `src/project-report.md`.
