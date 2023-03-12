/* */
/* ******************************************* */
/* Definitions */
%option noyywrap nodefault yylineno case-insensitive
%{
    #include <stdlib.h>
    typedef struct symbol
    {
        char* name;
        struct ref* reflist;
    };
    typedef struct ref
    {
        struct ref* next;
        char* filename;
        int flags;
        int lineno;
    };

    #define NHASH 9997
    symbol table[NHASH];
    symbol* lookup(char*);
    void addref(int, char*, char*, int);
    char* curfilename;
%}
/* ******************************************* */
/* Rules */
%%
%%
//***********************************************
// User Code
int main(int argc, char** argv)
{
    return EXIT_SUCCESS;
}
