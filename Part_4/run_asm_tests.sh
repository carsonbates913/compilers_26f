#!/bin/bash
# Runs every test in assembly_gen_tests/ through minic.out and checks the
# generated 32-bit x86 assembly against a clang-compiled reference.
#
# For each test it saves (in asm_results/):
#   name.s         - assembly produced by your compiler
#   name.log       - full stdout/stderr of minic.out
#   name.link_err  - assembler/linker errors (if any)
# then links name.s with a driver (same print/read as main.c, but func's
# argument comes from the command line), runs it for several values of n,
# and compares the output with the same C file compiled natively by clang.
#
# Apple Silicon can't run `clang -m32` binaries, so the assembly is
# assembled, linked and run inside an i386 Linux Docker container
# (image "minic-i386", built automatically the first time).
#
# Usage: ./run_asm_tests.sh [-v] [test_dir]
#   -v        print the generated assembly for each test
#   test_dir  directory with the *.c tests (default: assembly_gen_tests)
#
# Env overrides:
#   N_VALUES="0 1 4 10"   values of n passed to func
#
# Your compiler is invoked as:   ./minic.out <test.c> <output.s>
# (if it ignores argv[2] and writes test.s instead, that is picked up too)

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BOLD='\033[1m'
NC='\033[0m'

VERBOSE=0
if [ "$1" == "-v" ]; then VERBOSE=1; shift; fi
TEST_DIR="${1:-assembly_gen_tests}"
OUT_DIR="asm_results"
N_VALUES="${N_VALUES:-0 1 4 10}"
# Values fed to read() (max_n / sum_n call read() n times)
INPUT="3 7 1 9 4 2 8 6 5 10 12 11 15 14 13 20 18 17 16 19"
IMAGE="minic-i386"

cd "$(dirname "$0")" || exit 1

# Run a command with a time limit (macOS has no `timeout`)
run_limited() { perl -e 'alarm shift; exec @ARGV' 5 "$@"; }

# ---- prerequisites -------------------------------------------------------
if ! docker info > /dev/null 2>&1; then
    echo -e "${RED}Docker is not running. Start Docker Desktop and retry.${NC}"; exit 1
fi
if ! docker image inspect "$IMAGE" > /dev/null 2>&1; then
    echo "Building $IMAGE Docker image (one time)..."
    printf 'FROM i386/alpine:3.20\nRUN apk add --no-cache gcc musl-dev\n' \
        | docker build --platform linux/386 -t "$IMAGE" - > /dev/null \
        || { echo -e "${RED}Failed to build $IMAGE image.${NC}"; exit 1; }
fi

make clean > /dev/null && make > "$OUT_DIR.build.log" 2>&1
if [ ! -f "./minic.out" ]; then
    echo -e "${RED}Build failed:${NC}"; tail -20 "$OUT_DIR.build.log"; exit 1
fi
rm -f "$OUT_DIR.build.log"

rm -rf "$OUT_DIR"; mkdir -p "$OUT_DIR"

# Driver: same print/read as main.c, n taken from argv[1]
cat > "$OUT_DIR/driver.c" <<'EOF'
#include <stdio.h>
#include <stdlib.h>
int func(int);
int read(){ int x; scanf("%d", &x); return x; }
void print(int x){ printf("%d\n", x); }
int main(int argc, char** argv){
    int i = func(atoi(argv[1]));
    printf("In main printing return value of test: %d\n", i);
    return 0;
}
EOF

pass=0; fail=0; failed_names=()

for file in "$TEST_DIR"/*.c; do
    [ -e "$file" ] || continue
    name=$(basename "$file" .c)
    [ "$name" == "main" ] && continue
    asm="$OUT_DIR/$name.s"
    echo -e "\n${BOLD}=================== $name ===================${NC}"

    # ---- your compiler ----
    rm -f test.s "$asm"
    run_limited ./minic.out "$file" "$asm" > "$OUT_DIR/$name.log" 2>&1
    status=$?
    [ ! -s "$asm" ] && [ -s test.s ] && mv test.s "$asm"

    if [ ! -s "$asm" ]; then
        echo -e "[${RED}FAIL${NC}] $name -> no assembly produced (exit $status, see $OUT_DIR/$name.log)"
        fail=$((fail + 1)); failed_names+=("$name"); continue
    fi
    if [ $VERBOSE -eq 1 ]; then
        echo -e "${YELLOW}--- your assembly ---${NC}"; cat "$asm"
    fi

    # ---- reference: native clang ----
    clang -w "$file" "$OUT_DIR/driver.c" -o "$OUT_DIR/$name.expected.out" 2> /dev/null
    for n in $N_VALUES; do
        echo "$INPUT" | run_limited "$OUT_DIR/$name.expected.out" "$n" \
            > "$OUT_DIR/$name.expected.$n.txt" 2>&1
    done

    # ---- yours: assemble, link and run inside i386 Linux ----
    docker run --rm --platform linux/386 -v "$PWD/$OUT_DIR":/w -w /w "$IMAGE" sh -c '
        name=$1; input=$2; shift 2
        gcc -m32 -no-pie -w "$name.s" driver.c -o "$name.mine.out" 2> "$name.link_err" || exit 99
        rm -f "$name.link_err"
        for n in "$@"; do
            echo "$input" | timeout 5 "./$name.mine.out" "$n" > "$name.mine.$n.txt" 2>&1
            echo $? > "$name.mine.$n.status"
        done' _ "$name" "$INPUT" $N_VALUES
    if [ $? -eq 99 ]; then
        echo -e "[${RED}FAIL${NC}] $name -> assembly does not assemble/link:"
        sed 's/^/       /' "$OUT_DIR/$name.link_err" | head -15
        fail=$((fail + 1)); failed_names+=("$name"); continue
    fi

    ok=1
    for n in $N_VALUES; do
        st=$(cat "$OUT_DIR/$name.mine.$n.status" 2> /dev/null)
        if [ "$st" == "124" ] || [ "$st" == "143" ]; then
            echo -e "  ${RED}n=$n: timed out (infinite loop?)${NC}"; ok=0
        elif [ "$st" -ge 128 ] 2> /dev/null; then
            echo -e "  ${RED}n=$n: crashed (signal $((st - 128)))${NC}"; ok=0
        elif ! diff -q "$OUT_DIR/$name.expected.$n.txt" "$OUT_DIR/$name.mine.$n.txt" > /dev/null; then
            echo -e "  ${RED}n=$n: output differs (< expected, > yours)${NC}"
            diff "$OUT_DIR/$name.expected.$n.txt" "$OUT_DIR/$name.mine.$n.txt" | sed 's/^/       /' | head -15
            ok=0
        else
            echo -e "  ${GREEN}n=$n: ok${NC}"
        fi
    done

    if [ $ok -eq 1 ]; then
        echo -e "[${GREEN}PASS${NC}] $name"
        pass=$((pass + 1))
    else
        echo -e "[${RED}FAIL${NC}] $name"
        fail=$((fail + 1)); failed_names+=("$name")
    fi
done

echo -e "\n${BOLD}Passed: $pass   Failed: $fail${NC}   (files in $OUT_DIR/)"
[ $fail -gt 0 ] && echo -e "${RED}Failing: ${failed_names[*]}${NC}"
[ $fail -eq 0 ]
