#!/bin/bash
# Test script for pagination in character creation

echo "=== Testing Pagination in Character Creation ==="
echo ""
echo "Creating character with username: testpagination"
echo ""

(
  echo "testpagination"  # Username
  sleep 0.5
  echo "TestPass123"  # Password
  sleep 0.5
  echo "TestPass123"  # Confirm password
  sleep 0.5
  echo "n"  # Next page (races page 1 -> 2)
  sleep 0.5
  echo "n"  # Next page (races page 2 -> 3)
  sleep 0.5
  echo "25"  # Select race 25 (should be on page 3)
  sleep 0.5
  echo "n"  # Next page (occs page 1 -> 2)
  sleep 0.5
  echo "15"  # Select OCC 15 (should be on page 2)
  sleep 0.5
  echo "yes"  # Accept stats
  sleep 1
  echo "quit"  # Quit
  sleep 0.5
) | nc localhost 3000

echo ""
echo "=== Test Complete ==="
