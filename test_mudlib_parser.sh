#!/bin/bash
# AMLP MUD Driver - Mudlib Parser Validation Suite

cd ~/amlp-driver

RESULTS_DIR="mudlib_test_results_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$RESULTS_DIR"

TOTAL_FILES=0
PASSED_FILES=0
FAILED_FILES=0

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo "═══════════════════════════════════════════════════════════════"
echo "  AMLP MUDLIB PARSER VALIDATION SUITE"
echo "  Date: $(date)"
echo "═══════════════════════════════════════════════════════════════"
echo ""

test_file() {
    local filepath="$1"
    local category="$2"
    
    ((TOTAL_FILES++))
    
    ./build/driver --parse-test "$filepath" > "$RESULTS_DIR/$(basename "$filepath").log" 2>&1
    
    if [ $? -eq 0 ]; then
        ((PASSED_FILES++))
        echo -e "${GREEN}✅ PASS${NC} | $category | $(basename "$filepath")"
    else
        ((FAILED_FILES++))
        echo -e "${RED}❌ FAIL${NC} | $category | $(basename "$filepath")"
        grep -E "Error|Expected|Unexpected" "$RESULTS_DIR/$(basename "$filepath").log" | head -2 | sed 's/^/         /'
    fi
}

# Test Master
echo -e "${BLUE}PRIORITY 1: MASTER OBJECT${NC}"
echo ""
if [ -f lib/master.lpc ]; then
    test_file "lib/master.lpc" "CRITICAL"
elif [ -f lib/secure/master.lpc ]; then
    test_file "lib/secure/master.lpc" "CRITICAL"
fi
echo ""

# Test Standard Objects
echo -e "${BLUE}PRIORITY 2: STANDARD OBJECTS${NC}"
echo ""
find lib*/std -name "*.lpc" -o -name "*.c" 2>/dev/null | sort | while read file; do
    test_file "$file" "STD"
done
echo ""

# Test Commands
echo -e "${BLUE}PRIORITY 3: COMMAND FILES${NC}"
echo ""
find lib*/cmds -name "*.lpc" -o -name "*.c" 2>/dev/null | sort | head -10 | while read file; do
    test_file "$file" "CMD"
done
echo ""

# Summary
echo "═══════════════════════════════════════════════════════════════"
echo "  SUMMARY"
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "Total: $TOTAL_FILES"
echo -e "Passed: ${GREEN}$PASSED_FILES${NC}"
echo -e "Failed: ${RED}$FAILED_FILES${NC}"
echo ""
echo "Results saved to: $RESULTS_DIR/"
echo ""

# Error analysis
if [ $FAILED_FILES -gt 0 ]; then
    echo "Common error patterns:"
    grep -h "Error\|Expected\|Unexpected" $RESULTS_DIR/*.log 2>/dev/null | \
        sort | uniq -c | sort -rn | head -5 | sed 's/^/  /'
fi
