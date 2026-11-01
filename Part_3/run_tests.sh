#!/bin/bash
# Runs llvm_parser on every unoptimized .ll in optimizer_test_results and prints
# the full expected solution (*_opt.ll) followed by the full optimized output.
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
NC='\033[0m'

BAR="=============================================================================="
LINE="------------------------------------------------------------------------------"

cd "$(dirname "$0")" || exit 1
ROOT=$(pwd)
TEST_DIR="$ROOT/optimizer_test_results"

# Rebuild the optimizer using the makefile
make clean > /dev/null && make > /dev/null 2>&1
if [ ! -f "./llvm_parser" ]; then echo -e "${RED}Build failed.${NC}"; exit 1; fi

# Keep only the function definitions, dropping loop metadata and extra whitespace
extract_functions() {
    awk '/^define /{f=1} f{print} /^}/{f=0}' "$1" \
        | sed -E 's/, !llvm\.loop ![0-9]+//; s/[[:space:]]+$//; s/[[:space:]]+/ /g'
}

pass=0
fail=0
skip=0
results=""

# llvm_parser always writes test_new.ll to the current directory, so run it in a temp dir
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT

for file in "$TEST_DIR"/*.ll; do
    [ -e "$file" ] || continue
    [[ "$file" == *_opt.ll ]] && continue

    name=$(basename "$file" .ll)
    expected="$TEST_DIR/${name}_opt.ll"

    # cfold* and p2* solutions were generated with only local optimizations (see the README there)
    flags=""
    [[ "$name" == cfold* || "$name" == p2* ]] && flags="--local"

    (cd "$WORK" && rm -f test_new.ll && "$ROOT/llvm_parser" "$file" $flags > /dev/null 2>&1)
    status=$?
    actual="$WORK/test_new.ll"

    echo
    echo
    echo
    echo -e "${CYAN}${BAR}${NC}"
    echo -e "${CYAN}${BAR}${NC}"
    echo -e "${CYAN}    TEST: ${name}${NC}"
    echo -e "${CYAN}    input file: optimizer_test_results/${name}.ll${NC}"
    echo -e "${CYAN}${BAR}${NC}"
    echo -e "${CYAN}${BAR}${NC}"

    echo
    echo
    echo -e "${GREEN}${LINE}${NC}"
    echo -e "${GREEN}    [ ${name} ]  EXPECTED SOLUTION  (optimizer_test_results/${name}_opt.ll)${NC}"
    echo -e "${GREEN}${LINE}${NC}"
    echo
    if [ -f "$expected" ]; then
        cat "$expected"
    else
        echo -e "${YELLOW}    (no ${name}_opt.ll solution file exists for this test)${NC}"
    fi
    echo
    echo -e "${GREEN}${LINE}${NC}"
    echo -e "${GREEN}    END OF EXPECTED SOLUTION  [ ${name} ]${NC}"
    echo -e "${GREEN}${LINE}${NC}"

    echo
    echo
    echo -e "${YELLOW}${LINE}${NC}"
    echo -e "${YELLOW}    [ ${name} ]  YOUR OPTIMIZED OUTPUT  (llvm_parser ${name}.ll ${flags})${NC}"
    echo -e "${YELLOW}${LINE}${NC}"
    echo
    if [ $status -ne 0 ] || [ ! -f "$actual" ]; then
        echo -e "${RED}    (llvm_parser crashed or produced no output, exit code $status)${NC}"
    else
        cat "$actual"
    fi
    echo
    echo -e "${YELLOW}${LINE}${NC}"
    echo -e "${YELLOW}    END OF YOUR OPTIMIZED OUTPUT  [ ${name} ]${NC}"
    echo -e "${YELLOW}${LINE}${NC}"

    # Compare only the function bodies (headers/metadata differ between LLVM versions)
    if [ $status -ne 0 ] || [ ! -f "$actual" ]; then
        result="${RED}FAIL${NC}  (llvm_parser crashed or produced no output)"
        fail=$((fail + 1))
    elif [ ! -f "$expected" ]; then
        result="${YELLOW}SKIP${NC}  (no ${name}_opt.ll solution file to compare against)"
        skip=$((skip + 1))
    elif diff -q <(extract_functions "$expected") <(extract_functions "$actual") > /dev/null; then
        result="${GREEN}PASS${NC}  (function bodies match the solution)"
        pass=$((pass + 1))
    else
        result="${RED}FAIL${NC}  (function bodies differ from the solution)"
        fail=$((fail + 1))
    fi
    results+="    ${name}: ${result}\n"

    echo
    echo
    echo -e "${CYAN}${LINE}${NC}"
    echo -e "    [ ${name} ]  RESULT:  ${result}"
    echo -e "${CYAN}${LINE}${NC}"
done

echo
echo
echo -e "${CYAN}${BAR}${NC}"
echo -e "${CYAN}    SUMMARY${NC}"
echo -e "${CYAN}${BAR}${NC}"
echo
echo -e "$results"
echo -e "    ${GREEN}${pass} passed${NC}, ${RED}${fail} failed${NC}, ${YELLOW}${skip} skipped${NC}"
echo
echo -e "${CYAN}${BAR}${NC}"
