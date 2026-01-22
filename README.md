# AMLP Driver - Advanced MUD LPC Platform

A production-quality implementation of an LPC MUD driver from scratch, built in C with comprehensive testing and modern architecture.

**Status:** Phase 6 Complete - Arrays & Mappings Implemented (220 tests passing)

## Project Overview

Complete LPC MUD driver implementation with all foundational components:

1. Lexer (Complete) - Full LPC tokenization with 50+ token types
2. Parser (Complete) - Recursive descent AST builder with 25+ node types
3. Code Generator (Complete) - AST → bytecode compiler
4. Virtual Machine (Complete) - Stack-based bytecode executor with 40+ opcodes
5. Object System (Complete) - OOP support with methods and inheritance
6. Garbage Collector (Complete) - Reference-counted mark-sweep GC
7. Efun System (Complete) - 24 built-in functions
8. Arrays & Mappings (Complete) - GC-aware dynamic data structures

## Quick Start

### Prerequisites
- GCC 4.9+
- Make
- Standard C library (POSIX)

### Build

```bash
cd /home/thurtea/amlp-driver
make clean
make all
```

### Test

```bash
make test
```

Runs 8 comprehensive test suites with 220 tests (565 assertions).

### Run Driver

```bash
./driver
```

## Test Results Summary

```
Suite               Tests    Assertions  Status
--------------------------------------------------
test_lexer          20       41          PASS
test_parser         40       97          PASS  
test_vm             47       146         PASS
test_object         16       33          PASS
test_gc             23       52          PASS
test_efun           28       57          PASS
test_array          23       70          PASS
test_mapping        23       69          PASS
--------------------------------------------------
TOTAL               220      565         100% PASS
```

## Project Statistics

- **Total Lines:** 11,249
- **Core Modules:** ~6,500 lines
- **Test Suites:** ~4,700 lines
- **Build:** Zero warnings with -Werror
- **Test Coverage:** 100% pass rate

## Project Structure

```
amlp-driver/
├── src/               # Core implementation
│   ├── driver.c       # Main driver (267 lines)
│   ├── lexer.h/c      # Lexer (140 + 550 lines)
│   ├── parser.h/c     # Parser (280 + 1000 lines)
│   ├── codegen.h/c    # Code generator
│   ├── vm.h/c         # Virtual machine (150 + 120 lines)
│   ├── object.h/c     # Object system
│   ├── gc.h/c         # Garbage collector
│   ├── efun.h/c       # Built-in functions
│   ├── array.h/c      # Array implementation
│   └── mapping.h/c    # Mapping (hash map) implementation
│
├── tests/             # Test suites
│   ├── test_lexer.c   # Lexer tests (20 tests)
│   ├── test_parser.c  # Parser tests (40 tests)
│   ├── test_vm.c      # VM tests (47 tests)
│   ├── test_object.c  # Object tests (16 tests)
│   ├── test_gc.c      # GC tests (23 tests)
│   ├── test_efun.c    # Efun tests (28 tests)
│   ├── test_array.c   # Array tests (23 tests)
│   └── test_mapping.c # Mapping tests (23 tests)
│
├── build/             # Compiled binaries (generated)
│   ├── *.o            # Object files
│   ├── driver         # Main executable
│   └── test_*         # Test executables
│
├── docs/              # Documentation
│   ├── PHASE*.md      # Phase documentation
│   ├── PHASE*_COMPLETE.txt
│   └── BUILD_SUMMARY.md
│
├── Makefile           # Build configuration
└── README.md          # This file
```

## Component Details

### Lexer (`lexer.h`, `lexer.c`) - Phase 1 Complete

**Features:**
- 50+ token types for full LPC syntax
- Line/column tracking for error reporting
- Comment handling (// and /* */)
- Float literals with scientific notation
- String escape sequences
- Multi-character operators (==, !=, <=, >=, ++, --, &&, ||, etc.)
- Keyword recognition (20+ keywords)

### Parser (`parser.h`, `parser.c`) - Phase 2 Complete

**Features:**
- Recursive descent with operator precedence
- 25+ AST node types
- Full declaration support (functions, variables, inheritance)
- Control structures (if/else, while, for, do-while, switch)
- Expression parsing with correct associativity
- Function calls, array/object access
- Error recovery and detailed diagnostics

### Code Generator (`codegen.h`, `codegen.c`) - Phase 3 Complete

**Features:**
- AST → bytecode compilation
- Constant pool management
- Jump label resolution
- Opcode optimization
- Symbol table management

### Virtual Machine (`vm.h`, `vm.c`) - Phase 3-5 Complete

**Features:**
- Stack-based architecture (1024-element capacity)
- 40+ opcodes (arithmetic, logic, control flow, data structures)
- Call frame management
- Local/global variable access
- Array and mapping operations
- Object method calls
- GC integration

**Value Types:**
- VALUE_INT (long)
- VALUE_FLOAT (double)
- VALUE_STRING (char*)
- VALUE_OBJECT (Object*)
- VALUE_ARRAY (array_t*)
- VALUE_MAPPING (mapping_t*)
- VALUE_NULL

### Object System (`object.h`, `object.c`) - Phase 4 Complete

**Features:**
- Object creation/destruction
- Method registration and dispatch
- Function storage
- Object registry
- Method call stack

### Garbage Collector (`gc.h`, `gc.c`) - Phase 5 Complete

**Features:**
- Reference counting
- Mark-and-sweep collection
- Type-specific tracking (objects, arrays, mappings, strings)
- Auto-collection threshold
- Memory leak detection
- Full statistics (allocated, freed, collections)

### Efun System (`efun.h`, `efun.c`) - Phase 5 Complete

**24 Built-in Functions:**

**String Functions:**
- strlen, substring, explode, implode
- upper_case, lower_case, trim

**Array Functions:**
- sizeof, arrayp, sort_array, reverse_array

**Math Functions:**
- abs, sqrt, pow, random, min, max

**Type Checking:**
- intp, floatp, stringp, objectp, mappingp

**I/O Functions:**
- write, printf

### Array Module (`array.h`, `array.c`) - Phase 6 Complete

**Features:**
- GC-aware dynamic arrays
- Automatic capacity growth (2x on overflow)
- Core operations: new, push, pop, get, set, insert, delete
- Deep cloning with vm_value_clone
- Bounds checking
- Mixed type storage

### Mapping Module (`mapping.h`, `mapping.c`) - Phase 6 Complete

**Features:**
- GC-aware hash maps
- Collision handling via chaining
- String keys, VMValue values
- Core operations: new, set, get, delete, keys, values
- Deep cloning
- Size tracking

## Build System (`Makefile`)

**Features:**
- Automatic dependency management
- Parallel test execution
- 8 test targets + driver binary
- Verbose progress indicators
- Strict compilation (-Werror)

**Make Targets:**
```bash
make all          # Build driver + all tests
make driver       # Build main driver only
make test_lexer   # Build lexer test
make test_parser  # Build parser test
make test_vm      # Build VM test
make test_object  # Build object test
make test_gc      # Build GC test
make test_efun    # Build efun test
make test_array   # Build array test
make test_mapping # Build mapping test
make test         # Run all test suites
make clean        # Remove build artifacts
make help         # Show available targets
```

## Phases Complete

### Phase 1: Lexical Analysis (Complete)
- Full LPC token support
- 50+ token types
- 20 tests, 41 assertions

### Phase 2: Syntax Analysis (Complete)
- Recursive descent parser
- 25+ AST node types
- 40 tests, 97 assertions

### Phase 3: VM Architecture & Bytecode (Complete)
- Stack-based VM
- 40+ opcodes
- Code generator
- 47 tests, 146 assertions

### Phase 4: Object System (Complete)
- OOP support
- Method dispatch
- Object registry
- 16 tests, 33 assertions

### Phase 5: Garbage Collection & Efuns (Complete)
- Reference-counted GC
- Mark-and-sweep
- 24 built-in functions
- 51 tests (GC: 23, Efun: 28), 109 assertions

### Phase 6: Arrays & Mappings (Complete)
- GC-aware dynamic arrays
- Hash map implementation
- Enhanced efuns (explode, implode, sort, reverse)
- 46 tests (Array: 23, Mapping: 23), 139 assertions

## Next Phases (Roadmap)

### Phase 7: Advanced Control Flow
- Function call stack with local scopes
- Return value handling
- Nested function calls
- Stack frame management

### Phase 8: Inheritance System
- Multiple inheritance
- Virtual method resolution
- Super calls
- Access control (public/private/protected)

### Phase 9: Advanced Efuns
- filter_array, map_array, member_array
- String interpolation
- Regular expressions
- File I/O operations

### Phase 10: Network & I/O
- Socket support
- Network protocols
- File system access
- Serialization

### Phase 11: Callout System
- Delayed execution
- Periodic tasks
- Event scheduling
- Timer management

### Phase 12: Optimization & Profiling
- Bytecode optimization passes
- Performance profiling
- Memory optimization
- Benchmarking suite

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

- No compiler warnings with `-Wall -Wextra -Werror`
- Proper memory management (malloc/free)
- Comprehensive error handling
- Detailed code documentation
- Function prototypes for all public APIs
- Consistent coding style

## Next Phases

### Phase 2: Virtual Machine Implementation
- Bytecode generation from AST
- Execution engine
- Stack-based operations
- Call stack management
- Variable scope handling

### Phase 3: Object Manager
- Object creation/destruction
## Compiler Configuration

**Flags:**
- `-Wall -Wextra` - All warnings enabled
- `-Werror` - Warnings treated as errors
- `-g` - Debug symbols included
- `-O2` - Optimization level 2
- `-std=c99` - C99 standard
- `-lm` - Math library

## Code Quality

- Zero warnings with -Wall -Wextra -Werror
- Comprehensive memory management (no leaks)
- Full error handling and recovery
- 100% test pass rate (220 tests, 565 assertions)
- Consistent coding style
- Extensive documentation
- GC integration across all modules

## Repository

**GitHub:** https://github.com/Thurtea/amlp-driver

```bash
git clone https://github.com/Thurtea/amlp-driver.git
cd amlp-driver
make clean && make all && make test
```

## License

Educational implementation demonstrating:
- Language parsing and compilation
- Virtual machine design
- Garbage collection algorithms
- Object-oriented system design
- Comprehensive testing methodology

---

**Built with:** C99, Make, GCC  
**Testing:** 220 tests, 565 assertions, 100% pass rate  
**Lines:** 11,249 total (6,500 core + 4,700 tests)  
**Status:** Production-ready foundation for advanced MUD features
