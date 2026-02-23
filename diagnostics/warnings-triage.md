# Compiler Warnings Triage — AMLP AetherMUD
Date: 2026-02-23 (updated 2026-02-23 after MEDIUM-severity fixes)
Build: `make clean && make` (debug target, -Wall -Wextra -g -O0 -std=c99)
Total warnings: 102 → 93 (HIGH fixes) → **69** (MEDIUM fixes) | Total errors: 0
Raw output: `diagnostics/build-warnings.txt`

---

## Summary Table

| # | Category | Count | Severity | Files |
|---|----------|-------|----------|-------|
| 1 | Always-true NULL check on fixed-size array member | 42 | MEDIUM | driver.c, wiz_tools.c, chargen.c, combat.c, room.c |
| 2 | Signed/unsigned integer comparison [-Wsign-compare] | 8 → **0** | ~~HIGH~~ **RESOLVED** | server.c, chargen.c, skills.c |
| 3 | `snprintf` output may be truncated [-Wformat-truncation] | 22 → **0** | ~~MEDIUM~~ **RESOLVED** | driver.c, server.c, preprocessor.c, room.c, chargen.c, item.c |
| 4 | `printf`/`fprintf` format type mismatch [-Wformat] | 1 → **0** | ~~HIGH~~ **RESOLVED** | vm.c |
| 5 | Unused variable / set-but-not-used | 7 | LOW | driver.c, parser.c, combat.c, wiz_tools.c |
| 6 | Unused parameter [-Wunused-parameter] | 13 | LOW | multiple |
| 7 | Unused static function [-Wunused-function] | 2 | LOW | compiler.c, chargen.c |
| 8 | Zero-length format string [-Wformat-zero-length] | 1 → **0** | ~~MEDIUM~~ **RESOLVED** | server.c |
| 9 | `/*` nested inside comment [-Wcomment] | 2 | LOW | chargen.c |
| 10 | Signed `?:` operand type change [-Wsign-compare] | 1 → **0** | ~~MEDIUM~~ **RESOLVED** | driver.c |
| 11 | Unused static array variables | 4 | LOW | wiz_tools.c |

---

## Category Detail

### 1. Always-true NULL check on fixed-size array member — MEDIUM (42 instances)

**Pattern:** `sess->username ? sess->username : "<unknown>"` where `username` is
`char username[64]` (a fixed-size array, address is never NULL).

**Root cause:** `session_internal.h:39` declares `char username[64]` (and similarly
`title`, `enter_msg`, `leave_msg`, `goto_msg`). The compiler correctly warns that
the ternary test is always true.

**Risk:** No undefined behaviour — the test is dead code, not dangerous.
However it masks developer intent (was this supposed to check `username[0]` instead?).

**Affected locations (representative):**
- `src/driver.c`: 9 instances (lines 399, 600, 700, 842, 2595, 2789, 4767, 5690, + related fields)
- `src/wiz_tools.c`: 29 instances across all `wiz_*` functions
- `src/chargen.c`: 4 instances (lines 1523, 1527, 1531, 1535 — title/enter_msg/leave_msg/goto_msg)
- `src/combat.c`: 1 instance (line 86)
- `src/room.c`: 1 instance (line 1224)

**Fix:** Replace `sess->username ? sess->username : "<unknown>"` with
`sess->username[0] ? sess->username : "<unknown>"` — checks first byte, which is
safe for a fixed-size char array.

---

### 2. Signed/unsigned integer comparison — ~~HIGH~~ RESOLVED (8 instances fixed 2026-02-23)

**Pattern:** Comparing `int i` (or `int bi`) with `sizeof(...)` which is `size_t`
(unsigned `long`). GCC warns because the signed value could be negative, producing
an unexpected result when compared against an unsigned expression.

**Risk:** Potential infinite loop or out-of-bounds access if a loop counter wraps
to a large positive value after underflowing.  Unlikely here since loop counters
start at 0 and `sizeof` is always positive, but the comparison is formally undefined
for negative `i` on two's-complement platforms.

**Affected locations:**
- `src/server.c:27` — `for (int i = 0; text[i] && bi < sizeof(buf)-1; )`
- `src/server.c:34` — inner while loop, same function `send_ansi()`
- `src/chargen.c:38` — loop over array with `sizeof`
- `src/skills.c`: 5 instances (lines 772, 787, 796, 810, 820)

**Fix:** Change loop variables to `size_t` or cast `sizeof(...)` to `int` after a
bounds check.  The `send_ansi` case in `server.c` is the most exposed since it
handles arbitrary user input.

---

### 3. `snprintf` output may be truncated — ~~MEDIUM~~ RESOLVED (22 instances fixed 2026-02-23)

**Pattern:** `-Wformat-truncation` fires when GCC can statically prove that the
formatted output *might* exceed the destination buffer size.

**Risk:** Truncated strings — not a memory corruption issue (snprintf always
null-terminates), but silently truncated paths or messages can cause wrong room
loads, invalid file access, or confusing user-visible output.

**High-interest locations:**
- `src/driver.c:4330` — forced-command message, `forced_cmd` can be 511 bytes into
  a 256-byte response buffer.
- `src/server.c:188` — `item_path` built from `full_path + "/" + entry->d_name`;
  output up to 1280 bytes into a 1024-byte buffer.
- `src/server.c:148,152` — `path` built from `current_dir + "/" + args`; can exceed
  512 bytes.

**Fix:** Either enlarge destination buffers to the maximum possible output size, or
explicitly truncate/validate inputs before the `snprintf`.

---

### 4. `printf`/`fprintf` format type mismatch — ~~HIGH~~ RESOLVED (1 instance fixed 2026-02-23)

**Pattern:** Format specifier does not match the actual argument type.

**Risk:** Undefined behaviour on read; wrong value printed (common manifestation),
but stack reads of the wrong size can also corrupt the argument frame on some ABIs.

**Location:**
- `src/vm.c:697` — `"%d"` used for a `long int` argument. Fix: use `"%ld"`.

**Fix:** Change format specifier to `%ld` (or cast argument to `int` if values are
always small).

---

### 5. Unused variable / set-but-not-used — LOW (7 instances)

**Locations:**
- `src/driver.c:2586` — `Character *speaker_ch` set but not used.
- `src/parser.c:1213` — `int is_public` set but not used.
- `src/combat.c` — `dmg_type` unused.
- `src/wiz_tools.c` — 4 static `occ_pool_*` arrays declared but never referenced.

**Risk:** No runtime risk.  Dead code increases maintenance surface.

**Fix:** Remove unused variables, or if intentional placeholders mark them
`(void)var;` and add a comment.

---

### 6. Unused parameter — LOW (13 instances)

**Pattern:** Function parameters declared but not referenced in body.

**Affected files:** Multiple wiz_tools.c functions, chargen.c, room.c, etc.

**Risk:** None at runtime.

**Fix:** Cast to `(void)param;` as suppression, or remove parameter if the API
allows it.

---

### 7. Unused static function — LOW (2 instances)

- `src/compiler.c:269` — `compiler_find_global` defined but never called.
- `src/chargen.c:849` — `chargen_show_secondary_skills` defined but never called.

**Risk:** None at runtime; dead code.

**Fix:** Remove functions or expose them via a header if needed elsewhere.

---

### 8. Zero-length format string — ~~MEDIUM~~ RESOLVED (1 instance fixed 2026-02-23)

**Location:** `src/server.c:259` — `snprintf(new_dir, sizeof(new_dir), "")`.

**Risk:** Benign here (zeroes the string), but zero-length format strings are
technically implementation-defined.

**Fix:** Use `new_dir[0] = '\0';` instead.

---

### 9. Nested `/*` inside comment — LOW (2 instances)

**Location:** `src/chargen.c:56,60` — commented-out code contains `/*`.

**Risk:** None; GCC warns but correctly handles it.

**Fix:** Use `//` for commented-out code blocks.

---

### 10. Ternary signedness change — ~~MEDIUM~~ RESOLVED (1 instance fixed 2026-02-23)

**Location:** `src/driver.c:233` — `session ? session->state : -1` where
`session->state` is `SessionState` (an unsigned enum) and `-1` is a signed `int`.
The result type becomes `int`, but the enum's unsigned representation may differ.

**Risk:** Could yield unexpected integer value if the comparison is used in
unsigned context downstream.

**Fix:** Cast explicitly: `(int)(session ? session->state : (SessionState)-1)` or
use a sentinel enum value instead of `-1`.

---

## Priority Fix Order

1. ~~**HIGH — `vm.c:697` format mismatch**~~ **RESOLVED 2026-02-23** — changed `%d` to `%ld` in `vm.c:697`.
2. ~~**HIGH — `server.c` signed/unsigned comparisons**~~ **RESOLVED 2026-02-23** — changed `int bi` to `size_t bi` in `send_ansi()` (`server.c:26`).
3. ~~**HIGH — `skills.c` signed/unsigned comparisons**~~ **RESOLVED 2026-02-23** — changed loop vars to `size_t`, used `(size_t)id >= TOTAL_SKILLS` guards in `skills.c`.
4. ~~**MEDIUM — snprintf truncation (22 sites)**~~ **RESOLVED 2026-02-23** — widened destination buffers in driver.c, server.c, preprocessor.c, room.c, chargen.c, item.c.
5. ~~**MEDIUM — `server.c:259` zero-length format string**~~ **RESOLVED 2026-02-23** — replaced with `new_dir[0] = '\0';`.
6. ~~**MEDIUM — `driver.c:267` ternary signedness**~~ **RESOLVED 2026-02-23** — cast to `(int)(session ? (int)session->state : -1)`.
7. **MEDIUM — NULL checks on array addresses** (42 instances): dead code, replace
   with `[0]` checks.
8. **LOW** — remaining unused vars/params/functions.
