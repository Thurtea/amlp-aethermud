#!/bin/bash
# Automated MUD Command Testing

PORT=3000
LOG="test-results.log"

echo "=== AMLP MUD Test Suite ===" | tee $LOG

# Test 1: Connection
echo -e "\n[TEST] Connection test..." | tee -a $LOG
(echo ""; sleep 1) | telnet localhost $PORT 2>&1 | head -10 | tee -a $LOG

# Test 2: Basic commands
echo -e "\n[TEST] Command test..." | tee -a $LOG
{
    sleep 1
    echo "help"
    sleep 1
    echo "who"
    sleep 1
    echo "look"
    sleep 1
    echo "quit"
} | telnet localhost $PORT 2>&1 | grep -v "Escape character" | tee -a $LOG

# Test 3: Character creation flow
echo -e "\n[TEST] Chargen test..." | tee -a $LOG
{
    sleep 1
    echo "testuser"
    sleep 1
    echo "testpass"
    sleep 1
    echo "quit"
} | telnet localhost $PORT 2>&1 | tee -a $LOG

echo -e "\n=== Test Complete ===" | tee -a $LOG
echo "Results saved to: $LOG"