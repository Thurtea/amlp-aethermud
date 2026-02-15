# AMLP Aethermud

This repository is the single source of truth for the AMLP MUD system.

It contains the driver, the LPC mudlib, documentation, tests, and the build system. Development is consolidated here and no longer requires copying code between separate repositories.

## Consolidation Notice

- The `amlp-driver` and `amlp-library` repositories are now archived and deprecated.
- This repository replaces those projects as the canonical source for development and releases.
- The aethermud-client remains separate for now and can be added as a git submodule when needed.

## Repository Structure

Top-level layout and purpose:

- `src/`  : C driver source code (compiler, VM, runtime)
- `lib/`  : LPC mudlib, commands, objects, domains, and tests
- `config/`: Runtime configuration files
- `docs/` : Design notes, guides, and architecture documents
- `scripts/`: Helper scripts for building and maintenance
- `build/` : Build artifacts including the `driver` binary
- `tools/` : Utility scripts and data used for development
- `lpc-extension/`: Editor support for `.lpc` files (optional)

## Development Workflow

Edit, test, and commit directly in this repository. Do not copy code between repositories.

1. Edit files in `src/` or `lib/`.
2. Run the build and tests locally.
3. Commit changes and push to the central repo.

Recommended commands:

```bash
# build the driver
make clean && make driver

# run unit or integration tests (where available)
make test

# control the running server
./mud.ctl start
# AMLP Driver

A modern LPC MUD driver written from scratch in C, featuring a complete LPC implementation with lexer, parser, bytecode compiler, and stack-based virtual machine.

## Overview

AMLP Driver is a high-performance MUD (Multi-User Dungeon) driver that interprets LPC (Lars Pensjö C) code. It provides a complete object-oriented environment with garbage collection, dynamic arrays, mappings, and a rich set of built-in functions for game development.

Key Features:
- Complete LPC compiler and bytecode VM
- Garbage-collected object system
- Native support for .lpc file extension
- Real-time compilation and object loading
- Telnet and websocket connectivity
- Comprehensive character creation system

## Quick Start

```bash
# Build the driver
make clean && make driver

# Start the MUD server
./mud.ctl start

# Connect to your MUD
telnet localhost 3000
```

## Project Structure

```
amlp-driver/
├── src/              # C source code 
│   ├── lexer.c       # LPC tokenization
│   ├── parser.c      # Recursive descent parser
│   ├── codegen.c     # Bytecode generation
│   ├── vm.c          # Stack-based virtual machine
│   ├── object.c      # Object system
│   ├── gc.c          # Garbage collector
│   └── efun.c        # Built-in functions
├── lib/              # LPC mudlib 
├── docs/             # Documentation
├── config/           # Configuration files
└── mud.ctl           # Server control script
```

## LPC File Extension

This driver uses the `.lpc` extension for all LPC library files, clearly distinguishing them from C driver code. For proper syntax highlighting in VS Code, use the AMLP LPC Extension included in this repository.

Installation:
```bash
# From the amlp-driver directory:
cp -r lpc-extension ~/.vscode/extensions/

# Or install directly from the repo:
cp -r /path/to/amlp-driver/lpc-extension ~/.vscode/extensions/

# Restart VS Code
# Your .lpc files will now have proper syntax highlighting!
```

The extension provides:
- Syntax highlighting for LPC keywords and functions
- Code snippets for common LPC patterns
- Language configuration for proper bracket matching and auto-indentation
- Quick reference guides for AMLP development

## Usage

### Server Management

```bash
./mud.ctl start      # Start the MUD server
./mud.ctl stop       # Stop the server
./mud.ctl restart    # Restart the server
./mud.ctl status     # Check server status
```

### Configuration

Edit `config/runtime.conf` to customize:
- Port numbers (default: 3000 for telnet, 3001 for websocket)
- Mudlib location
- Master object path
- Security settings

### Connecting

**Telnet:**
```bash
telnet localhost 3000
```

**Mudlet/TinTin++:**
- Host: localhost
- Port: 3000

First player to connect receives admin privileges automatically.

## Development

### Building from Source

Requirements:
- GCC 4.9+ or Clang
- GNU Make
- POSIX-compliant system (Linux, macOS, WSL)

Build:
```bash
make clean           # Clean previous builds
make driver          # Build driver only
make all             # Build driver and utilities
```

### Architecture

The driver implements a complete LPC environment:
- **Lexer** - Tokenizes LPC source code
- **Parser** - Builds abstract syntax trees
- **Compiler** - Generates bytecode
- **VM** - Executes bytecode in a stack-based virtual machine
- **Object System** - Manages LPC objects with inheritance
- **Garbage Collector** - Reference-counted memory management
- **Efuns** - Built-in functions for strings, arrays, math, I/O

## Contributing

Contributions are welcome! This project demonstrates:
- Compiler construction techniques
- Virtual machine design
- Garbage collection implementation
- Network protocol handling

## License

MIT License - See LICENSE for details
