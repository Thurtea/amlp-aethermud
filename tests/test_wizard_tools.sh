#!/bin/bash

# Wizard Tools Testing Script
# This script provides a guided walkthrough of wizard tool features
# Place this in /home/thurtea/amlp-driver/tests/ and run: bash test_wizard_tools.sh

RESET='\033[0m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'

DRIVER_PATH="/home/thurtea/amlp-driver"
TESTS_PASSED=0
TESTS_FAILED=0

# Helper functions
print_header() {
    echo -e "${BLUE}=== $1 ===${RESET}"
}

print_test() {
    echo -e "${YELLOW}→ $1${RESET}"
}

print_pass() {
    echo -e "${GREEN}✓ PASS: $1${RESET}"
    ((TESTS_PASSED++))
}

print_fail() {
    echo -e "${RED}✗ FAIL: $1${RESET}"
    ((TESTS_FAILED++))
}

# Verify driver is built
check_driver() {
    print_header "Checking Driver Build"
    
    if [ ! -f "$DRIVER_PATH/build/driver" ]; then
        print_fail "Driver executable not found"
        echo "Please build driver: cd $DRIVER_PATH && make"
        exit 1
    fi
    
    if [ ! -x "$DRIVER_PATH/build/driver" ]; then
        print_fail "Driver is not executable"
        exit 1
    fi
    
    print_pass "Driver executable found and is executable"
}

# Verify LPC files exist
check_files() {
    print_header "Checking Command Files"
    
    local files=(
        "lib/std/player.lpc"
        "lib/daemon/command.lpc"
        "lib/cmds/wizard/pwd.lpc"
        "lib/cmds/wizard/cd.lpc"
        "lib/cmds/ls.lpc"
        "lib/cmds/wizard/clone.lpc"
        "lib/cmds/wizard/load.lpc"
        "lib/cmds/wizard/update.lpc"
        "lib/cmds/wizard/destruct.lpc"
        "lib/cmds/wizard/cat.lpc"
        "lib/cmds/wizard/ed.lpc"
    )
    
    for file in "${files[@]}"; do
        if [ -f "$DRIVER_PATH/$file" ]; then
            print_pass "File exists: $file"
        else
            print_fail "File missing: $file"
        fi
    done
}

# Verify command registration
check_registration() {
    print_header "Checking Command Registration"
    
    local commands=(
        "pwd"
        "cd"
        "ls"
        "clone"
        "load"
        "update"
        "destruct"
        "cat"
        "ed"
    )
    
    for cmd in "${commands[@]}"; do
        if grep -q "commands\[\"$cmd\"\]" "$DRIVER_PATH/lib/daemon/command.lpc"; then
            print_pass "Command registered: $cmd"
        else
            print_fail "Command not registered: $cmd"
        fi
    done
}

# Verify working directory functions
check_working_dir() {
    print_header "Checking Working Directory Functions"
    
    local functions=(
        "set_cwd"
        "query_cwd"
        "resolve_path"
    )
    
    for func in "${functions[@]}"; do
        if grep -q "${func}" "$DRIVER_PATH/lib/std/player.lpc"; then
            print_pass "Function exists: $func"
        else
            print_fail "Function missing: $func"
        fi
    done
}

# Check code quality
check_code_quality() {
    print_header "Code Quality Checks"
    
    print_test "Checking for main() function signatures..."
    
    local wizard_cmds=(
        "pwd.lpc"
        "cd.lpc"
        "clone.lpc"
        "load.lpc"
        "update.lpc"
        "destruct.lpc"
        "cat.lpc"
        "ed.lpc"
    )
    
    for cmd in "${wizard_cmds[@]}"; do
        if grep -q "int main(string" "$DRIVER_PATH/lib/cmds/wizard/$cmd"; then
            print_pass "Correct function signature: $cmd"
        else
            print_fail "Invalid function signature: $cmd"
        fi
    done
}

# Check for common issues
check_common_issues() {
    print_header "Checking for Common Issues"
    
    # Check for color codes (should not exist in most commands)
    print_test "Checking for color codes..."
    if ! grep -q "%^" "$DRIVER_PATH/lib/cmds/wizard/pwd.lpc"; then
        print_pass "No color codes in pwd.lpc (good)"
    else
        print_fail "Color codes found in pwd.lpc"
    fi
    
    # Check for previous_object usage
    print_test "Checking for previous_object() usage..."
    if grep -q "previous_object()" "$DRIVER_PATH/lib/cmds/wizard/cd.lpc"; then
        print_pass "previous_object() found in cd.lpc"
    else
        print_fail "previous_object() missing in cd.lpc"
    fi
    
    # Check for tell_object usage
    print_test "Checking for tell_object() usage..."
    if grep -q "tell_object(player," "$DRIVER_PATH/lib/cmds/wizard/pwd.lpc"; then
        print_pass "tell_object() found in pwd.lpc"
    else
        print_fail "tell_object() missing in pwd.lpc"
    fi
}

# Verify compilation
check_compilation() {
    print_header "Verifying Driver Compilation"
    
    print_test "Checking if driver was recently compiled..."
    
    if [ -f "$DRIVER_PATH/build/driver" ]; then
        local build_time=$(stat -c %Y "$DRIVER_PATH/build/driver" 2>/dev/null || stat -f %m "$DRIVER_PATH/build/driver")
        local current_time=$(date +%s)
        local diff=$((current_time - build_time))
        
        if [ $diff -lt 3600 ]; then
            print_pass "Driver compiled within last hour"
        else
            print_test "Driver last compiled $(($diff / 60)) minutes ago"
            print_test "Recommend rebuilding: cd $DRIVER_PATH && make"
        fi
    fi
}

# Check git status
check_git() {
    print_header "Checking Git History"
    
    if [ -d "$DRIVER_PATH/.git" ]; then
        print_test "Checking recent commits..."
        
        local commits=$(cd "$DRIVER_PATH" && git log --oneline -5 2>/dev/null | grep -i "wizard\|phase" | wc -l)
        
        if [ $commits -gt 0 ]; then
            print_pass "Found wizard/phase commits in history"
            cd "$DRIVER_PATH" && git log --oneline -5 | head -5
        else
            print_fail "No wizard/phase commits found"
        fi
    else
        print_fail "Git repository not found"
    fi
}

# Summary
print_summary() {
    print_header "Test Summary"
    
    echo ""
    echo -e "Tests Passed:  ${GREEN}$TESTS_PASSED${RESET}"
    echo -e "Tests Failed:  ${RED}$TESTS_FAILED${RESET}"
    
    if [ $TESTS_FAILED -eq 0 ]; then
        echo ""
        echo -e "${GREEN}✓ All checks passed!${RESET}"
        echo ""
        echo "Next steps:"
        echo "1. Start the MUD server: $DRIVER_PATH/build/driver"
        echo "2. Log in and test wizard commands:"
        echo "   pwd              # Show current directory"
        echo "   ls               # List directory"
        echo "   cd /domains/tavern"
        echo "   clone /lib/std/weapon"
        echo "3. See WIZARD_TOOLS_GUIDE.md for detailed documentation"
        return 0
    else
        echo ""
        echo -e "${RED}✗ Some checks failed. Please review above.${RESET}"
        return 1
    fi
}

# Main execution
main() {
    echo ""
    echo -e "${BLUE}╔═══════════════════════════════════════════╗${RESET}"
    echo -e "${BLUE}║   AMLP Wizard Tools Testing Script        ║${RESET}"
    echo -e "${BLUE}║   Version 1.0                             ║${RESET}"
    echo -e "${BLUE}╚═══════════════════════════════════════════╝${RESET}"
    echo ""
    
    check_driver
    check_files
    check_registration
    check_working_dir
    check_code_quality
    check_common_issues
    check_compilation
    check_git
    
    echo ""
    print_summary
    
    local exit_code=$?
    
    echo ""
    echo -e "${BLUE}Tests completed at $(date)${RESET}"
    
    exit $exit_code
}

# Run main
main
