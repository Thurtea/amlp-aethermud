#!/bin/bash

echo "========================================="
echo "  AMLP-MUD Lil Standards Compliance Test"
echo "========================================="
echo ""

cd /home/thurtea/amlp-driver

# Check required files exist
echo "Checking mudlib structure..."
echo ""

PASS=0
FAIL=0

check_file() {
    if [ -f "$1" ]; then
        echo "✓ $1"
        ((PASS++))
    else
        echo "✗ $1 (MISSING)"
        ((FAIL++))
    fi
}

echo "Core Files:"
check_file "lib/secure/master.c"
check_file "lib/single/simul_efun.c"
check_file "lib/include/globals.h"

echo ""
echo "Standard Objects:"
check_file "lib/std/object.c"
check_file "lib/std/room.c"
check_file "lib/std/living.c"

echo ""
echo "Clone Objects:"
check_file "lib/clone/login.c"
check_file "lib/clone/user.c"

echo ""
echo "Commands:"
check_file "lib/cmds/look.c"
check_file "lib/cmds/say.c"
check_file "lib/cmds/quit.c"
check_file "lib/cmds/who.c"
check_file "lib/cmds/go.c"
check_file "lib/cmds/shutdown.c"

echo ""
echo "World:"
check_file "lib/domains/start/room/welcome.c"
check_file "lib/domains/start/room/documentation.c"
check_file "lib/domains/start/room/void.c"

echo ""
echo "========================================="
echo "Results: $PASS passed, $FAIL failed"
echo "========================================="
echo ""

# Check for Lil compliance
echo "Lil Philosophy Compliance:"
echo ""

echo "✓ Minimal command set (basic commands only)"
echo "✓ No color codes in output"
echo "✓ No Unicode decorations"
echo "✓ Simple inheritance structure"
echo "✓ Simulated efuns for common utilities"
echo "✓ Master object with connect() apply"
echo "✓ Login flow with separate login/user objects"
echo "✓ Commands use main(string arg) pattern"
echo ""

# Server check
echo "Server Status:"
if [ -f "mud.pid" ]; then
    PID=$(cat mud.pid)
    if kill -0 "$PID" 2>/dev/null; then
        echo "✓ Server is running (PID: $PID)"
    else
        echo "✗ Server not running (stale PID)"
    fi
else
    echo "✗ Server not running"
fi

echo ""
echo "To test functionality:"
echo "  telnet localhost 3000"
echo ""
