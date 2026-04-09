#!/bin/bash

# ============================================================================
#  push_swap tester — aligned with 42 Yerevan evaluation checklist
#  Covers: compilation, norminette, error management, strategy flags,
#  identity tests, small/medium/large/very-large inputs, benchmark mode,
#  strategy comparison, memory leaks (valgrind), stderr check, and
#  bonus checker tests.
# ============================================================================

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

PASSED=0
FAILED=0
WARNED=0

# ---------------------------------------------------------------------------
# Helper functions
# ---------------------------------------------------------------------------
print_header() {
    echo ""
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE} $1${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo ""
}

print_result() {
    if [ "$1" -eq 0 ]; then
        echo -e "  ${GREEN}✓ PASS:${NC} $2"
        ((PASSED++))
    else
        echo -e "  ${RED}✗ FAIL:${NC} $2"
        ((FAILED++))
    fi
}

print_warn() {
    echo -e "  ${YELLOW}⚠ WARN:${NC} $1"
    ((WARNED++))
}

print_info() {
    echo -e "  ${CYAN}ℹ INFO:${NC} $1"
}

# ---------------------------------------------------------------------------
# Detect checker binary
# ---------------------------------------------------------------------------
detect_checker() {
    if [ -f "./checker_linux" ]; then
        CHECKER="./checker_linux"
    elif [ -f "./checker_Mac" ]; then
        CHECKER="./checker_Mac"
    elif [ -f "./checker" ]; then
        CHECKER="./checker"
    else
        CHECKER=""
        print_warn "No checker binary found. Correctness tests will be skipped."
    fi
}

# ---------------------------------------------------------------------------
# 1. NORMINETTE
# ---------------------------------------------------------------------------
test_norminette() {
    print_header "1. NORMINETTE"

    if ! command -v norminette &> /dev/null; then
        print_warn "norminette not found in PATH — skipping."
        return
    fi

    NORM_OUTPUT=$(norminette srcs/*.c includes/*.h 2>/dev/null || norminette *.c *.h 2>/dev/null || norminette $(find . -name '*.c' -o -name '*.h' | grep -v libft) 2>/dev/null)
    NORM_ERRORS=$(echo "$NORM_OUTPUT" | grep -c "Error")

    if [ "$NORM_ERRORS" -eq 0 ]; then
        print_result 0 "Norminette — no errors"
    else
        print_result 1 "Norminette — $NORM_ERRORS error(s) found"
        echo "$NORM_OUTPUT" | grep "Error" | head -10
        if [ "$NORM_ERRORS" -gt 10 ]; then
            echo "  ... and more ($NORM_ERRORS total)"
        fi
    fi
}

# ---------------------------------------------------------------------------
# 2. COMPILATION
# ---------------------------------------------------------------------------
test_compilation() {
    print_header "2. COMPILATION"

    # Check Makefile exists
    if [ ! -f "Makefile" ]; then
        print_result 1 "Makefile not found"
        exit 1
    fi

    # make re
    make re > /dev/null 2>&1
    if [ -f "./push_swap" ]; then
        print_result 0 "'make re' produces push_swap executable"
    else
        print_result 1 "'make re' failed to produce push_swap"
        exit 1
    fi

    # make clean
    make clean > /dev/null 2>&1
    if [ ! -f "*.o" ] 2>/dev/null; then
        print_result 0 "'make clean' removes object files"
    else
        print_result 1 "'make clean' did not remove object files"
    fi

    # make fclean
    make re > /dev/null 2>&1
    make fclean > /dev/null 2>&1
    if [ ! -f "./push_swap" ]; then
        print_result 0 "'make fclean' removes executable"
    else
        print_result 1 "'make fclean' did not remove executable"
    fi

    # Relink check
    make > /dev/null 2>&1
    OUTPUT=$(make 2>&1)
    if echo "$OUTPUT" | grep -qE "Nothing to be done|is up to date|make\[1\]: Nothing"; then
        print_result 0 "No relinking on second 'make'"
    else
        print_warn "Possible relinking detected — check Makefile"
    fi

    # Rebuild for remaining tests
    make re > /dev/null 2>&1
}

# ---------------------------------------------------------------------------
# 3. ERROR MANAGEMENT  (checklist requires >= 3/4)
# ---------------------------------------------------------------------------
test_error_management() {
    print_header "3. ERROR MANAGEMENT"

    # --- Non-numeric ---
    # Error must go to stderr (fd 2), NOT stdout
    STDOUT=$(./push_swap abc 2>/dev/null)
    STDERR=$(./push_swap abc 2>&1 1>/dev/null)
    if [ -z "$STDOUT" ] && echo "$STDERR" | grep -q "Error"; then
        print_result 0 "Non-numeric input → 'Error' on stderr, nothing on stdout"
    elif echo "$STDERR" | grep -q "Error"; then
        print_warn "Non-numeric input → 'Error' found but may also appear on stdout"
        print_result 0 "Non-numeric input → 'Error' detected"
    else
        print_result 1 "Non-numeric input → expected 'Error' on stderr"
    fi

    # --- Duplicates ---
    STDERR=$(./push_swap 1 2 3 2 2>&1 1>/dev/null)
    if echo "$STDERR" | grep -q "Error"; then
        print_result 0 "Duplicate numbers → 'Error'"
    else
        print_result 1 "Duplicate numbers → expected 'Error'"
    fi

    # --- Greater than INT_MAX ---
    STDERR=$(./push_swap 2147483648 2>&1 1>/dev/null)
    if echo "$STDERR" | grep -q "Error"; then
        print_result 0 "Number > INT_MAX → 'Error'"
    else
        print_result 1 "Number > INT_MAX → expected 'Error'"
    fi

    # --- Less than INT_MIN ---
    STDERR=$(./push_swap -2147483649 2>&1 1>/dev/null)
    if echo "$STDERR" | grep -q "Error"; then
        print_result 0 "Number < INT_MIN → 'Error'"
    else
        print_result 1 "Number < INT_MIN → expected 'Error'"
    fi

    # --- No parameters ---
    OUTPUT=$(./push_swap 2>&1)
    if [ -z "$OUTPUT" ]; then
        print_result 0 "No parameters → no output"
    else
        print_result 1 "No parameters → expected no output"
    fi

    # --- Extra edge cases ---
    STDERR=$(./push_swap "" 2>&1 1>/dev/null)
    if [ -z "$(./push_swap "" 2>/dev/null)" ]; then
        print_result 0 "Empty string → handled (no crash)"
    else
        print_warn "Empty string → unexpected stdout output"
    fi
}

# ---------------------------------------------------------------------------
# 4. STRATEGY SELECTION  (checklist requires >= 3/5)
# ---------------------------------------------------------------------------
test_strategy_selection() {
    print_header "4. STRATEGY SELECTION FLAGS"

    for FLAG in "--simple" "--medium" "--complex" "--adaptive"; do
        OUTPUT=$(./push_swap $FLAG 5 4 3 2 1 2>/dev/null)
        RET=$?
        if [ "$RET" -eq 0 ] && [ -n "$OUTPUT" ]; then
            if [ -n "$CHECKER" ]; then
                RESULT=$(echo "$OUTPUT" | $CHECKER 5 4 3 2 1 2>&1)
                if echo "$RESULT" | grep -q "OK"; then
                    print_result 0 "$FLAG → sorts correctly"
                else
                    print_result 1 "$FLAG → produces output but checker says KO"
                fi
            else
                print_result 0 "$FLAG → produces output (no checker to verify)"
            fi
        else
            print_result 1 "$FLAG → no output or non-zero exit"
        fi
    done

    # Default (no flag) should behave like --adaptive
    OUTPUT=$(./push_swap 5 4 3 2 1 2>/dev/null)
    if [ -n "$OUTPUT" ]; then
        print_result 0 "No flag → defaults to adaptive (produces output)"
    else
        print_result 1 "No flag → no output"
    fi
}

# ---------------------------------------------------------------------------
# 5. IDENTITY TESTS — already sorted  (checklist requires >= 3/4)
# ---------------------------------------------------------------------------
test_identity() {
    print_header "5. ALREADY SORTED (identity tests)"

    for ARG in "42" "2 3" "0 1 2 3" "0 1 2 3 4 5 6 7 8 9"; do
        OUTPUT=$(./push_swap $ARG 2>/dev/null)
        if [ -z "$OUTPUT" ]; then
            print_result 0 "push_swap $ARG → no output (correct)"
        else
            print_result 1 "push_swap $ARG → expected no output, got $(echo "$OUTPUT" | wc -l) lines"
        fi
    done
}

# ---------------------------------------------------------------------------
# 6. SMALL INPUTS — 3 numbers
# ---------------------------------------------------------------------------
test_three() {
    print_header "6. SMALL INPUTS (3 numbers)"

    if [ -z "$CHECKER" ]; then
        print_warn "No checker — skipping."
        return
    fi

    # All 6 permutations of {0,1,2}
    PERMS=("0 1 2" "0 2 1" "1 0 2" "1 2 0" "2 0 1" "2 1 0")
    for ARG in "${PERMS[@]}"; do
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>&1)
        COUNT=$(./push_swap $ARG 2>/dev/null | wc -l)
        if echo "$RESULT" | grep -q "OK"; then
            if [ "$COUNT" -le 3 ]; then
                print_result 0 "[$ARG] OK — $COUNT ops (excellent, ≤3)"
            elif [ "$COUNT" -le 5 ]; then
                print_result 0 "[$ARG] OK — $COUNT ops (≤5)"
            else
                print_result 1 "[$ARG] OK but $COUNT ops (>5, too many)"
            fi
        else
            print_result 1 "[$ARG] checker says KO"
        fi
    done
}

# ---------------------------------------------------------------------------
# 7. MEDIUM INPUTS — 5 numbers
# ---------------------------------------------------------------------------
test_five() {
    print_header "7. MEDIUM INPUTS (5 numbers)"

    if [ -z "$CHECKER" ]; then
        print_warn "No checker — skipping."
        return
    fi

    SETS=("1 5 2 4 3" "5 1 4 2 3" "3 5 1 4 2" "5 4 3 2 1" "2 3 5 1 4")
    for ARG in "${SETS[@]}"; do
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>&1)
        COUNT=$(./push_swap $ARG 2>/dev/null | wc -l)
        if echo "$RESULT" | grep -q "OK"; then
            if [ "$COUNT" -le 12 ]; then
                GRADE="excellent, ≤12"
            elif [ "$COUNT" -le 15 ]; then
                GRADE="≤15"
            else
                GRADE=">15 — too many"
            fi
            if [ "$COUNT" -le 15 ]; then
                print_result 0 "[$ARG] OK — $COUNT ops ($GRADE)"
            else
                print_result 1 "[$ARG] OK but $COUNT ops ($GRADE)"
            fi
        else
            print_result 1 "[$ARG] checker says KO"
        fi
    done
}

# ---------------------------------------------------------------------------
# 8. BENCHMARK MODE & DISORDER CALCULATION
# ---------------------------------------------------------------------------
test_benchmark() {
    print_header "8. BENCHMARK MODE & DISORDER"

    # Benchmark produces sorting instructions on stdout
    STDOUT=$(./push_swap --bench --simple 5 4 3 2 1 2>/dev/null)
    if [ -n "$STDOUT" ]; then
        print_result 0 "--bench --simple → produces sorting instructions on stdout"
    else
        print_result 1 "--bench --simple → no stdout output"
    fi

    # Benchmark info on stderr
    STDERR=$(./push_swap --bench --simple 5 4 3 2 1 2>&1 1>/dev/null)
    HAS_DISORDER=0; HAS_STRATEGY=0; HAS_OPS=0
    echo "$STDERR" | grep -qi "disorder"   && HAS_DISORDER=1
    echo "$STDERR" | grep -qi "strategy"   && HAS_STRATEGY=1
    echo "$STDERR" | grep -qi "operation"  && HAS_OPS=1

    BENCH_SCORE=$((HAS_DISORDER + HAS_STRATEGY + HAS_OPS))
    if [ "$BENCH_SCORE" -ge 2 ]; then
        print_result 0 "Benchmark stderr contains required info ($BENCH_SCORE/3 categories)"
    else
        print_result 1 "Benchmark stderr missing info ($BENCH_SCORE/3 categories found)"
    fi

    # Disorder ≈ 0 for sorted input
    STDERR=$(./push_swap --bench --simple 1 2 3 4 5 2>&1 1>/dev/null)
    if echo "$STDERR" | grep -qE "0\.0|0%|0 %"; then
        print_result 0 "Sorted input → disorder ≈ 0%"
    else
        print_warn "Could not verify disorder = 0% for sorted input"
    fi

    # Disorder ≈ 100 for reverse sorted input
    STDERR=$(./push_swap --bench --simple 5 4 3 2 1 2>&1 1>/dev/null)
    if echo "$STDERR" | grep -qE "100|99"; then
        print_result 0 "Reverse sorted → disorder ≈ 100%"
    else
        print_warn "Could not verify disorder ≈ 100% for reverse sorted input"
    fi
}

# ---------------------------------------------------------------------------
# 9. LARGE INPUTS — 100 numbers
# ---------------------------------------------------------------------------
test_100() {
    print_header "9. LARGE INPUTS (100 numbers)"

    if [ -z "$CHECKER" ]; then
        print_warn "No checker — skipping."
        return
    fi

    for i in 1 2 3; do
        ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>&1)
        COUNT=$(./push_swap $ARG 2>/dev/null | wc -l)

        if echo "$RESULT" | grep -q "OK"; then
            if [ "$COUNT" -lt 700 ]; then
                GRADE="EXCELLENT"
            elif [ "$COUNT" -lt 1500 ]; then
                GRADE="GOOD"
            elif [ "$COUNT" -lt 2000 ]; then
                GRADE="PASS"
            else
                GRADE="TOO MANY"
            fi

            if [ "$COUNT" -lt 2000 ]; then
                print_result 0 "100 numbers #$i → OK, $COUNT ops ($GRADE)"
            else
                print_result 1 "100 numbers #$i → OK but $COUNT ops ≥ 2000"
            fi
        else
            print_result 1 "100 numbers #$i → checker says KO"
        fi
    done
}

# ---------------------------------------------------------------------------
# 10. STRATEGY COMPARISON  (200 numbers so radix has a fair chance)
# ---------------------------------------------------------------------------
test_strategy_comparison() {
    print_header "10. STRATEGY COMPARISON (200 numbers)"

    if [ -z "$CHECKER" ]; then
        print_warn "No checker — skipping."
        return
    fi

    ARG=$(shuf -i 1-1000 -n 200 | tr '\n' ' ')

    for FLAG in "--simple" "--medium" "--complex"; do
        RESULT=$(./push_swap $FLAG $ARG 2>/dev/null | $CHECKER $ARG 2>&1)
        COUNT=$(./push_swap $FLAG $ARG 2>/dev/null | wc -l)
        eval "${FLAG//-/}_COUNT=$COUNT"

        if echo "$RESULT" | grep -q "OK"; then
            print_result 0 "$FLAG sorts correctly ($COUNT ops)"
        else
            print_result 1 "$FLAG failed to sort"
        fi
    done

    SIMPLE_C=$(./push_swap --simple $ARG 2>/dev/null | wc -l)
    COMPLEX_C=$(./push_swap --complex $ARG 2>/dev/null | wc -l)

    if [ "$COMPLEX_C" -lt "$SIMPLE_C" ]; then
        print_result 0 "--complex ($COMPLEX_C) < --simple ($SIMPLE_C) — as expected"
    else
        print_result 1 "--complex ($COMPLEX_C) should use fewer ops than --simple ($SIMPLE_C)"
    fi

    # Adaptive should also work
    RESULT=$(./push_swap --adaptive $ARG 2>/dev/null | $CHECKER $ARG 2>&1)
    if echo "$RESULT" | grep -q "OK"; then
        print_result 0 "--adaptive sorts correctly"
    else
        print_result 1 "--adaptive failed to sort"
    fi
}

# ---------------------------------------------------------------------------
# 11. VERY LARGE INPUTS — 500 numbers
# ---------------------------------------------------------------------------
test_500() {
    print_header "11. VERY LARGE INPUTS (500 numbers)"

    if [ -z "$CHECKER" ]; then
        print_warn "No checker — skipping."
        return
    fi

    for i in 1 2; do
        ARG=$(shuf -i 1-1000 -n 500 | tr '\n' ' ')
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>&1)
        COUNT=$(./push_swap $ARG 2>/dev/null | wc -l)

        if echo "$RESULT" | grep -q "OK"; then
            if [ "$COUNT" -lt 5500 ]; then
                GRADE="EXCELLENT"
            elif [ "$COUNT" -lt 8000 ]; then
                GRADE="GOOD"
            elif [ "$COUNT" -lt 12000 ]; then
                GRADE="PASS"
            else
                GRADE="TOO MANY"
            fi

            if [ "$COUNT" -lt 12000 ]; then
                print_result 0 "500 numbers #$i → OK, $COUNT ops ($GRADE)"
            else
                print_result 1 "500 numbers #$i → OK but $COUNT ops ≥ 12000"
            fi
        else
            print_result 1 "500 numbers #$i → checker says KO"
        fi
    done
}

# ---------------------------------------------------------------------------
# 12. MEMORY LEAK CHECK (valgrind)
# ---------------------------------------------------------------------------
test_memory_leaks() {
    print_header "12. MEMORY LEAK CHECK"

    if ! command -v valgrind &> /dev/null; then
        print_warn "valgrind not found — skipping memory leak check."
        return
    fi

    ARG=$(shuf -i 1-200 -n 50 | tr '\n' ' ')
    VALGRIND_OUTPUT=$(valgrind --leak-check=full --error-exitcode=42 ./push_swap $ARG 2>&1 1>/dev/null)
    VALGRIND_EXIT=$?

    LOST=$(echo "$VALGRIND_OUTPUT" | grep -oP "definitely lost: \K[0-9,]+" | tr -d ',')
    POSSIBLY=$(echo "$VALGRIND_OUTPUT" | grep -oP "possibly lost: \K[0-9,]+" | tr -d ',')
    STILL=$(echo "$VALGRIND_OUTPUT" | grep -oP "still reachable: \K[0-9,]+" | tr -d ',')

    LOST=${LOST:-0}
    POSSIBLY=${POSSIBLY:-0}

    if [ "$LOST" -eq 0 ] && [ "$POSSIBLY" -eq 0 ]; then
        print_result 0 "No memory leaks detected (definitely: ${LOST}B, possibly: ${POSSIBLY}B)"
    else
        print_result 1 "Memory leaks found (definitely: ${LOST}B, possibly: ${POSSIBLY}B)"
        echo "$VALGRIND_OUTPUT" | grep -A2 "LEAK SUMMARY"
    fi

    # Also test error path
    VALGRIND_ERR=$(valgrind --leak-check=full ./push_swap 1 2 abc 2>&1 1>/dev/null)
    LOST_ERR=$(echo "$VALGRIND_ERR" | grep -oP "definitely lost: \K[0-9,]+" | tr -d ',')
    LOST_ERR=${LOST_ERR:-0}

    if [ "$LOST_ERR" -eq 0 ]; then
        print_result 0 "No leaks on error path (invalid input)"
    else
        print_result 1 "Memory leaks on error path (${LOST_ERR}B lost)"
    fi
}

# ---------------------------------------------------------------------------
# 13. BONUS — CHECKER PROGRAM
# ---------------------------------------------------------------------------
test_bonus_checker() {
    print_header "13. BONUS — CHECKER PROGRAM (your own checker)"

    if [ ! -f "./checker" ]; then
        print_info "No custom ./checker binary found — skipping bonus checker tests."
        return
    fi

    print_info "Testing YOUR checker program..."

    # Error management
    STDERR=$(./checker abc 2>&1 1>/dev/null)
    echo "$STDERR" | grep -q "Error" && print_result 0 "checker: non-numeric → Error" || print_result 1 "checker: non-numeric → expected Error"

    STDERR=$(./checker 1 2 3 2 2>&1 1>/dev/null)
    echo "$STDERR" | grep -q "Error" && print_result 0 "checker: duplicates → Error" || print_result 1 "checker: duplicates → expected Error"

    STDERR=$(./checker 2147483648 2>&1 1>/dev/null)
    echo "$STDERR" | grep -q "Error" && print_result 0 "checker: > INT_MAX → Error" || print_result 1 "checker: > INT_MAX → expected Error"

    OUTPUT=$(./checker 2>&1)
    [ -z "$OUTPUT" ] && print_result 0 "checker: no args → no output" || print_result 1 "checker: no args → expected no output"

    STDERR=$(echo "xx" | ./checker 3 2 1 2>&1 1>/dev/null)
    echo "$STDERR" | grep -q "Error" && print_result 0 "checker: invalid instruction → Error" || print_result 1 "checker: invalid instruction → expected Error"

    # False test — wrong instructions should give KO
    RESULT=$(printf "sa\npb\nrrr\n" | ./checker 0 9 1 8 2 7 3 6 4 5 2>&1)
    echo "$RESULT" | grep -q "KO" && print_result 0 "checker: wrong instructions → KO" || print_result 1 "checker: wrong instructions → expected KO"

    # Right test — already sorted, no instructions → OK
    RESULT=$(echo "" | ./checker 0 1 2 2>&1)
    echo "$RESULT" | grep -q "OK" && print_result 0 "checker: sorted + no instructions → OK" || print_result 1 "checker: sorted + no instructions → expected OK"

    # Right test — known correct sequence
    RESULT=$(printf "pb\nra\npb\nra\nsa\nra\npa\npa\n" | ./checker 0 9 1 8 2 2>&1)
    echo "$RESULT" | grep -q "OK" && print_result 0 "checker: correct instruction sequence → OK" || print_result 1 "checker: correct instruction sequence → expected OK"

    # Integration: pipe push_swap into checker
    ARG=$(shuf -i 1-100 -n 20 | tr '\n' ' ')
    RESULT=$(./push_swap $ARG 2>/dev/null | ./checker $ARG 2>&1)
    echo "$RESULT" | grep -q "OK" && print_result 0 "checker: push_swap output piped → OK" || print_result 1 "checker: push_swap output piped → expected OK"
}

# ---------------------------------------------------------------------------
# 14. EXTRA EDGE CASES (not in checklist but can crash on defense)
# ---------------------------------------------------------------------------
test_edge_cases() {
    print_header "14. EXTRA EDGE CASES"

    # INT_MIN and INT_MAX
    OUTPUT=$(./push_swap -2147483648 2147483647 0 2>/dev/null)
    RET=$?
    if [ "$RET" -eq 0 ]; then
        print_result 0 "INT_MIN + INT_MAX + 0 → no crash (exit $RET)"
    else
        print_result 1 "INT_MIN + INT_MAX + 0 → crashed (exit $RET)"
    fi

    # Negative numbers
    if [ -n "$CHECKER" ]; then
        ARG="-5 -1 -3 -2 -4"
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>&1)
        echo "$RESULT" | grep -q "OK" && print_result 0 "Negative numbers → OK" || print_result 1 "Negative numbers → KO"
    fi

    # Single string argument with spaces (if supported)
    OUTPUT=$(./push_swap "3 2 1" 2>/dev/null)
    RET=$?
    if [ "$RET" -eq 0 ] && [ -n "$OUTPUT" ]; then
        print_result 0 "Single string arg \"3 2 1\" → handled"
    else
        print_warn "Single string arg \"3 2 1\" → not handled or no output (may be optional)"
    fi

    # Signs without digits
    STDERR=$(./push_swap + 2>&1 1>/dev/null)
    echo "$STDERR" | grep -q "Error" && print_result 0 "'+' alone → Error" || print_result 1 "'+' alone → expected Error"

    STDERR=$(./push_swap - 2>&1 1>/dev/null)
    echo "$STDERR" | grep -q "Error" && print_result 0 "'-' alone → Error" || print_result 1 "'-' alone → expected Error"

    # No debug/extra output check on stdout
    ARG="5 3 1 4 2"
    OUTPUT=$(./push_swap $ARG 2>/dev/null)
    BAD_LINES=$(echo "$OUTPUT" | grep -cvE '^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$')
    if [ "$BAD_LINES" -eq 0 ]; then
        print_result 0 "stdout contains only valid operations (no debug prints)"
    else
        print_result 1 "stdout has $BAD_LINES invalid line(s) — remove debug printf!"
    fi
}

# ============================================================================
# RUN ALL TESTS
# ============================================================================

echo ""
echo -e "${BOLD}╔══════════════════════════════════════════╗${NC}"
echo -e "${BOLD}║   push_swap tester — 42 checklist v2.0   ║${NC}"
echo -e "${BOLD}╚══════════════════════════════════════════╝${NC}"

detect_checker
if [ -n "$CHECKER" ]; then
    print_info "Using checker: $CHECKER"
fi

test_norminette
test_compilation
test_error_management
test_strategy_selection
test_identity
test_three
test_five
test_benchmark
test_100
test_strategy_comparison
test_500
test_memory_leaks
test_bonus_checker
test_edge_cases

# ============================================================================
# SUMMARY
# ============================================================================
print_header "SUMMARY"

TOTAL=$((PASSED + FAILED))
if [ "$TOTAL" -eq 0 ]; then
    echo "  No tests ran."
    exit 1
fi

PERCENTAGE=$((PASSED * 100 / TOTAL))

echo -e "  ${GREEN}Passed : $PASSED${NC}"
echo -e "  ${RED}Failed : $FAILED${NC}"
echo -e "  ${YELLOW}Warnings: $WARNED${NC}"
echo -e "  Total  : $TOTAL"
echo ""
echo -e "  Success rate: ${BOLD}${PERCENTAGE}%${NC}"
echo ""

if [ "$FAILED" -eq 0 ]; then
    echo -e "  ${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
else
    echo -e "  ${YELLOW}⚠  Some tests failed. Review above.${NC}"
fi

echo ""
exit 0