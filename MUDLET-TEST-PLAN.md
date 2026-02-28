# AetherMUD — Mudlet Test Plan

**Date:** 2026-02-28
**Driver:** Custom C (AMLP), telnet port 3000
**Mudlib:** lib/ (LPC, AMLP enhanced)

---

## Prerequisites

| Item | Value |
|------|-------|
| Server start | `./mud.ctl start` |
| Telnet port | 3000 |
| Mudlet connection | Host: `localhost`, Port: `3000` |
| Alias file | `mudlet/aethermud.xml` (if present) |

---

## Section 1 — Connection and Login

### 1.1 Fresh connection
- [ ] Open Mudlet → New Profile → `localhost:3000`
- [ ] Receive welcome banner (no garbled text)
- [ ] Prompted for character name

### 1.2 First admin (Thurtea)
- [ ] Enter name: `Thurtea`
- [ ] Set password (new account flow)
- [ ] Confirm password
- [ ] Receive no chargen prompts — land directly in world
- [ ] Verify admin rank: type `stats` — privilege level shows 2 (Admin)
- [ ] Verify admin message broadcast appears

### 1.3 Existing player login
- [ ] Log out: `quit`
- [ ] Reconnect → enter `Thurtea` → enter saved password
- [ ] Land in last saved room without re-doing chargen
- [ ] Stats, inventory, credits preserved

### 1.4 Test character login (Splynncryth)
- [ ] Connect as `Splynncryth` (new account)
- [ ] No chargen — lands in world as Player rank
- [ ] Type `stats` — confirms privilege level 0

---

## Section 2 — Character Creation (Normal Player)

### 2.1 Chargen flow
- [ ] Connect as a new name (e.g., `Torva`)
- [ ] Set and confirm password
- [ ] Race selection list appears (87 races)
- [ ] Select a non-dragon race (e.g., Human)
- [ ] OCC selection list appears
- [ ] Select an OCC (e.g., Cyber-Knight)
- [ ] Stats rolling: stats displayed, option to re-roll or confirm
- [ ] Alignment selection (Good/Selfish/Evil)
- [ ] Secondary skill selection (pick 3)
- [ ] Land in village center
- [ ] `look` shows room description

### 2.2 Dragon race (RCC path)
- [ ] Connect as new char, select Great Horned Dragon
- [ ] OCC selection is skipped
- [ ] Dragon Hatchling RCC auto-assigned
- [ ] Land in starting area

---

## Section 3 — Test Characters via Admin Orb

### 3.1 Setup
Log in as Thurtea first. The admin orb is in inventory after promotion.

- [ ] Log in additionally as `test_ck` in a second Mudlet tab
- [ ] Log in as `test_sunaj` in a third tab
- [ ] Log in as `test_dragon` in a fourth tab
- [ ] Back in Thurtea: type `setup_test_chars`
- [ ] Confirm output: "Setting up 3 test character(s)..."
- [ ] Each test char receives gear notification in their tab

### 3.2 test_ck verification (Human Cyber-Knight L15)
- [ ] `inventory` — shows light plate armor, vibro-sword, laser pistol, e-clip
- [ ] `stats` — level 15, PS 18, PP 17, PE 16, IQ 16
- [ ] `wear light plate armor` — equips successfully
- [ ] `wield vibro sword` — equips successfully
- [ ] `equipment` — shows worn armor and wielded weapon

### 3.3 test_sunaj verification (Atlantean Sunaj Assassin L15)
- [ ] `inventory` — shows shadow armor, vibro-knife, laser pistol, darkness grenade, e-clip
- [ ] `stats` — level 15, appropriate stats
- [ ] `wear shadow armor` → equips
- [ ] `wield vibro knife` → equips
- [ ] `examine shadow armor` — shows stealth bonus description

### 3.4 test_dragon verification (Great Horned Dragon L15)
- [ ] `inventory` — empty (no gear expected for dragons)
- [ ] `stats` — level 15, PS 30, PE 28, SPD 22
- [ ] `look` — room description visible

---

## Section 4 — Movement and Navigation

- [ ] `look` / `l` — room description
- [ ] `exits` — list of available exits
- [ ] `north` / `n` — move north (or appropriate exit)
- [ ] `south` / `s` — move back
- [ ] Movement blocked on invalid exit: "You can't go that way."
- [ ] Room names display correctly on entry

---

## Section 5 — Communication Commands

- [ ] `say Hello` — room sees "Thurtea says: Hello"
- [ ] `' Hello` — shorthand say works
- [ ] `emote waves` — room sees "Thurtea waves"
- [ ] `: waves` — shorthand emote works
- [ ] `shout Test shout` — all players receive shout
- [ ] `tell <other_player> Hi` — private message delivered
- [ ] `chat Testing` — chat channel message

---

## Section 6 — Information Commands

- [ ] `who` — lists online players with correct ranks/colors
  - Admin: red
  - Wizard: yellow
  - Player: default
- [ ] `score` — character score sheet
- [ ] `stats` — full stat block (IQ/ME/MA/PS/PP/PE/PB/SPD, HP, SDC/MDC, credits)
- [ ] `inventory` / `i` — lists carried items
- [ ] `equipment` / `eq` — lists equipped items
- [ ] `skills` — lists character skills
- [ ] `help` — help system responds
- [ ] `time` / `date` — server time displayed

---

## Section 7 — Item Interaction

- [ ] `take <item>` — pick up an item on the ground
- [ ] `drop <item>` — drop carried item
- [ ] `put <item> in <container>` — put item in container
- [ ] `give <item> to <player>` — give item to another online player
- [ ] `examine <item>` — shows long description
- [ ] `examine vibro sword` — shows vibro-sword long desc
- [ ] `examine shadow armor` — shows stealth bonus text

---

## Section 8 — Equipment Commands

- [ ] `wear <armor>` — equips armor
- [ ] `wield <weapon>` — equips weapon in hand
- [ ] `remove <armor>` — unequips armor
- [ ] `unwield <weapon>` — unequips weapon
- [ ] `equipment` — shows currently equipped items

---

## Section 9 — Combat

- [ ] Find an NPC (New Camelot guard in appropriate room)
- [ ] `consider <npc>` — shows difficulty estimate
- [ ] `attack <npc>` / `kill <npc>` — initiates combat
- [ ] Combat messages appear every 2 seconds (heartbeat tick)
- [ ] `flee` — exits combat to a random adjacent room
- [ ] NPC dies: corpse appears, loot possible
- [ ] `firstaid` — requires first_aid skill; heals SDC on success

---

## Section 10 — Position Commands

- [ ] `sit` — sit down; room sees "Thurtea sits down."
- [ ] `stand` — stand up
- [ ] `sleep` — lie down; room sees "Thurtea falls asleep."
- [ ] `wake` — wake up

---

## Section 11 — Wizard Tools (rank 1 — Wizard)

To test, promote a test player: as Thurtea, `promote test_ck 1`

- [ ] Promotion message broadcasts to room
- [ ] test_ck receives id_card and code_tool in inventory
- [ ] test_ck teleported to their workroom

### 11.1 id_card
- [ ] `identify <object>` — full stat block for an item or NPC
- [ ] `finger <player>` — shows player profile (title, race, idle, location)

### 11.2 code_tool
- [ ] `update /lib/std/room.lpc` — reload room object, confirm "Updated."
- [ ] `errors` — shows last 20 lines of /log/debug_priv.log

---

## Section 12 — Admin Tools (rank 2 — Admin)

As Thurtea (auto-admin).

### 12.1 crystal_ball
- [ ] `goto <player>` — teleport to player's location
- [ ] `goto /domains/wizard/thurtea/workroom` — teleport to path
- [ ] `trans <player>` — bring target to your location

### 12.2 wizard_staff
- [ ] `force <player> look` — player executes `look`
- [ ] `force` on equal/higher rank: "You cannot force someone of equal or higher rank."
- [ ] `invis` — "You fade from view."
- [ ] `vis` — "You become visible again."

### 12.3 admin_wand
- [ ] `promote <player> 1` — promotes to Wizard
- [ ] `promote <player> 0` — demotes to Player (same as demote)
- [ ] `demote <player>` — demotes to Player rank
- [ ] `shutdown` (DO NOT RUN unless intended) — broadcasts shutdown and halts driver

### 12.4 admin_orb
- [ ] `mudstats` — shows player count, staff count, uptime, WHO table
- [ ] `purge <offline_player>` — removes save file for named offline player
- [ ] `setup_test_chars` — sets up all online test_* characters

---

## Section 13 — Monolithic Wiztool Commands

As any wizard+ character with the monolithic wiztool.

- [ ] `ls /lib/cmds/` — lists command files
- [ ] `cd /lib/single/` — changes working directory
- [ ] `pwd` — shows current working directory
- [ ] `cat /lib/single/vibro_sword.lpc` — prints file contents
- [ ] `eval 1+1` — evaluates LPC expression, returns 2
- [ ] `update /lib/wiz/admin_orb.lpc` — reloads the orb object
- [ ] `goto <player_or_path>` — teleport (if crystal_ball present, uses crystal_ball)
- [ ] `stat <object>` — shows object properties
- [ ] `clone /lib/single/vibro_sword` — clones an object into the room

---

## Section 14 — Save and Load

- [ ] `save` — saves character, confirms "Character saved."
- [ ] Note stats/credits/inventory
- [ ] `quit`
- [ ] Log back in → verify all stats, credits, inventory match
- [ ] Equipped items are re-equipped after load

---

## Section 15 — Edge Cases

- [ ] Unknown command: "Unknown command: foo" + help hint
- [ ] Say with no args: appropriate error or empty say
- [ ] Take nonexistent item: "You don't see that here."
- [ ] Attack yourself: appropriate error message
- [ ] `promote <self> 3` — refused (max level 2)
- [ ] Player tries `orb` without carrying admin orb — unknown command (not granted)
- [ ] Player tries `purge` without orb — unknown command

---

## Section 16 — Clan System

- [ ] Create an Atlantean character
- [ ] `clan` — shows no clan affiliation
- [ ] `clan aerihman` — joins clan, unlocks Sunaj Assassin OCC
- [ ] OCC re-selection now shows Sunaj Assassin as available option

---

## Notes

- **Privilege levels**: 0=Player, 1=Wizard, 2=Admin (no level 3 exists)
- **test_* login**: characters with `test_` prefix skip chargen automatically
- **Thurtea**: always auto-promoted to admin on any new account creation
- **Workrooms**: created at `/domains/wizard/<lowercase_name>/workroom.lpc`
- **NPC heartbeat**: fires every 2 seconds; respawn delay set per NPC
- **Combat tick**: 2-second real-time heartbeat
- **Corpse decay**: 300 seconds (5 minutes) after NPC death
