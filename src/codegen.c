/*
 * codegen.c - Code Generator Implementation
 * 
 * Implements AST-to-bytecode compilation for the AMLP driver.
 * This module walks the Abstract Syntax Tree and emits bytecode
 * instructions for execution by the Virtual Machine.
 */

#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========== Forward Declarations ========== */

static int codegen_compile_node(CodeGenerator *cg, ASTNode *node);

/* ========== Helper Functions ========== */

static void* xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Fatal: memory allocation failed\n");
        exit(1);
    }
    return ptr;
}

static void* xrealloc(void *ptr, size_t size) {
    ptr = realloc(ptr, size);
    if (!ptr) {
        fprintf(stderr, "Fatal: memory reallocation failed\n");
        exit(1);
    }
    return ptr;
}

static char* xstrdup(const char *str) {
    if (!str) return NULL;
    char *dup = xmalloc(strlen(str) + 1);
    strcpy(dup, str);
    return dup;
}

/* ========== Symbol Table Implementation ========== */

static unsigned int symbol_hash(const char *name) {
    unsigned int hash = 5381;
    for (int i = 0; name[i]; i++)
        hash = ((hash << 5) + hash) + (unsigned char)name[i];
    return hash;
}

SymbolTable* symbol_table_create(SymbolTable *parent) {
    SymbolTable *table = xmalloc(sizeof(SymbolTable));
    table->capacity = 64;
    table->size = 0;
    table->buckets = xmalloc(sizeof(Symbol*) * table->capacity);
    memset(table->buckets, 0, sizeof(Symbol*) * table->capacity);
    table->scope_depth = parent ? parent->scope_depth + 1 : 0;
    table->parent = parent;
    return table;
}

Symbol* symbol_table_add(SymbolTable *table, const char *name, 
                         SymbolType type, int index) {
    if (!table || !name) return NULL;
    
    unsigned int hash = symbol_hash(name) % table->capacity;
    Symbol *sym = xmalloc(sizeof(Symbol));
    sym->name = xstrdup(name);
    sym->type = type;
    sym->index = index;
    sym->scope_depth = table->scope_depth;
    
    sym->next = table->buckets[hash];
    table->buckets[hash] = sym;
    table->size++;
    return sym;
}

Symbol* symbol_table_lookup(SymbolTable *table, const char *name) {
    if (!table || !name) return NULL;
    
    SymbolTable *current = table;
    while (current) {
        unsigned int hash = symbol_hash(name) % current->capacity;
        Symbol *sym = current->buckets[hash];
        while (sym) {
            if (strcmp(sym->name, name) == 0)
                return sym;
            sym = sym->next;
        }
        current = current->parent;
    }
    return NULL;
}

void symbol_table_free(SymbolTable *table) {
    if (!table) return;
    for (int i = 0; i < table->capacity; i++) {
        Symbol *sym = table->buckets[i];
        while (sym) {
            Symbol *next = sym->next;
            free(sym->name);
            free(sym);
            sym = next;
        }
    }
    free(table->buckets);
    free(table);
}

/* ========== Code Generator Implementation ========== */

CodeGenerator* codegen_init(VirtualMachine *vm) {
    CodeGenerator *cg = xmalloc(sizeof(CodeGenerator));
    cg->vm = vm;
    cg->symbol_table = symbol_table_create(NULL);
    cg->current_function = NULL;
    cg->in_function = 0;
    cg->labels = xmalloc(sizeof(Label) * 64);
    cg->label_count = 0;
    cg->label_capacity = 64;
    cg->loop_start = -1;
    cg->loop_end = -1;
    cg->in_loop = 0;
    cg->error_count = 0;
    return cg;
}

void codegen_error(CodeGenerator *cg, const char *message) {
    if (cg) {
        cg->error_count++;
        fprintf(stderr, "Code Generation Error: %s\n", message);
    }
}

int codegen_get_current_address(CodeGenerator *cg) {
    if (!cg || !cg->current_function) return -1;
    return cg->current_function->instruction_count;
}

int codegen_emit_opcode(CodeGenerator *cg, OpCode opcode) {
    if (!cg || !cg->current_function) return -1;
    
    VMFunction *func = cg->current_function;
    if (func->instruction_count >= func->instruction_capacity) {
        func->instruction_capacity = func->instruction_capacity * 2 + 1;
        func->instructions = xrealloc(func->instructions, 
                                      sizeof(VMInstruction) * func->instruction_capacity);
    }
    
    int addr = func->instruction_count;
    func->instructions[addr].opcode = opcode;
    memset(&func->instructions[addr].operand, 0, sizeof(func->instructions[addr].operand));
    func->instruction_count++;
    return addr;
}

int codegen_emit_int(CodeGenerator *cg, OpCode opcode, long operand) {
    if (!cg || !cg->current_function) return -1;
    
    VMFunction *func = cg->current_function;
    if (func->instruction_count >= func->instruction_capacity) {
        func->instruction_capacity = func->instruction_capacity * 2 + 1;
        func->instructions = xrealloc(func->instructions, 
                                      sizeof(VMInstruction) * func->instruction_capacity);
    }
    
    int addr = func->instruction_count;
    func->instructions[addr].opcode = opcode;
    func->instructions[addr].operand.int_operand = operand;
    func->instruction_count++;
    return addr;
}

int codegen_emit_float(CodeGenerator *cg, OpCode opcode, double operand) {
    if (!cg || !cg->current_function) return -1;
    
    VMFunction *func = cg->current_function;
    if (func->instruction_count >= func->instruction_capacity) {
        func->instruction_capacity = func->instruction_capacity * 2 + 1;
        func->instructions = xrealloc(func->instructions, 
                                      sizeof(VMInstruction) * func->instruction_capacity);
    }
    
    int addr = func->instruction_count;
    func->instructions[addr].opcode = opcode;
    func->instructions[addr].operand.float_operand = operand;
    func->instruction_count++;
    return addr;
}

int codegen_emit_string(CodeGenerator *cg, OpCode opcode, const char *operand) {
    if (!cg || !cg->current_function) return -1;
    
    VMFunction *func = cg->current_function;
    if (func->instruction_count >= func->instruction_capacity) {
        func->instruction_capacity = func->instruction_capacity * 2 + 1;
        func->instructions = xrealloc(func->instructions, 
                                      sizeof(VMInstruction) * func->instruction_capacity);
    }
    
    int addr = func->instruction_count;
    func->instructions[addr].opcode = opcode;
    func->instructions[addr].operand.string_operand = xstrdup(operand);
    func->instruction_count++;
    return addr;
}

int codegen_create_label(CodeGenerator *cg, const char *name) {
    if (!cg) return -1;
    if (cg->label_count >= cg->label_capacity) {
        cg->label_capacity = cg->label_capacity * 2 + 1;
        cg->labels = xrealloc(cg->labels, sizeof(Label) * cg->label_capacity);
    }
    
    int idx = cg->label_count;
    cg->labels[idx].name = xstrdup(name);
    cg->labels[idx].address = -1;
    cg->labels[idx].patch_locations = xmalloc(sizeof(int) * 16);
    cg->labels[idx].patch_count = 0;
    cg->labels[idx].patch_capacity = 16;
    cg->label_count++;
    return idx;
}

int codegen_mark_label(CodeGenerator *cg, int label_index) {
    if (!cg || label_index < 0 || label_index >= cg->label_count) return -1;
    
    Label *label = &cg->labels[label_index];
    label->address = codegen_get_current_address(cg);
    
    /* Patch all forward references */
    for (int i = 0; i < label->patch_count; i++) {
        int patch_addr = label->patch_locations[i];
        cg->current_function->instructions[patch_addr].operand.address_operand = label->address;
    }
    label->patch_count = 0;
    return 0;
}

int codegen_emit_jump(CodeGenerator *cg, OpCode opcode, int label_index) {
    if (!cg || label_index < 0 || label_index >= cg->label_count) return -1;
    
    Label *label = &cg->labels[label_index];
    int addr = codegen_emit_int(cg, opcode, label->address);
    
    if (label->address == -1) {
        /* Forward reference - add to patch list */
        if (label->patch_count >= label->patch_capacity) {
            label->patch_capacity = label->patch_capacity * 2 + 1;
            label->patch_locations = xrealloc(label->patch_locations, 
                                               sizeof(int) * label->patch_capacity);
        }
        label->patch_locations[label->patch_count++] = addr;
    }
    return addr;
}

int codegen_patch_address(CodeGenerator *cg, int address, int target) {
    if (!cg || !cg->current_function) return -1;
    if (address < 0 || address >= cg->current_function->instruction_count) return -1;
    cg->current_function->instructions[address].operand.address_operand = target;
    return 0;
}

/* ========== AST Compilation ========== */

static int codegen_compile_binary_op(CodeGenerator *cg, BinaryOpNode *node) {
    if (!cg || !node) return -1;
    
    /* Compile left operand */
    ASTNode *left = (ASTNode*)node->left;
    if (codegen_compile_node(cg, left) < 0) return -1;
    
    /* Compile right operand */
    ASTNode *right = (ASTNode*)node->right;
    if (codegen_compile_node(cg, right) < 0) return -1;
    
    /* Emit appropriate operator instruction */
    if (strcmp(node->operator, "+") == 0) {
        codegen_emit_opcode(cg, OP_ADD);
    } else if (strcmp(node->operator, "-") == 0) {
        codegen_emit_opcode(cg, OP_SUB);
    } else if (strcmp(node->operator, "*") == 0) {
        codegen_emit_opcode(cg, OP_MUL);
    } else if (strcmp(node->operator, "/") == 0) {
        codegen_emit_opcode(cg, OP_DIV);
    } else if (strcmp(node->operator, "%") == 0) {
        codegen_emit_opcode(cg, OP_MOD);
    } else if (strcmp(node->operator, "==") == 0) {
        codegen_emit_opcode(cg, OP_EQ);
    } else if (strcmp(node->operator, "!=") == 0) {
        codegen_emit_opcode(cg, OP_NE);
    } else if (strcmp(node->operator, "<") == 0) {
        codegen_emit_opcode(cg, OP_LT);
    } else if (strcmp(node->operator, "<=") == 0) {
        codegen_emit_opcode(cg, OP_LE);
    } else if (strcmp(node->operator, ">") == 0) {
        codegen_emit_opcode(cg, OP_GT);
    } else if (strcmp(node->operator, ">=") == 0) {
        codegen_emit_opcode(cg, OP_GE);
    } else if (strcmp(node->operator, "&&") == 0) {
        codegen_emit_opcode(cg, OP_AND);
    } else if (strcmp(node->operator, "||") == 0) {
        codegen_emit_opcode(cg, OP_OR);
    } else if (strcmp(node->operator, "&") == 0) {
        codegen_emit_opcode(cg, OP_BIT_AND);
    } else if (strcmp(node->operator, "|") == 0) {
        codegen_emit_opcode(cg, OP_BIT_OR);
    } else if (strcmp(node->operator, "^") == 0) {
        codegen_emit_opcode(cg, OP_BIT_XOR);
    } else if (strcmp(node->operator, "<<") == 0) {
        codegen_emit_opcode(cg, OP_LSHIFT);
    } else if (strcmp(node->operator, ">>") == 0) {
        codegen_emit_opcode(cg, OP_RSHIFT);
    } else {
        codegen_error(cg, "Unknown binary operator");
        return -1;
    }
    return 0;
}

static int codegen_compile_unary_op(CodeGenerator *cg, UnaryOpNode *node) {
    if (!cg || !node) return -1;
    
    ASTNode *operand = (ASTNode*)node->operand;
    if (codegen_compile_node(cg, operand) < 0) return -1;
    
    if (strcmp(node->operator, "-") == 0) {
        codegen_emit_opcode(cg, OP_NEG);
    } else if (strcmp(node->operator, "!") == 0) {
        codegen_emit_opcode(cg, OP_NOT);
    } else if (strcmp(node->operator, "~") == 0) {
        codegen_emit_opcode(cg, OP_BIT_NOT);
    } else {
        codegen_error(cg, "Unknown unary operator");
        return -1;
    }
    return 0;
}

static int codegen_compile_assignment(CodeGenerator *cg, AssignmentNode *node) {
    if (!cg || !node) return -1;
    
    /* Compile the value being assigned */
    if (codegen_compile_node(cg, node->value) < 0) return -1;
    
    /* Handle target */
    if (node->target->type == NODE_IDENTIFIER) {
        IdentifierNode *ident = (IdentifierNode*)node->target->data;
        Symbol *sym = symbol_table_lookup(cg->symbol_table, ident->name);
        
        if (!sym) {
            /* Auto-create global variable */
            sym = symbol_table_add(cg->symbol_table, ident->name, SYMBOL_VARIABLE, 0);
        }
        
        if (sym->type == SYMBOL_VARIABLE) {
            codegen_emit_int(cg, OP_STORE_LOCAL, sym->index);
        }
    } else if (node->target->type == NODE_ARRAY_ACCESS) {
        ArrayAccessNode *arr = (ArrayAccessNode*)node->target->data;
        if (codegen_compile_node(cg, arr->array) < 0) return -1;
        if (codegen_compile_node(cg, arr->index) < 0) return -1;
        codegen_emit_opcode(cg, OP_STORE_ARRAY);
    }
    return 0;
}

static int codegen_compile_function_call(CodeGenerator *cg, FunctionCallNode *node) {
    if (!cg || !node) return -1;
    
    /* Compile arguments in order */
    for (int i = 0; i < node->argument_count; i++) {
        if (codegen_compile_node(cg, node->arguments[i]) < 0) return -1;
    }
    
    /* Look up function or emit call by name */
    Symbol *func_sym = symbol_table_lookup(cg->symbol_table, node->function_name);
    int func_idx = func_sym ? func_sym->index : -1;
    
    codegen_emit_int(cg, OP_CALL, func_idx);
    return 0;
}

static int codegen_compile_array_access(CodeGenerator *cg, ArrayAccessNode *node) {
    if (!cg || !node) return -1;
    
    if (codegen_compile_node(cg, node->array) < 0) return -1;
    if (codegen_compile_node(cg, node->index) < 0) return -1;
    codegen_emit_opcode(cg, OP_INDEX_ARRAY);
    return 0;
}

int codegen_compile_expression(CodeGenerator *cg, ASTNode *node) {
    if (!cg || !node) return -1;
    
    switch (node->type) {
        case NODE_LITERAL_NUMBER: {
            LiteralNumberNode *lit = (LiteralNumberNode*)node->data;
            if (lit->is_float) {
                codegen_emit_float(cg, OP_PUSH_FLOAT, lit->float_value);
            } else {
                codegen_emit_int(cg, OP_PUSH_INT, lit->int_value);
            }
            break;
        }
        
        case NODE_LITERAL_STRING: {
            LiteralStringNode *lit = (LiteralStringNode*)node->data;
            codegen_emit_string(cg, OP_PUSH_STRING, lit->value);
            break;
        }
        
        case NODE_LITERAL_MAPPING: {
            MappingLiteralNode *mapping = (MappingLiteralNode*)node->data;
            /* Push key-value pairs onto stack in reverse order */
            for (int i = mapping->pair_count - 1; i >= 0; i--) {
                /* Push key first, then value */
                if (codegen_compile_expression(cg, mapping->keys[i]) < 0) return -1;
                if (codegen_compile_expression(cg, mapping->values[i]) < 0) return -1;
            }
            /* Emit OP_MAKE_MAPPING with pair count */
            codegen_emit_int(cg, OP_MAKE_MAPPING, mapping->pair_count);
            break;
        }
        
        case NODE_IDENTIFIER: {
            IdentifierNode *ident = (IdentifierNode*)node->data;
            Symbol *sym = symbol_table_lookup(cg->symbol_table, ident->name);
            if (sym) {
                codegen_emit_int(cg, OP_LOAD_LOCAL, sym->index);
            } else {
                codegen_error(cg, "Undefined variable");
                return -1;
            }
            break;
        }
        
        case NODE_BINARY_OP: {
            BinaryOpNode *binop = (BinaryOpNode*)node->data;
            return codegen_compile_binary_op(cg, binop);
        }
        
        case NODE_UNARY_OP: {
            UnaryOpNode *unop = (UnaryOpNode*)node->data;
            return codegen_compile_unary_op(cg, unop);
        }
        
        case NODE_ASSIGNMENT: {
            AssignmentNode *assign = (AssignmentNode*)node->data;
            return codegen_compile_assignment(cg, assign);
        }
        
        case NODE_FUNCTION_CALL: {
            FunctionCallNode *call = (FunctionCallNode*)node->data;
            return codegen_compile_function_call(cg, call);
        }
        
        case NODE_ARRAY_ACCESS: {
            ArrayAccessNode *arr = (ArrayAccessNode*)node->data;
            return codegen_compile_array_access(cg, arr);
        }
        
        default:
            codegen_error(cg, "Unknown expression type");
            return -1;
    }
    return 0;
}

static int codegen_compile_variable_decl(CodeGenerator *cg, VariableDeclNode *node) {
    if (!cg || !node) return -1;
    
    /* Allocate local variable index */
    int var_idx = cg->current_function ? cg->current_function->local_var_count : 0;
    if (cg->current_function) cg->current_function->local_var_count++;
    
    symbol_table_add(cg->symbol_table, node->name, SYMBOL_VARIABLE, var_idx);
    
    /* Compile initializer if present */
    if (node->initializer) {
        if (codegen_compile_node(cg, node->initializer) < 0) return -1;
        codegen_emit_int(cg, OP_STORE_LOCAL, var_idx);
    }
    return 0;
}

static int codegen_compile_if_statement(CodeGenerator *cg, IfStatementNode *node) {
    if (!cg || !node) return -1;
    
    /* Compile condition */
    if (codegen_compile_node(cg, node->condition) < 0) return -1;
    
    /* Create label for else/end */
    int else_label = codegen_create_label(cg, "else");
    codegen_emit_jump(cg, OP_JUMP_IF_FALSE, else_label);
    
    /* Compile then block */
    if (codegen_compile_node(cg, node->then_statement) < 0) return -1;
    
    if (node->else_statement) {
        int end_label = codegen_create_label(cg, "end_if");
        codegen_emit_jump(cg, OP_JUMP, end_label);
        
        codegen_mark_label(cg, else_label);
        if (codegen_compile_node(cg, node->else_statement) < 0) return -1;
        codegen_mark_label(cg, end_label);
    } else {
        codegen_mark_label(cg, else_label);
    }
    return 0;
}

static int codegen_compile_while_loop(CodeGenerator *cg, WhileLoopNode *node) {
    if (!cg || !node) return -1;
    
    int loop_start = codegen_create_label(cg, "loop_start");
    int loop_end = codegen_create_label(cg, "loop_end");
    
    int prev_loop_start = cg->loop_start;
    int prev_loop_end = cg->loop_end;
    int prev_in_loop = cg->in_loop;
    
    cg->loop_start = loop_start;
    cg->loop_end = loop_end;
    cg->in_loop = 1;
    
    /* Mark loop start */
    codegen_mark_label(cg, loop_start);
    
    /* Compile condition */
    if (codegen_compile_node(cg, node->condition) < 0) return -1;
    
    /* Jump to end if condition is false */
    codegen_emit_jump(cg, OP_JUMP_IF_FALSE, loop_end);
    
    /* Compile body */
    if (codegen_compile_node(cg, node->body) < 0) return -1;
    
    /* Jump back to start */
    codegen_emit_jump(cg, OP_JUMP, loop_start);
    
    /* Mark loop end */
    codegen_mark_label(cg, loop_end);
    
    cg->loop_start = prev_loop_start;
    cg->loop_end = prev_loop_end;
    cg->in_loop = prev_in_loop;
    return 0;
}

static int codegen_compile_return_statement(CodeGenerator *cg, ReturnStatementNode *node) {
    if (!cg || !node) return -1;
    
    if (node->value) {
        if (codegen_compile_node(cg, node->value) < 0) return -1;
    } else {
        codegen_emit_opcode(cg, OP_PUSH_NULL);
    }
    
    codegen_emit_opcode(cg, OP_RETURN);
    return 0;
}

static int codegen_compile_block(CodeGenerator *cg, BlockNode *node) {
    if (!cg || !node) return -1;
    
    /* Enter new scope */
    SymbolTable *prev_table = cg->symbol_table;
    cg->symbol_table = symbol_table_create(prev_table);
    
    /* Compile all statements */
    for (int i = 0; i < node->statement_count; i++) {
        if (codegen_compile_node(cg, node->statements[i]) < 0) {
            symbol_table_free(cg->symbol_table);
            cg->symbol_table = prev_table;
            return -1;
        }
    }
    
    /* Exit scope */
    symbol_table_free(cg->symbol_table);
    cg->symbol_table = prev_table;
    return 0;
}

int codegen_compile_statement(CodeGenerator *cg, ASTNode *node) {
    if (!cg || !node) return -1;
    
    switch (node->type) {
        case NODE_VARIABLE_DECL: {
            VariableDeclNode *decl = (VariableDeclNode*)node->data;
            return codegen_compile_variable_decl(cg, decl);
        }
        
        case NODE_IF_STATEMENT: {
            IfStatementNode *ifstmt = (IfStatementNode*)node->data;
            return codegen_compile_if_statement(cg, ifstmt);
        }
        
        case NODE_WHILE_LOOP: {
            WhileLoopNode *whilestmt = (WhileLoopNode*)node->data;
            return codegen_compile_while_loop(cg, whilestmt);
        }
        
        case NODE_RETURN_STATEMENT: {
            ReturnStatementNode *ret = (ReturnStatementNode*)node->data;
            return codegen_compile_return_statement(cg, ret);
        }
        
        case NODE_BLOCK: {
            BlockNode *block = (BlockNode*)node->data;
            return codegen_compile_block(cg, block);
        }
        
        case NODE_EXPRESSION_STATEMENT: {
            ASTNode *expr = (ASTNode*)node->data;
            if (codegen_compile_node(cg, expr) < 0) return -1;
            codegen_emit_opcode(cg, OP_POP);
            break;
        }
        
        default:
            /* Try to compile as expression */
            return codegen_compile_expression(cg, node);
    }
    return 0;
}

static int codegen_compile_node(CodeGenerator *cg, ASTNode *node) {
    if (!cg || !node) return -1;
    
    /* Dispatch based on node type */
    if (node->type >= NODE_BLOCK && node->type <= NODE_EXPRESSION_STATEMENT) {
        return codegen_compile_statement(cg, node);
    } else {
        return codegen_compile_expression(cg, node);
    }
}

int codegen_compile_function(CodeGenerator *cg, ASTNode *node) {
    if (!cg || !node) return -1;
    if (node->type != NODE_FUNCTION_DECL) return -1;
    
    FunctionDeclNode *func_decl = (FunctionDeclNode*)node->data;
    
    /* Create function */
    VMFunction *func = xmalloc(sizeof(VMFunction));
    func->name = xstrdup(func_decl->name);
    func->param_count = func_decl->parameter_count;
    func->local_var_count = func_decl->parameter_count;
    func->instructions = xmalloc(sizeof(VMInstruction) * 256);
    func->instruction_count = 0;
    func->instruction_capacity = 256;
    
    /* Set as current function for code generation */
    VMFunction *prev_func = cg->current_function;
    cg->current_function = func;
    int prev_in_func = cg->in_function;
    cg->in_function = 1;
    
    /* Add parameters to symbol table */
    for (int i = 0; i < func_decl->parameter_count; i++) {
        symbol_table_add(cg->symbol_table, func_decl->parameters[i].name, 
                        SYMBOL_PARAMETER, i);
    }
    
    /* Compile function body */
    if (codegen_compile_node(cg, func_decl->body) < 0) {
        /* Error compiling function */
        free(func->name);
        free(func->instructions);
        free(func);
        cg->current_function = prev_func;
        cg->in_function = prev_in_func;
        return -1;
    }
    
    /* Ensure function ends with return */
    if (func->instruction_count == 0 || 
        func->instructions[func->instruction_count - 1].opcode != OP_RETURN) {
        codegen_emit_opcode(cg, OP_PUSH_NULL);
        codegen_emit_opcode(cg, OP_RETURN);
    }
    
    /* Add function to VM */
    int func_idx = vm_add_function(cg->vm, func);
    
    /* Restore previous function */
    cg->current_function = prev_func;
    cg->in_function = prev_in_func;
    
    return func_idx;
}

int codegen_compile(CodeGenerator *cg, ASTNode *ast) {
    if (!cg || !ast) return -1;
    
    /* Create main function for top-level code */
    VMFunction *main_func = xmalloc(sizeof(VMFunction));
    main_func->name = xstrdup("main");
    main_func->param_count = 0;
    main_func->local_var_count = 0;
    main_func->instructions = xmalloc(sizeof(VMInstruction) * 1024);
    main_func->instruction_count = 0;
    main_func->instruction_capacity = 1024;
    
    cg->current_function = main_func;
    cg->in_function = 1;
    
    /* Process program node */
    if (ast->type == NODE_PROGRAM) {
        ProgramNode *prog = (ProgramNode*)ast->data;
        
        /* First pass: register all functions */
        for (int i = 0; i < prog->declaration_count; i++) {
            if (prog->declarations[i]->type == NODE_FUNCTION_DECL) {
                codegen_compile_function(cg, prog->declarations[i]);
            }
        }
        
        /* Second pass: compile top-level statements */
        for (int i = 0; i < prog->declaration_count; i++) {
            if (prog->declarations[i]->type != NODE_FUNCTION_DECL) {
                if (codegen_compile_node(cg, prog->declarations[i]) < 0) {
                    cg->error_count++;
                }
            }
        }
    } else {
        if (codegen_compile_node(cg, ast) < 0) {
            cg->error_count++;
        }
    }
    
    /* Ensure main ends with halt */
    codegen_emit_opcode(cg, OP_HALT);
    
    /* Load main function's bytecode into VM */
    vm_load_bytecode(cg->vm, main_func->instructions, main_func->instruction_count);
    
    if (cg->error_count > 0) return -1;
    return 0;
}

/* Public wrapper for expression compilation */
int codegen_compile_expression_public(CodeGenerator *cg, ASTNode *node) {
    return codegen_compile_expression(cg, node);
}

/* Public wrapper for statement compilation */
int codegen_compile_statement_public(CodeGenerator *cg, ASTNode *node) {
    return codegen_compile_statement(cg, node);
}

void codegen_free(CodeGenerator *cg) {
    if (!cg) return;
    
    symbol_table_free(cg->symbol_table);
    
    for (int i = 0; i < cg->label_count; i++) {
        free(cg->labels[i].name);
        free(cg->labels[i].patch_locations);
    }
    free(cg->labels);
    
    if (cg->current_function) {
        free(cg->current_function->name);
        free(cg->current_function->instructions);
        free(cg->current_function);
    }
    
    free(cg);
}
