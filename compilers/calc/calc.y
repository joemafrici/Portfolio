/* Calculator Parser Generator From Flex & Bison */
/* ******************************************* */
%{
#include <stdio.h>
int yylex();
void yyerror(const char*);
int yydebug;
%}
/* ******************************************* */
%define parse.error detailed
%define parse.lac full
/* declare tokens */
/* terminal symbols */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token OP CP
%token EOL

/* ******************************************* */
/* grammar */
%%
calclist:   /* nothing - matches at beginning of input */
        | calclist exp EOL      { printf("= %d\n", $2); }
        | calclist EOL          { }
        ;
exp: factor                     /* default $$ = $1 */
   | exp ADD factor             { $$ = $1 + $3; }
   | exp SUB factor             { $$ = $1 - $3; }
   ;
factor: term
      | factor MUL term         { $$ = $1 * $3; }
      | factor DIV term         { $$ = $1 / $3; }
      ;
term: NUMBER
    | ABS term                  { $$ = $2 >= 0? $2 : - $2; }
    | OP exp CP                 { $$ = $2; }
    ;
%%
//***********************************************
// main function
int main(int argc, char **argv)
{
    #ifdef YYDEBUG
        yydebug = 1;
    #endif

    yyparse();
}
//***********************************************
// Prints error to stderr
void yyerror(const char* s)
{
    fprintf(stderr, "error: %s\n", s);
}
