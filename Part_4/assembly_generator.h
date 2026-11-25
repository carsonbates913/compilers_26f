#ifndef ASSEMBLY_GENERATOR_H
#define ASSEMBLY_GENERATOR_H
#include <llvm-c/Core.h>
#include <string>

void code_generation(LLVMModuleRef mod, std::string outFile);

#endif
