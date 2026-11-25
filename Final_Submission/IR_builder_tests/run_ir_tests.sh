#!/bin/bash
# Runs every .c test through minic.out and compares against clang.
#
# For each test it saves (in ir_results/):
#   pN.mine.ll      - IR produced by your build_LLVM_IR (test.ll)
#   pN.expected.ll  - reference IR from clang -O0
#   pN.log          - full stdout/stderr of minic.out
# and then links both versions against main.c, runs them on the same
# input, and reports whether the program output matches.
#
# Usage: ./run_ir_tests.sh [-q] [test_dir]
#   -q        don't print the IR to the terminal (files are still saved)
#   test_dir  directory with the *.c tests (default: ir_tests). main.c is taken
#             from test_dir if present, otherwise from ../Part_4/main.c

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BOLD='\033[1m'
NC='\033[0m'

QUIET=0
if [ "$1" == "-q" ]; then QUIET=1; shift; fi
TEST_DIR="${1:-ir_tests}"
OUT_DIR="ir_results"
# Includes the 8 3 2 9 password sequence so example3 terminates
INPUT="3 7 1 9 4 2 8 6 3 5 2 10 9 11 12 13 14 15 16 17 18 19 20"

CLANG="$(brew --prefix llvm@21 2>/dev/null)/bin/clang"
[ -x "$CLANG" ] || CLANG=clang

# Run a command with a time limit (macOS has no `timeout`)
run_limited() { perl -e 'alarm shift; exec @ARGV' 5 "$@"; }

make clean > /dev/null && make > /dev/null 2>&1
if [ ! -f "./minic.out" ]; then echo -e "${RED}Build failed.${NC}"; exit 1; fi
MAIN_C="$TEST_DIR/main.c"
[ -f "$MAIN_C" ] || MAIN_C="../Part_4/main.c"
if [ ! -f "$MAIN_C" ]; then echo -e "${RED}No main.c in $TEST_DIR or ../Part_4${NC}"; exit 1; fi

mkdir -p "$OUT_DIR"
pass=0; fail=0

for file in "$TEST_DIR"/*.c; do
    [ -e "$file" ] || continue
    name=$(basename "$file" .c)
    [ "$name" == "main" ] && continue
    mine="$OUT_DIR/$name.mine.ll"
    expected="$OUT_DIR/$name.expected.ll"
    echo -e "\n${BOLD}=================== $name ===================${NC}"

    # Your compiler: it writes test.ll into the current directory
    rm -f test.ll "$mine"
    run_limited ./minic.out "$file" > "$OUT_DIR/$name.log" 2>&1
    status=$?
    [ -f test.ll ] && mv test.ll "$mine"

    # Reference IR from clang
    "$CLANG" -S -emit-llvm -O0 -fno-discard-value-names -Xclang -disable-O0-optnone \
        -target x86_64-pc-linux-gnu "$file" -o "$expected" 2> /dev/null

    if [ $QUIET -eq 0 ]; then
        echo -e "${YELLOW}--- your IR ---${NC}"
        if [ -f "$mine" ]; then cat "$mine"; else echo "(none produced)"; fi
        echo -e "${YELLOW}--- expected IR (clang -O0) ---${NC}"
        sed -n '/^define/,/^}/p' "$expected"
    fi

    if [ ! -f "$mine" ]; then
        echo -e "[${RED}FAIL${NC}] $name -> no test.ll produced (exit $status, see $OUT_DIR/$name.log)."
        echo "       Is build_LLVM_IR(root) called from main() in minic.y?"
        fail=$((fail + 1)); continue
    fi

    # Behavioral check: strip the linux triple so the IR links on this machine
    sed '/^target triple/d; /^target datalayout/d' "$mine" > "$OUT_DIR/$name.host.ll"
    if ! "$CLANG" -Wno-override-module "$OUT_DIR/$name.host.ll" "$MAIN_C" \
            -o "$OUT_DIR/$name.mine.out" 2> "$OUT_DIR/$name.compile_err"; then
        echo -e "[${RED}FAIL${NC}] $name -> your IR does not compile:"
        sed 's/^/       /' "$OUT_DIR/$name.compile_err" | head -10
        fail=$((fail + 1)); continue
    fi
    "$CLANG" "$file" "$MAIN_C" -o "$OUT_DIR/$name.expected.out" 2> /dev/null

    got=$(echo "$INPUT" | run_limited "$OUT_DIR/$name.mine.out" 2>&1)
    got_status=$?
    want=$(echo "$INPUT" | run_limited "$OUT_DIR/$name.expected.out" 2>&1)

    if [ $got_status -eq 142 ]; then
        echo -e "[${RED}FAIL${NC}] $name -> your program timed out (infinite loop?)"
        fail=$((fail + 1))
    elif [ "$got" == "$want" ]; then
        echo -e "[${GREEN}PASS${NC}] $name -> program output matches"
        pass=$((pass + 1))
    else
        echo -e "[${RED}FAIL${NC}] $name -> program output differs"
        diff <(echo "$want") <(echo "$got") | sed 's/^/       /'
        fail=$((fail + 1))
    fi
done

echo -e "\n${BOLD}Passed: $pass   Failed: $fail${NC}   (files in $OUT_DIR/)"
