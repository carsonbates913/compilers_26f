#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include <llvm-c/Core.h>

void optimize(LLVMModuleRef module, bool local_only = false);

#endif
