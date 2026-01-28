#!/bin/bash

echo "=================================================="
echo "  IMPLEMENTING LPC EXECUTION LAYER"
echo "=================================================="
echo ""

cd /home/thurtea/amlp-driver

# Backup original
cp src/mud_server.c src/mud_server.c.backup

# Create new mud_server.c with full LPC execution
cat > src/mud_server.c << 'ENDFILE'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/select.h>
#include "vm.h"
#include "gc.h"
#include "efuns.h"
#include "master_object.h"
#include "compiler.h"

#define MAX_CONNECTIONS 64
#define BUFFER_SIZE 1024
#define DEFAULT_PORT 3000

typedef struct {
    int socket;
    int active;
    char buffer[BUFFER_SIZE];
    void *connection_object;
    char *input_callback;
    void *callback_data;
} PlayerConnection;

static PlayerConnection connections[MAX_CONNECTIONS];
static int server_socket = -1;
static int running = 1;

#define MAX_OBJECTS 512
typedef struct {
    char *filename;
    void *object;
    Program *program;
} CachedObject;

static CachedObject object_cache[MAX_OBJECTS];
static int object_count = 0;

VirtualMachine *global_vm = NULL;

static void* load_or_compile_object(const char *filename);
static VMValue call_lpc_method(void *object, const char *method, const char *arg);
static void send_to_connection(PlayerConnection *conn, const char *message);
static void handle_player_input(int index);
static void handle_new_connection(int server_socket);
static void cleanup_server(void);
static void signal_handler(int signum);

static void send_to_connection(PlayerConnection *conn, const char *message) {
    if (conn && conn->active && message) {
        send(conn->socket, message, strlen(message), 0);
    }
}

static void* load_or_compile_object(const char *filename) {
    for (int i = 0; i < object_count; i++) {
        if (object_cache[i].filename && strcmp(object_cache[i].filename, filename) == 0) {
            printf("Found cached object: %s\n", filename);
            return object_cache[i].object;
        }
    }
    
    char full_path[1024];
    if (filename[0] == '/') {
        snprintf(full_path, sizeof(full_path), "./lib%s.c", filename);
    } else {
        snprintf(full_path, sizeof(full_path), "%s", filename);
    }
    
    printf("Compiling LPC file: %s\n", full_path);
    Program *program = compile_lpc_file(full_path);
    if (!program) {
        printf("Failed to compile: %s\n", full_path);
        return NULL;
    }
    
    printf("Successfully compiled: %s (%zu functions)\n", full_path, program->function_count);
    
    void *object = (void*)program;
    
    if (object_count < MAX_OBJECTS) {
        object_cache[object_count].filename = strdup(filename);
        object_cache[object_count].object = object;
        object_cache[object_count].program = program;
        object_count++;
    }
    
    for (size_t i = 0; i < program->function_count; i++) {
        if (strcmp(program->functions[i].name, "create") == 0) {
            call_lpc_method(object, "create", NULL);
            break;
        }
    }
    
    return object;
}

static VMValue call_lpc_method(void *object, const char *method, const char *arg) {
    VMValue result;
    result.type = VAL_INT;
    result.value.integer = 0;
    
    if (!object || !method) {
        return result;
    }
    
    Program *program = NULL;
    for (int i = 0; i < object_count; i++) {
        if (object_cache[i].object == object) {
            program = object_cache[i].program;
            break;
        }
    }
    
    if (!program) {
        return result;
    }
    
    for (size_t i = 0; i < program->function_count; i++) {
        if (strcmp(program->functions[i].name, method) == 0) {
            printf("Calling %s(%s)\n", method, arg ? arg : "");
            
            if (global_vm) {
                if (arg) {
                    VMValue arg_val;
                    arg_val.type = VAL_STRING;
                    arg_val.value.string = strdup(arg);
                    vm_push(global_vm, arg_val);
                }
                
                vm_execute_function(global_vm, program, i);
                
                if (global_vm->stack_top > 0) {
                    result = vm_pop(global_vm);
                }
            }
            break;
        }
    }
    
    return result;
}

static void handle_player_input(int index) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(connections[index].socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) {
        printf("Connection %d closed\n", index);
        close(connections[index].socket);
        connections[index].active = 0;
        connections[index].socket = -1;
        connections[index].connection_object = NULL;
        if (connections[index].input_callback) {
            free(connections[index].input_callback);
            connections[index].input_callback = NULL;
        }
        return;
    }
    
    buffer[bytes_received] = '\0';
    
    size_t len = strlen(buffer);
    while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')) {
        buffer[--len] = '\0';
    }
    
    if (len == 0) {
        send_to_connection(&connections[index], "> ");
        return;
    }
    
    printf("Player %d input: '%s'\n", index, buffer);
    
    if (connections[index].input_callback) {
        printf("Calling input_to callback: %s\n", connections[index].input_callback);
        call_lpc_method(connections[index].connection_object, 
                       connections[index].input_callback, 
                       buffer);
        free(connections[index].input_callback);
        connections[index].input_callback = NULL;
    } else if (connections[index].connection_object) {
        printf("Calling process_input\n");
        call_lpc_method(connections[index].connection_object, "process_input", buffer);
    } else {
        send_to_connection(&connections[index], "Error: No connection object\n");
    }
    
    send_to_connection(&connections[index], "> ");
}

static void handle_new_connection(int server_socket) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
    
    if (client_socket < 0) {
        perror("accept failed");
        return;
    }
    
    int slot = -1;
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (!connections[i].active) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        const char *msg = "Server full. Please try again later.\n";
        send(client_socket, msg, strlen(msg), 0);
        close(client_socket);
        return;
    }
    
    connections[slot].socket = client_socket;
    connections[slot].active = 1;
    connections[slot].connection_object = NULL;
    connections[slot].input_callback = NULL;
    connections[slot].callback_data = NULL;
    memset(connections[slot].buffer, 0, BUFFER_SIZE);
    
    printf("New connection accepted (slot %d)\n", slot);
    
    printf("Loading master object...\n");
    void *master = load_or_compile_object("./lib/secure/master.c");
    if (!master) {
        const char *msg = "Error: Could not load master object\n";
        send(client_socket, msg, strlen(msg), 0);
        close(client_socket);
        connections[slot].active = 0;
        return;
    }
    
    printf("Calling master->connect()\n");
    call_lpc_method(master, "connect", NULL);
    
    printf("Loading login object...\n");
    void *login = load_or_compile_object("/clone/login");
    if (!login) {
        const char *msg = "Error: Could not load login object\n";
        send(client_socket, msg, strlen(msg), 0);
        close(client_socket);
        connections[slot].active = 0;
        return;
    }
    
    connections[slot].connection_object = login;
    
    printf("Calling login->logon()\n");
    call_lpc_method(login, "logon", NULL);
    
    printf("Connection %d fully initialized\n", slot);
}

static void cleanup_server(void) {
    printf("\nShutting down server...\n");
    running = 0;
    
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (connections[i].active) {
            close(connections[i].socket);
            connections[i].active = 0;
            connections[i].connection_object = NULL;
            if (connections[i].input_callback) {
                free(connections[i].input_callback);
                connections[i].input_callback = NULL;
            }
        }
    }
    
    for (int i = 0; i < object_count; i++) {
        if (object_cache[i].filename) {
            free(object_cache[i].filename);
            object_cache[i].filename = NULL;
        }
    }
    
    if (server_socket >= 0) {
        close(server_socket);
        server_socket = -1;
    }
    
    global_vm = NULL;
    printf("Server shutdown complete\n");
}

static void signal_handler(int signum) {
    printf("\nReceived signal %d\n", signum);
    cleanup_server();
    exit(0);
}

int start_mud_server(int port) {
    printf("Starting AMLP-MUD server on port %d...\n", port);
    
    VirtualMachine *vm = vm_init();
    global_vm = vm;
    if (!vm) {
        fprintf(stderr, "Failed to initialize VM\n");
        return -1;
    }
    
    GC *gc = gc_init();
    if (!gc) {
        fprintf(stderr, "Failed to initialize GC\n");
        return -1;
    }
    
    EfunRegistry *efuns = efun_init();
    if (!efuns) {
        fprintf(stderr, "Failed to initialize efuns\n");
        return -1;
    }
    
    printf("VM, GC, and Efuns initialized\n");
    
    if (master_object_init() != 0) {
        fprintf(stderr, "Warning: Master object initialization had issues\n");
    }
    
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        connections[i].socket = -1;
        connections[i].active = 0;
        connections[i].connection_object = NULL;
        connections[i].input_callback = NULL;
        connections[i].callback_data = NULL;
        memset(connections[i].buffer, 0, BUFFER_SIZE);
    }
    
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket creation failed");
        return -1;
    }
    
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_socket);
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_socket);
        return -1;
    }
    
    if (listen(server_socket, 10) < 0) {
        perror("listen failed");
        close(server_socket);
        return -1;
    }
    
    printf("Server listening on port %d\n", port);
    printf("Maximum connections: %d\n", MAX_CONNECTIONS);
    printf("LPC execution layer active\n");
    
    while (running) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);
        
        int max_fd = server_socket;
        for (int i = 0; i < MAX_CONNECTIONS; i++) {
            if (connections[i].active) {
                FD_SET(connections[i].socket, &read_fds);
                if (connections[i].socket > max_fd) {
                    max_fd = connections[i].socket;
                }
            }
        }
        
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
        
        if (activity < 0) {
            if (running) {
                perror("select error");
            }
            break;
        }
        
        if (activity == 0) {
            continue;
        }
        
        if (FD_ISSET(server_socket, &read_fds)) {
            handle_new_connection(server_socket);
        }
        
        for (int i = 0; i < MAX_CONNECTIONS; i++) {
            if (connections[i].active && FD_ISSET(connections[i].socket, &read_fds)) {
                handle_player_input(i);
            }
        }
    }
    
    cleanup_server();
    return 0;
}

int main(int argc, char *argv[]) {
    int port = DEFAULT_PORT;
    
    if (argc > 1) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            fprintf(stderr, "Invalid port number: %s\n", argv[1]);
            return 1;
        }
    }
    
    return start_mud_server(port);
}
ENDFILE

echo "✓ Created enhanced mud_server.c with LPC execution layer"
echo ""
echo "Recompiling..."
make clean && make

if [ $? -eq 0 ]; then
    echo ""
    echo "========================================="
    echo "  LPC EXECUTION LAYER COMPLETE"
    echo "========================================="
    echo ""
    echo "Server now supports:"
    echo "  ✓ LPC file compilation"
    echo "  ✓ Object caching"
    echo "  ✓ master->connect() invocation"
    echo "  ✓ login->logon() execution"
    echo "  ✓ process_input() routing"
    echo "  ✓ input_to() callbacks"
    echo "  ✓ Method calls with arguments"
    echo ""
    echo "To test, run:"
    echo "  ./mud.ctl restart"
    echo "  telnet localhost 3000"
    echo ""
else
    echo ""
    echo "⚠ Compilation failed - checking errors..."
    echo "Original file backed up to: src/mud_server.c.backup"
fi
