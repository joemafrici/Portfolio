/* calculator from Flex & Bison by John Levine */
%{
#include "calc.tab.h"
%}

%option noinput
%option nounput
%option nodefault

%%
"+"                 { return ADD; }
"-"                 { return SUB; }
"*"                 { return MUL; }
"/"                 { return DIV; }
"|"                 { return ABS; }
"("                 { return OP; }
")"                 { return CP; }
"//".*              { /* ignore comment */ }
[0-9]+              { yylval = atoi(yytext); return NUMBER; }
0x[a-f0-9]+         { yylval = strtol(yytext, NULL, 16); return NUMBER; }
\n                  { return EOL; }
[ \t]               { /* ignore whitespace */ }
.                   { printf("MYSTERY CHARACTER %c\n", *yytext); }
%%
/*
int main(int argc, char** argv)
{
    int tok;

    while (tok = yylex())
    {
        printf("%d", tok);
        if (tok == NUMBER) printf(" = %d\n", yylval);
        else printf("\n");
    }
}
*/
