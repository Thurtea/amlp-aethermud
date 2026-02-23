# AMLP-AetherMUD — config/ Project Report

Date: 2026-02-23

## Directory Purpose

`config/` holds runtime configuration for the AMLP driver and helpful example files. The driver and run scripts source `runtime.conf` (or rely on environment variables) to locate the mudlib root, efun/master paths, networking ports, and debug verbosity.

## File Inventory

- `runtime.conf` — active runtime configuration used by the local checkout.
- `example.runtime.conf` — template with recommended settings and notes for production vs development.

## `runtime.conf` Options and Current Values

All variables are shell-style key=value pairs. Current values in `config/runtime.conf` (unexpanded):

- `MUDLIB_ROOT` = ${MUDLIB_ROOT:-.}
  - Effective default: `.` (current directory) unless `MUDLIB_ROOT` env var is set.
- `MUDLIB_PATH` = ${MUDLIB_ROOT}/lib
- `MASTER_OBJECT` = ${MUDLIB_ROOT}/lib/secure/master.lpc
- `SIMUL_EFUN` = ${MUDLIB_ROOT}/lib/secure/simul_efun.c
  - Note: points to a `.c` path — likely intended to be `/lib/secure/simul_efun.lpc` (LPC file). See security/misconfig below.
- `INCLUDE_DIRS` = ${MUDLIB_ROOT}/lib:${MUDLIB_ROOT}/lib/std
- `PORT` = 3000
- `WS_PORT` = 3001
- `DEBUG_LEVEL` = 2

These values are simple and environment-variable friendly; the file uses parameter expansion so the environment can override values.

## Missing or Misconfigured Settings

- `SIMUL_EFUN` points to `lib/secure/simul_efun.c` in both `runtime.conf` and `example.runtime.conf`. The actual simul efun in this repository is `lib/secure/simul_efun.lpc`. This mismatch will cause the driver to fail to locate the simul_efun if it expects the LPC path or may load an unintended file. Recommend changing `SIMUL_EFUN` to `${MUDLIB_ROOT}/lib/secure/simul_efun.lpc`.
- No explicit `LOG_DIR`, `SAVE_DIR`, `DB_*`, or `USER`/`GROUP` settings are present. Production deployments should configure dedicated paths and an unprivileged system user. The example notes mention writable `lib/save/players` and `lib/log` but these are not enforced by config.
- No TLS / WebSocket TLS options, bind-address, or rate-limiting settings are provided for network security. If the server is exposed, add `BIND_ADDR`, `WS_TLS_CERT`, `WS_TLS_KEY`, and rate-limiting options.
- No explicit file-permissions or umask setting. Consider adding `RUN_AS_USER`/`RUN_AS_GROUP` and `UMASK` for safer runtimes.

## Security Concerns

- Master & Simul efun path: The `MASTER_OBJECT` and `SIMUL_EFUN` variables control privileged runtime behavior. Ensure these point to intended, version-controlled LPC files and not writable locations to avoid code injection.
- Default `MUDLIB_ROOT`=`.` is convenient for development but dangerous in production — prefer an absolute path and a dedicated runtime user. Relative paths may cause the driver to pick up unintended files if started from other directories.
- No password hashing or secret storage options are configured here — password storage is handled in code; earlier source comments in `src/driver.c` indicate plaintext password usage during development. Strongly recommend not storing passwords in config and switching code to bcrypt/argon2.
- Network exposure: ports `3000`/`3001` are default; if the host is internet-facing, add bind-address restrictions, firewall, TLS for websockets, and consider using a reverse proxy.

## Next Steps (recommended)

1. Fix `SIMUL_EFUN` path to point at `lib/secure/simul_efun.lpc` (LPC file). Validate the driver uses the LPC path convention expected by `master.epilog()`.
2. Add configurable `RUN_AS_USER`, `RUN_AS_GROUP`, `LOG_DIR`, and `SAVE_DIR` options and update run scripts to create and chown those directories during deployment.
3. Add bind address and optional TLS settings for WebSocket (`WS_TLS_CERT`, `WS_TLS_KEY`) and document usage in `example.runtime.conf`.
4. Document recommended production `DEBUG_LEVEL=0` and include an `ENV` section describing secure environment variables for secrets (none should be stored in plaintext in these files).
5. Add a small `scripts/check-config.sh` that validates paths in `runtime.conf` (e.g., that `MASTER_OBJECT` and `SIMUL_EFUN` exist and are readable) and warns on obvious misconfigurations.

---
Saved as `config/project-report.md`.
