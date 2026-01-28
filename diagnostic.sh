#!/bin/bash
# AMLP MUD - Quick Diagnostic Check

echo "╔════════════════════════════════════════════════════════════════╗"
echo "║  AMLP MUD - System Diagnostic                                  ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo ""

cd ~/amlp-driver

echo "═══════════════════════════════════════════════════════════════"
echo " 1. File Structure Check"
echo "═══════════════════════════════════════════════════════════════"

check_file() {
    if [ -f "$1" ]; then
        echo "  ✓ $1"
        return 0
    else
        echo "  ✗ MISSING: $1"
        return 1
    fi
}

# Critical files
check_file "lib/secure/master.lpc"
check_file "lib/secure/simul_efun.lpc"
check_file "lib/std/wiztool.lpc"
check_file "lib/std/player.lpc"
check_file "lib/daemon/command.lpc"
check_file "lib/include/globals.h"

# Check for stray .c files (we use .lpc for the mudlib)
echo ""
c_count=$(find lib -name "*.c" 2>/dev/null | wc -l)
if [ $c_count -gt 0 ]; then
    echo "  ⚠️  WARNING: Found $c_count .c files (should be .lpc for the mudlib)"
    echo "     Run: find lib -name '*.c' -type f"
else
    echo "  ✓ No stray .c files found in lib (good)"
fi

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo " 2. Directory Structure"
echo "═══════════════════════════════════════════════════════════════"

check_dir() {
    if [ -d "$1" ]; then
        echo "  ✓ $1"
    else
        echo "  ✗ MISSING: $1"
    fi
}

check_dir "lib/save/players"
check_dir "lib/log"
check_dir "lib/daemon"
check_dir "lib/cmds"
check_dir "lib/std"

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo " 3. Content Checks"
echo "═══════════════════════════════════════════════════════════════"

# Check if player.c has wiztool integration
if grep -q "query_wiztool" lib/std/player.lpc 2>/dev/null; then
    echo "  ✓ player.lpc has wiztool integration"
else
    echo "  ✗ player.lpc missing wiztool integration"
    echo "    (needs query_wiztool() function)"
fi

# Check if player.c routes commands
if grep -q "COMMAND_D" lib/std/player.lpc 2>/dev/null; then
    echo "  ✓ player.lpc routes to command daemon"
else
    echo "  ✗ player.lpc missing COMMAND_D routing"
    echo "    (needs to call COMMAND_D in process_input)"
fi

# Check if master.c loads daemons
if grep -q "daemon/command" lib/secure/master.lpc 2>/dev/null; then
    echo "  ✓ master.lpc loads command daemon"
else
    echo "  ✗ master.lpc doesn't load command daemon"
fi

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo " 4. Process Check"
echo "═══════════════════════════════════════════════════════════════"

if pgrep -f "driver 3000" > /dev/null; then
    echo "  ✓ Driver is running (port 3000)"
    echo ""
    echo "  Recent log entries:"
    if [ -f lib/log/server.log ]; then
        tail -n 5 lib/log/server.log | sed 's/^/    /'
    fi
else
    echo "  ✗ Driver is NOT running"
    echo "    Start with: ./build/driver 3000"
fi

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo " 5. Quick Syntax Check"
echo "═══════════════════════════════════════════════════════════════"

# Check for common syntax issues
error_count=0

if grep -n "\.lpc" lib/secure/master.lpc 2>/dev/null | grep -v "^Binary" | head -3; then
    echo "  ⚠️  master.lpc references other .lpc files (normal)"
    ((error_count++))
fi

if ! grep -q "#include.*globals" lib/std/player.lpc 2>/dev/null; then
    echo "  ⚠️  player.lpc missing #include <globals.h>"
    ((error_count++))
fi

if [ $error_count -eq 0 ]; then
    echo "  ✓ No obvious syntax issues detected"
fi

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo " SUMMARY"
echo "═══════════════════════════════════════════════════════════════"
echo ""

if [ -f lib/secure/master.lpc ] && [ -f lib/std/wiztool.lpc ] && [ -f lib/daemon/command.lpc ]; then
    echo "✓ Core files present"
    echo ""
    echo "Next steps:"
    echo "  1. If driver not running: ./build/driver 3000"
    echo "  2. Run manual test: bash /home/claude/manual_test.sh"
    echo "  3. Or run automated: python3 /home/claude/robust_mud_test.py"
else
    echo "✗ Missing critical files"
    echo ""
    echo "Need to copy implementation files (use .lpc versions):" 
    echo "  cp /home/claude/command_daemon.lpc lib/daemon/command.lpc"
    echo "  cp /home/claude/wiztool.lpc lib/std/wiztool.lpc"
    echo "  cp /home/claude/master.lpc lib/secure/master.lpc"
    echo "  cp /home/claude/globals.h lib/include/globals.h"
fi

echo ""
