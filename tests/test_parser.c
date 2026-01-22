/*
 * test_parser.c - Parser Test Suite
 * 
 * This test program verifies the parser's ability to build
 * Abstract Syntax Trees from LPC source code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"

/* Test counter */
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

/**
 * Helper function to run a parser test
 */
void run_parser_test(const char *test_name, const char *lpc_code) {
    tests_run++;
    printf("\n[Test %d] %s\n", tests_run, test_name);
    printf("Code:\n%s\n", lpc_code);
    printf("AST:\n");

    /* Initialize lexer and parser */
    Lexer *lexer = lexer_init_from_string(lpc_code);
    if (!lexer) {
        printf("  ERROR: Failed to initialize lexer\n");
        tests_failed++;
        return;
    }

    Parser *parser = parser_init(lexer);
    if (!parser) {
        printf("  ERROR: Failed to initialize parser\n");
        lexer_free(lexer);
        tests_failed++;
        return;
    }

    /* Parse the program */
    ASTNode *root = parser_parse(parser);
    if (!root) {
        printf("  ERROR: Failed to parse program\n");
        parser_free(parser);
        lexer_free(lexer);
        tests_failed++;
        return;
    }

    /* Print the AST */
    parser_print_ast(root, 1);

    /* Cleanup */
    ast_node_free(root);
    parser_free(parser);
    lexer_free(lexer);

    printf("Parse completed\n");
    tests_passed++;
}

/**
 * Test simple variable declaration
 */
void test_variable_decl(void) {
    const char *code = "int x = 42;";
    run_parser_test("Variable Declaration", code);
}

/**
 * Test function declaration
 */
void test_function_decl(void) {
    const char *code = "void test() { }";
    run_parser_test("Function Declaration", code);
}

/**
 * Test function with parameters
 */
void test_function_params(void) {
    const char *code = "int add(int a, int b) { return a + b; }";
    run_parser_test("Function with Parameters", code);
}

/**
 * Test if statement
 */
void test_if_statement(void) {
    const char *code = "void test() { if (x > 0) { y = 1; } }";
    run_parser_test("If Statement", code);
}

/**
 * Test while loop
 */
void test_while_loop(void) {
    const char *code = "void test() { while (i < 10) { i = i + 1; } }";
    run_parser_test("While Loop", code);
}

/**
 * Test return statement
 */
void test_return_statement(void) {
    const char *code = "int getValue() { return 42; }";
    run_parser_test("Return Statement", code);
}

/**
 * Test binary operations
 */
void test_binary_ops(void) {
    const char *code = "void test() { x = a + b; y = c * d; z = e - f; }";
    run_parser_test("Binary Operations", code);
}

/**
 * Test function call
 */
void test_function_call(void) {
    const char *code = "void test() { write(\"hello\"); print(42); }";
    run_parser_test("Function Calls", code);
}

/**
 * Test array access
 */
void test_array_access(void) {
    const char *code = "void test() { x = arr[0]; y = matrix[i][j]; }";
    run_parser_test("Array Access", code);
}

/**
 * Test complex expression
 */
void test_complex_expr(void) {
    const char *code = "void test() { result = (x + y) * z - (a / b) % c; }";
    run_parser_test("Complex Expression", code);
}

/**
 * Test multiple declarations
 */
void test_multiple_decls(void) {
    const char *code = "int x = 5; string name = \"test\"; void foo() { }";
    run_parser_test("Multiple Declarations", code);
}

/**
 * Main test runner
 */
int main(void) {
    printf("========================================\n");
    printf("  LPC MUD Driver - Parser Test Suite\n");
    printf("========================================\n");

    /* Run all tests */
    test_variable_decl();
    test_function_decl();
    test_function_params();
    test_if_statement();
    test_while_loop();
    test_return_statement();
    test_binary_ops();
    test_function_call();
    test_array_access();
    test_complex_expr();
    test_multiple_decls();

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
