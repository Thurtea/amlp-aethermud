# AetherMUD Full Project Audit
**Date:** 2026-03-02  
**Server Status:** Boots and listens on Telnet :3000 / WebSocket :3001  
**Build Status:** 33/33 C source files compile; 0 errors, 0 warnings  
**CI:** GitHub Actions — build + test + warnings jobs on push/PR to `main`

---

## ✅ Completed / Working

### C Engine (`src/` — 39,293 total lines)

- **`src/driver.c` (6,471 lines)** — Monolithic MUD server: `select()`-based loop for up to 100 simultaneous clients, dual Telnet/WebSocket listener on ports 3000/3001, full login/chargen pipeline, session management, LPC command dispatch, ~50+ hardcoded commands (`brief`, `verbose`, `prompt`, `password`, `map`, `title`, `settitle`, `setenter`, `setleave`, `setgoto`, `pet`, `feed`, `echo`, `view`, `color`, etc.)
- **`src/vm.c` (1,481 lines)** — Stack-based bytecode VM (1,024-slot stack, 256 globals, 64 functions, 128 string pool); reference-counted strings via `VMStringHeader` prefix; full `vm_init()` / `vm_execute()` / `vm_cleanup()`.
- **`src/compiler.c` (1,441 lines)** + **`src/codegen.c` (1,127 lines)** + **`src/lexer.c` (657 lines)** + **`src/parser.c` (1,618 lines)** + **`src/preprocessor.c` (634 lines)** — Complete LPC compiler pipeline: lexer → parser → codegen → bytecode.
- **`src/efun.c` (3,064 lines)** — Full efun registry (load_object, clone_object, users, find_player, tell_object, tell_room, write, environment, all_inventory, move_object, call_out, remove_call_out, file_size, get_dir, crypt, etc.)
- **`src/combat.c` (1,231 lines)** — Full melee system: linked-list `active_combats`, per-tick attack distribution across `MELEE_ROUND_TICKS`, `attack_roll()` (d20 + PS bonus vs. AC), `damage_roll()` (Palladium PS bonus table), `combat_severity()` prose-only damage descriptors, `handle_player_death()`.
- **`src/chargen.c` (3,448 lines)** — Character creation: 3d6 stat rolling, language assignment, wizard workroom creation (`lib/domains/wizard/<name>/workroom.lpc`), save/restore pipeline.
- **`src/magic.c` (1,175 lines)** — 35-spell static C database (Warlock/Ley Line magic); `magic_severity()` prose-only damage descriptors; PPE cost validation; spell execution entry point.
- **`src/psionics.c` (742 lines)** — 26-power static C database (Super, Telepathy, Healing, Physical, Sensitive categories); ISP cost tracking; power activation entry point.
- **`src/skills.c` (917 lines)** — Palladium skill resolution: d100 roll, attribute modifier (+1/2pts above 10), crit success ≤5 / crit fail ≥96; `SKILL_DATABASE[]` with Rogue skills (prowl, streetwise, safecracking, disguise, pick locks, pick pockets, gambling, palming, concealment).
- **`src/death.c` (279 lines)** — Full death handling: corpse creation + loot transfer, blood pool creation, 300-second decay registry (`CorpseDecayEntry[32]`), `corpse_tick()` heartbeat, `corpse_reclaim_for_player()`, permanent death on `lives_remaining ≤ 0`, scar system (5 locations × 5 descriptions, stored in `ch->scars[]`), post-death HP/SDC/PPE/ISP restoration, teleport to recovery room.
- **`src/race_loader.c` (889 lines)** — Loads race/OCC JSON and LPC files, applies stat modifiers/minimums/maximums, validates OCC–race compatibility at chargen.
- **`src/item.c` (1,275 lines)** — Full item system with inventory serialization (write/read to `.o` save files, format v11); container support; equipment slot management.
- **`src/npc.c` (594 lines)** — NPC heartbeat, AI tick, spawn/respawn registration, `perform_npc_attack()`.
- **`src/password.c`** — bcrypt-based password hashing (`crypt_r()`); legacy plaintext→bcrypt upgrade path in login.
- **`src/room.c` (1,982 lines)** — Room loading, player movement, `room_broadcast()`, LPC room `create()` execution on first load, C-backed New Camelot fallback rooms.
- **`src/server.c` (931 lines)** — TCP accept loop, WebSocket upgrade handshake, session lifecycle management.
- **`src/websocket.c` (632 lines)** — RFC 6455 WebSocket framing (text/binary/ping/pong/close frames), masking, fragmentation.
- **`src/wiz_tools.c` (1,331 lines)** — `wiz_goto()` (teleport by path or player name), `wiz_summon()`, timestamped wizard log, Staff of Demotion / RP Skill Tool / Tattoo-Gun C-side implementations.
- **`src/gc.c` (431 lines)** — Reference-counting garbage collector with cycle detection; `gc_collect()` triggered by driver heartbeat.
- **`src/mapping.c` (172 lines)** — LPC mapping type (hash table, `VM_MAPPING_BUCKETS=16`).
- **`src/program.c` + `src/program_loader.c`** — Compiled LPC program storage, caching, and on-demand loading.

### LPC Secure Layer (`lib/secure/`)

- **`master.lpc`** — Root master object: bootstraps daemons in order (simul_efun → chargen → combat → skills → spells → languages → npc_daemon → command), initializes save directories.
- **`simul_efun.lpc`** — Global LPC utility functions available to all objects: ANSI constants (`BOLD`, `RED`, `GREEN`, `CYAN`, etc.), `notify_fail()`, `color_code()` lookup table, `wrap_text()`, `center_text()`, `pad_right()`, `member_array()`, `to_int()`, `lower_case()`, `capitalize()`, `strsrch()`, and others.
- **`char_create.lpc`** — Interactive character creation wizard, delegates to `chargen` daemon.
- **`first_connect.lpc`** — First-boot admin install intercept.
- **`install.lpc`** — First-boot directory seeding and admin account setup.
- **`motd.lpc`** — MOTD display at login.
- **`wiz_perms.lpc`** — Wizard permission / access-control helpers.
- **`formatting.lpc`** — Text-formatting utilities (word-wrap, columns, etc.).

### LPC Standard Library (`lib/std/`)

- **`living.lpc` (2,306 lines)** — Complete base class for players and NPCs: all Palladium stats (IQ/ME/MA/PS/PP/PE/PB/SPD), full HP/SDC/MDC interaction pipeline (MDC armor absorbs MDC damage; MDC damage ×100 through SDC armor; SDC armor reduces by AR%), psionic system (ISP, power list, `use_isp()`), magic system (PPE, spell list, `use_ppe()`), introduction/name memory system, position/RP desc, experience/credits, language tracking.
- **`player.lpc` (1,374 lines)** — Player-specific layer: bcrypt password storage, privilege levels (0=Player/1=Wizard/2=Admin), title/surname system, save/restore, level-up with PPE/ISP gains, wiztool attachment/detachment, `enter_world()` routing.
- **`room.lpc`** — Base room: short/long desc, exit mapping, item/NPC inventory, `set_property()`, `no_fight`/`no_combat` flags, `light` level.
- **`npc.lpc` (2,306+ lines)** — NPC base: `on_spawn()` → heartbeat loop, `take_damage()` override, `die()`, aggro flag, `perform_attack()`, `npc_heartbeat()` AI tick.
- **`occ.lpc` (1,112 lines)** — Full OCC base class: all Palladium OCC attributes, XP/level table, `apply_to_player()` (stat bonuses, HP/SDC/PPE/ISP, attacks, skills, equipment), `level_up()`, `award_xp()`, `get_occ_info()`, `get_xp_progress()`.
- **`race.lpc` (906 lines)** — Full race base class: stat modifiers/minimums/maximums, natural AR/SDC/MDC, Phase 2 combat (attacks per round, parries, auto-parry, auto-dodge), racial abilities, OCC allow/forbid lists, faction/language/alignment, `apply_to_player()`, `generate_physical_traits()`.
- **`skill.lpc` (198 lines)** — Skill base class: `calculate_percentage()` (base + level bonus + IQ bonus + synergy bonuses, capped), `attempt()` (d100 roll), `meets_requirements()`.
- **`spell.lpc` (195 lines)** — Spell base class: PPE validation, `can_cast()`, `cast()` (deduct PPE, echo incantation, call `apply_effect()`), `calculate_duration()`.
- **`object.lpc`** — Base object: identity, inventory, environment, property mapping, item stacking.
- **`weapon.lpc` (29 lines)** — Minimal base: `weapon_type`, `damage_num`, `damage_sides`, `damage_type`, `is_weapon()=1`.
- **`armor.lpc` (31 lines)** — Minimal base: `armor_type`, `armor_rating`, MDC pool with `reduce_mdc()`, `is_armor()=1`.
- **`shop.lpc`** — Dual-currency shop (UC/BMC), ordered inventory, configurable sell-rate, `no_combat` property auto-set.
- **`daemon.lpc`** — Base daemon: idempotent `create()`, standard logging.
- **`language.lpc`** — Language base class: id, name, family, fluency level, `garble_text()`.
- **`companion.lpc`, `corpse.lpc`, `blood_pool.lpc`, `container.lpc`, `psionic.lpc`, `vehicle.lpc`, `vehicle_room.lpc`, `wiztool.lpc`, `workroom_template.lpc`** — Supporting std objects.

### Daemons (`lib/daemon/`)

- **`chargen.lpc` (1,129 lines)** — 11-state character creation machine (NONE→RACE→RACE_CONFIRM→STATS_ROLL→STATS_ASSIGN→OCC→OCC_CONFIRM→ALIGNMENT→SKILLS→EQUIPMENT→FINALIZE→COMPLETE), race/OCC caching, Palladium 3d6 rolling with exceptional-roll bonus, `get_valid_occs_for_race()`, `apply_racial_modifiers()`.
- **`combat.lpc` (899 lines)** — Centralized combat manager: `active_combats` mapping, `start_combat()` / `end_combat()` / `add_to_combat()`, `combat_heartbeat()`, `process_combat_round()`, `perform_single_attack()` (d20 + combat bonus vs. 10 + dodge), attack/parry/dodge/miss broadcast with Mudlib `%^COLOR%^` markup, `query_combat_status()`.
- **`command.lpc`** — Command dispatch daemon: maps verb → LPC command file, caches loaded objects, checks privilege requirements, routes player input.
- **`skills.lpc`** — Loads all 155 skill LPC files from 14 subdirectories; `query_skill()`, category index, `format_skill_list()`.
- **`spells.lpc`** — Loads all 77 spell LPC files by level; `query_spell()`, `query_spells_by_level()`.
- **`languages.lpc`** — Loads all language LPC files; `query_language_by_name()`, family filtering, `garble_for_listener()`.
- **`npc_daemon.lpc`** — NPC registry, spawn-on-room-load, respawn timer management.
- **`login.lpc`** — Login sequence coordinator.
- **`psionics.lpc`** — Psionics daemon (loads psionic powers from `lib/psionics/`).

### Login / User Objects

- **`lib/clone/login.lpc` (199 lines)** — Full login flow: name prompt, new-char redirect via `exec()` to `char_create`, existing-char password verify (bcrypt `crypt(pass, stored)`), echo-off during password input, MOTD display, `enter_world()` call.
- **`lib/clone/user.lpc` (284 lines)** — Live player object: dual command dispatch (command daemon → LPC file fallback), `save_me()`/`restore_me()` to `lib/saves/players/<name>.o`, wiztool attach/detach, `net_dead()`/`reconnect()` with reentrancy guard, `enter_world()` with first-connect admin routing.

### Commands (`lib/cmds/`)

- **153 total LPC command files** across `lib/cmds/` (player), `lib/cmds/admin/`, `lib/cmds/creator/`, `lib/cmds/wizard/`, `lib/cmds/wiz/`, `lib/cmds/dragon/`.
- **Fully functional player commands (confirmed):** `look`, `say`, `tell`, `who`, `attack`, `kill`, `cast`, `skills`, `help`, `wield`, `wear`, `quit`, `go`, `get`, `drop`, `put`, `give`, `inventory`, `equipment`, `score` (→stats), `stats`, `examine`, `open`, `close`, `lock`, `unlock`, `shout`, `chat`, `dchat`, `emote`, `whisper`, `language`, `languages`, `introduce`, `remember`, `forget`, `buy`, `sell`, `balance`, `money`, `exchange`, `drink`, `read`, `sit`, `stand`, `sleep`, `wake`, `follow`, `group`, `flee`, `repair`, `firstaid`, `consider`, `description`, `prompt`, `save`, `tattoo`, `tattoos`, `rp`, `telepathy`, `psi`, `pskills`, `manifest`, `metamorph`, `hatch`, `prowl`, `crystal`, `orb`, `wand`, `time`, `credits`, `start`, `stop`, `drive`, `pilot`, `enter`, `exits`, `occs`, `selectocc`, `sskills`, `qcs`, `clan`, `group`.
- **Admin/wizard commands (confirmed functional):** `promote`, `demote`, `stat`, `goto`, `wiz`, `wiztool`, `warmboot`, `shutdown`, `grantskill`, `reequip`, `setrole`, `buildtest`, `testskill`, `tattoogun`, `findobj`, `rp_wiz`, `language` (admin version), `eval` (→wiztool), `cd` (→wiztool), `clone` (→wiztool), `users`.
- **Creator commands (functional):** `cat`, `cd`, `cleanup`, `clone`, `create`, `deploy`, `destruct`, `ed`, `eval`, `find`, `force`, `grep`, `head`, `language`, `load`, `ls`, `mkdir`, `mkobject`, `mkroom`, `modify`, `pwd`, `tail`, `update`.

### Content Systems

- **86 race files** in `lib/races/` — Palladium Rifts-setting breadth: humans, demihumans, dragons (8 types), vampires (3 types), fae (8 types), giants (4 types), supernatural (10+ types), weres (3 types), psionic RCCs (8 types), Coalition/Rifts-specific (15+ types), and more.
- **63 OCC files** in `lib/occs/` — Covering all Palladium archetypes: vagabond, city rat, pirate, sailor, smuggler, rogue scholar, rogue scientist, forger, freelance spy, professional thief, mercenary, ranger, wilderness scout, special forces, coalition grunt, headhunter, operator, robot pilot, power armor pilot, glitter boy pilot, full conversion borg, body fixer, cyber doc, techno wizard, ley line walker, mystic, warlock, temporal wizard, elemental fusionist, necromancer, biomancer, stone master, battle magus, shifter, juicer (regular/ninja/mega/titan/dragon), crazy, maxi man, mind melter, burster, psi stalker, psi healer, psi mystic, gifted gypsy, tattooed man, royal knight, cyber knight, undead slayer, sunaj assassin, atlantean (nomad/slave), and others.
- **77 spell LPC files** across levels 1–15 in `lib/spells/`.
- **155 skill LPC files** (including subdirectory stubs) in `lib/skills/`.
- **69 psionic power LPC files** in `lib/psionics/`.

### Domain Rooms

- **`lib/domains/start/`** — Village Center (fountain), lake shore, lake far shore, shop (general), welcome room, documentation room, void room, combat arena, NPC Moxim, NPC test goblin, merchant Grok.
- **`lib/domains/new_camelot/`** — Town square, gate, tavern, training grounds, stables, blacksmith forge, chapel, falconer shop, 20 garden rooms (grid + north path), 4 connector rooms, guard NPC.
- **`lib/domains/splynn/`** — Tutorial entry (Rift Gate), south alley, catacombs (entry/hall/alcove/vault), black market, juicer clinic, Rocky's bar, Serena's parlor, Splynn library, stat chamber, train platform; NPCs: dimensional traveler, black market vendor, Doc Voss, Rocky, Serena, skeleton warrior; objects: net gun, obsidian blade, PPE talisman, predator armor, spell scroll.
- **`lib/domains/staff_castle/`** — 11-room castle (main hall, throne room, dining hall, kitchen, library, garden, observatory, stables, war room, upper hall, stairs + 3-room hedge maze); NPC Spike.
- **`lib/domains/death/`** — Recovery room (post-death), healer NPC.
- **`lib/domains/admin/`** — Admin start room, orientation room, the_system NPC.
- **`lib/domains/wizard/`** — Wizard Castle (main hall, elevator, 4 role offices, training room, monitor room, dog NPC Spike); 13 personal wizard workrooms (auto-generated for each staff account).
- **`lib/domains/castle/`** — Entry room, Spike NPC.
- **`lib/domains/chi_town/`** — Entry, gate, market; coalition soldier NPC, vendor NPC, vendor stall object.

### Build & Infrastructure

- **`Makefile`** — 33-file build, 16 named test targets, `make test` runs all; `asan`/`release`/`debug` variants; human-readable build progress; warning summary on completion.
- **`mud.sh`** — Server management: `start/stop/restart/status`, PID file management, log rotation (40K lines → archive, 10 kept), `wipe_players/wizards/all`, `fresh` (stop+wipe+rebuild+start), `tail_log`.
- **`.github/workflows/ci.yml`** — Three CI jobs: `build` (`-Werror`), `test` (15 test binaries), `warnings` (lint pass, fails if any `warning:` in output).
- **`config/runtime.conf`** — `MUDLIB_ROOT`, `MUDLIB_PATH`, `MASTER_OBJECT`, `SIMUL_EFUN`, `PORT=3000`, `WS_PORT=3001`, `DEBUG_LEVEL=2`.
- **`lib/Makefile`** — LPC linting / syntax check targets.
- **`lpc-extension/`** — VS Code LPC syntax highlighting extension (TextMate grammar, snippets, language config).
- **16 C unit tests** (`test_lexer`, `test_parser`, `test_vm`, `test_object`, `test_gc`, `test_efun`, `test_array`, `test_mapping`, `test_compiler`, `test_program`, `test_simul_efun`, `test_vm_execution`, `test_lpc_execution`, `test_password`, `test_save_load`, `test_parser_stability`).

### Wizard Hierarchy & Tools

- 4-tier wizard hierarchy: Admin (priv 2) > Domain/Code/RP (priv 1) > Apprentice (priv 0.5) > Player.
- `lib/wiz/`: admin_orb, admin_wand, code_tool, crystal_ball, id_card, qcs_tool, rp_skill_tool, staff_handbook, staff_of_demotion, wizard_staff.
- QCS tools (`lib/std/qcs/`): room, npc, barkeep, vendor, door, armor, weapon, item — builder scaffolding objects.
- `lib/cmds/admin/promote.lpc` — Full promotion ceremony with workroom creation, wizkit cloning, and welcome message.

---

## ⚠️ Incomplete / Stubbed

### Races (`lib/races/`) — ~28 skeletal stubs

Each stub sets only `race_name`, `race_id`, `race_description`, size, and basic stat modifiers. All are **missing**: SDC/MDC values, combat bonuses, natural weapons, resistances/immunities/vulnerabilities, racial abilities, OCC restrictions, alignment restrictions, languages, factions, starting gear.

| Stub Race | Missing |
|-----------|---------|
| `rahu_man.lpc` | All abilities, MDC, OCC restrictions |
| `kankoran.lpc` | Abilities, natural weapons, pack-sense |
| `ratling.lpc` | Abilities, natural weapons |
| `silver_bells_faerie.lpc` | Magic potential, fae abilities |
| `werebear.lpc` | Lycanthrope abilities, MDC war form |
| `weretiger.lpc` | Lycanthrope abilities, MDC war form |
| `wild_psi_stalker.lpc` | ISP sensing, psionic abilities |
| `hawrk_ka.lpc` / `hawrke_duhk.lpc` | Full Hawrk stats |
| `jotan.lpc` / `titan.lpc` | Giant abilities, enormous SDC |
| `ice_dragon.lpc` / `fire_dragon.lpc` | Dragon breath, MDC, abilities |
| `thunder_lizard_dragon.lpc` | Dragon abilities |
| `coyle.lpc` / `equinoid.lpc` / `conservator.lpc` | RCC abilities |
| `bogie.lpc` | Fae abilities |
| `bearman.lpc` / `basilisk.lpc` | Natural weapons, petrification |
| `gurgoyle.lpc` | Flight, MDC |
| `night_elves_faerie.lpc` | Abilities |
| `nimro_fire_giant.lpc` | Giant abilities |
| `secondary_vampire.lpc` / `wild_vampire.lpc` | Vampire powers |
| `pogtal_dragon_slayer.lpc` | Abilities |
| `promethean.lpc` / `noli.lpc` / `eandroth.lpc` | Alien/outsider abilities |
| `simvan.lpc` / `trimadore.lpc` / `uteni.lpc` | Coalition/Rifts abilities |
| `cat_girl.lpc` | Mutant abilities |
| `dragon_hatchling.lpc` | Should be RCC with full MDC |

### OCCs (`lib/occs/`) — 5 files with TODO markers or incomplete content

| File | Issue |
|------|-------|
| `coalition_grunt.lpc` | 1 TODO line — equipment package incomplete |
| `cyber_doc.lpc` | 1 TODO — cybernetics treatment mechanics pending |
| `psi_mystic.lpc` | 1 TODO — psionic power list placeholder |
| `tattooed_man.lpc` | 2 TODOs — tattoo-magic mechanics not implemented; falls back to melee |
| `undead_slayer.lpc` | 2 TODOs — silver/holy weapon bonus not wired |
| `pending.lpc` | 7-line placeholder; does NOT inherit `/std/occ`; crashes if OCC methods called |

### Skills (`lib/skills/`) — 144 of 155 files have `TODO:CONTENT` or unimplemented `perform()`

Categories with zero working `perform()` implementations:
- **Rogue skills (11):** streetwise, safecracking, disguise, pick_locks, impersonation, forgery, pick_pockets, palming, gambling, prowl, concealment — all have skeleton `perform() { return 0; }` stubs.
- **Modern weapons (6):** rifle, pistol, revolver, shotgun, SMG, heavy MD — stubs.
- **Medical (multiple):** paramedic, medical_doctor, field_surgery, forensics — stubs.
- **Pilot skills:** all stubs.
- **9 entire categories have zero working files:** communications, domestic, electrical, espionage, mechanical, military, science, wilderness, technical (partial).

### Psionics (`lib/psionics/`) — ~9 files with stubs

- `healing/increased_healing.lpc` — stub `activate()`.
- `physical/pyrokinesis.lpc` — stub `activate()`.
- 7 additional powers with `TODO:CONTENT` or empty `activate()` bodies.

### Spells (`lib/spells/`) — Partial coverage

- JSON reference data (in `lib/spells/level_*.json`) covers 75 spells.
- LPC files exist for 77 spells — but levels 4–9 are sparsely covered.
- `lib/std/spell.lpc::apply_effect()` returns `1` with comment "Override me" — any spell that forgets to override will silently do nothing when cast.

### Commands — Wiztool-delegating stubs

The following commands work only if a wiztool is attached; they contain no independent logic:
- `lib/cmds/eval.lpc` — delegates `wt->process_command("eval", args)`; no standalone LPC evaluation.
- `lib/cmds/cd.lpc` — delegates to wiztool.
- `lib/cmds/clone.lpc` — delegates to wiztool.
- `lib/cmds/goto.lpc` — player-goto works; room-path goto delegates to wiztool.

### Admin Commands — Partial stubs

- `lib/cmds/admin/orb.lpc` — "Pending requests: (stub)" and "Server uptime: (stub)" in `admin_orb` sub-commands (lines 82, 85).
- `lib/cmds/admin/stat.lpc` — Reports only 4 fields (file name, OID, short desc, environment); a complete `stat` should show inventory, properties, living stats, etc.
- `lib/cmds/admin/shutdown.lpc` — Comment says "Should add security check here"; no privilege gate on the `shutdown()` call.

### Domain Areas — Incomplete or Minimal

- **`lib/domains/tutorial/`** — Only 3 files: `rooms/start.lpc` (stub room, no description, no exits), `objects/weapon.lpc`, `npc/guard.lpc`. The tutorial is not playable.
- **`lib/domains/forest/`** — Only 1 file: `rooms/void.lpc`. The forest domain is empty.
- **`lib/domains/chi_town/`** — 6 files (entry, gate, market, 2 NPCs, 1 object). No interior rooms, no shops, no quest content.
- **`lib/domains/castle/`** — 2 files (entry room, Spike NPC). Single-room stub domain.
- **`domains/code/workroom.lpc`** and **`domains/rp/workroom.lpc`** — Exist at top-level `domains/` (outside `lib/`) which is outside the LPC path. Possibly orphaned files.

### C Engine — Known Stubs/TODOs

- **`src/driver.c:749`** — `/* TODO: Shout to adjacent rooms (requires room linkage) */` — `shout` command does not propagate to adjacent rooms.
- **`src/room.c:574`** — `TODO:VM-DISPATCH` — `init()` callback on player room arrival not yet wired; NPCs that rely on `init()` for aggro trigger won't activate when a player walks in.
- **`src/room.c:930`** — New Camelot rooms 4–10 are C stub rooms, not LPC-backed yet.
- **`src/item.c:1206,1245`** — `TODO:VM-BRIDGE` — property delta replay not implemented; `delta_count` always 0. Item property changes after creation may not persist correctly.
- **`src/race_loader.c:552,559`** — `TODO:INTEGRATION` — OCC combat bonus mappings and `set_attacks_per_round()` not yet applied at the C level.
- **`src/chargen.h:166`** — `TODO:VM-BRIDGE` — `query_skill_bonus()` must route through `obj_call_method()` but doesn't yet.
- **`src/chargen.c:1064`** — `(int)strlen(...)` cast: `strlen()` returns `size_t`; casting to `int` can truncate on 64-bit systems if string length exceeds `INT_MAX`. Not a practical risk for character names but technically incorrect.

### Save Format

- New Character struct fields (`save_vs_*`, `racial_abilities`, `race_skill_bonus`) are not in save format v11; they will be silently dropped on save/load cycles.

---

## ❌ Missing / Not Implemented

### `lib/etc/` — Does not exist

Referenced in design docs as the location for config flags and server metadata files. The directory does not exist.

### `lib/races/` — Missing `add_resistance()`, `add_immunity()`, `add_vulnerability()`

`race.lpc::apply_to_player()` calls `player->add_resistance()`, `player->add_immunity()`, `player->add_vulnerability()`, `player->add_faction()`, and `player->set_hostile_faction()`. **None of these methods exist in `living.lpc`**. All racial resistances, immunities, vulnerabilities, and faction assignments are **silently dropped** for every race at character creation.

### `lib/std/armor.lpc` — Missing `query_slot()`

`wear.lpc` line 28 calls `function_exists("query_slot", item)`. `armor.lpc` does not define `query_slot()`. Any armor that only inherits the base class **cannot be worn** — the command prints "You can't wear that." Every piece of armor in the game needs to explicitly define `query_slot()` or the base class must add it.

### `lib/std/weapon.lpc` — Missing key fields

- No `query_slot()` method (wield.lpc guards with `function_exists` so not fatal, but slots are untracked).
- No weight, reach, rate of fire, ammo capacity, AP value, or any Palladium weapon stat beyond damage.
- No damage bonus field.

### `lib/std/living.lpc` — Cybernetics & combat bonuses silently discarded

`set_max_cybernetics()`, `set_cybernetics_allowed()`, `add_cybernetic()`, and `add_combat_bonus()` are all explicit `/* stub */` no-ops. The cybernetics system and OCC-granted combat bonuses (`combat_progression` table in `occ.lpc::level_up()`) are completely non-functional.

### Intermud / MudNet

`lib/daemon/intermud.lpc` exists but its implementation status is unknown (not audited for depth). Cross-MUD chat, player locator, and mail are not verified working.

### Vehicle system

`lib/std/vehicle.lpc` and `lib/std/vehicle_room.lpc` exist but are not wired to player commands. `lib/cmds/drive.lpc` and `lib/cmds/pilot.lpc` exist. No actual vehicle objects in any domain.

### Clan system

`lib/cmds/clan.lpc` exists. No clan database daemon, no clan storage, no clan membership tracking.

### Shemarria / Coven Base (Splynn)

Referenced in `BOOT_READY.md` as upcoming domain content. No files exist.

### Quest system

No quest daemon, quest state tracking, or quest journal. No `lib/daemon/quest.lpc`.

### Mail system

No in-game mail. No `lib/daemon/mail.lpc`.

### Board / bulletin board system

No boards in any domain. No `lib/std/board.lpc`.

### Bank system

`lib/cmds/balance.lpc` and `lib/cmds/exchange.lpc` exist. No bank daemon or account persistence.

### Auction system

Not present.

### Crafting system

Not present.

### `lib/saves/VampireTest.save` and `lib/saves/CyberKnightTest.save`

Both are placeholder text files, not real player save files.

---

## 🐛 Bugs & Issues Found

### HIGH Severity

1. **`lib/cmds/go.lpc:67` — Room has no `look()` method**  
   After a successful move, `tell_object(player, dest->look())` is called. `room.lpc` defines no `look()` method. This call returns 0/null — **the player sees nothing upon entering a room**. Fix: call the `look` command via `player->force_me("look")` or compose output from `dest->query_short()` + `dest->query_long()` + exits directly.

2. **`lib/std/armor.lpc` — `query_slot()` missing**  
   All armor inheriting only the base class cannot be worn. `wear.lpc:28` fails the `function_exists("query_slot", item)` check and returns "You can't wear that." Fix: add `string query_slot() { return "body"; }` to `armor.lpc`.

3. **`lib/std/race.lpc::apply_to_player()` — 5 missing methods on `living.lpc`**  
   `add_resistance()`, `add_immunity()`, `add_vulnerability()`, `add_faction()`, `set_hostile_faction()` are called but do not exist. All racial resistances, immunities, and faction assignments silently fail for every race. Fix: add these methods to `living.lpc` with appropriate data storage.

4. **`lib/cmds/admin/shutdown.lpc` — No privilege gate**  
   `shutdown()` is called without checking the caller's privilege level. Any player who can access this command path (e.g. via wiztool injection) could shut down the server. Fix: add `if (previous_object()->query_privilege_level() < 2)` guard.

### MEDIUM Severity

5. **`lib/std/living.lpc` — Cybernetics & combat bonuses are no-ops**  
   `set_max_cybernetics()`, `set_cybernetics_allowed()`, `add_cybernetic()`, `add_combat_bonus()` are all `/* stub */` no-ops. `occ.lpc::apply_to_player()` and `level_up()` call these; cybernetics limits and `combat_progression` table bonuses are silently dropped.

6. **`lib/cmds/help.lpc:306,315,324,333,343,353` — Raw ANSI in help headers**  
   Six `write("\033[1m--- Help: ... ---\033[0m\n")` calls emit bold ANSI escape codes in LPC fallback help section headers. **Violates Rule 1** (no ANSI except WHO, room exits, tells). Fix: remove bold markers, use plain text headers.

7. **`lib/cmds/admin/promote.lpc:97,131,137` — Raw ANSI in tell messages**  
   Uses `\033[1;33m`, `\033[1;32m`, and `\033[1m` in `tell_object()` calls to the promoted player. **Violates Rule 1**. Fix: remove ANSI from `tell_object()` lines (already approved for tells only for player-to-player tells; wizard promotion ceremony messages are admin-to-player, not player-to-player).

8. **`lib/cmds/sirname.lpc:84,99,100,159,162,163` — Raw ANSI in non-approved contexts**  
   Six ANSI escape uses in sirname-request and sirname-grant notification messages. **Violates Rule 1**. Fix: remove ANSI markup.

9. **`src/room.c:574` — `init()` never called on player arrival**  
   NPCs set to aggressive via `init()` callbacks will not attack players who walk into their room. This breaks standard MUD aggro behavior. Fix: wire `TODO:VM-DISPATCH` for per-move `init()` callback.

10. **`src/race_loader.c:552,559` — OCC combat bonuses not applied at C level**  
    After race/OCC loading at chargen, `set_attacks_per_round()` and OCC combat bonus mappings are not applied to the C-level `Character` struct. Players may start with fewer attacks than their OCC specifies.

### LOW Severity

11. **`lib/cmds/who.lpc:33` — Apprentice wizards shown as green `[Roleplay]`**  
    The file header specifies apprentice creators (wizard with no role yet) should be shown in cyan. The code maps all unroled wizards to the `[Roleplay]` (green) case. There is no cyan path.

12. **`lib/cmds/admin/stat.lpc` — Uses `previous_object()` instead of `this_player()`**  
    Should use `this_player()` to identify the command issuer.

13. **`lib/domains/tutorial/rooms/start.lpc` — Wrong inheritance**  
    File says `inherit "/std/object"` but is a room. Should be `inherit "/std/room"`. Has no exits and cannot be navigated.

14. **`lib/domains/tutorial/npc/guard.lpc` — Wrong inheritance path**  
    Uses `inherit "std/living.c"` (relative path + `.c` extension). Should be `inherit "/std/living"` or `inherit "/std/npc"`.

15. **`lib/domains/new_camelot/garden/npc/magic_bush.lpc` — Full-path inheritance**  
    Uses `inherit "/lib/std/living.lpc"` (includes the `lib/` prefix and `.lpc` extension). Path resolution depends on `MUDLIB_ROOT` matching. Should be `inherit "/std/living"`.

16. **`lib/std/occ.lpc::apply_to_player()` — Equipment clone paths unverified**  
    Calls `clone_object(item_path)` for standard equipment packages using paths like `/obj/item/backpack`. These object files are not confirmed to exist; failed clones return 0 silently.

17. **`lib/occs/pending.lpc` — Does not inherit `/std/occ`**  
    Defines bare stubs for `query_occ_name()`, `query_occ_id()`, `get_occ_info()`, and empty `create()`. Will crash if any real OCC method is called on it.

18. **`src/item.c:1206,1245` — Property delta replay not implemented**  
    `delta_count` always 0. Item property changes after initial creation (e.g., damage to a weapon during play) may not correctly persist through save/load cycles.

19. **`domains/code/workroom.lpc` and `domains/rp/workroom.lpc` exist outside `lib/`**  
    These files are at the repository root `domains/` directory, not under `lib/domains/`. They are outside the LPC include path and will never be loaded by the driver. Likely orphaned/leftover files.

20. **`lib/secure/simul_efun.lpc:5-11,96-103` — ANSI constants defined globally**  
    The simul_efun file defines `BOLD`, `RED`, `GREEN`, etc. as global strings and a full `color_code()` lookup table. These are available to all LPC objects, making it trivial to accidentally (or intentionally) use colors in non-approved contexts. The constants themselves are not a violation, but their broad availability makes Rule 1 enforcement rely entirely on developer discipline.

---

## 📋 Priority Work Queue

1. **Fix `go.lpc:67` — Room look on arrival** *(HIGH, 1 line fix)*  
   Change `tell_object(player, dest->look())` to `player->force_me("look")`. This is the single most player-visible bug — every room transition is silent.

2. **Fix `armor.lpc` — Add `query_slot()` to base class** *(HIGH, 3 line fix)*  
   Add `string query_slot() { return "body"; }` to `lib/std/armor.lpc`. Without this, no armor can be worn.

3. **Fix `living.lpc` — Add resistance/immunity/vulnerability/faction methods** *(HIGH, ~30 lines)*  
   Add `add_resistance()`, `add_immunity()`, `add_vulnerability()`, `add_faction()`, `set_hostile_faction()` with proper data structures. All racial combat advantages are currently lost at chargen.

4. **Fix `shutdown.lpc` — Add admin privilege gate** *(HIGH, 2 line fix)*  
   Add `if (previous_object()->query_privilege_level() < 2) { write("No.\n"); return 1; }` at top of `main()`.

5. **Wire `init()` callback on room arrival (`src/room.c:574`)** *(HIGH, ~20 lines C)*  
   Implement the `TODO:VM-DISPATCH` for per-move `init()`. Without this, NPC aggro and room-entry events don't fire.

6. **Implement cybernetics storage in `living.lpc`** *(MEDIUM, ~40 lines)*  
   Convert `set_max_cybernetics()`, `add_cybernetic()` stubs to real data storage. Also implement `add_combat_bonus()` with a mapping store so `occ.lpc::level_up()` bonuses accumulate correctly.

7. **Fix ANSI Rule 1 violations** *(MEDIUM, ~20 line changes across 4 files)*  
   Remove raw `\033[` codes from `help.lpc` (6 sites), `promote.lpc` (3 sites), `sirname.lpc` (6 sites). Also fix `who.lpc` cyan/apprentice case.

8. **Wire OCC combat bonuses at C level (`src/race_loader.c:552,559`)** *(MEDIUM, ~30 lines C)*  
   Implement `set_attacks_per_round()` and OCC combat bonus map application in the race/OCC loading path.

9. **Fix tutorial domain** *(MEDIUM, ~100 LPC lines)*  
   Correct `rooms/start.lpc` inheritance from `object` to `room`, add exits, add proper description. Fix `npc/guard.lpc` inheritance path.

10. **Flesh out ~28 skeletal race stubs** *(HIGH content effort)*  
    Prioritize the most-selected races: `kankoran`, `rahu_man`, `hawrk_ka`, `werebear`, `weretiger`, `wild_psi_stalker`, `cat_girl`, `dragon_hatchling`. Add MDC/SDC, natural weapons, racial abilities, OCC restrictions.

11. **Implement rogue skill `perform()` bodies** *(MEDIUM, 11 files × ~50 lines)*  
    `prowl`, `streetwise`, `pick_locks`, `pick_pockets`, `safecracking`, `disguise`, `palming`, `concealment`, `gambling`, `forgery`, `impersonation`.

12. **Implement modern weapon skills `perform()` bodies** *(MEDIUM, 6 files × ~30 lines)*  
    Rifle, pistol, revolver, shotgun, SMG, heavy MD.

13. **Fix item property delta replay (`src/item.c:1206,1245`)** *(MEDIUM, ~40 lines C)*  
    Implement `TODO:VM-BRIDGE` property delta tracking so item state changes persist through save/load.

14. **Build forest and chi_town domains** *(LOW–MEDIUM, significant content work)*  
    Forest has 1 void room. Chi_town has only 6 files. Both should connect to the main world.

15. **Implement clan daemon** *(LOW priority, ~300 LPC lines)*  
    `lib/cmds/clan.lpc` exists but has no backend.

16. **Add `query_slot()` to domain armor objects** *(LOW, sweep all domain `obj/` directories)*  
    Until base `armor.lpc` is fixed (#2 above), any domain armor without explicit `query_slot()` cannot be worn.

17. **Implement quest system** *(LOW, deferred)*  
    Quest daemon, state tracking, journal command.

18. **Remove orphaned `domains/` top-level directory** *(Housekeeping)*  
    `domains/code/workroom.lpc` and `domains/rp/workroom.lpc` are outside `lib/` and will never be loaded.

19. **Fix `stat.lpc`** — expand to show all living stats, inventory, properties; change `previous_object()` to `this_player()`.

20. **Add production settings to `config/runtime.conf`** *(LOW)*  
    `RUN_AS_USER`, `LOG_DIR`, TLS configuration, `MAX_CLIENTS` override.

---

## 📁 Directory Map

| Directory | Purpose |
|-----------|---------|
| `src/` | All C engine source (VM, compiler, server, combat, magic, psionics, skills, items, NPCs, death, websocket, wiz tools, etc.) |
| `src/driver.c` | Main MUD server — 6,471 lines; handles connections, login, chargen, commands, heartbeat |
| `lib/` | All LPC game code root (MUD lib directory, served as virtual filesystem root) |
| `lib/secure/` | Highest-privilege LPC files: master object, simul_efun, char_create, install, motd, wiz_perms, formatting |
| `lib/std/` | Base LPC classes: living, player, npc, room, object, weapon, armor, shop, spell, skill, occ, race, daemon, vehicle, wiztool, etc. |
| `lib/std/qcs/` | Quick Content System builder tools: room, npc, barkeep, vendor, door, armor, weapon, item templates |
| `lib/clone/` | Transient per-connection objects: login.lpc (pre-auth), user.lpc (authenticated player) |
| `lib/daemon/` | Persistent server-side service objects: chargen, combat, skills, spells, languages, psionics, npc_daemon, login, command, intermud |
| `lib/cmds/` | Player command LPC files (verb → file mapping) |
| `lib/cmds/admin/` | Admin-only commands (promote, demote, stat, goto, warmboot, shutdown, wiztool, etc.) |
| `lib/cmds/creator/` | Creator/domain-wizard tools (cat, cd, clone, create, deploy, ed, eval, find, force, grep, load, ls, mkdir, mkobject, mkroom, etc.) |
| `lib/cmds/wizard/` | Wizard commands (clone, destruct, eval, language, reload, setocc, update) |
| `lib/cmds/wiz/` | Additional wizard shortcuts (eval, giveskill, set, update) |
| `lib/cmds/dragon/` | Dragon race-specific commands (breath) |
| `lib/cmds/players/` | Legacy player command location (contains emote.c in `.c` extension — likely orphaned) |
| `lib/races/` | 86 LPC race definition files for all Palladium Rifts races |
| `lib/occs/` | 63 LPC OCC/RCC definition files |
| `lib/skills/` | 155 LPC skill files across 14 subdirectories (physical, weapons, technical, medical, pilot, rogue, wilderness, science, electrical, mechanical, espionage, communications, domestic, military) |
| `lib/spells/` | 77 LPC spell files in level subdirectories (level1–level15); plus JSON reference data (level_1.json through level_15.json) |
| `lib/psionics/` | ~69 LPC psionic power files in category subdirectories |
| `lib/languages/` | LPC language definition files |
| `lib/domains/` | All playable game areas |
| `lib/domains/start/` | Starting area: village center, lake, shop, orientation room, tutorial NPCs |
| `lib/domains/new_camelot/` | New Camelot: full town with 20 garden rooms, tavern, blacksmith, stables, chapel, training grounds, falconer |
| `lib/domains/splynn/` | Splynn Dimensionals: tutorial entry, catacombs dungeon, black market, juicer clinic, Rocky's bar, library, stat chamber |
| `lib/domains/staff_castle/` | Staff Castle: 11 rooms + 3-room hedge maze, Spike NPC |
| `lib/domains/wizard/` | Wizard Castle (staff offices) + 13 personal workrooms |
| `lib/domains/death/` | Death recovery area: recovery room + healer NPC |
| `lib/domains/admin/` | Admin area: start room, orientation room, the_system NPC |
| `lib/domains/chi_town/` | Chi-Town stub: entry, gate, market (very incomplete) |
| `lib/domains/castle/` | Castle stub: 2 files, effectively empty |
| `lib/domains/forest/` | Forest stub: 1 void room only |
| `lib/domains/tutorial/` | Tutorial stub: 3 files, not playable |
| `lib/wiz/` | Physical wizard tool objects cloned into wizard inventory at promotion |
| `lib/test/` | In-game LPC test scripts (integration_smoke_test, clone_test, test_dragon, etc.) |
| `lib/data/help/` | Static help text files (commands, concepts, spells, systems, wizard paths) |
| `lib/saves/` | Player save files (`.o` format); also holds placeholder `VampireTest.save` / `CyberKnightTest.save` |
| `lib/creators/` | Creator documentation (readme.md) |
| `lib/tools/` | LPC/shell dev tools: `generate_stubs.sh` (OCC/race/skill stub generator) |
| `lib/log/` | Runtime log files (server.log, wizard.log, debug_priv.log, promotions log) |
| `build/` | Compiled binary (`build/driver`) and build artifacts (`build/.warnings.txt`) |
| `config/` | Runtime configuration: `runtime.conf`, `example.runtime.conf`, `project-report.md` |
| `scripts/` | Development/maintenance shell scripts and Python utilities (cleanup, normalization, duplicate analysis, TTRPG JSON conversion) |
| `tests/` | C unit tests (16 binaries), Python integration tests, shell integration tests |
| `tests/lpc/` | Small LPC programs used as compiler/VM test inputs |
| `docs/` | Project documentation: implementation-plan.md, content-audit.md, lpc-room-system.md, new-camelot-migration.md, summary |
| `diagnostics/` | Build warning logs and TODO scan output (historical state records) |
| `REPORTS/` | Integration test run notes, stub review CSV checklist, stub triage document, wiztool test run |
| `tools/` | Developer tools: LLM index builder, help-file checker, QCS audit TSV, stub inventories, UI demo, ws_client HTML, ws_telnet_proxy (Node.js + Python) |
| `lpc-extension/` | VS Code extension providing LPC syntax highlighting (TextMate grammar, snippets) |
| `logs/` | Build and test run output logs |
| `data/` | Server banner text (`banner.txt`), one-off shell scripts |
| `domains/` | **Orphaned top-level directory** (outside `lib/`); contains `code/workroom.lpc` and `rp/workroom.lpc` — not reachable by driver |
| `.github/workflows/` | CI pipeline: `ci.yml` with build / test / warnings jobs |
