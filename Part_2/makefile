source = minic

LLVM_CONFIG := $(shell command -v llvm-config-21 2>/dev/null || echo $$(brew --prefix llvm@21)/bin/llvm-config)

$(source).out: $(source).l $(source).y ast.c semantic_analysis.c builder_alg.c
	yacc -d $(source).y
	lex $(source).l
	g++ -g `$(LLVM_CONFIG) --cxxflags` -std=c++20 -o $(source).out lex.yy.c y.tab.c ast.c semantic_analysis.c builder_alg.c `$(LLVM_CONFIG) --ldflags --libs core --system-libs`

clean:
	rm -f lex.yy.c y.tab.c y.tab.h $(source).out