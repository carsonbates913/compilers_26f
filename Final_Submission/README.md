miniC Compiler
--------------
1. Build
-----
make
-----


2. Run
-----
./minic.out <input.c> <output.s>
------

Runs parsing, semantic analysis, IR building, optimization, and
assembly generation. If no output file is given, assembly is
written to output.s.

To run the generated assembly:

------
clang -m32 output.s assembly_gen_tests/main.c
./a.out
------

Tests
-----

Full pipeline:
bash assembly_gen_tests/run_asm_tests.sh

Note: fact.c and max_n.c are not valid miniC and are expected to
fail; fact_minic.c and max_n_minic.c are the valid versions.

Semantic analysis:
    ./minic.out parser/semantic_analysis_test/analysis_tests/<file>

Parser:
    ./minic.out parser/semantic_analysis_test/parser_tests/<file>

IR builder:
    ./minic.out IR_builder_tests/ir_tests/<file>.c

Cleanup
-------
make clean
-------