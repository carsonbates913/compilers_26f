#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ast.h"

int check_variable(char* name, std::vector<std::vector<char*>> block_stack);

int dfs(astNode* node, std::vector<std::vector<char*>> block_stack);

int semantic_analysis(astNode* root_node);

#endif