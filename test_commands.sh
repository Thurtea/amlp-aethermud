#!/bin/bash
# AMLP Driver - Quick Command Test Script
# Tests basic command functionality via netcat

SERVER="localhost"
PORT="3000"
TIMEOUT=2

echo "╔════════════════════════════════════════════════════════════════╗"
echo "║          AMLP DRIVER - COMMAND TESTING SCRIPT                ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo ""

# Check if server is running
if ! nc -z $SERVER $PORT 2>/dev/null; then
    echo "❌ ERROR: Server is not running on $SERVER:$PORT"
    echo "Start server with: ./mud.ctl start"
    exit 1
fi

echo "✓ Server is running on $SERVER:$PORT"
echo ""

# Function to send commands and capture output
function test_command() {
    local username=$1
    local password=$2
    local commands=$3
    local description=$4
    
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "TEST: $description"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    
    # Create command sequence
    {
        sleep 0.5
        echo "$username"
        sleep 0.5
        echo "$password"
        sleep 0.5
        echo "$password"
        sleep 1
        
        # Send each command with delay
        IFS=$'\n'
        for cmd in $commands; do
            echo "$cmd"
            sleep 0.3
        done
        
        sleep 0.5
        echo "quit"
        sleep 0.5
    } | nc $SERVER $PORT 2>&1 | grep -v "^$" | tail -30
    
    echo ""
}

# Test 1: Basic Player Commands
echo "═══════════════════════════════════════════════════════════════════"
echo " TEST SUITE 1: BASIC PLAYER COMMANDS"
echo "═══════════════════════════════════════════════════════════════════"
echo ""

COMMANDS="help
look
stats
who
save"

test_command "testbasic" "test123" "$COMMANDS" "Player: Basic Commands (help, look, stats, who, save)"

# Test 2: Movement Commands  
echo "═══════════════════════════════════════════════════════════════════"
echo " TEST SUITE 2: MOVEMENT SYSTEM"
echo "═══════════════════════════════════════════════════════════════════"
echo ""

COMMANDS="n
look
e
look
w
look
s
look"

test_command "testmove" "test123" "$COMMANDS" "Player: Movement (n, e, w, s, look)"

# Test 3: Communication Commands
echo "═══════════════════════════════════════════════════════════════════"
echo " TEST SUITE 3: COMMUNICATION"
echo "═══════════════════════════════════════════════════════════════════"
echo ""

COMMANDS="say Hello, this is a test message!
emote waves enthusiastically
who"

test_command "testchat" "test123" "$COMMANDS" "Player: Communication (say, emote)"

# Summary
echo "═══════════════════════════════════════════════════════════════════"
echo " TEST SUMMARY"
echo "═══════════════════════════════════════════════════════════════════"
echo ""
echo "✓ Basic command infrastructure tests complete"
echo ""
echo "MANUAL TESTING REQUIRED FOR:"
echo "  - Wizard commands (goto, clone) - Requires privilege level 1"
echo "  - Admin commands (promote, users, shutdown) - Requires level 2"
echo "  - Multi-user interaction tests"
echo "  - Character persistence across sessions"
echo ""
echo "To promote a user for wizard/admin testing:"
echo "  1. Create user 'testadmin' via nc localhost 3000"
echo "  2. Connect as that user"
echo "  3. Run: promote testadmin 2"
echo "  4. Run: promote testwizard 1"
echo ""
echo "See COMMAND_TEST_CHECKLIST.md for comprehensive manual testing guide"
echo "═══════════════════════════════════════════════════════════════════"
