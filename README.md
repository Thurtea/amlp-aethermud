# LPC MUD Driver Project

A comprehensive implementation of an LPC MUD driver from scratch, built in C with a focus on clean architecture and proper testing.

**Status:** ✅ Foundation Complete - Ready for Virtual Machine Implementation

## Project Overview

This project implements the core components of an LPC MUD driver:

1. **Lexer** (✅ Complete) - Tokenizes LPC source code
2. **Parser** (✅ Complete) - Builds Abstract Syntax Trees (AST)
3. **Virtual Machine** (🔄 Stub) - Executes parsed code
4. **Object Manager** (📋 Planned) - Manages game objects
5. **Garbage Collector** (📋 Planned) - Memory management
6. **Efun System** (📋 Planned) - Built-in functions

## Quick Start

### Prerequisites
- GCC 4.9+
- Make
- Standard C library (POSIX)

### Build

```bash
cd /home/thurtea/amlp-driver
make clean
make
```

### Test

```bash
make test
```

This will run both lexer and parser test suites.

### Run Driver

```bash
./driver
```

The driver will initialize all subsystems and enter the main event loop.

## Project Structure

```
amlp-driver/
├── Makefile           # Build configuration
├── README.md          # This file
├── BUILD_SUMMARY.md   # Build and test results
│
├── Core Components
├── driver.c           # Main driver initialization (267 lines)
├── driver.o           # Compiled object
│
├── Lexer
├── lexer.h            # Lexer API (140 lines)
├── lexer.c            # Lexer implementation (550+ lines)
├── lexer.o            # Compiled object
│
├── Parser
├── parser.h           # Parser API (280+ lines)
├── parser.c           # Parser implementation (1000+ lines)
├── parser.o           # Compiled object
│
├── Virtual Machine
├── vm.h               # VM API (150+ lines)
├── vm.c               # VM stub (120+ lines)
├── vm.o               # Compiled object
│
├── Tests
├── test_lexer.c       # Lexer test suite (10 tests)
├── test_parser.c      # Parser test suite (11 tests)
│
├── Executables
├── driver             # Main driver executable
├── test_lexer         # Lexer test executable
└── test_parser        # Parser test executable
```

## Component Details

### Lexer (`lexer.h`, `lexer.c`)

**Features:**
- ✅ Full LPC token support (identifiers, numbers, strings, operators, keywords)
- ✅ Line and column tracking for error reporting
- ✅ Comment handling (single-line `//` and multi-line `/* */`)
- ✅ Floating-point literal support with exponents
- ✅ String escape sequence handling
- ✅ Multi-character operator recognition (==, !=, <=, >=, ++, --, &&, ||, etc.)
- ✅ Keyword vs identifier distinction

**API Functions:**
```c
Lexer* lexer_init(const char *filename);
Lexer* lexer_init_from_string(const char *source);
Token lexer_get_next_token(Lexer *lexer);
Token lexer_peek_token(Lexer *lexer);
void lexer_reset(Lexer *lexer);
void lexer_free(Lexer *lexer);
const char* token_type_to_string(TokenType type);
```

### Parser (`parser.h`, `parser.c`)

**Features:**
- ✅ Recursive descent parser with proper operator precedence
- ✅ 25+ AST node types for different language constructs
- ✅ Support for declarations (functions, variables, inheritance)
- ✅ Control structures (if/else, while, for, do-while, switch)
- ✅ Expression parsing with correct precedence
- ✅ Function calls, array access, member access
- ✅ Error reporting with recovery
- ✅ AST printing for debugging

**Supported Constructs:**
- Variable declarations with initializers
- Function declarations with parameters
- Control flow (if/else, while, for, switch)
- Binary operations with precedence
- Unary operations (++, --, -, !)
- Assignment operators (=, +=, -=, *=, /=)
- Array and object access
- Function calls

**API Functions:**
```c
Parser* parser_init(Lexer *lexer);
ASTNode* parser_parse(Parser *parser);
void parser_free(Parser *parser);
void ast_node_free(ASTNode *node);
const char* ast_node_to_string(ASTNodeType type);
void parser_print_ast(ASTNode *node, int indent);
```

### Virtual Machine (`vm.h`, `vm.c`)

**Current Status:** Stub implementation ready for expansion

**Planned Features:**
- Execution stack management
- Call frame tracking
- Value type system (int, float, string, object, array, mapping)
- Bytecode execution
- Function calls and returns
- Memory management integration

**API Functions:**
```c
VirtualMachine* vm_init(void);
int vm_load_program(VirtualMachine *vm, ASTNode *program);
int vm_execute(VirtualMachine *vm);
VMValue vm_execute_node(VirtualMachine *vm, ASTNode *node);
int vm_push_value(VirtualMachine *vm, VMValue value);
VMValue vm_pop_value(VirtualMachine *vm);
void vm_free(VirtualMachine *vm);
```

### Build System (`Makefile`)

**Features:**
- Automatic dependency tracking
- Verbose build output with progress indicators
- Separate compilation and linking
- Multiple build targets
- Test suite integration
- Clean and distclean targets

**Make Targets:**
```bash
make              # Build everything (default)
make driver       # Build main driver only
make test_lexer   # Build lexer test
make test_parser  # Build parser test
make test         # Run all tests
make clean        # Remove build artifacts
make distclean    # Remove all generated files
make help         # Show available targets
```

## Test Suites

### Lexer Tests (10 tests)

1. ✅ Variable Declaration
2. ✅ String Literals
3. ✅ Function Calls
4. ✅ Binary Operators
5. ✅ Control Structures (if/else)
6. ✅ While Loops
7. ✅ Array Access
8. ✅ Comments (single and multi-line)
9. ✅ Float Literals with Exponents
10. ✅ Complex Expressions

**Result:** All 10/10 tests passed ✅

### Parser Tests (11 tests)

1. ✅ Variable Declarations
2. ✅ Function Declarations
3. ✅ Functions with Parameters
4. ✅ If Statements
5. ✅ While Loops
6. ✅ Return Statements
7. ✅ Binary Operations
8. ✅ Function Calls
9. ✅ Array Access
10. ✅ Complex Expressions
11. ✅ Multiple Declarations

**Result:** All 11/11 tests passed ✅

## Compiler Configuration

**Flags:**
- `-Wall -Wextra` - Enable all warnings
- `-Werror` - Treat warnings as errors (strict mode)
- `-g` - Include debug symbols
- `-O2` - Optimization level 2
- `-std=c99` - C99 standard compliance
- `-lm` - Link math library

**Build Output:**
```
[Compiling] driver.c
[Compiling] lexer.c
[Compiling] parser.c
[Compiling] vm.c
[Linking] Building driver executable...
[Success] Driver built successfully!
```

## Usage Examples

### Run Lexer Test
```bash
./test_lexer
```

Output shows tokenization of sample LPC code.

### Run Parser Test
```bash
./test_parser
```

Output shows AST structure for parsed code.

### Run Driver
```bash
./driver
```

Initializes all subsystems and runs the main event loop.

## Code Quality

- ✅ No compiler warnings with `-Wall -Wextra -Werror`
- ✅ Proper memory management (malloc/free)
- ✅ Comprehensive error handling
- ✅ Detailed code documentation
- ✅ Function prototypes for all public APIs
- ✅ Consistent coding style

## Next Phases

### Phase 2: Virtual Machine Implementation
- Bytecode generation from AST
- Execution engine
- Stack-based operations
- Call stack management
- Variable scope handling

### Phase 3: Object Manager
- Object creation/destruction
- Object registry
- Reference counting
- Object properties
- Method calls

### Phase 4: Garbage Collector
- Reference tracking
- Mark-and-sweep algorithm
- Memory recovery
- Circular reference detection

### Phase 5: Efun System
- Built-in function registration
- Native function binding
- Efun dispatching
- Standard library

### Phase 6: Integration & Testing
- End-to-end tests
- Performance benchmarks
- Memory leak detection
- Stress testing

## Development Notes

- **Language:** C (C99 standard)
- **Paradigm:** Procedural with function-based abstraction
- **Compilation:** Direct compilation, no preprocessing required
- **Testing:** Custom test suites with detailed output
- **Documentation:** Inline comments and separate summaries

## License & Attribution

This is an educational implementation of an LPC MUD driver. It is designed to demonstrate:
- Language parsing and compilation techniques
- Abstract syntax tree construction
- Recursive descent parsing
- Virtual machine design
- Software architecture in C

## Author Notes

Built as a comprehensive learning project to demonstrate:
1. Complete lexer implementation from scratch
2. Production-quality parser with error recovery
3. Proper C project structure and build system
4. Comprehensive test coverage
5. Clean API design

All components are fully documented and ready for extension.
