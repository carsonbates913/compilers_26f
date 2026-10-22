#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ast.h"

static bool has_return = false;
static std::string function_name;
static int num_params;

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

bool dfs(astNode* node, std::vector<std::vector<char*>>* block_stack, bool is_function_def){
  //printf("new dfs\n");
  //printf("node type: ");
  bool is_valid = true;
  switch(node -> type){
    case ast_var: {
      //printf("variable\n");
      bool result = is_declared(node->var.name, block_stack, false);
      if(!result){
        printf("error: variable %s is not declared\n", node->var.name);
      }
      return result;
      break;
    }
    case ast_cnst: {
      //printf("constant\n");
      return true;
      break;
    }
    case ast_stmt: {
      //printf("statement - ");
      astStmt* stmt = &(node->stmt);
      
      switch(stmt -> type){
        case ast_call: {
          //printf("call\n");
          std::string current_name = stmt->call.name;
          //printf("gave current_name\n");
          int required_num_params;
          if (current_name == "read") {
            required_num_params = 0;
          } else if (current_name == "print") {
            //printf("see its print\n");
            required_num_params = 1;
          } else if (current_name == function_name) {
            required_num_params = num_params;
          } else {
            printf("error: function not defined\n");
            return is_valid = false;
          }
          if(stmt->call.param != NULL){
            //printf("call param is not null\n");
            if(required_num_params != 1){
              printf("error: param is given when not expected");
              is_valid = false;
            }
            is_valid = (is_valid && dfs(stmt->call.param, block_stack, false));
          }else{
            //printf("it is null \n");
            if(required_num_params != 0){
              printf("error: no params are given when expected");
              is_valid = false;
            }
          }
          return is_valid;
          break;
        }
        case ast_ret: {
          //printf("return\n");
          has_return = true;

          return dfs(stmt->ret.expr, block_stack, false);
        }
        case ast_block: {
          //printf("block\n");

          if(!is_function_def){
            std::vector<char*> new_block;
            block_stack->push_back(new_block);
          }

          vector<astNode*> slist = *(stmt->block.stmt_list);
          vector<astNode*>::iterator it = slist.begin();
          while (it != slist.end()){
            is_valid = (is_valid && dfs(*it, block_stack, false));
            it++;
          }
          block_stack->pop_back();
          return is_valid;
          break;
        }
        case ast_while: {
         //printf("while\n");
          is_valid = (is_valid && dfs(stmt->whilen.cond, block_stack, false));
          is_valid = (is_valid && dfs(stmt->whilen.body, block_stack, false));
          return is_valid;
        }
        case ast_if: {
          //printf("if\n");
          is_valid = (is_valid && dfs(stmt->ifn.cond, block_stack, false));

          is_valid = (is_valid && dfs(stmt->ifn.if_body, block_stack, false));

          if(stmt->ifn.else_body != NULL) {
            is_valid = (is_valid && dfs(stmt->ifn.else_body, block_stack, false));
          }
          return is_valid;
          break;
        }
        case ast_asgn: {
          //printf("asgn\n");

          astNode* rhs = stmt->asgn.rhs;
          if (rhs != NULL && rhs->type == ast_stmt && rhs->stmt.type == ast_call) {
            std::string x = rhs->stmt.call.name;
            if (x == "print") {
              printf("error: assigning the result of void function print\n");
              return false;
            }
          }

          is_valid = (is_valid && dfs(stmt->asgn.rhs, block_stack, false));
          is_valid = (is_valid && dfs(stmt->asgn.lhs, block_stack, false));
          return is_valid;
          break;
        }
        case ast_decl: {
          //printf("declaring %s\n", stmt->decl.name);
          if(!is_function_def){
            bool result = is_declared(stmt->decl.name, block_stack, true);
            if(result){
              printf("error: variable already declared");
              return false;
            }else{
              block_stack->back().push_back(stmt->decl.name);
              return true;
            }
          }else{
            std::vector<char*> new_block;
            block_stack->push_back(new_block);
            block_stack->back().push_back(stmt->decl.name);
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
      //printf("prog\n");
      return dfs(node->prog.func, block_stack, false);
      break;
    }
    case ast_func: {
     // printf("function\n");
      if (function_name.empty()) {
        function_name = node->func.name;
        num_params = (node->func.param != NULL) ? 1 : 0;
      }else{
        printf("error: cannot declare more than one function\n");
      }
      if(node->func.param != NULL) {
        is_valid = (is_valid && dfs(node->func.param, block_stack, true));
      }
      is_valid = (is_valid && dfs(node->func.body, block_stack, true));
      return is_valid;
      break;
    }
    case ast_rexpr: {
      //printf("relational\n");
      is_valid = (is_valid && dfs(node->rexpr.lhs, block_stack, false));
      is_valid = (is_valid && dfs(node->rexpr.rhs, block_stack, false));
      return is_valid;
      break;
    }
    case ast_uexpr: {
      //printf("unary\n");
      return dfs(node->uexpr.expr, block_stack, false);
      break;
    }
    case ast_bexpr: {
      //printf("binary\n");
      is_valid = (is_valid && dfs(node->bexpr.lhs, block_stack, false));
      is_valid = (is_valid && dfs(node->bexpr.rhs, block_stack, false));
      return is_valid;
      break;
    }
    case ast_extern: {
      //printf("extern\n");
      return true;
      break;
    }
    default: {
      return false;
    }
    return false;
  }
  return false;
}

int semantic_analysis(astNode* root_node){
  std::string function_name;

  std::vector<std::vector<char*>> block_stack;
  std::vector<char*> first;
  block_stack.push_back(first);

  bool result = dfs(root_node, &block_stack, false);
  if(!has_return && result == true){
    printf("error: no return value given\n");
    return 0;
  }
  return ((result == true) ? 1 : 0);
}

//iterate through the tree from left to right
//building a vector of names by checking declarations
//then we are iterating through the rest of the statement checking if the statements use declared variables
//if we enter a new block, we pop our list on a stack. We repeat, except we check that stack also when looking at the variables used