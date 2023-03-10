/* Calculator Parser Generator From Flex & Bison */
%{
#include <stdio.h>
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL

%%
calclist:   /* nothing - matches at beginning of input */
        | calclist exp EOL      { printf("= %d\n", $1); }
        ;
exp: factor                     /* default $$ = $1 */
   | exp ADD factor             { $$ = $1 + $3; }
   | exp SUB factor             { $$ = $1 - $3; }
   ;
factor: term
      | factor MUl term         { $$ = $1 * $3; }
      | factor DIV term         { $$ = $1 / $3; }
      ;
term: NUMBER
    | ABS term                  { $$ = $2 >= 0? $2 : - $2; }
    ;
%%

main(int argc, char **argv)
{
    yyparse();
}

yyerror(char* s)
{
    fprintf(stderr, "error: %s\n", s);
}
