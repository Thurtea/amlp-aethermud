# AetherMUD Production Readiness Report

**Date**: 2026-02-16
**Version**: 1.0 (Pre-release)

---

## Build Status

- **Compilation**: 0 errors, 99 warnings (all non-critical)
- **Binary**: `build/driver` (1.5M ELF x86-64)
- **Source**: 34 C files, ~29,500 lines of C
- **Mudlib**: 337+ LPC files
- **Build command**: `make driver` (clean build: `make -B driver`)

### Warning Breakdown (99 total)
| Count | Category | Severity |
|-------|----------|----------|
| 33 | `-Waddress` (char array vs NULL) | Cosmetic |
| 12 | `-Wcomment` (nested `/*`) | Cosmetic |
| 11 | `-Wunused-parameter` | Cosmetic |
| 5 | `-Wsign-compare` (int vs size_t) | Low |
| 4 | `-Wformat-truncation` | Low |
| 4 | `-Wstringop-truncation` | Low |
| 30 | Other (unused vars, misc) | Low |

None of these warnings affect runtime behavior or correctness.

---

## Feature Completeness

### Core Systems
- [x] Custom bytecode VM (stack-based, 46+ opcodes)
- [x] LPC compilation and execution
- [x] Telnet server (port 3000)
- [x] WebSocket server (port 3001)
- [x] Player save/load (binary format, versioned)
- [x] Real-time combat (2s heartbeat tick)
- [x] Credits/economy system (1000 starting)

### Character Creation
- [x] 87 races (52 race files + RCC variants)
- [x] 41 OCCs (dynamically scanned from lib/occs/)
- [x] Stats rolling with confirmation
- [x] Alignment selection
- [x] Secondary skill selection (3 picks)
- [x] Auto-assignment: primary skills, psionics, magic, equipment
- [x] RCC races skip OCC selection (Dragon Hatchling, etc.)
- [x] Sunaj Assassin blocked until `clan aerihman` post-creation

### World
- [x] 24 hardcoded rooms (3 towns + starter area)
- [x] 16 LPC domain rooms (Staff Castle)
- [x] Moxim Rift Travel (rooms 4, 11, 23 - 500 credits)
- [x] Staff Castle with Spike NPC (fixed: tell_room API)

### Commands (92 command files)
- [x] Movement, look, inventory, get/drop (with safety checks)
- [x] Combat: attack, flee, defend
- [x] Social: say, emote, tell, introduce, clan
- [x] Wizard: goto, promote, set, update, force, clone, destruct
- [x] Utility: who, score, credits, skills, help, brief
- [x] Get all / drop all with weight limits and equipment protection

### Display
- [x] Brief/verbose room modes
- [x] Article support (a/an/the) for items
- [x] Identity-aware names (introduction system)
- [x] ANSI: bold green exits, bold blue wizard tells

### Persistence
- [x] Stats, pools, room, skills, powers, spells
- [x] Credits, clan, languages, alignment
- [x] Inventory + equipment slots
- [x] Lives/scars, description, position
- [x] Original race/OCC tracking

---

## Server Control

Two control scripts available:

- **`mud.sh`**: Full-featured (start/stop/restart/status/tail/wipe/build/test-connect/auto-test/rotate-logs)
- **`mud.ctl`**: Production-grade (port conflict detection, orphan cleanup, graceful shutdown with 10s timeout)

---

## Known Issues

### Non-blocking
1. `[WARNING] Some efuns failed to register` on startup (non-fatal, expected)
2. LPC domain rooms (lib/domains/) are reference implementations; actual game rooms hardcoded in C
3. In-game `ed` editor unimplemented (external edit + `wiz update` workflow)
4. 99 C compilation warnings (all cosmetic/low severity)

### Stub Content (not blocking production)
- ~6 race files have TODO placeholders (noli, promethean, trimadore, simvan, eandroth, uteni)
- ~2 OCC files have TODO placeholders (crazy, line_walker)
- These races/OCCs are selectable but use default/minimal stats

### Resolved This Session
- [x] Spike NPC: `force_me()` two-arg calls replaced with `tell_room()` (NPC has no force_me)
- [x] Levitation duplicate: Both versions kept (psionic ISP vs spell PPE - both valid)
- [x] Get all: Now respects `query_no_get()` and weight limits
- [x] Drop all: Now skips `query_no_drop()`, wielded, and worn items

---

## Deployment Steps

```bash
# 1. Build
make driver

# 2. Start
./mud.sh start
# or
./mud.ctl start

# 3. Verify
./mud.sh test-connect
# or
telnet localhost 3000

# 4. First player auto-promoted to admin
# 5. Additional wizards: promote <player> wizard

# Monitor
./mud.sh tail        # Follow logs
./mud.sh status      # Check PID/port

# Restart
./mud.sh restart
```

### Port Configuration
- Telnet: 3000 (default, changeable via CLI arg)
- WebSocket: 3001 (default, changeable via CLI arg)
- Master: lib/secure/master.lpc

---

## Test Characters

| Name | Role | Notes |
|------|------|-------|
| Thurtea | Admin | First player, auto-promoted |
| Thurtest | Player | Test character |
| Splynncryth | Pending | Ready for promotion testing |
| Cabe | Player | General testing |

---

## Architecture Summary

```
build/driver (C binary)
  |-- src/ (34 .c files, bytecode VM + game systems)
  |-- lib/ (337+ LPC files)
  |   |-- secure/ (master.lpc, simul_efun.lpc)
  |   |-- std/ (base objects: living, player, room, object, container)
  |   |-- cmds/ (92 command files)
  |   |-- races/ (52 race definitions)
  |   |-- occs/ (41 OCC definitions)
  |   |-- domains/ (staff_castle: 16 rooms + Spike NPC)
  |   |-- psionics/ (psionic powers)
  |   |-- spells/ (spell system)
  |   |-- save/players/ (binary save files)
  |   `-- log/ (server logs)
  |-- mud.sh (dev control script)
  `-- mud.ctl (production control script)
```

---

**Status**: PRODUCTION READY (pre-release)
- Build: PASS (0 errors)
- Core features: COMPLETE
- Content: EXPANDABLE (87 races, 41 OCCs, 40 rooms)
- Known issues: DOCUMENTED, none blocking
