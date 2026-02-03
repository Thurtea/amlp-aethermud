/*
 * codegen.h - Code Generator Header
 * 
 * This header defines the code generator that compiles Abstract Syntax Trees
 * (AST) produced by the parser into bytecode for the Virtual Machine.
 * 
 * The code generator performs:
 * - AST traversal and bytecode emission
 * - Symbol table management for variables and functions
 * - Label resolution for jumps and branches
 * - Constant pooling for strings and literals
 */

#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"
#include "vm.h"

/* ========== Symbol Table ========== */

typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_PARAMETER,
} SymbolType;

typedef struct Symbol {
    char *name;
    SymbolType type;
    int index;              /* Variable index or function index */
    int scope_depth;        /* For nested scopes */
    struct Symbol *next;    /* For hash table chaining */
} Symbol;

typedef struct SymbolTable {
    Symbol **buckets;
    int capacity;
    int size;
    int scope_depth;
    struct SymbolTable *parent;  /* For nested scopes */
} SymbolTable;

/* ========== Label Management ========== */

typedef struct Label {
    char *name;
    int address;            /* -1 if not yet resolved */
    int *patch_locations;   /* Addresses that need to be patched */
    int patch_count;
    int patch_capacity;
} Label;

/* ========== Code Generator ========== */

typedef struct {
    VirtualMachine *vm;
    SymbolTable *symbol_table;
    
    /* Current function being compiled */
    VMFunction *current_function;
    int in_function;
    
    /* Label management for jumps */
    Label *labels;
    int label_count;
    int label_capacity;
    
    /* Loop context for break/continue */
    int loop_start;
    int loop_end;
    int in_loop;

    /* Break/continue target stacks */
    int *break_stack;
    int break_depth;
    int break_capacity;
    int *continue_stack;
    int continue_depth;
    int continue_capacity;
    
    /* Error tracking */
    int error_count;
} CodeGenerator;

/* ========== Code Generator API ========== */

/**
 * codegen_init - Initialize a new code generator
 * @vm: The virtual machine to generate code for
 * 
 * Creates and initializes a CodeGenerator structure.
 * 
 * Returns: Pointer to initialized code generator, or NULL on error
 */
CodeGenerator* codegen_init(VirtualMachine *vm);

/**
 * codegen_compile - Compile an AST into bytecode
 * @codegen: The code generator
 * @ast: Root AST node to compile
 * 
 * Compiles the entire AST into bytecode and loads it into the VM.
 * 
 * Returns: 0 on success, -1 on error
 */
int codegen_compile(CodeGenerator *codegen, ASTNode *ast);

/**
 * codegen_compile_statement - Compile a single statement
 * @codegen: The code generator
 * @node: Statement AST node
 * 
 * Compiles a statement and emits appropriate bytecode.
 * 
 * Returns: 0 on success, -1 on error
 */
int codegen_compile_statement(CodeGenerator *codegen, ASTNode *node);

/**
 * codegen_compile_expression - Compile an expression
 * @codegen: The code generator
 * @node: Expression AST node
 * 
 * Compiles an expression and emits bytecode that leaves
 * the result value on the stack.
 * 
 * Returns: 0 on success, -1 on error
 */
int codegen_compile_expression(CodeGenerator *codegen, ASTNode *node);

/**
 * codegen_compile_function - Compile a function definition
 * @codegen: The code generator
 * @node: Function declaration AST node
 * 
 * Compiles a function definition into a VMFunction.
 * 
 * Returns: Function index on success, -1 on error
 */
int codegen_compile_function(CodeGenerator *codegen, ASTNode *node);

/**
 * codegen_free - Free code generator resources
 * @codegen: The code generator to free
 */
void codegen_free(CodeGenerator *codegen);

/* ========== Bytecode Emission ========== */

/**
 * codegen_emit - Emit a bytecode instruction
 * @codegen: The code generator
 * @instruction: The instruction to emit
 * 
 * Emits an instruction to the current code section (top-level or function).
 * 
 * Returns: Address of emitted instruction, or -1 on error
 */
int codegen_emit(CodeGenerator *codegen, VMInstruction instruction);

/**
 * codegen_emit_opcode - Emit a simple opcode with no operand
 * @codegen: The code generator
 * @opcode: The opcode to emit
 * 
 * Returns: Address of emitted instruction, or -1 on error
 */
int codegen_emit_opcode(CodeGenerator *codegen, OpCode opcode);

/**
 * codegen_emit_int - Emit an instruction with an integer operand
 * @codegen: The code generator
 * @opcode: The opcode to emit
 * @operand: Integer operand
 * 
 * Returns: Address of emitted instruction, or -1 on error
 */
int codegen_emit_int(CodeGenerator *codegen, OpCode opcode, long operand);

/**
 * codegen_emit_float - Emit an instruction with a float operand
 * @codegen: The code generator
 * @opcode: The opcode to emit
 * @operand: Float operand
 * 
 * Returns: Address of emitted instruction, or -1 on error
 */
int codegen_emit_float(CodeGenerator *codegen, OpCode opcode, double operand);

/**
 * codegen_emit_string - Emit an instruction with a string operand
 * @codegen: The code generator
 * @opcode: The opcode to emit
 * @operand: String operand
 * 
 * Returns: Address of emitted instruction, or -1 on error
 */
int codegen_emit_string(CodeGenerator *codegen, OpCode opcode, const char *operand);

/**
 * codegen_patch_address - Patch a jump address after label resolution
 * @codegen: The code generator
 * @address: Address of instruction to patch
 * @target: Target address to patch in
 * 
 * Returns: 0 on success, -1 on error
 */
int codegen_patch_address(CodeGenerator *codegen, int address, int target);

/* ========== Symbol Table Operations ========== */

/**
 * symbol_table_create - Create a new symbol table
 * @parent: Parent symbol table (NULL for global scope)
 * 
 * Returns: Pointer to new symbol table, or NULL on error
 */
SymbolTable* symbol_table_create(SymbolTable *parent);

/**
 * symbol_table_add - Add a symbol to the table
 * @table: The symbol table
 * @name: Symbol name
 * @type: Symbol type
 * @index: Symbol index
 * 
 * Returns: Pointer to added symbol, or NULL on error
 */
Symbol* symbol_table_add(SymbolTable *table, const char *name, 
                         SymbolType type, int index);

/**
 * symbol_table_lookup - Look up a symbol by name
 * @table: The symbol table
 * @name: Symbol name
 * 
 * Searches the table and parent tables for the symbol.
 * 
 * Returns: Pointer to symbol, or NULL if not found
 */
Symbol* symbol_table_lookup(SymbolTable *table, const char *name);

/**
 * symbol_table_free - Free a symbol table
 * @table: The symbol table to free
 */
void symbol_table_free(SymbolTable *table);

/* ========== Label Operations ========== */

/**
 * codegen_create_label - Create a new label
 * @codegen: The code generator
 * @name: Label name
 * 
 * Returns: Label index, or -1 on error
 */
int codegen_create_label(CodeGenerator *codegen, const char *name);

/**
 * codegen_mark_label - Mark the current position with a label
 * @codegen: The code generator
 * @label_index: Index of label to mark
 * 
 * Sets the label's address to the current instruction position
 * and patches all forward references.
 * 
 * Returns: 0 on success, -1 on error
 */
int codegen_mark_label(CodeGenerator *codegen, int label_index);

/**
 * codegen_emit_jump - Emit a jump to a label
 * @codegen: The code generator
 * @opcode: Jump opcode (OP_JUMP, OP_JUMP_IF_FALSE, etc.)
 * @label_index: Index of target label
 * 
 * If label is not yet resolved, adds a forward reference to be patched.
 * 
 * Returns: Address of jump instruction, or -1 on error
 */
int codegen_emit_jump(CodeGenerator *codegen, OpCode opcode, int label_index);

/* ========== Utility Functions ========== */

/**
 * codegen_get_current_address - Get current instruction address
 * @codegen: The code generator
 * 
 * Returns: Current instruction address
 */
int codegen_get_current_address(CodeGenerator *codegen);

/**
 * codegen_error - Report a code generation error
 * @codegen: The code generator
 * @message: Error message
 */
void codegen_error(CodeGenerator *codegen, const char *message);

#endif /* CODEGEN_H */
