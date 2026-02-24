# Compiler Warnings Triage — AMLP AetherMUD
Date: 2026-02-23 | **Final: 0 warnings, 0 errors**
Build: `make clean && make` (debug target, -Wall -Wextra -g -O2 -std=c99)
Total warnings: 102 → 93 (HIGH fixes) → 69 (MEDIUM fixes) → **0** (LOW fixes 2026-02-23)
Raw output: `diagnostics/build-warnings.txt`

---

## Summary Table

| # | Category | Count | Severity | Status |
|---|----------|-------|----------|--------|
| 1 | Always-true NULL check on fixed-size array member | 42 → **0** | MEDIUM | **RESOLVED 2026-02-23** |
| 2 | Signed/unsigned integer comparison [-Wsign-compare] | 8 → **0** | HIGH | **RESOLVED 2026-02-23** |
| 3 | `snprintf` output may be truncated [-Wformat-truncation] | 22 → **0** | MEDIUM | **RESOLVED 2026-02-23** |
| 4 | `printf`/`fprintf` format type mismatch [-Wformat] | 1 → **0** | HIGH | **RESOLVED 2026-02-23** |
| 5 | Unused variable / set-but-not-used | 7 → **0** | LOW | **RESOLVED 2026-02-23** |
| 6 | Unused parameter [-Wunused-parameter] | 13 → **0** | LOW | **RESOLVED 2026-02-23** |
| 7 | Unused static function [-Wunused-function] | 2 → **0** | LOW | **RESOLVED 2026-02-23** |
| 8 | Zero-length format string [-Wformat-zero-length] | 1 → **0** | MEDIUM | **RESOLVED 2026-02-23** |
| 9 | `/*` nested inside comment [-Wcomment] | 2 → **0** | LOW | **RESOLVED 2026-02-23** |
| 10 | Signed `?:` operand type change [-Wsign-compare] | 1 → **0** | MEDIUM | **RESOLVED 2026-02-23** |
| 11 | Unused static array variables | 4 → **0** | LOW | **RESOLVED 2026-02-23** |

---

## Resolution Log

### HIGH Priority (resolved first)

1. **`vm.c:697` format mismatch** — changed `%d` → `%ld` for `long int` argument.
2. **`server.c` signed/unsigned comparisons** — changed `int bi` → `size_t bi` in `send_ansi()`.
3. **`chargen.c` language loop** — changed loop variable to `size_t`.
4. **`skills.c` 5 comparisons** — changed loop vars to `size_t`, used `(size_t)id >= TOTAL_SKILLS` guards.

### MEDIUM Priority

5. **22 snprintf truncation sites** — widened destination buffers in driver.c, server.c, preprocessor.c, room.c, chargen.c, item.c; used `%.63s` format cap for player name copy.
6. **`server.c:259` zero-length format string** — replaced with `new_dir[0] = '\0';`.
7. **`driver.c:267` ternary signedness** — cast to `(int)(session ? (int)session->state : -1)`.
8. **42 NULL checks on `char[]` array addresses** — replaced `->username ? ->username : "x"` with `->username[0] ? ->username : "x"` across driver.c, wiz_tools.c, room.c, combat.c; removed dead `&&` guards where address was always non-NULL.

### LOW Priority

9. **Unused variables** — removed `speaker_ch` (driver.c), `dmg_type` (item.c), `cache_idx` (room.c), `is_public` (parser.c).
10. **Unused parameters** — added `(void)param;` in magic.c, item.c (2), wiz_tools.c, other locations.
11. **Unused static functions** — added `__attribute__((unused))` to `compiler_find_global` (compiler.c).
12. **Unused static arrays** — removed 4 `occ_pool_*` arrays from wiz_tools.c.
13. **`-Wcomment`** — changed nested `/* */` to `//` style in chargen.c.
14. **Buffer size mismatches (final 4)** — widened `Scar.location[64]→128`, `Scar.description[128]→256` (chargen.h); widened `ed_fspath[1024]→1030` (session_internal.h); used `"%.63s"` format cap in driver.c giveskill command.

---

## Final State

```
$ make clean && make driver 2>&1 | grep "Warnings:"
Warnings:       0
```

**Priority 4 COMPLETE — 2026-02-23**
