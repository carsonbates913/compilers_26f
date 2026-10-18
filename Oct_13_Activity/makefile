LLVMCODE = llvm_parser
TEST = test
INCLUDES = -I /usr/include/llvm-c-21/ -I /usr/include/llvm-21/ 
$(LLVMCODE): $(LLVMCODE).c
	gcc -g $(INCLUDES) -c $(LLVMCODE).c
	g++ $(LLVMCODE).o `llvm-config-21 --cxxflags --ldflags --libs core` -I /usr/include/llvm-c-21/ -o $@

llvm_file: $(TEST).c
	clang -S -emit-llvm $(TEST).c -o $(TEST).ll

clean: 
	rm -rf $(LLVMCODE)
	rm -rf *.o
