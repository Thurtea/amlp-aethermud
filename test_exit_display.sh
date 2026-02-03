#!/bin/bash
# Test exit display and character features

(
  # Wait for connection
  sleep 1
  # Enter username
  echo "testchar"
  sleep 1
  # New password
  echo "test123"
  sleep 1
  # Confirm password
  echo "test123"
  sleep 1
  # Select race: 1 (Human)
  echo "1"
  sleep 1
  # Confirm race
  echo "y"
  sleep 1
  # Gender: m
  echo "m"
  sleep 1  
  # Select OCC: 1 (first one)
  echo "1"
  sleep 1
  # Confirm OCC
  echo "y"
  sleep 1
  # Roll stats (keep rolling)
  echo ""
  sleep 1
  echo ""
  sleep 1
  # Accept stats
  echo "y"
  sleep 1
  # Accept default alignment
  echo ""
  sleep 1
  # Finish creation
  echo ""
  sleep 2
  # Look command
  echo "look"
  sleep 2
  # Check inventory
  echo "inventory"
  sleep 2
  # Check score
  echo "score"
  sleep 2
  # Quit
  echo "quit"
  sleep 1
) | timeout 45 nc localhost 3000
