#!/bin/bash
# Test script for command system with output routing

echo "=== Testing Command System with Fixed Output Routing ==="
echo ""

# Try connecting and running basic commands
# Use a longer timeout to see the full interaction
{
    sleep 1
    echo "admin"           # Username (existing player)
    sleep 1
    echo "admin123"        # Password (6+ chars)
    sleep 1
    echo "admin123"        # Confirm password (for new user)
    sleep 2
    echo "look"            # Test look command
    sleep 1
    echo "inventory"       # Test inventory command
    sleep 1
    echo "score"           # Test score command
    sleep 1
    echo "help"            # Test help command
    sleep 1
    echo "quit"            # Exit
    sleep 1
} | timeout 20 nc localhost 3000

echo ""
echo "=== Test Complete ==="
