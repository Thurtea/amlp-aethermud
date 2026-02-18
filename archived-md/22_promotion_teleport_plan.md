**Promotion Teleport Plan**

Generated: 2026-02-16

Objective: when a player is promoted to `Wizard` or `Admin`, teleport them to the Staff Castle entrance (`/domains/staff_castle/room/courtyard`) and present a welcome message describing new abilities and workroom/home usage.

1) Current `promote` command source

File: `lib/cmds/admin/promote.lpc`

```c
// /lib/cmds/admin/promote.lpc
// Promote command - Grant wizard/admin privileges to a player
//
// Usage: promote <player> <level>
// Levels: 0 = Player, 1 = Wizard, 2 = Admin
//
// Admins can promote to any level
// Wizards can only promote to Wizard (level 1)

#include <globals.h>

int main(string arg) {
    object user, target;
    string target_name, level_str;
    int new_level, user_level;
    
    user = previous_object();
    user_level = user->query_privilege_level();
    
    // Check if user has permission
    if (user_level < PRIV_WIZARD) {
        tell_object(user, "You must be at least a Wizard to use this command.\n");
        return 1;
    }
    
    // Parse arguments
    if (!arg || arg == "") {
        tell_object(user, "Usage: promote <player> <level>\n");
        tell_object(user, "Levels: 0 = Player, 1 = Wizard, 2 = Admin\n");
        return 1;
    }
    
    if (sscanf(arg, "%s %s", target_name, level_str) != 2) {
        tell_object(user, "Usage: promote <player> <level>\n");
        tell_object(user, "Levels: 0 = Player, 1 = Wizard, 2 = Admin\n");
        return 1;
    }
    
    // Validate level
    new_level = to_int(level_str);
    if (new_level < 0 || new_level > 2) {
        tell_object(user, "Invalid level. Use 0 (Player), 1 (Wizard), or 2 (Admin).\n");
        return 1;
    }
    
    // Wizards can only promote to Wizard level
    if (user_level == PRIV_WIZARD && new_level != PRIV_WIZARD) {
        tell_object(user, "Wizards can only promote players to Wizard level.\n");
        tell_object(user, "You need Admin privileges to set other levels.\n");
        return 1;
    }
    
    // Find target player (must be online)
    target_name = lower_case(target_name);
    target = find_player(target_name);
    
    if (!target) {
        tell_object(user, "Player not found: " + target_name + "\n");
        tell_object(user, "Note: Player must be online to promote.\n");
        return 1;
    }
    
    // Get current level for feedback
    int old_level = target->query_privilege_level();
    
    // Set new privilege level
    target->set_privilege_level(new_level);
    
    // Save the change
    if (function_exists("save_player", target)) {
        target->save_player();
    }
    
    // Convert level numbers to names for display
    string level_names = ({ "Player", "Wizard", "Admin" });
    string new_title = level_names[new_level];
    string old_title = level_names[old_level];
    
    // Notify the user who performed the action
    if (old_level == new_level) {
        tell_object(user, target_name + " is already " + new_title + ".\n");
    } else if (new_level > old_level) {
        tell_object(user, "Promoted " + target_name + " from " + old_title + 
                    " to " + new_title + ".\n");
    } else {
        tell_object(user, "Demoted " + target_name + " from " + old_title + 
                    " to " + new_title + ".\n");
    }
    
    // Notify the target player
    if (old_level != new_level) {
        tell_object(target, "\n*** Your privilege level has been changed! ***\n");
        tell_object(target, "Old level: " + old_title + "\n");
        tell_object(target, "New level: " + new_title + "\n");
        
        if (new_level >= PRIV_WIZARD) {
            tell_object(target, "\nType 'wiz help' for wizard commands.\n");
        }
        tell_object(target, "\n");
    }
    
    return 1;
}

string query_help() {
    return 
"PROMOTE - Grant wizard or admin privileges to a player\n\n"
"Usage:\n"
"  promote <player> <level>\n\n"
"Levels:\n"
"  0 = Player (normal user)\n"
"  1 = Wizard (builder access, basic admin tools)\n"
"  2 = Admin (full system access)\n\n"
"Restrictions:\n"
"  - Wizards can only promote players to Wizard level (1)\n"
"  - Admins can promote to any level\n"
"  - Target player must be online\n\n"
"Examples:\n"
"  promote thurtest 1          Grant Wizard privileges\n"
"  promote jane 2              Grant Admin privileges (Admin only)\n\n"
"See also: demote, who\n";
}
```

2) Does `promote` already teleport on promotion?

- No. Current implementation sets `target->set_privilege_level(new_level)` and saves, then notifies the target. There is no teleport/move call or message about being sent to the Staff Castle.

3) Where to add teleport logic

- Insert point: inside `main()` after the block that notifies the `target` of the level change, within the `if (old_level != new_level)` conditional and gated to promotions to wizard/admin (i.e. when `new_level >= PRIV_WIZARD` and `new_level > old_level`).

- Recommended insertion (pseudocode):

```
// after notifying the target about level change
if (old_level != new_level && new_level >= PRIV_WIZARD && new_level > old_level) {
    // Teleport target to staff castle courtyard
    string castle_entrance = "/domains/staff_castle/room/courtyard";
    if (function_exists("move", target)) {
        target->move(castle_entrance);
    } else {
        move_object(target, castle_entrance);
    }

    // Send welcome + orientation messages
    tell_object(target, "\nWelcome to the Staff Castle!\n");
    tell_object(target, "You have been granted " + new_title + " privileges.\n");
    tell_object(target, "A staff member will show you the workroom; use 'home' to return.\n");
    tell_room(castle_entrance, target->query_cap_name() + " arrives in a swirl of light.\n", ({ target }));
}
```

4) Staff castle entrance room path

- Use: `/domains/staff_castle/room/courtyard`

5) Proposed welcome message text

- Short welcome (immediate):

"\nWelcome to the Staff Castle, %s!\nYou have been promoted to %s.\n"

- Extended orientation (sent after teleport):

"Welcome to the Staff Castle — the administrative hub. A few quick notes:\n"
- "- `wiz help` shows common wizard/admin commands."\n
- "- Your personal workroom will be created or assigned shortly. Use `home` to return to it."\n
- "- Be mindful: admin powers affect live players and systems. Use them responsibly. Read `/doc/admin/guide` for policies and tools."\n
- "If you need a walkthrough, contact a senior admin or run `staff tour` (if available)."

Example combined message (sent via `tell_object(target, ...)`):

```
\nWelcome to the Staff Castle, %s! You are now a %s.

This is the administrative hub. A personal workroom will be created for you shortly — use `home` to return to it. Type `wiz help` to see your new commands. Use your powers responsibly.
\n```

6) Additional considerations

- Permissions: ensure `promote` only teleports when `new_level > old_level` to avoid teleporting when demoting or re-saving the same level.
- Workroom creation: consider whether promoting should also create/assign a workroom. If so, the promotion logic should call the existing workroom allocation routine (e.g., `assign_workroom(target)`) before teleporting. If such helper does not exist, do not create it here — coordinate with area/workroom code.
- Logging: add an entry to admin logs when teleporting promoted players for auditability.

7) Next steps (implementation sequence)

1. Add teleport + welcome message snippet into `lib/cmds/admin/promote.lpc` at the insertion point described above.
2. Optionally, hook into workroom-allocation logic if available; otherwise, send guidance to the promoted player about requesting a workroom.
3. Add audit log line (e.g., `log_file("promotions", ...)`).
4. Test in server: promote a test player to wizard/admin and verify teleport, messages, and that `home`/workroom flow is correct.

If you'd like, I can implement the minimal teleport + welcome message patch now and run smoke tests. Say "Apply minimal patch" to proceed.
