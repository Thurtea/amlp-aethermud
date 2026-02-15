"# AetherMUD Spell/Psionic Refactor Primer - Part 1/3"

## 1. Project Overview

- AetherMUD is a Rifts RPG text-based multiplayer game (MUD). It uses a custom C driver (~15,000 lines) implementing core systems and runtime behavior for the game world.

- The server exposes an LPC scripting layer used for many in-game behaviors, but the spell and psionic systems are currently implemented in C inside the driver for performance and integration reasons.

- At present players invoke magical or psionic effects by prefixing the ability with a verb: spells are used with `cast <name>` and psionics with `manifest <name>`.

- The refactor goal is to make individual spell and psionic names act as direct commands (for example, `tongues` instead of `cast tongues`), improving discoverability, allowing shorter input flows, and enabling more flexible command dispatch logic.

- Relevant documentation to consult during this refactor includes `LPC_INFRASTRUCTURE_MAP.md` and `INTEGRATION_ROADMAP.md` which map how the C driver and LPC layers interact and outline integration points.

## 2. Character Data Structures

The driver defines the following C structures relevant to spells and psionics (from `src/chargen.h`). These exact typedefs are used by the codebase:

```c
typedef struct Spell {
    int id;
    char *name;              // e.g., "Tongues", "Swim as a Fish"
    int level;
    int ppe_cost;
    int duration;            // In rounds
    int damage_dice;
    int damage_sides;
} Spell;

typedef struct PsionicPower {
    int id;
    char *name;              // e.g., "Telepathy", "Remote Viewing"
    int category;            // 1=healing, 2=physical, 3=sensitive, 4=super
    int isp_cost;
    int duration;
    int damage_dice;
    int damage_sides;
} PsionicPower;

typedef struct Character {
    // ... many other fields ...
    
    Spell *spells;                    // Dynamic array of known spells
    int num_spells;                   // Count of spells in array
    
    PsionicPower *psionic_powers;     // Dynamic array of known powers
    int num_psionic_powers;           // Count of powers in array
    
    // Magic resources
    struct {
        int ppe_current;
        int ppe_max;
        bool is_meditating;
        int meditation_rounds_active;
        // ... other magic fields ...
    } magic;
    
    // Psionic resources
    struct {
        int isp_current;
        int isp_max;
        bool is_meditating;
        int meditation_rounds_active;
        // ... other psionic fields ...
    } psionics;
    
    // ... many other fields ...
} Character;
```

Explanations:

- `Spell` / `PsionicPower` fields:
  - `id`: numeric identifier for the spell/power (used internally).
  - `name`: pointer to a NUL-terminated string describing the ability (user-facing).
  - `level` / `category`: organizational metadata used for learning, restrictions, or UI grouping.
  - `ppe_cost` / `isp_cost`: resource cost to activate the ability.
  - `duration`: how long the effect lasts, in combat rounds.
  - `damage_dice` / `damage_sides`: classic dN-dM style damage representation.

- `Character` fields (relevant parts):
  - `Spell *spells`: pointer to a heap-allocated array (dynamic) of `Spell` entries the character knows.
  - `int num_spells`: number of valid entries in the `spells` array.
  - `PsionicPower *psionic_powers`: same pattern for psionic powers.
  - `int num_psionic_powers`: count for the psionic array.

- How the arrays work:
  - Arrays are dynamically allocated (e.g., via `malloc`/`realloc`) and owned by the `Character` instance.
  - The `num_spells` / `num_psionic_powers` counters indicate how many elements are currently valid.
  - To iterate: `for (int i = 0; i < ch->num_spells; ++i) { Spell *s = &ch->spells[i]; /* use s */ }`.

- Accessing PPE/ISP values:
  - Use nested struct syntax, for example: `ch->magic.ppe_current` and `ch->psionics.isp_current`.

- Memory management notes:
  - The `spells` and `psionic_powers` pointers reference heap memory; code must `free()` or `realloc()` them appropriately when adding/removing abilities or when destroying the `Character`.
  - Individual `name` fields are `char *` strings and may also require allocation/freeing depending on how names are stored (common patterns: shared interned strings vs. per-structure strdup).

Examples:

- Check if a character can afford a spell:

```c
if (ch->magic.ppe_current >= s->ppe_cost) {
    /* can cast */
}
```

- Iterate known psionics and print commands:

```c
for (int i = 0; i < ch->num_psionic_powers; ++i) {
    PsionicPower *p = &ch->psionic_powers[i];
    printf("Known: %s\n", p->name);
}
```

## 3. Name Conversion Algorithm

The primary challenge for the dispatcher is converting multi-word ability names like "Swim as a Fish" into a canonical single-word command `swimasafish` for matching. Below is a safe, bounded C implementation with comments:

```c
/* Convert spell/psionic name to command format */
/* Input: "Swim as a Fish" or "Remote Viewing" */
/* Output: "swimasafish" or "remoteviewing" */

char spell_cmd[64] = {0};           // Null-initialize 64-byte buffer
const char *src = spell->name;      // Source pointer to spell name
char *dst = spell_cmd;              // Destination pointer to buffer

while (*src && (dst - spell_cmd) < 63) {  // While not end AND space remains
    if (*src != ' ' && *src != '-') {     // Skip spaces and hyphens
        *dst++ = (char)tolower((unsigned char)*src); // Lowercase and copy char
    }
    src++;                                 // Advance source
}
*dst = '\0';                               // Null-terminate
```

Why each step matters:

- We skip spaces and hyphens so users can type either the full phrase or a compact form without punctuation — i.e., `cast swim as a fish` and `swimasafish` map the same way. This improves convenience and avoids users needing to remember exact spacing or punctuation.
- We use `tolower()` to perform case-insensitive matching so commands behave the same regardless of typed case (`Tongues`, `tongues`, `TONGUES`). It's applied per-character during copy.
- The buffer is sized to 64 bytes as a safety margin for the longest reasonable spell name; this prevents extremely long names from overflowing the stack buffer.
- The check `(dst - spell_cmd) < 63` ensures we leave room for the NUL terminator and prevents buffer overflow by limiting the number of written characters to 63.
- Result example: input `"Swim as a Fish"` becomes `"swimasafish"` and `"Remote Viewing"` becomes `"remoteviewing"`.

## 4. Current Command Dispatcher Pattern

Command parsing and dispatch in the driver follow a simple string comparison pattern. The snapshot below (from `src/driver.c` around command parsing) demonstrates the approach:

```c
// Command parsing in apply_native_function()
char cmd[256] = {0};
const char *args = NULL;

// Parse command and arguments
if (session_input) {
    sscanf(session_input, "%255s", cmd);
    args = strchr(session_input, ' ');
    if (args) args++;  // Skip the space
}

// Convert to lowercase
for (int i = 0; cmd[i]; i++) {
    cmd[i] = tolower((unsigned char)cmd[i]);
}

// Command dispatch chain
if (strcmp(cmd, "look") == 0) {
    // Handle look command
    return result;
}

if (strcmp(cmd, "kill") == 0 || strcmp(cmd, "attack") == 0) {
    // Handle attack command
    return result;
}

if (strcmp(cmd, "score") == 0) {
    // Handle score command
    return result;
}

// ... many more commands ...

// At the very end (THIS IS WHERE WE INSERT):
return vm_value_create_string("Unknown command. Type 'help' for assistance.\r\n");
```

Key points:

- Commands are normalized to lowercase and compared with `strcmp()` for exact matches.
- `args` points to everything after the first space (or is `NULL` if no arguments were provided), and is used by command handlers to parse arguments.
- Each command handler returns a `VMValue` (or equivalent result) back to the caller; this is how results and messages are propagated to the session.
- The "Unknown command" fallback is the final return path. Our dynamic dispatcher for spell/psionic commands must be invoked just before this fallback — if a typed token matches a converted `spell_cmd` or `psionic_cmd`, we should handle it and return the appropriate `VMValue`.
- Dispatch pattern to follow when inserting ability commands:
  - Convert input `cmd` into the same canonical form used for ability names (remove spaces/hyphens, lowercase).
  - Search the character's known abilities arrays (`ch->spells`, `ch->psionic_powers`) for a matching canonical name.
  - If found and resources allow, invoke the existing C activation logic and return its `VMValue` result.

Examples for clarity:

- User types `Swim as a Fish` currently as `cast swim as a fish`. After the refactor they could instead type `swimasafish` and the dispatcher will:
  - Normalize `swimasafish` (already canonical), find it in `ch->spells`, check `ch->magic.ppe_current >= ppe_cost`, then execute the spell handler and return the resulting `VMValue`.

- If no match is found in any ability list, the code falls through and returns the existing "Unknown command" `VMValue` so existing help behavior remains intact.

---

Do not proceed to sections 5–10 yet; this file contains Part 1/3 as requested. Review these sections and tell me when you're ready to continue with Parts 2/3.

## 5. Dynamic Command Dispatcher Implementation

This is the core of the refactor. The dispatcher must be inserted in `src/driver.c` RIGHT BEFORE the "Unknown command" return statement.

```c
/* ========== DYNAMIC SPELL/PSIONIC COMMAND DISPATCHER ========== */
/* This section checks if the typed command matches any known spell */
/* or psionic power name after name normalization. */
/* Insert this BEFORE the "Unknown command" fallback return. */

/* Step 1: Check if this is a known spell */
for (int i = 0; i < session->character.num_spells; i++) {
  Spell *spell = &session->character.spells[i];
    
  /* Convert spell name to command format (lowercase, no spaces/hyphens) */
  char spell_cmd[64] = {0};
  const char *src = spell->name;
  char *dst = spell_cmd;
  while (*src && (dst - spell_cmd) < 63) {
    if (*src != ' ' && *src != '-') {
      *dst++ = (char)tolower((unsigned char)*src);
    }
    src++;
  }
  *dst = '\0';
    
  /* Does the typed command match this spell? */
  if (strcmp(cmd, spell_cmd) == 0) {
    /* SPELL COMMAND MATCHED - now handle casting */
        
    /* Parse target from args (NULL/empty = self-cast) */
    PlayerSession *target = NULL;
        
    if (!args || !args) {
      /* No target specified - cast on self */
      target = session;
    } else {
      /* Find target player in current room */
      Room *room = session->current_room;
      if (room) {
        for (int j = 0; j < room->num_players; j++) {
          if (strcasecmp(room->players[j]->username, args) == 0) {
            target = room->players[j];
            break;
          }
        }
      }
            
      if (!target) {
        send_to_player(session, "You don't see '%s' here.\n", args);
        result.type = VALUE_NULL;
        return result;
      }
    }
        
    /* Check PPE cost */
    if (session->character.magic.ppe_current < spell->ppe_cost) {
      send_to_player(session, "You need %d P.P.E. to cast %s (you have %d).\n",
        spell->ppe_cost, spell->name, session->character.magic.ppe_current);
      result.type = VALUE_NULL;
      return result;
    }
        
    /* Deduct PPE */
    session->character.magic.ppe_current -= spell->ppe_cost;
        
    /* Announce casting */
    send_to_player(session, "You cast %s! (%d P.P.E. spent)\n", 
      spell->name, spell->ppe_cost);
        
    /* Broadcast to room (excluding caster) */
    if (session->current_room) {
      for (int j = 0; j < session->current_room->num_players; j++) {
        PlayerSession *other = session->current_room->players[j];
        if (other != session) {
          char race_name[128];
          get_introduced_name(other, session, race_name, sizeof(race_name));
          send_to_player(other, "%s casts %s!\n", race_name, spell->name);
        }
      }
    }
        
    /* Apply spell effect (calls existing function) */
    apply_spell_effect(session, spell, target);
        
    result.type = VALUE_NULL;
    return result;
  }
}

/* Step 2: Check if this is a known psionic power */
for (int i = 0; i < session->character.num_psionic_powers; i++) {
  PsionicPower *power = &session->character.psionic_powers[i];
    
  /* Convert power name to command format */
  char power_cmd[64] = {0};
  const char *src = power->name;
  char *dst = power_cmd;
  while (*src && (dst - power_cmd) < 63) {
    if (*src != ' ' && *src != '-') {
      *dst++ = (char)tolower((unsigned char)*src);
    }
    src++;
  }
  *dst = '\0';
    
  /* Does the typed command match this power? */
  if (strcmp(cmd, power_cmd) == 0) {
    /* PSIONIC POWER MATCHED - now handle manifesting */
        
    /* Check ISP cost */
    if (session->character.psionics.isp_current < power->isp_cost) {
      send_to_player(session, "You need %d I.S.P. to manifest %s (you have %d).\n",
        power->isp_cost, power->name, session->character.psionics.isp_current);
      result.type = VALUE_NULL;
      return result;
    }
        
    /* Deduct ISP */
    session->character.psionics.isp_current -= power->isp_cost;
        
    /* Announce manifesting */
    send_to_player(session, "You manifest %s! (%d I.S.P. spent)\n", 
      power->name, power->isp_cost);
        
    /* Apply psionic effect with args (new function - see section 7) */
    apply_psionic_effect_with_args(session, power, args);
        
    result.type = VALUE_NULL;
    return result;
  }
}

/* If we reach here, no spell/psionic matched - fall through to "Unknown command" */
```

Explanation notes:

- This code goes in `src/driver.c` in the command dispatcher chain and must be placed BEFORE the existing "Unknown command" return.
- Loop order checks spells first, then psionics; both use the same name normalization algorithm shown in Section 3.
- Target parsing: `NULL`/empty `args` implies self-cast; otherwise we attempt to find the named player in the current room.
- Resource checks are performed before deduction; if the caster lacks PPE/ISP we send a message and return without changing resources.
- Broadcasts use `get_introduced_name()` to produce privacy-aware display names when informing others in the room.
- If no match is found, control falls through so the original "Unknown command" behavior is preserved.

## 6. Spell Effect Implementation Updates

The `apply_spell_effect()` function in `src/magic.c` needs updates for new and existing spells. Use the following signature and implementation pattern (examples):

```c
/* Function signature (in src/magic.c) */
void apply_spell_effect(PlayerSession *caster, Spell *spell, PlayerSession *target);

/* Implementation examples for specific spells */

void apply_spell_effect(PlayerSession *caster, Spell *spell, PlayerSession *target) {
  if (!caster || !spell) return;
  if (!target) target = caster; /* Default to self-cast */
    
  /* Spell effects by name - use strcasecmp for case-insensitive */
    
  if (strcasecmp(spell->name, "Tongues") == 0) {
    /* Grant temporary understanding of all languages */
    send_to_player(target, "You suddenly understand all languages!\n");
    if (target != caster) {
      send_to_player(caster, "You grant %s understanding of all languages.\n", 
        target->username);
    }
    /* TODO: Set temporary language flags for spell duration */
  }
    
  else if (strcasecmp(spell->name, "Swim as a Fish") == 0 ||
       strcasecmp(spell->name, "Swim As A Fish") == 0) {
    /* Grant swimming skill at 98% for duration */
    send_to_player(target, "You feel at home in the water!\n");
    set_temporary_skill(target, 2, 98, spell->duration); /* Skill ID 2 = Swimming */
    if (target != caster) {
      send_to_player(caster, "You grant %s the ability to swim.\n", target->username);
    }
  }
    
  else if (strcasecmp(spell->name, "Wind Rush") == 0) {
    /* ROOM-WIDE EFFECT - affects all players in room except caster */
    if (!caster->current_room) return;
        
    Room *room = caster->current_room;
    send_to_player(caster, "You summon a powerful gust of wind!\n");
        
    for (int i = 0; i < room->num_players; i++) {
      PlayerSession *victim = room->players[i];
      if (victim == caster) continue; /* Skip caster */
            
      /* Saving throw: d20 + ME bonus vs DC (10 + caster level) */
      int save_roll = (rand() % 20) + 1;
      save_roll += (victim->character.attributes.me - 10) / 2;
      int dc = 10 + caster->character.level;
            
      if (save_roll >= dc) {
        /* Saved - resisted the wind */
        send_to_player(victim, "You brace yourself against the magical wind!\n");
        send_to_player(caster, "%s resists the wind!\n", victim->username);
      } else {
        /* Failed save - take damage and possible knockback */
        send_to_player(victim, "A powerful gust of wind slams into you!\n");
        send_to_player(caster, "The wind catches %s!\n", victim->username);
                
        /* Deal 2d6 damage */
        int damage = (rand() % 6) + 1 + (rand() % 6) + 1;
                
        /* Apply to MDC if creature has it, otherwise SDC/HP */
        if (victim->character.mdc_current > 0) {
          victim->character.mdc_current -= damage;
          if (victim->character.mdc_current < 0) {
            victim->character.mdc_current = 0;
          }
        } else if (victim->character.sdc_current > 0) {
          victim->character.sdc_current -= damage;
          if (victim->character.sdc_current < 0) {
            victim->character.hp_current += victim->character.sdc_current;
            victim->character.sdc_current = 0;
          }
        } else {
          victim->character.hp_current -= damage;
        }
                
        /* 50% chance to blow into random adjacent room */
        if ((rand() % 100) < 50 && room->num_exits > 0) {
          int exit_idx = rand() % room->num_exits;
          Room *dest_room = room_find_by_id(room->exits[exit_idx].destination_id);
          if (dest_room) {
            send_to_player(victim, "The wind blows you into another room!\n");
            room_remove_player(room, victim);
            victim->current_room = dest_room;
            room_add_player(dest_room, victim);
            cmd_look(victim, "");
          }
        }
      }
    }
  }
    
  else if (strcasecmp(spell->name, "Armor of Ithan") == 0) {
    /* Grant MDC shield: 10 MDC per caster level */
    int bonus_mdc = 10 * caster->character.level;
    target->character.mdc_current += bonus_mdc;
    if (target->character.mdc_current > target->character.mdc_max + bonus_mdc) {
      target->character.mdc_current = target->character.mdc_max + bonus_mdc;
    }
    send_to_player(target, "Armor of Ithan surrounds you! (+%d MDC)\n", bonus_mdc);
    if (target != caster) {
      send_to_player(caster, "You surround %s with Armor of Ithan.\n", target->username);
    }
  }
    
  else if (strcasecmp(spell->name, "Heal Wounds") == 0) {
    /* Heal HP: 2d6 + caster level */
    int heal = (rand() % 6) + 1 + (rand() % 6) + 1 + caster->character.level;
    int old_hp = target->character.hp_current;
    target->character.hp_current += heal;
    if (target->character.hp_current > target->character.hp_max) {
      target->character.hp_current = target->character.hp_max;
    }
    int actual_heal = target->character.hp_current - old_hp;
    send_to_player(target, "Your wounds close! (+%d HP)\n", actual_heal);
    if (target != caster) {
      send_to_player(caster, "You heal %s for %d HP.\n", target->username, actual_heal);
    }
  }
    
  else {
    /* Unknown spell - fallback */
    send_to_player(caster, "The spell fizzles with no effect.\n");
  }
}
```

Notes:

- This function lives in `src/magic.c` and is called from the dispatcher when a spell command matches.
- Signature: takes `caster`, a `Spell *`, and a `PlayerSession *target` (NULL defaults to caster).
- Use `strcasecmp()` for case-insensitive spell-name matches.
- Room-wide spells iterate all players except the caster.
- Saving throws use a d20 roll plus an attribute modifier versus a DC computed from caster level.
- Damage application order: MDC -> SDC -> HP.
- Helper functions referenced: `set_temporary_skill()`, `room_remove_player()`, `room_add_player()`, `cmd_look()`.

## 7. Psionic Effect Implementation with Arguments

Psionics often require complex argument parsing (targets, messages, remote effects). Add a new function `apply_psionic_effect_with_args()` in `src/psionics.c` and declare it in `src/psionics.h`.

```c
/* New function signature (add to src/psionics.h header) */
void apply_psionic_effect_with_args(PlayerSession *psionicist, PsionicPower *power, const char *args);

/* Implementation in src/psionics.c */

void apply_psionic_effect_with_args(PlayerSession *psionicist, PsionicPower *power, const char *args) {
  if (!psionicist || !power) return;
    
  /* Handle psionics that need argument parsing */
    
  if (strcasecmp(power->name, "Telepathy") == 0) {
    /* Requires: <target> <message> */
    if (!args || !args) {
      send_to_player(psionicist, "Usage: telepathy <player> <message>\n");
      return;
    }
        
    /* Parse: first word = target, rest = message */
    char target_name[64] = {0};
    sscanf(args, "%63s", target_name);
        
    const char *message = strchr(args, ' ');
    if (!message || !message) {
      send_to_player(psionicist, "What message do you want to send?\n");
      return;
    }
    message++; /* Skip past the space */
        
    /* Find target player (must be online) */
    PlayerSession *target = NULL;
    for (int i = 0; i < num_sessions; i++) {
      if (sessions[i].state == STATE_PLAYING &&
        strcasecmp(sessions[i].username, target_name) == 0) {
        target = &sessions[i];
        break;
      }
    }
        
    if (!target) {
      send_to_player(psionicist, "You don't know anyone by that name.\n");
      return;
    }
        
    /* Check if introduced (must know them) */
    int introduced = 0;
    for (int i = 0; i < psionicist->character.num_introduced; i++) {
      if (strcasecmp(psionicist->character.introduced_names[i], target->username) == 0) {
        introduced = 1;
        break;
      }
    }
        
    if (!introduced) {
      send_to_player(psionicist, "You haven't been introduced to %s.\n", target_name);
      return;
    }
        
    /* Send telepathic message */
    send_to_player(psionicist, "You project to %s: \"%s\"\n", target->username, message);
    send_to_player(target, "[TELEPATHY from %s]: \"%s\"\n", psionicist->username, message);
  }
    
  else if (strcasecmp(power->name, "Remote Viewing") == 0) {
    /* Requires: <target> */
    if (!args || !args) {
      send_to_player(psionicist, "Usage: remoteview <player>\n");
      return;
    }
        
    /* Find target player */
    PlayerSession *target = NULL;
    for (int i = 0; i < num_sessions; i++) {
      if (sessions[i].state == STATE_PLAYING &&
        strcasecmp(sessions[i].username, args) == 0) {
        target = &sessions[i];
        break;
      }
    }
        
    if (!target || !target->current_room) {
      send_to_player(psionicist, "You can't sense that person.\n");
      return;
    }
        
    /* Check if introduced */
    int introduced = 0;
    for (int i = 0; i < psionicist->character.num_introduced; i++) {
      if (strcasecmp(psionicist->character.introduced_names[i], target->username) == 0) {
        introduced = 1;
        break;
      }
    }
        
    if (!introduced) {
      send_to_player(psionicist, "You haven't been introduced to %s.\n", args);
      return;
    }
        
    /* Show target's room */
    send_to_player(psionicist, "\n[REMOTE VIEWING: %s's location]\n", target->username);
    send_to_player(psionicist, "%s\n%s\n", 
      target->current_room->name,
      target->current_room->description);
        
    /* List players in the room */
    for (int i = 0; i < target->current_room->num_players; i++) {
      PlayerSession *occupant = target->current_room->players[i];
      char display_name[128];
      get_introduced_name(psionicist, occupant, display_name, sizeof(display_name));
      send_to_player(psionicist, "%s is here.\n", display_name);
    }
    send_to_player(psionicist, "[End remote viewing]\n\n");
  }
    
  else {
    /* Simple psionic - call existing effect handler */
    /* This would be the existing psionics_activate_power() logic */
    send_to_player(psionicist, "You activate %s!\n", power->name);
  }
}
```

Notes:

- A new function is required because psionics often need complex argument parsing and privacy checks.
- `Telepathy` parsing: expects `<target> <message>`, finds target, checks `introduced_names`, then sends direct telepathic messages.
- `Remote Viewing` parsing: expects `<target>`, finds target, checks introduced list, then displays the target's room and occupants using `get_introduced_name()`.
- Both rely on the "introduction" privacy mechanic — you can only use these psionics on introduced players.
- For psionics that don't require arguments, fall back to existing activation logic.
- Don't forget to declare the function in `src/psionics.h`.

## 8. Granting Test Spells and Psionics to Admin Characters

To test the refactor, admin characters need test spells and psionics auto-granted on creation. Modify `src/chargen.c` in the `chargen_create_admin()` function.

Add this code AFTER the character initialization but BEFORE the function returns:

```c
/* Grant test spells for refactor testing */
sess->character.num_spells = 5;
sess->character.spells = calloc(5, sizeof(Spell));

/* Spell 1: Tongues (level 6, allows understanding all languages) */
sess->character.spells[0].id = 1;
sess->character.spells[0].name = strdup("Tongues");
sess->character.spells[0].level = 6;
sess->character.spells[0].ppe_cost = 12;
sess->character.spells[0].duration = 100;  /* 100 rounds */
sess->character.spells[0].damage_dice = 0;
sess->character.spells[0].damage_sides = 0;

/* Spell 2: Swim As A Fish (level 2, grants swimming ability) */
sess->character.spells[1].id = 2;
sess->character.spells[1].name = strdup("Swim As A Fish");
sess->character.spells[1].level = 2;
sess->character.spells[1].ppe_cost = 6;
sess->character.spells[1].duration = 50;   /* 50 rounds */
sess->character.spells[1].damage_dice = 0;
sess->character.spells[1].damage_sides = 0;

/* Spell 3: Wind Rush (level 5, room-wide knockback effect) */
sess->character.spells[2].id = 3;
sess->character.spells[2].name = strdup("Wind Rush");
sess->character.spells[2].level = 5;
sess->character.spells[2].ppe_cost = 20;
sess->character.spells[2].duration = 1;    /* Instant effect */
sess->character.spells[2].damage_dice = 2;
sess->character.spells[2].damage_sides = 6; /* 2d6 damage */

/* Spell 4: Armor of Ithan (level 3, grants MDC shield) */
sess->character.spells[3].id = 4;
sess->character.spells[3].name = strdup("Armor of Ithan");
sess->character.spells[3].level = 3;
sess->character.spells[3].ppe_cost = 10;
sess->character.spells[3].duration = 40;   /* 40 rounds */
sess->character.spells[3].damage_dice = 0;
sess->character.spells[3].damage_sides = 0;

/* Spell 5: Heal Wounds (level 5, restores HP) */
sess->character.spells[4].id = 5;
sess->character.spells[4].name = strdup("Heal Wounds");
sess->character.spells[4].level = 5;
sess->character.spells[4].ppe_cost = 10;
sess->character.spells[4].duration = 1;    /* Instant effect */
sess->character.spells[4].damage_dice = 2;
sess->character.spells[4].damage_sides = 6; /* 2d6 + level healing */

/* Grant test psionic powers for refactor testing */
sess->character.num_psionic_powers = 2;
sess->character.psionic_powers = calloc(2, sizeof(PsionicPower));

/* Psionic 1: Telepathy (sensitive, send mental messages) */
sess->character.psionic_powers[0].id = 1;
sess->character.psionic_powers[0].name = strdup("Telepathy");
sess->character.psionic_powers[0].category = 3; /* 3 = Sensitive */
sess->character.psionic_powers[0].isp_cost = 4;
sess->character.psionic_powers[0].duration = 1;    /* Per message */
sess->character.psionic_powers[0].damage_dice = 0;
sess->character.psionic_powers[0].damage_sides = 0;

/* Psionic 2: Remote Viewing (sensitive, view distant location) */
sess->character.psionic_powers[1].id = 2;
sess->character.psionic_powers[1].name = strdup("Remote Viewing");
sess->character.psionic_powers[1].category = 3; /* 3 = Sensitive */
sess->character.psionic_powers[1].isp_cost = 10;
sess->character.psionic_powers[1].duration = 10;   /* 10 rounds */
sess->character.psionic_powers[1].damage_dice = 0;
sess->character.psionic_powers[1].damage_sides = 0;
```

Explanation:

- This grants exactly 5 test spells and 2 test psionics to every admin character.
- Uses `calloc()` to allocate heap memory for the arrays.
- Uses `strdup()` to allocate memory for name strings (important: prevents shared string issues).
- Sets realistic PPE/ISP costs and durations based on spell/power level.
- Damage dice/sides are 0 for utility spells, non-zero for offensive ones.
- Location: inside `chargen_create_admin()` in `src/chargen.c`, after basic character setup.

## 9. Common Pitfalls for GPT-5 Mini

When implementing this refactor, watch out for these common mistakes:

### Pitfall 1: Forgetting `tolower()` in name conversion
**Problem:** Commands typed as "Tongues" won't match "tongues" if you forget case normalization.

**Solution:** Always use `tolower((unsigned char)*src)` when copying characters in the name conversion loop.

### Pitfall 2: Not checking array bounds
**Problem:** Code crashes if `num_spells` or `num_psionic_powers` is 0 or negative.

**Solution:** Always check: `for (int i = 0; i < session->character.num_spells; i++)` — the loop naturally handles 0 count.

### Pitfall 3: Forgetting NULL checks on `session->current_room`
**Problem:** Segmentation fault when trying to broadcast to room if player isn't in a room.

**Solution:** Always check: `if (session->current_room) { /* safe to use room */ }`

### Pitfall 4: Not handling NULL or empty `args`
**Problem:** Crash or undefined behavior when checking `args[0]` if `args` is NULL.

**Solution:** Always check both: `if (!args || !args[0]) { /* handle no arguments */ }`

### Pitfall 5: Wrong return pattern for VMValue
**Problem:** Forgetting to set `result.type = VALUE_NULL;` and return properly causes dispatch chain to break.

**Solution:** Every command handler must end with:
```c
result.type = VALUE_NULL;
return result;
```

### Pitfall 6: Using `strchr()` without checking return value
**Problem:** When parsing "telepathy Cabe Hello", if there's no space, `strchr()` returns NULL and dereferencing it crashes.

**Solution:** Always check:
```c
const char *message = strchr(args, ' ');
if (!message || !message) {
   /* handle error - no message provided */
   return;
}
message++; /* NOW safe to advance */
```

### Pitfall 7: Buffer overflow in room announcements
**Problem:** Using fixed buffers like `char race_name[64]` but not checking size in `get_introduced_name()`.

**Solution:** Always pass buffer size: `get_introduced_name(other, session, race_name, sizeof(race_name));`

### Pitfall 8: Memory leaks with `strdup()`
**Problem:** Test data uses `strdup()` which allocates memory, but not freeing it causes leaks.

**Solution:** This is OK for admin test data (created once), but production code should track and free these strings when character is destroyed.

### Pitfall 9: Inserting dispatcher in wrong location
**Problem:** Putting the dynamic dispatcher AFTER "Unknown command" means it never runs.

**Solution:** Find the line `return vm_value_create_string("Unknown command. Type 'help' for assistance.\r\n");` and insert the entire dispatcher RIGHT BEFORE it.

### Pitfall 10: Not declaring new functions in headers
**Problem:** Compiler errors about undefined function `apply_psionic_effect_with_args()`.

**Solution:** Add declaration to `src/psionics.h`:
```c
void apply_psionic_effect_with_args(PlayerSession *psionicist, PsionicPower *power, const char *args);
```

## 10. Complete Test Cases and Expected Results

After implementing the refactor, test these scenarios as an admin character:

### Test 1: List known spells
**Command:** `spells`

**Expected output:**
```
=== KNOWN SPELLS ===
1. Tongues (Level 6, 12 PPE)
2. Swim As A Fish (Level 2, 6 PPE)
3. Wind Rush (Level 5, 20 PPE)
4. Armor of Ithan (Level 3, 10 PPE)
5. Heal Wounds (Level 5, 10 PPE)
```

### Test 2: Cast spell on self (no target)
**Command:** `tongues`

**Expected output (to caster):**
```
You cast Tongues! (12 P.P.E. spent)
You suddenly understand all languages!
```

**Expected output (to others in room):**
```
A human casts Tongues!
```

### Test 3: Cast spell on target
**Setup:** Have another player "Cabe" in the room

**Command:** `swimasafish Cabe`

**Expected output (to caster):**
```
You cast Swim As A Fish! (6 P.P.E. spent)
You grant Cabe the ability to swim.
```

**Expected output (to Cabe):**
```
A human casts Swim As A Fish!
You feel at home in the water!
```

### Test 4: Room-wide spell
**Setup:** Have 2+ other players in room

**Command:** `windrush`

**Expected output (to caster):**
```
You cast Wind Rush! (20 P.P.E. spent)
You summon a powerful gust of wind!
Cabe resists the wind!
The wind catches Thurtest!
```

**Expected output (to victim who failed save):**
```
A human casts Wind Rush!
A powerful gust of wind slams into you!
The wind blows you into another room!

[Room description of new location]
```

### Test 5: Insufficient resources
**Setup:** Spend PPE until you have less than 12

**Command:** `tongues`

**Expected output:**
```
You need 12 P.P.E. to cast Tongues (you have 8).
```

### Test 6: Target not found
**Command:** `swimasafish NonexistentPlayer`

**Expected output:**
```
You don't see 'NonexistentPlayer' here.
```

### Test 7: Telepathy (multi-word arguments)
**Setup:** Be introduced to player "Thurtest"

**Command:** `telepathy Thurtest Hello from my mind!`

**Expected output (to sender):**
```
You manifest Telepathy! (4 I.S.P. spent)
You project to Thurtest: "Hello from my mind!"
```

**Expected output (to Thurtest):**
```
[TELEPATHY from Thurtea]: "Hello from my mind!"
```

### Test 8: Telepathy with non-introduced player
**Setup:** NOT introduced to player "Stranger"

**Command:** `telepathy Stranger Test message`

**Expected output:**
```
You manifest Telepathy! (4 I.S.P. spent)
You haven't been introduced to Stranger.
```

### Test 9: Remote Viewing
**Setup:** Be introduced to player "Cabe" who is in another room

**Command:** `remoteview Cabe`

**Expected output:**
```
You manifest Remote Viewing! (10 I.S.P. spent)

[REMOTE VIEWING: Cabe's location]
Splynn - Market Center
The heart of Splynn, a dimensional market city ruled by the
Splugorth. Alien beings of every description crowd the streets.
A vampire is here.
A splugorth is here.
[End remote viewing]
```

### Test 10: Unknown command still works
**Command:** `thiscommanddoesnotexist`

**Expected output:**
```
Unknown command. Type 'help' for assistance.
```

---

## Build and Test Instructions

After implementing all sections:

1. **Clean build:**
```bash
./mud.ctl stop
rm -f lib/save/players/*.dat
make clean
make driver
./mud.ctl start
```

2. **Login as admin** (admin gets test spells/psionics auto-granted)

3. **Test basic spell casting:**
  - Type `spells` to verify 5 test spells loaded
  - Type `tongues` to cast on self
  - Type `swimasafish` to cast on self

4. **Test targeting:**
  - Have another character login
  - Type `introduce` to introduce yourself
  - Type `swimasafish <theirname>` to cast on them

5. **Test psionics:**
  - Type `telepathy <name> test message`
  - Type `remoteview <name>`

6. **Test error cases:**
  - Try casting with insufficient PPE
  - Try targeting non-existent player
  - Try telepathy on non-introduced player
  - Type garbage command to verify "Unknown command" still works


