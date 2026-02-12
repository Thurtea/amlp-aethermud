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
./mud.ctl stop
./mud.ctl restart
```

## Build Instructions

Requirements:

- GCC or Clang
- GNU Make
- POSIX-compliant system (Linux is recommended)

To build the driver and tools:

```bash
make clean
make all
```

Start the server:

```bash
./mud.ctl start
```

Server logs are available at `lib/log/server.log`.

## Adding the Client as a Submodule (optional)

If you want to include the aethermud-client in this repo later, add it as a submodule:

```bash
git submodule add https://example.com/aethermud-client.git client
git submodule update --init --recursive
```

For now continue developing the client separately on your Windows environment.

## Notes and Recommendations

- The consolidated repo is the authoritative development workspace. Do not maintain parallel live changes in archived repos.
- Keep `lib/` and `src/` in sync by editing here and running the test cycle.
- If you need help converting CI or release scripts from the archived repos, open an issue or request assistance.

## License

MIT License - See LICENSE for details

**Version:** 0.7.0 | **Status:** Active Development | **Language:** C + LPC
