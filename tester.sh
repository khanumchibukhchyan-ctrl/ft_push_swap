#!/bin/bash

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Счетчики
PASSED=0
FAILED=0

# Функция для печати заголовков
print_header() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}\n"
}

# Функция для печати результата теста
print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✓ PASSED:${NC} $2"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAILED:${NC} $2"
        ((FAILED++))
    fi
}

# Проверка наличия программы
if [ ! -f "./push_swap" ]; then
    echo -e "${RED}Error: push_swap executable not found!${NC}"
    echo "Please run 'make' first."
    exit 1
fi

# Проверка наличия checker
CHECKER=""
if [ -f "./checker_linux" ]; then
    CHECKER="./checker_linux"
elif [ -f "./checker_Mac" ]; then
    CHECKER="./checker_Mac"
elif [ -f "./checker" ]; then
    CHECKER="./checker"
else
    echo -e "${YELLOW}Warning: checker not found. Some tests will be skipped.${NC}"
fi

# ============================================
# 1. ТЕСТ КОМПИЛЯЦИИ
# ============================================
print_header "1. COMPILATION TEST"

make re > /dev/null 2>&1
if [ -f "./push_swap" ]; then
    print_result 0 "Makefile compilation successful"
else
    print_result 1 "Makefile compilation failed"
    exit 1
fi

# ============================================
# 2. ОБРАБОТКА ОШИБОК
# ============================================
print_header "2. ERROR HANDLING"

# Нечисловые параметры
OUTPUT=$(./push_swap abc 2>&1)
if echo "$OUTPUT" | grep -q "Error"; then
    print_result 0 "Non-numeric parameters"
else
    print_result 1 "Non-numeric parameters (expected 'Error')"
fi

# Дублирующиеся числа
OUTPUT=$(./push_swap 1 2 3 2 2>&1)
if echo "$OUTPUT" | grep -q "Error"; then
    print_result 0 "Duplicate numbers"
else
    print_result 1 "Duplicate numbers (expected 'Error')"
fi

# Число больше MAX_INT
OUTPUT=$(./push_swap 2147483648 2>&1)
if echo "$OUTPUT" | grep -q "Error"; then
    print_result 0 "Number greater than MAX_INT"
else
    print_result 1 "Number greater than MAX_INT (expected 'Error')"
fi

# Без параметров
OUTPUT=$(./push_swap 2>&1)
if [ -z "$OUTPUT" ]; then
    print_result 0 "No parameters (empty output)"
else
    print_result 1 "No parameters (should be empty)"
fi

# ============================================
# 3. ВЫБОР СТРАТЕГИИ
# ============================================
print_header "3. STRATEGY SELECTION"

# --simple
OUTPUT=$(./push_swap --simple 5 4 3 2 1 2>&1)
if [ $? -eq 0 ] && [ -n "$OUTPUT" ]; then
    print_result 0 "--simple flag works"
else
    print_result 1 "--simple flag"
fi

# --medium
OUTPUT=$(./push_swap --medium 5 4 3 2 1 2>&1)
if [ $? -eq 0 ] && [ -n "$OUTPUT" ]; then
    print_result 0 "--medium flag works"
else
    print_result 1 "--medium flag"
fi

# --complex
OUTPUT=$(./push_swap --complex 5 4 3 2 1 2>&1)
if [ $? -eq 0 ] && [ -n "$OUTPUT" ]; then
    print_result 0 "--complex flag works"
else
    print_result 1 "--complex flag"
fi

# --adaptive
OUTPUT=$(./push_swap --adaptive 5 4 3 2 1 2>&1)
if [ $? -eq 0 ] && [ -n "$OUTPUT" ]; then
    print_result 0 "--adaptive flag works"
else
    print_result 1 "--adaptive flag"
fi

# Без флага (default)
OUTPUT=$(./push_swap 5 4 3 2 1 2>&1)
if [ $? -eq 0 ] && [ -n "$OUTPUT" ]; then
    print_result 0 "No flag (defaults to adaptive)"
else
    print_result 1 "No flag default behavior"
fi

# ============================================
# 4. УЖЕ ОТСОРТИРОВАННЫЕ ДАННЫЕ
# ============================================
print_header "4. ALREADY SORTED INPUTS"

OUTPUT=$(./push_swap 42 2>&1)
if [ -z "$OUTPUT" ]; then
    print_result 0 "Single number (no output)"
else
    print_result 1 "Single number (expected no output)"
fi

OUTPUT=$(./push_swap 2 3 2>&1)
if [ -z "$OUTPUT" ]; then
    print_result 0 "Two sorted numbers (no output)"
else
    print_result 1 "Two sorted numbers (expected no output)"
fi

OUTPUT=$(./push_swap 0 1 2 3 2>&1)
if [ -z "$OUTPUT" ]; then
    print_result 0 "Four sorted numbers (no output)"
else
    print_result 1 "Four sorted numbers (expected no output)"
fi

OUTPUT=$(./push_swap 0 1 2 3 4 5 6 7 8 9 2>&1)
if [ -z "$OUTPUT" ]; then
    print_result 0 "Ten sorted numbers (no output)"
else
    print_result 1 "Ten sorted numbers (expected no output)"
fi

# ============================================
# 5. МАЛЫЕ ДАННЫЕ (3 ЧИСЛА)
# ============================================
print_header "5. SMALL INPUTS (3 numbers)"

if [ -n "$CHECKER" ]; then
    ARG="2 1 0"
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>&1)
    COUNT=$(./push_swap $ARG | wc -l)
    
    if echo "$RESULT" | grep -q "OK"; then
        if [ $COUNT -le 5 ]; then
            print_result 0 "3 numbers: $ARG (OK, $COUNT operations ≤5)"
        else
            print_result 1 "3 numbers: $ARG (OK but $COUNT operations >5)"
        fi
    else
        print_result 1 "3 numbers: $ARG (checker failed)"
    fi

    ARG="0 2 1"
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>&1)
    if echo "$RESULT" | grep -q "OK"; then
        print_result 0 "3 numbers: $ARG"
    else
        print_result 1 "3 numbers: $ARG"
    fi
else
    echo -e "${YELLOW}Skipping (no checker)${NC}"
fi

# ============================================
# 6. СРЕДНИЕ ДАННЫЕ (5 ЧИСЕЛ)
# ============================================
print_header "6. MEDIUM INPUTS (5 numbers)"

if [ -n "$CHECKER" ]; then
    ARG="1 5 2 4 3"
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>&1)
    COUNT=$(./push_swap $ARG | wc -l)
    
    if echo "$RESULT" | grep -q "OK"; then
        if [ $COUNT -le 15 ]; then
            print_result 0 "5 numbers: $ARG (OK, $COUNT operations ≤15)"
        else
            print_result 1 "5 numbers: $ARG (OK but $COUNT operations >15)"
        fi
    else
        print_result 1 "5 numbers: $ARG (checker failed)"
    fi

    # Дополнительные тесты
    for ARG in "5 1 4 2 3" "3 5 1 4 2"; do
        RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>&1)
        if echo "$RESULT" | grep -q "OK"; then
            print_result 0 "5 numbers: $ARG"
        else
            print_result 1 "5 numbers: $ARG"
        fi
    done
else
    echo -e "${YELLOW}Skipping (no checker)${NC}"
fi

# ============================================
# 7. BENCHMARK MODE
# ============================================
print_header "7. BENCHMARK MODE"

OUTPUT=$(./push_swap --bench --simple 5 4 3 2 1 2>/dev/null)
if [ -n "$OUTPUT" ]; then
    print_result 0 "Benchmark produces sorting instructions"
else
    print_result 1 "Benchmark produces sorting instructions"
fi

./push_swap --bench --simple 5 4 3 2 1 2>bench_temp.txt >/dev/null
if [ -f bench_temp.txt ]; then
    if grep -q "disorder\|Disorder\|strategy\|Strategy\|operations\|Operations" bench_temp.txt; then
        print_result 0 "Benchmark output contains required info"
    else
        print_result 1 "Benchmark output missing required info"
    fi
    rm -f bench_temp.txt
fi

# Проверка disorder для отсортированного ввода
./push_swap --bench --simple 1 2 3 4 5 2>bench_temp.txt >/dev/null
if [ -f bench_temp.txt ]; then
    if grep -q "0\|0.0" bench_temp.txt; then
        print_result 0 "Disorder calculation for sorted input (≈0%)"
    else
        print_result 1 "Disorder calculation for sorted input"
    fi
    rm -f bench_temp.txt
fi

# ============================================
# 8. БОЛЬШИЕ ДАННЫЕ (100 ЧИСЕЛ)
# ============================================
print_header "8. LARGE INPUTS (100 numbers)"

if [ -n "$CHECKER" ]; then
    for i in {1..2}; do
        ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
        RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>&1)
        COUNT=$(./push_swap $ARG | wc -l)
        
        if echo "$RESULT" | grep -q "OK"; then
            if [ $COUNT -lt 2000 ]; then
                if [ $COUNT -lt 700 ]; then
                    print_result 0 "100 numbers test $i (OK, $COUNT operations - EXCELLENT)"
                elif [ $COUNT -lt 1500 ]; then
                    print_result 0 "100 numbers test $i (OK, $COUNT operations - GOOD)"
                else
                    print_result 0 "100 numbers test $i (OK, $COUNT operations - PASS)"
                fi
            else
                print_result 1 "100 numbers test $i (OK but $COUNT operations ≥2000)"
            fi
        else
            print_result 1 "100 numbers test $i (checker failed)"
        fi
    done
else
    echo -e "${YELLOW}Skipping (no checker)${NC}"
fi

# ============================================
# 9. ТЕСТИРОВАНИЕ РАЗНЫХ СТРАТЕГИЙ
# ============================================
print_header "9. STRATEGY COMPARISON"

if [ -n "$CHECKER" ]; then
    ARG=$(shuf -i 1-200 -n 50 | tr '\n' ' ')
    
    SIMPLE_COUNT=$(./push_swap --simple $ARG | wc -l)
    MEDIUM_COUNT=$(./push_swap --medium $ARG | wc -l)
    COMPLEX_COUNT=$(./push_swap --complex $ARG | wc -l)
    
    SIMPLE_OK=$(./push_swap --simple $ARG | $CHECKER $ARG 2>&1)
    MEDIUM_OK=$(./push_swap --medium $ARG | $CHECKER $ARG 2>&1)
    COMPLEX_OK=$(./push_swap --complex $ARG | $CHECKER $ARG 2>&1)
    
    if echo "$SIMPLE_OK" | grep -q "OK"; then
        print_result 0 "--simple sorts correctly ($SIMPLE_COUNT ops)"
    else
        print_result 1 "--simple failed to sort"
    fi
    
    if echo "$MEDIUM_OK" | grep -q "OK"; then
        print_result 0 "--medium sorts correctly ($MEDIUM_COUNT ops)"
    else
        print_result 1 "--medium failed to sort"
    fi
    
    if echo "$COMPLEX_OK" | grep -q "OK"; then
        print_result 0 "--complex sorts correctly ($COMPLEX_COUNT ops)"
    else
        print_result 1 "--complex failed to sort"
    fi
    
    if [ $COMPLEX_COUNT -lt $SIMPLE_COUNT ]; then
        print_result 0 "--complex uses fewer operations than --simple"
    else
        print_result 1 "--complex should use fewer operations than --simple"
    fi
else
    echo -e "${YELLOW}Skipping (no checker)${NC}"
fi

# ============================================
# 10. ОЧЕНЬ БОЛЬШИЕ ДАННЫЕ (500 ЧИСЕЛ)
# ============================================
print_header "10. VERY LARGE INPUTS (500 numbers)"

if [ -n "$CHECKER" ]; then
    for i in {1..2}; do
        ARG=$(shuf -i 1-1000 -n 500 | tr '\n' ' ')
        RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>&1)
        COUNT=$(./push_swap $ARG | wc -l)
        
        if echo "$RESULT" | grep -q "OK"; then
            if [ $COUNT -lt 12000 ]; then
                if [ $COUNT -lt 5500 ]; then
                    print_result 0 "500 numbers test $i (OK, $COUNT operations - EXCELLENT)"
                elif [ $COUNT -lt 8000 ]; then
                    print_result 0 "500 numbers test $i (OK, $COUNT operations - GOOD)"
                else
                    print_result 0 "500 numbers test $i (OK, $COUNT operations - PASS)"
                fi
            else
                print_result 1 "500 numbers test $i (OK but $COUNT operations ≥12000)"
            fi
        else
            print_result 1 "500 numbers test $i (checker failed)"
        fi
    done
else
    echo -e "${YELLOW}Skipping (no checker)${NC}"
fi

# ============================================
# ИТОГИ
# ============================================
print_header "TEST SUMMARY"

TOTAL=$((PASSED + FAILED))
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "Total: $TOTAL"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}\n"
else
    echo -e "\n${YELLOW}⚠️  Some tests failed. Please review.${NC}\n"
fi

# Процент успеха
PERCENTAGE=$((PASSED * 100 / TOTAL))
echo -e "Success rate: ${PERCENTAGE}%"

exit 0