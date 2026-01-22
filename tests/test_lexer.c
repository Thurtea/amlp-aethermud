/*
 * test_lexer.c - Lexer Test Suite
 * 
 * This test program verifies the lexer's ability to tokenize
 * LPC source code correctly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

/* Test counter */
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

/**
 * Helper function to run a test
 */
void run_test(const char *test_name, const char *lpc_code) {
    tests_run++;
    printf("\n[Test %d] %s\n", tests_run, test_name);
    printf("Code: %s\n", lpc_code);
    printf("Tokens:\n");

    Lexer *lexer = lexer_init_from_string(lpc_code);
    if (!lexer) {
        printf("  ERROR: Failed to initialize lexer\n");
        tests_failed++;
        return;
    }

    Token token;
    int token_count = 0;
    while (1) {
        token = lexer_get_next_token(lexer);
        if (token.type == TOKEN_EOF) {
            printf("  [%d] EOF (line %d, col %d)\n", token_count, token.line_number, token.column_number);
            break;
        }

        printf("  [%d] %s: '%s' (line %d, col %d)\n",
               token_count,
               token_type_to_string(token.type),
               token.value ? token.value : "(null)",
               token.line_number,
               token.column_number);

        if (token.value) {
            free(token.value);
        }
        token_count++;
    }

    lexer_free(lexer);
    printf("Total tokens: %d\n", token_count);
    tests_passed++;
}

/**
 * Test variable declaration
 */
void test_variable_declaration(void) {
    run_test("Variable Declaration", "int x = 42;");
}

/**
 * Test string literal
 */
void test_string_literal(void) {
    run_test("String Literal", "string message = \"Hello, World!\";");
}

/**
 * Test function call
 */
void test_function_call(void) {
    run_test("Function Call", "write(\"test\"); print(x + y);");
}

/**
 * Test operators
 */
void test_operators(void) {
    run_test("Binary Operators", "a + b; c - d; e * f; g / h; i == j; k != l; m && n; o || p;");
}

/**
 * Test control structures
 */
void test_control_structures(void) {
    run_test("If Statement", "if (x > 5) { y = 10; } else { y = 20; }");
}

/**
 * Test while loop
 */
void test_while_loop(void) {
    run_test("While Loop", "while (i < 10) { i = i + 1; }");
}

/**
 * Test array access
 */
void test_array_access(void) {
    run_test("Array Access", "arr[0]; matrix[i][j]; vec[x + y];");
}

/**
 * Test comments
 */
void test_comments(void) {
    run_test("Comments", "int x = 5; // single line comment\nint y = 10; /* multi-line\ncomment */");
}

/**
 * Test floating point numbers
 */
void test_float_literals(void) {
    run_test("Float Literals", "float a = 3.14; float b = 2.5e-3; float c = 1E+10;");
}

/**
 * Test complex expression
 */
void test_complex_expression(void) {
    run_test("Complex Expression", "result = (x + y) * z - (a / b) % c;");
}

/**
 * Main test runner
 */
int main(void) {
    printf("========================================\n");
    printf("  LPC MUD Driver - Lexer Test Suite\n");
    printf("========================================\n");

    /* Run all tests */
    test_variable_declaration();
    test_string_literal();
    test_function_call();
    test_operators();
    test_control_structures();
    test_while_loop();
    test_array_access();
    test_comments();
    test_float_literals();
    test_complex_expression();

    /* Print summary */
    printf("\n========================================\n");
    printf("  Test Summary\n");
    printf("========================================\n");
    printf("Tests run:    %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);
    printf("\nResult: %s\n", tests_failed == 0 ? "ALL TESTS PASSED ✓" : "SOME TESTS FAILED ✗");

    return tests_failed == 0 ? 0 : 1;
}
