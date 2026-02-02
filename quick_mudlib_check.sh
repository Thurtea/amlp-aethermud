#!/bin/bash
# Quick test of critical mudlib files

cd ~/amlp-driver

echo "═══════════════════════════════════════════════════════════════"
echo "  QUICK MUDLIB VALIDATION CHECK"
echo "═══════════════════════════════════════════════════════════════"
echo ""

# Test 1: Master Object
echo "1. Testing master.lpc..."
if [ -f lib/master.lpc ]; then
    MASTER_FILE="lib/master.lpc"
elif [ -f lib/secure/master.lpc ]; then
    MASTER_FILE="lib/secure/master.lpc"
else
    echo "   ❌ ERROR: No master.lpc found!"
    exit 1
fi

./build/driver --parse-test "$MASTER_FILE" 2>&1 | head -20

if ./build/driver --parse-test "$MASTER_FILE" >/dev/null 2>&1; then
    echo ""
    echo "   ✅ master.lpc PARSES SUCCESSFULLY!"
    echo "   🎉 This is a MAJOR milestone!"
    echo ""
else
    echo ""
    echo "   ❌ master.lpc FAILED TO PARSE"
    echo ""
    
    # Save full error
    ./build/driver --parse-test "$MASTER_FILE" 2>&1 > /tmp/master_error.log
    
    echo "   First error:"
    grep -E "Error|Expected|Unexpected" /tmp/master_error.log | head -1 | sed 's/^/   /'
    echo ""
    
    # Check for missing features
    if grep -q "({" "$MASTER_FILE"; then
        echo "   ⚠️  master.lpc uses ARRAY LITERALS: ({ })"
    fi
    
    if grep -q "\[:" "$MASTER_FILE"; then
        echo "   ⚠️  master.lpc uses MAPPING LITERALS: ([ ])"
    fi
    
    if grep -q "foreach" "$MASTER_FILE"; then
        echo "   ⚠️  master.lpc uses FOREACH LOOPS"
    fi
    
    if grep -q "#include\|#define" "$MASTER_FILE"; then
        echo "   ⚠️  master.lpc uses PREPROCESSOR DIRECTIVES"
    fi
    
    echo ""
    echo "   Full error log: /tmp/master_error.log"
    echo ""
fi

# Test 2: Sample command files
echo "2. Testing command files..."
echo ""

PASSED=0
FAILED=0

for cmd_file in lib/cmds/*.lpc lib/cmds/*.c; do
    if [ -f "$cmd_file" ]; then
        cmd_name=$(basename "$cmd_file")
        if ./build/driver --parse-test "$cmd_file" >/dev/null 2>&1; then
            echo "   ✅ $cmd_name"
            ((PASSED++))
        else
            echo "   ❌ $cmd_name"
            ((FAILED++))
        fi
        
        if [ $((PASSED + FAILED)) -ge 5 ]; then
            break
        fi
    fi
done

echo ""
echo "   Commands: $PASSED passed, $FAILED failed"
echo ""

# Test 3: Standard objects
echo "3. Testing standard objects..."
echo ""

tested=0
for std_file in lib/std/*.lpc lib/std/*.c; do
    if [ -f "$std_file" ]; then
        std_name=$(basename "$std_file")
        if ./build/driver --parse-test "$std_file" >/dev/null 2>&1; then
            echo "   ✅ $std_name"
        else
            echo "   ❌ $std_name"
        fi
        ((tested++))
        if [ $tested -ge 3 ]; then
            break
        fi
    fi
done

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo "  For detailed analysis, create and run: test_mudlib_parser.sh"
echo "═══════════════════════════════════════════════════════════════"
