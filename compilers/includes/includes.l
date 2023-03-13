/* */
/* ******************************************* */
/* Definitions */
%option noyywrap
%option nodefault
%option nounput
%x IFILE
%{
    #include <stdlib.h>
    typedef struct bufstack bufstack;
    struct bufstack
    {
        bufstack *prev;
        YY_BUFFER_STATE bs;
        int lineno;
        char* filename;
        FILE* file;
    } *cur_bs = NULL;

    char* cur_filename;
    int push_file(char* filename);
    int pop_file();
%}
/* ******************************************* */
/* Rules */
/* ^"#"[ \t]*include[ \t]*\[\"<]       { BEGIN IFILE; } */
%%
"#"include.<                          { BEGIN IFILE; }
<IFILE>[^ \t\n\">]+                 {   /* throw away the rest of the include
                                         * line
                                         * */
                                        int c;
                                        while ((c = input()) && c != '\n');
                                        /* when scanning returns to this file,
                                         * resume at beginning of line following
                                         * the include
                                         */
                                        yylineno++;
                                        if (!push_file(yytext))
                                            yyterminate(); /* no such file */
                                        BEGIN INITIAL;
                                    }
<IFILE>.|\n                         {   fprintf(stderr, "%4d bad include line\n"
                                            "scanned: %s\n", yylineno, yytext);
                                        yyterminate();
                                    }
                                        /* pop file stack at end of file
                                         * terminate if outermost file*/
<<EOF>>                             {   if (!pop_file()) yyterminate(); }
                                        /* print the line number at the
                                         * beginning of each line */
^.                                  {   fprintf(yyout, "%4d %s",
                                            yylineno, yytext);
                                    }
^\n                                 {   fprintf(yyout, "%4d %s",
                                            yylineno++, yytext);
                                    }
\n                                  { ECHO; yylineno++; }
.                                   { ECHO; }
%%
//***********************************************
// User Code
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "need filename\n");
        return EXIT_FAILURE;
    }
    if (push_file(argv[1])) yylex();
}
//***********************************************
// Push a file onto the stack
// Save previous file state
// Prepare scanner state to read from beginning
// of new file
// Called after scanner matches a #include
// filename: name of the file to push
// return: 1 on success
// return: 0 on failure
int push_file(char *filename)
{
    printf("push_file called with filename %s\n", filename);
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror(filename);
        return 0;
    }

    bufstack *bs = malloc(sizeof(bufstack));
    if (!bs)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // we are in a nested include
    // store current line number
    if (cur_bs) cur_bs->lineno = yylineno;
    bs->prev = cur_bs;

    bs->bs = yy_create_buffer(file, YY_BUF_SIZE);
    bs->file = file;
    bs->filename = filename;
    yy_switch_to_buffer(bs->bs);
    cur_bs = bs;
    yylineno = 1;
    cur_filename = filename;
    return 1;

}
//***********************************************
// Pops a file off the stack
// Delete current buffer state
// Restore scanner state for previous file
// return: 1 on success
// return: 0 on failure
int pop_file()
{
    bufstack* bs = cur_bs;
    bufstack* prev_bs;

    if (!bs) return 0;

    fclose(bs->file);
    yy_delete_buffer(bs->bs);

    prev_bs = bs->prev;
    free(bs);

    if (!prev_bs) return 0;

    yy_switch_to_buffer(prev_bs->bs);
    cur_bs = prev_bs;
    yylineno = cur_bs->lineno;
    cur_filename = cur_bs->filename;
    return 1;
}
