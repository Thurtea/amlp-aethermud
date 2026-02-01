# AMLP MUD - Complete Implementation Roadmap
**Created:** February 1, 2026  
**Goal:** Transform from 4/4 to 50/35 races/OCCs + full RPG systems

---

## 📊 Current State Assessment

### ✅ Complete (100%)
- Server infrastructure (telnet + websocket)
- 20 commands (player/wizard/admin)
- Character persistence (save/load)
- Room system (4 rooms)
- Multi-user support
- Privilege levels
- Authentication system

### ⚠️ Partial (8-11%)
- **Races:** 4/50 working (8%)
- **OCCs:** 4/35 working (11%)

### ❌ Not Implemented (0%)
- Skills system
- Spells system
- Psionics system
- Combat system
- Equipment system
- NPC system
- Inventory with actual items
- Economy/shops
- Quests

---

## 🎯 PHASE 1: Complete Race/OCC Implementation (CURRENT)
**Timeline:** 1-2 days  
**Priority:** HIGH - Foundation for all character-based systems

### Tasks:

#### 1.1 Expand Race Selection (4 → 50 races)
- [x] Audit all 50 race LPC files for stat modifiers
- [ ] Implement paginated race selection menu
- [ ] Add all 50 races to chargen.c
- [ ] Implement race-specific stat bonuses
- [ ] Add race descriptions
- [ ] Test each race creation

**Races to Add (46 new):**
```
adult_dragon, ancient_dragon, brodkil, burster, cat_girl, changeling,
cosmo_knight, deevil, demon, dog_boy, dragon_juicer, eandroth, gargoyle,
gnome, goblin, godling, halfling, hobgoblin, mega_juicer, mind_bleeder,
mind_melter, minion, minotaur, mutant_animal, nightbane, noli, ogre,
orc, promethean, psi_ghost, psi_healer, psi_stalker, quick_flex, simvan,
splugorth, splugorth_minion, splynn_slave, thorny_dragon, titan_juicer,
trimadore, troll, true_atlantean, uteni, vampire, werewolf, wolfen
```

#### 1.2 Expand OCC Selection (4 → 35 OCCs)
- [ ] Audit all 35 OCC LPC files for abilities
- [ ] Implement paginated OCC selection menu
- [ ] Add all 35 OCCs to chargen.c
- [ ] Implement OCC-specific starting stats
- [ ] Add ISP/PPE allocation by OCC
- [ ] Add OCC descriptions
- [ ] Test each OCC creation

**OCCs to Add (31 new):**
```
battle_magus, biomancer, body_fixer, burster, city_rat, cosmo_knight,
crazy, dragon_hatchling_rcc, elemental_fusionist, full_conversion_borg,
headhunter, juicer, line_walker, mercenary, mind_melter, mystic,
necromancer, operator, power_armor_pilot, psi_healer, psi_stalker,
robot_pilot, rogue_scholar, sea_titan, shifter, special_forces,
stone_master, temporal_wizard, vagabond, warlock, wilderness_scout
```

#### 1.3 Race/OCC Interaction System
- [ ] Validate race/OCC combinations (some are incompatible)
- [ ] Implement RCC (Racial Character Classes) rules
- [ ] Add race-specific OCC restrictions
- [ ] Add combined bonuses

**Deliverables:**
- Modified chargen.c with all 50 races + 35 OCCs
- Paginated selection menus
- Race/OCC stat modifier system
- Updated help text and descriptions

**Success Criteria:**
- Player can select any of 50 races
- Player can select any of 35 OCCs (with validation)
- Stats correctly reflect race + OCC modifiers
- All combinations save/load correctly

---

## 🎯 PHASE 2: Skills System
**Timeline:** 3-5 days  
**Priority:** HIGH - Required for meaningful character progression  
**Depends on:** Phase 1 complete

### 2.1 Core Skills Infrastructure
- [ ] Create skills.c / skills.h
- [ ] Define skill data structure (name, category, base %, modifiers)
- [ ] Parse skill files from lib/skills/
- [ ] Implement skill check system (1d100 vs skill %)
- [ ] Add skills to character save file

### 2.2 Skill Categories
**Physical Skills:**
- [ ] Climbing, Swimming, Running, Acrobatics
- [ ] Hand to Hand (Basic, Expert, Martial Arts)

**Technical Skills:**
- [ ] Computer Operations, Electronics, Mechanics
- [ ] Pilot (Automobile, Hovercycle, Power Armor, Robot)
- [ ] Literacy, Mathematics, Language

**Weapons Proficiencies:**
- [ ] WP Energy Rifle, WP Energy Pistol
- [ ] WP Sword, WP Knife, WP Blunt
- [ ] WP Heavy Weapons

**Medical Skills:**
- [ ] First Aid, Paramedic, Cybernetic Medicine

**Wilderness Skills:**
- [ ] Tracking, Survival, Land Navigation

### 2.3 OCC Skill Packages
- [ ] Assign starting skills by OCC
- [ ] Implement skill selection during chargen
- [ ] Add skill advancement on level up

### 2.4 Skill Commands
- [ ] `skills` - List all skills with percentages
- [ ] `use <skill>` - Use a skill
- [ ] `practice <skill>` - Skill training

**Deliverables:**
- skills.c with full skill system
- 50+ skills implemented
- Skill checks working
- OCC-specific skill packages

---

## 🎯 PHASE 3: Combat System
**Timeline:** 5-7 days  
**Priority:** HIGH - Core gameplay loop  
**Depends on:** Phase 1, 2 complete

### 3.1 Combat Infrastructure
- [ ] Create combat.c / combat.h
- [ ] Define combat state machine
- [ ] Initiative system (based on SPD + 1d20)
- [ ] Attack/defense roll system
- [ ] Damage calculation

### 3.2 Combat Commands
- [ ] `attack <target>` - Initiate combat
- [ ] `strike <target>` - Melee attack
- [ ] `shoot <target>` - Ranged attack
- [ ] `dodge` - Defensive action
- [ ] `parry` - Block attack
- [ ] `flee` - Run from combat

### 3.3 Damage & Death
- [ ] HP/SDC damage tracking
- [ ] Critical hits (natural 20)
- [ ] Death mechanics
- [ ] Respawn system
- [ ] Experience from combat

### 3.4 Combat Balance
- [ ] Weapon damage tables
- [ ] Armor AR/SDC values
- [ ] PS damage bonuses
- [ ] Strike/parry/dodge bonuses from PP

**Deliverables:**
- Working turn-based combat
- Attack/damage/death cycle
- Experience from victories
- Combat messages and feedback

---

## 🎯 PHASE 4: Equipment & Inventory
**Timeline:** 3-5 days  
**Priority:** MEDIUM - Enhances gameplay depth  
**Depends on:** Phase 3 complete

### 4.1 Item System
- [ ] Create item.c / item.h
- [ ] Define item types (weapon, armor, consumable, misc)
- [ ] Item properties (weight, value, stats)
- [ ] Item persistence in save files

### 4.2 Inventory Management
- [ ] Weight limit (based on PS)
- [ ] `get <item>` - Pick up item
- [ ] `drop <item>` - Drop item
- [ ] `give <item> <player>` - Trade items
- [ ] Better `inventory` display

### 4.3 Equipment System
- [ ] Equipment slots (weapon, armor, accessories)
- [ ] `equip <item>` - Wear/wield item
- [ ] `unequip <item>` - Remove item
- [ ] Stat bonuses from equipment
- [ ] Equipment restrictions by OCC

### 4.4 Initial Item Database
**Weapons (20+):**
- [ ] Vibro-Blade (2d4 MD)
- [ ] NG-57 Ion Blaster (3d6 MD)
- [ ] Wilk's Laser Rifle (3d6 MD)
- [ ] Neural Mace (stun weapon)
- [ ] Heavy plasma cannon

**Armor (15+):**
- [ ] Urban Warrior EBA (50 MDC)
- [ ] Huntsman Armor (60 MDC)
- [ ] Glitter Boy Armor (770 MDC)
- [ ] Light body armor
- [ ] Coalition SAMAS power armor

**Consumables (10+):**
- [ ] Health potions (restore HP)
- [ ] PPE crystals (restore magic)
- [ ] ISP boosters (restore psionics)
- [ ] Food/water

**Deliverables:**
- 50+ items in game
- Functional inventory system
- Equipment slots working
- Item spawns in rooms

---

## 🎯 PHASE 5: Magic & Psionics
**Timeline:** 5-7 days  
**Priority:** MEDIUM - Core to setting  
**Depends on:** Phase 3 complete

### 5.1 Psionics System
- [ ] Create psionics.c / psionics.h
- [ ] ISP cost system
- [ ] Psionic power structure (Healing, Physical, Sensitive, Super)
- [ ] Power activation command: `use <power>`

**Powers to Implement (20+):**
- [ ] Mind Block (super)
- [ ] Telekinesis (physical)
- [ ] Sixth Sense (sensitive)
- [ ] Bio-Regeneration (healing)
- [ ] Telepathy (sensitive)
- [ ] Pyrokinesis (super)
- [ ] Mind Blast (super)

### 5.2 Magic System
- [ ] Create magic.c / magic.h
- [ ] PPE cost system
- [ ] Spell levels (1-15)
- [ ] Spell casting command: `cast <spell> [target]`
- [ ] Spell components (for some spells)

**Spells to Implement (30+):**
- [ ] Magic Armor (level 1)
- [ ] Fireball (level 5)
- [ ] Teleport (level 10)
- [ ] Rift Teleportation (level 15)
- [ ] Lightning Bolt
- [ ] Summon Lesser Demon

### 5.3 OCC Power Assignment
- [ ] Assign starting powers by OCC
- [ ] Power selection during chargen
- [ ] Power advancement on level up
- [ ] Power restrictions by OCC type

**Deliverables:**
- 20+ psionic powers working
- 30+ magic spells working
- ISP/PPE resource management
- Power/spell progression system

---

## 🎯 PHASE 6: NPC & Creature System
**Timeline:** 4-6 days  
**Priority:** MEDIUM - Brings world to life  
**Depends on:** Phase 3, 5 complete

### 6.1 NPC Infrastructure
- [ ] Create npc.c / npc.h
- [ ] NPC data structure (like player but AI-controlled)
- [ ] NPC spawn system
- [ ] NPC persistence in rooms

### 6.2 NPC AI Behaviors
- [ ] Idle behavior (wander, emote)
- [ ] Dialogue system
- [ ] Merchant behavior (buy/sell)
- [ ] Guard behavior (attack hostiles)
- [ ] Quest giver behavior

### 6.3 Initial NPCs (20+)
**Friendly NPCs:**
- [ ] Coalition Officer (quest giver)
- [ ] Black Market Dealer (merchant)
- [ ] Techno-Wizard (merchant, enchanter)
- [ ] Bar Patron (dialogue)
- [ ] City Guard (protector)

**Hostile NPCs:**
- [ ] Coalition Grunt (enemy)
- [ ] Deadboy Squad Leader (tough enemy)
- [ ] Brodkil Demon (monster)
- [ ] Xiticix Warrior (insect monster)
- [ ] Splugorth Slaver (villain)

### 6.4 NPC Commands
- [ ] `talk <npc>` - Start dialogue
- [ ] `buy <item> [from <npc>]` - Purchase
- [ ] `sell <item> [to <npc>]` - Sell item
- [ ] `give <item> <npc>` - Quest items

**Deliverables:**
- 20+ NPCs in world
- Basic AI behaviors
- Merchant system
- NPC combat

---

## 🎯 PHASE 7: Economy System
**Timeline:** 2-3 days  
**Priority:** LOW - Quality of life  
**Depends on:** Phase 4, 6 complete

### 7.1 Currency
- [ ] Add "credits" to character save file
- [ ] Starting credits by OCC
- [ ] Display credits in `stats`
- [ ] Credit drops from enemies

### 7.2 Shops
- [ ] Shop data structure (inventory, prices)
- [ ] Buy/sell mechanics
- [ ] Price variation by location
- [ ] Merchant reputation

### 7.3 Loot System
- [ ] Item drops from enemies
- [ ] Loot tables by enemy type
- [ ] Rare item drops
- [ ] Corpse looting

**Deliverables:**
- Working economy
- 5+ shops in world
- Buy/sell commands
- Loot drops from combat

---

## 🎯 PHASE 8: World Expansion
**Timeline:** 5-7 days (ongoing)  
**Priority:** MEDIUM - Content depth  
**Depends on:** Phase 1-6 complete

### 8.1 Room Expansion (4 → 50+ rooms)
**Chi-Town District (15 rooms):**
- [ ] Plaza (hub)
- [ ] Coalition HQ levels
- [ ] Slums
- [ ] Bar/tavern
- [ ] Weapon shop
- [ ] Armor shop
- [ ] Magic shop
- [ ] Residential area

**Wilderness (15 rooms):**
- [ ] Forest areas
- [ ] Ruins of old city
- [ ] Ley line nexus
- [ ] Xiticix hive entrance
- [ ] Abandoned bunker

**Special Locations (20 rooms):**
- [ ] Tolkeen (magic city)
- [ ] Free Quebec
- [ ] Lazlo (scholar city)
- [ ] Splynn Dimensional Market
- [ ] Lone Star Complex

### 8.2 Room Features
- [ ] Room objects (furniture, containers)
- [ ] Hidden exits (requires search)
- [ ] Locked doors (requires keys)
- [ ] Environmental effects (ley line energy)
- [ ] Room-specific events

**Deliverables:**
- 50+ interconnected rooms
- Multiple cities/regions
- Environmental variety
- Hidden areas

---

## 🎯 PHASE 9: Quest System
**Timeline:** 4-6 days  
**Priority:** MEDIUM - Player motivation  
**Depends on:** Phase 6, 8 complete

### 9.1 Quest Infrastructure
- [ ] Create quest.c / quest.h
- [ ] Quest data structure (objectives, rewards)
- [ ] Quest tracking in save file
- [ ] Quest log command: `quests`

### 9.2 Quest Types
- [ ] Kill quests (defeat X enemies)
- [ ] Fetch quests (bring item to NPC)
- [ ] Delivery quests (take item to location)
- [ ] Exploration quests (discover location)
- [ ] Dialogue quests (talk to NPCs)

### 9.3 Initial Quests (10+)
- [ ] "Coalition Threat" - Kill 5 Coalition soldiers
- [ ] "Lost Relic" - Find ancient tech in ruins
- [ ] "Supply Run" - Deliver package to Tolkeen
- [ ] "Demon Hunt" - Defeat Brodkil demon
- [ ] "Dimensional Rescue" - Save prisoner from Splugorth

### 9.4 Rewards
- [ ] XP rewards
- [ ] Credit rewards
- [ ] Item rewards
- [ ] Reputation gains

**Deliverables:**
- 10+ quests in game
- Quest tracking system
- Quest rewards
- Quest log display

---

## 🎯 PHASE 10: Advanced Features
**Timeline:** 7-10 days (ongoing)  
**Priority:** LOW - Polish and depth  
**Depends on:** All previous phases

### 10.1 Character Advancement
- [ ] Level up system (1-15)
- [ ] XP requirements per level
- [ ] Stat increases on level up
- [ ] Skill point allocation
- [ ] New powers/spells per level

### 10.2 Guilds & Factions
- [ ] Guild data structure
- [ ] Coalition States faction
- [ ] Tolkeen faction
- [ ] Black Market faction
- [ ] Reputation system
- [ ] Faction-specific quests

### 10.3 Player Housing
- [ ] Purchasable apartments/houses
- [ ] Item storage (like a bank)
- [ ] Furniture/decoration
- [ ] Housing costs (rent/mortgage)

### 10.4 Crafting System
- [ ] Techno-Wizard enchanting
- [ ] Weapon modifications
- [ ] Armor repairs
- [ ] Potion brewing (for mystics)
- [ ] Recipe system

### 10.5 PvP System
- [ ] PvP arenas
- [ ] Duel challenge command
- [ ] PvP restrictions (no griefing)
- [ ] PvP rewards/rankings

### 10.6 Social Features
- [ ] Mail system (send messages offline)
- [ ] Friends list
- [ ] Ignore list
- [ ] Tells (private messages)
- [ ] Channels (guild chat, OOC)

---

## 📅 Complete Timeline

### Immediate (Week 1)
- **Days 1-2:** Phase 1 - All 50 races + 35 OCCs ← **YOU ARE HERE**

### Short Term (Weeks 2-4)
- **Days 3-7:** Phase 2 - Skills System
- **Days 8-14:** Phase 3 - Combat System
- **Days 15-19:** Phase 4 - Equipment & Inventory

### Medium Term (Months 2-3)
- **Days 20-26:** Phase 5 - Magic & Psionics
- **Days 27-32:** Phase 6 - NPC System
- **Days 33-35:** Phase 7 - Economy

### Long Term (Months 3-6)
- **Days 36-42:** Phase 8 - World Expansion
- **Days 43-48:** Phase 9 - Quest System
- **Days 49+:** Phase 10 - Advanced Features (ongoing)

**Total Development Time:** ~6-8 months for complete Rifts MUD

---

## 🎯 Success Metrics

### Phase 1 Complete (Race/OCC)
- ✅ 50 races selectable
- ✅ 35 OCCs selectable
- ✅ All combinations work
- ✅ Stat modifiers correct

### MVP Complete (Phases 1-4)
- ✅ Full character creation
- ✅ Skills working
- ✅ Combat functional
- ✅ Equipment system
- ✅ 20+ rooms
- **= Playable MUD**

### Full Game Complete (All Phases)
- ✅ All 85 race/OCC combinations
- ✅ 50+ skills
- ✅ 50+ spells/powers
- ✅ 50+ items
- ✅ 20+ NPCs
- ✅ 50+ rooms
- ✅ 10+ quests
- ✅ Economy working
- **= Professional MUD**

---

## 🚀 Current Priority: Phase 1

**Next Steps (Today):**
1. ✅ Create this roadmap
2. [ ] Implement paginated menu system
3. [ ] Add all 50 races to chargen.c
4. [ ] Add all 35 OCCs to chargen.c
5. [ ] Test all combinations
6. [ ] Commit and tag release v0.2.0

**Time Estimate:** 4-6 hours

Let's begin! 🎮
