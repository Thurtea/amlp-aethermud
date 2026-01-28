#!/bin/bash

# Script to rename LPC library files from .c to .lpc
# Runs from /home/thurtea/amlp-driver
# 
# RENAMES:
#   - All .c files in lib/ (recursive)
#   - All .c files in tests/lpc/
# 
# PRESERVES:
#   - All .c files in src/ (C driver code)
#   - All test_*.c and demo_*.c files in tests/ (C test code)

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counter for renamed files
count=0

echo -e "${YELLOW}Starting LPC file renaming...${NC}\n"

# Function to rename files in a directory
rename_in_dir() {
    local dir=$1
    local pattern=$2
    
    if [ ! -d "$dir" ]; then
        echo -e "${YELLOW}Directory $dir does not exist, skipping${NC}"
        return
    fi
    
    echo -e "${GREEN}Processing: $dir${NC}"
    
    # Find all .c files and rename them to .lpc
    while IFS= read -r -d '' file; do
        if [ -f "$file" ]; then
            newfile="${file%.c}.lpc"
            echo "  Renaming: $file → $newfile"
            mv "$file" "$newfile"
            ((count++))
        fi
    done < <(find "$dir" -type f -name "$pattern" -print0)
}

# Rename files in lib directories
echo -e "\n${YELLOW}=== Renaming LPC Library Files ===${NC}\n"

rename_in_dir "lib/clone" "*.c"
rename_in_dir "lib/cmds" "*.c"
rename_in_dir "lib/domains" "*.c"
rename_in_dir "lib/secure" "*.c"
rename_in_dir "lib/single" "*.c"
rename_in_dir "lib/std" "*.c"

# Rename master.c if it exists
if [ -f "lib/master.c" ]; then
    echo -e "${GREEN}Processing: lib/master.c${NC}"
    echo "  Renaming: lib/master.c → lib/master.lpc"
    mv "lib/master.c" "lib/master.lpc"
    ((count++))
fi

# Rename files in tests/lpc
echo -e "\n${YELLOW}=== Renaming LPC Test Files ===${NC}\n"
rename_in_dir "tests/lpc" "*.c"

# Summary
echo -e "\n${GREEN}=== Renaming Complete ===${NC}"
echo -e "${GREEN}Total files renamed: $count${NC}"
echo -e "\n${YELLOW}Files NOT renamed (as expected):${NC}"
echo "  - src/*.c (C driver files)"
echo "  - tests/test_*.c (C test files)"
echo "  - tests/demo_*.c (C demo files)"

# Verification
echo -e "\n${YELLOW}=== Verification ===${NC}"
echo "Remaining .c files in lib/:"
remaining_lib=$(find lib -name "*.c" 2>/dev/null | wc -l)
echo "  $remaining_lib (should be 0)"

echo "Remaining .c files in tests/lpc/:"
remaining_test=$(find tests/lpc -name "*.c" 2>/dev/null | wc -l)
echo "  $remaining_test (should be 0)"

echo "New .lpc files in lib/:"
new_lpc=$(find lib -name "*.lpc" 2>/dev/null | wc -l)
echo "  $new_lpc"

if [ "$remaining_lib" -eq 0 ] && [ "$remaining_test" -eq 0 ]; then
    echo -e "\n${GREEN}✓ Renaming successful!${NC}"
else
    echo -e "\n${RED}⚠ Warning: Some .c files remain in lib/ or tests/lpc/${NC}"
fi
