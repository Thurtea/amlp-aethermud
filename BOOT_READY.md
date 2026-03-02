# AetherMUD — Boot Ready

## Date
2026-03-01

## What Works
- 86 races fully implemented
- 63 OCCs fully implemented
- 69 psionics fully implemented (4 categories: physical, sensitive, healing, super)
- 77 spells implemented across all 15 levels
- Full wizard hierarchy: Admin, Domain, Code, RP
- Secure bcrypt password storage
- Save/restore on disconnect and quit
- Verb-based combat (no numeric damage)
- In-game file editor (ed)
- QCS tools: room, npc, barkeep, vendor, door
- WHO/users commands: ANSI rank flags (Admin=red, Domain=blue, Coding=cyan, RP=green); players see only population tier + staff count
- Serena NPC in Splynn — paid remote viewing of online players (500 UC via `remoteview <name>`)
- 152 commands (99 player-facing, 53 wizard/admin)
- Splynn Catacombs: train platform, 4 dungeon rooms, skeleton warriors, Obsidian Blade (25% rare spawn)
- Juicer conversion clinic (Doc Voss, 10000 UC, permanent psionic/magic lock)
- Splynn Library + Spell-Teaching Scroll (one-use per player)
- Stat Enhancement Chamber (one-use +1 stat per player)
- Combat skill rolls: 1d20 + combat_skill vs 10 + dodge

## Known Gaps (Next Sprint)
- Spell activation not yet wired to combat loop (spells defined, cast command exists, damage routing incomplete)
- Splynn: all major areas wired; vehicle-train to Shemarria and Coven Base pending
- Economy: shop daemon stub in lib/std/shop.lpc — buy/sell wired; room-level shop objects needed per area
- Vehicle system not wired
- Juicer OCC conversion process not in-game (OCC defined, process room/NPC not built)
- Merc group base system not implemented
- Smuggler UC/BMC exchange ability not implemented

## Design Seeds (From Original Mud — Build When Ready)
- **Rocky's Bar (Splynn)**: Barkeep NPC; use `qcs create barkeep rocky`.
  Rocky sells drinks and carries a 100 MDC rechargeable armor talisman (PPE-powered,
  activates from inventory, works on most races). Good use of the new barkeep + vendor types.
- **Splynn Black Market**: Hidden door behind a knockable pillar south of Rocky's.
  `qcs create door black_market_entrance` with no key; trigger opens it via room action.
  Vendor inside sells predator-style stealth armor, net launchers, and black market gear.
  Black market items use BMC currency.
- **Stat Boost Chamber**: Room in Splynn that lets players roll to improve one attribute
  before OCC selection. Flag on pfile prevents using it twice.
- **Spell-Teaching Scroll**: Item in Splynn library. `read scroll` teaches one spell permanently.
  Implement as an object with a `do_read` that calls `player->learn_spell(spell_id)`.
- **Smuggler UC/BMC Exchange**: Smuggler OCC ability: `exchange <amount> to bmc` /
  `exchange <amount> to uc` at a configurable rate that improves with level.
  Can be offered as a paid service to other players.
- **Secret Unlockable Classes**: Pattern already established with Sunaj Assassin via `clan aerihman`.
  Extend with more post-creation unlock paths (quests, items, faction standing).
- **Juicer Conversion Process**: Dedicated room sequence with an NPC surgeon.
  Player commits their character (flagged `juicer_process_complete`), gains juicer bonuses,
  loses the ability to use psionics or magic permanently.
- **Catacombs / Obsidian Blade**: Dungeon area with the obsidian blade as a rare spawn.
  Train in Splynn leads there; amulet + card combo for Shemarria rail gun run.
- **Merc Group Bases**: `qcs create room` + vendor NPC combo for automated base generation.
  Player inputs group name; QCS stamps out a linked set of rooms under their domain folder.

## How To Boot
```
cd ~/amlp-aethermud
make
./mud.sh
```

## Connect
```
telnet localhost 3000
```
