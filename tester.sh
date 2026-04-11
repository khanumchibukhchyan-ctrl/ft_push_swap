#!/bin/bash

# ============================================================================
# Push_swap & Checker — Full Evaluation Test Suite
# Based on the 42 scale for push_swap
# ============================================================================

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

PUSH_SWAP="./push_swap"
CHECKER="./checker"

# Auto-detect system checker binary
if [ -f "./checker_linux" ]; then
    SYSTEM_CHECKER="./checker_linux"
elif [ -f "./checker_Mac" ]; then
    SYSTEM_CHECKER="./checker_Mac"
else
    SYSTEM_CHECKER=""
fi

PASS=0
FAIL=0
WARN=0
TOTAL=0

# ============================================================================
# Helper functions
# ============================================================================

print_header() {
    echo ""
    echo -e "${BOLD}${CYAN}═══════════════════════════════════════════════════${RESET}"
    echo -e "${BOLD}${CYAN}  $1${RESET}"
    echo -e "${BOLD}${CYAN}═══════════════════════════════════════════════════${RESET}"
}

pass() {
    echo -e "  ${GREEN}✓ PASS${RESET}: $1"
    ((PASS++))
    ((TOTAL++))
}

fail() {
    echo -e "  ${RED}✗ FAIL${RESET}: $1"
    ((FAIL++))
    ((TOTAL++))
}

warn() {
    echo -e "  ${YELLOW}⚠ WARN${RESET}: $1"
    ((WARN++))
}

info() {
    echo -e "  ${CYAN}ℹ INFO${RESET}: $1"
}

check_sort() {
    local args="$1"
    if [ -z "$SYSTEM_CHECKER" ]; then
        result=$($PUSH_SWAP $args | $CHECKER $args)
    else
        result=$($PUSH_SWAP $args | $SYSTEM_CHECKER $args)
    fi
    echo "$result"
}

count_ops() {
    local args="$1"
    $PUSH_SWAP $args | wc -l | tr -d ' '
}

count_ops_flag() {
    local flag="$1"
    local args="$2"
    $PUSH_SWAP $flag $args | wc -l | tr -d ' '
}

check_sort_flag() {
    local flag="$1"
    local args="$2"
    if [ -z "$SYSTEM_CHECKER" ]; then
        result=$($PUSH_SWAP $flag $args | $CHECKER $args)
    else
        result=$($PUSH_SWAP $flag $args | $SYSTEM_CHECKER $args)
    fi
    echo "$result"
}


# ============================================================================
# 0. PRELIMINARY CHECKS
# ============================================================================

print_header "0. PRELIMINARY CHECKS"

if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}ERROR: $PUSH_SWAP not found. Run 'make' first.${RESET}"
    exit 1
fi
pass "push_swap binary exists"

if [ ! -f "$CHECKER" ]; then
    warn "Bonus checker binary not found — bonus tests will be skipped"
    HAS_CHECKER=0
else
    pass "Checker binary exists"
    HAS_CHECKER=1
fi

if [ -n "$SYSTEM_CHECKER" ]; then
    info "System checker found: $SYSTEM_CHECKER"
else
    warn "No system checker (checker_linux / checker_Mac) found — using own checker"
fi


# ============================================================================
# 1. MAKEFILE
# ============================================================================

print_header "1. MAKEFILE"

if [ -f "Makefile" ]; then
    pass "Makefile exists"
else
    fail "Makefile not found"
fi

for rule in all clean fclean re; do
    if grep -q "^$rule" Makefile 2>/dev/null; then
        pass "Makefile has '$rule' rule"
    else
        fail "Makefile missing '$rule' rule"
    fi
done

if grep -q "\-Wall" Makefile && grep -q "\-Wextra" Makefile && grep -q "\-Werror" Makefile; then
    pass "Makefile uses -Wall -Wextra -Werror"
else
    fail "Makefile missing required compilation flags (-Wall -Wextra -Werror)"
fi


# ============================================================================
# 2. ERROR MANAGEMENT (push_swap)
# ============================================================================

print_header "2. ERROR MANAGEMENT (push_swap)"

output=$($PUSH_SWAP "a" "b" "c" 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Non-numeric parameters → 'Error' on stderr"
else
    fail "Non-numeric parameters → expected 'Error' on stderr, got: '$output'"
fi

output=$($PUSH_SWAP 1 2 3 2 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Duplicate numbers → 'Error' on stderr"
else
    fail "Duplicate numbers → expected 'Error' on stderr, got: '$output'"
fi

output=$($PUSH_SWAP 1 2 99999999999 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Number > INT_MAX → 'Error' on stderr"
else
    fail "Number > INT_MAX → expected 'Error' on stderr, got: '$output'"
fi

output=$($PUSH_SWAP 1 2 -99999999999 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Number < INT_MIN → 'Error' on stderr"
else
    fail "Number < INT_MIN → expected 'Error' on stderr, got: '$output'"
fi

output=$($PUSH_SWAP 2>&1)
if [ -z "$output" ]; then
    pass "No parameters → no output"
else
    fail "No parameters → expected no output, got: '$output'"
fi

output=$($PUSH_SWAP "" 2>&1 1>/dev/null)
if [ -z "$output" ] || echo "$output" | grep -q "Error"; then
    pass "Empty string parameter → no output or 'Error'"
else
    fail "Empty string parameter → unexpected output: '$output'"
fi

output=$($PUSH_SWAP 1 "abc" 3 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Mixed valid/invalid params → 'Error' on stderr"
else
    fail "Mixed valid/invalid params → expected 'Error'"
fi


# ============================================================================
# 3. STRATEGY SELECTION FLAGS
# ============================================================================

print_header "3. STRATEGY SELECTION FLAGS"

for flag in --simple --medium --complex --adaptive; do
    result=$(check_sort_flag "$flag" "5 4 3 2 1")
    if [ "$result" = "OK" ]; then
        ops=$(count_ops_flag "$flag" "5 4 3 2 1")
        pass "$flag 5 4 3 2 1 → OK ($ops ops)"
    else
        fail "$flag 5 4 3 2 1 → expected OK, got: '$result'"
    fi
done

result=$(check_sort "5 4 3 2 1")
if [ "$result" = "OK" ]; then
    pass "No flag (default) 5 4 3 2 1 → OK"
else
    fail "No flag (default) 5 4 3 2 1 → expected OK, got: '$result'"
fi


# ============================================================================
# 4. IDENTITY TEST — Already sorted inputs
# ============================================================================

print_header "4. IDENTITY TEST — Already sorted inputs"

identity_tests=("42" "2 3" "0 1 2 3" "0 1 2 3 4 5 6 7 8 9")
for args in "${identity_tests[@]}"; do
    ops=$(count_ops "$args")
    if [ "$ops" -eq 0 ]; then
        pass "Already sorted [$args] → 0 instructions"
    else
        fail "Already sorted [$args] → expected 0 instructions, got $ops"
    fi
done


# ============================================================================
# 5. SMALL INPUTS (3 numbers)
# ============================================================================

print_header "5. SMALL INPUTS (3 numbers)"

three_tests=("2 1 0" "0 2 1" "1 0 2" "1 2 0" "2 0 1")
for args in "${three_tests[@]}"; do
    result=$(check_sort "$args")
    ops=$(count_ops "$args")
    if [ "$result" = "OK" ]; then
        if [ "$ops" -le 3 ]; then
            pass "[$args] → OK, $ops ops (≤3, excellent)"
        elif [ "$ops" -le 5 ]; then
            pass "[$args] → OK, $ops ops (≤5, acceptable)"
        else
            warn "[$args] → OK, but $ops ops (>5, too many)"
            ((PASS++)); ((TOTAL++))
        fi
    else
        fail "[$args] → expected OK, got: '$result'"
    fi
done


# ============================================================================
# 6. MEDIUM INPUTS (5 numbers)
# ============================================================================

print_header "6. MEDIUM INPUTS (5 numbers)"

five_tests=("1 5 2 4 3" "5 1 4 2 3" "3 5 1 4 2" "5 4 3 2 1" "2 3 5 1 4")
for args in "${five_tests[@]}"; do
    result=$(check_sort "$args")
    ops=$(count_ops "$args")
    if [ "$result" = "OK" ]; then
        if [ "$ops" -le 12 ]; then
            pass "[$args] → OK, $ops ops (≤12, good)"
        elif [ "$ops" -le 15 ]; then
            pass "[$args] → OK, $ops ops (≤15, acceptable)"
        else
            warn "[$args] → OK, but $ops ops (>15, too many)"
            ((PASS++)); ((TOTAL++))
        fi
    else
        fail "[$args] → expected OK, got: '$result'"
    fi
done


# ============================================================================
# 7. BENCHMARK MODE
# ============================================================================

print_header "7. BENCHMARK MODE (--bench)"

stdout_out=$($PUSH_SWAP --bench --simple 5 4 3 2 1 2>/dev/null)
if [ -n "$stdout_out" ]; then
    pass "--bench --simple → produces instructions on stdout"
else
    fail "--bench --simple → no instructions on stdout"
fi

stderr_out=$($PUSH_SWAP --bench --simple 5 4 3 2 1 2>&1 1>/dev/null)
if [ -n "$stderr_out" ]; then
    pass "--bench --simple → produces benchmark info on stderr"
    if echo "$stderr_out" | grep -iq "disorder\|%"; then
        pass "Benchmark output contains disorder info"
    else
        warn "Benchmark output may be missing disorder percentage"
    fi
    if echo "$stderr_out" | grep -iq "strategy\|simple\|algorithm"; then
        pass "Benchmark output contains strategy info"
    else
        warn "Benchmark output may be missing strategy name"
    fi
    if echo "$stderr_out" | grep -iq "operation\|count\|total"; then
        pass "Benchmark output contains operations count"
    else
        warn "Benchmark output may be missing operations count"
    fi
else
    fail "--bench --simple → no benchmark info on stderr"
fi

stderr_sorted=$($PUSH_SWAP --bench --simple 1 2 3 4 5 2>&1 1>/dev/null)
info "Sorted input benchmark: $stderr_sorted"

stderr_reverse=$($PUSH_SWAP --bench --simple 5 4 3 2 1 2>&1 1>/dev/null)
info "Reverse sorted benchmark: $stderr_reverse"


# ============================================================================
# 8. LARGE INPUTS (100 numbers)
# ============================================================================

print_header "8. LARGE INPUTS (100 numbers)"

for i in 1 2 3; do
    ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
    result=$(check_sort "$ARG")
    ops=$(count_ops "$ARG")
    if [ "$result" = "OK" ]; then
        if [ "$ops" -lt 700 ]; then
            pass "100 numbers (run $i) → OK, $ops ops (<700, excellent)"
        elif [ "$ops" -lt 1500 ]; then
            pass "100 numbers (run $i) → OK, $ops ops (<1500, good)"
        elif [ "$ops" -lt 2000 ]; then
            pass "100 numbers (run $i) → OK, $ops ops (<2000, pass)"
        else
            fail "100 numbers (run $i) → OK but $ops ops (≥2000, too many)"
        fi
    else
        fail "100 numbers (run $i) → expected OK, got: '$result'"
    fi
done


# ============================================================================
# 9. STRATEGY FLAGS COMPARISON (50 numbers)
# ============================================================================

print_header "9. STRATEGY FLAGS COMPARISON (50 numbers)"

ARG50=$(shuf -i 1-200 -n 50 | tr '\n' ' ')
info "Testing with same 50 numbers across strategies"

for flag in --simple --medium --complex --adaptive; do
    result=$(check_sort_flag "$flag" "$ARG50")
    ops=$(count_ops_flag "$flag" "$ARG50")
    if [ "$result" = "OK" ]; then
        pass "$flag → OK, $ops ops"
    else
        fail "$flag → expected OK, got: '$result'"
    fi
done


# ============================================================================
# 10. VERY LARGE INPUTS (500 numbers)
# ============================================================================

print_header "10. VERY LARGE INPUTS (500 numbers)"

for i in 1 2; do
    ARG=$(shuf -i 1-1000 -n 500 | tr '\n' ' ')
    result=$(check_sort "$ARG")
    ops=$(count_ops "$ARG")
    if [ "$result" = "OK" ]; then
        if [ "$ops" -lt 5500 ]; then
            pass "500 numbers (run $i) → OK, $ops ops (<5500, excellent)"
        elif [ "$ops" -lt 8000 ]; then
            pass "500 numbers (run $i) → OK, $ops ops (<8000, good)"
        elif [ "$ops" -lt 12000 ]; then
            pass "500 numbers (run $i) → OK, $ops ops (<12000, pass)"
        else
            fail "500 numbers (run $i) → OK but $ops ops (≥12000, too many)"
        fi
    else
        fail "500 numbers (run $i) → expected OK, got: '$result'"
    fi
done


# ============================================================================
# 11. BONUS — CHECKER ERROR MANAGEMENT
# ============================================================================

if [ "$HAS_CHECKER" -eq 1 ]; then

print_header "11. BONUS — CHECKER ERROR MANAGEMENT"

output=$($CHECKER "a" "b" "c" < /dev/null 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Checker: non-numeric params → 'Error'"
else
    fail "Checker: non-numeric params → expected 'Error', got: '$output'"
fi

output=$($CHECKER 1 2 3 2 < /dev/null 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Checker: duplicate numbers → 'Error'"
else
    fail "Checker: duplicate numbers → expected 'Error', got: '$output'"
fi

output=$($CHECKER 1 2 99999999999 < /dev/null 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Checker: number > INT_MAX → 'Error'"
else
    fail "Checker: number > INT_MAX → expected 'Error', got: '$output'"
fi

output=$($CHECKER < /dev/null 2>&1)
if [ -z "$output" ]; then
    pass "Checker: no params → no output"
else
    fail "Checker: no params → expected no output, got: '$output'"
fi

output=$(printf "invalid_op\n" | $CHECKER 1 2 3 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Checker: invalid instruction → 'Error'"
else
    fail "Checker: invalid instruction → expected 'Error', got: '$output'"
fi

output=$(printf " sa \n" | $CHECKER 3 2 1 2>&1 1>/dev/null)
if echo "$output" | grep -q "Error"; then
    pass "Checker: instruction with spaces → 'Error'"
else
    fail "Checker: instruction with spaces → expected 'Error', got: '$output'"
fi


# ============================================================================
# 12. BONUS — CHECKER FALSE TESTS (should output KO)
# ============================================================================

print_header "12. BONUS — CHECKER FALSE TESTS"

# From the scale: [0 9 1 8 2 7 3 6 4 5] with sa, pb, rrr
output=$(printf "sa\npb\nrrr\n" | $CHECKER 0 9 1 8 2 7 3 6 4 5)
if [ "$output" = "KO" ]; then
    pass "Checker: [0 9 1 8 2 7 3 6 4 5] with sa,pb,rrr → KO"
else
    fail "Checker: [0 9 1 8 2 7 3 6 4 5] with sa,pb,rrr → expected KO, got: '$output'"
fi

# sa,sa cancels out — stack stays unsorted
output=$(printf "sa\nsa\n" | $CHECKER 5 3 1 4 2)
if [ "$output" = "KO" ]; then
    pass "Checker: [5 3 1 4 2] with sa,sa → KO"
else
    fail "Checker: [5 3 1 4 2] with sa,sa → expected KO, got: '$output'"
fi

# pb moves top to b — b not empty so KO
output=$(printf "pb\n" | $CHECKER 3 1 2)
if [ "$output" = "KO" ]; then
    pass "Checker: [3 1 2] with pb → KO (b not empty)"
else
    fail "Checker: [3 1 2] with pb → expected KO, got: '$output'"
fi

# ra on 4 reverse-sorted: [4 3 2 1] → [3 2 1 4] — still unsorted
output=$(printf "ra\n" | $CHECKER 4 3 2 1)
if [ "$output" = "KO" ]; then
    pass "Checker: [4 3 2 1] with ra → KO"
else
    fail "Checker: [4 3 2 1] with ra → expected KO, got: '$output'"
fi


# ============================================================================
# 13. BONUS — CHECKER CORRECT TESTS (should output OK)
# ============================================================================

print_header "13. BONUS — CHECKER CORRECT TESTS"

# Already sorted, EOF immediately — no instructions
output=$($CHECKER 0 1 2 < /dev/null)
if [ "$output" = "OK" ]; then
    pass "Checker: [0 1 2] with no instructions (EOF) → OK"
else
    fail "Checker: [0 1 2] no instructions → expected OK, got: '$output'"
fi

# From the scale: [0 9 1 8 2] with pb,ra,pb,ra,sa,ra,pa,pa
output=$(printf "pb\nra\npb\nra\nsa\nra\npa\npa\n" | $CHECKER 0 9 1 8 2)
if [ "$output" = "OK" ]; then
    pass "Checker: [0 9 1 8 2] with pb,ra,pb,ra,sa,ra,pa,pa → OK"
else
    fail "Checker: [0 9 1 8 2] with pb,ra,pb,ra,sa,ra,pa,pa → expected OK, got: '$output'"
fi

# sa sorts [2 1 3]
output=$(printf "sa\n" | $CHECKER 2 1 3)
if [ "$output" = "OK" ]; then
    pass "Checker: [2 1 3] with sa → OK"
else
    fail "Checker: [2 1 3] with sa → expected OK, got: '$output'"
fi

# Self-consistency: push_swap output piped into own checker
for args in "5 4 3 2 1" "42 0 -1 100 7" "3 2 1"; do
    instructions=$($PUSH_SWAP $args)
    output=$(echo "$instructions" | $CHECKER $args)
    if [ "$output" = "OK" ]; then
        pass "Self-consistency: [$args] → OK"
    else
        fail "Self-consistency: [$args] → expected OK, got: '$output'"
    fi
done

# Self-consistency with 100 random numbers
ARG100=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
instructions=$($PUSH_SWAP $ARG100)
output=$(echo "$instructions" | $CHECKER $ARG100)
if [ "$output" = "OK" ]; then
    pass "Self-consistency: 100 random numbers → OK"
else
    fail "Self-consistency: 100 random numbers → expected OK"
fi

# Self-consistency with 500 random numbers
ARG500=$(shuf -i 1-1000 -n 500 | tr '\n' ' ')
instructions=$($PUSH_SWAP $ARG500)
output=$(echo "$instructions" | $CHECKER $ARG500)
if [ "$output" = "OK" ]; then
    pass "Self-consistency: 500 random numbers → OK"
else
    fail "Self-consistency: 500 random numbers → expected OK"
fi

fi  # end HAS_CHECKER


# ============================================================================
# SUMMARY
# ============================================================================

print_header "SUMMARY"
echo ""
echo -e "  ${GREEN}Passed : $PASS${RESET}"
echo -e "  ${RED}Failed : $FAIL${RESET}"
echo -e "  ${YELLOW}Warnings: $WARN${RESET}"
echo -e "  Total  : $TOTAL"
echo ""

if [ "$FAIL" -eq 0 ]; then
    echo -e "  ${GREEN}${BOLD}All tests passed!${RESET}"
else
    echo -e "  ${RED}${BOLD}Some tests failed. Review output above.${RESET}"
fi

echo ""
exit $FAIL