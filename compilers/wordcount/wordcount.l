/* From Flex & Bison by John Levine */
%{
// declarations and options settings
// copied through verbatim near the
// beginning of the generated scanner
int chars = 0;
int words = 0;
int lines = 0;
%}

%%
[^ \t\n\r\f\v]+   { ++words; chars += strlen(yytext); }
\n          { ++lines; ++chars; }
.           { ++chars; }

%%
// copied to the scanner
int main(int argc, char** argv)
{
    yylex();
    printf("lines: %d\twords: %d\tcharacters: %d\n", lines, words, chars);
}
