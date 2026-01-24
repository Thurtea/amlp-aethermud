#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "master_object.h"
#include "compiler.h"
#include "program.h"
#include "vm.h"

static Program *master_program = NULL;
static VirtualMachine *master_vm = NULL;

int master_object_init(const char *master_path, VirtualMachine *vm) {
    if (!master_path || !vm) {
        fprintf(stderr, "[ERROR] Invalid parameters to master_object_init\n");
        return -1;
    }
    
    // Clean up any existing master object
    if (master_program) {
        program_free(master_program);
        master_program = NULL;
    }
    
    // Compile the master object using compiler interface
    FILE *file = fopen(master_path, "r");
    if (!file) {
        fprintf(stderr, "[ERROR] Cannot open master file: %s\n", master_path);
        return -1;
    }
    
    // Create a simple compilation for now - TODO: proper integration
    master_program = calloc(1, sizeof(Program));
    if (!master_program) {
        fprintf(stderr, "[ERROR] Failed to allocate master program\n");
        fclose(file);
        return -1;
    }
    
    fclose(file);
    master_vm = vm;
    
    fprintf(stdout, "[DEBUG] Master object initialized from: %s\n", master_path);
    return 0;
}

VMValue master_call(const char *func_name, VMValue *args, int arg_count) {
    (void)args;     // Mark unused to avoid warnings
    (void)arg_count; // Mark unused to avoid warnings
    
    VMValue null_val = {.type = VALUE_NULL, .data.int_value = 0};
    
    if (!master_is_loaded()) {
        fprintf(stderr, "[ERROR] Master object not loaded\n");
        return null_val;
    }
    
    if (!func_name) {
        fprintf(stderr, "[ERROR] Function name is NULL\n");
        return null_val;
    }
    
    // TODO: Implement function calling in VM
    fprintf(stdout, "[DEBUG] Calling master function: %s\n", func_name);
    
    return null_val;
}

void master_object_free(void) {
    if (master_program) {
        free(master_program);
        master_program = NULL;
    }
    master_vm = NULL;
}

int master_is_loaded(void) {
    return (master_program != NULL && master_vm != NULL);
}

Program* master_get_program(void) {
    return master_program;
}

