/* */
/* ******************************************* */
/* Definitions */
%option nounput noyywrap nodefault yylineno case-insensitive
%{
    #include <string>
    #include <unordered_map>
    #include <list>
    #include <iostream>

    struct ref
    {
        std::string filename;
        int flags;
        int lineno;
    };
    struct symbol
    {
        std::string name;
        std::list<ref> reflist;
    };
    std::unordered_map<std::string, symbol> symbol_table;
    std::string curfilename;
%}
/* ******************************************* */
/* Rules */
%%
a |
an |
and |
are |
as |
at |
be |
but |
for |
in |
is |
it |
of |
on |
or |
that |
the |
this |
to                          { /* ignore common words */ }

[a-z]+(\'(s|t))?            {
                                if (const auto it = symbol_table.find(yytext);
                                    it != symbol_table.end())
                                {
                                    symbol& cursymbol = it->second;
                                    ref curref = ref { yytext, 0, yylineno };
                                    it->second.reflist.push_back(curref);
                                }
                                else
                                {
                                    /* doesn't exist in table */

                                }


                                ref curref = ref { yytext, 0, yylineno };
                                symbol cursymbol = symbol { yytext };
                                cursymbol.reflist.push_back(curref);
                                symbol_table[yytext] = cursymbol;
                            }
.|\n                        { /* ignore everything else */ }
%%
//***********************************************
// User Code
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "provide filename" << std::endl;
    }
    else
    {
        for (auto ii = 1; ii < argc; ++ii)
        {
            FILE *file = fopen(argv[ii], "r");
            if (!file) perror(argv[1]); return EXIT_FAILURE;

            curfilename = argv[ii];
            yyrestart(file);
            yylineno = 1;
            yylex();
            fclose(file);
        }
    }
    //printrefs();

    return EXIT_SUCCESS;

}
