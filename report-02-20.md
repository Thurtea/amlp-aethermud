# AetherMUD Driver — Session Report
**Date:** 2026-02-20
**Branch:** main
**Author:** Claude Sonnet 4.6

---

## Build Health

| Item | Status |
|------|--------|
| Build result | **PASS** — `make: Nothing to be done for 'driver'` (up-to-date, 0 errors) |
| Binary | `build/driver` — 1.6 MB ELF 64-bit x86-64 |
| Build timestamp | 2026-02-20 23:25 |
| Source files | 34 `.c` files, 34 `.h` files (68 total) |
| Total lines | ~37,021 |
| Save format | Magic `0x414D4C50`, version **10** |

---

## Source Files Summary

| File | Description | Notes |
|------|-------------|-------|
| `src/driver.c` | Main event loop, command dispatch | ~5100+ lines |
| `src/chargen.c` | Character creation, save/load | Save version 10 |
| `src/chargen.h` | Character struct definitions | `permanently_dead`, `death_killer[64]` added |
| `src/death.c` | Death handling | 3-arg `handle_player_death()` |
| `src/combat.c` | Real-time combat engine | No-combat guard for recovery_room |
| `src/npc.c` | NPC templates, AI, XP bridge | 8 templates; mage AI; LPC XP bridge |
| `src/magic.c` | Spell database, casting logic | 35 spells (ids 0–34) |
| `src/psionics.c` | Psionic powers, ISP management | 26 powers (ids 0–25) |
| `src/wiz_tools.c` | Wizard tools, admin commands | `cmd_slay`, `cmd_npcspawn` |
| `src/wiz_tools.h` | Wizard tool declarations | — |
| `src/room.c` | Room system, exits, broadcasting | — |
| `src/skills.c` | Skill database | — |
| `src/item.c` | Item / inventory / equipment | — |

---

## Magic System

- **Spell count:** 35 (ids 0–34)
- **Schools:** Warlock (0–7), Mystic/Warlock (8–15), Wizard (16–25), Battle Mage (26–31), Ritual (32–33), Energy Bolt (34)

### Notable Combat Spells

| ID | Name | Damage | PPE | Effect |
|----|------|--------|-----|--------|
| 8 | Fireball | 4d6 MD | 5 | 10-ft radius area effect; loops all room NPCs/players |
| 9 | Lightning Bolt | 2d6 MD | 5 | Chains to 2nd target via `magic_chain_lightning()` |
| 34 | Energy Bolt | 1d6+2 MD | 3 | Single-target concentrated energy blast; `base_damage = 2` |

### Fireball Area Effect (verified)
`area_effect_feet = 10` causes `magic_apply_effect()` to loop all NPCs and players in room, calling `combat_apply_damage()` on each.

---

## Psionics System

- **Power count:** 26 (ids 0–25)
- **Categories:** Super (0–2, 25), Telepathy (3–5, 24), Healing (6–11), Physical (12–16), Sensitive (17–23)

### Notable Combat Powers

| ID | Name | Damage | ISP | Effect |
|----|------|--------|-----|--------|
| 13 | Electrokinesis | 2d6 MD | 3 | Electrical ranged attack |
| 14 | Pyrokinesis | 3d6 SD | 3 | Fire ranged attack |
| 25 | Mind Bolt | 2d6 MD | 8 | **Bypasses armor**, category `PSION_SUPER`, range 150 ft |

---

## NPC System

- **Template count:** 8 (`NPC_TEMPLATE_COUNT`)
- **Pool size:** `MAX_NPCS_GLOBAL` slots
- **Spawn API:** `npc_spawn(NpcTemplateId, room_id)` and `npc_spawn_by_path(template_id, lpc_path)`

### NPC Templates

| Enum | Name | Level | Type | XP | Aggro |
|------|------|-------|------|----|-------|
| `NPC_GOBLIN` | a goblin | 1 | SDC | 50 | Yes |
| `NPC_DOG_BOY` | a Dog Boy scout | 3 | MDC | 150 | Yes |
| `NPC_DEAD_BOY` | a Coalition Dead Boy | 5 | MDC | 250 | Yes |
| `NPC_BRODKIL` | a Brodkil demon | 7 | MDC | 500 | Yes |
| `NPC_DRAGON_HATCHLING` | a young dragon hatchling | 10 | MDC | 1000 | Yes |
| `NPC_MOXIM` | Moxim | 15 | MDC | 2000 | No |
| `NPC_SPIKE` | Spike | 1 | SDC | 0 | No (pettable) |
| `NPC_MAGE` | a rogue mage | 4 | SDC | 200 | Yes (casts Fireball) |

### NPC Mage AI
- Casts Fireball at ~15% chance per tick
- Escalates to ~60% cast chance when HP falls at or below 30%

### XP Award Bridge (npc.c:413–417)
```c
/* Prefer LPC add_experience() so level-up logic stays in player.lpc */
VMValue xp_arg = vm_value_create_int(xp_reward);
obj_call_method(global_vm, lpc_obj, "add_experience", &xp_arg, 1);
```
Falls back to C-side `ch->xp += xp_reward` if no LPC object is present.

---

## Death System

### Character Struct Fields (chargen.h)
```c
int lives_remaining;      /* Remaining lives (starts at 5) */
int permanently_dead;     /* 1 = character has died permanently, cannot log in */
char death_killer[64];    /* Name of what delivered the permanent kill */
Scar scars[MAX_SCARS];    /* Scar records (max 5) */
int scar_count;
```

### Function Signature (death.c:45)
```c
void handle_player_death(PlayerSession *sess, PlayerSession *killer,
                         const char *npc_killer_name);
```

### Death Flow
1. **Lives > 0:** Decrement `lives_remaining`, add scar, teleport to `recovery_room`, restore all pools.
2. **Lives == 0:** Set `permanently_dead = 1`, write `death_killer`, save character, send dissolution message, `STATE_DISCONNECTING`.

### Call Sites (8 total)
| File | Scenario | killer arg | npc_killer_name arg |
|------|----------|-----------|---------------------|
| `combat.c` (×2) | PvP melee hit | attacker session | NULL |
| `wiz_tools.c` | `slay` command | sess (admin) | NULL |
| `psionics.c` | Mind Bolt kill | NULL | npc->name |
| `magic.c` (×2) | Fireball / Energy Bolt kill | NULL | npc->name |
| `npc.c` (×2) | NPC melee / fireball kill | NULL | npc->name |

### Login Guard (driver.c:4949)
```c
if (session->character.permanently_dead) {
    send_to_player(session,
        "\n=== CHARACTER DECEASED ===\n"
        "This character has permanently died.\n"
        "Slain by: %s\n"
        "Please create a new character.\n\n", killer);
    session->state = STATE_DISCONNECTING;
}
```

---

## Recovery System

### Recovery Room (lib/domains/death/recovery_room.lpc)
- Short: "Recovery Chamber"
- Property: `no_combat` (LPC flag; C enforced separately)
- Exit: `chute` → `/domains/start/village_center`
- Spawns `healer_npc` via `reset()` if not present

### No-Combat Guard (combat.c:162, 268)
Both `combat_engage()` and `combat_engage_npc()` check:
```c
if (attacker->current_room && attacker->current_room->lpc_path &&
    strstr(attacker->current_room->lpc_path, "recovery_room")) {
    send_to_player(attacker,
        "A gentle force prevents violence here. Rest and recover.\n");
    return NULL;
}
```

### `return` Command (driver.c:1624)
- Valid only in rooms whose `lpc_path` contains `"recovery_room"`
- Moves player to `room_get_start()`
- Broadcasts "A shimmering portal opens and a figure steps through."

---

## Command System

### New Commands Added This Session

| Command | Syntax | Privilege | Source |
|---------|--------|-----------|--------|
| `slay` | `slay [<player>\|me]` | >= 2 (Admin) | wiz_tools.c / driver.c:3924 |
| `npcspawn` | `npcspawn <type>` | >= 2 (Admin) | wiz_tools.c / driver.c:3935 |
| `xp` / `experience` | `xp` | Player | driver.c:1900 |
| `return` | `return` | Player (in recovery room) | driver.c:1624 |

### `npcspawn` Type Map
| Input | Template |
|-------|----------|
| `guard` | NPC_DOG_BOY |
| `bandit` | NPC_BRODKIL |
| `merchant` | NPC_MOXIM |
| `mage` | NPC_MAGE |
| `goblin` | NPC_GOBLIN |
| `scout` / `dog_boy` | NPC_DOG_BOY |
| `dead_boy` / `deadboy` | NPC_DEAD_BOY |
| `brodkil` | NPC_BRODKIL |
| `dragon` | NPC_DRAGON_HATCHLING |
| `moxim` | NPC_MOXIM |
| `spike` | NPC_SPIKE |

### `xp` Command Output Format
```
Level: <n> | XP: <n> | Next level at: <n> XP
```
Next-level formula: `cur_lvl * 1000`

---

## Save Format (Version 10)

| Version | Addition |
|---------|----------|
| 1 | Base stats, skills, equipment |
| 3 | LPC room path |
| 4 | Lives, scars |
| 5 | `wizard_role` (32 bytes) |
| 6 | Title, enter/leave/goto messages (128 bytes each) |
| 7 | `bm_credits` (int) |
| 8 | Tattoos (`num_tattoos` + MAX_TATTOO_NAME=48 each) |
| **9** | `permanently_dead` (int) |
| **10** | `death_killer` (64 bytes) |

---

## Library Status

| Path | Status |
|------|--------|
| `lib/domains/death/recovery_room.lpc` | Exists — no-combat room, chute exit |
| `lib/domains/death/healer_npc.lpc` | Exists — spawned by recovery_room reset |
| `lib/secure/master.lpc` | Active master object |
| `lib/secure/simul_efun.lpc` | Exists (stubs, not yet populated) |
| `lib/domains/start/` | Reference LPC only; rooms hardcoded in C |

---

## Files Changed This Session

| File | Changes |
|------|---------|
| `src/chargen.h` | Added `permanently_dead`, `death_killer[64]`; 3-arg `handle_player_death` declaration |
| `src/chargen.c` | Save version 9→10; serialize/deserialize new death fields |
| `src/death.c` | Updated to 3-arg signature; permanent death logic; `death_killer` assignment with capitalize |
| `src/combat.c` | No-combat guard in `combat_engage()` and `combat_engage_npc()`; 3-arg death calls |
| `src/driver.c` | Added `return`, `xp`/`experience` commands; wired `slay`/`npcspawn`; login permanently_dead guard |
| `src/wiz_tools.c` | `cmd_slay()`, `cmd_npcspawn()` with type_map; privilege_level >= 2 |
| `src/wiz_tools.h` | Updated `handle_player_death` extern declaration to 3-arg |
| `src/npc.c` | NPC_MAGE template; mage fireball AI; XP LPC bridge; 3-arg death calls |
| `src/magic.c` | Energy Bolt (id 34); fireball area-effect loop; lightning bolt chain; 3-arg death calls |
| `src/psionics.c` | Mind Bolt (id 25); 3-arg death call |

---

## Outstanding Tasks

1. **Mudlet test sequence:** `npcspawn mage` → attack mage → die → reconnect (see deceased message) → `return` → `xp` → kill NPCs until level-up → `slay me`
2. **`simul_efun.lpc`** — stubs need population (commonly-used LPC helper functions)
3. **Missing player commands:** `open`, `close`, `lock`, `unlock`, `read`, `write`, `sleep`, `wake`, `sit`, `stand`
4. **LPC `add_experience` level-up logic** — currently in `player.lpc` but level-up check not verified end-to-end from C XP bridge
5. **Recovery room corpse retrieval** — body chute returns player but corpse/item recovery not implemented

---

## API Reference (C-level)

### handle_player_death
```c
void handle_player_death(PlayerSession *sess,   /* victim */
                         PlayerSession *killer, /* PvP attacker, or NULL */
                         const char *npc_killer_name); /* NPC name, or NULL */
```

### npc_spawn / npc_spawn_by_path
```c
NPC* npc_spawn(NpcTemplateId template_id, int room_id);
NPC* npc_spawn_by_path(NpcTemplateId template_id, const char *lpc_path);
```

### LPC XP Bridge
```c
extern VirtualMachine *global_vm;
VMValue xp_arg = vm_value_create_int(xp_amount);
obj_call_method(global_vm, (obj_t*)player->player_object, "add_experience", &xp_arg, 1);
```

### Privilege Levels
| Level | Role | Notes |
|-------|------|-------|
| 0 | Player | Default |
| 1 | Wizard | `setrole` / promote |
| 2 | Admin | Max; `slay`, `npcspawn`, all wiz tools |
