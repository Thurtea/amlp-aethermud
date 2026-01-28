# AMLP Driver - Development Guide

Detailed technical documentation for the AMLP Driver implementation.

## Table of Contents

- [Component Details](#component-details)
- [Phase History](#phase-history)
- [Roadmap](#roadmap)
- [Compiler Configuration](#compiler-configuration)
- [Build System](#build-system)

## Component Details

### Lexer (`lexer.h`, `lexer.c`) - Phase 1

**Lines:** 140 (header) + 550 (implementation)

**Features:**
- 50+ token types for full LPC syntax
- Line/column tracking for error reporting
- Comment handling (// and /* */)
- Float literals with scientific notation
- String escape sequences
- Multi-character operators (==, !=, <=, >=, ++, --, &&, ||, etc.)
- Keyword recognition (20+ keywords)

**Token Types:**
```
TOKEN_INT, TOKEN_FLOAT, TOKEN_STRING, TOKEN_IDENTIFIER
TOKEN_IF, TOKEN_ELSE, TOKEN_WHILE, TOKEN_FOR, TOKEN_DO
TOKEN_RETURN, TOKEN_BREAK, TOKEN_CONTINUE, TOKEN_SWITCH, TOKEN_CASE
TOKEN_PLUS, TOKEN_MINUS, TOKEN_MULTIPLY, TOKEN_DIVIDE
TOKEN_EQUAL, TOKEN_NOT_EQUAL, TOKEN_LESS, TOKEN_GREATER
TOKEN_AND, TOKEN_OR, TOKEN_NOT, TOKEN_ASSIGN
```

### Parser (`parser.h`, `parser.c`) - Phase 2

**Lines:** 280 (header) + 1000 (implementation)

**Features:**
- Recursive descent with operator precedence
- 25+ AST node types
- Full declaration support (functions, variables, inheritance)
- Control structures (if/else, while, for, do-while, switch)
- Expression parsing with correct associativity
- Function calls, array/object access
- Error recovery and detailed diagnostics

**AST Node Types:**
```
NODE_PROGRAM, NODE_FUNCTION_DECL, NODE_VAR_DECL
NODE_IF_STMT, NODE_WHILE_STMT, NODE_FOR_STMT
NODE_RETURN_STMT, NODE_EXPR_STMT
NODE_BINARY_OP, NODE_UNARY_OP
NODE_INT_LITERAL, NODE_FLOAT_LITERAL, NODE_STRING_LITERAL
NODE_IDENTIFIER, NODE_ARRAY_ACCESS, NODE_FUNCTION_CALL
```

### Code Generator (`codegen.h`, `codegen.c`) - Phase 3

**Features:**
- AST -> bytecode compilation
- Constant pool management
- Jump label resolution
- Opcode optimization
- Symbol table management

**Constant Pool:**
- Integers
- Floats
- Strings
- Function references

**Symbol Tables:**
- Global variables
- Local variables (per-function scope)
- Function symbols

### Virtual Machine (`vm.h`, `vm.c`) - Phase 3-5

**Lines:** 150 (header) + 120 (implementation)

**Architecture:**
- Stack-based execution model
- 1024-element value stack
- Call frame management
- Local/global variable storage
- GC integration

**Value Types:**
```c
typedef enum {
    VALUE_NULL,
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_STRING,
    VALUE_OBJECT,
    VALUE_ARRAY,
    VALUE_MAPPING
} ValueType;

typedef struct {
    ValueType type;
    union {
        long int_val;
        double float_val;
        char* string_val;
        Object* object_val;
        array_t* array_val;
        mapping_t* mapping_val;
    };
} VMValue;
```

**Opcodes (40+):**
```
OP_PUSH_INT, OP_PUSH_FLOAT, OP_PUSH_STRING, OP_PUSH_NULL
OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD
OP_EQ, OP_NE, OP_LT, OP_GT, OP_LE, OP_GE
OP_AND, OP_OR, OP_NOT
OP_JUMP, OP_JUMP_IF_FALSE, OP_JUMP_IF_TRUE
OP_CALL, OP_RETURN
OP_LOAD_LOCAL, OP_STORE_LOCAL
OP_LOAD_GLOBAL, OP_STORE_GLOBAL
OP_NEW_ARRAY, OP_ARRAY_GET, OP_ARRAY_SET, OP_ARRAY_PUSH
OP_NEW_MAPPING, OP_MAPPING_GET, OP_MAPPING_SET
OP_CALL_EFUN
```

### Object System (`object.h`, `object.c`) - Phase 4

**Features:**
- Object creation/destruction
- Method registration and dispatch
- Function storage
- Object registry
- Method call stack

**Object Structure:**
```c
typedef struct Object {
    int id;
    char* name;
    Function** methods;
    int method_count;
    int method_capacity;
    struct Object* parent;
} Object;
```

**API:**
```c
Object* object_new(const char* name);
void object_free(Object* obj);
void object_add_method(Object* obj, Function* func);
Function* object_get_method(Object* obj, const char* name);
VMValue object_call_method(Object* obj, const char* name, VMValue* args, int arg_count);
```

### Garbage Collector (`gc.h`, `gc.c`) - Phase 5

**Features:**
- Reference counting
- Mark-and-sweep collection
- Type-specific tracking (objects, arrays, mappings, strings)
- Auto-collection threshold
- Memory leak detection
- Full statistics

**Tracked Types:**
- Objects (via object registry)
- Arrays (via array pool)
- Mappings (via mapping pool)
- Strings (via string pool)

**GC API:**
```c
void gc_init(void);
void gc_register_object(Object* obj);
void gc_register_array(array_t* arr);
void gc_register_mapping(mapping_t* map);
void gc_register_string(char* str);
void gc_collect(void);
void gc_print_stats(void);
```

**Collection Algorithm:**
1. Mark phase: Traverse reachable objects from roots
2. Sweep phase: Free unmarked objects
3. Reset marks for next cycle

### Efun System (`efun.h`, `efun.c`) - Phase 5

**24 Built-in Functions:**

**String Functions:**
- `int strlen(string str)` - String length
- `string substring(string str, int start, int len)` - Extract substring
- `string* explode(string str, string delimiter)` - Split string into array
- `string implode(string* arr, string glue)` - Join array into string
- `string upper_case(string str)` - Convert to uppercase
- `string lower_case(string str)` - Convert to lowercase
- `string trim(string str)` - Remove leading/trailing whitespace

**Array Functions:**
- `int sizeof(mixed* arr)` - Array/mapping size
- `int arrayp(mixed val)` - Check if value is array
- `mixed* sort_array(mixed* arr)` - Sort array (ascending)
- `mixed* reverse_array(mixed* arr)` - Reverse array order

**Math Functions:**
- `int abs(int n)` - Absolute value
- `float sqrt(float n)` - Square root
- `float pow(float base, float exp)` - Power function
- `int random(int max)` - Random number [0, max)
- `int min(int a, int b)` - Minimum of two values
- `int max(int a, int b)` - Maximum of two values

**Type Checking:**
- `int intp(mixed val)` - Check if integer
- `int floatp(mixed val)` - Check if float
- `int stringp(mixed val)` - Check if string
- `int objectp(mixed val)` - Check if object
- `int mappingp(mixed val)` - Check if mapping

**I/O Functions:**
- `void write(string str)` - Output string
- `void printf(string fmt, ...)` - Formatted output

### Array Module (`array.h`, `array.c`) - Phase 6

**Features:**
- GC-aware dynamic arrays
- Automatic capacity growth (2x on overflow)
- Deep cloning with type preservation
- Bounds checking
- Mixed type storage

**Structure:**
```c
typedef struct {
    VMValue* elements;
    int size;
    int capacity;
} array_t;
```

**API:**
```c
array_t* array_new(void);
void array_free(array_t* arr);
void array_push(array_t* arr, VMValue value);
VMValue array_pop(array_t* arr);
VMValue array_get(array_t* arr, int index);
void array_set(array_t* arr, int index, VMValue value);
void array_insert(array_t* arr, int index, VMValue value);
void array_delete(array_t* arr, int index);
array_t* array_clone(array_t* arr);
```

### Mapping Module (`mapping.h`, `mapping.c`) - Phase 6

**Features:**
- GC-aware hash maps
- Collision handling via chaining
- String keys, VMValue values
- Deep cloning
- Size tracking

**Structure:**
```c
typedef struct MappingEntry {
    char* key;
    VMValue value;
    struct MappingEntry* next;
} MappingEntry;

typedef struct {
    MappingEntry** buckets;
    int capacity;
    int size;
} mapping_t;
```

**API:**
```c
mapping_t* mapping_new(void);
void mapping_free(mapping_t* map);
void mapping_set(mapping_t* map, const char* key, VMValue value);
VMValue mapping_get(mapping_t* map, const char* key);
void mapping_delete(mapping_t* map, const char* key);
char** mapping_keys(mapping_t* map);
VMValue* mapping_values(mapping_t* map);
mapping_t* mapping_clone(mapping_t* map);
```

## Phase History

### Phase 1: Lexical Analysis (Complete)
**Tests:** 20 tests, 41 assertions

**Implemented:**
- Full LPC token support (50+ types)
- Line/column tracking
- Comment handling
- String escape sequences
- Multi-character operators
- Keyword recognition

**Test Coverage:**
- Basic tokenization
- String literals with escapes
- Float literals (including scientific notation)
- Multi-character operators
- Comments (single-line and multi-line)
- Error handling

### Phase 2: Syntax Analysis (Complete)
**Tests:** 40 tests, 97 assertions

**Implemented:**
- Recursive descent parser
- 25+ AST node types
- Operator precedence handling
- Control flow structures
- Function declarations
- Expression parsing

**Test Coverage:**
- Variable declarations
- Function declarations
- Control structures (if/else, while, for)
- Binary/unary expressions
- Function calls
- Array/object access
- Error recovery

### Phase 3: VM Architecture & Bytecode (Complete)
**Tests:** 47 tests, 146 assertions

**Implemented:**
- Stack-based VM
- 40+ opcodes
- Code generator (AST -> bytecode)
- Constant pool
- Symbol tables
- Jump resolution

**Test Coverage:**
- Arithmetic operations
- Logical operations
- Control flow (jumps, conditionals)
- Function calls
- Variable access (local/global)
- Stack operations

### Phase 4: Object System (Complete)
**Tests:** 16 tests, 33 assertions

**Implemented:**
- Object creation/destruction
- Method registration
- Method dispatch
- Object registry
- Inheritance (basic)

**Test Coverage:**
- Object creation
- Method registration
- Method calls
- Object hierarchy
- Memory management

### Phase 5: Garbage Collection & Efuns (Complete)
**Tests:** 51 tests (GC: 23, Efun: 28), 109 assertions

**Implemented:**
- Reference-counted GC
- Mark-and-sweep algorithm
- Type-specific tracking
- 24 built-in functions
- Automatic collection

**Test Coverage:**
- Object lifecycle
- String management
- Array/mapping tracking
- Collection triggers
- Memory leak detection
- All 24 efuns

### Phase 6: Arrays & Mappings (Complete)
**Tests:** 46 tests (Array: 23, Mapping: 23), 139 assertions

**Implemented:**
- Dynamic arrays with GC integration
- Hash maps with collision handling
- Deep cloning
- Enhanced efuns (explode, implode, sort, reverse)

**Test Coverage:**
- Array operations (push, pop, get, set, insert, delete)
- Mapping operations (set, get, delete, keys, values)
- GC integration
- Clone operations
- Bounds checking

## Roadmap

### Phase 7: Advanced Control Flow (Planned)
**Goals:**
- Function call stack with local scopes
- Return value handling
- Nested function calls
- Stack frame management
- Proper scope chain

**Tasks:**
- Implement call frames
- Add scope resolution
- Support nested calls
- Handle return values
- Add tail call optimization

### Phase 8: Inheritance System (Planned)
**Goals:**
- Multiple inheritance
- Virtual method resolution
- Super calls
- Access control (public/private/protected)

**Tasks:**
- Implement method resolution order (MRO)
- Add virtual dispatch
- Support super keyword
- Implement access modifiers
- Add interface support

### Phase 9: Advanced Efuns (Planned)
**Goals:**
- filter_array, map_array, member_array
- String interpolation
- Regular expressions
- File I/O operations

**New Efuns:**
- `filter_array(mixed* arr, function func)`
- `map_array(mixed* arr, function func)`
- `member_array(mixed val, mixed* arr)`
- `regexp(string pattern, string str)`
- `read_file(string path)`
- `write_file(string path, string content)`

### Phase 10: Network & I/O (Planned)
**Goals:**
- Socket support
- Network protocols
- File system access
- Serialization

**Features:**
- TCP/UDP socket API
- HTTP support
- File I/O with permissions
- Object serialization (save/load)

### Phase 11: Callout System (Planned)
**Goals:**
- Delayed execution
- Periodic tasks
- Event scheduling
- Timer management

**API:**
- `call_out(function func, int delay, mixed args...)`
- `remove_call_out(int id)`
- `call_out_info()`

### Phase 12: Optimization & Profiling (Planned)
**Goals:**
- Bytecode optimization passes
- Performance profiling
- Memory optimization
- Benchmarking suite

**Optimizations:**
- Constant folding
- Dead code elimination
- Inlining
- Register allocation

## Compiler Configuration

### Flags

```makefile
CFLAGS = -Wall -Wextra -Werror -g -O2 -std=c99
LDFLAGS = -lm
```

**Explanation:**
- `-Wall` - Enable all standard warnings
- `-Wextra` - Enable extra warnings
- `-Werror` - Treat warnings as errors (strict mode)
- `-g` - Include debug symbols
- `-O2` - Optimization level 2
- `-std=c99` - C99 standard compliance
- `-lm` - Link math library (for sqrt, pow, etc.)

### Build Output

```
[Compiling] driver.c
[Compiling] lexer.c
[Compiling] parser.c
[Compiling] codegen.c
[Compiling] vm.c
[Compiling] object.c
[Compiling] gc.c
[Compiling] efun.c
[Compiling] array.c
[Compiling] mapping.c
[Linking] Building driver executable...
[Success] Driver built successfully!
```

## Build System

### Makefile Structure

The build system supports:
- Automatic dependency management
- Parallel test execution
- Multiple build targets
- Progress indicators
- Clean builds

### Make Targets

```bash
make all              # Build driver + all tests
make driver           # Build driver only
make test_lexer       # Build lexer test
make test_parser      # Build parser test
make test_vm          # Build VM test
make test_object      # Build object test
make test_gc          # Build GC test
make test_efun        # Build efun test
make test_array       # Build array test
make test_mapping     # Build mapping test
make test             # Run all test suites
make clean            # Remove build artifacts
make help             # Show available targets
```

### Dependencies

Each source file's dependencies are automatically tracked:

```makefile
driver.o: driver.c driver.h lexer.h parser.h codegen.h vm.h object.h gc.h
lexer.o: lexer.c lexer.h
parser.o: parser.c parser.h lexer.h
codegen.o: codegen.c codegen.h parser.h vm.h
vm.o: vm.c vm.h gc.h array.h mapping.h
```

## Code Quality Standards

### Memory Management
- All malloc() calls paired with free()
- No memory leaks (verified with valgrind)
- GC integration for managed types
- Reference counting where appropriate

### Error Handling
- Comprehensive error checking
- Detailed error messages
- Graceful failure modes
- Recovery mechanisms

### Testing
- 100% test pass rate
- Comprehensive coverage
- Edge case testing
- Performance benchmarks

### Documentation
- Function-level comments
- API documentation
- Usage examples
- Architecture diagrams

---

**Last Updated:** January 27, 2026  
**Current Phase:** Phase 6 Complete  
**Next Milestone:** Phase 7 - Advanced Control Flow
