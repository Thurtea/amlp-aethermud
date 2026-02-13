/*
 * driver.c - AMLP MUD Driver with Network Server
 * 
 * Main executable combining:
 * - LPC compiler and Virtual Machine
 * - Multi-client network server using select()
 * - Login system with character creation
 * - Session management and privilege system
 * - Command execution pipeline
 * - WebSocket support for web clients
 * 
 * Usage:
 *   ./driver [telnet_port] [ws_port] [master_file]
 * 
 * Default telnet port: 3000
 * Default WebSocket port: 3001
 * Default master: lib/secure/master.lpc
 */

#define _GNU_SOURCE  /* for memmem(), strcasestr() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/* Terminal ioctl */
#include <sys/ioctl.h>
#include <termios.h>

#include "vm.h"
#include "compiler.h"
#include "master_object.h"
#include "efun.h"
#include "debug.h"
#include "skills.h"
#include "combat.h"
#include "item.h"
#include "psionics.h"
#include "magic.h"
#include "websocket.h"
#include "session.h"
#include "object.h"
#include "room.h"
#include "chargen.h"
#include "race_loader.h"
#include "ui_frames.h"

#define MAX_CLIENTS 100
#define BUFFER_SIZE 4096
#define INPUT_BUFFER_SIZE 2048
#define WS_BUFFER_SIZE 65536
#define DEFAULT_PORT 3000
#define DEFAULT_WS_PORT 3001
#define DEFAULT_MASTER_PATH "lib/secure/master.lpc"
#define SESSION_TIMEOUT 1800  /* 30 minutes */

/* Connection types and session state are defined in session_internal.h */

/* Player session data (shared) */
#include "session_internal.h"

/* Global state */
int server_running = 1;
VirtualMachine *global_vm = NULL;
PlayerSession *sessions[MAX_CLIENTS];
static int first_player_created = 0;  /* Track if first player has logged in */

typedef struct {
    char raw[INPUT_BUFFER_SIZE];
    char cmd[64];
    char args[256];
    char path[32];
} CommandDebugContext;

static FILE *command_debug_log = NULL;
static int command_debug_enabled = 0;
static CommandDebugContext command_debug_ctx;

/* session management functions are implemented in src/session.c */

/* Function prototypes */
void handle_shutdown_signal(int sig);
int initialize_vm(const char *master_path);
void cleanup_vm(void);
int test_parse_file(const char *filename);  /* ADD THIS LINE */
void init_session(PlayerSession *session, int fd, const char *ip, ConnectionType conn_type);
void free_session(PlayerSession *session);
void handle_session_input(PlayerSession *session, const char *input);
void handle_websocket_data(PlayerSession *session, const uint8_t *data, size_t len);
void process_login_state(PlayerSession *session, const char *input);
void process_chargen_state(PlayerSession *session, const char *input);
void process_playing_state(PlayerSession *session, const char *input);
void send_to_player(PlayerSession *session, const char *format, ...);
void send_prompt(PlayerSession *session);
VMValue execute_command(PlayerSession *session, const char *command);
void broadcast_message(const char *message, PlayerSession *exclude);
void check_session_timeouts(void);
void* create_player_object(const char *username, const char *password_hash);
VMValue call_player_command(void *player_obj, const char *command);
int setup_ws_listener(int port);
PlayerSession* find_session_for_player(void *player_obj);

static void command_debug_init(void);
static void command_debug_set_context(const char *raw, const char *cmd,
                                      const char *args, const char *path);
static void command_debug_log_result(PlayerSession *session, VMValue result);

/* Filesystem command functions (implemented in server.c) */
int cmd_ls_filesystem(PlayerSession *session, const char *args);
int cmd_cd_filesystem(PlayerSession *session, const char *args);
int cmd_pwd_filesystem(PlayerSession *session);
int cmd_cat_filesystem(PlayerSession *session, const char *args);

/* Priority gameplay command functions */
static int cmd_tell(PlayerSession *session, const char *arg);
static int cmd_chat(PlayerSession *session, const char *arg);
static int cmd_whisper(PlayerSession *session, const char *arg);
static int cmd_shout(PlayerSession *session, const char *arg);
static int cmd_exits(PlayerSession *session, const char *arg);
static int cmd_examine(PlayerSession *session, const char *arg);
static int cmd_give_item(PlayerSession *session, const char *arg);

static const char *value_type_name(ValueType type) {
    switch (type) {
        case VALUE_UNINITIALIZED: return "uninitialized";
        case VALUE_INT: return "int";
        case VALUE_FLOAT: return "float";
        case VALUE_STRING: return "string";
        case VALUE_OBJECT: return "object";
        case VALUE_ARRAY: return "array";
        case VALUE_MAPPING: return "mapping";
        case VALUE_NULL: return "null";
        case VALUE_FUNCTION: return "function";
        default: return "unknown";
    }
}

static void command_debug_init(void) {
    const char *enabled = getenv("AMLP_COMMAND_DEBUG");
    if (!enabled || strcmp(enabled, "0") == 0) {
        return;
    }

    command_debug_log = fopen("logs/command_debug.log", "a");
    if (!command_debug_log) {
        WARN_LOG("Failed to open logs/command_debug.log");
        return;
    }

    command_debug_enabled = 1;
    memset(&command_debug_ctx, 0, sizeof(command_debug_ctx));
    DEBUG_LOG("Command debug logging enabled");
}

static void command_debug_set_context(const char *raw, const char *cmd,
                                      const char *args, const char *path) {
    if (!command_debug_enabled) return;

    if (raw) {
        strncpy(command_debug_ctx.raw, raw, sizeof(command_debug_ctx.raw) - 1);
    } else {
        command_debug_ctx.raw[0] = '\0';
    }

    if (cmd) {
        strncpy(command_debug_ctx.cmd, cmd, sizeof(command_debug_ctx.cmd) - 1);
    } else {
        command_debug_ctx.cmd[0] = '\0';
    }

    if (args) {
        strncpy(command_debug_ctx.args, args, sizeof(command_debug_ctx.args) - 1);
    } else {
        command_debug_ctx.args[0] = '\0';
    }

    if (path) {
        strncpy(command_debug_ctx.path, path, sizeof(command_debug_ctx.path) - 1);
    } else {
        command_debug_ctx.path[0] = '\0';
    }
}

static void command_debug_log_result(PlayerSession *session, VMValue result) {
    if (!command_debug_enabled || !command_debug_log) return;

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    const char *user = (session && session->username[0]) ? session->username : "guest";
    const char *ip = (session && session->ip_address[0]) ? session->ip_address : "unknown";
    const char *path = command_debug_ctx.path[0] ? command_debug_ctx.path : "unknown";

    size_t result_len = 0;
    if (result.type == VALUE_STRING && result.data.string_value) {
        result_len = strlen(result.data.string_value);
    }

    fprintf(command_debug_log,
            "[%s] user=%s ip=%s state=%d path=%s cmd='%s' args='%s' raw='%s' result=%s len=%zu\n",
            timestamp,
            user,
            ip,
            session ? session->state : -1,
            path,
            command_debug_ctx.cmd,
            command_debug_ctx.args,
            command_debug_ctx.raw,
            value_type_name(result.type),
            result_len);
    fflush(command_debug_log);
}

/* Signal handler */
void handle_shutdown_signal(int sig) {
    (void)sig;
    fprintf(stderr, "\n[Server] Received shutdown signal\n");
    server_running = 0;
}

/* Initialize VM and master object */
int initialize_vm(const char *master_path) {
    fprintf(stderr, "[Server] Initializing VM...\n");
    
    global_vm = vm_init();
    if (!global_vm) {
        fprintf(stderr, "[Server] ERROR: Failed to initialize VM\n");
        return -1;
    }
    
    fprintf(stderr, "[Server] Loading master object: %s\n", master_path);
    
    if (master_object_init(master_path, global_vm) != 0) {
        fprintf(stderr, "[Server] ERROR: Failed to load master object\n");
        vm_free(global_vm);
        global_vm = NULL;
        return -1;
    }
    
    fprintf(stderr, "[Server] VM initialized successfully\n");
    return 0;
}

/* Cleanup VM resources */
void cleanup_vm(void) {
    if (global_vm) {
        fprintf(stderr, "[Server] Cleaning up VM...\n");
        master_object_cleanup();
        vm_free(global_vm);
        global_vm = NULL;
    }
}

/* Create player object through VM */
void* create_player_object(const char *username, const char *password_hash __attribute__((unused))) {
    if (!global_vm) return NULL;
    
    fprintf(stderr, "[Server] Creating LPC player object for: %s\n", username);
    
    /* Clone full /std/player object */
    VMValue path_value = vm_value_create_string("/std/player");
    VMValue result = efun_clone_object(global_vm, &path_value, 1);
    
    if (result.type != VALUE_OBJECT || !result.data.object_value) {
        fprintf(stderr, "[Server] ERROR: Failed to clone /std/player for %s\n", username);
        return NULL;
    }
    
    obj_t *player_obj = (obj_t *)result.data.object_value;
    fprintf(stderr, "[Server] Player object cloned successfully: %s\n", 
            player_obj->name ? player_obj->name : "<unnamed>");
    
    /* Call setup_player(username, password_hash) */
    VMValue setup_args[2];
    setup_args[0] = vm_value_create_string(username);
    setup_args[1] = vm_value_create_string(password_hash ? password_hash : "");
    
    VMValue setup_result = obj_call_method(global_vm, player_obj, "setup_player", setup_args, 2);
    (void)setup_result;  /* Ignore result */
    
    fprintf(stderr, "[Server] Player object initialized for %s (methods: %d)\n", 
            username, player_obj->method_count);
    
    return (void *)player_obj;
}

/* Call player object's process_command method */
VMValue call_player_command(void *player_obj, const char *command) {
    VMValue result;
    result.type = VALUE_NULL;

    if (!player_obj || !global_vm || !command) {
        fprintf(stderr, "[Server] call_player_command: NULL parameter (obj=%p, vm=%p, cmd=%p)\n",
                player_obj, global_vm, (void*)command);
        return result;
    }

    fprintf(stderr, "[Server] Calling player command: '%s' (len=%zu)\n", command, strlen(command));

    // Cast player_obj to obj_t*
    obj_t *obj = (obj_t *)player_obj;

    // Prepare argument (command string)
    VMValue cmd_arg = vm_value_create_string(command);
    fprintf(stderr, "[Server] DEBUG: Created VMValue string: type=%d, ptr=%p, value='%s'\n",
            cmd_arg.type, (void*)cmd_arg.data.string_value, 
            cmd_arg.data.string_value ? cmd_arg.data.string_value : "(null)");

    /* Debug: check whether object exposes process_command */
    VMFunction *m = obj_get_method(obj, "process_command");
    if (!m) {
        fprintf(stderr, "[Server] DEBUG: player object '%s' has no process_command()\n",
                obj->name ? obj->name : "<unnamed>");
    } else {
        fprintf(stderr, "[Server] DEBUG: player object '%s' has process_command (%d params, %d locals)\n",
                obj->name ? obj->name : "<unnamed>", m->param_count, m->local_var_count);
    }
    
    fprintf(stderr, "[Server] DEBUG: Before call_method: stack->top=%d\n", 
            global_vm->stack ? global_vm->stack->top : -1);

    // Call process_command on the player object
    result = obj_call_method(global_vm, obj, "process_command", &cmd_arg, 1);
    
    fprintf(stderr, "[Server] DEBUG: After call_method: stack->top=%d\n", 
            global_vm->stack ? global_vm->stack->top : -1);

    /* Debug: log return type */
    if (result.type == VALUE_STRING) {
        fprintf(stderr, "[Server] DEBUG: process_command returned string: %s\n",
                result.data.string_value ? result.data.string_value : "(null)");
    } else if (result.type == VALUE_INT) {
        fprintf(stderr, "[Server] DEBUG: process_command returned int: %ld\n",
                result.data.int_value);
    } else {
        fprintf(stderr, "[Server] DEBUG: process_command returned type %d\n", result.type);
    }

    /* PHASE 2: Release our reference to the string
     * The string was ref-counted when created and again when pushed to stack.
     * We release our local reference here.
     * The stack's reference will be released when the function returns.
     */
    vm_value_release(&cmd_arg);

    return result;
}

/* Initialize a new player session */
void init_session(PlayerSession *session, int fd, const char *ip, ConnectionType conn_type) {
    memset(session, 0, sizeof(PlayerSession));
    session->fd = fd;
    session->state = STATE_CONNECTING;
    session->connection_type = conn_type;
    session->ws_state = (conn_type == CONN_WEBSOCKET) ? WS_STATE_CONNECTING : WS_STATE_CLOSED;
    session->last_activity = time(NULL);
    session->connect_time = time(NULL);
    session->player_object = NULL;
    session->privilege_level = 0;  /* Default to player */
    strncpy(session->ip_address, ip, INET_ADDRSTRLEN - 1);
    session->input_length = 0;
    session->ws_buffer_length = 0;
    session->is_color = 1;  /* ANSI color on by default */
    /* Default terminal size until detected/overridden */
    session->terminal_width = 80;
    session->terminal_height = 24;

    /* Try to detect terminal size if the fd is a controlling tty (may fail on sockets) */
    if (conn_type == CONN_TELNET && fd >= 0) {
        struct winsize ws;
        if (ioctl(fd, TIOCGWINSZ, &ws) == 0) {
            if (ws.ws_col > 0) session->terminal_width = (int)ws.ws_col;
            if (ws.ws_row > 0) session->terminal_height = (int)ws.ws_row;
        }
    }
}

/* Free session resources */
void free_session(PlayerSession *session) {
    if (!session) return;

    /* Clean up combat state on disconnect */
    if (session->in_combat) {
        combat_disengage(session);
    }

    /* Clean up snoop relationships */
    if (session->snooping) {
        session->snooping->snooped_by = NULL;
        session->snooping = NULL;
    }
    if (session->snooped_by) {
        session->snooped_by->snooping = NULL;
        session->snooped_by = NULL;
    }

    if (session->player_object) {
        /* Persist a minimal savefile on disconnect as a temporary measure
         * until the VM-backed LPC objects are fully implemented. This
         * creates lib/save/players/<name>.o with basic info so the mudlib
         * can detect a savefile exists. */
        if (session->username && session->username[0]) {
            char path[512];
            snprintf(path, sizeof(path), "lib/save/players/%s.o", session->username);
            FILE *f = fopen(path, "w");
            if (f) {
                fprintf(f, "# AMLP minimal save file\n");
                fprintf(f, "name:%s\n", session->username);
                fprintf(f, "priv:%d\n", session->privilege_level);
                fclose(f);
                fprintf(stderr, "[Server] Wrote minimal savefile: %s\n", path);
            } else {
                fprintf(stderr, "[Server] WARNING: failed to write savefile %s\n", path);
            }
        }

        /* TODO: Call destruct on player object when object system ready */
        session->player_object = NULL;
    }
    
    if (session->fd > 0) {
        close(session->fd);
        session->fd = -1;
    }
    
    free(session);
}

/* Send formatted output to player */
/* Find the session associated with a player object */
PlayerSession* find_session_for_player(void *player_obj) {
    if (!player_obj) return NULL;
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i] && sessions[i]->player_object == player_obj) {
            return sessions[i];
        }
    }
    
    return NULL;
}

/* Send a message to a player's session */
void send_message_to_player_session(void *player_obj, const char *message) {
    if (!player_obj || !message) return;
    
    PlayerSession *session = find_session_for_player(player_obj);
    if (session) {
        send_to_player(session, "%s", message);
    }
}

void send_to_player(PlayerSession *session, const char *format, ...) {
    if (!session || session->fd <= 0) return;
    
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer) - 3, format, args);
    va_end(args);
    
    if (len > 0 && len < BUFFER_SIZE - 3) {
        /* Snoop echo: if someone is snooping this session, echo output */
        if (session->snooped_by && session->snooped_by->fd > 0) {
            char snoop_buf[BUFFER_SIZE + 64];
            int slen = snprintf(snoop_buf, sizeof(snoop_buf), "[Snoop: %s] %s",
                                session->username, buffer);
            if (slen > 0 && session->snooped_by->connection_type == CONN_TELNET) {
                send(session->snooped_by->fd, snoop_buf, slen, 0);
            }
        }

        if (session->connection_type == CONN_WEBSOCKET) {
            /* WebSocket: send as text frame */
            if (session->ws_state == WS_STATE_OPEN) {
                /* Convert ANSI codes for web display */
                char *web_text = ws_convert_ansi(buffer, 1);
                if (web_text) {
                    /* Normalize line endings for web */
                    char *normalized = ws_normalize_line_endings(web_text);
                    free(web_text);
                    
                    if (normalized) {
                        size_t frame_len;
                        uint8_t *frame = ws_encode_text(normalized, &frame_len);
                        free(normalized);
                        
                        if (frame) {
                            send(session->fd, frame, frame_len, 0);
                            free(frame);
                        }
                    }
                }
            }
        } else {
            /* Telnet: ensure CRLF line endings */
            if (buffer[len-1] == '\n' && (len < 2 || buffer[len-2] != '\r')) {
                buffer[len-1] = '\r';
                buffer[len] = '\n';
                buffer[len+1] = '\0';
                len++;
            }
            send(session->fd, buffer, len, 0);
        }
    }
}

/* Send command prompt based on state */
void send_prompt(PlayerSession *session) {
    switch (session->state) {
        case STATE_CONNECTING:
            send_to_player(session,
                "\r\n"
                "=========================================\r\n"
                "    AMLP Driver - Development Server\r\n"
                "             Version 0.1.0\r\n"
                "=========================================\r\n"
                "\r\n"
                "Welcome to the AMLP MUD!\r\n"
                "\r\n"
                "Enter your name: ");
            session->state = STATE_GET_NAME;
            break;
            
        case STATE_GET_NAME:
            send_to_player(session, "Enter your name: ");
            break;
            
        case STATE_GET_PASSWORD:
            send_to_player(session, "Password: ");
            break;
            
        case STATE_NEW_PASSWORD:
            send_to_player(session, "Choose a password: ");
            break;
            
        case STATE_CONFIRM_PASSWORD:
            send_to_player(session, "Confirm password: ");
            break;
            
        case STATE_PLAYING:
            send_to_player(session, "\r\n> ");
            break;
            
        default:
            break;
    }
}

/* ========================================================================
 * PRIORITY GAMEPLAY COMMANDS
 * ======================================================================== */

/* Helper: Find a player session by name */
PlayerSession* find_player_by_name(const char *name) {
    if (!name || !*name) return NULL;
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i] && 
            sessions[i]->state == STATE_PLAYING && 
            sessions[i]->username && 
            strcasecmp(sessions[i]->username, name) == 0) {
            return sessions[i];
        }
    }
    return NULL;
}

/* 1. TELL - Send private message to another player */
static int cmd_tell(PlayerSession *session, const char *arg) {
    char target_name[64];
    char message[1024];
    
    if (!arg || !*arg) {
        send_to_player(session, "Usage: tell <player> <message>\n");
        return 1;
    }
    
    /* Parse: "playername message text" */
    if (sscanf(arg, "%63s %1023[^\n]", target_name, message) != 2) {
        send_to_player(session, "Usage: tell <player> <message>\n");
        return 1;
    }
    
    /* Find target player */
    PlayerSession *target = find_player_by_name(target_name);
    if (!target) {
        send_to_player(session, "Player '%s' not found.\n", target_name);
        return 1;
    }
    
    if (target == session) {
        send_to_player(session, "Talking to yourself again?\n");
        return 1;
    }
    
    /* Send messages - blue text when wizard is involved */
    if (session->privilege_level >= 1 || target->privilege_level >= 1) {
        send_to_player(target, "\n\033[1;34m<%s tells you> %s\033[0m\n", session->username, message);
        send_to_player(session, "\033[1;34m<You tell %s> %s\033[0m\n", target->username, message);
    } else {
        send_to_player(target, "\n<%s tells you> %s\n", session->username, message);
        send_to_player(session, "<You tell %s> %s\n", target->username, message);
    }

    /* Track for reply command */
    strncpy(target->last_tell_from, session->username, sizeof(target->last_tell_from) - 1);
    target->last_tell_from[sizeof(target->last_tell_from) - 1] = '\0';

    return 1;
}

/* 2. CHAT - Global chat channel */
static int cmd_chat(PlayerSession *session, const char *arg) {
    if (!arg || !*arg) {
        send_to_player(session, "Usage: chat <message>\n");
        return 1;
    }
    
    /* Broadcast to all players */
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i] && sessions[i]->state == STATE_PLAYING) {
            if (sessions[i] == session) {
                send_to_player(sessions[i], "[CHAT: %s] %s\n", session->username, arg);
            } else {
                send_to_player(sessions[i], "\n[CHAT: %s] %s\n", session->username, arg);
            }
        }
    }
    
    return 1;
}

/* 3. WHISPER - Private message to someone in the same room */
static int cmd_whisper(PlayerSession *session, const char *arg) {
    char target_name[64];
    char message[1024];
    
    if (!arg || !*arg) {
        send_to_player(session, "Usage: whisper <player> <message>\n");
        return 1;
    }
    
    if (!session->current_room) {
        send_to_player(session, "You are nowhere.\n");
        return 1;
    }
    
    /* Parse: "playername message text" */
    if (sscanf(arg, "%63s %1023[^\n]", target_name, message) != 2) {
        send_to_player(session, "Usage: whisper <player> <message>\n");
        return 1;
    }
    
    /* Find player in current room */
    PlayerSession *target = NULL;
    Room *room = session->current_room;
    
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] && room->players[i] != session &&
            room->players[i]->username &&
            strcasecmp(room->players[i]->username, target_name) == 0) {
            target = room->players[i];
            break;
        }
    }
    
    if (!target) {
        send_to_player(session, "Player '%s' not found in this room.\n", target_name);
        return 1;
    }
    
    /* Send whisper */
    send_to_player(target, "%s whispers to you: %s\n", session->username, message);
    send_to_player(session, "You whisper to %s: %s\n", target->username, message);
    
    /* Let others know something was whispered (but not what) */
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] && room->players[i] != session && room->players[i] != target) {
            send_to_player(room->players[i], "%s whispers something to %s.\n",
                          session->username, target->username);
        }
    }
    
    return 1;
}

/* 4. SHOUT - Loud message heard in area */
static int cmd_shout(PlayerSession *session, const char *arg) {
    if (!arg || !*arg) {
        send_to_player(session, "Usage: shout <message>\n");
        return 1;
    }
    
    if (!session->current_room) {
        send_to_player(session, "You are nowhere.\n");
        return 1;
    }
    
    Room *room = session->current_room;
    
    /* Shout in current room */
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] && room->players[i] != session) {
            send_to_player(room->players[i], "%s shouts: %s\n", session->username, arg);
        }
    }
    send_to_player(session, "You shout: %s\n", arg);
    
    /* TODO: Shout to adjacent rooms (requires room linkage) */
    
    return 1;
}

/* 5. EXITS - Show available exits from current room */
static int cmd_exits(PlayerSession *session, const char *arg) {
    (void)arg;  /* Unused */
    
    if (!session->current_room) {
        send_to_player(session, "You are nowhere.\n");
        return 1;
    }
    
    Room *room = session->current_room;
    send_to_player(session, "\nObvious exits:\n");
    
    int has_exit = 0;
    if (room->exits.north >= 0) {
        send_to_player(session, "  North\n");
        has_exit = 1;
    }
    if (room->exits.south >= 0) {
        send_to_player(session, "  South\n");
        has_exit = 1;
    }
    if (room->exits.east >= 0) {
        send_to_player(session, "  East\n");
        has_exit = 1;
    }
    if (room->exits.west >= 0) {
        send_to_player(session, "  West\n");
        has_exit = 1;
    }
    if (room->exits.up >= 0) {
        send_to_player(session, "  Up\n");
        has_exit = 1;
    }
    if (room->exits.down >= 0) {
        send_to_player(session, "  Down\n");
        has_exit = 1;
    }
    
    if (!has_exit) {
        send_to_player(session, "  None.\n");
    }
    send_to_player(session, "\n");
    
    return 1;
}

/* 6. EXAMINE - Inspect objects/players in detail */
static int cmd_examine(PlayerSession *session, const char *arg) {
    if (!arg || !*arg) {
        send_to_player(session, "Examine what?\n");
        return 1;
    }
    
    if (!session->current_room) {
        send_to_player(session, "You are nowhere.\n");
        return 1;
    }
    
    /* Check for "room" or "here" */
    if (strcasecmp(arg, "room") == 0 || strcasecmp(arg, "here") == 0) {
        cmd_look(session, "");
        return 1;
    }
    
    /* Look for player in room */
    Room *room = session->current_room;
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] && room->players[i]->username &&
            strcasecmp(room->players[i]->username, arg) == 0) {
            
            PlayerSession *target = room->players[i];
            if (target == session) {
                send_to_player(session, "That's you!\n");
            } else {
                send_to_player(session, "You examine %s.\n", target->username);
                send_to_player(session, "Race: %s  O.C.C.: %s\n",
                              target->character.race,
                              target->character.occ);
                send_to_player(session, "They appear to be in good health.\n");
            }
            return 1;
        }
    }
    
    /* Check inventory */
    Item *inv_item = inventory_find(&session->character.inventory, arg);
    if (inv_item) {
        send_to_player(session, "%s (%s)\n", inv_item->name, item_type_to_string(inv_item->type));
        send_to_player(session, "%s\n", inv_item->description);
        if (inv_item->type == ITEM_WEAPON_MELEE || inv_item->type == ITEM_WEAPON_RANGED) {
            send_to_player(session, "Damage: %dd%d %s  Weight: %d lbs  Value: %d cr\n",
                inv_item->stats.damage_dice, inv_item->stats.damage_sides,
                inv_item->stats.is_mega_damage ? "MD" : "SDC",
                inv_item->weight, inv_item->value);
        } else if (inv_item->type == ITEM_ARMOR) {
            send_to_player(session, "AR: %d  MDC/SDC: %d/%d  Weight: %d lbs  Value: %d cr\n",
                inv_item->stats.ar, inv_item->current_durability, inv_item->stats.sdc_mdc,
                inv_item->weight, inv_item->value);
        } else {
            send_to_player(session, "Weight: %d lbs  Value: %d cr\n",
                inv_item->weight, inv_item->value);
        }
        return 1;
    }

    /* Check room items */
    Item *room_item2 = room_find_item(room, arg);
    if (room_item2) {
        send_to_player(session, "%s (%s)\n", room_item2->name, item_type_to_string(room_item2->type));
        send_to_player(session, "%s\n", room_item2->description);
        return 1;
    }

    /* Check room details (examinable scenery from LPC set_items) */
    const char *detail_desc = room_find_detail(room, arg);
    if (detail_desc) {
        send_to_player(session, "%s\n", detail_desc);
        return 1;
    }

    send_to_player(session, "You don't see that here.\n");

    return 1;
}

/* 10. GIVE - Give items to other players */
static int cmd_give_item(PlayerSession *session, const char *arg) {
    if (!arg || !*arg) {
        send_to_player(session, "Usage: give <item> to <player>\n");
        return 1;
    }

    if (!session->current_room) {
        send_to_player(session, "You are nowhere.\n");
        return 1;
    }

    /* Parse "item to player" or "item player" */
    char item_name[128], target_name[64];
    const char *sep = strcasestr(arg, " to ");
    if (sep) {
        size_t ilen = (size_t)(sep - arg);
        if (ilen >= sizeof(item_name)) ilen = sizeof(item_name) - 1;
        strncpy(item_name, arg, ilen);
        item_name[ilen] = '\0';
        strncpy(target_name, sep + 4, sizeof(target_name) - 1);
        target_name[sizeof(target_name) - 1] = '\0';
    } else {
        /* Try last word as player name */
        const char *last_space = strrchr(arg, ' ');
        if (!last_space) {
            send_to_player(session, "Usage: give <item> to <player>\n");
            return 1;
        }
        size_t ilen = (size_t)(last_space - arg);
        if (ilen >= sizeof(item_name)) ilen = sizeof(item_name) - 1;
        strncpy(item_name, arg, ilen);
        item_name[ilen] = '\0';
        strncpy(target_name, last_space + 1, sizeof(target_name) - 1);
        target_name[sizeof(target_name) - 1] = '\0';
    }

    /* Trim whitespace */
    char *p = item_name + strlen(item_name) - 1;
    while (p > item_name && *p == ' ') *p-- = '\0';
    p = target_name;
    while (*p == ' ') p++;
    if (p != target_name) memmove(target_name, p, strlen(p) + 1);

    /* Find target player in same room */
    PlayerSession *target = NULL;
    Room *room = session->current_room;
    for (int i = 0; i < room->num_players; i++) {
        if (room->players[i] && room->players[i] != session &&
            strcasecmp(room->players[i]->username, target_name) == 0) {
            target = room->players[i];
            break;
        }
    }
    if (!target) {
        send_to_player(session, "%s is not here.\n", target_name);
        return 1;
    }

    /* Find item in giver's inventory */
    Item *item = inventory_find(&session->character.inventory, item_name);
    if (!item) {
        send_to_player(session, "You don't have '%s'.\n", item_name);
        return 1;
    }

    /* Check if equipped */
    if (item->is_equipped) {
        send_to_player(session, "You need to unequip %s first.\n", item->name);
        return 1;
    }

    /* Check if target can carry it */
    if (!inventory_can_carry(&target->character.inventory, item->weight)) {
        send_to_player(session, "%s can't carry that much weight.\n", target->username);
        return 1;
    }

    /* Transfer */
    Item *removed = inventory_remove(&session->character.inventory, item_name);
    if (removed) {
        inventory_add(&target->character.inventory, removed);
        send_to_player(session, "You give %s to %s.\n", removed->name, target->username);
        send_to_player(target, "%s gives you %s.\n", session->username, removed->name);

        char msg[256];
        snprintf(msg, sizeof(msg), "%s gives %s to %s.\n",
                 session->username, removed->name, target->username);
        room_broadcast(room, msg, session);
    }

    return 1;
}

/* Helper: extract the first quoted string after a setter call in LPC source.
 * Searches for the setter name (e.g. "set_short"), then returns the first
 * double-quoted value following it.  Supports both snake_case (set_short)
 * and PascalCase (SetShort) conventions.  Returns a malloc'd string or NULL. */
static char* clone_extract_string(const char *buf, const char *snake, const char *pascal) {
    const char *p = strstr(buf, snake);
    if (!p && pascal) p = strstr(buf, pascal);
    if (!p) return NULL;
    p = strchr(p, '"');
    if (!p) return NULL;
    p++;  /* skip opening quote */
    const char *end = strchr(p, '"');
    if (!end) return NULL;
    size_t len = (size_t)(end - p);
    char *val = malloc(len + 1);
    if (!val) return NULL;
    memcpy(val, p, len);
    val[len] = '\0';
    return val;
}

/* Helper: extract an integer argument from a setter call, e.g. set_weight(5).
 * Supports both naming conventions. Returns 0 if not found. */
static int clone_extract_int(const char *buf, const char *snake, const char *pascal) {
    const char *p = strstr(buf, snake);
    if (!p && pascal) p = strstr(buf, pascal);
    if (!p) return 0;
    p = strchr(p, '(');
    if (!p) return 0;
    return atoi(p + 1);
}

/* Extract integer value from set_property("key", N) in LPC source.
 * Returns 1 if found and sets *out, 0 otherwise. */
static int clone_extract_property_int(const char *buf, const char *key, int *out) {
    const char *p = buf;
    char needle[128];
    snprintf(needle, sizeof(needle), "set_property(\"%s\",", key);
    p = strstr(buf, needle);
    if (!p) return 0;
    p = strchr(p, ',');
    if (!p) return 0;
    *out = atoi(p + 1);
    return 1;
}

/* Extract string value from set_property("key", "value") in LPC source.
 * Returns malloc'd string or NULL. */
static char* clone_extract_property_string(const char *buf, const char *key) {
    char needle[128];
    snprintf(needle, sizeof(needle), "set_property(\"%s\",", key);
    const char *p = strstr(buf, needle);
    if (!p) return NULL;
    p = strchr(p, '"');
    if (!p) return NULL;
    p++;
    const char *end = strchr(p, '"');
    if (!end) return NULL;
    size_t len = (size_t)(end - p);
    char *val = malloc(len + 1);
    if (!val) return NULL;
    memcpy(val, p, len);
    val[len] = '\0';
    return val;
}

/* Resolve an LPC-style clone argument to a filesystem path.
 * Handles: /lib/objects/weapons/sword, lib/objects/weapons/sword,
 *          objects/weapons/sword, /lib/objects/weapons/sword.lpc
 * Writes the result into out_path (max out_size bytes).
 * Returns 1 if the resolved file exists, 0 otherwise. */
int resolve_lpc_path(const char *args, char *out_path, size_t out_size) {
    /* Strip leading slash */
    const char *p = (args[0] == '/') ? args + 1 : args;

    /* Strip trailing .lpc if the user typed it (we add it ourselves) */
    char clean[512];
    strncpy(clean, p, sizeof(clean) - 1);
    clean[sizeof(clean) - 1] = '\0';
    size_t clen = strlen(clean);
    if (clen > 4 && strcmp(clean + clen - 4, ".lpc") == 0) {
        clean[clen - 4] = '\0';
    }

    /* Build candidate paths in order of preference */
    const char *fmts[] = {
        "%s.lpc",                 /* exact path or already has lib/ prefix */
        "lib/%s.lpc",             /* relative to lib/ */
        "lib/objects/%s.lpc",     /* common objects folder */
        "lib/objects/%s/%s.lpc",  /* try nested under a folder matching base */
        "lib/psionics/%s.lpc",    /* psionics folder */
        "lib/objects/psionic/%s.lpc",
        "lib/occs/%s.lpc",
        NULL
    };

    for (int i = 0; fmts[i]; i++) {
        if (strstr(fmts[i], "%s/%s.lpc")) {
            /* attempt to split clean into folder/name if it contains a '/'
             * otherwise try common folder + clean */
            snprintf(out_path, out_size, "lib/objects/%s.lpc", clean);
            if (access(out_path, R_OK) == 0) {
                fprintf(stderr, "[Clone] Resolved '%s' -> '%s'\n", args, out_path);
                return 1;
            }
            continue;
        }
        snprintf(out_path, out_size, fmts[i], clean);
        if (access(out_path, R_OK) == 0) {
            fprintf(stderr, "[Clone] Resolved '%s' -> '%s'\n", args, out_path);
            return 1;
        }
    }

    fprintf(stderr, "[Clone] Could not resolve '%s' (tried '%s.lpc', 'lib/%s.lpc')\n",
            args, clean, clean);
    return 0;
}

/* Parse a simple LPC object file and create a C Item from it.
 * Extracts property setters from the source text to populate a C Item struct.
 * Supports both snake_case (set_short) and PascalCase (SetShort) naming. */
Item* item_create_from_lpc(const char *fs_path) {
    FILE *f = fopen(fs_path, "r");
    if (!f) {
        fprintf(stderr, "[Clone] fopen failed for '%s': %s\n", fs_path, strerror(errno));
        return NULL;
    }

    char buf[4096];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    buf[n] = '\0';

    /* Allocate a blank item */
    Item *item = (Item *)calloc(1, sizeof(Item));
    if (!item) return NULL;
    item->id = -1;  /* dynamic item, not from template */
    item->type = ITEM_MISC;
    item->stack_count = 1;

    /* Extract string properties (try both naming conventions) */
    char *name_val  = clone_extract_string(buf, "set_name(",  "SetKeyName(");
    char *short_val = clone_extract_string(buf, "set_short(", "SetShort(");
    char *long_val  = clone_extract_string(buf, "set_long(",  "SetLong(");

    /* Prefer short description as display name (matches inventory display).
     * Fall back to set_name value if no short desc. */
    if (short_val) {
        item->name = short_val;
        free(name_val);
    } else if (name_val) {
        item->name = name_val;
    } else {
        item->name = strdup("unknown object");
    }

    item->description = long_val ? long_val : strdup("An unremarkable object.");

    /* Extract numeric properties */
    item->weight = clone_extract_int(buf, "set_weight(", "SetMass(");
    item->value  = clone_extract_int(buf, "set_value(",  "SetBaseCost(");

    /* Extract known set_property(...) values used in many LPC objects */
    int tmp;
    if (clone_extract_property_int(buf, "damage_dice", &tmp)) {
        item->stats.damage_dice = tmp;
    }
    if (clone_extract_property_int(buf, "damage_sides", &tmp)) {
        item->stats.damage_sides = tmp;
    }
    if (clone_extract_property_int(buf, "damage_bonus", &tmp)) {
        item->stats.damage_bonus = tmp;
    }
    if (clone_extract_property_int(buf, "is_mega_damage", &tmp)) {
        item->stats.is_mega_damage = tmp ? true : false;
    }
    if (clone_extract_property_int(buf, "strike_bonus", &tmp)) {
        item->stats.strike_bonus = tmp;
    }
    if (clone_extract_property_int(buf, "parry_bonus", &tmp)) {
        item->stats.parry_bonus = tmp;
    }
    if (clone_extract_property_int(buf, "ar", &tmp)) {
        item->stats.ar = tmp;
    }
    /* weapon_type may be set via set_property("weapon_type", "sword") */
    char *wtype = clone_extract_property_string(buf, "weapon_type");
    if (wtype) {
        if (strstr(wtype, "sword")) item->weapon_type = WEAPON_SWORD;
        else if (strstr(wtype, "knife")) item->weapon_type = WEAPON_KNIFE;
        else if (strstr(wtype, "axe")) item->weapon_type = WEAPON_AXE;
        else if (strstr(wtype, "pistol")) item->weapon_type = WEAPON_PISTOL;
        else if (strstr(wtype, "rifle")) item->weapon_type = WEAPON_RIFLE;
        free(wtype);
    }

    /* If the LPC explicitly indicates damage fields via set_property, prefer them over filename heuristics */

    /* Infer type from path keywords */
    if (strstr(fs_path, "weapon") || strstr(fs_path, "weap")) {
        item->type = ITEM_WEAPON_MELEE;
        if (item->stats.damage_dice == 0) item->stats.damage_dice = 1;
        if (item->stats.damage_sides == 0) item->stats.damage_sides = 6;
        if (item->weapon_type == WEAPON_UNARMED) item->weapon_type = WEAPON_SWORD;
    } else if (strstr(fs_path, "armor")) {
        item->type = ITEM_ARMOR;
        if (item->stats.ar == 0) item->stats.ar = 10;
        if (item->stats.sdc_mdc == 0) item->stats.sdc_mdc = 30;
        if (item->current_durability == 0) item->current_durability = item->stats.sdc_mdc;
    }

    fprintf(stderr, "[Clone] Created item from '%s': name='%s' weight=%d value=%d\n",
            fs_path, item->name, item->weight, item->value);
    return item;
}

/* Execute command through VM */
VMValue execute_command(PlayerSession *session, const char *command) {
    VMValue result;
    result.type = VALUE_NULL;
    
    if (!global_vm || !session) {
        return result;
    }
    
    fprintf(stderr, "[execute_command] INPUT: command=%p '%s'\n", 
            (void*)command, command ? command : "(NULL)");
    
    /* Parse command early for filesystem checks */
    char cmd_buffer[256];
    strncpy(cmd_buffer, command, sizeof(cmd_buffer) - 1);
    cmd_buffer[sizeof(cmd_buffer) - 1] = '\0';
    
    /* Convert to lowercase for comparison */
    char *cmd = cmd_buffer;
    for (int i = 0; cmd[i]; i++) {
        cmd[i] = tolower(cmd[i]);
    }
    
    /* Parse command and arguments */
    char *args = strchr(cmd, ' ');
    if (args) {
        *args = '\0';
        args++;
        while (*args == ' ') args++;
    }

    command_debug_set_context(command, cmd, args ? args : "", "builtin");
    
    /* Filesystem commands for wizards/admins - CHECK FIRST BEFORE PLAYER OBJECT */
    if (session->privilege_level >= 1) {
        if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "dir") == 0) {
            command_debug_set_context(command, cmd, args ? args : "", "filesystem");
            cmd_ls_filesystem(session, args);
            return vm_value_create_string("");
        }
        
        if (strcmp(cmd, "cd") == 0) {
            command_debug_set_context(command, cmd, args ? args : "", "filesystem");
            cmd_cd_filesystem(session, args);
            return vm_value_create_string("");
        }
        
        if (strcmp(cmd, "pwd") == 0) {
            command_debug_set_context(command, cmd, args ? args : "", "filesystem");
            cmd_pwd_filesystem(session);
            return vm_value_create_string("");
        }
        
        if (strcmp(cmd, "cat") == 0 || strcmp(cmd, "more") == 0) {
            command_debug_set_context(command, cmd, args ? args : "", "filesystem");
            cmd_cat_filesystem(session, args);
            return vm_value_create_string("");
        }
    }
    
    /* If player object exists, route command through it. Set the
     * current VM session so efuns like this_player() can access it. */
    if (session->player_object) {
        command_debug_set_context(command, cmd, args ? args : "", "vm");
        set_current_session(session);
        result = call_player_command(session->player_object, command);
        set_current_session(NULL);

        /* If VM returns valid result, use it */
        if (result.type == VALUE_STRING && result.data.string_value) {
            return result;
        }

        command_debug_set_context(command, cmd, args ? args : "", "builtin");
    }
    
    /* Fallback to built-in commands if no player object or no result */
    
    /* Built-in commands */
    
    /* Movement commands */
    if (strcmp(cmd, "north") == 0 || strcmp(cmd, "n") == 0) {
        cmd_move(session, "north");
        result.type = VALUE_NULL;
        return result;
    }
    if (strcmp(cmd, "south") == 0 || strcmp(cmd, "s") == 0) {
        cmd_move(session, "south");
        result.type = VALUE_NULL;
        return result;
    }
    if (strcmp(cmd, "east") == 0 || strcmp(cmd, "e") == 0) {
        cmd_move(session, "east");
        result.type = VALUE_NULL;
        return result;
    }
    if (strcmp(cmd, "west") == 0 || strcmp(cmd, "w") == 0) {
        cmd_move(session, "west");
        result.type = VALUE_NULL;
        return result;
    }
    if (strcmp(cmd, "up") == 0 || strcmp(cmd, "u") == 0) {
        cmd_move(session, "up");
        result.type = VALUE_NULL;
        return result;
    }
    if (strcmp(cmd, "down") == 0 || strcmp(cmd, "d") == 0) {
        cmd_move(session, "down");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "logout") == 0) {
        /* Auto-save before quitting */
        send_to_player(session, "\r\nSaving your character...\r\n");
        if (save_character(session)) {
            send_to_player(session, " Character saved.\r\n");
        } else {
            send_to_player(session, " Warning: Failed to save character.\r\n");
        }
        
        return vm_value_create_string("quit");
    }
    
    if (strcmp(cmd, "save") == 0) {
        if (save_character(session)) {
            send_to_player(session, " Character saved successfully.\r\n");
        } else {
            send_to_player(session, " Failed to save character.\r\n");
        }
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "help") == 0) {
        int w = FRAME_WIDTH;
        send_to_player(session, "\r\n");
        frame_top(session, w);
        frame_title(session, "AETHERMUD COMMAND REFERENCE", w);
        frame_header(session, "BASIC", w);
        frame_line(session, "help                - Show this help", w);
        frame_line(session, "look / l            - Look around", w);
        frame_line(session, "inventory / i       - Check inventory", w);
        frame_line(session, "stats / score       - Character sheet", w);
        frame_line(session, "skills              - Show all skills", w);
        frame_line(session, "pskills / sskills   - Primary / secondary", w);
        frame_line(session, "save                - Save character", w);
        frame_line(session, "quit / logout       - Save and disconnect", w);
        frame_header(session, "MOVEMENT", w);
        frame_line(session, "north/south/east/west  (or n/s/e/w)", w);
        frame_line(session, "up / down              (or u/d)", w);
        frame_line(session, "rift <dest>         - Rift travel (500 cr)", w);
        frame_header(session, "COMMUNICATION", w);
        frame_line(session, "say <msg>           - Speak (in language)", w);
        frame_line(session, "tell <player> <msg> - Private message", w);
        frame_line(session, "reply <msg>         - Reply to last tell", w);
        frame_line(session, "chat <msg>          - Global chat", w);
        frame_line(session, "shout <msg>         - Shout nearby", w);
        frame_line(session, "whisper <who> <msg> - Whisper in room", w);
        frame_line(session, "emote <action>      - Perform an emote", w);
        frame_line(session, "converse            - Toggle talk mode", w);
        frame_line(session, "speak <language>    - Change language", w);
        frame_line(session, "languages / langs   - List languages", w);
        frame_header(session, "COMBAT", w);
        frame_line(session, "attack <target>     - Engage combat", w);
        frame_line(session, "stop                - Disengage", w);
        frame_line(session, "flee                - Attempt escape", w);
        frame_line(session, "assist <player>     - Help an ally", w);
        frame_line(session, "autoparry/autododge - Toggle auto-defense", w);
        frame_line(session, "wimpy <percent>     - Auto-flee threshold", w);
        frame_line(session, "rest / wake         - Rest / stand up", w);
        frame_header(session, "SOCIAL", w);
        frame_line(session, "introduce <player>  - Introduce yourself", w);
        frame_line(session, "remember            - Known introductions", w);
        frame_line(session, "who                 - Players online", w);
        frame_line(session, "title <text>        - Set who-list title", w);
        frame_header(session, "OTHER", w);
        frame_line(session, "credits / balance   - Check credits", w);
        frame_line(session, "clan                - View/join a clan", w);
        frame_line(session, "scan                - Peek adjacent rooms", w);
        frame_line(session, "examine <target>    - Inspect object/player", w);
        frame_line(session, "map                 - ASCII area map", w);
        frame_line(session, "brief               - Toggle brief mode", w);
        frame_line(session, "spells / powers     - Magic / psionics", w);
        if (session->privilege_level >= 1) {
            frame_header(session, "WIZARD (Level 1+)", w);
            frame_line(session, "wiztool / wiz       - Wizard command ref", w);
            frame_line(session, "goto <room>         - Teleport to room", w);
            frame_line(session, "set <p> <f> <v>     - Set player attr", w);
            frame_line(session, "heal <player>       - Restore all pools", w);
            frame_line(session, "slay <target>       - Instant kill", w);
            frame_line(session, "trans/summon <p>    - Teleport player", w);
            frame_line(session, "finger <player>     - Detailed info", w);
            frame_line(session, "award <p> <xp>      - Give experience", w);
            frame_line(session, "clone <path>        - Clone object", w);
            frame_line(session, "eval <code>         - Execute LPC", w);
            frame_line(session, "snoop / invis       - Spy / hide", w);
            frame_line(session, "godmode             - Toggle immunity", w);
            frame_line(session, "peace               - End room combat", w);
            frame_line(session, "ls/cd/pwd/cat       - Filesystem", w);
        }
        if (session->privilege_level >= 2) {
            frame_header(session, "ADMIN (Level 2)", w);
            frame_line(session, "promote <p> <lvl>   - Set privilege", w);
            frame_line(session, "force <p> <cmd>     - Force command", w);
            frame_line(session, "shutdown / reboot   - Server control", w);
            frame_line(session, "kick / ban <player> - Remove player", w);
            frame_line(session, "broadcast <msg>     - Message all", w);
            frame_line(session, "users               - User listing", w);
        }
        frame_bottom(session, w);
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "look") == 0 || strcmp(cmd, "l") == 0) {
        cmd_look(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "rift") == 0) {
        cmd_rift(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "credits") == 0 || strcmp(cmd, "balance") == 0) {
        send_to_player(session, "You have %d credits.\r\n", session->character.credits);
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "clan") == 0) {
        cmd_clan(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "speak") == 0) {
        cmd_speak(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "languages") == 0 || strcmp(cmd, "langs") == 0) {
        cmd_languages(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "grant") == 0) {
        cmd_grant(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "revoke") == 0) {
        cmd_revoke(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "stats") == 0 || strcmp(cmd, "score") == 0) {
        cmd_stats(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "skills") == 0) {
        cmd_skills(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "pskills") == 0) {
        Character *ch = &session->character;
        int is_rcc = (ch->occ && strcasestr(ch->occ, "Dragon Hatchling") != NULL);
        int w = FRAME_WIDTH;
        char buf[128];
        send_to_player(session, "\r\n");
        frame_top(session, w);
        frame_title(session, "PRIMARY SKILLS (O.C.C.)", w);
        frame_sep(session, w);
        if (is_rcc) {
            frame_line(session, "Dragon RCC uses racial abilities", w);
            frame_line(session, "instead of OCC primary skills.", w);
        } else {
            int limit = ch->num_skills < 5 ? ch->num_skills : 5;
            for (int i = 0; i < limit; i++) {
                const char *sname = skill_get_name(ch->skills[i].skill_id);
                snprintf(buf, sizeof(buf), "%-32s %3d%%", sname, ch->skills[i].percentage);
                frame_line(session, buf, w);
            }
            if (limit == 0) frame_line(session, "No primary skills assigned.", w);
        }
        frame_bottom(session, w);
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "sskills") == 0) {
        Character *ch = &session->character;
        int is_rcc = (ch->occ && strcasestr(ch->occ, "Dragon Hatchling") != NULL);
        int start_idx = is_rcc ? 0 : 5;
        int w = FRAME_WIDTH;
        char buf[128];
        send_to_player(session, "\r\n");
        frame_top(session, w);
        frame_title(session, "SECONDARY SKILLS (Player-chosen)", w);
        frame_sep(session, w);
        if (ch->num_skills <= start_idx) {
            frame_line(session, "No secondary skills selected.", w);
        } else {
            for (int i = start_idx; i < ch->num_skills; i++) {
                const char *sname = skill_get_name(ch->skills[i].skill_id);
                snprintf(buf, sizeof(buf), "%-32s %3d%%", sname, ch->skills[i].percentage);
                frame_line(session, buf, w);
            }
        }
        frame_bottom(session, w);
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "attack") == 0 || strcmp(cmd, "kill") == 0) {
        cmd_attack(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "strike") == 0) {
        cmd_strike(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "shoot") == 0) {
        cmd_shoot(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "dodge") == 0) {
        cmd_dodge(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "flee") == 0) {
        cmd_flee(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    /* STOP - Disengage from combat */
    if (strcmp(cmd, "stop") == 0) {
        if (!session->in_combat) {
            send_to_player(session, "You are not in combat.\n");
        } else {
            combat_disengage(session);
            send_to_player(session, "You stop fighting.\n");
        }
        result.type = VALUE_NULL;
        return result;
    }

    /* ASSIST - Join combat targeting their target */
    if (strcmp(cmd, "assist") == 0) {
        if (!args || !*args) {
            send_to_player(session, "Assist who?\n");
            result.type = VALUE_NULL;
            return result;
        }
        PlayerSession *ally = find_player_by_name(args);
        if (!ally) {
            send_to_player(session, "Player '%s' not found.\n", args);
        } else if (!ally->in_combat || !ally->combat_target) {
            send_to_player(session, "%s is not in combat.\n", ally->username);
        } else {
            send_to_player(session, "You rush to assist %s!\n", ally->username);
            combat_engage(session, ally->combat_target);
        }
        result.type = VALUE_NULL;
        return result;
    }

    /* AUTODODGE - Toggle auto-dodge */
    if (strcmp(cmd, "autododge") == 0) {
        session->character.auto_dodge_enabled = !session->character.auto_dodge_enabled;
        send_to_player(session, "Auto-dodge is now %s.\n",
                       session->character.auto_dodge_enabled ? "ON" : "OFF");
        result.type = VALUE_NULL;
        return result;
    }

    /* AUTOPARRY - Toggle auto-parry */
    if (strcmp(cmd, "autoparry") == 0) {
        session->character.auto_parry_enabled = !session->character.auto_parry_enabled;
        send_to_player(session, "Auto-parry is now %s.\n",
                       session->character.auto_parry_enabled ? "ON" : "OFF");
        result.type = VALUE_NULL;
        return result;
    }

    /* WIMPY - Set auto-flee threshold */
    if (strcmp(cmd, "wimpy") == 0) {
        if (!args || !*args) {
            if (session->character.wimpy_threshold > 0) {
                send_to_player(session, "Wimpy is set to %d%% HP.\n", session->character.wimpy_threshold);
            } else {
                send_to_player(session, "Wimpy is disabled. Usage: wimpy <percent> (0 to disable)\n");
            }
        } else {
            int pct = atoi(args);
            if (pct < 0) pct = 0;
            if (pct > 90) pct = 90;
            session->character.wimpy_threshold = pct;
            if (pct > 0) {
                send_to_player(session, "Wimpy set to %d%% HP. You will auto-flee when HP drops below %d%%.\n", pct, pct);
            } else {
                send_to_player(session, "Wimpy disabled.\n");
            }
        }
        result.type = VALUE_NULL;
        return result;
    }

    /* REST - Sit down and regenerate */
    if (strcmp(cmd, "rest") == 0) {
        if (session->in_combat) {
            send_to_player(session, "You can't rest while in combat!\n");
        } else if (session->is_resting) {
            send_to_player(session, "You are already resting.\n");
        } else {
            session->is_resting = 1;
            send_to_player(session, "You sit down and rest.\n");
            if (session->current_room) {
                char msg[256];
                snprintf(msg, sizeof(msg), "%s sits down and rests.\n", session->username);
                room_broadcast(session->current_room, msg, session);
            }
        }
        result.type = VALUE_NULL;
        return result;
    }

    /* WAKE / STAND - Stand up from resting */
    if (strcmp(cmd, "wake") == 0 || strcmp(cmd, "stand") == 0) {
        if (!session->is_resting) {
            send_to_player(session, "You are already standing.\n");
        } else {
            session->is_resting = 0;
            send_to_player(session, "You stand up.\n");
            if (session->current_room) {
                char msg[256];
                snprintf(msg, sizeof(msg), "%s stands up.\n", session->username);
                room_broadcast(session->current_room, msg, session);
            }
        }
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "inventory") == 0 || strcmp(cmd, "i") == 0) {
        cmd_inventory(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "equip") == 0 || strcmp(cmd, "eq") == 0 || strcmp(cmd, "wield") == 0 || strcmp(cmd, "wear") == 0) {
        cmd_equip(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "unequip") == 0 || strcmp(cmd, "uneq") == 0 || strcmp(cmd, "remove") == 0) {
        cmd_unequip(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "worn") == 0 || strcmp(cmd, "equipment") == 0 || strcmp(cmd, "eq") == 0) {
        cmd_worn(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "get") == 0 || strcmp(cmd, "take") == 0) {
        cmd_get(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "drop") == 0) {
        cmd_drop(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    /* Psionics commands (Phase 5) */
    if (strcmp(cmd, "use") == 0) {
        cmd_use_power(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "powers") == 0 || strcmp(cmd, "abilities") == 0 ||
        strcmp(cmd, "psionics") == 0) {
        cmd_powers(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "isp") == 0 || strcmp(cmd, "inner_strength") == 0) {
        cmd_isp(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    /* Magic commands (Phase 5) */
    if (strcmp(cmd, "cast") == 0) {
        cmd_cast(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "spells") == 0 || strcmp(cmd, "grimoire") == 0) {
        cmd_spells(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "ppe") == 0 || strcmp(cmd, "ppp") == 0) {
        cmd_ppe(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "meditate") == 0) {
        cmd_meditate(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "say") == 0) {
        if (args && *args) {
            Character *speaker_ch = &session->character;
            const char *lang = speaker_ch->current_language;
            if (!lang) lang = "american";

            /* Message to speaker */
            char self_msg[BUFFER_SIZE];
            snprintf(self_msg, sizeof(self_msg), "You say, \"%s\" in %s.\r\n", args, lang);

            /* Send to room occupants with language check */
            if (session->current_room) {
                Room *room = session->current_room;
                for (int i = 0; i < room->num_players; i++) {
                    PlayerSession *listener = room->players[i];
                    if (!listener || listener == session) continue;

                    /* Determine display name: use username if introduced, else race */
                    Character *lch = &listener->character;
                    const char *speaker_name = NULL;
                    for (int j = 0; j < lch->introduced_count; j++) {
                        if (lch->introduced_to[j] &&
                            strcasecmp(lch->introduced_to[j], session->username) == 0) {
                            speaker_name = session->username;
                            break;
                        }
                    }
                    if (!speaker_name) {
                        speaker_name = speaker_ch->race ? speaker_ch->race : "Someone";
                        /* Prepend "A " for race description */
                        char race_desc[128];
                        snprintf(race_desc, sizeof(race_desc), "A %s", speaker_name);

                        /* Check if listener knows the language */
                        int knows_lang = 0;
                        for (int k = 0; k < lch->num_languages; k++) {
                            if (lch->languages[k] && strcasecmp(lch->languages[k], lang) == 0) {
                                knows_lang = 1;
                                break;
                            }
                        }

                        char listener_msg[BUFFER_SIZE];
                        if (knows_lang) {
                            snprintf(listener_msg, sizeof(listener_msg),
                                "%s says, \"%s\" in %s.\r\n", race_desc, args, lang);
                        } else {
                            snprintf(listener_msg, sizeof(listener_msg),
                                "%s says something unintelligible in %s.\r\n", race_desc, lang);
                        }
                        send_to_player(listener, "%s", listener_msg);
                        continue;
                    }

                    /* Listener knows speaker by name */
                    int knows_lang = 0;
                    for (int k = 0; k < lch->num_languages; k++) {
                        if (lch->languages[k] && strcasecmp(lch->languages[k], lang) == 0) {
                            knows_lang = 1;
                            break;
                        }
                    }

                    char listener_msg[BUFFER_SIZE];
                    if (knows_lang) {
                        snprintf(listener_msg, sizeof(listener_msg),
                            "%s says, \"%s\" in %s.\r\n", speaker_name, args, lang);
                    } else {
                        snprintf(listener_msg, sizeof(listener_msg),
                            "%s says something unintelligible in %s.\r\n", speaker_name, lang);
                    }
                    send_to_player(listener, "%s", listener_msg);
                }
            }

            return vm_value_create_string(self_msg);
        } else {
            return vm_value_create_string("Say what?\r\n");
        }
    }
    
    if (strcmp(cmd, "emote") == 0) {
        if (args && *args) {
            char msg[BUFFER_SIZE];
            snprintf(msg, sizeof(msg), "%s %s\r\n", session->username, args);
            broadcast_message(msg, session);
            return vm_value_create_string(msg);
        } else {
            return vm_value_create_string("Emote what?\r\n");
        }
    }
    
    /* Priority gameplay commands */
    if (strcmp(cmd, "tell") == 0) {
        cmd_tell(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "chat") == 0) {
        cmd_chat(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "whisper") == 0) {
        cmd_whisper(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "shout") == 0) {
        cmd_shout(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "exits") == 0) {
        cmd_exits(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "examine") == 0 || strcmp(cmd, "exam") == 0) {
        cmd_examine(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "give") == 0) {
        cmd_give_item(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    if (strcmp(cmd, "who") == 0) {
        int w = FRAME_WIDTH;
        int count = 0;
        char buf[128];
        send_to_player(session, "\r\n");
        frame_top(session, w);
        frame_title(session, "PLAYERS ONLINE", w);
        frame_sep(session, w);

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (sessions[i] && sessions[i]->state == STATE_PLAYING) {
                if (sessions[i]->is_invisible && session->privilege_level < 1)
                    continue;
                time_t idle = time(NULL) - sessions[i]->last_activity;
                const char *priv = (sessions[i]->privilege_level == 2) ? " [Admin]" :
                                  (sessions[i]->privilege_level == 1) ? " [Wiz]" : "";
                const char *invis_tag = sessions[i]->is_invisible ? " (invis)" : "";
                const char *title_str = sessions[i]->title[0] ? sessions[i]->title : "";
                if (title_str[0]) {
                    snprintf(buf, sizeof(buf), "%-16s%s%s %s  (%lds idle)",
                            sessions[i]->username, priv, invis_tag, title_str, idle);
                } else {
                    snprintf(buf, sizeof(buf), "%-16s%s%s  (%lds idle)",
                            sessions[i]->username, priv, invis_tag, idle);
                }
                frame_line(session, buf, w);
                count++;
            }
        }

        frame_sep(session, w);
        snprintf(buf, sizeof(buf), "Total: %d player%s", count, count == 1 ? "" : "s");
        frame_line(session, buf, w);
        frame_bottom(session, w);
        result.type = VALUE_NULL;
        return result;
    }

    if (strcmp(cmd, "stats") == 0) {
        /* Use the chargen_display_stats which now has frames */
        cmd_stats(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }
    
    /* Movement commands */
    const char *directions[] = {"north", "south", "east", "west", "up", "down", 
                               "n", "s", "e", "w", "u", "d", NULL};
    for (int i = 0; directions[i]; i++) {
        if (strcmp(cmd, directions[i]) == 0) {
            return vm_value_create_string("You can't go that way.\r\n");
        }
    }
    
    /* Admin commands */
    if (strcmp(cmd, "promote") == 0) {
        if (session->privilege_level < 2) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        
        if (!args || *args == '\0') {
            return vm_value_create_string(
                "Usage: promote <player> <level>\r\n"
                "Levels: 0=player, 1=wizard, 2=admin\r\n");
        }
        
        char target_name[64];
        int new_level;
        if (sscanf(args, "%63s %d", target_name, &new_level) != 2) {
            return vm_value_create_string(
                "Usage: promote <player> <level>\r\n"
                "Levels: 0=player, 1=wizard, 2=admin\r\n");
        }
        
        if (new_level < 0 || new_level > 2) {
            return vm_value_create_string("Invalid level. Use 0 (player), 1 (wizard), or 2 (admin).\r\n");
        }
        
        // Find and promote player
        int promoted = 0;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (sessions[i] && sessions[i]->state == STATE_PLAYING &&
                strcmp(sessions[i]->username, target_name) == 0) {
                sessions[i]->privilege_level = new_level;
                promoted = 1;
                break;
            }
        }
        
        if (promoted) {
            char msg[256];
            const char *level_name = (new_level == 2) ? "Admin" : 
                                     (new_level == 1) ? "Wizard" : "Player";
            snprintf(msg, sizeof(msg), 
                    "Promoted %s to %s (level %d).\r\n", 
                    target_name, level_name, new_level);
            return vm_value_create_string(msg);
        } else {
            return vm_value_create_string("Player not found.\r\n");
        }
    }
    
    if (strcmp(cmd, "users") == 0) {
        if (session->privilege_level < 2) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        
        char msg[BUFFER_SIZE];
        strcpy(msg, "Connected users:\r\n");
        strcat(msg, "Name            Privilege      Idle\r\n");
        strcat(msg, "----------------------------------------------\r\n");
        
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (sessions[i] && sessions[i]->state == STATE_PLAYING) {
                const char *priv_name = (sessions[i]->privilege_level == 2) ? "Admin" :
                                       (sessions[i]->privilege_level == 1) ? "Wizard" : "Player";
                time_t idle = time(NULL) - sessions[i]->last_activity;
                char line[128];
                snprintf(line, sizeof(line), "%-15s %-14s %ld sec\r\n",
                        sessions[i]->username, priv_name, idle);
                strcat(msg, line);
            }
        }
        
        return vm_value_create_string(msg);
    }
    
    /* Wizard commands */
    if (strcmp(cmd, "goto") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }

        if (!args || *args == '\0') {
            return vm_value_create_string(
                "Usage: goto <room_id>  or  goto /domains/path/to/room\r\n"
                "Bootstrap rooms: 0=Void, 1=Chi-Town Plaza, 2=Coalition HQ, 3=Merchant District\r\n"
                "LPC rooms: goto /domains/staff_castle/room/courtyard\r\n");
        }

        Room *target_room = NULL;

        /* If argument starts with / it's an LPC path */
        if (args[0] == '/') {
            target_room = room_get_by_path(args);
            if (!target_room) {
                send_to_player(session, "Could not load LPC room '%s'.\r\n", args);
                result.type = VALUE_NULL;
                return result;
            }
        } else {
            int room_id = atoi(args);
            target_room = room_get_by_id(room_id);
        }

        if (!target_room) {
            return vm_value_create_string("Invalid room ID.\r\n");
        }
        
        /* Remove from current room */
        if (session->current_room) {
            room_remove_player(session->current_room, session);
            
            char leave_msg[256];
            snprintf(leave_msg, sizeof(leave_msg), 
                    "%s vanishes in a puff of smoke.\r\n", session->username);
            room_broadcast(session->current_room, leave_msg, NULL);
        }
        
        /* Add to target room */
        session->current_room = target_room;
        room_add_player(target_room, session);
        
        char arrive_msg[256];
        snprintf(arrive_msg, sizeof(arrive_msg), 
                "%s appears in a puff of smoke.\r\n", session->username);
        room_broadcast(target_room, arrive_msg, session);
        
        /* Show new room */
        cmd_look(session, "");
        
        result.type = VALUE_NULL;
        return result;
    }
    
    /* Clone command: creates objects from LPC files or item templates.
     * Until full LPC command dispatch is wired up, this C handler reads
     * LPC object files, extracts properties, and creates C Items that
     * integrate with the existing inventory system. */
    if (strcmp(cmd, "clone") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("Error: Insufficient privileges. Wizard access required.\r\n");
        }
        if (!args || *args == '\0') {
            return vm_value_create_string(
                "Usage: clone <object_path>\r\n"
                "Example: clone /lib/objects/weapons/sword\r\n");
        }

        /* First try item template name lookup (e.g. "Steel Sword") */
        Item *tmpl = item_find_by_name(args);
        if (tmpl) {
            Item *new_item = item_clone(tmpl);
            if (new_item && inventory_add(&session->character.inventory, new_item)) {
                char msg[512];
                snprintf(msg, sizeof(msg),
                    "You clone %s.\r\nIt has been added to your inventory.\r\n",
                    new_item->name);
                return vm_value_create_string(msg);
            }
            if (new_item) item_free(new_item);
            return vm_value_create_string("Error: Could not add item to inventory (weight limit?).\r\n");
        }

        /* Try LPC file path (e.g. /lib/objects/weapons/sword) */
        char fs_path[512];
        if (!resolve_lpc_path(args, fs_path, sizeof(fs_path))) {
            char msg[512];
            snprintf(msg, sizeof(msg),
                "Error: Failed to clone object: %s\r\n"
                "File not found. Check the path and try again.\r\n", args);
            return vm_value_create_string(msg);
        }

        Item *new_item = item_create_from_lpc(fs_path);
        if (!new_item) {
            char msg[512];
            snprintf(msg, sizeof(msg),
                "Error: Failed to parse LPC object: %s\r\n", fs_path);
            return vm_value_create_string(msg);
        }

        if (!inventory_add(&session->character.inventory, new_item)) {
            item_free(new_item);
            return vm_value_create_string("Error: Could not add item to inventory (weight limit?).\r\n");
        }

        /* Extract short desc for the message */
        char msg[512];
        snprintf(msg, sizeof(msg),
            "You clone %s.\r\nIt has been added to your inventory.\r\n",
            new_item->name);
        return vm_value_create_string(msg);
    }

    /* ====================================================================
     * WIZARD COMMANDS - Character Management (Phase 1)
     * ==================================================================== */

    /* SET - Set player attributes (THE most critical wizard command) */
    if (strcmp(cmd, "set") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string(
                "Usage: set <player> <field> <value>\r\n"
                "Fields: occ, race, level, hp, max_hp, sdc, max_sdc, mdc, max_mdc,\r\n"
                "        isp, max_isp, ppe, max_ppe, xp,\r\n"
                "        stat_iq, stat_me, stat_ma, stat_ps, stat_pp, stat_pe, stat_pb, stat_spd\r\n");
        }

        char target_name[64], field[64], value_str[256];
        if (sscanf(args, "%63s %63s %255[^\n]", target_name, field, value_str) < 3) {
            return vm_value_create_string("Usage: set <player> <field> <value>\r\n");
        }

        PlayerSession *target = find_player_by_name(target_name);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }

        Character *ch = &target->character;
        char response[512];

        if (strcmp(field, "occ") == 0) {
            if (ch->occ) free(ch->occ);
            ch->occ = strdup(value_str);
            load_occ_data(value_str, ch);
            apply_race_and_occ(target);
            snprintf(response, sizeof(response),
                "Set %s's O.C.C. to '%s' and applied bonuses.\r\n",
                target_name, value_str);
            send_to_player(target, "Your O.C.C. has been set to: %s\r\n", value_str);
        } else if (strcmp(field, "race") == 0) {
            if (ch->race) free(ch->race);
            ch->race = strdup(value_str);
            load_race_data(value_str, ch);
            apply_race_and_occ(target);
            snprintf(response, sizeof(response),
                "Set %s's race to '%s' and applied bonuses.\r\n",
                target_name, value_str);
            send_to_player(target, "Your race has been set to: %s\r\n", value_str);
        } else if (strcmp(field, "level") == 0) {
            ch->level = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's level to %d.\r\n",
                    target_name, ch->level);
            send_to_player(target, "Your level has been set to %d.\r\n", ch->level);
        } else if (strcmp(field, "hp") == 0) {
            ch->hp = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's HP to %d.\r\n",
                    target_name, ch->hp);
        } else if (strcmp(field, "max_hp") == 0) {
            ch->max_hp = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's max HP to %d.\r\n",
                    target_name, ch->max_hp);
        } else if (strcmp(field, "sdc") == 0) {
            ch->sdc = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's SDC to %d.\r\n",
                    target_name, ch->sdc);
        } else if (strcmp(field, "max_sdc") == 0) {
            ch->max_sdc = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's max SDC to %d.\r\n",
                    target_name, ch->max_sdc);
        } else if (strcmp(field, "mdc") == 0) {
            ch->mdc = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's MDC to %d.\r\n",
                    target_name, ch->mdc);
        } else if (strcmp(field, "max_mdc") == 0) {
            ch->max_mdc = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's max MDC to %d.\r\n",
                    target_name, ch->max_mdc);
        } else if (strcmp(field, "isp") == 0) {
            ch->isp = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's ISP to %d.\r\n",
                    target_name, ch->isp);
        } else if (strcmp(field, "max_isp") == 0) {
            ch->max_isp = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's max ISP to %d.\r\n",
                    target_name, ch->max_isp);
        } else if (strcmp(field, "ppe") == 0) {
            ch->ppe = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's PPE to %d.\r\n",
                    target_name, ch->ppe);
        } else if (strcmp(field, "max_ppe") == 0) {
            ch->max_ppe = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's max PPE to %d.\r\n",
                    target_name, ch->max_ppe);
        } else if (strcmp(field, "xp") == 0) {
            ch->xp = atoi(value_str);
            check_and_apply_level_up(target);
            snprintf(response, sizeof(response), "Set %s's XP to %d.\r\n",
                    target_name, ch->xp);
        } else if (strcmp(field, "stat_iq") == 0) {
            ch->stats.iq = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's IQ to %d.\r\n",
                    target_name, ch->stats.iq);
        } else if (strcmp(field, "stat_me") == 0) {
            ch->stats.me = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's ME to %d.\r\n",
                    target_name, ch->stats.me);
        } else if (strcmp(field, "stat_ma") == 0) {
            ch->stats.ma = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's MA to %d.\r\n",
                    target_name, ch->stats.ma);
        } else if (strcmp(field, "stat_ps") == 0) {
            ch->stats.ps = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's PS to %d.\r\n",
                    target_name, ch->stats.ps);
        } else if (strcmp(field, "stat_pp") == 0) {
            ch->stats.pp = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's PP to %d.\r\n",
                    target_name, ch->stats.pp);
        } else if (strcmp(field, "stat_pe") == 0) {
            ch->stats.pe = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's PE to %d.\r\n",
                    target_name, ch->stats.pe);
        } else if (strcmp(field, "stat_pb") == 0) {
            ch->stats.pb = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's PB to %d.\r\n",
                    target_name, ch->stats.pb);
        } else if (strcmp(field, "stat_spd") == 0) {
            ch->stats.spd = atoi(value_str);
            snprintf(response, sizeof(response), "Set %s's SPD to %d.\r\n",
                    target_name, ch->stats.spd);
        } else {
            snprintf(response, sizeof(response), "Unknown field: %s\r\n", field);
        }

        return vm_value_create_string(response);
    }

    /* HEAL - Restore player's HP/SDC/MDC/ISP/PPE */
    if (strcmp(cmd, "heal") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: heal <player> [amount]\r\n");
        }

        char target_name[64];
        int amount = 0;
        sscanf(args, "%63s %d", target_name, &amount);

        PlayerSession *target = find_player_by_name(target_name);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }

        Character *ch = &target->character;
        if (amount > 0) {
            ch->hp = (ch->hp + amount > ch->max_hp) ? ch->max_hp : ch->hp + amount;
            ch->sdc = (ch->sdc + amount > ch->max_sdc) ? ch->max_sdc : ch->sdc + amount;
        } else {
            ch->hp = ch->max_hp;
            ch->sdc = ch->max_sdc;
            ch->mdc = ch->max_mdc;
            ch->isp = ch->max_isp;
            ch->ppe = ch->max_ppe;
        }

        send_to_player(target, "You feel a warm healing energy wash over you!\r\n");
        char response[256];
        snprintf(response, sizeof(response), "Healed %s. HP: %d/%d SDC: %d/%d\r\n",
                target_name, ch->hp, ch->max_hp, ch->sdc, ch->max_sdc);
        return vm_value_create_string(response);
    }

    /* SLAY - Instant kill a target */
    if (strcmp(cmd, "slay") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: slay <player>\r\n");
        }

        PlayerSession *target = find_player_by_name(args);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }

        target->character.hp = 0;
        target->character.sdc = 0;

        /* End combat if target is in one */
        CombatRound *combat = combat_get_active(target);
        if (combat) {
            combat_end(combat);
        }

        send_to_player(target, "\r\nYou have been slain by %s!\r\n",
                       session->username);

        if (session->current_room) {
            char msg[256];
            snprintf(msg, sizeof(msg), "%s has been slain by %s!\r\n",
                    target->username, session->username);
            room_broadcast(session->current_room, msg, session);
        }

        char response[256];
        snprintf(response, sizeof(response), "You slay %s.\r\n", target->username);
        return vm_value_create_string(response);
    }

    /* AWARD - Give experience points to a player */
    if (strcmp(cmd, "award") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: award <player> <xp_amount>\r\n");
        }

        char target_name[64];
        int xp_amount = 0;
        if (sscanf(args, "%63s %d", target_name, &xp_amount) != 2 || xp_amount <= 0) {
            return vm_value_create_string("Usage: award <player> <xp_amount>\r\n");
        }

        PlayerSession *target = find_player_by_name(target_name);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }

        target->character.xp += xp_amount;
        check_and_apply_level_up(target);

        send_to_player(target, "You have been awarded %d experience points! (Total: %d XP)\r\n",
                       xp_amount, target->character.xp);
        char response[256];
        snprintf(response, sizeof(response), "Awarded %d XP to %s. (Total: %d XP, Level: %d)\r\n",
                xp_amount, target_name, target->character.xp, target->character.level);
        return vm_value_create_string(response);
    }

    /* ====================================================================
     * WIZARD COMMANDS - Teleportation & Room Control (Phase 2)
     * ==================================================================== */

    /* TRANS / SUMMON - Teleport a player to your room */
    if (strcmp(cmd, "trans") == 0 || strcmp(cmd, "summon") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: trans <player>\r\n");
        }
        if (!session->current_room) {
            return vm_value_create_string("You are nowhere.\r\n");
        }

        PlayerSession *target = find_player_by_name(args);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }
        if (target == session) {
            return vm_value_create_string("You can't summon yourself.\r\n");
        }

        /* Remove from old room */
        if (target->current_room) {
            char leave_msg[256];
            snprintf(leave_msg, sizeof(leave_msg),
                    "%s vanishes in a flash of light.\r\n", target->username);
            room_broadcast(target->current_room, leave_msg, target);
            room_remove_player(target->current_room, target);
        }

        /* Add to wizard's room */
        target->current_room = session->current_room;
        room_add_player(session->current_room, target);

        char arrive_msg[256];
        snprintf(arrive_msg, sizeof(arrive_msg),
                "%s appears in a flash of light.\r\n", target->username);
        room_broadcast(session->current_room, arrive_msg, target);

        send_to_player(target, "You have been summoned by %s!\r\n", session->username);
        cmd_look(target, "");

        char response[256];
        snprintf(response, sizeof(response), "You summon %s to your location.\r\n",
                target->username);
        return vm_value_create_string(response);
    }

    /* PEACE - End all combat in the current room */
    if (strcmp(cmd, "peace") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!session->current_room) {
            return vm_value_create_string("You are nowhere.\r\n");
        }

        Room *room = session->current_room;
        int ended = 0;
        for (int i = 0; i < room->num_players; i++) {
            if (room->players[i]) {
                CombatRound *combat = combat_get_active(room->players[i]);
                if (combat) {
                    combat_end(combat);
                    ended++;
                }
            }
        }

        if (ended > 0) {
            room_broadcast(session->current_room,
                "Peace has been restored by divine intervention.\r\n", NULL);
            return vm_value_create_string("Combat ended.\r\n");
        }
        return vm_value_create_string("There is no combat in this room.\r\n");
    }

    /* RESET - Reset the current room */
    if (strcmp(cmd, "reset") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!session->current_room) {
            return vm_value_create_string("You are nowhere.\r\n");
        }

        /* Free and clear room items */
        Room *room = session->current_room;
        Item *ri2 = room->items;
        while (ri2) {
            Item *next = ri2->next;
            item_free(ri2);
            ri2 = next;
        }
        room->items = NULL;

        room_broadcast(room, "The room shimmers and resets.\r\n", NULL);
        return vm_value_create_string("Room reset.\r\n");
    }

    /* ====================================================================
     * WIZARD COMMANDS - Player Management (Phase 3)
     * ==================================================================== */

    /* KICK - Force disconnect a player */
    if (strcmp(cmd, "kick") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: kick <player>\r\n");
        }

        PlayerSession *target = find_player_by_name(args);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }
        if (target == session) {
            return vm_value_create_string("You can't kick yourself.\r\n");
        }
        if (target->privilege_level >= session->privilege_level) {
            return vm_value_create_string("You can't kick someone of equal or higher privilege.\r\n");
        }

        /* Save first */
        save_character(target);

        send_to_player(target, "\r\nYou have been kicked from the game by %s.\r\n",
                       session->username);

        char kick_msg[256];
        snprintf(kick_msg, sizeof(kick_msg), "%s has been kicked from the game.\r\n",
                target->username);
        broadcast_message(kick_msg, target);

        /* Remove from room */
        if (target->current_room) {
            room_remove_player(target->current_room, target);
        }

        target->state = STATE_DISCONNECTING;

        char response[256];
        snprintf(response, sizeof(response), "Kicked %s from the game.\r\n",
                target->username);
        return vm_value_create_string(response);
    }

    /* FINGER - Show detailed player info */
    if (strcmp(cmd, "finger") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: finger <player>\r\n");
        }

        PlayerSession *target = find_player_by_name(args);
        if (!target) {
            return vm_value_create_string("Player not found or not online.\r\n");
        }

        Character *ch = &target->character;
        char info[2048];
        time_t idle = time(NULL) - target->last_activity;
        time_t online = time(NULL) - target->connect_time;

        snprintf(info, sizeof(info),
            "=== FINGER: %s ===\r\n"
            "  Race:    %s\r\n"
            "  O.C.C.:  %s\r\n"
            "  Level:   %d\r\n"
            "  XP:      %d\r\n"
            "  HP:      %d/%d\r\n"
            "  SDC:     %d/%d\r\n"
            "  MDC:     %d/%d\r\n"
            "  ISP:     %d/%d\r\n"
            "  PPE:     %d/%d\r\n"
            "  Stats:   IQ:%d ME:%d MA:%d PS:%d PP:%d PE:%d PB:%d SPD:%d\r\n"
            "  Priv:    %d (%s)\r\n"
            "  Room:    %s (ID: %d)\r\n"
            "  IP:      %s\r\n"
            "  Idle:    %ld seconds\r\n"
            "  Online:  %ld seconds\r\n"
            "==================\r\n",
            target->username,
            ch->race ? ch->race : "None",
            ch->occ ? ch->occ : "None",
            ch->level, ch->xp,
            ch->hp, ch->max_hp,
            ch->sdc, ch->max_sdc,
            ch->mdc, ch->max_mdc,
            ch->isp, ch->max_isp,
            ch->ppe, ch->max_ppe,
            ch->stats.iq, ch->stats.me, ch->stats.ma, ch->stats.ps,
            ch->stats.pp, ch->stats.pe, ch->stats.pb, ch->stats.spd,
            target->privilege_level,
            target->privilege_level == 2 ? "Admin" :
            target->privilege_level == 1 ? "Wizard" : "Player",
            target->current_room ? target->current_room->name : "Nowhere",
            target->current_room ? target->current_room->id : -1,
            target->ip_address,
            idle, online);

        return vm_value_create_string(info);
    }

    /* WHEREIS - Show where a player is */
    if (strcmp(cmd, "whereis") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: whereis <player>\r\n");
        }

        PlayerSession *target = find_player_by_name(args);
        if (!target) {
            return vm_value_create_string("Player not found or not online.\r\n");
        }

        char response[256];
        if (target->current_room) {
            snprintf(response, sizeof(response), "%s is in %s (Room ID: %d)\r\n",
                    target->username, target->current_room->name, target->current_room->id);
        } else {
            snprintf(response, sizeof(response), "%s is nowhere (no room assigned)\r\n",
                    target->username);
        }
        return vm_value_create_string(response);
    }

    /* SCAN - Show contents of adjacent rooms (available to all players) */
    if (strcmp(cmd, "scan") == 0) {
        if (!session->current_room) {
            return vm_value_create_string("You are nowhere.\r\n");
        }

        Room *room = session->current_room;
        char scan_buf[2048];
        strcpy(scan_buf, "You scan the area...\r\n\r\n");

        struct { const char *dir; int id; } dirs[] = {
            {"North", room->exits.north},
            {"South", room->exits.south},
            {"East", room->exits.east},
            {"West", room->exits.west},
            {"Up", room->exits.up},
            {"Down", room->exits.down},
        };

        for (int d = 0; d < 6; d++) {
            if (dirs[d].id < 0) continue;
            Room *adj = room_get_by_id(dirs[d].id);
            if (!adj) continue;

            char line[256];
            snprintf(line, sizeof(line), "  %s: %s", dirs[d].dir, adj->name);
            strcat(scan_buf, line);

            if (adj->num_players > 0) {
                strcat(scan_buf, " [");
                for (int p = 0; p < adj->num_players; p++) {
                    if (adj->players[p] && adj->players[p]->username[0]) {
                        if (adj->players[p]->is_invisible && session->privilege_level < 1)
                            continue;
                        if (p > 0) strcat(scan_buf, ", ");
                        strcat(scan_buf, adj->players[p]->username);
                    }
                }
                strcat(scan_buf, "]");
            }
            strcat(scan_buf, "\r\n");
        }

        return vm_value_create_string(scan_buf);
    }

    /* ====================================================================
     * WIZARD COMMANDS - Utility (Phase 4)
     * ==================================================================== */

    /* SNOOP - See everything a player sees */
    if (strcmp(cmd, "snoop") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }

        /* No args = stop snooping */
        if (!args || !*args) {
            if (session->snooping) {
                session->snooping->snooped_by = NULL;
                char response[256];
                snprintf(response, sizeof(response), "You stop snooping %s.\r\n",
                        session->snooping->username);
                session->snooping = NULL;
                return vm_value_create_string(response);
            }
            return vm_value_create_string("You are not snooping anyone.\r\n");
        }

        PlayerSession *target = find_player_by_name(args);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }
        if (target == session) {
            return vm_value_create_string("You can't snoop yourself.\r\n");
        }
        if (target->snooped_by) {
            return vm_value_create_string("That player is already being snooped.\r\n");
        }

        /* Stop current snoop if any */
        if (session->snooping) {
            session->snooping->snooped_by = NULL;
        }

        session->snooping = target;
        target->snooped_by = session;

        char response[256];
        snprintf(response, sizeof(response), "You begin snooping %s.\r\n",
                target->username);
        return vm_value_create_string(response);
    }

    /* INVIS - Toggle wizard invisibility */
    if (strcmp(cmd, "invis") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }

        session->is_invisible = !session->is_invisible;
        if (session->is_invisible) {
            return vm_value_create_string("You fade from view. You are now invisible.\r\n");
        } else {
            return vm_value_create_string("You become visible again.\r\n");
        }
    }

    /* GODMODE - Toggle damage immunity */
    if (strcmp(cmd, "godmode") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }

        session->is_godmode = !session->is_godmode;
        if (session->is_godmode) {
            return vm_value_create_string("God mode ENABLED. You are immune to all damage.\r\n");
        } else {
            return vm_value_create_string("God mode DISABLED. You are mortal once more.\r\n");
        }
    }

    /* FORCE - Force a player to execute a command (admin only) */
    if (strcmp(cmd, "force") == 0) {
        if (session->privilege_level < 2) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: force <player> <command>\r\n");
        }

        char target_name[64];
        char forced_cmd[512];
        if (sscanf(args, "%63s %511[^\n]", target_name, forced_cmd) != 2) {
            return vm_value_create_string("Usage: force <player> <command>\r\n");
        }

        PlayerSession *target = find_player_by_name(target_name);
        if (!target) {
            return vm_value_create_string("Player not found.\r\n");
        }

        send_to_player(target, "%s forces you to: %s\r\n", session->username, forced_cmd);
        execute_command(target, forced_cmd);

        char response[256];
        snprintf(response, sizeof(response), "You force %s to: %s\r\n",
                target_name, forced_cmd);
        return vm_value_create_string(response);
    }

    /* ====================================================================
     * WIZARD COMMANDS - Object Management (Phase 5)
     * ==================================================================== */

    /* DESTRUCT - Remove an item from room or inventory by name */
    if (strcmp(cmd, "destruct") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: destruct <item_name>\r\n");
        }

        /* Try inventory first */
        Item *item = inventory_remove(&session->character.inventory, args);
        if (item) {
            char response[256];
            snprintf(response, sizeof(response), "Destructed '%s' from your inventory.\r\n",
                    item->name);
            item_free(item);
            return vm_value_create_string(response);
        }

        /* Try room items */
        if (session->current_room) {
            Item *room_item = room_find_item(session->current_room, args);
            if (room_item) {
                room_remove_item(session->current_room, room_item);
                item_free(room_item);
                char response[256];
                snprintf(response, sizeof(response), "Destructed '%s' from the room.\r\n", args);
                return vm_value_create_string(response);
            }
        }

        return vm_value_create_string("Item not found in your inventory or this room.\r\n");
    }

    /* CLEAN - Remove all items from current room */
    if (strcmp(cmd, "clean") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!session->current_room) {
            return vm_value_create_string("You are nowhere.\r\n");
        }

        /* Free and clear all room items */
        Item *ri = session->current_room->items;
        while (ri) {
            Item *next = ri->next;
            item_free(ri);
            ri = next;
        }
        session->current_room->items = NULL;
        room_broadcast(session->current_room,
            "A magical wind sweeps through, clearing the room of debris.\r\n", NULL);
        return vm_value_create_string("Room cleaned.\r\n");
    }

    /* EVAL - Execute LPC code inline (wizard tool) */
    if (strcmp(cmd, "eval") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: eval <lpc_code>\r\n"
                "Example: eval return 2 + 2;\r\n"
                "Example: eval return \"hello\";\r\n");
        }

        /* Wrap the code in a function so the compiler can handle it */
        char source[2048];
        snprintf(source, sizeof(source),
            "mixed __eval__() { %s }", args);

        Program *prog = compiler_compile_string(source, "__eval__");
        if (!prog) {
            return vm_value_create_string("Eval error: compilation failed.\r\n");
        }

        if (prog->last_error != COMPILE_SUCCESS) {
            char err_msg[512];
            snprintf(err_msg, sizeof(err_msg), "Eval compile error: %s\r\n",
                    compiler_error_string(prog->last_error));
            program_free(prog);
            return vm_value_create_string(err_msg);
        }

        /* Try to find and execute the __eval__ function */
        int func_idx = program_find_function(prog, "__eval__");
        if (func_idx < 0) {
            program_free(prog);
            return vm_value_create_string("Eval error: could not find eval function.\r\n");
        }

        /* Load program into VM and execute */
        /* For safety, capture result and clean up */
        set_current_session(session);

        /* Add the function to the VM temporarily */
        VMFunction *eval_func = NULL;
        if (func_idx >= 0 && (size_t)func_idx < prog->function_count) {
            eval_func = vm_function_create(
                prog->functions[func_idx].name,
                prog->functions[func_idx].arg_count,
                prog->functions[func_idx].local_count);
            if (eval_func && prog->bytecode) {
                /* Load bytecode as instructions */
                int vm_func_idx = vm_add_function(global_vm, eval_func);
                if (vm_func_idx >= 0) {
                    vm_call_function(global_vm, vm_func_idx, 0);
                    vm_execute(global_vm);
                }
            }
        }

        set_current_session(NULL);

        /* Get result from stack if any */
        VMValue eval_result = vm_pop_value(global_vm);
        char *result_str = vm_value_to_string(eval_result);

        char response[1024];
        snprintf(response, sizeof(response), "=> %s\r\n",
                result_str ? result_str : "(null)");
        if (result_str) free(result_str);
        vm_value_free(&eval_result);
        program_free(prog);

        return vm_value_create_string(response);
    }

    /* WIZTOOL - Framed wizard command reference */
    if (strcmp(cmd, "wiztool") == 0 || strcmp(cmd, "wiz") == 0) {
        if (session->privilege_level < 1) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }

        int w = FRAME_WIDTH;
        send_to_player(session, "\r\n");
        frame_top(session, w);
        frame_title(session, "WIZARD TOOLBOX", w);

        frame_header(session, "CHARACTER MGMT", w);
        frame_line(session, "set <p> <field> <val>  - Set attribute", w);
        frame_line(session, "  fields: occ, race, level, hp, max_hp,", w);
        frame_line(session, "  sdc, max_sdc, mdc, max_mdc, isp, ppe,", w);
        frame_line(session, "  max_isp, max_ppe, xp, stat_*", w);
        frame_line(session, "heal <player> [amt]    - Restore pools", w);
        frame_line(session, "slay <player>          - Instant kill", w);
        frame_line(session, "award <player> <xp>    - Give XP", w);
        frame_line(session, "finger <player>        - Detailed info", w);

        frame_header(session, "TELEPORTATION", w);
        frame_line(session, "goto <room_id>         - Teleport self", w);
        frame_line(session, "trans/summon <player>   - Summon player", w);
        frame_line(session, "whereis <player>       - Locate player", w);

        frame_header(session, "ROOM CONTROL", w);
        frame_line(session, "peace                  - End all combat", w);
        frame_line(session, "reset                  - Reset room", w);
        frame_line(session, "clean                  - Remove items", w);

        frame_header(session, "ITEMS & OBJECTS", w);
        frame_line(session, "clone <path|name>      - Clone item", w);
        frame_line(session, "destruct <item>        - Destroy item", w);
        frame_line(session, "grant <p> <type> <n>   - Grant ability", w);
        frame_line(session, "revoke <p> <type> <n>  - Revoke ability", w);

        frame_header(session, "UTILITY", w);
        frame_line(session, "snoop [player]         - Spy on player", w);
        frame_line(session, "invis                  - Toggle invisible", w);
        frame_line(session, "godmode                - Toggle immunity", w);
        frame_line(session, "eval <lpc_code>        - Execute LPC", w);
        frame_line(session, "ls/cd/pwd/cat          - Filesystem", w);

        if (session->privilege_level >= 2) {
            frame_header(session, "ADMIN ONLY", w);
            frame_line(session, "promote <p> <level>    - Set privilege", w);
            frame_line(session, "kick <player>          - Disconnect", w);
            frame_line(session, "ban <player>           - Permanent ban", w);
            frame_line(session, "force <p> <cmd>        - Force command", w);
            frame_line(session, "broadcast <msg>        - Message all", w);
            frame_line(session, "users                  - User listing", w);
            frame_line(session, "reboot [delay]         - Restart server", w);
            frame_line(session, "shutdown [delay]       - Stop server", w);
        }

        frame_bottom(session, w);
        result.type = VALUE_NULL;
        return result;
    }

    /* ====================================================================
     * ADMIN COMMANDS (Phase 6)
     * ==================================================================== */

    /* REBOOT - Graceful server restart */
    if (strcmp(cmd, "reboot") == 0) {
        if (session->privilege_level < 2) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }

        int delay = 0;
        if (args && *args) {
            delay = atoi(args);
        }

        /* Save all players */
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (sessions[i] && sessions[i]->state == STATE_PLAYING) {
                save_character(sessions[i]);
            }
        }

        char msg[256];
        if (delay > 0) {
            snprintf(msg, sizeof(msg),
                "[SYSTEM] Server rebooting in %d seconds by %s. All characters saved.\r\n",
                delay, session->username);
        } else {
            snprintf(msg, sizeof(msg),
                "[SYSTEM] Server rebooting NOW by %s. All characters saved.\r\n",
                session->username);
        }
        broadcast_message(msg, NULL);

        fprintf(stderr, "[Server] Reboot initiated by %s (delay=%d)\n",
                session->username, delay);
        server_running = 0;
        return vm_value_create_string("Reboot initiated. All characters saved.\r\n");
    }

    /* BAN - Ban a player */
    if (strcmp(cmd, "ban") == 0) {
        if (session->privilege_level < 2) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: ban <player>\r\n");
        }

        /* Append to ban file */
        FILE *bf = fopen("lib/save/banned.txt", "a");
        if (bf) {
            fprintf(bf, "%s\n", args);
            fclose(bf);
        }

        /* Kick if online */
        PlayerSession *target = find_player_by_name(args);
        if (target) {
            save_character(target);
            send_to_player(target, "\r\nYou have been BANNED from this server.\r\n");
            if (target->current_room) {
                room_remove_player(target->current_room, target);
            }
            target->state = STATE_DISCONNECTING;
        }

        char response[256];
        snprintf(response, sizeof(response), "Banned %s. Added to lib/save/banned.txt.\r\n",
                args);
        return vm_value_create_string(response);
    }

    /* BROADCAST / WALL - Admin message to all players */
    if (strcmp(cmd, "broadcast") == 0 || strcmp(cmd, "wall") == 0) {
        if (session->privilege_level < 2) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        if (!args || !*args) {
            return vm_value_create_string("Usage: broadcast <message>\r\n");
        }

        char msg[BUFFER_SIZE];
        snprintf(msg, sizeof(msg), "\r\n[ADMIN: %s] %s\r\n",
                session->username, args);
        broadcast_message(msg, NULL);
        return vm_value_create_string("Message broadcast.\r\n");
    }

    /* ====================================================================
     * PLAYER COMMANDS (Phase 7)
     * ==================================================================== */

    /* ====================================================================
     * NEW PLAYER COMMANDS - Social/RP + UI/Settings
     * ==================================================================== */

    /* REPLY - Reply to last tell sender */
    if (strcmp(cmd, "reply") == 0) {
        if (!args || !*args) {
            return vm_value_create_string("Reply what? Usage: reply <message>\r\n");
        }
        if (!session->last_tell_from[0]) {
            return vm_value_create_string("No one has sent you a tell yet.\r\n");
        }

        PlayerSession *target = find_player_by_name(session->last_tell_from);
        if (!target) {
            char response[256];
            snprintf(response, sizeof(response), "%s is no longer online.\r\n", session->last_tell_from);
            return vm_value_create_string(response);
        }

        send_to_player(target, "\n<%s tells you> %s\n", session->username, args);
        strncpy(target->last_tell_from, session->username, sizeof(target->last_tell_from) - 1);

        char response[1024];
        snprintf(response, sizeof(response), "<You tell %s> %s\r\n", target->username, args);
        return vm_value_create_string(response);
    }

    /* PEMOTE - Possessive emote: "Bob's eyes widen" */
    if (strcmp(cmd, "pemote") == 0) {
        if (!args || !*args) {
            return vm_value_create_string("Pemote what? Usage: pemote <action>\r\n");
        }
        char msg[BUFFER_SIZE];
        snprintf(msg, sizeof(msg), "%s's %s\r\n", session->username, args);
        broadcast_message(msg, session);
        return vm_value_create_string(msg);
    }

    /* THINK - Display internal thought */
    if (strcmp(cmd, "think") == 0) {
        if (!args || !*args) {
            return vm_value_create_string("Think what?\r\n");
        }
        char msg[BUFFER_SIZE];
        snprintf(msg, sizeof(msg), "%s . o O ( %s )\r\n", session->username, args);
        if (session->current_room) {
            room_broadcast(session->current_room, msg, NULL);
        } else {
            send_to_player(session, "%s", msg);
        }
        result.type = VALUE_NULL;
        return result;
    }

    /* CONVERSE - Toggle conversation mode */
    if (strcmp(cmd, "converse") == 0) {
        session->converse_mode = !session->converse_mode;
        if (session->converse_mode) {
            return vm_value_create_string("Conversation mode ON. All input will be spoken. Type '.' to exit.\r\n");
        } else {
            return vm_value_create_string("Conversation mode OFF.\r\n");
        }
    }

    /* INTRODUCE / GREET - Introduce yourself to someone in room */
    if (strcmp(cmd, "introduce") == 0 || strcmp(cmd, "greet") == 0) {
        if (!args || !*args) {
            return vm_value_create_string("Introduce yourself to whom?\r\n");
        }
        if (!session->current_room) {
            return vm_value_create_string("You are nowhere.\r\n");
        }

        PlayerSession *target = NULL;
        Room *room = session->current_room;
        for (int i = 0; i < room->num_players; i++) {
            if (room->players[i] && room->players[i] != session &&
                room->players[i]->username &&
                strcasecmp(room->players[i]->username, args) == 0) {
                target = room->players[i];
                break;
            }
        }

        if (!target) {
            return vm_value_create_string("They are not here.\r\n");
        }

        /* Add to target's introduced list */
        Character *tch = &target->character;
        if (tch->introduced_count < 32) {
            /* Check if already introduced */
            for (int i = 0; i < tch->introduced_count; i++) {
                if (tch->introduced_to[i] && strcasecmp(tch->introduced_to[i], session->username) == 0) {
                    return vm_value_create_string("They already know who you are.\r\n");
                }
            }
            tch->introduced_to[tch->introduced_count] = strdup(session->username);
            tch->introduced_count++;
        }

        send_to_player(target, "%s introduces themselves to you.\r\n", session->username);
        char response[256];
        snprintf(response, sizeof(response), "You introduce yourself to %s.\r\n", target->username);
        return vm_value_create_string(response);
    }

    /* FORGET - Forget an introduction */
    if (strcmp(cmd, "forget") == 0) {
        if (!args || !*args) {
            return vm_value_create_string("Forget whom?\r\n");
        }

        Character *ch = &session->character;
        for (int i = 0; i < ch->introduced_count; i++) {
            if (ch->introduced_to[i] && strcasecmp(ch->introduced_to[i], args) == 0) {
                free(ch->introduced_to[i]);
                /* Shift remaining entries */
                for (int j = i; j < ch->introduced_count - 1; j++) {
                    ch->introduced_to[j] = ch->introduced_to[j+1];
                }
                ch->introduced_count--;
                char response[256];
                snprintf(response, sizeof(response), "You forget %s.\r\n", args);
                return vm_value_create_string(response);
            }
        }
        return vm_value_create_string("You don't know that person.\r\n");
    }

    /* REMEMBER - List remembered introductions */
    if (strcmp(cmd, "remember") == 0) {
        Character *ch = &session->character;
        if (ch->introduced_count == 0) {
            return vm_value_create_string("You haven't been introduced to anyone.\r\n");
        }

        char msg[BUFFER_SIZE];
        strcpy(msg, "People you've been introduced to:\r\n");
        for (int i = 0; i < ch->introduced_count; i++) {
            if (ch->introduced_to[i]) {
                char line[128];
                snprintf(line, sizeof(line), "  %s\r\n", ch->introduced_to[i]);
                strcat(msg, line);
            }
        }
        return vm_value_create_string(msg);
    }

    /* BRIEF - Toggle brief room descriptions */
    if (strcmp(cmd, "brief") == 0) {
        session->is_brief = !session->is_brief;
        if (session->is_brief) {
            return vm_value_create_string("Brief mode ON. Room descriptions will be shortened.\r\n");
        } else {
            return vm_value_create_string("Brief mode OFF. Full room descriptions will be shown.\r\n");
        }
    }

    /* COLOR / ANSI - Toggle ANSI color */
    if (strcmp(cmd, "color") == 0 || strcmp(cmd, "ansi") == 0) {
        session->is_color = !session->is_color;
        if (session->is_color) {
            return vm_value_create_string("Color mode ON.\r\n");
        } else {
            return vm_value_create_string("Color mode OFF.\r\n");
        }
    }

    /* SCORE - Detailed stats display (extends existing stats) */
    if (strcmp(cmd, "score") == 0 && 0) {
        /* stats/score already handled above, this is a no-op placeholder */
    }

    /* PASSWORD - Change password */
    if (strcmp(cmd, "password") == 0) {
        if (!args || !*args) {
            return vm_value_create_string("Usage: password <old_password> <new_password>\r\n");
        }

        char old_pw[128], new_pw[128];
        if (sscanf(args, "%127s %127s", old_pw, new_pw) != 2) {
            return vm_value_create_string("Usage: password <old_password> <new_password>\r\n");
        }

        /* Verify old password */
        if (strcmp(old_pw, session->password_hash) != 0) {
            return vm_value_create_string("Incorrect old password.\r\n");
        }

        strncpy(session->password_hash, new_pw, sizeof(session->password_hash) - 1);
        save_character(session);
        return vm_value_create_string("Password changed successfully.\r\n");
    }

    /* ECHO - Echo text back to self */
    if (strcmp(cmd, "echo") == 0) {
        if (!args || !*args) {
            return vm_value_create_string("Echo what?\r\n");
        }
        char msg[BUFFER_SIZE];
        snprintf(msg, sizeof(msg), "%s\r\n", args);
        return vm_value_create_string(msg);
    }

    /* VIEW - Alias for examine */
    if (strcmp(cmd, "view") == 0) {
        cmd_examine(session, args ? args : "");
        result.type = VALUE_NULL;
        return result;
    }

    /* POSITION - Set position description */
    if (strcmp(cmd, "position") == 0) {
        if (!args || !*args) {
            if (session->is_resting) {
                return vm_value_create_string("You are resting.\r\n");
            } else {
                return vm_value_create_string("You are standing.\r\n");
            }
        }
        /* Position is handled via rest/stand commands */
        return vm_value_create_string("Use 'rest' to sit down or 'stand' to stand up.\r\n");
    }

    /* MAP - Show basic ASCII area map */
    if (strcmp(cmd, "map") == 0) {
        if (!session->current_room) {
            return vm_value_create_string("You are nowhere.\r\n");
        }

        Room *room = session->current_room;
        char map_buf[1024];

        /* Build a simple 3x3 directional map */
        char n_sym = (room->exits.north >= 0) ? '#' : ' ';
        char s_sym = (room->exits.south >= 0) ? '#' : ' ';
        char e_sym = (room->exits.east >= 0) ? '#' : ' ';
        char w_sym = (room->exits.west >= 0) ? '#' : ' ';
        char u_sym = (room->exits.up >= 0) ? '+' : ' ';
        char d_sym = (room->exits.down >= 0) ? '-' : ' ';

        snprintf(map_buf, sizeof(map_buf),
            "     %c\r\n"
            "     |\r\n"
            " %c---@---%c  %c up  %c dn\r\n"
            "     |\r\n"
            "     %c\r\n"
            "\r\n@ = You   # = Exit   + = Up   - = Down\r\n",
            n_sym, w_sym, e_sym, u_sym, d_sym, s_sym);

        return vm_value_create_string(map_buf);
    }

    /* TITLE - Set custom title */
    if (strcmp(cmd, "title") == 0) {
        if (!args || !*args) {
            session->title[0] = '\0';
            return vm_value_create_string("Title cleared.\r\n");
        }

        strncpy(session->title, args, sizeof(session->title) - 1);
        session->title[sizeof(session->title) - 1] = '\0';

        char response[256];
        snprintf(response, sizeof(response), "Title set to: %s\r\n", session->title);
        return vm_value_create_string(response);
    }

    if (strcmp(cmd, "shutdown") == 0) {
        if (session->privilege_level < 2) {
            return vm_value_create_string("You don't have permission to use that command.\r\n");
        }
        
        int delay = 0;
        if (args && *args != '\0') {
            delay = atoi(args);
        }
        
        char msg[256];
        snprintf(msg, sizeof(msg), 
                "SYSTEM: Admin %s is shutting down the server%s%d second%s.\r\n",
                session->username,
                delay > 0 ? " in " : "",
                delay,
                delay == 1 ? "" : "s");
        broadcast_message(msg, NULL);
        
        fprintf(stderr, "[Server] Shutdown initiated by %s\n", session->username);
        server_running = 0;
        return vm_value_create_string("Server shutdown initiated.\r\n");
    }
    
    /* Unknown command */
    command_debug_set_context(command, cmd, args ? args : "", "unknown");
    char error_msg[512];
    snprintf(error_msg, sizeof(error_msg), 
            "Unknown command: %.200s\r\nType 'help' for available commands.\r\n", cmd);
    return vm_value_create_string(error_msg);
}

/* Broadcast message to all players except one */
void broadcast_message(const char *message, PlayerSession *exclude) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i] && 
            sessions[i]->state == STATE_PLAYING && 
            sessions[i] != exclude) {
            send_to_player(sessions[i], "%s", message);
        }
    }
}

/* Process input during login states */
void process_login_state(PlayerSession *session, const char *input) {
    char clean_input[256];
    strncpy(clean_input, input, sizeof(clean_input) - 1);
    clean_input[sizeof(clean_input) - 1] = '\0';
    
    /* Strip whitespace */
    char *start = clean_input;
    while (*start && isspace(*start)) start++;
    char *end = start + strlen(start) - 1;
    while (end > start && isspace(*end)) *end-- = '\0';
    
    switch (session->state) {
        case STATE_GET_NAME:
            if (strlen(start) < 3 || strlen(start) > 15) {
                send_to_player(session,
                    "Name must be between 3 and 15 characters.\r\n");
                send_prompt(session);
                return;
            }

            /* Check ban list */
            {
                FILE *bf = fopen("lib/save/banned.txt", "r");
                if (bf) {
                    char ban_line[128];
                    while (fgets(ban_line, sizeof(ban_line), bf)) {
                        /* Strip newline */
                        char *nl = strchr(ban_line, '\n');
                        if (nl) *nl = '\0';
                        if (strcasecmp(ban_line, start) == 0) {
                            fclose(bf);
                            send_to_player(session,
                                "\r\nYou have been banned from this server.\r\n");
                            session->state = STATE_DISCONNECTING;
                            return;
                        }
                    }
                    fclose(bf);
                }
            }

            strncpy(session->username, start, sizeof(session->username) - 1);

            /* Check if character exists */
            if (character_exists(session->username)) {
                send_to_player(session, 
                    "\r\nWelcome back, %s!\r\n", 
                    session->username);
                session->state = STATE_GET_PASSWORD;
            } else {
                send_to_player(session, 
                    "\r\nWelcome, %s! You appear to be new here.\r\n", 
                    session->username);
                session->state = STATE_NEW_PASSWORD;
            }
            send_prompt(session);
            break;
            
        case STATE_GET_PASSWORD:
            /* Verify password */
            
            /* Load existing character (this populates password_hash) */
            if (load_character(session, session->username)) {
                /* Simple password verification - compare with stored hash */
                /* Note: For dev purposes, storing plaintext. TODO: Use proper bcrypt */
                if (session->password_hash[0] && strcmp(session->password_hash, start) != 0) {
                    send_to_player(session, "\r\nIncorrect password.\r\n");
                    session->state = STATE_DISCONNECTING;
                    break;
                }
                send_to_player(session, "\r\nWelcome back!\r\n");
                send_to_player(session, "Your character has been restored.\r\n\r\n");

                /* Initialize inventory/equipment for loaded character */
                inventory_init(&session->character.inventory,
                               session->character.stats.ps > 0 ? session->character.stats.ps : 10);
                equipment_init(&session->character.equipment);

                /* Create LPC player object for existing character */
                session->player_object = create_player_object(
                    session->username,
                    "");  /* Password hash not needed for existing players */
                
                if (!session->player_object) {
                    fprintf(stderr, "[Server] WARNING: Failed to create LPC player object for %s\n",
                            session->username);
                    /* Continue anyway - C commands will still work */
                }
                
                session->state = STATE_PLAYING;
                
                /* Add player to their saved room */
                if (session->current_room) {
                    room_add_player(session->current_room, session);
                } else {
                    /* Fallback to start room if load failed */
                    Room *start = room_get_start();
                    if (start) {
                        session->current_room = start;
                        room_add_player(start, session);
                    }
                }
                
                /* Show room description */
                cmd_look(session, "");
                send_prompt(session);
                
                /* Announce login */
                char login_msg[256];
                snprintf(login_msg, sizeof(login_msg), 
                        "%s has entered the game.\r\n", session->username);
                broadcast_message(login_msg, session);
            } else {
                send_to_player(session, 
                    "\r\nError loading character. Please contact an administrator.\r\n");
                session->state = STATE_DISCONNECTING;
            }
            break;
            
        case STATE_NEW_PASSWORD:
            if (strlen(start) < 6) {
                send_to_player(session, 
                    "Password must be at least 6 characters.\r\n");
                send_prompt(session);
                return;
            }
            
            strncpy(session->password_buffer, start, sizeof(session->password_buffer) - 1);
            session->state = STATE_CONFIRM_PASSWORD;
            send_prompt(session);
            break;
            
        case STATE_CONFIRM_PASSWORD:
            if (strcmp(session->password_buffer, start) != 0) {
                send_to_player(session, 
                    "\r\nPasswords don't match. Let's try again.\r\n");
                memset(session->password_buffer, 0, sizeof(session->password_buffer));
                session->state = STATE_NEW_PASSWORD;
                send_prompt(session);
                return;
            }
            
            /* Store password hash (using plaintext for dev - TODO: bcrypt) */
            strncpy(session->password_hash, session->password_buffer, sizeof(session->password_hash) - 1);
            session->password_hash[sizeof(session->password_hash) - 1] = '\0';
            
            /* Create player object */
            session->player_object = create_player_object(
                session->username, 
                session->password_buffer);
            
            if (!session->player_object) {
                send_to_player(session, 
                    "\r\nError: Failed to create player object.\r\n");
                session->state = STATE_DISCONNECTING;
                return;
            }
            
            /* First player becomes admin */
            if (!first_player_created) {
                session->privilege_level = 2;  /* Admin */
                first_player_created = 1;
                fprintf(stderr, "[Server] First player created: %s (privilege: Admin)\n",
                       session->username);
            } else {
                session->privilege_level = 0;  /* Regular player */
            }
            
            /* Start character generation */
            memset(session->password_buffer, 0, sizeof(session->password_buffer));
            session->state = STATE_CHARGEN;
            chargen_init(session);
            break;
            
        default:
            break;
    }
}

/* Process input during character generation */
void process_chargen_state(PlayerSession *session, const char *input) {
    chargen_process_input(session, input);
}

/* Process input during playing state */
void process_playing_state(PlayerSession *session, const char *input) {
    fprintf(stderr, "[process_playing_state] INPUT: input=%p '%s'\n",
            (void*)input, input ? input : "(NULL)");

    /* Converse mode: treat all input as "say <input>" unless it's "." to exit */
    if (session->converse_mode && input && input[0] != '\0') {
        if (strcmp(input, ".") == 0) {
            session->converse_mode = 0;
            send_to_player(session, "Conversation mode OFF.\r\n");
            send_prompt(session);
            return;
        }
        /* Prepend "say " to the input */
        char say_buf[BUFFER_SIZE];
        snprintf(say_buf, sizeof(say_buf), "say %s", input);
        VMValue result = execute_command(session, say_buf);
        if (result.type == VALUE_STRING && result.data.string_value) {
            send_to_player(session, "%s", result.data.string_value);
            vm_value_release(&result);
        }
        send_prompt(session);
        return;
    }

    VMValue result = execute_command(session, input);

    if (result.type == VALUE_STRING && result.data.string_value) {
        if (strcmp(result.data.string_value, "quit") == 0) {
            send_to_player(session, "\r\nGoodbye, %s!\r\n", session->username);

            char logout_msg[256];
            snprintf(logout_msg, sizeof(logout_msg),
                    "%s has left the game.\r\n", session->username);
            broadcast_message(logout_msg, session);

            session->state = STATE_DISCONNECTING;
        } else {
            send_to_player(session, "%s", result.data.string_value);
            send_prompt(session);
        }

        command_debug_log_result(session, result);

        if (result.data.string_value) {
            vm_value_release(&result);
        }
    } else if (result.type == VALUE_NULL) {
        command_debug_log_result(session, result);
        /* Command handled its own output, just send prompt */
        send_prompt(session);
    } else {
        command_debug_log_result(session, result);
        send_to_player(session, "Command failed to execute.\r\n");
        send_prompt(session);
    }
}

/* Handle incoming input for a session */
void handle_session_input(PlayerSession *session, const char *input) {
    if (!session) return;
    
    session->last_activity = time(NULL);
    
    size_t input_len = strlen(input);
    if (session->input_length + input_len >= INPUT_BUFFER_SIZE - 1) {
        send_to_player(session, "\r\nInput too long. Clearing buffer.\r\n");
        session->input_length = 0;
        send_prompt(session);
        return;
    }
    
    memcpy(session->input_buffer + session->input_length, input, input_len);
    session->input_length += input_len;
    session->input_buffer[session->input_length] = '\0';
    
    char *line_start = session->input_buffer;
    char *newline;
    
    while ((newline = strchr(line_start, '\n')) != NULL) {
        *newline = '\0';
        
        char *cr = strchr(line_start, '\r');
        if (cr) *cr = '\0';
        
        if (session->state == STATE_CONNECTING) {
            send_prompt(session);
        } else if (session->state == STATE_CHARGEN) {
            if (strlen(line_start) > 0) {
                process_chargen_state(session, line_start);
            }
        } else if (session->state == STATE_PLAYING) {
            if (strlen(line_start) > 0) {
                process_playing_state(session, line_start);
            } else {
                send_prompt(session);
            }
        } else {
            process_login_state(session, line_start);
        }
        
        line_start = newline + 1;
    }
    
    size_t remaining = strlen(line_start);
    if (remaining > 0) {
        memmove(session->input_buffer, line_start, remaining + 1);
        session->input_length = remaining;
    } else {
        session->input_length = 0;
        session->input_buffer[0] = '\0';
    }
}

/* Check for idle session timeouts */
void check_session_timeouts(void) {
    time_t now = time(NULL);
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i]) {
            time_t idle = now - sessions[i]->last_activity;
            
            if (idle > SESSION_TIMEOUT) {
                // Exempt wizards/admins from idle timeout
                if (sessions[i]->privilege_level == 0) {
                    send_to_player(sessions[i], "You have been idle too long. Disconnecting...");
                    fprintf(stderr, "[Server] Timeout disconnect: %s (slot %d)\n",
                           sessions[i]->username[0] ? sessions[i]->username : "guest",
                           i);
                    sessions[i]->state = STATE_DISCONNECTING;
                }
                // Wizards (level 1+) are never kicked for idle
            }
        }
    }
}

/* Handle WebSocket data */
void handle_websocket_data(PlayerSession *session, const uint8_t *data, size_t len) {
    if (!session || !data) return;
    
    session->last_activity = time(NULL);
    
    /* Append to WebSocket buffer */
    if (session->ws_buffer_length + len >= WS_BUFFER_SIZE) {
        fprintf(stderr, "[Server] WebSocket buffer overflow, clearing\n");
        session->ws_buffer_length = 0;
        return;
    }
    
    memcpy(session->ws_buffer + session->ws_buffer_length, data, len);
    session->ws_buffer_length += len;
    
    /* Handle based on WebSocket state */
    if (session->ws_state == WS_STATE_CONNECTING) {
        /* Check for complete HTTP request (ends with \r\n\r\n) */
        if (memmem(session->ws_buffer, session->ws_buffer_length, "\r\n\r\n", 4) != NULL) {
            /* Null-terminate for string processing */
            session->ws_buffer[session->ws_buffer_length] = '\0';
            
            WSHandshake handshake;
            if (ws_handle_handshake((char*)session->ws_buffer, session->ws_buffer_length, &handshake) == 0) {
                /* Send handshake response */
                send(session->fd, handshake.response, handshake.response_len, 0);
                ws_handshake_free(&handshake);
                
                session->ws_state = WS_STATE_OPEN;
                session->ws_buffer_length = 0;
                
                fprintf(stderr, "[Server] WebSocket handshake complete for slot\n");
                
                /* Send welcome prompt */
                send_prompt(session);
            } else {
                /* Invalid handshake */
                fprintf(stderr, "[Server] WebSocket handshake failed\n");
                session->state = STATE_DISCONNECTING;
            }
        }
        return;
    }
    
    /* Process WebSocket frames */
    while (session->ws_buffer_length > 0 && session->ws_state == WS_STATE_OPEN) {
        WSFrame frame;
        size_t consumed;
        
        int result = ws_decode_frame(session->ws_buffer, session->ws_buffer_length, &frame, &consumed);
        
        if (result > 0) {
            /* Need more data */
            break;
        }
        
        if (result < 0) {
            /* Error */
            fprintf(stderr, "[Server] WebSocket frame decode error\n");
            session->state = STATE_DISCONNECTING;
            break;
        }
        
        /* Handle frame by opcode */
        switch (frame.opcode) {
            case WS_OPCODE_TEXT:
                /* Process as normal input */
                if (frame.payload && frame.payload_len > 0) {
                    /* Add newline if not present (for command processing) */
                    char input[INPUT_BUFFER_SIZE];
                    size_t copy_len = frame.payload_len;
                    if (copy_len >= sizeof(input) - 2) {
                        copy_len = sizeof(input) - 2;
                    }
                    memcpy(input, frame.payload, copy_len);
                    input[copy_len] = '\n';
                    input[copy_len + 1] = '\0';
                    
                    handle_session_input(session, input);
                }
                break;
                
            case WS_OPCODE_BINARY:
                /* Ignore binary frames for now */
                break;
                
            case WS_OPCODE_CLOSE:
                /* Client initiated close */
                fprintf(stderr, "[Server] WebSocket close received\n");
                {
                    size_t close_len;
                    uint8_t *close_frame = ws_encode_close(WS_CLOSE_NORMAL, "Goodbye", &close_len);
                    if (close_frame) {
                        send(session->fd, close_frame, close_len, 0);
                        free(close_frame);
                    }
                }
                session->ws_state = WS_STATE_CLOSED;
                session->state = STATE_DISCONNECTING;
                break;
                
            case WS_OPCODE_PING:
                /* Respond with pong */
                {
                    size_t pong_len;
                    uint8_t *pong_frame = ws_encode_pong(frame.payload, frame.payload_len, &pong_len);
                    if (pong_frame) {
                        send(session->fd, pong_frame, pong_len, 0);
                        free(pong_frame);
                    }
                }
                break;
                
            case WS_OPCODE_PONG:
                /* Received pong, ignore */
                break;
        }
        
        ws_frame_free(&frame);
        
        /* Remove consumed bytes from buffer */
        if (consumed < session->ws_buffer_length) {
            memmove(session->ws_buffer, session->ws_buffer + consumed, 
                    session->ws_buffer_length - consumed);
            session->ws_buffer_length -= consumed;
        } else {
            session->ws_buffer_length = 0;
        }
    }
}

/* Setup WebSocket listener socket */
int setup_ws_listener(int port) {
    int ws_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ws_fd < 0) {
        fprintf(stderr, "[Server] ERROR: WebSocket socket() failed: %s\n", strerror(errno));
        return -1;
    }
    
    int opt = 1;
    setsockopt(ws_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in ws_addr;
    memset(&ws_addr, 0, sizeof(ws_addr));
    ws_addr.sin_family = AF_INET;
    ws_addr.sin_addr.s_addr = INADDR_ANY;
    ws_addr.sin_port = htons(port);
    
    if (bind(ws_fd, (struct sockaddr*)&ws_addr, sizeof(ws_addr)) < 0) {
        fprintf(stderr, "[Server] ERROR: WebSocket bind() failed: %s\n", strerror(errno));
        close(ws_fd);
        return -1;
    }
    
    if (listen(ws_fd, 10) < 0) {
        fprintf(stderr, "[Server] ERROR: WebSocket listen() failed: %s\n", strerror(errno));
        close(ws_fd);
        return -1;
    }
    
    return ws_fd;
}

/* Test mode: parse a single file and report results */
int test_parse_file(const char *filename) {
    fprintf(stderr, "[Parser Test] File: %s\n", filename);
    fprintf(stderr, "[Parser Test] Initializing compiler...\n");
    
    /* Initialize VM (needed for compiler) */
    global_vm = vm_init();
    if (!global_vm) {
        fprintf(stderr, "[Parser Test] FAILED: Could not initialize VM\n");
        return 1;
    }
    
    /* Attempt to compile the file */
    fprintf(stderr, "[Parser Test] Compiling...\n");
    Program *prog = compiler_compile_file(filename);
    
    if (!prog) {
        fprintf(stderr, "[Parser Test] FAILED: Compilation failed\n");
        vm_free(global_vm);
        return 1;
    }
    
    fprintf(stderr, "[Parser Test] SUCCESS: File parsed successfully\n");
    fprintf(stderr, "[Parser Test] Functions found: %zu\n", prog->function_count);
    fprintf(stderr, "[Parser Test] Bytecode size: %zu bytes\n", prog->bytecode_len);
    
    /* Clean up */
    program_free(prog);
    vm_free(global_vm);
    
    return 0;
}

/* Main server */
int main(int argc, char **argv) {
    /* ADD THIS BLOCK AT THE START OF main() */
    /* Check for --parse-test mode */
    if (argc >= 3 && strcmp(argv[1], "--parse-test") == 0) {
        return test_parse_file(argv[2]);
    }
    
    int port = DEFAULT_PORT;
    int ws_port = DEFAULT_WS_PORT;
    const char *master_path = DEFAULT_MASTER_PATH;
    
    if (argc >= 2) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            fprintf(stderr, "Usage: %s [telnet_port] [ws_port] [master_path]\n", argv[0]);
            return 1;
        }
    }
    
    if (argc >= 3) {
        ws_port = atoi(argv[2]);
        if (ws_port <= 0 || ws_port > 65535) {
            fprintf(stderr, "Usage: %s [telnet_port] [ws_port] [master_path]\n", argv[0]);
            return 1;
        }
    }
    
    if (argc >= 4) {
        master_path = argv[3];
    }
    
    signal(SIGINT, handle_shutdown_signal);
    signal(SIGTERM, handle_shutdown_signal);
    signal(SIGPIPE, SIG_IGN);
    
    if (initialize_vm(master_path) != 0) {
        return 1;
    }

    command_debug_init();
    
    /* Initialize game world */
    room_init_world();
    
    /* Initialize skill system */
    skill_init();
    
    /* Initialize combat system */
    combat_init();
    
    /* Initialize item system */
    item_init();
    
    /* Initialize psionics system (Phase 5) */
    psionics_init();
    
    /* Initialize magic system (Phase 5) */
    magic_init();
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        sessions[i] = NULL;
    }
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        fprintf(stderr, "[Server] ERROR: socket() failed: %s\n", strerror(errno));
        cleanup_vm();
        return 1;
    }
    
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "[Server] ERROR: bind() failed: %s\n", strerror(errno));
        close(server_fd);
        cleanup_vm();
        return 1;
    }
    
    if (listen(server_fd, 10) < 0) {
        fprintf(stderr, "[Server] ERROR: listen() failed: %s\n", strerror(errno));
        close(server_fd);
        cleanup_vm();
        return 1;
    }
    
    /* Setup WebSocket listener */
    int ws_fd = setup_ws_listener(ws_port);
    if (ws_fd < 0) {
        fprintf(stderr, "[Server] WARNING: WebSocket listener failed, continuing with telnet only\n");
    }
    
    fprintf(stderr, "[Server] Telnet listening on port %d\n", port);
    if (ws_fd > 0) {
        fprintf(stderr, "[Server] WebSocket listening on port %d\n", ws_port);
    }
    fprintf(stderr, "[Server] Ready for connections\n\n");
    
    time_t last_timeout_check = time(NULL);
    time_t last_combat_tick = time(NULL);

    while (server_running) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);
        
        int max_fd = server_fd;
        
        /* Add WebSocket listener to select set */
        if (ws_fd > 0) {
            FD_SET(ws_fd, &read_fds);
            if (ws_fd > max_fd) {
                max_fd = ws_fd;
            }
        }
        
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (sessions[i] && sessions[i]->fd > 0) {
                FD_SET(sessions[i]->fd, &read_fds);
                if (sessions[i]->fd > max_fd) {
                    max_fd = sessions[i]->fd;
                }
            }
        }
        
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
        
        if (activity < 0 && errno != EINTR) {
            fprintf(stderr, "[Server] ERROR: select() failed: %s\n", strerror(errno));
            break;
        }
        
        if (activity < 0) continue;
        
        /* Handle telnet connections */
        if (FD_ISSET(server_fd, &read_fds)) {
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
            int new_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
            
            if (new_fd >= 0) {
                int slot = -1;
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (!sessions[i]) {
                        slot = i;
                        break;
                    }
                }
                
                if (slot >= 0) {
                    sessions[slot] = malloc(sizeof(PlayerSession));
                    init_session(sessions[slot], new_fd, inet_ntoa(client_addr.sin_addr), CONN_TELNET);
                    fprintf(stderr, "[Server] Telnet connection slot %d from %s\n", 
                           slot, sessions[slot]->ip_address);
                    send_prompt(sessions[slot]);
                } else {
                    const char *msg = "Server full.\r\n";
                    send(new_fd, msg, strlen(msg), 0);
                    close(new_fd);
                }
            }
        }
        
        /* Handle WebSocket connections */
        if (ws_fd > 0 && FD_ISSET(ws_fd, &read_fds)) {
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
            int new_fd = accept(ws_fd, (struct sockaddr*)&client_addr, &addr_len);
            
            if (new_fd >= 0) {
                int slot = -1;
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (!sessions[i]) {
                        slot = i;
                        break;
                    }
                }
                
                if (slot >= 0) {
                    sessions[slot] = malloc(sizeof(PlayerSession));
                    init_session(sessions[slot], new_fd, inet_ntoa(client_addr.sin_addr), CONN_WEBSOCKET);
                    fprintf(stderr, "[Server] WebSocket connection slot %d from %s\n", 
                           slot, sessions[slot]->ip_address);
                    /* Don't send prompt yet - wait for handshake */
                } else {
                    const char *msg = "HTTP/1.1 503 Service Unavailable\r\n\r\n";
                    send(new_fd, msg, strlen(msg), 0);
                    close(new_fd);
                }
            }
        }
        
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (!sessions[i] || sessions[i]->fd <= 0) continue;
            
            if (sessions[i]->state == STATE_DISCONNECTING) {
                fprintf(stderr, "[Server] Closing slot %d\n", i);
                free_session(sessions[i]);
                sessions[i] = NULL;
                continue;
            }
            
            if (FD_ISSET(sessions[i]->fd, &read_fds)) {
                char buffer[BUFFER_SIZE];
                ssize_t bytes = recv(sessions[i]->fd, buffer, sizeof(buffer) - 1, 0);
                
                if (bytes <= 0) {
                    fprintf(stderr, "[Server] Disconnect slot %d\n", i);
                    free_session(sessions[i]);
                    sessions[i] = NULL;
                } else {
                    if (sessions[i]->connection_type == CONN_WEBSOCKET) {
                        /* Handle as WebSocket data */
                        handle_websocket_data(sessions[i], (uint8_t*)buffer, bytes);
                    } else {
                        /* Handle as telnet data */
                        buffer[bytes] = '\0';
                        handle_session_input(sessions[i], buffer);
                    }
                }
            }
        }
        
        time_t now = time(NULL);
        if (now - last_timeout_check > 60) {
            check_session_timeouts();
            last_timeout_check = now;
        }

        /* Combat heartbeat - every 2 seconds */
        if (now - last_combat_tick >= COMBAT_TICK_SECS) {
            combat_tick();
            combat_regen_tick();
            last_combat_tick = now;
        }
    }
    
    fprintf(stderr, "\n[Server] Shutting down...\n");
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i]) {
            send_to_player(sessions[i], "\r\nServer shutting down...\r\n");
            free_session(sessions[i]);
        }
    }
    
    close(server_fd);
    if (ws_fd > 0) {
        close(ws_fd);
    }
    cleanup_vm();
    
    fprintf(stderr, "[Server] Shutdown complete\n");
    return 0;
}
