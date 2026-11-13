#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ast.h"
#include <llvm-c/Core.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <set>
#include <string>

static bool has_return = false;
static std::string function_name;
static int num_params;
static std::map<std::string, std::vector<std::vector<astNode>> var_names;
static std::map<std::string, std::vector<astNode> end_result;

void collapse_map(){
  for( std::string key_name : var_names.getKeys()){
    std::vector<std::vector<astNode>> vec_value = var_names.get(key_name);
    for(int i = 1; i < vec_value.length + 1; i++){
      std::string new_name = key_name + i
      std::vector<astNode> new_vector = vec_value[i-1];
      for( astNode x : new_vector){
        // change name of x to new_name;
      }
      end_result.push(new_name, new_vector);
    }
  }
}

static std::map<std::string, LLVMValueRef> var_map;
static LLVMValueRef func;
static LLVMValueRef func_read;
static LLVMValueRef func_print;
static LLVMTypeRef ret_read;
static LLVMTypeRef ret_print;
static LLVMValueRef ret_ref;
static LLVMBasicBlockRef retBB;

LLVMBasicBlockRef genIRStmt(astNode* node, LLVMBuilderRef builder, LLVMBasicBlockRef startBB);
LLVMValueRef genIRExpr(astNode* node, LLVMBuilderRef builder);
void deleteUnreachableBlocks(LLVMValueRef func);

LLVMModuleRef build_LLVM_IR(astNode* root_node) {
	//Creating a module 
  LLVMModuleRef mod = LLVMModuleCreateWithName("");
	LLVMSetTarget(mod, "x86_64-pc-linux-gnu");
  
	
	//Creating extern function for read.
  LLVMTypeRef* param_read = NULL;
  ret_read = LLVMFunctionType(LLVMInt32Type(), param_read, 0, 0);
  func_read = LLVMAddFunction(mod, "read", ret_read);

  	//Creating extern function for print.
  LLVMTypeRef param_print[] = {LLVMInt32Type()};
  ret_print = LLVMFunctionType(LLVMVoidType(), param_print, 1, 0);
  func_print = LLVMAddFunction(mod, "print", ret_print);

  //Creating a function in a module
  astNode* function_node = root_node->prog.func;
  int num_params = (function_node->func.param != NULL) ? 1 : 0;
  LLVMTypeRef param_types[] = {LLVMInt32Type()};
  LLVMTypeRef func_type = LLVMFunctionType(LLVMInt32Type(), param_types, num_params, 0);
  func = LLVMAddFunction(mod, function_node->func.name, func_type);

	//All instructions need to be created using a builder. The builder specifies
	//where the instructions are added.
  LLVMBuilderRef builder = LLVMCreateBuilder();

  //Creating a basic block
  LLVMBasicBlockRef entryBB = LLVMAppendBasicBlock(func, "");

  // Create a set with names of all parameters and local variables (strongly recommend using C++ strings for names).
  ///

  // This positions the builder in the end of the first basicblock. There are other position functions in Core.h
  LLVMPositionBuilderAtEnd(builder, entryBB);

  // Initialize var_map to a new map: 
  //For each name in the set created above: 
  //Generate an alloc statement 
  //Add name, LLVMvalueRef of alloc statement generated above to var_map  

  for(auto& x : var_map){
      LLVMValueRef y = LLVMBuildAlloca(builder, LLVMInt32Type(), x.first.c_str()); 
	    LLVMSetAlignment(y, 4);
      x.second = y;
  }

	//Generate an alloc instruction for the return value and keep the LLVMValueRef, ret_ref, of this instruction available everywhere in your program
	ret_ref = LLVMBuildAlloca(builder, LLVMInt32Type(), "return"); 
	LLVMSetAlignment(ret_ref, 4);

	//Creating store instructions to make local copy of parameters
  if(num_params == 1){
      LLVMBuildStore(builder, LLVMGetParam(func, 0), var_map[function_node->func.param->stmt.decl.name]);
  }

  retBB = LLVMAppendBasicBlock(func, "retBB");
  LLVMPositionBuilderAtEnd(builder, retBB);
  LLVMValueRef ret_value = LLVMBuildLoad2(builder, LLVMInt32Type(), ret_ref, "");
  LLVMBuildRet(builder, ret_value);

  LLVMBasicBlockRef exitBB = genIRStmt(function_node->func.body, builder, entryBB);
  LLVMValueRef exit_term = LLVMGetBasicBlockTerminator(exitBB);
  if(exit_term == NULL){
    LLVMPositionBuilderAtEnd(builder, exitBB);
    LLVMBuildBr(builder, retBB);
  }

  /// BFS to identify Basic Blocks not reached
  deleteUnreachableBlocks(func);

	//Writing out the LLVM IR file and to stderr
	LLVMDumpModule(mod); //stderr
	LLVMPrintModuleToFile (mod, "test.ll", NULL); //to file here

	//Cleanup
  LLVMDisposeBuilder(builder);
	LLVMDisposeModule(mod);
}

LLVMBasicBlockRef genIRStmt(astNode* node, LLVMBuilderRef builder, LLVMBasicBlockRef startBB){
  astStmt* stmt = &(node->stmt);
  switch(stmt -> type){
    case ast_decl: {
      return startBB;
    }
    case ast_asgn: {
      LLVMPositionBuilderAtEnd(builder, startBB);
      LLVMValueRef result = genIRExpr(node->stmt.asgn.rhs, builder);
      astNode* var_node = node->stmt.asgn.lhs;

      LLVMBuildStore(builder, result, var_map[var_node->var.name]);
      return startBB;
    }
    case ast_call: {
      LLVMPositionBuilderAtEnd(builder, startBB);
      LLVMValueRef result = genIRExpr(node->stmt.call.param, builder);
      LLVMBuildCall2(builder, ret_print, func_print, &result, 1, "");
      return startBB;
    }
    case ast_while: {
      LLVMPositionBuilderAtEnd(builder, startBB);
      LLVMBasicBlockRef condBB = LLVMAppendBasicBlock(func, "condBB");
      LLVMBuildBr(builder, condBB);
      LLVMPositionBuilderAtEnd(builder, condBB);
      LLVMValueRef result = genIRExpr(node->stmt.whilen.cond, builder);
      LLVMBasicBlockRef trueBB = LLVMAppendBasicBlock(func, "trueBB");
      LLVMBasicBlockRef falseBB = LLVMAppendBasicBlock(func, "falseBB");
      LLVMBuildCondBr(builder, result, trueBB, falseBB);
      LLVMBasicBlockRef trueExitBB = genIRStmt(node->stmt.whilen.body, builder, trueBB);
      LLVMPositionBuilderAtEnd(builder, trueExitBB);
      LLVMBuildBr(builder, condBB);
      return falseBB;
    }
    case ast_if: {
      LLVMPositionBuilderAtEnd(builder, startBB);
      LLVMValueRef result = genIRExpr(node->stmt.ifn.cond, builder);
      LLVMBasicBlockRef trueBB = LLVMAppendBasicBlock(func, "trueBB");
      LLVMBasicBlockRef falseBB = LLVMAppendBasicBlock(func, "falseBB");
      LLVMBuildCondBr(builder, result, trueBB, falseBB);
      LLVMBasicBlockRef ifExitBB = genIRStmt(node->stmt.ifn.if_body, builder, trueBB);
      if(node->stmt.ifn.else_body == NULL){
        LLVMPositionBuilderAtEnd(builder, ifExitBB);
        LLVMBuildBr(builder, falseBB);
        return falseBB;
      }else{
        LLVMBasicBlockRef elseExitBB = genIRStmt(node->stmt.ifn.else_body, builder, falseBB);
        LLVMBasicBlockRef endBB = LLVMAppendBasicBlock(func, "endBB");
        LLVMPositionBuilderAtEnd(builder, ifExitBB);
        LLVMBuildBr(builder, endBB);
        LLVMPositionBuilderAtEnd(builder, elseExitBB);
        LLVMBuildBr(builder, endBB);
        return endBB;
      }
    }
    case ast_ret: {
      LLVMPositionBuilderAtEnd(builder, startBB);
      LLVMValueRef result = genIRExpr(node->stmt.ret.expr, builder);
      LLVMBuildStore(builder, result, ret_ref);
      LLVMBuildBr(builder, retBB);
      LLVMBasicBlockRef endBB = LLVMAppendBasicBlock(func, "endBB");
      return endBB;
    }
    case ast_block: {
      LLVMBasicBlockRef prevBB = startBB;
      vector<astNode*> slist = *(node->stmt.block.stmt_list);
      vector<astNode*>::iterator it = slist.begin();
      while (it != slist.end()){
        prevBB = genIRStmt(*it, builder, prevBB);
        it++;
      }
      return prevBB;
    }
    default: {
      return startBB;
    }
  }
}

LLVMValueRef genIRExpr(astNode* node, LLVMBuilderRef builder){
    switch(node -> type){
    case ast_cnst: {
      return LLVMConstInt(LLVMInt32Type(), node->cnst.value, true);
      break;
    }
    case ast_var: {
      return LLVMBuildLoad2(builder, LLVMInt32Type(), var_map[node->var.name], "");
      break;
    }
    case ast_uexpr: {
      LLVMValueRef uexpr_ref = genIRExpr(node->uexpr.expr, builder);
      LLVMValueRef zero_ref = LLVMConstInt(LLVMInt32Type(), 0, true);
      return LLVMBuildSub(builder, zero_ref, uexpr_ref, "");
      break;
    }
    case ast_bexpr: {
      LLVMValueRef lhs_ref = genIRExpr(node->bexpr.lhs, builder);
      LLVMValueRef rhs_ref = genIRExpr(node->bexpr.rhs, builder);
      LLVMValueRef calc_ref;
      switch(node->bexpr.op){
        case add: {
          calc_ref = LLVMBuildAdd(builder, lhs_ref, rhs_ref, "");
          break;
        }
        case sub: {
          calc_ref = LLVMBuildSub(builder, lhs_ref, rhs_ref, "");
          break;
        }
        case mul: {
          calc_ref = LLVMBuildMul(builder, lhs_ref, rhs_ref, "");
          break;
        }
        default: {
          calc_ref = NULL;
          break;
        }
      }

      return calc_ref;
      break;
    }
    case ast_rexpr: {
      LLVMValueRef lhs_ref = genIRExpr(node->rexpr.lhs, builder);
      LLVMValueRef rhs_ref = genIRExpr(node->rexpr.rhs, builder);
      LLVMValueRef cmp_ref;
      switch(node->rexpr.op){
        case lt: {
          LLVMIntPredicate op = LLVMIntSLT;
          cmp_ref = LLVMBuildICmp(builder, op, lhs_ref, rhs_ref, "");
          break;
        }
        case gt: {
          LLVMIntPredicate op = LLVMIntSGT;
          cmp_ref = LLVMBuildICmp(builder, op, lhs_ref, rhs_ref, "");
          break;
        }
        case le: {
          LLVMIntPredicate op = LLVMIntSLE;
          cmp_ref = LLVMBuildICmp(builder, op, lhs_ref, rhs_ref, "");
          break;
        }
        case ge: {
          LLVMIntPredicate op = LLVMIntSGE;
          cmp_ref = LLVMBuildICmp(builder, op, lhs_ref, rhs_ref, "");
          break;
        }
        case eq: {
          LLVMIntPredicate op = LLVMIntEQ;
          cmp_ref = LLVMBuildICmp(builder, op, lhs_ref, rhs_ref, "");
          break;
        }
        case neq: {
          LLVMIntPredicate op = LLVMIntNE;
          cmp_ref = LLVMBuildICmp(builder, op, lhs_ref, rhs_ref, "");
          break;
        }
      }
      return cmp_ref;
      break;
    }
    case ast_stmt: {
      return LLVMBuildCall2(builder, ret_read, func_read, NULL, 0, "");
    }
    default: {
      return NULL;
      break;
    }
  }
}

void deleteUnreachableBlocks(LLVMValueRef func){
  bool changed = true;
  while (changed) {
    changed = false;
    LLVMBasicBlockRef result = LLVMGetNextBasicBlock(LLVMGetEntryBasicBlock(func));
    while (result) {
      LLVMBasicBlockRef next = LLVMGetNextBasicBlock(result);
      if (LLVMGetFirstUse(LLVMBasicBlockAsValue(result)) == NULL) {
        LLVMDeleteBasicBlock(result);
        changed = true;
      }
      result = next;
    }
  }
}