#ifndef BUILDER_ALG_H
#define BUILDER_ALG_H
#include <llvm-c/Core.h>
#include "ast.h"

LLVMModuleRef build_LLVM_IR(astNode* root_node);

#endif
