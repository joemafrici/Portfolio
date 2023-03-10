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
    | calclist exp EOL          { printf("= %d\n", $1); }
    ;
exp: factor
   | exp ADD factor             { $$ = $1 + $3; }
   | exp SUB factor             { $$ = $1 - $3; }
   ;

%%
