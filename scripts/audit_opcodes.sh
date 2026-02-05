#!/bin/bash
# Opcode Encoding Audit Script
cd /home/thurtea/amlp-aethermud

echo "=== OPCODE AUDIT ==="
echo "Checking compiler bytecode generation..."
echo ""

echo "Opcodes defined in vm.h:"
grep "OP_" src/vm.h | grep -E '^\s*(OP_|/\*)' | head -20
echo ""

echo "Compiler emit functions used:"
grep -n "compiler_emit" src/compiler.c | grep -v "^[[:space:]]*/" | wc -l
echo " total emit calls found"
echo ""

echo "Build status check: See next task"
