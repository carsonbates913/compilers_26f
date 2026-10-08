%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ast.h"
extern int yylex();
extern int yylex_destroy();
extern int yywrap();
void yyerror(const char *);
extern FILE *yyin;
astNode *root;
%}

%union{
	int ival;
	char *idname;
	astNode *nptr;
	vector<astNode*> *svec;
}

// You need to add types of tokens and non-terminals
%token <idname> ID 
%token <ival> NUM
%token INT GT LT EQ GE LE

%type <nptr> assignment unaryexpression functionCall binaryexpression statement
%type <nptr> declaration term
%type <svec> declarations statements
%type <nptr> block

%start program /* build the grammar bottom up */
%%

program : block {root = $1;}

block : '{' declarations statements '}'		{
																						$2->insert($2->end(), $3->begin(), $3->end());
																						delete $3;
																						$$ = createBlock($2);
																					}
statements : statements statement {$$ = $1; $$->push_back($2);}
   				 | statement {$$ = new vector<astNode*>(); $$->push_back($1);}

statement : assignment ';' {$$ = $1;}

assignment : ID '=' term {$$ = createAsgn(createVar($1), $3); free($1);}
	| ID '=' binaryexpression {$$ = createAsgn(createVar($1), $3); free($1);}
	| ID '=' functionCall {$$ = createAsgn(createVar($1), $3); free($1);}
	| ID '=' unaryexpression {$$ = createAsgn(createVar($1), $3); free($1);}

unaryexpression : '-' term {$$ = createUExpr($2, uminus);}

functionCall : ID '(' ')' {$$ = createCall($1); free($1);}

binaryexpression : term '+' term {$$ = createBExpr($1, $3, add);}
								 | term '-' term {$$ = createBExpr($1, $3, sub);}
								 | term '*' term {$$ = createBExpr($1, $3, mul);}
								 | term '/' term {$$ = createBExpr($1, $3, divide);}

declarations : declarations declaration { $$ = $1; $$->push_back($2);}
						 | declaration {	$$ = new vector<astNode*>(); $$->push_back($1);}

declaration : INT ID ';' {$$ = createDecl($2); free($2);}

term : ID {$$ = createVar($1); free($1);}
		 | NUM {$$ = createCnst($1);}

%%
int main(int argc, char** argv){
	if (argc == 2){
  	yyin = fopen(argv[1], "r");
	}
	yyparse(); // Will set the root
	printNode(root);
	//sem_flag = semantic_analysis(root)
 	// Convert to LLVM IR
	// Code optimizer
	// Assembly code generator


	// Cleanup	
	freeNode(root);

	if (yyin != stdin)
		fclose(yyin);
	
	yylex_destroy();

	
	return 0;
}

void yyerror(const char *){
	fprintf(stderr, "Syntax error\n");
}
