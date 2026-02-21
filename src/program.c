#include "program.h"
#include "vm.h"
#include "program_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Load and compile program from file
 */
Program* program_load_file(const char *filename) {
    if (!filename) return NULL;
    return compiler_compile_file(filename);
}

/**
 * Load and compile program from string
 */
Program* program_load_string(const char *source, const char *name) {
    if (!source || !name) return NULL;
    return compiler_compile_string(source, name);
}

/**
 * Execute a function in a program by name
 * Returns result of function execution
 */
VMValue program_execute_function(Program *prog, const char *function_name,
                                 VMValue *args, int arg_count) {
    if (!prog || !function_name) {
        return (VMValue){.type = VALUE_NULL};
    }
    
    int func_idx = program_find_function(prog, function_name);
    if (func_idx < 0) {
        fprintf(stderr, "Error: Function '%s' not found in program\n", function_name);
        return (VMValue){.type = VALUE_NULL};
    }
    
    return program_execute_by_index(prog, func_idx, args, arg_count);
}

/**
 * Execute a function by index.
 * Creates a fresh VM, loads the program, pushes args, calls the function,
 * and returns a cloned copy of the result before tearing the VM down.
 */
VMValue program_execute_by_index(Program *prog, int function_index,
                                 VMValue *args, int arg_count) {
    if (!prog || function_index < 0 || function_index >= (int)prog->function_count) {
        fprintf(stderr, "[program] execute_by_index: invalid program or function index %d\n",
                function_index);
        return (VMValue){.type = VALUE_NULL};
    }

    VirtualMachine *vm = vm_init();
    if (!vm) {
        fprintf(stderr, "[program] execute_by_index: vm_init() failed\n");
        return (VMValue){.type = VALUE_NULL};
    }

    if (program_loader_load(vm, prog) != 0) {
        fprintf(stderr, "[program] execute_by_index: program_loader_load() failed\n");
        vm_free(vm);
        return (VMValue){.type = VALUE_NULL};
    }

    /* After loading, function_index maps 1:1 to vm->functions[function_index]. */
    if (function_index >= vm->function_count) {
        fprintf(stderr, "[program] execute_by_index: function_index %d out of range after load\n",
                function_index);
        vm_free(vm);
        return (VMValue){.type = VALUE_NULL};
    }

    int stack_before = vm->stack->top;

    for (int i = 0; i < arg_count; i++) {
        if (vm_push_value(vm, args[i]) != 0) {
            fprintf(stderr, "[program] execute_by_index: stack push failed at arg %d\n", i);
            vm_free(vm);
            return (VMValue){.type = VALUE_NULL};
        }
    }

    VMValue result = {.type = VALUE_NULL};
    if (vm_call_function(vm, function_index, arg_count) == 0
            && vm->stack->top > stack_before) {
        /* Clone before vm_free() releases the stack. */
        result = vm_value_clone(vm_pop_value(vm));
    }

    vm_free(vm);
    return result;
}

/**
 * Get number of functions in program
 */
int program_function_count(Program *prog) {
    if (!prog) return 0;
    return prog->function_count;
}

/**
 * Get function name by index
 */
const char* program_function_name(Program *prog, int index) {
    if (!prog || index < 0 || index >= (int)prog->function_count) {
        return NULL;
    }
    return prog->functions[index].name;
}

/**
 * Get function argument count by index
 */
int program_function_args(Program *prog, int index) {
    if (!prog || index < 0 || index >= (int)prog->function_count) {
        return -1;
    }
    return prog->functions[index].arg_count;
}

/**
 * Get number of globals in program
 */
int program_global_count(Program *prog) {
    if (!prog) return 0;
    return prog->global_count;
}

/**
 * Get global variable name by index
 */
const char* program_global_name(Program *prog, int index) {
    if (!prog || index < 0 || index >= (int)prog->global_count) {
        return NULL;
    }
    return prog->globals[index].name;
}

/**
 * Get error string
 */
const char* program_error_string(exec_error_t error) {
    switch (error) {
        case EXEC_SUCCESS:
            return "Success";
        case EXEC_ERROR_FUNCTION_NOT_FOUND:
            return "Function not found";
        case EXEC_ERROR_INVALID_ARGS:
            return "Invalid arguments";
        case EXEC_ERROR_RUNTIME:
            return "Runtime error";
        case EXEC_ERROR_STACK_OVERFLOW:
            return "Stack overflow";
        default:
            return "Unknown error";
    }
}
