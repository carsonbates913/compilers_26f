%{
#include<stdio.h>
extern int yylex();
extern int yylex_destroy();
extern int yywrap();
int yyerror(char*);
extern FILE *yyin;
%}
%union{
  int ival;
  char* sname;
}

%token <ival> NUM
%token <sname> NAME
%type <ival> score
%start exprs
%%
exprs: exprs '\n' expr
      | expr

expr: NAME ':' score {printf("%s: %d\n", $1, $3);}

score: score NUM {$$ = $1 + $2;}
      | NUM {$$ = $1;}
%%
int yyerror(char *s){
  fprintf(stderr, "%s\n", s);
  return 0;
}

int main(int argc, char* argv[]){
  if (argc == 2){
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
      fprintf(stderr, "File open error\n");
      return 1;
    }
  }
  yyparse();
  if (argc == 2) fclose(yyin);
  yylex_destroy();
  return 0; 
}