#!/bin/bash
set -e

DRIVER_ROOT="/home/thurtea/amlp-driver"
LIBRARY_ROOT="/home/thurtea/amlp-library"

echo "=== AMLP Driver + Library Integration Test ==="
echo ""

echo "1. Testing Driver Build..."
cd "$DRIVER_ROOT"
make clean
make
echo "✓ Driver built successfully"
echo ""

echo "2. Testing Library Compilation..."
SUCCESS=0
FAILED=0
for file in $(find "$LIBRARY_ROOT" -name "*.c" -type f | sort); do
    echo -n "  $(basename $file)... "
    if ./build/driver compile "$file" > /dev/null 2>&1; then
        echo "✓"
        SUCCESS=$((SUCCESS + 1))
    else
        echo "✗"
        FAILED=$((FAILED + 1))
    fi
done
echo ""
echo "Results: $SUCCESS passed, $FAILED failed"
echo ""

echo "3. Testing Master Object..."
./build/driver compile "$LIBRARY_ROOT/master.c"
echo ""

echo "4. Driver Status:"
echo "  - Lexer: ✓"
echo "  - Parser: ✓"
echo "  - Compiler: ✓"
echo "  - Bytecode Generator: ✓"
echo "  - VM/Executor: ✗ (Phase 7.6 - not implemented)"
echo ""

echo "=== Integration Test Complete ==="
echo ""
echo "Next steps to run library online:"
echo "1. Implement VM executor (Phase 7.6)"
echo "2. Implement object loader"
echo "3. Implement master object apply methods"
echo "4. Start network listener on port 4000"
