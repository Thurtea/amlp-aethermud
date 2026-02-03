#!/bin/bash
# Manual command testing - creates character then tests commands

echo "=== Manual Command Test ==="
echo "This will connect and walk through creating a character,"
echo "then test if commands produce output."
echo ""
echo "Steps:"
echo "1. Enter username: testuser2"
echo "2. Enter password twice: test123456"
echo "3. Select race: 1 (Human)"
echo "4. Type 'yes' to accept stats"
echo "5. Try commands: look, inventory, score, help"
echo "6. Type 'quit' to exit"
echo ""
echo "Watch for command output to verify the fix is working!"
echo ""
echo "Press Enter to start, or Ctrl+C to cancel..."
read

nc localhost 3000
