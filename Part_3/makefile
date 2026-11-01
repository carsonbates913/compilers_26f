LLVMCODE = llvm_parser
TEST = test

LLVM_CONFIG  := $(shell command -v llvm-config-21 2>/dev/null || echo $$(brew --prefix llvm@21)/bin/llvm-config)
LLVM_VERSION := $(shell $(LLVM_CONFIG) --version 2>/dev/null)
LLVM_BIN     := $(shell $(LLVM_CONFIG) --bindir 2>/dev/null)

ifneq ($(firstword $(subst ., ,$(LLVM_VERSION))),21)
$(error Need LLVM 21, but found '$(LLVM_VERSION)' using $(LLVM_CONFIG))
endif

$(LLVMCODE): $(LLVMCODE).cpp
	g++ -g `$(LLVM_CONFIG) --cxxflags` -std=c++20 -c $(LLVMCODE).cpp
	g++ $(LLVMCODE).o `$(LLVM_CONFIG) --ldflags --libs core --system-libs` -o $@

llvm_file: $(TEST).c
	$(LLVM_BIN)/clang -S -emit-llvm $(TEST).c -o $(TEST).ll

clean:
	rm -rf $(LLVMCODE)
	rm -rf *.o