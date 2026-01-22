/*
 * lexer.h - Lexical Analyzer Header
 * 
 * This header defines the token types, token structure, and the Lexer structure
 * used for tokenizing LPC source code. The lexer converts raw source code into
 * a stream of tokens that can be parsed by the parser.
 */

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========== Token Types ========== */

typedef enum {
    /* Literals */
    TOKEN_IDENTIFIER,           /* Variable, function, or object names */
    TOKEN_NUMBER,               /* Integer literals (0-9+) */
    TOKEN_FLOAT,                /* Floating point literals */
    TOKEN_STRING,               /* String literals ("...") */
    
    /* Keywords */
    TOKEN_KEYWORD,              /* Reserved keywords (if, while, void, etc.) */
    
    /* Operators */
    TOKEN_OPERATOR,             /* Operators (+, -, *, /, etc.) */
    
    /* Delimiters */
    TOKEN_LPAREN,               /* ( */
    TOKEN_RPAREN,               /* ) */
    TOKEN_LBRACE,               /* { */
    TOKEN_RBRACE,               /* } */
    TOKEN_LBRACKET,             /* [ */
    TOKEN_RBRACKET,             /* ] */
    TOKEN_SEMICOLON,            /* ; */
    TOKEN_COMMA,                /* , */
    TOKEN_DOT,                  /* . */
    TOKEN_COLON,                /* : */
    
    /* Special */
    TOKEN_EOF,                  /* End of file */
    TOKEN_ERROR                 /* Lexical error */
} TokenType;

/* ========== Token Structure ========== */

typedef struct {
    TokenType type;             /* Type of token */
    char *value;                /* String representation of token */
    int line_number;            /* Line where token appears */
    int column_number;          /* Column where token starts */
} Token;

/* ========== Lexer Structure ========== */

typedef struct {
    char *buffer;               /* Complete source code buffer */
    int buffer_size;            /* Total buffer size */
    int position;               /* Current position in buffer */
    int line_number;            /* Current line number */
    int column_number;          /* Current column number */
    int token_count;            /* Total tokens processed */
} Lexer;

/* ========== Lexer API Functions ========== */

/**
 * lexer_init - Initialize a lexer from a file
 * @filename: Path to the LPC source file to tokenize
 * 
 * Allocates and initializes a Lexer structure, reads the entire file
 * into memory, and prepares it for tokenization.
 * 
 * Returns: Pointer to initialized Lexer, or NULL on error
 */
Lexer* lexer_init(const char *filename);

/**
 * lexer_init_from_string - Initialize a lexer from a string buffer
 * @source: String containing LPC source code
 * 
 * Allocates and initializes a Lexer structure from an in-memory string.
 * Useful for testing or dynamically loaded code.
 * 
 * Returns: Pointer to initialized Lexer, or NULL on error
 */
Lexer* lexer_init_from_string(const char *source);

/**
 * lexer_get_next_token - Get the next token from the lexer
 * @lexer: Pointer to the Lexer structure
 * 
 * Advances the lexer position and returns the next token from the input.
 * Automatically skips whitespace and handles line number tracking.
 * 
 * Returns: Token structure containing token type, value, and position info
 */
Token lexer_get_next_token(Lexer *lexer);

/**
 * lexer_peek_token - Peek at the next token without consuming it
 * @lexer: Pointer to the Lexer structure
 * 
 * Returns the next token without advancing the lexer position.
 * Useful for lookahead parsing.
 * 
 * Returns: Token structure of the next token
 */
Token lexer_peek_token(Lexer *lexer);

/**
 * lexer_reset - Reset the lexer to the beginning
 * @lexer: Pointer to the Lexer structure
 * 
 * Resets the position, line number, and column number to their initial values.
 * Allows re-tokenization of the same source code.
 */
void lexer_reset(Lexer *lexer);

/**
 * lexer_free - Free all lexer resources
 * @lexer: Pointer to the Lexer structure
 * 
 * Deallocates the lexer structure and its associated buffers.
 * Should be called when tokenization is complete.
 */
void lexer_free(Lexer *lexer);

/**
 * token_type_to_string - Convert a token type to its string representation
 * @type: TokenType to convert
 * 
 * Useful for debugging and error messages.
 * 
 * Returns: String name of the token type
 */
const char* token_type_to_string(TokenType type);

#endif /* LEXER_H */
