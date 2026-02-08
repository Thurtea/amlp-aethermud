# AMLP Driver

A modern LPC MUD driver written from scratch in C, featuring a complete LPC implementation with lexer, parser, bytecode compiler, and stack-based virtual machine.

## Overview

AMLP Driver is a high-performance MUD (Multi-User Dungeon) driver that interprets LPC (Lars Pensjö C) code. It provides a complete object-oriented environment with garbage collection, dynamic arrays, mappings, and a rich set of built-in functions for game development.

**Key Features:**

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

**Installation:**

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

### Prompt Customization

Players can customize their command prompt with status information.

## Development

### Building from Source

**Requirements:**

- GCC 4.9+ or Clang
- GNU Make
- POSIX-compliant system (Linux, macOS, WSL)

**Build:**

```bash
make clean           # Clean previous builds
make driver          # Build driver only
make all             # Build driver and utilities
```

**Understanding Build Warnings:**

When you run `make`, you may see compiler warnings. We've created comprehensive documentation explaining each warning:

- **[diagnostics/INDEX.md](diagnostics/INDEX.md)** - Start here for overview
- **[diagnostics/quick-reference.md](diagnostics/quick-reference.md)** - One-line solutions table
- **[diagnostics/README.md](diagnostics/README.md)** - Detailed navigation guide

The build output includes **clickable file paths** in most terminals - just click to open the relevant documentation!

```
╔════════════════════════════════════════════════════════════════════════════╗
╠════════════════════════════════════════════════════════════════════════════╣
║  BUILD SUCCESSFUL                                                          ║
╠════════════════════════════════════════════════════════════════════════════╣
║  Warnings:       50                                                        ║
║  Warning details: diagnostics/README.md      ← Click to learn more!        ║
╚════════════════════════════════════════════════════════════════════════════╝
```

Current warnings are **safe to ignore** - the MUD runs perfectly with them. But if you want to understand or fix them, the diagnostics directory has everything you need.

### LPC Development

Create rooms, objects, and NPCs using LPC:

```lpc
// lib/domains/myworld/rooms/entry.lpc
inherit "/std/room";

void create() {
    ::create();
    set_short("The Entrance");
    set_long("You stand at the entrance to a grand adventure.");
    add_exit("north", "/domains/myworld/rooms/hall");
}
```

See `docs/WIZTOOL.md` for in-game building tools.

## Documentation

- **Administrator Guide** - Server setup and management
- **Wiztool Guide** - In-game building commands
- **Development Guide** - Technical implementation details

## Architecture

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

---

**Version:** 0.7.0 | **Status:** Active Development | **Language:** C + LPC
