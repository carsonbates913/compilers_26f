%{
	#include <stdio.h>
	#include "ast.h"
	#include "y.tab.h"
	#include <string.h>
%}
letter [a-zA-Z]
digit [0-9]
%%
int										{return INT;}

{letter}[a-zA-Z0-9_]*	{ yylval.idname = strdup(yytext);
													return ID;}
[1-9]{digit}+						{ yylval.ival = atoi(yytext);
													return NUM;}
">"									  {return GT;}
"<"									  {return LT;}
"=="									{return EQ;}
">="									{return GE;}
"<="								  {return LE;}
[ \t\n]
.										{return yytext[0];}
%%

int yywrap(){
	return 1;
}

