# AMLP Driver - Command Testing Checklist
**Date:** February 1, 2026  
**Server:** localhost:3000 (telnet) / localhost:3001 (websocket)

## Overview
This checklist covers all implemented commands for Player (Level 0), Wizard (Level 1), and Admin (Level 2) privilege levels.

---

## Test Setup

### Create Test Characters
Connect via: `nc localhost 3000`

1. **Player Account:** username `testplayer` (default privilege: 0)
2. **Wizard Account:** username `testwizard` (will be promoted to level 1)
3. **Admin Account:** username `testadmin` (will be promoted to level 2)

### Promote Test Accounts
After creating all three accounts, connect as `testadmin` and run:
```
promote testwizard 1
promote testadmin 2
```

---

## PLAYER COMMANDS (Level 0) - Everyone can use these

### Basic Commands
- [ ] `help` - Shows command list
- [ ] `look` or `l` - View room description
- [ ] `stats` or `score` - View character stats
- [ ] `who` - List online players
- [ ] `save` - Manually save character
- [ ] `quit` or `logout` - Save and disconnect

### Communication
- [ ] `say <message>` - Say something to the room
  - Test: `say Hello, everyone!`
  - Expected: Others in room see: "testplayer says: Hello, everyone!"
  
- [ ] `emote <action>` - Perform an emote
  - Test: `emote waves enthusiastically`
  - Expected: Others see: "testplayer waves enthusiastically"

### Inventory
- [ ] `inventory` or `i` - Check inventory
  - Expected: "You are carrying nothing." (not implemented yet)

### Movement Commands
- [ ] `north` or `n` - Move north
- [ ] `south` or `s` - Move south
- [ ] `east` or `e` - Move east
- [ ] `west` or `w` - Move west
- [ ] `up` or `u` - Move up
- [ ] `down` or `d` - Move down

### Movement Test Route (from The Void):
```
n      -> Chi-Town Plaza
e      -> Coalition HQ
w      -> Back to Plaza
w      -> Merchant District
e      -> Back to Plaza
s      -> The Void
```

---

## WIZARD COMMANDS (Level 1+) - Requires privilege_level >= 1

### Teleportation
- [ ] `goto <room_id>` - Teleport to a specific room
  - Test: `goto 0` - Teleport to The Void
  - Test: `goto 1` - Teleport to Chi-Town Plaza
  - Test: `goto 2` - Teleport to Coalition HQ
  - Test: `goto 3` - Teleport to Merchant District
  - Test: `goto 99` - Invalid room (should fail)
  - Expected: "vanishes in a puff of smoke" / "appears in a puff of smoke"

### Object Creation
- [ ] `clone <object>` - Create an object
  - Test: `clone sword`
  - Test: `clone shield`
  - Test: `clone potion`
  - Test: `clone invalid` - Unknown object (should fail)
  - Expected: Success messages describing object creation

### Permission Tests (as Player)
- [ ] Try `goto 1` as testplayer - Should see: "You don't have permission"
- [ ] Try `clone sword` as testplayer - Should see: "You don't have permission"

---

## ADMIN COMMANDS (Level 2) - Requires privilege_level >= 2

### User Management
- [ ] `promote <player> <level>` - Change user privilege
  - Test: `promote testplayer 1` - Make wizard
  - Test: `promote testplayer 0` - Demote to player
  - Test: `promote testplayer 3` - Invalid level (should fail)
  - Test: `promote nonexistent 1` - Player not found (should fail)

- [ ] `users` - Show detailed user list
  - Expected: Table showing Name, Privilege, Idle time
  - Should show all connected users with privilege levels

### Server Control
- [ ] `shutdown` - Shut down server (WARNING: actually shuts down)
  - Test with delay: `shutdown 10` - Shuts down in 10 seconds
  - Expected: Broadcast message to all users
  - **NOTE:** Only test this when ready to restart server!

### Permission Tests (as Wizard and Player)
- [ ] Try `promote` as testwizard - Should see: "You don't have permission"
- [ ] Try `users` as testwizard - Should see: "You don't have permission"
- [ ] Try `shutdown` as testwizard - Should see: "You don't have permission"
- [ ] Try `promote` as testplayer - Should see: "You don't have permission"

---

## CHARACTER PERSISTENCE TESTS

### Save/Load Tests
1. [ ] Create character, move to different room, type `save`
2. [ ] Type `quit` - Should auto-save
3. [ ] Reconnect with same username
4. [ ] Verify character loads in correct room
5. [ ] Verify stats are restored
6. [ ] Test with multiple characters

### Auto-Save Tests
- [ ] After character creation - Should see " Character saved!"
- [ ] Before quit - Should see " Character saved."
- [ ] Manual save command - Should see " Character saved successfully."

---

## MULTI-USER INTERACTION TESTS

### Two Players in Same Room
1. [ ] Connect as testplayer and testwizard
2. [ ] Have both go to Chi-Town Plaza
3. [ ] Type `look` - Should see other player listed under "Also here:"
4. [ ] Have one player `say hello` - Other should see it
5. [ ] Have one player `emote dances` - Other should see it
6. [ ] Have one player move away - Other should see departure message
7. [ ] Have the player return - Others should see arrival message

### Wizard Teleportation with Observers
1. [ ] Have testplayer in Chi-Town Plaza
2. [ ] Have testwizard `goto 1` to Plaza
3. [ ] testplayer should see: "testwizard appears in a puff of smoke."
4. [ ] Have testwizard `goto 0` away
5. [ ] testplayer should see: "testwizard vanishes in a puff of smoke."

---

## ERROR HANDLING TESTS

### Invalid Commands
- [ ] Type gibberish command - Should see: "Unknown command: <cmd>"
- [ ] Type `help` to verify available commands

### Invalid Arguments
- [ ] `goto` (no args) - Should show usage
- [ ] `clone` (no args) - Should show available objects
- [ ] `promote testplayer` (missing level) - Should show usage
- [ ] `promote` (no args) - Should show usage

### Permission Boundaries
- [ ] Player tries wizard command - Permission denied
- [ ] Player tries admin command - Permission denied
- [ ] Wizard tries admin command - Permission denied
- [ ] Admin can use all commands - All should work

---

## ROOM SYSTEM TESTS

### Room 0: The Void
- [ ] Description displays correctly
- [ ] Exit: north (to Chi-Town Plaza)
- [ ] Can move north successfully

### Room 1: Chi-Town Plaza
- [ ] Description displays correctly
- [ ] Exits: south (Void), east (Coalition HQ), west (Merchant District)
- [ ] All exits work correctly
- [ ] Can return to starting positions

### Room 2: Coalition Headquarters
- [ ] Description displays correctly
- [ ] Exit: west (back to Plaza)
- [ ] Movement works correctly

### Room 3: Merchant District
- [ ] Description displays correctly
- [ ] Exit: east (back to Plaza)
- [ ] Movement works correctly

### Movement Edge Cases
- [ ] Try invalid direction (e.g., `n` from Coalition HQ) - Should see: "You can't go that way"
- [ ] Try movement shortcuts (n/s/e/w/u/d) - All should work
- [ ] Movement messages broadcast to other players in room

---

## STRESS TESTS

### Multiple Concurrent Users
- [ ] 3+ users online simultaneously
- [ ] All can move independently
- [ ] `who` command shows all users
- [ ] Chat/emotes work between users
- [ ] Privilege levels display correctly in `who` list

### Rapid Command Execution
- [ ] Execute 10+ commands rapidly
- [ ] Server remains responsive
- [ ] No memory leaks or crashes
- [ ] All commands execute correctly

---

## KNOWN LIMITATIONS / NOT YET IMPLEMENTED

The following are listed in help but not fully functional:
- Inventory system (items don't persist, but clone creates messages)
- Combat system
- Skills/spells/psionics (race/OCC selection exists, but abilities not hooked up)
- NPCs (no monsters/guards yet)
- Equipment system
- Experience/leveling beyond level 1

The following LPC files exist but aren't used (C bypass mode):
- All files in `lib/cmds/` (LPC command files)
- All files in `lib/daemon/` (LPC daemon files)  
- All files in `lib/races/`, `lib/occs/`, `lib/skills/`, `lib/spells/`, `lib/psionics/`

**Note:** The server is using C-based implementation, bypassing the LPC parser which has known issues.

---

## Test Results Log

Date: ________________
Tester: ________________

### Player Commands
Pass: ____ / 15  
Failed: ______________________________________________

### Wizard Commands  
Pass: ____ / 8
Failed: ______________________________________________

### Admin Commands
Pass: ____ / 5
Failed: ______________________________________________

### System Tests
Pass: ____ / 12
Failed: ______________________________________________

### Overall Pass Rate: ______%

---

## Bug Reports / Issues Found

1. ___________________________________________________________
2. ___________________________________________________________
3. ___________________________________________________________
4. ___________________________________________________________
5. ___________________________________________________________

---

## Server Control Commands

**Start Server:** `cd /home/thurtea/amlp-driver && ./mud.ctl start`  
**Stop Server:** `cd /home/thurtea/amlp-driver && ./mud.ctl stop`  
**Restart Server:** `cd /home/thurtea/amlp-driver && ./mud.ctl restart`  
**Check Status:** `ps aux | grep build/driver`  

**Connect (Telnet):** `nc localhost 3000`  
**Connect (Mudlet):** Add server `localhost:3000`

**Logs:** `/home/thurtea/amlp-driver/logs/driver.log`  
**Save Files:** `/home/thurtea/amlp-driver/lib/save/players/`
