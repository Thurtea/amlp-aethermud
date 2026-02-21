/* tests/test_lpc_execution.c
 * Integration test: compile LPC source, execute a function, verify result.
 */
#include "compiler.h"
#include "program.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

static int tests_passed = 0;
static int tests_total = 0;

static void test(const char *name, int condition) {
    tests_total++;
    if (condition) {
        printf("  PASS: %s\n", name);
        tests_passed++;
    } else {
        printf("  FAIL: %s\n", name);
    }
}

int main(void) {
    printf("\n");
    printf("========================================\n");
    printf("AMLP LPC Execution - Integration Tests\n");
    printf("========================================\n");
    printf("\n");

    /* Test 1: compile and execute add(int a, int b) { return a + b; } */
    {
        printf("[TEST 1] Execute LPC function: add(3, 4) == 7\n");

        const char *source = "int add(int a, int b) { return a + b; }";
        Program *prog = compiler_compile_string(source, "test_add");
        test("Program compiled", prog != NULL);

        if (prog) {
            test("No compile error", prog->last_error == COMPILE_SUCCESS);
            test("Function count >= 1", (int)prog->function_count >= 1);

            int func_idx = program_find_function(prog, "add");
            test("add() found", func_idx >= 0);

            if (func_idx >= 0) {
                VMValue args[2];
                args[0].type = VALUE_INT;
                args[0].data.int_value = 3;
                args[1].type = VALUE_INT;
                args[1].data.int_value = 4;

                VMValue result = program_execute_by_index(prog, func_idx, args, 2);
                test("Result type is INT", result.type == VALUE_INT);
                test("Result value is 7", result.type == VALUE_INT && result.data.int_value == 7);
            }

            program_free(prog);
        }
    }
    printf("\n");

    /* Test 2: execute a constant-returning function */
    {
        printf("[TEST 2] Execute LPC function: answer() == 42\n");

        const char *source = "int answer() { return 42; }";
        Program *prog = compiler_compile_string(source, "test_answer");
        test("Program compiled", prog != NULL);

        if (prog) {
            int func_idx = program_find_function(prog, "answer");
            test("answer() found", func_idx >= 0);

            if (func_idx >= 0) {
                VMValue result = program_execute_by_index(prog, func_idx, NULL, 0);
                test("Result type is INT", result.type == VALUE_INT);
                test("Result value is 42",
                     result.type == VALUE_INT && result.data.int_value == 42);
            }

            program_free(prog);
        }
    }
    printf("\n");

    /* Test 3: invalid function index returns NULL */
    {
        printf("[TEST 3] Out-of-bounds function index returns VALUE_NULL\n");

        const char *source = "void noop() { }";
        Program *prog = compiler_compile_string(source, "test_null");
        test("Program compiled", prog != NULL);

        if (prog) {
            VMValue result = program_execute_by_index(prog, 999, NULL, 0);
            test("Returns VALUE_NULL for bad index", result.type == VALUE_NULL);
            program_free(prog);
        }
    }
    printf("\n");

    printf("========================================\n");
    printf("Results: %d/%d passed\n", tests_passed, tests_total);
    printf("========================================\n");
    printf("\n");

    return (tests_passed == tests_total) ? 0 : 1;
}
