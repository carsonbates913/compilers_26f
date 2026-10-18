#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ast.h"

bool is_declared(const char* name, const std::vector<std::vector<char*>> *block_stack, bool isDeclaring) {
  for (size_t i = (isDeclaring ? (block_stack->size() - 1) : 0); i < block_stack->size(); i++) {
    for(size_t j = 0; j < (*block_stack)[i].size(); j++){
      if(strcmp(name, (*block_stack)[i][j]) == 0){
        return true;
      }
    }
  }
  return false;
}

bool dfs(astNode* node, std::vector<std::vector<char*>>* block_stack){
  printf("new dfs\n");
  printf("node type: ");
  bool is_valid = true;
  switch(node -> type){
    case ast_var: {
      printf("if\n");
      return is_declared(node->var.name, block_stack, false);
      break;
    }
    case ast_cnst: {
      printf("constant\n");
      return true;
      break;
    }
    case ast_stmt: {
      printf("statement - ");
      astStmt* stmt = &(node->stmt);
      
      switch(stmt -> type){
        case ast_call: {
          printf("call\n");
          if(stmt->call.param != NULL){
            is_valid = (is_valid && dfs(stmt->call.param, block_stack));
          }
          return is_valid;
          break;
        }
        case ast_ret: {
          printf("return\n");
          return dfs(stmt->ret.expr, block_stack);
        }
        case ast_block: {
          printf("block\n");

          std::vector<char*> new_block;
          block_stack->push_back(new_block);

          vector<astNode*> slist = *(stmt->block.stmt_list);
          vector<astNode*>::iterator it = slist.begin();
          while (it != slist.end()){
            is_valid = (is_valid && dfs(*it, block_stack));
            it++;
          }
          block_stack->pop_back();
          return is_valid;
          break;
        }
        case ast_while: {
          printf("while\n");
          is_valid = (is_valid && dfs(stmt->whilen.cond, block_stack));
          is_valid = (is_valid && dfs(stmt->whilen.body, block_stack));
          return is_valid;
        }
        case ast_if: {
          printf("if\n");
          is_valid = (is_valid && dfs(stmt->ifn.cond, block_stack));

          is_valid = (is_valid && dfs(stmt->ifn.if_body, block_stack));

          if(stmt->ifn.else_body != NULL) {
            is_valid = (is_valid && dfs(stmt->ifn.else_body, block_stack));
          }
          return is_valid;
          break;
        }
        case ast_asgn: {
          printf("asgn\n");
          is_valid = (is_valid && dfs(stmt->asgn.rhs, block_stack));
          is_valid = (is_valid && dfs(stmt->asgn.lhs, block_stack));
          return is_valid;
          break;
        }
        case ast_decl: {
          printf("declaring %s\n", stmt->decl.name);
          bool result = is_declared(stmt->decl.name, block_stack, true);
          printf("decl done - %d\n", result);
          if(result){
            printf("already declared - false");
            return false;
          }else{
            printf("pushing\n");
            block_stack->back().push_back(stmt->decl.name);
            printf("done pushing \n");
            return true;
          }
          break;
        }
        default: {
          printf("nothing\n");
        }
      }
      return false;
      break;
    }
    case ast_prog: {
      printf("prog\n");
      return dfs(node->prog.func, block_stack);
      break;
    }
    case ast_func: {
      printf("funct\n");
      if(node->func.param != NULL) {
        is_valid = (is_valid && dfs(node->func.param, block_stack));
      }
      is_valid = (is_valid && dfs(node->func.body, block_stack));
      return is_valid;
      break;
    }
    case ast_rexpr: {
      printf("relational\n");
      is_valid = (is_valid && dfs(node->rexpr.lhs, block_stack));
      is_valid = (is_valid && dfs(node->rexpr.rhs, block_stack));
      return is_valid;
      break;
    }
    case ast_uexpr: {
      printf("unary\n");
      return dfs(node->uexpr.expr, block_stack);
      break;
    }
    case ast_bexpr: {
      printf("binary\n");
      is_valid = (is_valid && dfs(node->bexpr.lhs, block_stack));
      is_valid = (is_valid && dfs(node->bexpr.rhs, block_stack));
      return is_valid;
      break;
    }
    case ast_extern: {
      printf("extern\n");
      return true;
      break;
    }
    return false;
  }
}

int semantic_analysis(astNode* root_node){
  std::vector<std::vector<char*>> block_stack;
  std::vector<char*> first;
  block_stack.push_back(first);

  bool result = dfs(root_node, &block_stack);
  return (result ? 1 : 0);
}

//iterate through the tree from left to right
//building a vector of names by checking declarations
//then we are iterating through the rest of the statement checking if the statements use declared variables
//if we enter a new block, we pop our list on a stack. We repeat, except we check that stack also when looking at the variables used