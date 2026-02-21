/*
 * wiz_tools.c - Implementation of wizard customization tools
 * 
 * Three core wizard tools:
 * 1. Staff of Demotion - Character demotion and reset
 * 2. RP-Wiz Skill Tool - O.C.C. and skill assignment
 * 3. Tattoo-Gun - Apply beneficial magical tattoos
 */

#include "wiz_tools.h"
#include "chargen.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "npc.h"
#include "session_internal.h"
#include "vm.h"
#include "efun.h"
#include "driver.h"
#include "object.h"
#include "item.h"
#include "skills.h"
#include <time.h>

/* Forward declarations for driver helpers used here (defined in driver.c) */
extern void handle_player_death(PlayerSession *sess, PlayerSession *killer,
                                const char *npc_killer_name);
extern PlayerSession* find_player_by_name(const char *name);
extern void room_add_player(Room *room, PlayerSession *player);
extern void room_remove_player(Room *room, PlayerSession *player);
extern Room* room_get_by_path(const char *lpc_path);
extern Room* room_get_by_id(int id);
extern void room_broadcast(Room *room, const char *message, PlayerSession *exclude);
extern void cmd_look(PlayerSession *sess, const char *args);
extern int save_character(PlayerSession *sess);
extern void broadcast_message(const char *message, PlayerSession *exclude);
extern void send_to_player(PlayerSession *sess, const char *fmt, ...);
extern VMValue execute_command(PlayerSession *session, const char *command);
extern PlayerSession *sessions[];
extern VirtualMachine *global_vm;

/* Forward declarations for helpers implemented later in this file */
int assign_primary_skills(Character *player, const char *occ_name);

/* Simple wizard action logger */
static void wiz_log(const char *fmt, ...) {
    FILE *f = fopen("lib/log/wizard.log", "a");
    if (!f) return;
    time_t now = time(NULL);
    char tbuf[32];
    struct tm *tm = localtime(&now);
    strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", tm);
    fprintf(f, "[%s] ", tbuf);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
    fprintf(f, "\n");
    fclose(f);
}

/* ------------------------------------------------------------------ */
/* Wizard/admin helper functions (wrap common driver admin actions) */

/* Teleport the wizard themselves to a room (by LPC path or numeric id) */
int wiz_goto(PlayerSession *sess, const char *room_arg) {
    /* Level 3 required for movement/visibility wizard actions */
    if (!sess || sess->privilege_level < 3 || !room_arg) return 0;
    Room *target = NULL;
    if (room_arg[0] == '/') {
        target = room_get_by_path(room_arg);
        if (!target) return 0;
    } else {
        int id = atoi(room_arg);
        target = room_get_by_id(id);
        if (!target) return 0;
    }

    if (sess->current_room) {
        room_remove_player(sess->current_room, sess);
        char leave_msg[256];
        snprintf(leave_msg, sizeof(leave_msg), "%s vanishes in a puff of smoke.\r\n", sess->username);
        room_broadcast(sess->current_room, leave_msg, NULL);
    }

    sess->current_room = target;
    room_add_player(target, sess);

    char arrive_msg[256];
    snprintf(arrive_msg, sizeof(arrive_msg), "%s appears in a puff of smoke.\r\n", sess->username);
    room_broadcast(target, arrive_msg, sess);

    cmd_look(sess, "");
    wiz_log("%s used goto -> %s", sess->username ? sess->username : "<unknown>", room_arg);
    return 1;
}

/* Summon another player into the wizard's current room */
int wiz_summon(PlayerSession *sess, const char *player_name) {
    /* Level 3 required for summon */
    if (!sess || sess->privilege_level < 3 || !player_name) return 0;
    if (!sess->current_room) return 0;
    PlayerSession *target = find_player_by_name(player_name);
    if (!target || target == sess) return 0;

    if (target->current_room) {
        char leave_msg[256];
        snprintf(leave_msg, sizeof(leave_msg), "%s vanishes in a flash of light.\r\n", target->username);
        room_broadcast(target->current_room, leave_msg, target);
        room_remove_player(target->current_room, target);
    }

    target->current_room = sess->current_room;
    room_add_player(sess->current_room, target);

    char arrive_msg[256];
    snprintf(arrive_msg, sizeof(arrive_msg), "%s appears in a flash of light.\r\n", target->username);
    room_broadcast(sess->current_room, arrive_msg, target);

    send_to_player(target, "You have been summoned by %s!\r\n", sess->username);
    cmd_look(target, "");
    wiz_log("%s summoned %s to room id=%d", sess->username ? sess->username : "<unknown>", target->username, sess->current_room ? sess->current_room->id : -1);
    return 1;
}

/* Teleport a player to a specified room (by path or id) */
int wiz_teleport(PlayerSession *sess, const char *player_name, const char *room_arg) {
    /* Level 4 required for player manipulation (teleport others) */
    if (!sess || sess->privilege_level < 4 || !player_name || !room_arg) return 0;
    PlayerSession *target = find_player_by_name(player_name);
    if (!target) return 0;

    Room *dest = NULL;
    if (room_arg[0] == '/') {
        dest = room_get_by_path(room_arg);
        if (!dest) return 0;
    } else {
        int id = atoi(room_arg);
        dest = room_get_by_id(id);
        if (!dest) return 0;
    }

    if (target->current_room) {
        char leave_msg[256];
        snprintf(leave_msg, sizeof(leave_msg), "%s vanishes in a flash of light.\r\n", target->username);
        room_broadcast(target->current_room, leave_msg, target);
        room_remove_player(target->current_room, target);
    }

    target->current_room = dest;
    room_add_player(dest, target);

    char arrive_msg[256];
    snprintf(arrive_msg, sizeof(arrive_msg), "%s appears in a flash of light.\r\n", target->username);
    room_broadcast(dest, arrive_msg, target);
    send_to_player(target, "You have been teleported by %s!\r\n", sess->username);
    cmd_look(target, "");
    wiz_log("%s teleported %s -> %s", sess->username ? sess->username : "<unknown>", target->username, room_arg);
    return 1;
}

/* Force a player to execute a command (admin-only) */
int wiz_force(PlayerSession *sess, const char *target_name, const char *command) {
    /* Level 4 required for forcing commands */
    if (!sess || sess->privilege_level < 4 || !target_name || !command) return 0;
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) return 0;
    if (target == sess) return 0;

    send_to_player(target, "%s forces you to: %s\r\n", sess->username, command);
    /* Execute command through existing driver path */
    VMValue res = execute_command(target, command);
    /* Release VM return value if any */
    if (res.type != VALUE_NULL) vm_value_release(&res);
    wiz_log("%s forced %s to: %s", sess->username ? sess->username : "<unknown>", target->username, command);
    return 1;
}

/* Initiate graceful server shutdown (admin-only). If delay_seconds > 0, announce it. */
int wiz_shutdown(PlayerSession *sess, int delay_seconds) {
    /* Level 5 required for destructive/dangerous ops */
    if (!sess || sess->privilege_level < 5) return 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i] && sessions[i]->state == STATE_PLAYING) {
            save_character(sessions[i]);
        }
    }

    char msg[256];
    if (delay_seconds > 0) {
        snprintf(msg, sizeof(msg), "[SYSTEM] Admin %s is shutting down the server in %d seconds. All characters saved.\r\n", sess->username, delay_seconds);
    } else {
        snprintf(msg, sizeof(msg), "[SYSTEM] Admin %s is shutting down the server NOW. All characters saved.\r\n", sess->username);
    }
    broadcast_message(msg, NULL);

    fprintf(stderr, "[Server] Shutdown initiated by %s\n", sess->username);
    server_running = 0;
    wiz_log("%s initiated shutdown (delay=%d)", sess->username ? sess->username : "<unknown>", delay_seconds);
    return 1;
}

/* Reload an LPC object or daemon via efun load_object */
int wiz_reload(PlayerSession *sess, const char *lpc_path) {
    /* Level 2: read-only / testing reloads */
    if (!sess || sess->privilege_level < 2 || !lpc_path) return 0;
    VMValue path_val = vm_value_create_string(lpc_path);
    VMValue res = efun_load_object(global_vm, &path_val, 1);
    vm_value_release(&path_val);
    /* If result is an object, consider successful; basic check: not null */
    if (res.type != VALUE_NULL) {
        vm_value_release(&res);
        wiz_log("%s reloaded %s", sess->username ? sess->username : "<unknown>", lpc_path);
        return 1;
    }
    return 0;
}

/* ---------------- Batch 2: additional wizard helpers ---------------- */

/* Start/stop snooping on a player (monitor their output) */
int wiz_snoop(PlayerSession *sess, const char *target_name, int enable) {
    if (!sess || sess->privilege_level < 3 || !target_name) return 0;
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) return 0;

    if (enable) {
        if (sess->snooping) {
            send_to_player(sess, "You are already snooping %s.\n", sess->snooping->username);
            return 0;
        }
        sess->snooping = target;
        target->snooped_by = sess;
        send_to_player(sess, "You are now snooping %s.\n", target->username);
        wiz_log("%s started snooping %s", sess->username ? sess->username : "<unknown>", target->username);
    } else {
        if (sess->snooping != target) {
            send_to_player(sess, "You are not snooping %s.\n", target->username);
            return 0;
        }
        sess->snooping = NULL;
        target->snooped_by = NULL;
        send_to_player(sess, "Stopped snooping %s.\n", target->username);
        wiz_log("%s stopped snooping %s", sess->username ? sess->username : "<unknown>", target->username);
    }
    return 1;
}

/* Toggle wizard invisibility */
int wiz_invisible(PlayerSession *sess, int enable) {
    if (!sess || sess->privilege_level < 3) return 0;
    sess->is_invisible = enable ? 1 : 0;
    send_to_player(sess, "You are now %svisible.\n", sess->is_invisible ? "" : "not ");
    wiz_log("%s set invisible=%d", sess->username ? sess->username : "<unknown>", sess->is_invisible);
    return 1;
}

/* Set a numeric stat on a target player or their Character struct */
int wiz_set_stat(PlayerSession *sess, const char *target_name, const char *stat, int value) {
    if (!sess || sess->privilege_level < 4 || !target_name || !stat) return 0;
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) return 0;
    Character *ch = &target->character;

    if (strcasecmp(stat, "hp") == 0) {
        ch->hp = value;
        if (ch->hp > ch->max_hp) ch->hp = ch->max_hp;
    } else if (strcasecmp(stat, "max_hp") == 0 || strcasecmp(stat, "maxhp") == 0) {
        ch->max_hp = value;
        if (ch->hp > ch->max_hp) ch->hp = ch->max_hp;
    } else if (strcasecmp(stat, "sdc") == 0) {
        ch->sdc = value;
        if (ch->sdc > ch->max_sdc) ch->sdc = ch->max_sdc;
    } else if (strcasecmp(stat, "max_sdc") == 0) {
        ch->max_sdc = value;
        if (ch->sdc > ch->max_sdc) ch->sdc = ch->max_sdc;
    } else if (strcasecmp(stat, "ppe") == 0) {
        ch->ppe = value;
        if (ch->ppe > ch->max_ppe) ch->ppe = ch->max_ppe;
    } else if (strcasecmp(stat, "max_ppe") == 0) {
        ch->max_ppe = value;
        if (ch->ppe > ch->max_ppe) ch->ppe = ch->max_ppe;
    } else if (strcasecmp(stat, "isp") == 0) {
        ch->isp = value;
        if (ch->isp > ch->max_isp) ch->isp = ch->max_isp;
    } else if (strcasecmp(stat, "max_isp") == 0) {
        ch->max_isp = value;
        if (ch->isp > ch->max_isp) ch->isp = ch->max_isp;
    } else if (strcasecmp(stat, "xp") == 0) {
        ch->xp = value;
    } else if (strcasecmp(stat, "level") == 0) {
        ch->level = value;
    } else if (strcasecmp(stat, "credits") == 0) {
        ch->credits = value;
    } else if (strcasecmp(stat, "iq") == 0) {
        ch->stats.iq = value;
    } else if (strcasecmp(stat, "me") == 0) {
        ch->stats.me = value;
    } else if (strcasecmp(stat, "ma") == 0) {
        ch->stats.ma = value;
    } else if (strcasecmp(stat, "ps") == 0) {
        ch->stats.ps = value;
    } else if (strcasecmp(stat, "pp") == 0) {
        ch->stats.pp = value;
    } else if (strcasecmp(stat, "pe") == 0) {
        ch->stats.pe = value;
    } else if (strcasecmp(stat, "pb") == 0) {
        ch->stats.pb = value;
    } else if (strcasecmp(stat, "spd") == 0) {
        ch->stats.spd = value;
    } else {
        send_to_player(sess, "Unknown stat '%s'.\n", stat);
        return 0;
    }

    send_to_player(sess, "Set %s's %s = %d\n", target->username, stat, value);
    send_to_player(target, "Your %s was set to %d by %s\n", stat, value, sess->username);
    wiz_log("%s set %s.%s = %d", sess->username ? sess->username : "<unknown>", target->username, stat, value);
    return 1;
}

/* Grant XP to a player */
int wiz_grant_xp(PlayerSession *sess, const char *target_name, int xp_amount) {
    if (!sess || sess->privilege_level < 4 || !target_name) return 0;
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) return 0;
    Character *ch = &target->character;
    ch->xp += xp_amount;
    send_to_player(sess, "Granted %d XP to %s (total XP=%d)\n", xp_amount, target->username, ch->xp);
    send_to_player(target, "You were awarded %d XP by %s\n", xp_amount, sess->username);
    wiz_log("%s granted %d XP to %s (total %d)", sess->username ? sess->username : "<unknown>", xp_amount, target->username, ch->xp);
    return 1;
}

/* Heal a player fully */
int wiz_heal(PlayerSession *sess, const char *target_name) {
    if (!sess || sess->privilege_level < 4 || !target_name) return 0;
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) return 0;
    Character *ch = &target->character;
    ch->hp = ch->max_hp;
    ch->sdc = ch->max_sdc;
    ch->ppe = ch->max_ppe;
    ch->isp = ch->max_isp;
    ch->mdc = ch->max_mdc;
    send_to_player(target, "You feel fully restored by %s's magic.\n", sess->username);
    send_to_player(sess, "Healed %s to full health.\n", target->username);
    wiz_log("%s healed %s (hp=%d sdc=%d ppe=%d isp=%d)", sess->username ? sess->username : "<unknown>", target->username, ch->hp, ch->sdc, ch->ppe, ch->isp);
    return 1;
}

/* Clone an LPC object and give to a target player or leave in room */
int wiz_clone(PlayerSession *sess, const char *lpc_path, const char *target_name) {
    if (!sess || sess->privilege_level < 4 || !lpc_path) return 0;

    /* Prefer creating a C Item from the LPC source file when possible so
     * the driver-side inventory/equipment/examine system can interact
     * with the item. Fall back to VM-level clone if the source file
     * cannot be located or parsed. */
    char fs_path[512];
    if (resolve_lpc_path(lpc_path, fs_path, sizeof(fs_path))) {
        Item *new_item = item_create_from_lpc(fs_path);
        if (!new_item) {
            send_to_player(sess, "Failed to parse LPC object: %s\n", fs_path);
            return 0;
        }

        /* If a target player is given, add to their inventory */
        if (target_name && target_name[0]) {
            PlayerSession *target = find_player_by_name(target_name);
            if (!target) {
                item_free(new_item);
                send_to_player(sess, "Player '%s' not found.\n", target_name);
                return 0;
            }
            /* Wiz/admin bypass weight check when giving items to players */
            bool target_added = (sess->privilege_level >= 1)
                ? inventory_add_force(&target->character.inventory, new_item)
                : inventory_add(&target->character.inventory, new_item);
            if (!target_added) {
                item_free(new_item);
                send_to_player(sess, "Could not add item to %s's inventory (weight limit?).\n", target->username);
                return 0;
            }
            send_to_player(target, "An object '%s' has been created for you by %s.\n", new_item->name, sess->username);
            send_to_player(sess, "Created %s and moved to %s.\n", new_item->name, target->username);
            wiz_log("%s cloned %s -> %s", sess->username ? sess->username : "<unknown>", fs_path, target->username);
            return 1;
        }

        /* No target: add to wizard's own inventory (always bypass weight check) */
        if (!inventory_add_force(&sess->character.inventory, new_item)) {
            item_free(new_item);
            send_to_player(sess, "Could not add item to your inventory (weight limit?).\n");
            return 0;
        }
        send_to_player(sess, "Created %s and added to your inventory.\n", new_item->name);
        wiz_log("%s cloned %s -> self", sess->username ? sess->username : "<unknown>", fs_path);
        return 1;
    }

    /* Fallback: do a VM-level clone if file couldn't be resolved */
    VMValue path_val = vm_value_create_string(lpc_path);
    VMValue res = efun_clone_object(global_vm, &path_val, 1);
    vm_value_release(&path_val);
    if (res.type != VALUE_OBJECT || !res.data.object_value) {
        if (res.type != VALUE_NULL) vm_value_release(&res);
        send_to_player(sess, "Failed to clone object: %s\n", lpc_path);
        return 0;
    }

    void *cloned_obj = res.data.object_value;

    /* If a target player is provided, try to move object into their inventory */
    if (target_name && target_name[0]) {
        PlayerSession *target = find_player_by_name(target_name);
        if (!target) {
            vm_value_release(&res);
            send_to_player(sess, "Player '%s' not found.\n", target_name);
            return 0;
        }

        if (target->player_object) {
            VMValue arg;
            arg.type = VALUE_OBJECT;
            arg.data.object_value = target->player_object;
            /* Call move_to on the cloned object to move into player */
            obj_call_method(global_vm, (obj_t *)cloned_obj, "move_to", &arg, 1);
            send_to_player(target, "An object %s has been cloned for you by %s.\n", lpc_path, sess->username);
            send_to_player(sess, "Cloned %s and moved to %s.\n", lpc_path, target->username);
            wiz_log("%s cloned %s -> %s", sess->username ? sess->username : "<unknown>", lpc_path, target->username);
        } else {
            vm_value_release(&res);
            send_to_player(sess, "Target player has no LPC object to receive the cloned object.\n");
            return 0;
        }
    } else {
        /* No target: attempt to move into wizard's room by calling move_to with their player_object if present */
        if (sess->player_object) {
            VMValue arg;
            arg.type = VALUE_OBJECT;
            arg.data.object_value = sess->player_object;
            obj_call_method(global_vm, (obj_t *)cloned_obj, "move_to", &arg, 1);
            send_to_player(sess, "Cloned %s and moved into your inventory/room.\n", lpc_path);
            wiz_log("%s cloned %s -> self", sess->username ? sess->username : "<unknown>", lpc_path);
        } else {
            vm_value_release(&res);
            send_to_player(sess, "No player object to receive the cloned item.\n");
            return 0;
        }
    }

    /* Release the cloned object VMValue reference */
    vm_value_release(&res);
    return 1;
}


/* ------------------------------------------------------------------ */

/* Destroy an LPC object by path or object name. Admin-only (level 5). */
int wiz_destruct(PlayerSession *sess, const char *target) {
    if (!sess || sess->privilege_level < 5 || !target) return 0;

    /* If looks like a path, try to find/load object */
    VMValue path_val = vm_value_create_string(target);
    VMValue found = efun_find_object(global_vm, &path_val, 1);
    vm_value_release(&path_val);

    if (found.type == VALUE_OBJECT && found.data.object_value) {
        obj_t *o = (obj_t *)found.data.object_value;
        obj_destroy(o);
        vm_value_release(&found);
        send_to_player(sess, "Destructed object: %s\n", target);
        wiz_log("%s destructed %s", sess->username ? sess->username : "<unknown>", target);
        return 1;
    }

    if (found.type != VALUE_NULL) vm_value_release(&found);
    send_to_player(sess, "Object not found: %s\n", target);
    return 0;
}

/* Promote or set a player's privilege level. Admin-only (level 5). */
int wiz_promote(PlayerSession *sess, const char *target_name, int new_level) {
    if (!sess || sess->privilege_level < 5 || !target_name) return 0;
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) {
        send_to_player(sess, "Player not found: %s\n", target_name);
        return 0;
    }
    if (target == sess) {
        send_to_player(sess, "You cannot change your own level.\n");
        return 0;
    }
    int old = target->privilege_level;
    target->privilege_level = new_level;
    save_character(target);
    send_to_player(sess, "%s -> %s set to level %d\n", target->username, target->username, new_level);
    send_to_player(target, "Your privilege level was changed by %s to %d\n", sess->username, new_level);
    wiz_log("%s changed %s from %d -> %d", sess->username ? sess->username : "<unknown>", target->username, old, new_level);
    return 1;
}

/* Wrapper command for promotion actions (C-level command wrapper) */
int cmd_promotion(PlayerSession *sess, const char *player_name, int new_level) {
    if (!sess || !player_name) return 0;
    return wiz_promote(sess, player_name, new_level);
}

/* Simple ban/unban implementation: account name or IP string. Admin-only (level 5). */
static int write_line_to_file(const char *path, const char *line) {
    FILE *f = fopen(path, "a");
    if (!f) return 0;
    fprintf(f, "%s\n", line);
    fclose(f);
    return 1;
}

static int remove_line_from_file(const char *path, const char *needle) {
    char tmp_path[512];
    snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", path);
    FILE *in = fopen(path, "r");
    FILE *out = fopen(tmp_path, "w");
    int found = 0;
    if (!in || !out) {
        if (in) fclose(in);
        if (out) fclose(out);
        return 0;
    }
    char buf[512];
    while (fgets(buf, sizeof(buf), in)) {
        /* strip newline */
        char *nl = strchr(buf, '\n'); if (nl) *nl = '\0';
        if (strcmp(buf, needle) == 0) { found = 1; continue; }
        fprintf(out, "%s\n", buf);
    }
    fclose(in);
    fclose(out);
    if (found) {
        remove(path);
        rename(tmp_path, path);
    } else {
        remove(tmp_path);
    }
    return found;
}

int wiz_ban(PlayerSession *sess, const char *target) {
    if (!sess || sess->privilege_level < 5 || !target) return 0;
    /* decide if IP (contains dot) or username */
    if (strchr(target, '.') != NULL) {
        /* treat as IP */
        if (!write_line_to_file("data/banned_ips.txt", target)) {
            send_to_player(sess, "Failed to write ban list.\n");
            return 0;
        }
        send_to_player(sess, "Banned IP: %s\n", target);
        wiz_log("%s banned IP %s", sess->username ? sess->username : "<unknown>", target);
        return 1;
    } else {
        if (!write_line_to_file("data/banned_accounts.txt", target)) {
            send_to_player(sess, "Failed to write ban list.\n");
            return 0;
        }
        send_to_player(sess, "Banned account: %s\n", target);
        wiz_log("%s banned account %s", sess->username ? sess->username : "<unknown>", target);
        return 1;
    }
}

int wiz_unban(PlayerSession *sess, const char *target) {
    if (!sess || sess->privilege_level < 5 || !target) return 0;
    if (strchr(target, '.') != NULL) {
        if (!remove_line_from_file("data/banned_ips.txt", target)) {
            send_to_player(sess, "IP not found in ban list: %s\n", target);
            return 0;
        }
        send_to_player(sess, "Unbanned IP: %s\n", target);
        wiz_log("%s unbanned IP %s", sess->username ? sess->username : "<unknown>", target);
        return 1;
    } else {
        if (!remove_line_from_file("data/banned_accounts.txt", target)) {
            send_to_player(sess, "Account not found in ban list: %s\n", target);
            return 0;
        }
        send_to_player(sess, "Unbanned account: %s\n", target);
        wiz_log("%s unbanned account %s", sess->username ? sess->username : "<unknown>", target);
        return 1;
    }
}


/* ============================================================================
 * O.C.C. SKILL CONFIGURATIONS (from Palladium Rifts)
 * ============================================================================ */

/* SOLDIER - Military Combat Specialist */
static OCCSkillConfig soldier_config = {
    .occ_name = "Soldier",
    .primary_count = 8,
    .primary_skills = {
        {"Hand to Hand: Basic", 40, 3, 1, 1},
        {"Sword", 60, 3, 1, 1},
        {"Rifle", 50, 3, 1, 1},
        {"Climbing", 30, 2, 1, 1},
        {"Swimming", 40, 2, 1, 1},
        {"Land Navigation", 35, 2, 1, 1},
        {"Weapons Systems", 35, 3, 1, 1},
        {"Military Etiquette", 50, 1, 1, 1},
    },
    .occ_related_max = 8,
    .secondary_max = 4,
};

/* MIND MELTER - Psychic Master */
static OCCSkillConfig mind_melter_config = {
    .occ_name = "Mind Melter",
    .primary_count = 9,
    .primary_skills = {
        {"Concentration", 50, 2, 1, 1},
        {"Meditation", 55, 2, 1, 1},
        {"Telepathy Basics", 40, 3, 1, 1},
        {"Track/Sense Psionic", 35, 3, 1, 1},
        {"Survive: Wilderness", 35, 2, 1, 1},
        {"Land Navigation", 40, 2, 1, 1},
        {"Lore: Creatures", 30, 2, 1, 1},
        {"Escape Artist", 40, 3, 1, 1},
        {"Lore: Demons & Monsters", 25, 2, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* LEY LINE WALKER - Mage */
static OCCSkillConfig ley_line_walker_config = {
    .occ_name = "Ley Line Walker",
    .primary_count = 10,
    .primary_skills = {
        {"Spell Knowledge", 50, 3, 1, 1},
        {"Meditation", 50, 2, 1, 1},
        {"Lore: Magic", 45, 2, 1, 1},
        {"Lore: Creatures", 35, 3, 1, 1},
        {"Language: Human", 65, 0, 1, 1},
        {"Language: Demongogian", 35, 2, 1, 1},
        {"Climb", 30, 2, 1, 1},
        {"Swim", 35, 2, 1, 1},
        {"Lore: Demons", 40, 3, 1, 1},
        {"Sense Ley Lines", 45, 3, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* ROGUE - Thief/Assassin */
static OCCSkillConfig rogue_config = {
    .occ_name = "Rogue",
    .primary_count = 9,
    .primary_skills = {
        {"Hand to Hand: Basic", 35, 3, 1, 1},
        {"Knife", 50, 3, 1, 1},
        {"Sword", 40, 3, 1, 1},
        {"Lockpicking", 45, 4, 1, 1},
        {"Detect Traps", 40, 3, 1, 1},
        {"Disarm Traps", 45, 3, 1, 1},
        {"Pickpocketing", 40, 4, 1, 1},
        {"Backstab", 50, 2, 1, 1},
        {"Evasion", 45, 3, 1, 1},
    },
    .occ_related_max = 7,
    .secondary_max = 5,
};

/* WILDERNESS SCOUT - Ranger */
static OCCSkillConfig wilderness_scout_config = {
    .occ_name = "Wilderness Scout",
    .primary_count = 10,
    .primary_skills = {
        {"Rifle", 55, 3, 1, 1},
        {"Archery", 50, 3, 1, 1},
        {"Climbing", 40, 3, 1, 1},
        {"Swimming", 50, 2, 1, 1},
        {"Tracking", 50, 4, 1, 1},
        {"Land Navigation", 50, 2, 1, 1},
        {"Hunting", 55, 3, 1, 1},
        {"Fishing", 50, 2, 1, 1},
        {"Botany", 35, 2, 1, 1},
        {"Wilderness Survival", 55, 2, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* SCHOLAR - Academic/Researcher */
static OCCSkillConfig scholar_config = {
    .occ_name = "Scholar",
    .primary_count = 10,
    .primary_skills = {
        {"Language: Human", 60, 1, 1, 1},
        {"Language: Old Kingdom", 40, 1, 1, 1},
        {"Lore: History", 55, 3, 1, 1},
        {"Lore: Legends and Myths", 45, 3, 1, 1},
        {"Lore: Creatures", 40, 2, 1, 1},
        {"Lore: Magic", 40, 2, 1, 1},
        {"Research", 60, 3, 1, 1},
        {"Memorization", 50, 2, 1, 1},
        {"Appraisal", 35, 2, 1, 1},
        {"Literacy", 70, 0, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* MERCHANT - Trader/Negotiator */
static OCCSkillConfig merchant_config = {
    .occ_name = "Merchant",
    .primary_count = 9,
    .primary_skills = {
        {"Appraisal", 50, 3, 1, 1},
        {"Bargain", 60, 3, 1, 1},
        {"Literacy", 70, 0, 1, 1},
        {"Calculation", 50, 2, 1, 1},
        {"Accounting", 45, 2, 1, 1},
        {"Language: Human", 60, 0, 1, 1},
        {"Streetwise", 40, 3, 1, 1},
        {"Detect Lies", 35, 3, 1, 1},
        {"Trade Knowledge", 60, 3, 1, 1},
    },
    .occ_related_max = 7,
    .secondary_max = 5,
};

/* MYSTIC - Spiritual Practitioner */
static OCCSkillConfig mystic_config = {
    .occ_name = "Mystic",
    .primary_count = 10,
    .primary_skills = {
        {"Meditation", 60, 2, 1, 1},
        {"Lore: Magic", 50, 2, 1, 1},
        {"Lore: Creatures", 40, 2, 1, 1},
        {"Lore: Arts & History", 45, 2, 1, 1},
        {"Spell Knowledge", 45, 3, 1, 1},
        {"Sense Magic", 40, 2, 1, 1},
        {"Linguistics", 40, 2, 1, 1},
        {"Philosophy", 50, 2, 1, 1},
        {"Healing", 45, 3, 1, 1},
        {"Lore: Demons", 35, 2, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* DRAGON HATCHLING - Young Dragon Rider */
static OCCSkillConfig dragon_hatchling_config = {
    .occ_name = "Dragon Hatchling RCC",
    .primary_count = 8,
    .primary_skills = {
        {"Hand to Hand: Combat", 45, 3, 1, 1},
        {"Sword", 55, 3, 1, 1},
        {"Mounted Combat", 40, 3, 1, 1},
        {"Animal Handling: Dragon", 55, 3, 1, 1},
        {"Climbing", 35, 2, 1, 1},
        {"Swimming", 40, 2, 1, 1},
        {"Leadership", 40, 2, 1, 1},
        {"Lore: Dragons", 60, 3, 1, 1},
    },
    .occ_related_max = 6,
    .secondary_max = 4,
};

/* OCC skill configuration lookup table */
typedef struct {
    const char *occ_name;
    OCCSkillConfig *config;
} SkillConfigEntry;

static const SkillConfigEntry skill_configs[] = {
    {"Soldier", &soldier_config},
    {"Mind Melter", &mind_melter_config},
    {"Ley Line Walker", &ley_line_walker_config},
    {"Rogue", &rogue_config},
    {"Wilderness Scout", &wilderness_scout_config},
    {"Scholar", &scholar_config},
    {"Merchant", &merchant_config},
    {"Mystic", &mystic_config},
    {"Dragon Hatchling RCC", &dragon_hatchling_config},
    {NULL, NULL}  /* Sentinel */
};

/* Simplified OCC pool skills - just names for now */
static const char *occ_pool_combat[] = {
    "Hand to Hand: Boxing", "Hand to Hand: Wrestling", "Axe",
    "Hammer/Mace", "Crossbow", "Energy Pistol", "Energy Rifle",
    "Armor Repair", "Weapon Repair", NULL
};

static const char *occ_pool_wilderness[] = {
    "Preserve Food", "Animal Husbandry", "Herbal Lore",
    "Cooking", "Rope Use", "Cryptography", NULL
};

static const char *occ_pool_scholar[] = {
    "Lore: Geography", "Lore: Technology", "Heraldry",
    "Alchemy", "Metallurgy", NULL
};

static const char *occ_pool_rogue[] = {
    "Etiquette", "Seduction", "Performance",
    "Dance", "Play Instrument", NULL
};

/* ============================================================================
 * INITIALIZATION & DISCOVERY
 * ============================================================================ */

/**
 * skill_tool_init()
 * Initialize skill system configuration
 */
void skill_tool_init(void) {
    /* Load all OCC skill configs from wiz_tools.c */
    /* Currently static-loaded; could be expanded to load from data files */
}

/* ============================================================================
 * SKILL ASSIGNMENT TOOL (RP-WIZ SKILL TOOL)
 * ============================================================================ */

/**
 * cmd_skill_assign()
 * Assign an O.C.C. and initiate skill selection for a character
 * 
 * Syntax: rp-skill-assign <player> to <occ>
 * 
 * Steps:
 * 1. Find player character
 * 2. Verify O.C.C. exists and is valid
 * 3. Assign O.C.C. and primary skills
 * 4. Create skill assignment session for wizard guidance
 */
int cmd_skill_assign(PlayerSession *sess, const char *player_name, const char *occ_name) {
    if (!sess || !player_name || !occ_name) {
        return 0;
    }
    /* Basic implementation: find player and assign occ primary skills */
    PlayerSession *target = find_player_by_name(player_name);
    if (!target) {
        send_to_player(sess, "Player not found: %s\n", player_name);
        return 0;
    }

    OCCSkillConfig *cfg = get_occ_skill_config(occ_name);
    if (!cfg) {
        send_to_player(sess, "Unknown O.C.C.: %s\n", occ_name);
        return 0;
    }

    /* Assign occ name and primary skills (basic assignment)
     * Note: assign_primary_skills should be expanded to set real skill records
     */
    if (target->character.occ) free(target->character.occ);
    target->character.occ = strdup(occ_name);
    int assigned = assign_primary_skills(&target->character, occ_name);
    save_character(target);
    send_to_player(sess, "Assigned O.C.C. %s to %s (%d primary skills set)\n", occ_name, target->username, assigned);
    send_to_player(target, "A wizard has assigned you the O.C.C. %s\n", occ_name);
    wiz_log("%s assigned O.C.C. %s -> %s", sess->username ? sess->username : "<unknown>", occ_name, target->username);
    return 1;
}

/* ============================================================================
 * STAFF OF DEMOTION (DEMOTION TOOL)
 * ============================================================================ */

/**
 * cmd_demotion()
 * Demote a character, optionally resetting O.C.C. and skills
 * 
 * Syntax: staff-of-demotion <player> level <n>
 * Syntax: staff-of-demotion <player> strip-occ
 * Syntax: staff-of-demotion <player> reset-skills
 * 
 * Actions:
 * - lower level: Reduces character level and adjusts HP/spell points
 * - strip-occ: Resets O.C.C. to "Awaiting Wizard Assignment"
 * - reset-skills: Resets character skills to base values
 */
int cmd_demotion(PlayerSession *sess, const char *player_name, const char *action, int value) {
    if (!sess || !player_name || !action) {
        return 0;
    }
    PlayerSession *target = find_player_by_name(player_name);
    if (!target) {
        send_to_player(sess, "Player not found: %s\n", player_name);
        return 0;
    }

    if (target == sess) {
        send_to_player(sess, "You cannot demote yourself.\n");
        return 0;
    }

    if (strcmp(action, "level") == 0) {
        /* Set or reduce level to value */
        if (value < 0) value = 0;
        target->character.level = value;
        /* Adjust HP to reasonable values (simple clamp) */
        if (target->character.max_hp < 1) target->character.max_hp = 10;
        if (target->character.hp > target->character.max_hp) target->character.hp = target->character.max_hp;
        send_to_player(sess, "%s's level set to %d\n", target->username, value);
        send_to_player(target, "You have been demoted to level %d by %s\n", value, sess->username);
        wiz_log("%s demoted %s -> level %d", sess->username ? sess->username : "<unknown>", target->username, value);
    } else if (strcmp(action, "strip-occ") == 0) {
        if (target->character.occ) free(target->character.occ);
        target->character.occ = strdup("Awaiting Wizard Assignment");
        send_to_player(sess, "Stripped O.C.C. from %s\n", target->username);
        send_to_player(target, "Your O.C.C. has been removed by a wizard.\n");
        wiz_log("%s stripped O.C.C. from %s", sess->username ? sess->username : "<unknown>", target->username);
    } else if (strcmp(action, "reset-skills") == 0) {
        target->character.num_skills = 0;
        memset(target->character.skills, 0, sizeof(target->character.skills));
        send_to_player(sess, "Reset skills for %s\n", target->username);
        send_to_player(target, "Your skills have been reset by a wizard.\n");
        wiz_log("%s reset skills for %s", sess->username ? sess->username : "<unknown>", target->username);
    } else {
        send_to_player(sess, "Unknown demotion action: %s\n", action);
        return 0;
    }

    save_character(target);
    return 1;
}

/* ============================================================================
 * TATTOO-GUN (MAGICAL TATTOO TOOL)
 * ============================================================================ */

/**
 * cmd_tattoo_gun()
 * Apply or remove magical tattoos to characters
 * 
 * Syntax: tattoo-gun show <player>     - Display current tattoos
 * Syntax: tattoo-gun list              - List available tattoos
 * Syntax: tattoo-gun apply <player> <tattoo> - Apply a tattoo
 * Syntax: tattoo-gun remove <player> <tattoo> - Remove a tattoo
 * 
 * Current tattoo types (FOUNDATION - EXPAND):
 * - Atlantean Dragon: +15% to all combat skills, +2 STR
 * - Ley Line Mark: +10% spell casting, +10% PPE pool
 * - Shifter Seal: +5% physical skills, shape-shifting affinity
 * - Mystic Rune: +5% all magic, +15% PPE pool
 */
/* Static table of available tattoos */
static const struct {
    const char *name;
    const char *effect;
} KNOWN_TATTOOS[] = {
    { "Atlantean Dragon", "+15% combat skills, +2 Physical Strength"    },
    { "Ley Line Mark",    "+10% spell casting, +10% PPE pool"           },
    { "Shifter Seal",     "+5% physical skills, shape-shifting affinity" },
    { "Mystic Rune",      "+5% all magic, +15% PPE pool"                },
    { NULL, NULL }
};
#define NUM_KNOWN_TATTOOS 4

int cmd_tattoo_gun(PlayerSession *sess, const char *action,
                   const char *player_name, const char *tattoo_name) {
    if (!sess || !action) return 0;

    if (strcmp(action, "list") == 0) {
        send_to_player(sess, "\n--- Available Tattoos ---\n");
        for (int i = 0; KNOWN_TATTOOS[i].name; i++) {
            send_to_player(sess, "  %-22s %s\n",
                           KNOWN_TATTOOS[i].name, KNOWN_TATTOOS[i].effect);
        }
        send_to_player(sess, "\nSyntax: tattoo-gun apply <player> <tattoo>\n");
        send_to_player(sess, "        tattoo-gun remove <player> <tattoo>\n");
        send_to_player(sess, "        tattoo-gun show <player>\n");
        return 1;
    }

    if (strcmp(action, "show") == 0) {
        if (!player_name || !player_name[0]) {
            send_to_player(sess, "Syntax: tattoo-gun show <player>\n");
            return 0;
        }
        PlayerSession *target = find_player_by_name(player_name);
        if (!target) {
            send_to_player(sess, "Player '%s' not found.\n", player_name);
            return 0;
        }
        Character *ch = &target->character;
        if (ch->num_tattoos == 0) {
            send_to_player(sess, "%s has no tattoos.\n", target->username);
            return 1;
        }
        send_to_player(sess, "\n--- Tattoos on %s ---\n", target->username);
        for (int i = 0; i < ch->num_tattoos; i++) {
            /* Look up effect string */
            const char *effect = "(unknown effect)";
            for (int j = 0; KNOWN_TATTOOS[j].name; j++) {
                if (strcasecmp(ch->tattoos[i].name, KNOWN_TATTOOS[j].name) == 0) {
                    effect = KNOWN_TATTOOS[j].effect;
                    break;
                }
            }
            send_to_player(sess, "  %d. %-22s %s\n", i + 1, ch->tattoos[i].name, effect);
        }
        return 1;
    }

    if (strcmp(action, "apply") == 0) {
        if (!player_name || !player_name[0] || !tattoo_name || !tattoo_name[0]) {
            send_to_player(sess, "Syntax: tattoo-gun apply <player> <tattoo>\n");
            return 0;
        }
        PlayerSession *target = find_player_by_name(player_name);
        if (!target) {
            send_to_player(sess, "Player '%s' not found.\n", player_name);
            return 0;
        }
        Character *ch = &target->character;
        if (ch->num_tattoos >= MAX_TATTOOS) {
            send_to_player(sess, "%s already has the maximum number of tattoos (%d).\n",
                           target->username, MAX_TATTOOS);
            return 0;
        }
        /* Validate tattoo name */
        const char *found_name = NULL;
        for (int i = 0; KNOWN_TATTOOS[i].name; i++) {
            if (strcasecmp(tattoo_name, KNOWN_TATTOOS[i].name) == 0) {
                found_name = KNOWN_TATTOOS[i].name;
                break;
            }
        }
        if (!found_name) {
            send_to_player(sess, "Unknown tattoo '%s'. Use 'tattoo-gun list' to see options.\n",
                           tattoo_name);
            return 0;
        }
        /* Check for duplicate */
        for (int i = 0; i < ch->num_tattoos; i++) {
            if (strcasecmp(ch->tattoos[i].name, found_name) == 0) {
                send_to_player(sess, "%s already has the %s tattoo.\n",
                               target->username, found_name);
                return 0;
            }
        }
        /* Apply */
        strncpy(ch->tattoos[ch->num_tattoos].name, found_name, MAX_TATTOO_NAME - 1);
        ch->tattoos[ch->num_tattoos].name[MAX_TATTOO_NAME - 1] = '\0';
        ch->num_tattoos++;
        save_character(target);
        send_to_player(target, "%s has inscribed a %s tattoo upon you.\n",
                       sess->username, found_name);
        send_to_player(sess, "Applied %s tattoo to %s.\n", found_name, target->username);
        wiz_log("%s applied tattoo '%s' to %s", sess->username, found_name, target->username);
        return 1;
    }

    if (strcmp(action, "remove") == 0) {
        if (!player_name || !player_name[0] || !tattoo_name || !tattoo_name[0]) {
            send_to_player(sess, "Syntax: tattoo-gun remove <player> <tattoo>\n");
            return 0;
        }
        PlayerSession *target = find_player_by_name(player_name);
        if (!target) {
            send_to_player(sess, "Player '%s' not found.\n", player_name);
            return 0;
        }
        Character *ch = &target->character;
        int found_idx = -1;
        for (int i = 0; i < ch->num_tattoos; i++) {
            if (strcasecmp(ch->tattoos[i].name, tattoo_name) == 0) {
                found_idx = i;
                break;
            }
        }
        if (found_idx < 0) {
            send_to_player(sess, "%s does not have the %s tattoo.\n",
                           target->username, tattoo_name);
            return 0;
        }
        /* Shift array down */
        char removed_name[MAX_TATTOO_NAME];
        strncpy(removed_name, ch->tattoos[found_idx].name, MAX_TATTOO_NAME - 1);
        removed_name[MAX_TATTOO_NAME - 1] = '\0';
        for (int i = found_idx; i < ch->num_tattoos - 1; i++) {
            ch->tattoos[i] = ch->tattoos[i + 1];
        }
        memset(&ch->tattoos[ch->num_tattoos - 1], 0, sizeof(Tattoo));
        ch->num_tattoos--;
        save_character(target);
        send_to_player(target, "Your %s tattoo has been removed by %s.\n",
                       removed_name, sess->username);
        send_to_player(sess, "Removed %s tattoo from %s.\n", removed_name, target->username);
        wiz_log("%s removed tattoo '%s' from %s", sess->username, removed_name, target->username);
        return 1;
    }

    send_to_player(sess, "Unknown action '%s'. Use: list, show, apply, remove\n", action);
    return 0;
}

/* ============================================================================
 * SKILL CONFIGURATION UTILITIES
 * ============================================================================ */

/**
 * get_occ_skill_config()
 * Retrieve the skill configuration for a given O.C.C.
 * Returns NULL if not found
 */
OCCSkillConfig *get_occ_skill_config(const char *occ_name) {
    if (!occ_name) return NULL;
    
    for (int i = 0; skill_configs[i].occ_name != NULL; i++) {
        if (strcmp(skill_configs[i].occ_name, occ_name) == 0) {
            return skill_configs[i].config;
        }
    }
    
    return NULL;
}

/**
 * get_skill_definition()
 * Delegate to the central skills system
 */
const SkillDef* get_skill_definition(const char *skill_name) {
    if (!skill_name) return NULL;
    /* Use the global skills system from skills.c */
    return skill_get_by_name(skill_name);
}

/**
 * validate_skill_assignment()
 * Check if a skill assignment is valid for the O.C.C.
 * - Validates OCC has slots available
 * - Validates skill exists
 * - Validates percentage is in valid range
 */
int validate_skill_assignment(const char *occ_name, const char *skill_name, 
                              int skill_type, int count_used) {
    OCCSkillConfig *config = get_occ_skill_config(occ_name);
    if (!config) {
        return 0;  /* Invalid O.C.C. */
    }
    
    /* Check against maximum allowed */
    if (skill_type == 'O' && count_used >= config->occ_related_max) {
        return 0;  /* OCC-related skill quota exceeded */
    }
    
    if (skill_type == 'S' && count_used >= config->secondary_max) {
        return 0;  /* Secondary skill quota exceeded */
    }
    
    /* Verify skill exists */
    if (!get_skill_definition(skill_name)) {
        return 0;  /* Skill not found */
    }
    
    return 1;  /* Valid */
}

/**
 * assign_primary_skills()
 * Assign all primary skills for an O.C.C.
 * These are mandatory and don't require wizard selection
 */
int assign_primary_skills(Character *player, const char *occ_name) {
    if (!player || !occ_name) return 0;
    OCCSkillConfig *config = get_occ_skill_config(occ_name);
    if (!config) return 0;

    /* Clear current primary entries from character (simple reset) */
    player->num_skills = 0;

    int assigned = 0;
    for (int i = 0; i < config->primary_count; i++) {
        if (!config->primary_skills[i].skill_name) continue;
        /* Map skill name to global skill id if available */
        int skill_id = skill_get_id_by_name(config->primary_skills[i].skill_name);
        if (skill_id < 0) continue; /* skill not found in global db */

        if (player->num_skills >= MAX_PLAYER_SKILLS) break;
        player->skills[player->num_skills].skill_id = skill_id;
        player->skills[player->num_skills].percentage = config->primary_skills[i].base_percent;
        player->skills[player->num_skills].uses = 0;
        player->num_skills++;
        assigned++;
    }

    return assigned;
}

/* ============================================================================
 * DEBUG & UTILITY FUNCTIONS
 * ============================================================================ */

/**
 * display_occ_skills()
 * Show all skills for an O.C.C. (for wizard reference)
 */
void display_occ_skills(PlayerSession *sess, const char *occ_name) {
    OCCSkillConfig *config = get_occ_skill_config(occ_name);

    if (!config) {
        return;
    }

    /* Output would be sent through the session/output system */
    /* TODO: Implement output via session system */
}

/* ============================================================================
 * ADMIN COMBAT / SPAWN COMMANDS
 * ============================================================================ */

/**
 * cmd_slay()
 * Instantly kill a player (or self).  Requires privilege_level >= 2 (Admin).
 *
 * Syntax: slay [<player>|me]
 */
int cmd_slay(PlayerSession *sess, const char *target_name) {
    if (!sess) return 0;
    if (sess->privilege_level < 2) {
        send_to_player(sess, "You don't have permission to do that.\n");
        return 0;
    }

    PlayerSession *target = NULL;

    if (!target_name || !*target_name || strcmp(target_name, "me") == 0) {
        target = sess;
    } else {
        target = find_player_by_name(target_name);
        if (!target) {
            send_to_player(sess, "No player found: %s\n", target_name);
            return 0;
        }
    }

    send_to_player(sess, "You smite %s from existence.\n", target->username);

    if (sess->current_room) {
        room_broadcast(sess->current_room,
            "A divine force strikes the area!\n", sess);
    }

    wiz_log("%s smote %s", sess->username ? sess->username : "<unknown>", target->username);
    handle_player_death(target, sess, NULL);
    return 1;
}

/**
 * cmd_npcspawn()
 * Spawn an NPC by type string into the wizard's current room.
 * Requires privilege_level >= 2 (Admin).
 *
 * Syntax: npcspawn <type>
 * Types: guard, bandit, mage, merchant, goblin, scout, dead_boy, brodkil, dragon, moxim, spike
 */
int cmd_npcspawn(PlayerSession *sess, const char *npc_type_str) {
    if (!sess) return 0;
    if (sess->privilege_level < 2) {
        send_to_player(sess, "You don't have permission to do that.\n");
        return 0;
    }
    if (!sess->current_room) {
        send_to_player(sess, "You have no current room.\n");
        return 0;
    }
    if (!npc_type_str || !*npc_type_str) {
        send_to_player(sess,
            "Usage: npcspawn <type>\n"
            "Valid: guard, bandit, mage, merchant, goblin, scout, dead_boy, brodkil, dragon\n");
        return 0;
    }

    /* Map type string to NpcTemplateId.
     * guard=Dog Boy (Coalition guard), bandit=Brodkil (aggressive raider),
     * merchant=Moxim (trader), and all original keywords preserved. */
    static const struct { const char *name; NpcTemplateId id; } type_map[] = {
        { "guard",     NPC_DOG_BOY         },
        { "bandit",    NPC_BRODKIL         },
        { "merchant",  NPC_MOXIM           },
        { "goblin",    NPC_GOBLIN          },
        { "scout",     NPC_DOG_BOY         },
        { "dog_boy",   NPC_DOG_BOY         },
        { "dead_boy",  NPC_DEAD_BOY        },
        { "deadboy",   NPC_DEAD_BOY        },
        { "brodkil",   NPC_BRODKIL         },
        { "dragon",    NPC_DRAGON_HATCHLING},
        { "moxim",     NPC_MOXIM           },
        { "spike",     NPC_SPIKE           },
        { "mage",      NPC_MAGE            },
        { NULL,        0                   }
    };

    NpcTemplateId template_id = -1;
    for (int i = 0; type_map[i].name; i++) {
        if (strcasecmp(type_map[i].name, npc_type_str) == 0) {
            template_id = type_map[i].id;
            break;
        }
    }

    if (template_id < 0) {
        send_to_player(sess,
            "Unknown NPC type '%s'. Valid: guard, bandit, mage, merchant\n",
            npc_type_str);
        return 0;
    }

    NPC *npc = npc_spawn(template_id, sess->current_room->id);
    if (!npc) {
        send_to_player(sess, "Failed to spawn NPC (pool full?).\n");
        return 0;
    }

    send_to_player(sess, "You summon %s into the room.\n", npc->name);
    room_broadcast(sess->current_room,
        "The air shimmers and something steps out of the ether!\n", sess);
    wiz_log("%s spawned NPC '%s' in room %d",
            sess->username ? sess->username : "<unknown>",
            npc->name, sess->current_room->id);
    return 1;
}
