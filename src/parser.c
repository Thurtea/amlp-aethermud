/*
 * parser.c - Parser Implementation
 * 
 * This file implements a recursive descent parser for LPC source code.
 * It consumes tokens from the lexer and builds an Abstract Syntax Tree (AST).
 */

#define _POSIX_C_SOURCE 200809L

#include "parser.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* ========== Forward Declarations ========== */

static void parser_advance(Parser *parser);
static int parser_match(Parser *parser, TokenType type);
static int parser_check(Parser *parser, TokenType type);
static void parser_expect(Parser *parser, TokenType type);
static void parser_error(Parser *parser, const char *message);
static void parser_synchronize(Parser *parser);

static ASTNode* parser_parse_declaration(Parser *parser, ProgramNode *program);
static ASTNode* parser_parse_statement(Parser *parser);
static ASTNode* parser_parse_expression(Parser *parser);
static ASTNode* parser_parse_assignment(Parser *parser);
static ASTNode* parser_parse_ternary(Parser *parser);
static ASTNode* parser_parse_logical_or(Parser *parser);
static ASTNode* parser_parse_logical_and(Parser *parser);
static ASTNode* parser_parse_equality(Parser *parser);
static ASTNode* parser_parse_comparison(Parser *parser);
static ASTNode* parser_parse_addition(Parser *parser);
static ASTNode* parser_parse_multiplication(Parser *parser);
static ASTNode* parser_parse_unary(Parser *parser);
static ASTNode* parser_parse_postfix(Parser *parser);
static ASTNode* parser_parse_primary(Parser *parser);
static ASTNode* parser_parse_block(Parser *parser);
static ASTNode* parser_parse_foreach(Parser *parser);
static char* parser_parse_type(Parser *parser);

static ASTNode* ast_node_create(ASTNodeType type, int line, int column);
static ProgramNode* program_node_create(void);
static void program_node_add_declaration(ProgramNode *node, ASTNode *decl);

/* ========== Utility Functions ========== */

/**
 * Advance to the next token
 */
static void parser_advance(Parser *parser) {
    parser->previous_token = parser->current_token;
    parser->current_token = lexer_get_next_token(parser->lexer);
}

/**
 * Check if current token matches type
 */
static int parser_check(Parser *parser, TokenType type) {
    return parser->current_token.type == type;
}

/**
 * Check if current token matches type and advance
 */
static int parser_match(Parser *parser, TokenType type) {
    if (parser_check(parser, type)) {
        parser_advance(parser);
        return 1;
    }
    return 0;
}

/**
 * Expect a specific token type or error
 */
static void parser_expect(Parser *parser, TokenType type) {
    if (!parser_check(parser, type)) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected '%s' but found '%s'",
                 token_type_to_string(type),
                 token_type_to_string(parser->current_token.type));
        parser_error(parser, msg);
    }
    parser_advance(parser);
}

/**
 * Report a parse error
 */
static void parser_error(Parser *parser, const char *message) {
    fprintf(stderr, "[Parser Error] Line %d, Column %d: %s\n",
            parser->current_token.line_number,
            parser->current_token.column_number,
            message);
    parser->error_count++;
    parser->error_recovery_mode = 1;
}

/**
 * Attempt to recover from an error by skipping tokens
 */
static void parser_synchronize(Parser *parser) {
    parser_advance(parser);

    while (!parser_check(parser, TOKEN_EOF)) {
        if (parser->previous_token.type == TOKEN_SEMICOLON) {
            parser->error_recovery_mode = 0;
            return;
        }

        switch (parser->current_token.type) {
            case TOKEN_KEYWORD:
                parser->error_recovery_mode = 0;
                return;
            default:
                break;
        }

        parser_advance(parser);
    }
}

/**
 * Create a new AST node
 */
static ASTNode* ast_node_create(ASTNodeType type, int line, int column) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    node->type = type;
    node->line = line;
    node->column = column;
    node->data = NULL;
    return node;
}

/**
 * Create a program node
 */
static ProgramNode* program_node_create(void) {
    ProgramNode *node = malloc(sizeof(ProgramNode));
    if (!node) return NULL;
    node->declarations = malloc(sizeof(ASTNode*) * 10);
    node->declaration_count = 0;
    node->capacity = 10;
    node->inherit_paths = malloc(sizeof(char*) * 4);
    node->inherit_count = 0;
    node->inherit_capacity = 4;
    return node;
}

/**
 * Add a declaration to a program node
 */
static void program_node_add_declaration(ProgramNode *prog, ASTNode *decl) {
    if (prog->declaration_count >= prog->capacity) {
        prog->capacity *= 2;
        prog->declarations = realloc(prog->declarations, sizeof(ASTNode*) * prog->capacity);
    }
    prog->declarations[prog->declaration_count++] = decl;
}

/**
 * Parse a type specification
 */
static char* parser_parse_type(Parser *parser) {
    char *type_str = NULL;

    if (parser_match(parser, TOKEN_KEYWORD)) {
        type_str = strdup(parser->previous_token.value);
    } else if (parser_match(parser, TOKEN_IDENTIFIER)) {
        type_str = strdup(parser->previous_token.value);
    } else {
        parser_error(parser, "Expected type specifier");
        return strdup("mixed");
    }

    /* Handle pointer/array types (e.g., string*, int[]) */
    if (parser_match(parser, TOKEN_OPERATOR) && strcmp(parser->previous_token.value, "*") == 0) {
        /* Pointer type (string* = array of strings in LPC) */
        char *array_type = malloc(strlen(type_str) + 3);
        sprintf(array_type, "%s[]", type_str);
        free(type_str);
        type_str = array_type;
    } else if (parser_match(parser, TOKEN_LBRACKET)) {
        parser_expect(parser, TOKEN_RBRACKET);
        char *array_type = malloc(strlen(type_str) + 3);
        sprintf(array_type, "%s[]", type_str);
        free(type_str);
        type_str = array_type;
    }

    return type_str;
}

/* ========== Expression Parsing ========== */

/**
 * Parse primary expressions (literals, identifiers, parenthesized expressions)
 */
static ASTNode* parser_parse_primary(Parser *parser) {
    ASTNode *node = NULL;
    int line = parser->current_token.line_number;
    int column = parser->current_token.column_number;

    /* Check for scope resolution operator :: (parent method call) */
    int is_parent_call = 0;
    if (parser_check(parser, TOKEN_OPERATOR) && 
        parser->current_token.value && 
        strcmp(parser->current_token.value, "::") == 0) {
        is_parent_call = 1;
        parser_advance(parser);  /* Consume '::' */
    }

    if (parser_match(parser, TOKEN_NUMBER)) {
        node = ast_node_create(NODE_LITERAL_NUMBER, line, column);
        LiteralNumberNode *num_node = malloc(sizeof(LiteralNumberNode));
        num_node->int_value = strtol(parser->previous_token.value, NULL, 10);
        num_node->is_float = 0;
        node->data = num_node;
    } else if (parser_match(parser, TOKEN_FLOAT)) {
        node = ast_node_create(NODE_LITERAL_NUMBER, line, column);
        LiteralNumberNode *num_node = malloc(sizeof(LiteralNumberNode));
        num_node->float_value = strtod(parser->previous_token.value, NULL);
        num_node->is_float = 1;
        node->data = num_node;
    } else if (parser_match(parser, TOKEN_STRING)) {
        node = ast_node_create(NODE_LITERAL_STRING, line, column);
        LiteralStringNode *str_node = malloc(sizeof(LiteralStringNode));
        str_node->value = strdup(parser->previous_token.value);
        node->data = str_node;
    } else if (parser_match(parser, TOKEN_IDENTIFIER) || parser_match(parser, TOKEN_KEYWORD)) {
        node = ast_node_create(NODE_IDENTIFIER, line, column);
        IdentifierNode *id_node = malloc(sizeof(IdentifierNode));
        id_node->name = strdup(parser->previous_token.value);
        id_node->is_parent_call = is_parent_call;  /* Mark parent call */
        node->data = id_node;
    } else if (parser_match(parser, TOKEN_ARRAY_START)) {
        /* Array literal: ({ element1, element2, ... }) */
        node = ast_node_create(NODE_LITERAL_ARRAY, line, column);
        ArrayLiteralNode *array = malloc(sizeof(ArrayLiteralNode));
        array->elements = malloc(sizeof(ASTNode*) * 10);
        array->element_count = 0;
        array->capacity = 10;
        
        /* Parse array elements */
        if (!parser_check(parser, TOKEN_ARRAY_END)) {
            while (1) {
                /* Parse element expression */
                ASTNode *element = parser_parse_assignment(parser);
                
                /* Resize if needed */
                if (array->element_count >= array->capacity) {
                    array->capacity *= 2;
                    array->elements = realloc(array->elements, sizeof(ASTNode*) * array->capacity);
                }
                
                array->elements[array->element_count++] = element;

                if (!parser_match(parser, TOKEN_COMMA)) {
                    break;
                }
                if (parser_check(parser, TOKEN_ARRAY_END)) {
                    break;
                }
            }
        }
        
        /* Expect closing }) */
        parser_expect(parser, TOKEN_ARRAY_END);
        node->data = array;
    } else if (parser_match(parser, TOKEN_LPAREN)) {
        /* Check for mapping literal: ([ ... ]) */
        if (parser_check(parser, TOKEN_LBRACKET)) {
            parser_advance(parser);  /* consume [ */
            
            node = ast_node_create(NODE_LITERAL_MAPPING, line, column);
            MappingLiteralNode *mapping = malloc(sizeof(MappingLiteralNode));
            mapping->keys = malloc(sizeof(ASTNode*) * 10);
            mapping->values = malloc(sizeof(ASTNode*) * 10);
            mapping->pair_count = 0;
            mapping->capacity = 10;
            
            /* Parse key-value pairs: key: value, ... */
            if (!parser_check(parser, TOKEN_RBRACKET)) {
                while (1) {
                    /* Parse key expression */
                    ASTNode *key = parser_parse_expression(parser);
                    
                    /* Expect colon */
                    parser_expect(parser, TOKEN_COLON);
                    
                    /* Parse value expression */
                    ASTNode *value = parser_parse_expression(parser);
                    
                    /* Resize if needed */
                    if (mapping->pair_count >= mapping->capacity) {
                        mapping->capacity *= 2;
                        mapping->keys = realloc(mapping->keys, sizeof(ASTNode*) * mapping->capacity);
                        mapping->values = realloc(mapping->values, sizeof(ASTNode*) * mapping->capacity);
                    }
                    
                    mapping->keys[mapping->pair_count] = key;
                    mapping->values[mapping->pair_count] = value;
                    mapping->pair_count++;

                    if (!parser_match(parser, TOKEN_COMMA)) {
                        break;
                    }
                    if (parser_check(parser, TOKEN_RBRACKET)) {
                        break;
                    }
                }
            }
            
            /* Expect closing ]) */
            parser_expect(parser, TOKEN_RBRACKET);
            parser_expect(parser, TOKEN_RPAREN);
            
            node->data = mapping;
        } else {
            /* Regular parenthesized expression */
            node = parser_parse_expression(parser);
            parser_expect(parser, TOKEN_RPAREN);
        }
    } else {
        char msg[256];
        snprintf(msg, sizeof(msg), "Unexpected token: %s", parser->current_token.value);
        parser_error(parser, msg);
        node = ast_node_create(NODE_IDENTIFIER, line, column);
    }

    return node;
}

/**
 * Parse postfix expressions (function calls, array access, member access)
 */
static ASTNode* parser_parse_postfix(Parser *parser) {
    ASTNode *node = parser_parse_primary(parser);

    while (1) {
        if (parser_match(parser, TOKEN_LPAREN)) {
            /* Function call */
            int line = parser->previous_token.line_number;
            int column = parser->previous_token.column_number;
            ASTNode *call_node = ast_node_create(NODE_FUNCTION_CALL, line, column);
            FunctionCallNode *fcall = malloc(sizeof(FunctionCallNode));
            
            if (node->type == NODE_IDENTIFIER) {
                IdentifierNode *id = (IdentifierNode*)node->data;
                fcall->function_name = strdup(id->name);
                fcall->is_parent_call = id->is_parent_call;  /* Preserve parent call flag */
                free(id);
                free(node);
            } else {
                fcall->function_name = strdup("unknown");
                fcall->is_parent_call = 0;
            }

            fcall->object = NULL;  /* Regular function call, not a method call */
            fcall->arguments = malloc(sizeof(ASTNode*) * 10);
            fcall->argument_count = 0;
            fcall->capacity = 10;

            if (!parser_check(parser, TOKEN_RPAREN)) {
                do {
                    ASTNode *arg = parser_parse_assignment(parser);
                    if (fcall->argument_count >= fcall->capacity) {
                        fcall->capacity *= 2;
                        fcall->arguments = realloc(fcall->arguments, sizeof(ASTNode*) * fcall->capacity);
                    }
                    fcall->arguments[fcall->argument_count++] = arg;
                } while (parser_match(parser, TOKEN_COMMA));
            }

            parser_expect(parser, TOKEN_RPAREN);
            call_node->data = fcall;
            node = call_node;
        } else if (parser_match(parser, TOKEN_LBRACKET)) {
            /* Array access or range slice */
            int line = parser->previous_token.line_number;
            int column = parser->previous_token.column_number;
            ASTNode *access_node = ast_node_create(NODE_ARRAY_ACCESS, line, column);
            ArrayAccessNode *arr_access = malloc(sizeof(ArrayAccessNode));
            arr_access->array = node;
            arr_access->end_index = NULL;
            arr_access->is_range = 0;
            
            /* Check for range operator: array[start..end], array[..end], array[start..] */
            if (parser_check(parser, TOKEN_RANGE)) {
                /* array[..end] or array[..] */
                parser_advance(parser);  /* consume .. */
                arr_access->index = NULL;  /* No start index */
                arr_access->is_range = 1;
                if (!parser_check(parser, TOKEN_RBRACKET)) {
                    arr_access->end_index = parser_parse_expression(parser);
                }
            } else {
                /* Parse first expression (index or range start) */
                arr_access->index = parser_parse_expression(parser);
                
                /* Check if this is a range */
                if (parser_match(parser, TOKEN_RANGE)) {
                    arr_access->is_range = 1;
                    /* Check for end expression */
                    if (!parser_check(parser, TOKEN_RBRACKET)) {
                        arr_access->end_index = parser_parse_expression(parser);
                    }
                }
            }
            
            parser_expect(parser, TOKEN_RBRACKET);
            access_node->data = arr_access;
            node = access_node;
        } else if (parser_match(parser, TOKEN_DOT)) {
            /* Member access */
            int line = parser->previous_token.line_number;
            int column = parser->previous_token.column_number;
            parser_expect(parser, TOKEN_IDENTIFIER);
            ASTNode *member_node = ast_node_create(NODE_MEMBER_ACCESS, line, column);
            MemberAccessNode *member = malloc(sizeof(MemberAccessNode));
            member->object = node;
            member->member = strdup(parser->previous_token.value);
            member_node->data = member;
            node = member_node;
        } else if (parser->current_token.type == TOKEN_OPERATOR &&
                   parser->current_token.value &&
                   strcmp(parser->current_token.value, "->") == 0) {
            /* Arrow operator (method call): object->method() */
            int line = parser->current_token.line_number;
            int column = parser->current_token.column_number;
            parser_advance(parser);  /* consume '->' */
            
            /* Expect method name */
            Token method_name = parser->current_token;
            parser_expect(parser, TOKEN_IDENTIFIER);
            
            /* Check if followed by parentheses (method call) */
            if (parser_match(parser, TOKEN_LPAREN)) {
                /* Method call: object->method(args) */
                ASTNode *call_node = ast_node_create(NODE_FUNCTION_CALL, line, column);
                FunctionCallNode *fcall = malloc(sizeof(FunctionCallNode));
                
                /* Create method name with object context */
                fcall->function_name = strdup(method_name.value);
                fcall->object = node;  /* Store the object being called */
                fcall->is_parent_call = 0;  /* This is a method call, not parent call */
                
                /* Parse arguments */
                fcall->arguments = malloc(sizeof(ASTNode*) * 10);
                fcall->argument_count = 0;
                fcall->capacity = 10;
                
                if (!parser_check(parser, TOKEN_RPAREN)) {
                    do {
                        ASTNode *arg = parser_parse_assignment(parser);
                        if (fcall->argument_count >= fcall->capacity) {
                            fcall->capacity *= 2;
                            fcall->arguments = realloc(fcall->arguments, sizeof(ASTNode*) * fcall->capacity);
                        }
                        fcall->arguments[fcall->argument_count++] = arg;
                    } while (parser_match(parser, TOKEN_COMMA));
                }
                
                parser_expect(parser, TOKEN_RPAREN);
                call_node->data = fcall;
                node = call_node;
            } else {
                /* Property access: object->property (no parentheses) */
                ASTNode *member_node = ast_node_create(NODE_MEMBER_ACCESS, line, column);
                MemberAccessNode *member = malloc(sizeof(MemberAccessNode));
                member->object = node;
                member->member = strdup(method_name.value);
                member_node->data = member;
                node = member_node;
            }
        } else if (parser->current_token.type == TOKEN_OPERATOR &&
                   (strcmp(parser->current_token.value, "++") == 0 ||
                    strcmp(parser->current_token.value, "--") == 0)) {
            int line = parser->current_token.line_number;
            int column = parser->current_token.column_number;
            const char *op = parser->current_token.value;
            parser_advance(parser);

            ASTNode *unary_node = ast_node_create(NODE_UNARY_OP, line, column);
            UnaryOpNode *unary = malloc(sizeof(UnaryOpNode));
            unary->operator = strdup(op);
            unary->operand = node;
            unary->is_prefix = 0;
            unary_node->data = unary;
            node = unary_node;
        } else {
            break;
        }
    }

    return node;
}

/**
 * Parse unary expressions (prefix ++, --, -, !, etc.)
 */
static ASTNode* parser_parse_unary(Parser *parser) {
    /* Check for type cast: (type)expression */
    if (parser->current_token.type == TOKEN_LPAREN) {
        Token next = lexer_peek_token(parser->lexer);
        if (next.type == TOKEN_KEYWORD) {
            const char *kw = next.value;
            if (strcmp(kw, "string") == 0 || strcmp(kw, "int") == 0 || 
                strcmp(kw, "object") == 0 || strcmp(kw, "mixed") == 0 ||
                strcmp(kw, "mapping") == 0 || strcmp(kw, "void") == 0 ||
                strcmp(kw, "float") == 0 || strcmp(kw, "status") == 0) {
                
                int line = parser->current_token.line_number;
                int column = parser->current_token.column_number;
                parser_advance(parser);  /* Consume '(' */
                parser_advance(parser);  /* Consume type keyword */
                
                if (parser->current_token.type != TOKEN_RPAREN) {
                    parser_error(parser, "Expected ')' after cast type");
                    if (next.value) free(next.value);
                    return NULL;
                }
                parser_advance(parser);  /* Consume ')' */
                
                ASTNode *expr = parser_parse_unary(parser);
                if (!expr) {
                    if (next.value) free(next.value);
                    return NULL;
                }
                
                ASTNode *cast_node = ast_node_create(NODE_CAST, line, column);
                CastNode *cast = malloc(sizeof(CastNode));
                cast->target_type = strdup(kw);
                cast->expression = expr;
                cast_node->data = cast;
                if (next.value) free(next.value);
                return cast_node;
            }
        }
        if (next.value) free(next.value);
    }
    
    if (parser->current_token.type == TOKEN_OPERATOR) {
        const char *op_str = parser->current_token.value;
        if (strcmp(op_str, "-") == 0 || strcmp(op_str, "!") == 0 || 
            strcmp(op_str, "~") == 0 || strcmp(op_str, "++") == 0 || 
            strcmp(op_str, "--") == 0) {
            
            int line = parser->current_token.line_number;
            int column = parser->current_token.column_number;
            parser_advance(parser);
            
            ASTNode *unary_node = ast_node_create(NODE_UNARY_OP, line, column);
            UnaryOpNode *unary = malloc(sizeof(UnaryOpNode));
            unary->operator = strdup(op_str);
            unary->operand = parser_parse_unary(parser);
            unary->is_prefix = 1;
            unary_node->data = unary;
            return unary_node;
        }
    }

    return parser_parse_postfix(parser);
}

/**
 * Parse multiplication and division expressions
 */
static ASTNode* parser_parse_multiplication(Parser *parser) {
    ASTNode *node = parser_parse_unary(parser);

    while (parser->current_token.type == TOKEN_OPERATOR) {
        const char *op = parser->current_token.value;
        if (strcmp(op, "*") != 0 && strcmp(op, "/") != 0 && strcmp(op, "%") != 0) {
            break;
        }

        int line = parser->current_token.line_number;
        int column = parser->current_token.column_number;
        parser_advance(parser);

        ASTNode *binop_node = ast_node_create(NODE_BINARY_OP, line, column);
        BinaryOpNode *binop = malloc(sizeof(BinaryOpNode));
        binop->left = node;
        binop->operator = strdup(op);
        binop->right = parser_parse_unary(parser);
        binop_node->data = binop;
        node = binop_node;
    }

    return node;
}

/**
 * Parse addition and subtraction expressions
 */
static ASTNode* parser_parse_addition(Parser *parser) {
    ASTNode *node = parser_parse_multiplication(parser);

    while (parser->current_token.type == TOKEN_OPERATOR) {
        const char *op = parser->current_token.value;
        if (strcmp(op, "+") != 0 && strcmp(op, "-") != 0) {
            break;
        }

        int line = parser->current_token.line_number;
        int column = parser->current_token.column_number;
        parser_advance(parser);

        ASTNode *binop_node = ast_node_create(NODE_BINARY_OP, line, column);
        BinaryOpNode *binop = malloc(sizeof(BinaryOpNode));
        binop->left = node;
        binop->operator = strdup(op);
        binop->right = parser_parse_multiplication(parser);
        binop_node->data = binop;
        node = binop_node;
    }

    return node;
}

/**
 * Parse comparison expressions (<, >, <=, >=)
 */
static ASTNode* parser_parse_comparison(Parser *parser) {
    ASTNode *node = parser_parse_addition(parser);

    while (parser->current_token.type == TOKEN_OPERATOR) {
        const char *op = parser->current_token.value;
        if (strcmp(op, "<") != 0 && strcmp(op, ">") != 0 && 
            strcmp(op, "<=") != 0 && strcmp(op, ">=") != 0) {
            break;
        }

        int line = parser->current_token.line_number;
        int column = parser->current_token.column_number;
        parser_advance(parser);

        ASTNode *binop_node = ast_node_create(NODE_BINARY_OP, line, column);
        BinaryOpNode *binop = malloc(sizeof(BinaryOpNode));
        binop->left = node;
        binop->operator = strdup(op);
        binop->right = parser_parse_addition(parser);
        binop_node->data = binop;
        node = binop_node;
    }

    return node;
}

/**
 * Parse equality expressions (==, !=)
 */
static ASTNode* parser_parse_equality(Parser *parser) {
    ASTNode *node = parser_parse_comparison(parser);

    while (parser->current_token.type == TOKEN_OPERATOR) {
        const char *op = parser->current_token.value;
        if (strcmp(op, "==") != 0 && strcmp(op, "!=") != 0) {
            break;
        }

        int line = parser->current_token.line_number;
        int column = parser->current_token.column_number;
        parser_advance(parser);

        ASTNode *binop_node = ast_node_create(NODE_BINARY_OP, line, column);
        BinaryOpNode *binop = malloc(sizeof(BinaryOpNode));
        binop->left = node;
        binop->operator = strdup(op);
        binop->right = parser_parse_comparison(parser);
        binop_node->data = binop;
        node = binop_node;
    }

    return node;
}

/**
 * Parse logical AND expressions (&&)
 */
static ASTNode* parser_parse_logical_and(Parser *parser) {
    ASTNode *node = parser_parse_equality(parser);

    while (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "&&") == 0) {
        int line = parser->current_token.line_number;
        int column = parser->current_token.column_number;
        parser_advance(parser);

        ASTNode *binop_node = ast_node_create(NODE_BINARY_OP, line, column);
        BinaryOpNode *binop = malloc(sizeof(BinaryOpNode));
        binop->left = node;
        binop->operator = strdup("&&");
        binop->right = parser_parse_equality(parser);
        binop_node->data = binop;
        node = binop_node;
    }

    return node;
}

/**
 * Parse logical OR expressions (||)
 */
static ASTNode* parser_parse_logical_or(Parser *parser) {
    ASTNode *node = parser_parse_logical_and(parser);

    while (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "||") == 0) {
        int line = parser->current_token.line_number;
        int column = parser->current_token.column_number;
        parser_advance(parser);

        ASTNode *binop_node = ast_node_create(NODE_BINARY_OP, line, column);
        BinaryOpNode *binop = malloc(sizeof(BinaryOpNode));
        binop->left = node;
        binop->operator = strdup("||");
        binop->right = parser_parse_logical_and(parser);
        binop_node->data = binop;
        node = binop_node;
    }

    return node;
}

/**
 * Parse ternary conditional expressions (condition ? true_expr : false_expr)
 */
static ASTNode* parser_parse_ternary(Parser *parser) {
    ASTNode *node = parser_parse_logical_or(parser);

    if (parser->current_token.type == TOKEN_QUESTION) {
        int line = parser->current_token.line_number;
        int column = parser->current_token.column_number;
        parser_advance(parser);  /* Consume '?' */

        ASTNode *ternary_node = ast_node_create(NODE_TERNARY_OP, line, column);
        TernaryOpNode *ternary = malloc(sizeof(TernaryOpNode));
        ternary->condition = node;
        ternary->true_expr = parser_parse_expression(parser);
        
        parser_expect(parser, TOKEN_COLON);
        
        ternary->false_expr = parser_parse_ternary(parser);
        ternary_node->data = ternary;
        return ternary_node;
    }

    return node;
}

/**
 * Parse assignment expressions (=, +=, -=, etc.)
 */
static ASTNode* parser_parse_assignment(Parser *parser) {
    ASTNode *node = parser_parse_ternary(parser);

    if (parser->current_token.type == TOKEN_OPERATOR) {
        const char *op = parser->current_token.value;
        if (strcmp(op, "=") == 0 || strcmp(op, "+=") == 0 || strcmp(op, "-=") == 0 ||
            strcmp(op, "*=") == 0 || strcmp(op, "/=") == 0) {
            
            int line = parser->current_token.line_number;
            int column = parser->current_token.column_number;
            parser_advance(parser);

            ASTNode *assign_node = ast_node_create(NODE_ASSIGNMENT, line, column);
            AssignmentNode *assign = malloc(sizeof(AssignmentNode));
            assign->target = node;
            assign->operator = strdup(op);
            assign->value = parser_parse_assignment(parser);
            assign_node->data = assign;
            return assign_node;
        }
    }

    return node;
}

/**
 * Parse complete expressions
 */
static ASTNode* parser_parse_expression(Parser *parser) {
    return parser_parse_assignment(parser);
}

/* ========== Statement Parsing ========== */

/**
 * Parse a block statement
 */
static ASTNode* parser_parse_block(Parser *parser) {
    int line = parser->current_token.line_number;
    int column = parser->current_token.column_number;
    parser_expect(parser, TOKEN_LBRACE);

    ASTNode *block_node = ast_node_create(NODE_BLOCK, line, column);
    BlockNode *block = malloc(sizeof(BlockNode));
    block->statements = malloc(sizeof(ASTNode*) * 20);
    block->statement_count = 0;
    block->capacity = 20;
    block_node->data = block;

    while (!parser_check(parser, TOKEN_RBRACE) && !parser_check(parser, TOKEN_EOF)) {
        ASTNode *stmt = parser_parse_statement(parser);
        if (stmt) {
            if (block->statement_count >= block->capacity) {
                block->capacity *= 2;
                block->statements = realloc(block->statements, sizeof(ASTNode*) * block->capacity);
            }
            block->statements[block->statement_count++] = stmt;
        }
    }

    parser_expect(parser, TOKEN_RBRACE);
    return block_node;
}

/**
 * Parse a foreach statement
 */
static ASTNode* parser_parse_foreach(Parser *parser) {
    parser_advance(parser);  /* Consume 'foreach' */
    int line = parser->previous_token.line_number;
    int column = parser->previous_token.column_number;

    parser_expect(parser, TOKEN_LPAREN);

    char *first_type = parser_parse_type(parser);
    if (!parser_match(parser, TOKEN_IDENTIFIER)) {
        parser_error(parser, "Expected identifier in foreach");
        free(first_type);
        return NULL;
    }
    char *first_name = strdup(parser->previous_token.value);

    char *second_type = NULL;
    char *second_name = NULL;
    int has_key = 0;

    if (parser_match(parser, TOKEN_COMMA)) {
        has_key = 1;
        second_type = parser_parse_type(parser);
        if (!parser_match(parser, TOKEN_IDENTIFIER)) {
            parser_error(parser, "Expected identifier in foreach");
            free(first_type);
            free(first_name);
            free(second_type);
            return NULL;
        }
        second_name = strdup(parser->previous_token.value);
    }

    if (parser_check(parser, TOKEN_COLON)) {
        parser_advance(parser);
    } else if (parser_check(parser, TOKEN_KEYWORD) &&
               strcmp(parser->current_token.value, "in") == 0) {
        parser_advance(parser);
    } else {
        parser_error(parser, "Expected ':' or 'in' in foreach");
    }

    ASTNode *collection = parser_parse_expression(parser);
    parser_expect(parser, TOKEN_RPAREN);

    ASTNode *body = parser_parse_statement(parser);

    ASTNode *foreach_node = ast_node_create(NODE_FOREACH_LOOP, line, column);
    ForeachLoopNode *foreach_stmt = malloc(sizeof(ForeachLoopNode));
    foreach_stmt->has_key = has_key;
    if (has_key) {
        foreach_stmt->key_type = first_type;
        foreach_stmt->key_name = first_name;
        foreach_stmt->value_type = second_type;
        foreach_stmt->value_name = second_name;
    } else {
        foreach_stmt->key_type = NULL;
        foreach_stmt->key_name = NULL;
        foreach_stmt->value_type = first_type;
        foreach_stmt->value_name = first_name;
    }
    foreach_stmt->collection = collection;
    foreach_stmt->body = body;
    foreach_node->data = foreach_stmt;
    return foreach_node;
}

/**
 * Parse a statement
 */
static ASTNode* parser_parse_statement(Parser *parser) {
    /* Empty statement (standalone semicolon, e.g. from catch{};) */
    if (parser_check(parser, TOKEN_SEMICOLON)) {
        parser_advance(parser);
        return NULL;
    }

    /* Local variable declaration - check if starts with a type keyword */
    if (parser_check(parser, TOKEN_KEYWORD)) {
        const char *word = parser->current_token.value;
        /* Check if it's a type keyword (not a statement keyword) */
        if (strcmp(word, "int") == 0 || strcmp(word, "string") == 0 || 
            strcmp(word, "object") == 0 || strcmp(word, "mixed") == 0 ||
            strcmp(word, "float") == 0 || strcmp(word, "mapping") == 0 ||
            strcmp(word, "void") == 0 || strcmp(word, "status") == 0) {
            
            char *type = parser_parse_type(parser);
            int line = parser->previous_token.line_number;
            int column = parser->previous_token.column_number;
            
            if (!parser_match(parser, TOKEN_IDENTIFIER)) {
                parser_error(parser, "Expected identifier after type");
                free(type);
                return NULL;
            }
            
            char *name = strdup(parser->previous_token.value);
            
            /* Parse first variable */
            ASTNode *var_node = ast_node_create(NODE_VARIABLE_DECL, line, column);
            VariableDeclNode *var = malloc(sizeof(VariableDeclNode));
            var->type = strdup(type);
            var->name = name;
            var->is_private = 0;
            var->is_static = 0;
            var->initializer = NULL;
            
            if (parser_match(parser, TOKEN_OPERATOR) && strcmp(parser->previous_token.value, "=") == 0) {
                var->initializer = parser_parse_expression(parser);
            }
            
            var_node->data = var;
            
            /* Check for comma-separated additional variables */
            if (parser_match(parser, TOKEN_COMMA)) {
                /* Need to create a block to hold multiple declarations */
                ASTNode *block_node = ast_node_create(NODE_BLOCK, line, column);
                BlockNode *block = malloc(sizeof(BlockNode));
                block->statements = malloc(sizeof(ASTNode*) * 10);
                block->statement_count = 0;
                block->capacity = 10;
                block_node->data = block;
                
                /* Add first variable */
                block->statements[block->statement_count++] = var_node;
                
                /* Parse remaining variables */
                do {
                    if (!parser_match(parser, TOKEN_IDENTIFIER)) {
                        parser_error(parser, "Expected identifier after comma");
                        break;
                    }
                    
                    ASTNode *next_var_node = ast_node_create(NODE_VARIABLE_DECL, line, column);
                    VariableDeclNode *next_var = malloc(sizeof(VariableDeclNode));
                    next_var->type = strdup(type);
                    next_var->name = strdup(parser->previous_token.value);
                    next_var->is_private = 0;
                    next_var->is_static = 0;
                    next_var->initializer = NULL;
                    
                    if (parser_match(parser, TOKEN_OPERATOR) && strcmp(parser->previous_token.value, "=") == 0) {
                        next_var->initializer = parser_parse_expression(parser);
                    }
                    
                    next_var_node->data = next_var;
                    
                    if (block->statement_count >= block->capacity) {
                        block->capacity *= 2;
                        block->statements = realloc(block->statements, sizeof(ASTNode*) * block->capacity);
                    }
                    block->statements[block->statement_count++] = next_var_node;
                    
                } while (parser_match(parser, TOKEN_COMMA));
                
                parser_expect(parser, TOKEN_SEMICOLON);
                free(type);
                return block_node;
            } else {
                parser_expect(parser, TOKEN_SEMICOLON);
                free(type);
                return var_node;
            }
        }
    }
    
    /* If statement */
    if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "if") == 0) {
        parser_advance(parser);  /* Consume 'if' */
        int line = parser->previous_token.line_number;
        int column = parser->previous_token.column_number;
        parser_expect(parser, TOKEN_LPAREN);
        ASTNode *if_node = ast_node_create(NODE_IF_STATEMENT, line, column);
        IfStatementNode *if_stmt = malloc(sizeof(IfStatementNode));
        if_stmt->condition = parser_parse_expression(parser);
        parser_expect(parser, TOKEN_RPAREN);
        if_stmt->then_statement = parser_parse_statement(parser);
        
        if_stmt->else_statement = NULL;
        if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "else") == 0) {
            parser_advance(parser);  /* Consume 'else' */
            if_stmt->else_statement = parser_parse_statement(parser);
        }
        
        if_node->data = if_stmt;
        return if_node;
    }

    /* While loop */
    if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "while") == 0) {
        parser_advance(parser);  /* Consume 'while' */
        int line = parser->previous_token.line_number;
        int column = parser->previous_token.column_number;
        parser_expect(parser, TOKEN_LPAREN);
        ASTNode *while_node = ast_node_create(NODE_WHILE_LOOP, line, column);
        WhileLoopNode *while_stmt = malloc(sizeof(WhileLoopNode));
        while_stmt->condition = parser_parse_expression(parser);
        parser_expect(parser, TOKEN_RPAREN);
        while_stmt->body = parser_parse_statement(parser);
        while_node->data = while_stmt;
        return while_node;
    }

    /* Foreach loop */
    if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "foreach") == 0) {
        return parser_parse_foreach(parser);
    }

    /* Switch statement */
    if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "switch") == 0) {
        parser_advance(parser);  /* Consume 'switch' */
        int line = parser->previous_token.line_number;
        int column = parser->previous_token.column_number;
        parser_expect(parser, TOKEN_LPAREN);
        
        ASTNode *switch_node = ast_node_create(NODE_SWITCH_STATEMENT, line, column);
        SwitchStatementNode *switch_stmt = malloc(sizeof(SwitchStatementNode));
        switch_stmt->expression = parser_parse_expression(parser);
        switch_stmt->cases = malloc(sizeof(ASTNode*) * 10);
        switch_stmt->case_count = 0;
        switch_stmt->capacity = 10;
        
        parser_expect(parser, TOKEN_RPAREN);
        parser_expect(parser, TOKEN_LBRACE);
        
        /* Parse case and default labels */
        while (!parser_check(parser, TOKEN_RBRACE) && !parser_check(parser, TOKEN_EOF)) {
            if (parser_check(parser, TOKEN_KEYWORD)) {
                if (strcmp(parser->current_token.value, "case") == 0) {
                    parser_advance(parser);  /* Consume 'case' */
                    int case_line = parser->previous_token.line_number;
                    int case_column = parser->previous_token.column_number;
                    
                    ASTNode *case_node = ast_node_create(NODE_CASE_LABEL, case_line, case_column);
                    CaseLabelNode *case_label = malloc(sizeof(CaseLabelNode));
                    case_label->value = parser_parse_expression(parser);
                    case_label->statements = malloc(sizeof(ASTNode*) * 10);
                    case_label->statement_count = 0;
                    case_label->capacity = 10;
                    case_label->is_default = 0;
                    
                    parser_expect(parser, TOKEN_COLON);
                    
                    /* Parse statements until next case/default/closing brace */
                    while (!parser_check(parser, TOKEN_RBRACE) && !parser_check(parser, TOKEN_EOF)) {
                        if (parser_check(parser, TOKEN_KEYWORD) &&
                            (strcmp(parser->current_token.value, "case") == 0 ||
                             strcmp(parser->current_token.value, "default") == 0)) {
                            break;
                        }
                        
                        ASTNode *stmt = parser_parse_statement(parser);
                        if (stmt) {
                            if (case_label->statement_count >= case_label->capacity) {
                                case_label->capacity *= 2;
                                case_label->statements = realloc(case_label->statements, 
                                                                sizeof(ASTNode*) * case_label->capacity);
                            }
                            case_label->statements[case_label->statement_count++] = stmt;
                        }
                    }
                    
                    case_node->data = case_label;
                    
                    if (switch_stmt->case_count >= switch_stmt->capacity) {
                        switch_stmt->capacity *= 2;
                        switch_stmt->cases = realloc(switch_stmt->cases, 
                                                     sizeof(ASTNode*) * switch_stmt->capacity);
                    }
                    switch_stmt->cases[switch_stmt->case_count++] = case_node;
                    
                } else if (strcmp(parser->current_token.value, "default") == 0) {
                    parser_advance(parser);  /* Consume 'default' */
                    int default_line = parser->previous_token.line_number;
                    int default_column = parser->previous_token.column_number;
                    
                    ASTNode *default_node = ast_node_create(NODE_DEFAULT_LABEL, default_line, default_column);
                    CaseLabelNode *default_label = malloc(sizeof(CaseLabelNode));
                    default_label->value = NULL;  /* Default has no value */
                    default_label->statements = malloc(sizeof(ASTNode*) * 10);
                    default_label->statement_count = 0;
                    default_label->capacity = 10;
                    default_label->is_default = 1;
                    
                    parser_expect(parser, TOKEN_COLON);
                    
                    /* Parse statements until closing brace */
                    while (!parser_check(parser, TOKEN_RBRACE) && !parser_check(parser, TOKEN_EOF)) {
                        if (parser_check(parser, TOKEN_KEYWORD) &&
                            (strcmp(parser->current_token.value, "case") == 0 ||
                             strcmp(parser->current_token.value, "default") == 0)) {
                            break;
                        }
                        
                        ASTNode *stmt = parser_parse_statement(parser);
                        if (stmt) {
                            if (default_label->statement_count >= default_label->capacity) {
                                default_label->capacity *= 2;
                                default_label->statements = realloc(default_label->statements, 
                                                                   sizeof(ASTNode*) * default_label->capacity);
                            }
                            default_label->statements[default_label->statement_count++] = stmt;
                        }
                    }
                    
                    default_node->data = default_label;
                    
                    if (switch_stmt->case_count >= switch_stmt->capacity) {
                        switch_stmt->capacity *= 2;
                        switch_stmt->cases = realloc(switch_stmt->cases, 
                                                     sizeof(ASTNode*) * switch_stmt->capacity);
                    }
                    switch_stmt->cases[switch_stmt->case_count++] = default_node;
                    
                } else {
                    break;  /* Some other keyword, exit loop */
                }
            } else {
                break;  /* Not a keyword, exit loop */
            }
        }
        
        parser_expect(parser, TOKEN_RBRACE);
        switch_node->data = switch_stmt;
        return switch_node;
    }

    /* Return statement */
    if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "return") == 0) {
        parser_advance(parser);  /* Consume 'return' */
        int line = parser->previous_token.line_number;
        int column = parser->previous_token.column_number;
        ASTNode *ret_node = ast_node_create(NODE_RETURN_STATEMENT, line, column);
        ReturnStatementNode *ret_stmt = malloc(sizeof(ReturnStatementNode));
        
        if (!parser_check(parser, TOKEN_SEMICOLON)) {
            ret_stmt->value = parser_parse_expression(parser);
        } else {
            ret_stmt->value = NULL;
        }
        
        parser_expect(parser, TOKEN_SEMICOLON);
        ret_node->data = ret_stmt;
        return ret_node;
    }

    /* Break statement */
    if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "break") == 0) {
        parser_advance(parser);  /* Consume 'break' */
        int line = parser->previous_token.line_number;
        int column = parser->previous_token.column_number;
        parser_expect(parser, TOKEN_SEMICOLON);
        return ast_node_create(NODE_BREAK_STATEMENT, line, column);
    }

    /* Continue statement */
    if (parser_check(parser, TOKEN_KEYWORD) && strcmp(parser->current_token.value, "continue") == 0) {
        parser_advance(parser);  /* Consume 'continue' */
        int line = parser->previous_token.line_number;
        int column = parser->previous_token.column_number;
        parser_expect(parser, TOKEN_SEMICOLON);
        return ast_node_create(NODE_CONTINUE_STATEMENT, line, column);
    }

    /* Block statement */
    if (parser_check(parser, TOKEN_LBRACE)) {
        return parser_parse_block(parser);
    }

    /* Expression statement */
    ASTNode *expr = parser_parse_expression(parser);
    parser_expect(parser, TOKEN_SEMICOLON);
    
    ASTNode *expr_stmt = ast_node_create(NODE_EXPRESSION_STATEMENT, expr->line, expr->column);
    expr_stmt->data = expr;
    return expr_stmt;
}

/* ========== Declaration Parsing ========== */

/**
 * Parse a declaration (function or variable)
 */
static ASTNode* parser_parse_declaration(Parser *parser, ProgramNode *program) {
    /* Check for type modifiers (private, public, protected, static) */
    int is_private = 0;
    int is_public = 0;
    int is_protected = 0;
    int is_static = 0;

    while (parser_check(parser, TOKEN_KEYWORD)) {
        if (strcmp(parser->current_token.value, "private") == 0) {
            is_private = 1;
            parser_advance(parser);
        } else if (strcmp(parser->current_token.value, "public") == 0) {
            is_public = 1;
            parser_advance(parser);
        } else if (strcmp(parser->current_token.value, "protected") == 0) {
            is_protected = 1;
            parser_advance(parser);
        } else if (strcmp(parser->current_token.value, "static") == 0) {
            is_static = 1;
            parser_advance(parser);
        } else {
            /* Not a modifier, must be the type */
            break;
        }
    }

    char *type = parser_parse_type(parser);
    int line = parser->previous_token.line_number;
    int column = parser->previous_token.column_number;

    if (!parser_match(parser, TOKEN_IDENTIFIER) && !parser_match(parser, TOKEN_KEYWORD)) {
        parser_error(parser, "Expected identifier after type");
        free(type);
        return NULL;
    }

    char *name = strdup(parser->previous_token.value);

    /* Function declaration */
    if (parser_match(parser, TOKEN_LPAREN)) {
        ASTNode *func_node = ast_node_create(NODE_FUNCTION_DECL, line, column);
        FunctionDeclNode *func = malloc(sizeof(FunctionDeclNode));
        func->return_type = type;
        func->name = name;
        func->parameters = NULL;
        func->parameter_count = 0;
        func->is_private = is_private || is_protected;  /* Use captured modifiers */
        func->is_static = is_static;

        /* Parse parameters (allow empty list) */
        if (!parser_check(parser, TOKEN_RPAREN)) {
            func->parameters = malloc(sizeof(struct {char *type; char *name;}) * 10);
            do {
                char *param_type = parser_parse_type(parser);
                if (!parser_match(parser, TOKEN_IDENTIFIER)) {
                    parser_error(parser, "Expected parameter name");
                    break;
                }
                func->parameters[func->parameter_count].type = param_type;
                func->parameters[func->parameter_count].name = strdup(parser->previous_token.value);
                func->parameter_count++;
            } while (parser_match(parser, TOKEN_COMMA));
        }

        parser_expect(parser, TOKEN_RPAREN);
        func->body = parser_parse_block(parser);
        func_node->data = func;
        return func_node;
    }

    /* Variable declaration */
    ASTNode *first_var_node = NULL;
    
    /* Parse comma-separated variable declarations: int a, b = 5, c; */
    do {
        ASTNode *var_node = ast_node_create(NODE_VARIABLE_DECL, line, column);
        VariableDeclNode *var = malloc(sizeof(VariableDeclNode));
        var->type = strdup(type);  /* Each var gets its own copy */
        var->name = name;
        var->is_private = is_private || is_protected;
        var->is_static = is_static;
        var->initializer = NULL;

        if (parser_match(parser, TOKEN_OPERATOR) && strcmp(parser->previous_token.value, "=") == 0) {
            var->initializer = parser_parse_expression(parser);
        }

        var_node->data = var;
        
        /* Add to program node (for additional variables) */
        if (first_var_node) {
            program_node_add_declaration(program, var_node);
        } else {
            first_var_node = var_node;  /* Return the first one */
        }
        
        /* Check for comma (more variables) */
        if (parser_match(parser, TOKEN_COMMA)) {
            /* Parse next variable name */
            if (!parser_match(parser, TOKEN_IDENTIFIER)) {
                parser_error(parser, "Expected identifier after comma");
                break;
            }
            name = strdup(parser->previous_token.value);
        } else {
            break;  /* No more variables */
        }
    } while (1);

    parser_expect(parser, TOKEN_SEMICOLON);
    free(type);  /* Free the original type string */
    return first_var_node;
}

/* ========== Public API ========== */

/**
 * Initialize parser
 */
Parser* parser_init(Lexer *lexer) {
    if (!lexer) {
        fprintf(stderr, "Error: Cannot initialize parser with NULL lexer\n");
        return NULL;
    }

    Parser *parser = malloc(sizeof(Parser));
    if (!parser) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->error_count = 0;
    parser->error_recovery_mode = 0;

    return parser;
}

/**
 * Parse the program
 */
ASTNode* parser_parse(Parser *parser) {
    if (!parser) {
        fprintf(stderr, "Error: Cannot parse with NULL parser\n");
        return NULL;
    }

    ProgramNode *program = program_node_create();
    ASTNode *prog_node = ast_node_create(NODE_PROGRAM, 1, 1);
    prog_node->data = program;

    while (!parser_check(parser, TOKEN_EOF)) {
        /* Handle inherit statements */
        if (parser_check(parser, TOKEN_KEYWORD) &&
            strcmp(parser->current_token.value, "inherit") == 0) {
            parser_advance(parser);  /* Skip 'inherit' */

            /* Expect a string path like "/std/object" */
            if (parser_check(parser, TOKEN_STRING)) {
                const char *path = parser->current_token.value;
                fprintf(stderr, "[Parser] Inherit statement: %s\n", path);

                /* Store inherit path in ProgramNode */
                if (program->inherit_count >= program->inherit_capacity) {
                    program->inherit_capacity *= 2;
                    program->inherit_paths = realloc(program->inherit_paths,
                        sizeof(char*) * program->inherit_capacity);
                }
                program->inherit_paths[program->inherit_count++] = strdup(path);

                parser_advance(parser);
            } else {
                parser_error(parser, "Expected string path after 'inherit'");
            }

            parser_expect(parser, TOKEN_SEMICOLON);
            continue;
        }
        
        ASTNode *decl = parser_parse_declaration(parser, program);
        if (decl) {
            program_node_add_declaration(program, decl);
        } else if (parser->error_recovery_mode) {
            parser_synchronize(parser);
        } else {
            parser_advance(parser);
        }
    }

    if (parser->error_count > 0) {
        fprintf(stderr, "[Parser] Completed with %d error(s)\n", parser->error_count);
    }

    return prog_node;
}

/**
 * Free parser resources
 */
void parser_free(Parser *parser) {
    if (!parser) return;
    free(parser);
}

/**
 * Recursively free AST nodes
 */
void ast_node_free(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM: {
            ProgramNode *prog = (ProgramNode*)node->data;
            for (int i = 0; i < prog->declaration_count; i++) {
                ast_node_free(prog->declarations[i]);
            }
            free(prog->declarations);
            free(prog);
            break;
        }
        case NODE_BLOCK: {
            BlockNode *block = (BlockNode*)node->data;
            for (int i = 0; i < block->statement_count; i++) {
                ast_node_free(block->statements[i]);
            }
            free(block->statements);
            free(block);
            break;
        }
        case NODE_FUNCTION_CALL: {
            FunctionCallNode *call = (FunctionCallNode*)node->data;
            free(call->function_name);
            for (int i = 0; i < call->argument_count; i++) {
                ast_node_free(call->arguments[i]);
            }
            free(call->arguments);
            free(call);
            break;
        }
        case NODE_BINARY_OP: {
            BinaryOpNode *binop = (BinaryOpNode*)node->data;
            ast_node_free(binop->left);
            ast_node_free(binop->right);
            free(binop->operator);
            free(binop);
            break;
        }
        case NODE_TERNARY_OP: {
            TernaryOpNode *ternary = (TernaryOpNode*)node->data;
            ast_node_free(ternary->condition);
            ast_node_free(ternary->true_expr);
            ast_node_free(ternary->false_expr);
            free(ternary);
            break;
        }
        case NODE_SWITCH_STATEMENT: {
            SwitchStatementNode *switch_stmt = (SwitchStatementNode*)node->data;
            ast_node_free(switch_stmt->expression);
            for (int i = 0; i < switch_stmt->case_count; i++) {
                ast_node_free(switch_stmt->cases[i]);
            }
            free(switch_stmt->cases);
            free(switch_stmt);
            break;
        }
        case NODE_CASE_LABEL:
        case NODE_DEFAULT_LABEL: {
            CaseLabelNode *case_label = (CaseLabelNode*)node->data;
            if (case_label->value) {
                ast_node_free(case_label->value);
            }
            for (int i = 0; i < case_label->statement_count; i++) {
                ast_node_free(case_label->statements[i]);
            }
            free(case_label->statements);
            free(case_label);
            break;
        }
        case NODE_FOREACH_LOOP: {
            ForeachLoopNode *foreach_stmt = (ForeachLoopNode*)node->data;
            free(foreach_stmt->key_type);
            free(foreach_stmt->key_name);
            free(foreach_stmt->value_type);
            free(foreach_stmt->value_name);
            ast_node_free(foreach_stmt->collection);
            ast_node_free(foreach_stmt->body);
            free(foreach_stmt);
            break;
        }
        case NODE_LITERAL_STRING: {
            LiteralStringNode *str = (LiteralStringNode*)node->data;
            free(str->value);
            free(str);
            break;
        }
        case NODE_LITERAL_ARRAY: {
            ArrayLiteralNode *array = (ArrayLiteralNode*)node->data;
            for (int i = 0; i < array->element_count; i++) {
                ast_node_free(array->elements[i]);
            }
            free(array->elements);
            free(array);
            break;
        }
        case NODE_LITERAL_MAPPING: {
            MappingLiteralNode *mapping = (MappingLiteralNode*)node->data;
            for (int i = 0; i < mapping->pair_count; i++) {
                ast_node_free(mapping->keys[i]);
                ast_node_free(mapping->values[i]);
            }
            free(mapping->keys);
            free(mapping->values);
            free(mapping);
            break;
        }
        case NODE_CAST: {
            CastNode *cast = (CastNode*)node->data;
            free(cast->target_type);
            ast_node_free(cast->expression);
            free(cast);
            break;
        }
        case NODE_IDENTIFIER: {
            IdentifierNode *id = (IdentifierNode*)node->data;
            free(id->name);
            free(id);
            break;
        }
        default:
            if (node->data) free(node->data);
            break;
    }

    free(node);
}

/**
 * Convert AST node type to string
 */
const char* ast_node_to_string(ASTNodeType type) {
    switch (type) {
        case NODE_PROGRAM:          return "PROGRAM";
        case NODE_FUNCTION_DECL:    return "FUNCTION_DECL";
        case NODE_VARIABLE_DECL:    return "VARIABLE_DECL";
        case NODE_BLOCK:            return "BLOCK";
        case NODE_IF_STATEMENT:     return "IF_STATEMENT";
        case NODE_WHILE_LOOP:       return "WHILE_LOOP";
        case NODE_FOREACH_LOOP:     return "FOREACH_LOOP";
        case NODE_SWITCH_STATEMENT: return "SWITCH_STATEMENT";
        case NODE_CASE_LABEL:       return "CASE_LABEL";
        case NODE_DEFAULT_LABEL:    return "DEFAULT_LABEL";
        case NODE_RETURN_STATEMENT: return "RETURN_STATEMENT";
        case NODE_BREAK_STATEMENT:  return "BREAK_STATEMENT";
        case NODE_CONTINUE_STATEMENT: return "CONTINUE_STATEMENT";
        case NODE_BINARY_OP:        return "BINARY_OP";
        case NODE_UNARY_OP:         return "UNARY_OP";
        case NODE_TERNARY_OP:       return "TERNARY_OP";
        case NODE_CAST:             return "CAST";
        case NODE_ASSIGNMENT:       return "ASSIGNMENT";
        case NODE_FUNCTION_CALL:    return "FUNCTION_CALL";
        case NODE_LITERAL_NUMBER:   return "LITERAL_NUMBER";
        case NODE_LITERAL_STRING:   return "LITERAL_STRING";
        case NODE_LITERAL_ARRAY:    return "LITERAL_ARRAY";
        case NODE_LITERAL_MAPPING:  return "LITERAL_MAPPING";
        case NODE_IDENTIFIER:       return "IDENTIFIER";
        default:                    return "UNKNOWN";
    }
}

/**
 * Print AST in readable format
 */
void parser_print_ast(ASTNode *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");
    printf("[%s]\n", ast_node_to_string(node->type));

    switch (node->type) {
        case NODE_PROGRAM: {
            ProgramNode *prog = (ProgramNode*)node->data;
            for (int i = 0; i < prog->declaration_count; i++) {
                parser_print_ast(prog->declarations[i], indent + 1);
            }
            break;
        }
        case NODE_FUNCTION_CALL: {
            FunctionCallNode *call = (FunctionCallNode*)node->data;
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Function: %s\n", call->function_name);
            for (int i = 0; i < call->argument_count; i++) {
                parser_print_ast(call->arguments[i], indent + 1);
            }
            break;
        }
        case NODE_IDENTIFIER: {
            IdentifierNode *id = (IdentifierNode*)node->data;
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Name: %s\n", id->name);
            break;
        }
        default:
            break;
    }
}
