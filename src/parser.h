/*
 * parser.h - Parser Header
 * 
 * This header defines the Abstract Syntax Tree (AST) node structures
 * and the Parser API for parsing LPC source code into an AST.
 */

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

/* ========== AST Node Type Enumeration ========== */

typedef enum {
    /* Program and declarations */
    NODE_PROGRAM,                   /* Root node containing all declarations */
    NODE_FUNCTION_DECL,             /* Function declaration */
    NODE_VARIABLE_DECL,             /* Variable declaration */
    NODE_INHERITANCE,               /* Inheritance declaration */
    
    /* Statements */
    NODE_BLOCK,                     /* Block of statements { ... } */
    NODE_IF_STATEMENT,              /* if statement */
    NODE_WHILE_LOOP,                /* while loop */
    NODE_FOR_LOOP,                  /* for loop */
    NODE_DO_WHILE,                  /* do-while loop */
    NODE_SWITCH_STATEMENT,          /* switch statement */
    NODE_CASE_LABEL,                /* case label */
    NODE_DEFAULT_LABEL,             /* default label */
    NODE_RETURN_STATEMENT,          /* return statement */
    NODE_BREAK_STATEMENT,           /* break statement */
    NODE_CONTINUE_STATEMENT,        /* continue statement */
    NODE_EXPRESSION_STATEMENT,      /* Expression as statement */
    
    /* Expressions */
    NODE_BINARY_OP,                 /* Binary operation (a + b) */
    NODE_UNARY_OP,                  /* Unary operation (-a, !a) */
    NODE_ASSIGNMENT,                /* Assignment (a = b) */
    NODE_FUNCTION_CALL,             /* Function call */
    NODE_ARRAY_ACCESS,              /* Array access (arr[i]) */
    NODE_MEMBER_ACCESS,             /* Member access (obj->member) */
    NODE_LITERAL_NUMBER,            /* Numeric literal */
    NODE_LITERAL_STRING,            /* String literal */
    NODE_LITERAL_ARRAY,             /* Array literal */
    NODE_LITERAL_MAPPING,           /* Mapping literal ([ key: value, ... ]) */
    NODE_IDENTIFIER,                /* Identifier */
    NODE_CAST,                      /* Type cast ((int)x) */
    
    /* Type nodes */
    NODE_TYPE_INT,                  /* int type */
    NODE_TYPE_STRING,               /* string type */
    NODE_TYPE_OBJECT,               /* object type */
    NODE_TYPE_MIXED,                /* mixed type */
    NODE_TYPE_VOID,                 /* void type */
    NODE_TYPE_MAPPING,              /* mapping type */
} ASTNodeType;

/* ========== AST Node Structures ========== */

/* Base AST node structure */
typedef struct ASTNode {
    ASTNodeType type;
    int line;
    int column;
    void *data;                     /* Type-specific data */
} ASTNode;

/* Program node - contains all top-level declarations */
typedef struct {
    ASTNode **declarations;         /* Array of declarations */
    int declaration_count;
    int capacity;
} ProgramNode;

/* Function declaration node */
typedef struct {
    char *return_type;              /* Return type (void, int, string, etc.) */
    char *name;                     /* Function name */
    struct {
        char *type;
        char *name;
    } *parameters;                  /* Function parameters */
    int parameter_count;
    ASTNode *body;                  /* Function body (block statement) */
    int is_private;                 /* 1 if private, 0 otherwise */
    int is_static;                  /* 1 if static, 0 otherwise */
} FunctionDeclNode;

/* Variable declaration node */
typedef struct {
    char *type;                     /* Variable type */
    char *name;                     /* Variable name */
    ASTNode *initializer;           /* Optional initializer expression */
    int is_static;
    int is_private;
} VariableDeclNode;

/* Block statement node */
typedef struct {
    ASTNode **statements;           /* Array of statements */
    int statement_count;
    int capacity;
} BlockNode;

/* If statement node */
typedef struct {
    ASTNode *condition;             /* Condition expression */
    ASTNode *then_statement;        /* Statement if condition is true */
    ASTNode *else_statement;        /* Optional else statement */
} IfStatementNode;

/* While loop node */
typedef struct {
    ASTNode *condition;
    ASTNode *body;
} WhileLoopNode;

/* For loop node */
typedef struct {
    ASTNode *initializer;           /* Variable declaration or expression */
    ASTNode *condition;
    ASTNode *increment;
    ASTNode *body;
} ForLoopNode;

/* Return statement node */
typedef struct {
    ASTNode *value;                 /* Optional return value expression */
} ReturnStatementNode;

/* Function call node */
typedef struct {
    char *function_name;            /* Name of function being called */
    ASTNode **arguments;            /* Array of argument expressions */
    int argument_count;
    int capacity;
} FunctionCallNode;

/* Binary operation node */
typedef struct {
    ASTNode *left;
    ASTNode *right;
    char *operator;                 /* Operator (+, -, *, /, etc.) */
} BinaryOpNode;

/* Unary operation node */
typedef struct {
    ASTNode *operand;
    char *operator;                 /* Operator (-, !, ~, etc.) */
    int is_prefix;                  /* 1 for prefix (++i), 0 for postfix (i++) */
} UnaryOpNode;

/* Assignment node */
typedef struct {
    ASTNode *target;                /* Assignment target (identifier, array access, etc.) */
    ASTNode *value;                 /* Value being assigned */
    char *operator;                 /* Assignment operator (=, +=, -=, etc.) */
} AssignmentNode;

/* Array access node */
typedef struct {
    ASTNode *array;                 /* Expression returning array */
    ASTNode *index;                 /* Index expression */
} ArrayAccessNode;

/* Member access node (object->member) */
typedef struct {
    ASTNode *object;
    char *member;
} MemberAccessNode;

/* Literal number node */
typedef struct {
    long int_value;
    double float_value;
    int is_float;
} LiteralNumberNode;

/* Literal string node */
typedef struct {
    char *value;
} LiteralStringNode;

/* Mapping literal node - represents ([ key: value, ... ]) */
typedef struct {
    ASTNode **keys;                 /* Array of key expressions */
    ASTNode **values;               /* Array of value expressions */
    int pair_count;
    int capacity;
} MappingLiteralNode;

/* Identifier node */
typedef struct {
    char *name;
} IdentifierNode;

/* ========== Parser Structure ========== */

typedef struct {
    Lexer *lexer;                   /* Lexer providing tokens */
    Token current_token;            /* Current token being parsed */
    Token previous_token;           /* Previous token (for error recovery) */
    int error_count;                /* Number of errors encountered */
    int error_recovery_mode;        /* 1 if in error recovery, 0 otherwise */
} Parser;

/* ========== Parser API Functions ========== */

/**
 * parser_init - Initialize a parser with a lexer
 * @lexer: Pointer to an initialized Lexer
 * 
 * Creates and initializes a Parser structure that will use the
 * provided lexer to tokenize and parse LPC source code.
 * 
 * Returns: Pointer to initialized Parser, or NULL on error
 */
Parser* parser_init(Lexer *lexer);

/**
 * parser_parse - Parse the entire LPC program
 * @parser: Pointer to the Parser
 * 
 * Parses the complete LPC source code and returns the root AST node
 * representing the entire program.
 * 
 * Returns: Pointer to root AST node (ProgramNode), or NULL on error
 */
ASTNode* parser_parse(Parser *parser);

/**
 * parser_free - Free all parser resources
 * @parser: Pointer to the Parser
 * 
 * Deallocates the parser structure and all associated AST nodes.
 */
void parser_free(Parser *parser);

/**
 * ast_node_free - Recursively free an AST node and its children
 * @node: Pointer to the ASTNode to free
 * 
 * Recursively frees the node and all its children.
 */
void ast_node_free(ASTNode *node);

/**
 * ast_node_to_string - Convert an AST node to its string representation
 * @type: The ASTNodeType to convert
 * 
 * Useful for debugging and printing AST information.
 * 
 * Returns: String name of the node type
 */
const char* ast_node_to_string(ASTNodeType type);

/**
 * parser_print_ast - Print the AST in a readable format
 * @node: Root node of the AST to print
 * @indent: Current indentation level (usually start with 0)
 * 
 * Recursively prints the AST with indentation showing the hierarchy.
 */
void parser_print_ast(ASTNode *node, int indent);

#endif /* PARSER_H */
