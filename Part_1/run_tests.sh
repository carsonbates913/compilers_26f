#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Rebuild your compiler using your Makefile
make clean && make
if [ ! -f "./minic.out" ]; then echo -e "${RED}Build failed.${NC}"; exit 1; fi

run_suite() {
    echo -e "\n=== Running $1 ==="
    for file in "$2"/*.c; do
        [ -e "$file" ] || continue
        
        # Capture the terminal output of your executable
        output=$(./minic.out "$file" 2>&1)
        
        # Check if the output contains "\n1\n" (Semantic Pass) or "\n0\n" (Semantic Fail)
        # If it doesn't print 0 or 1, it fell into a 'Syntax error' via yyerror()
        if echo "$output" | grep -q "^1$"; then
            flag=1
        elif echo "$output" | grep -q "^0$"; then
            flag=0
        else
            flag="syntax_error"
        fi

        filename=$(basename "$file")
        
        # Evaluate expectations against your naming convention
        if [[ "$filename" == *"_good"* && "$flag" == "1" ]]; then
            echo -e "  [${GREEN}PASS${NC}] $filename -> Semantic valid (1)"
        elif [[ "$filename" == *"_bad"* && "$flag" == "0" ]]; then
            echo -e "  [${GREEN}PASS${NC}] $filename -> Semantic invalid caught (0)"
        elif [[ "$flag" == "syntax_error" ]]; then
            echo -e "  [${RED}FAIL${NC}] $filename -> Broken by a Syntax Error!"
        else
            echo -e "  [${RED}FAIL${NC}] $filename -> Discrepancy! Expected matching name logic but got flag ($flag)"
        fi
    done
}

run_suite "Analysis Tests" "analysis_tests"
run_suite "Parser Tests" "parser_tests"
