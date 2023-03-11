/* */
/* ******************************************* */
/* Prologue */
%{
#include <stdio.h>
int yylex();
void yyerror(const char*);
int yydebug;
%}
/* ******************************************* */
/* Declarations */
%define parse.error detailed
%define parse.lac full
/* ******************************************* */
/* Grammar */
%%
%%
//***********************************************
// Epilogue
int main(int argc, char *argv)
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
