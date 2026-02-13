#!/bin/bash
# AMLP AetherMUD Setup Script

set -e

echo "=== AMLP AetherMUD Setup ==="

# Detect mudlib path
MUDLIB_PATH="$(pwd)/lib"
if [ ! -d "$MUDLIB_PATH" ]; then
    echo "ERROR: lib/ directory not found"
    exit 1
fi

echo "Mudlib path: $MUDLIB_PATH"

# Update driver config if needed
CONFIG_FILE="src/config.h"
if [ -f "$CONFIG_FILE" ]; then
    echo "Checking driver config..."
    grep -q "MUDLIB_PATH" "$CONFIG_FILE" || echo "#define MUDLIB_PATH \"$MUDLIB_PATH\"" >> "$CONFIG_FILE"
fi

# Build driver
echo "Building driver..."
make clean && make driver

# Create run directories
mkdir -p logs save data

# Locate driver binary (prefer build/driver)
DRIVER_BIN="./build/driver"
if [ ! -x "$DRIVER_BIN" ]; then
    if [ -x ./driver ]; then
        DRIVER_BIN="./driver"
    else
        DRIVER_BIN=""
    fi
fi

# Test driver launch (best-effort)
echo "Testing driver (best-effort, may be no test-parse)..."
if [ -n "$DRIVER_BIN" ]; then
    if "$DRIVER_BIN" --test-parse 2>/dev/null; then
        echo "Driver parse test succeeded"
    else
        echo "Driver exists but parse test not available or failed (continuing)"
    fi
else
    echo "Driver binary not found or not executable"
fi

echo ""
echo "=== Setup Complete ==="
echo "To start MUD: ./mud.sh start"
echo "To test client: telnet localhost 3000"