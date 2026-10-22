%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ast.h"
#include "semantic_analysis.h"
extern int yylex();
extern int yylex_destroy();
extern int yywrap();
void yyerror(const char *);
extern FILE *yyin;
astNode *root;
%}

%define parse.error detailed
%define parse.trace

%union{
	int ival;
	char *idname;
	astNode *nptr;
	vector<astNode*> *svec;
}

// You need to add types of tokens and non-terminals
%token <idname> ID
%token <ival> NUM
%token INT VOID GT LT EQ GE LE NEQ IF WHILE ELSE EXTERN RETURN PRINT READ

%type <nptr> assignmentstatement unaryexpression functionCall binaryexpression statement declaration term ifstatement whilestatement condition relationalexpression function block printextern readextern returnstatement relitem program binaryexpressioncore
%type <svec> declarations statements

%start program
%%



program : printextern readextern function						{$$ = createProg($1, $2, $3); root = $$;}
				| readextern printextern function						{$$ = createProg($1, $2, $3); root = $$;}

printextern : EXTERN VOID PRINT '(' INT ')' ';' 		{$$ = createExtern(strdup("print"));printf("Matched: extern print ;\n");}

readextern : EXTERN INT READ '(' ')' ';'						{$$ = createExtern(strdup("read"));}

function : INT ID '(' INT ID ')' block							{$$ = createFunc($2, createDecl($5), $7);}
				 | INT ID '(' ')' block											{$$ = createFunc($2, NULL, $5);}

whilestatement : WHILE condition block							{$$ = createWhile($2, $3);}

ifstatement : IF condition block										{$$ = createIf($2, $3);}
						| IF condition block ELSE block					{$$ = createIf($2, $3, $5);}
						| IF condition block ELSE statement			{$$ = createIf($2, $3, $5);}
						| IF condition statement								{$$ = createIf($2, $3);}
						| IF condition statement ELSE block			{$$ = createIf($2, $3, $5);}
						| IF condition statement ELSE statement {$$ = createIf($2, $3, $5);}

condition : '(' relationalexpression ')'						{$$ = $2;}

block : '{' declarations statements '}'							{
																											$2->insert($2->end(), $3->begin(), $3->end());
																											delete $3;
																											$$ = createBlock($2);
																										}
statements : statements statement 									{$$ = $1; $$->push_back($2);}
   				 | statement 															{$$ = new vector<astNode*>(); $$->push_back($1);}

statement : assignmentstatement 										{$$ = $1;}
					| ifstatement															{$$ = $1;}
					| whilestatement													{$$ = $1;}
					| returnstatement													{$$ = $1;}
					| functionCall ';'												{$$ = $1;}

returnstatement : RETURN term ';'										{$$ = createRet($2);}
								| RETURN binaryexpression ';'				{$$ = createRet($2);}
								| RETURN unaryexpression ';'				{$$ = createRet($2);}
								| RETURN functionCall ';'						{$$ = createRet($2);}

assignmentstatement : ID '=' term ';'								{$$ = createAsgn(createVar($1), $3); free($1);}
					 					| ID '=' binaryexpression ';'		{$$ = createAsgn(createVar($1), $3); free($1);}
					 					| ID '=' functionCall ';'				{$$ = createAsgn(createVar($1), $3); free($1);}
					 					| ID '=' unaryexpression ';'		{$$ = createAsgn(createVar($1), $3); free($1);}

unaryexpression : '-' term 													{$$ = createUExpr($2, uminus);}

functionCall : ID '(' ')' 													{$$ = createCall($1, NULL); free($1);}
						 | ID '(' term ')'											{$$ = createCall($1, $3); free($1);}
						 | PRINT '(' term ')'										{$$ = createCall(strdup("print"), $3); }
						 | READ '(' ')'													{$$ = createCall(strdup("read"), NULL);}

binaryexpression : '(' binaryexpressioncore ')'			{$$ = $2;}
								 | binaryexpressioncore							{$$ = $1;}

binaryexpressioncore : term '+' term 								{$$ = createBExpr($1, $3, add);}
										 | term '-' term 								{$$ = createBExpr($1, $3, sub);}
										 | term '*' term 								{$$ = createBExpr($1, $3, mul);}
										 | term '/' term 								{$$ = createBExpr($1, $3, divide);}

relationalexpression : relitem GT relitem 					{$$ = createRExpr($1, $3, gt);}
										 | relitem LT relitem 					{$$ = createRExpr($1, $3, lt);}
										 | relitem EQ relitem 					{$$ = createRExpr($1, $3, eq);}
										 | relitem GE relitem 					{$$ = createRExpr($1, $3, ge);}
										 | relitem LE relitem 					{$$ = createRExpr($1, $3, le);}
										 | relitem NEQ relitem					{$$ = createRExpr($1, $3, neq);}

relitem : term																			{$$ = $1;}
				| binaryexpression													{$$ = $1;}

declarations : declarations declaration 						{$$ = $1; $$->push_back($2);}
						 | declaration													{
																											$$ = new std::vector<astNode*>();
																											$$->push_back($1);
																										}
						 | 																			{$$ = new vector<astNode*>();}

declaration : INT ID ';' 														{$$ = createDecl($2); free($2);}

term : ID 																					{$$ = createVar($1); free($1);}
		 | '(' ID ')'																		{$$ = createVar($2); free($2);}
		 | NUM 																					{$$ = createCnst($1);}
		 | '(' NUM ')'																	{$$ = createCnst($2);}

%%
int main(int argc, char** argv){
	if (argc == 2){
  	yyin = fopen(argv[1], "r");
	}
	yyparse(); // Will set the root
	printNode(root);
	int sem_flag = semantic_analysis(root);
	printf("\n%d\n", sem_flag);

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
