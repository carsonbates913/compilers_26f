%{
  #include<stdio.h>
  #include<string.h>
  char* names[100];
  int scores[100];
  int idx = 0;
  int running_sum = 0;
%}
%%
([a-zA-Z]+) {
                names[idx] = strdup(yytext);
              }
([0-9]+)  {
            int val = atoi(yytext);
            running_sum += val;
          }
[ |,|:] { }
[\n]  {
        scores[idx] = running_sum;
        printf("%s: %d \n", names[idx], scores[idx]);
        idx++;
        running_sum = 0;
      }
%%
int yywrap(){
  return(1);
}
int main(int argc, char* argv[]){
  if (argc == 2){
    yyin = fopen(argv[1], "r");
    if (yyin == NULL){
      printf("Error\n");
      return(1);
    }
  }
  yylex();
  return(0);
}