%{
  #include <stdio.h>
  #include "y.tab.h"
%}
%%
([A-Z][a-zA-Z]*) {
  yylval.sname = strdup(yytext);
  return NAME;
}

[:] {return(yytext[0]);}

[0-9][0-9]* {
  yylval.ival = atoi(yytext);
  return NUM;
}

[ \t]

[\n] {
  return '\n';
}

[.]

%%
int yywrap() {
  return 1;
}