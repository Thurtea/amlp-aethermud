/*
 * test_vm.c - Virtual Machine Test Suite
 * 
 * Comprehensive test suite for the VM with 30+ tests covering:
 * - Stack operations
 * - Arithmetic operations (with type coercion)
 * - Comparison operations
 * - Logical operations
 * - Bitwise operations
 * - Control flow (if/while)
 * - Function calls
 * - Arrays and mappings
 * - Complex nested scenarios
 */

#include "vm.h"
#include "object.h"
#include "array.h"
#include "mapping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* ========== Test Framework ========== */

static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

static void test_setup(const char *name) {
    printf("\n[TEST %d] %s\n", tests_run + 1, name);
}

static void test_assert(int condition, const char *message) {
    tests_run++;
    if (condition) {
        tests_passed++;
        printf("  ✓ PASS\n");
    } else {
        tests_failed++;
        printf("  ✗ FAIL: %s\n", message);
    }
}

static void print_summary(void) {
    printf("\n");
    printf("========================================\n");
    printf("Test Results: %d/%d passed", tests_passed, tests_run);
    if (tests_failed > 0) {
        printf(" (%d failed)", tests_failed);
    }
    printf("\n");
    printf("========================================\n");
}

/* ========== Helper Functions ========== */

static __attribute__((unused)) VMValue make_int(long value) {
    VMValue v;
    v.type = VALUE_INT;
    v.data.int_value = value;
    return v;
}

static __attribute__((unused)) VMValue make_float(double value) {
    VMValue v;
    v.type = VALUE_FLOAT;
    v.data.float_value = value;
    return v;
}

static __attribute__((unused)) VMValue make_string(const char *value) {
    VMValue v;
    v.type = VALUE_STRING;
    v.data.string_value = (char*)value;
    return v;
}

static __attribute__((unused)) VMValue make_null(void) {
    VMValue v;
    v.type = VALUE_NULL;
    return v;
}

static __attribute__((unused)) VMValue make_object(void *ptr) {
    VMValue v;
    v.type = VALUE_OBJECT;
    v.data.object_value = ptr;
    return v;
}

/* ========== Test Helper: Manual Bytecode Assembly ========== */

static void load_bytecode(VirtualMachine *vm, OpCode opcodes[], 
                          long int_args[], double float_args[], char *string_args[], 
                          int count) {
    VMInstruction *instr = malloc(sizeof(VMInstruction) * count);
    for (int i = 0; i < count; i++) {
        instr[i].opcode = opcodes[i];
        instr[i].operand.int_operand = int_args[i];
        if (float_args[i] != 0.0) {
            instr[i].operand.float_operand = float_args[i];
        }
        if (string_args[i]) {
            instr[i].operand.string_operand = string_args[i];
        }
    }
    vm_load_bytecode(vm, instr, count);
    free(instr);
}

/* ========== TESTS: Basic Stack Operations ========== */

void test_push_int(void) {
    test_setup("Push integer constant");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_HALT};
    long int_args[] = {42, 0};
    double float_args[] = {0, 0};
    char *string_args[] = {NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 2);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 42, 
                "Expected int 42 on stack");
    
    vm_free(vm);
}

void test_push_float(void) {
    test_setup("Push float constant");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_FLOAT, OP_HALT};
    long int_args[] = {0, 0};
    double float_args[] = {3.14, 0};
    char *string_args[] = {NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 2);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_FLOAT && result.data.float_value > 3.13, 
                "Expected float ~3.14 on stack");
    
    vm_free(vm);
}

void test_push_string(void) {
    test_setup("Push string constant");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_STRING, OP_HALT};
    long int_args[] = {0, 0};
    double float_args[] = {0, 0};
    char *string_args[] = {"hello", NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 2);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_STRING && strcmp(result.data.string_value, "hello") == 0, 
                "Expected string 'hello' on stack");
    
    vm_free(vm);
}

void test_push_null(void) {
    test_setup("Push null value");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_NULL, OP_HALT};
    long int_args[] = {0, 0};
    double float_args[] = {0, 0};
    char *string_args[] = {NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 2);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_NULL, "Expected null value on stack");
    
    vm_free(vm);
}

void test_dup(void) {
    test_setup("Duplicate stack value");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_DUP, OP_HALT};
    long int_args[] = {99, 0, 0};
    double float_args[] = {0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 3);
    vm_execute(vm);
    
    test_assert(vm->stack->top == 2, "Expected 2 values on stack");
    test_assert(vm->stack->values[0].data.int_value == 99 && 
                vm->stack->values[1].data.int_value == 99, 
                "Expected duplicated value");
    
    vm_free(vm);
}

void test_pop(void) {
    test_setup("Pop stack value");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_POP, OP_HALT};
    long int_args[] = {10, 20, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    test_assert(vm->stack->top == 1 && vm->stack->values[0].data.int_value == 10, 
                "Expected one value (10) on stack after pop");
    
    vm_free(vm);
}

/* ========== TESTS: Arithmetic Operations ========== */

void test_add_ints(void) {
    test_setup("Add two integers: 5 + 3 = 8");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_ADD, OP_HALT};
    long int_args[] = {5, 3, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 8, 
                "Expected 5 + 3 = 8");
    
    vm_free(vm);
}

void test_add_floats(void) {
    test_setup("Add two floats: 1.5 + 2.5 = 4.0");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_FLOAT, OP_PUSH_FLOAT, OP_ADD, OP_HALT};
    long int_args[] = {0, 0, 0, 0};
    double float_args[] = {1.5, 2.5, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_FLOAT && result.data.float_value > 3.9 && result.data.float_value < 4.1, 
                "Expected 1.5 + 2.5 = 4.0");
    
    vm_free(vm);
}

void test_type_coercion_add(void) {
    test_setup("Type coercion: int + float = float (5 + 2.5 = 7.5)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_FLOAT, OP_ADD, OP_HALT};
    long int_args[] = {5, 0, 0, 0};
    double float_args[] = {0, 2.5, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_FLOAT && result.data.float_value > 7.4 && result.data.float_value < 7.6, 
                "Expected float result from mixed arithmetic");
    
    vm_free(vm);
}

void test_subtract(void) {
    test_setup("Subtraction: 10 - 3 = 7");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_SUB, OP_HALT};
    long int_args[] = {10, 3, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 7, 
                "Expected 10 - 3 = 7");
    
    vm_free(vm);
}

void test_multiply(void) {
    test_setup("Multiplication: 4 * 3 = 12");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_MUL, OP_HALT};
    long int_args[] = {4, 3, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 12, 
                "Expected 4 * 3 = 12");
    
    vm_free(vm);
}

void test_divide(void) {
    test_setup("Division: 10 / 2 = 5.0 (returns float)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_DIV, OP_HALT};
    long int_args[] = {10, 2, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_FLOAT && result.data.float_value > 4.9 && result.data.float_value < 5.1, 
                "Expected division to return float ~5.0");
    
    vm_free(vm);
}

void test_modulo(void) {
    test_setup("Modulo: 17 % 5 = 2");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_MOD, OP_HALT};
    long int_args[] = {17, 5, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 2, 
                "Expected 17 % 5 = 2");
    
    vm_free(vm);
}

void test_negate(void) {
    test_setup("Negation: -(-42) = 42");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_NEG, OP_NEG, OP_HALT};
    long int_args[] = {42, 0, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 42, 
                "Expected double negation to equal original");
    
    vm_free(vm);
}

/* ========== TESTS: Comparison Operations ========== */

void test_equal_true(void) {
    test_setup("Equality: 5 == 5 = 1 (true)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_EQ, OP_HALT};
    long int_args[] = {5, 5, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected true (1) for 5 == 5");
    
    vm_free(vm);
}

void test_equal_false(void) {
    test_setup("Equality: 5 == 3 = 0 (false)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_EQ, OP_HALT};
    long int_args[] = {5, 3, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 0, 
                "Expected false (0) for 5 == 3");
    
    vm_free(vm);
}

void test_not_equal(void) {
    test_setup("Not equal: 5 != 3 = 1 (true)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_NE, OP_HALT};
    long int_args[] = {5, 3, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected true (1) for 5 != 3");
    
    vm_free(vm);
}

void test_less_than(void) {
    test_setup("Less than: 3 < 5 = 1 (true)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_LT, OP_HALT};
    long int_args[] = {3, 5, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected true (1) for 3 < 5");
    
    vm_free(vm);
}

void test_greater_than(void) {
    test_setup("Greater than: 10 > 5 = 1 (true)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_GT, OP_HALT};
    long int_args[] = {10, 5, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected true (1) for 10 > 5");
    
    vm_free(vm);
}

void test_less_equal(void) {
    test_setup("Less or equal: 5 <= 5 = 1 (true)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_LE, OP_HALT};
    long int_args[] = {5, 5, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected true (1) for 5 <= 5");
    
    vm_free(vm);
}

void test_greater_equal(void) {
    test_setup("Greater or equal: 5 >= 3 = 1 (true)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_GE, OP_HALT};
    long int_args[] = {5, 3, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected true (1) for 5 >= 3");
    
    vm_free(vm);
}

/* ========== TESTS: Logical Operations ========== */

void test_logical_and_true(void) {
    test_setup("Logical AND: 1 && 1 = 1");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_AND, OP_HALT};
    long int_args[] = {1, 1, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected 1 for 1 && 1");
    
    vm_free(vm);
}

void test_logical_and_false(void) {
    test_setup("Logical AND: 1 && 0 = 0");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_AND, OP_HALT};
    long int_args[] = {1, 0, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 0, 
                "Expected 0 for 1 && 0");
    
    vm_free(vm);
}

void test_logical_or_true(void) {
    test_setup("Logical OR: 0 || 1 = 1");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_OR, OP_HALT};
    long int_args[] = {0, 1, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected 1 for 0 || 1");
    
    vm_free(vm);
}

void test_logical_not_true(void) {
    test_setup("Logical NOT: !0 = 1");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_NOT, OP_HALT};
    long int_args[] = {0, 0, 0};
    double float_args[] = {0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 3);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected 1 for !0");
    
    vm_free(vm);
}

void test_logical_not_false(void) {
    test_setup("Logical NOT: !5 = 0");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_NOT, OP_HALT};
    long int_args[] = {5, 0, 0};
    double float_args[] = {0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 3);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 0, 
                "Expected 0 for !5");
    
    vm_free(vm);
}

/* ========== TESTS: Bitwise Operations ========== */

void test_bitwise_and(void) {
    test_setup("Bitwise AND: 12 & 10 = 8 (1100 & 1010 = 1000)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_BIT_AND, OP_HALT};
    long int_args[] = {12, 10, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 8, 
                "Expected 12 & 10 = 8");
    
    vm_free(vm);
}

void test_bitwise_or(void) {
    test_setup("Bitwise OR: 12 | 10 = 14 (1100 | 1010 = 1110)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_BIT_OR, OP_HALT};
    long int_args[] = {12, 10, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 14, 
                "Expected 12 | 10 = 14");
    
    vm_free(vm);
}

void test_bitwise_xor(void) {
    test_setup("Bitwise XOR: 12 ^ 10 = 6 (1100 ^ 1010 = 0110)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_BIT_XOR, OP_HALT};
    long int_args[] = {12, 10, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 6, 
                "Expected 12 ^ 10 = 6");
    
    vm_free(vm);
}

void test_bitwise_not(void) {
    test_setup("Bitwise NOT: ~5 = -6");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_BIT_NOT, OP_HALT};
    long int_args[] = {5, 0, 0};
    double float_args[] = {0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 3);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == -6, 
                "Expected ~5 = -6");
    
    vm_free(vm);
}

void test_left_shift(void) {
    test_setup("Left shift: 5 << 2 = 20 (101 << 2 = 10100)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_LSHIFT, OP_HALT};
    long int_args[] = {5, 2, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 20, 
                "Expected 5 << 2 = 20");
    
    vm_free(vm);
}

void test_right_shift(void) {
    test_setup("Right shift: 20 >> 2 = 5 (10100 >> 2 = 101)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {OP_PUSH_INT, OP_PUSH_INT, OP_RSHIFT, OP_HALT};
    long int_args[] = {20, 2, 0, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 5, 
                "Expected 20 >> 2 = 5");
    
    vm_free(vm);
}

/* ========== TESTS: Control Flow ========== */

void test_jump(void) {
    test_setup("Unconditional jump");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 0: push 10
        OP_JUMP,               // 1: jump to address 3
        OP_PUSH_INT,           // 2: push 20 (skipped)
        OP_HALT                // 3: halt
    };
    long int_args[] = {10, 3, 20, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    test_assert(vm->stack->top == 1 && vm->stack->values[0].data.int_value == 10, 
                "Expected only 10 on stack (20 should be skipped)");
    
    vm_free(vm);
}

void test_jump_if_false_true(void) {
    test_setup("Jump if false (condition true, don't jump)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 0: push 1 (true)
        OP_JUMP_IF_FALSE,      // 1: jump to 4 if false
        OP_PUSH_INT,           // 2: push 42
        OP_HALT,               // 3: halt
    };
    long int_args[] = {1, 4, 42, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    // When condition is true (1), JUMP_IF_FALSE doesn't jump
    // Stack: condition gets popped by JUMP_IF_FALSE, then 42 is pushed
    test_assert(vm->stack->top == 1 && vm->stack->values[0].data.int_value == 42, 
                "Expected 42 to be pushed (condition was true)");
    
    vm_free(vm);
}

void test_jump_if_false_false(void) {
    test_setup("Jump if false (condition false, do jump)");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 0: push 0 (false)
        OP_JUMP_IF_FALSE,      // 1: jump to 4 if false
        OP_PUSH_INT,           // 2: push 42 (skipped)
        OP_HALT,               // 3: halt
    };
    long int_args[] = {0, 4, 42, 0};
    double float_args[] = {0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    // When condition is false (0), JUMP_IF_FALSE pops it and jumps to instruction 4 (HALT)
    // So 42 never gets pushed and stack should be empty
    test_assert(vm->stack->top == 0, 
                "Expected empty stack (condition popped, 42 skipped)");
    
    vm_free(vm);
}

/* ========== TESTS: Complex Operations ========== */

void test_arithmetic_sequence(void) {
    test_setup("Complex arithmetic: (5 + 3) * 2 - 1 = 15");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 5
        OP_PUSH_INT,           // 3
        OP_ADD,                // 5 + 3 = 8
        OP_PUSH_INT,           // 2
        OP_MUL,                // 8 * 2 = 16
        OP_PUSH_INT,           // 1
        OP_SUB,                // 16 - 1 = 15
        OP_HALT
    };
    long int_args[] = {5, 3, 0, 2, 0, 1, 0, 0};
    double float_args[] = {0, 0, 0, 0, 0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 8);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 15, 
                "Expected (5 + 3) * 2 - 1 = 15");
    
    vm_free(vm);
}

void test_comparison_chain(void) {
    test_setup("Comparison chain: (5 > 3) && (3 < 10) = 1");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 5
        OP_PUSH_INT,           // 3
        OP_GT,                 // 5 > 3 = 1
        OP_PUSH_INT,           // 3
        OP_PUSH_INT,           // 10
        OP_LT,                 // 3 < 10 = 1
        OP_AND,                // 1 && 1 = 1
        OP_HALT
    };
    long int_args[] = {5, 3, 0, 3, 10, 0, 0, 0};
    double float_args[] = {0, 0, 0, 0, 0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 8);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 1, 
                "Expected (5 > 3) && (3 < 10) = 1");
    
    vm_free(vm);
}

void test_mixed_operations(void) {
    test_setup("Mixed: int and float with coercion");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 10
        OP_PUSH_FLOAT,         // 2.5
        OP_ADD,                // 10 + 2.5 = 12.5 (float)
        OP_HALT
    };
    long int_args[] = {10, 0, 0, 0};
    double float_args[] = {0, 2.5, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 4);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_FLOAT && result.data.float_value > 12.4 && result.data.float_value < 12.6, 
                "Expected 10 + 2.5 = 12.5 (float)");
    
    vm_free(vm);
}

/* ========== TESTS: Array Operations ========== */

void test_make_array(void) {
    test_setup("Create array with 3 elements");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 1
        OP_PUSH_INT,           // 2
        OP_PUSH_INT,           // 3
        OP_MAKE_ARRAY,         // Make array from 3 elements
        OP_HALT
    };
    long int_args[] = {1, 2, 3, 3, 0};
    double float_args[] = {0, 0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 5);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_ARRAY && array_length(result.data.array_value) == 3, 
                "Expected array with 3 elements");
    
    vm_free(vm);
}

void test_array_index(void) {
    test_setup("Array access: [1, 2, 3][1] = 2");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_INT,           // 1
        OP_PUSH_INT,           // 2
        OP_PUSH_INT,           // 3
        OP_MAKE_ARRAY,         // Make array [1, 2, 3]
        OP_PUSH_INT,           // Index 1
        OP_INDEX_ARRAY,        // Access array[1]
        OP_HALT
    };
    long int_args[] = {1, 2, 3, 3, 1, 0, 0};
    double float_args[] = {0, 0, 0, 0, 0, 0, 0};
    char *string_args[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 7);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_INT && result.data.int_value == 2, 
                "Expected array[1] = 2");
    
    vm_free(vm);
}

/* ========== TESTS: Mapping Operations ========== */

void test_make_mapping(void) {
    test_setup("Create mapping with 2 key-value pairs");
    VirtualMachine *vm = vm_init();
    
    OpCode opcodes[] = {
        OP_PUSH_STRING,        // "name"
        OP_PUSH_STRING,        // "Alice"
        OP_PUSH_STRING,        // "age"
        OP_PUSH_INT,           // 25
        OP_MAKE_MAPPING,       // Make mapping from 2 pairs
        OP_HALT
    };
    long int_args[] = {0, 0, 0, 25, 2, 0};
    double float_args[] = {0, 0, 0, 0, 0, 0};
    char *string_args[] = {"name", "Alice", "age", NULL, NULL, NULL};
    
    load_bytecode(vm, opcodes, int_args, float_args, string_args, 6);
    vm_execute(vm);
    
    VMValue result = vm->stack->values[0];
    test_assert(result.type == VALUE_MAPPING && mapping_size(result.data.mapping_value) == 2, 
                "Expected mapping with 2 entries");
    
    vm_free(vm);
}

/* ========== TESTS: Object Method Calls ========== */

static VMFunction* make_const_method(const char *name, long value) {
    VMFunction *func = vm_function_create(name, 0, 0);
    VMInstruction ins1 = { .opcode = OP_PUSH_INT, .operand.int_operand = value };
    VMInstruction ins2 = { .opcode = OP_RETURN, .operand.int_operand = 0 };
    vm_function_add_instruction(func, ins1);
    vm_function_add_instruction(func, ins2);
    return func;
}

static VMFunction* make_sum_method(const char *name) {
    VMFunction *func = vm_function_create(name, 2, 2);
    VMInstruction ins1 = { .opcode = OP_LOAD_LOCAL, .operand.int_operand = 0 };
    VMInstruction ins2 = { .opcode = OP_LOAD_LOCAL, .operand.int_operand = 1 };
    VMInstruction ins3 = { .opcode = OP_ADD, .operand.int_operand = 0 };
    VMInstruction ins4 = { .opcode = OP_RETURN, .operand.int_operand = 0 };
    vm_function_add_instruction(func, ins1);
    vm_function_add_instruction(func, ins2);
    vm_function_add_instruction(func, ins3);
    vm_function_add_instruction(func, ins4);
    return func;
}

void test_call_method_direct(void) {
    test_setup("Call method on object");
    VirtualMachine *vm = vm_init();
    obj_t *obj = obj_new("TestObj");

    VMFunction *method = make_const_method("get_value", 42);
    vm_add_function(vm, method);
    obj_add_method(obj, method);

    /* Preload stack: object, method name (string) */
    vm_push_value(vm, make_object(obj));
    vm_push_value(vm, vm_value_create_string("get_value"));

    /* Program: CALL_METHOD 0 args, HALT */
    OpCode ops[] = {OP_CALL_METHOD, OP_HALT};
    long ints[] = {0, 0};
    double floats[] = {0, 0};
    char *strings[] = {NULL, NULL};
    load_bytecode(vm, ops, ints, floats, strings, 2);

    vm_execute(vm);

    test_assert(vm->stack->top == 1, "Expected one value on stack after call");
    VMValue result = vm_pop_value(vm);
    test_assert(result.type == VALUE_INT && result.data.int_value == 42,
                "Expected return value 42 from method");

    obj_free(obj);
    vm_free(vm);
}

void test_call_method_inherited(void) {
    test_setup("Call inherited method via prototype");
    VirtualMachine *vm = vm_init();
    obj_t *parent = obj_new("Parent");
    obj_t *child = obj_clone(parent);

    VMFunction *method = make_const_method("parent_value", 7);
    vm_add_function(vm, method);
    obj_add_method(parent, method);

    vm_push_value(vm, make_object(child));
    vm_push_value(vm, vm_value_create_string("parent_value"));

    OpCode ops[] = {OP_CALL_METHOD, OP_HALT};
    long ints[] = {0, 0};
    double floats[] = {0, 0};
    char *strings[] = {NULL, NULL};
    load_bytecode(vm, ops, ints, floats, strings, 2);

    vm_execute(vm);

    test_assert(vm->stack->top == 1, "Expected one value on stack after inherited call");
    VMValue result = vm_pop_value(vm);
    test_assert(result.type == VALUE_INT && result.data.int_value == 7,
                "Expected inherited return value 7");

    obj_free(child);
    obj_free(parent);
    vm_free(vm);
}

void test_call_method_with_args(void) {
    test_setup("Call method with arguments");
    VirtualMachine *vm = vm_init();
    obj_t *obj = obj_new("Adder");

    VMFunction *method = make_sum_method("add_two");
    vm_add_function(vm, method);
    obj_add_method(obj, method);

    vm_push_value(vm, make_object(obj));
    vm_push_value(vm, vm_value_create_string("add_two"));
    vm_push_value(vm, make_int(5));
    vm_push_value(vm, make_int(7));

    OpCode ops[] = {OP_CALL_METHOD, OP_HALT};
    long ints[] = {2, 0};
    double floats[] = {0, 0};
    char *strings[] = {NULL, NULL};
    load_bytecode(vm, ops, ints, floats, strings, 2);

    vm_execute(vm);

    test_assert(vm->stack->top == 1, "Expected one value on stack after arg call");
    VMValue result = vm_pop_value(vm);
    test_assert(result.type == VALUE_INT && result.data.int_value == 12,
                "Expected 5 + 7 = 12 from method");

    obj_free(obj);
    vm_free(vm);
}

void test_call_method_missing(void) {
    test_setup("Call missing method returns null");
    VirtualMachine *vm = vm_init();
    obj_t *obj = obj_new("NoMethod");

    vm_push_value(vm, make_object(obj));
    vm_push_value(vm, vm_value_create_string("missing"));

    OpCode ops[] = {OP_CALL_METHOD, OP_HALT};
    long ints[] = {0, 0};
    double floats[] = {0, 0};
    char *strings[] = {NULL, NULL};
    load_bytecode(vm, ops, ints, floats, strings, 2);

    vm_execute(vm);

    test_assert(vm->stack->top == 1, "Expected one value on stack after missing call");
    VMValue result = vm_pop_value(vm);
    test_assert(result.type == VALUE_NULL, "Expected null result when method missing");

    obj_free(obj);
    vm_free(vm);
}

/* ========== Main Test Runner ========== */

int main(void) {
    printf("\n========================================\n");
    printf("AMLP Virtual Machine - Test Suite\n");
    printf("========================================\n");
    
    /* Stack operations */
    test_push_int();
    test_push_float();
    test_push_string();
    test_push_null();
    test_dup();
    test_pop();
    
    /* Arithmetic */
    test_add_ints();
    test_add_floats();
    test_type_coercion_add();
    test_subtract();
    test_multiply();
    test_divide();
    test_modulo();
    test_negate();
    
    /* Comparison */
    test_equal_true();
    test_equal_false();
    test_not_equal();
    test_less_than();
    test_greater_than();
    test_less_equal();
    test_greater_equal();
    
    /* Logical */
    test_logical_and_true();
    test_logical_and_false();
    test_logical_or_true();
    test_logical_not_true();
    test_logical_not_false();
    
    /* Bitwise */
    test_bitwise_and();
    test_bitwise_or();
    test_bitwise_xor();
    test_bitwise_not();
    test_left_shift();
    test_right_shift();
    
    /* Control flow */
    test_jump();
    test_jump_if_false_true();
    test_jump_if_false_false();
    
    /* Complex */
    test_arithmetic_sequence();
    test_comparison_chain();
    test_mixed_operations();
    
    /* Arrays and mappings */
    test_make_array();
    test_array_index();
    test_make_mapping();

    /* Object method calls */
    test_call_method_direct();
    test_call_method_inherited();
    test_call_method_with_args();
    test_call_method_missing();
    
    print_summary();
    return tests_failed == 0 ? 0 : 1;
}
