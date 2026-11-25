#ifndef IR_BUILDER_H
#define IR_BUILDER_H
#include <llvm-c/Core.h>
#include "ast.h"

LLVMModuleRef build_LLVM_IR(astNode* root_node);

void preprocess(astNode* node);

#endif
