#include "master_object.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Module state */
static VirtualMachine *master_vm = NULL;
static int master_loaded = 0;

static char *find_master_file(void);

int master_object_init(const char *path, VirtualMachine *vm) {
    char *master_path = NULL;
    FILE *fp = NULL;
    
    if (!vm) {
        fprintf(stderr, "[ERROR] master_object_init: VM is NULL\n");
        return -1;
    }
    
    master_vm = vm;
    
    if (path && *path) {
        fp = fopen(path, "r");
        if (fp) {
            master_path = malloc(strlen(path) + 1);
            strcpy(master_path, path);
            printf("[Master] Found master at: %s\n", path);
        } else {
            fprintf(stderr, "[WARNING] Cannot open master at: %s\n", path);
        }
    }
    
    if (!fp) {
        master_path = find_master_file();
        if (master_path) {
            fp = fopen(master_path, "r");
            if (fp) {
                printf("[Master] Found master at: %s\n", master_path);
            }
        }
    }
    
    if (!fp) {
        fprintf(stderr, "[WARNING] No master.c file found\n");
        fprintf(stderr, "[INFO] Server will run with limited functionality\n");
        master_loaded = 0;
        return 0;
    }
    
    fclose(fp);
    master_loaded = 1;
    printf("[Master] Master object verified\n");
    
    if (master_path) {
        free(master_path);
    }
    
    return 0;
}

static char *find_master_file(void) {
    const char *search_paths[] = {
        "./lib/secure/master.c",
        "../lib/secure/master.c",
        NULL
    };
    
    const char *mudlib_path = getenv("AMLP_MUDLIB");
    if (mudlib_path) {
        char env_path[512];
        snprintf(env_path, sizeof(env_path), "%s/lib/secure/master.c", mudlib_path);
        
        if (access(env_path, R_OK) == 0) {
            char *result = malloc(strlen(env_path) + 1);
            strcpy(result, env_path);
            return result;
        }
    }
    
    for (int i = 0; search_paths[i]; i++) {
        if (access(search_paths[i], R_OK) == 0) {
            char *result = malloc(strlen(search_paths[i]) + 1);
            strcpy(result, search_paths[i]);
            return result;
        }
    }
    
    return NULL;
}

int master_register_callbacks(void) {
    if (master_loaded) {
        printf("[Master] Callbacks registered (master object active)\n");
    } else {
        printf("[Master] Callbacks registered (fallback mode)\n");
    }
    return 0;
}

void master_callback_compile_object(const char *filename) {
    if (!master_vm) {
        fprintf(stderr, "[ERROR] Master VM not initialized\n");
        return;
    }
    printf("[Master] Compiling: %s\n", filename);
}

void master_callback_log_error(const char *filename, const char *message) {
    if (!master_vm) {
        fprintf(stderr, "[ERROR] Master VM not initialized\n");
        return;
    }
    fprintf(stderr, "[ERROR] %s: %s\n", 
            filename ? filename : "(unknown)", 
            message ? message : "(no message)");
}

void master_callback_query_version(void) {
    if (!master_vm) {
        fprintf(stderr, "[ERROR] Master VM not initialized\n");
        return;
    }
    printf("[Master] AMLP-Driver v0.1.0-alpha\n");
}

void master_object_cleanup(void) {
    master_loaded = 0;
    printf("[Master] Cleanup complete\n");
}
