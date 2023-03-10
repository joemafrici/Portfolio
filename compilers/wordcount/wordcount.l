/* From Flex & Bison by John Levine */
/* ******************************************* */
/* Definitions */
%option noyywrap
%{
// copied verbatim near the top of output
#include <stdlib.h>
int chars = 0;
int words = 0;
int lines = 0;

int total_chars = 0;
int total_words = 0;
int total_lines = 0;
%}
/* ******************************************* */
/* Rules */
%%
[^ \t\n\r\f\v]+   { ++words; chars += strlen(yytext); }
\n          { ++lines; ++chars; }
.           { ++chars; }

%%
//***********************************************
// User Code
// copied to the scanner
int main(int argc, char** argv)
{
    if (argc < 2 )
    {
        yylex();
        printf("lines: %d\twords: %d\tcharacters: %d\n", lines, words, chars);
        return EXIT_SUCCESS;
    }

    for (size_t ii = 1; ii < argc; ++ii)
    {
        FILE* file = fopen(argv[ii], "r");
        if (!file)
        {
            perror(argv[ii]);
            return EXIT_FAILURE;
        }

        yyrestart(file);
        yylex();
        fclose(file);
        printf("lines: %d\twords: %d\tcharacters: %d\n", lines, words, chars);
        total_chars += chars;
        total_words += words;
        total_lines += lines;
        chars = 0;
        words = 0;
        lines = 0;

        if (argc > 2)
            printf("total lines: %d\twords: %d\tcharacters: %d\n",
                total_lines, total_words, total_chars);

    }

    return EXIT_SUCCESS;
}
