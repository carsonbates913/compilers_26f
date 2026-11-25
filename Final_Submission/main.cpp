#include <stdio.h>
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include "ast.h"
#include "semantic_analysis.h"
#include "IR_builder.h"
#include "optimizer.h"
#include "assembly_generator.h"

extern FILE *yyin;
extern int yyparse();
extern int yylex_destroy();
extern astNode *root;

static void cleanup(LLVMModuleRef mod){
	if (mod != NULL)
		LLVMDisposeModule(mod);
	if (root != NULL)
		freeNode(root);
	if (yyin != NULL && yyin != stdin)
		fclose(yyin);
	yylex_destroy();
	LLVMShutdown();
}

int main(int argc, char** argv){

	// read the name of the miniC file (and optionally the assembly output file)
	if (argc < 2 || argc > 3){
		fprintf(stderr, "Wrong input");
		return 1;
	}
	const char* output_file = (argc == 3) ? argv[2] : "output.s";

	yyin = fopen(argv[1], "r");
	if (yyin == NULL){
		fprintf(stderr, "Error: could not open file %s\n", argv[1]);
		return 1;
	}

	// begin parsing + syntax analysis + AST
	yyparse();

	// if the root is null, that means the parsing failed and doesn't match our grammar
	if (root == NULL){
		fprintf(stderr, "Parsing failed or root was not created\n");
		cleanup(NULL);
		return 1;
	}

	// run semantic analysis. If the flag is 1, it succeeded. Otherwise, it failed.
	int sem_flag = semantic_analysis(root);
	if (sem_flag == 0){
		fprintf(stderr, "Semantic Analysis failed\n");
		cleanup(NULL);
		return 1;
	}

	// preprocess (the first stage of IR building) — remove shadow variables
	preprocess(root);

	// return the module of the newly built LLVM IR
	LLVMModuleRef mod = build_LLVM_IR(root);

	// make sure the LLVM IR module is valid before optimizing it
	if (mod == NULL || LLVMVerifyModule(mod, LLVMPrintMessageAction, NULL)){
		fprintf(stderr, "LLVM IR Building failed\n");
		cleanup(mod);
		return 1;
	}

	// optimize the IR (CSE, dead code elimination, constant propagation + folding)
	optimize(mod);

	// register allocation + assembly code generation
	code_generation(mod, output_file);

	cleanup(mod);
	return 0;
}
