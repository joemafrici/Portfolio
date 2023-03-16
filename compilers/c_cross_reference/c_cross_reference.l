/* *******************************************
 * C Cross Referencer
 * Author: Joe Mafrici
 * ******************************************* */
/* Definitions */
%option nounput noyywrap nodefault yylineno
%x COMMENT
%x IFILE

UCN     (\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})
EXP     ([Ee][-+]?[0-9]+)
ILEN    ([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)

%{
    #include <string>
    #include <unordered_map>
    #include <vector>
    #include <list>
    #include <iostream>

    struct bufstate
    {
        YY_BUFFER_STATE bs;
        int lineno;
        std::string filename;
        FILE* file;
    }
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
    std::vector<bufstate> bufstack;
    std::string curfilename; /* this might always be on the top of the stack */
    bool defining;       /* set when a name is likely to be a
                          * definition rather than a reference*/
    void printrefs();
    void addref();
%}
/* ******************************************* */
/* Rules */
%%
"/*"                    { BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.   { /* do nothing */ }
<COMMENT><<EOF>>        { printf("%s:%d: Unterminated comment\n",
                            curfilename, yylineno); return EXIT_FAILURE; }
"//".*\n                { /* do nothing */ }
/* declaration keywords */
_Bool |
_Complex |
_Imaginary |
auto |
char |
const |
double |
enum |
extern |
float |
inline |
int |
long |
register |
restrict |
short |
signed |
static |
struct |
typedef |
union |
unsigned |
void |
volatile                { defining = true; }
/* keywords */
break
case
continue
default
do
else
for
goto
if
return
sizeof
switch
while                   { /* do nothing */ }

/* constants */

/* integers */
0[0-7]*{ILEN}?
[1-9][0-9]*{ILEN}?
0[Xx][0-9a-fA-F]+{ILEN}?
/* decimal float */
([0-9]*\.[0-9]+|[0-9]+\.){EXP}?[flFL]?
[0-9]+{EXP}[flFL]?

/* hex float */
0[Xx]([0-9a-fA-F]*\.[0-9a-fA-F]+\.?)[Pp][-+]?[0-9]+[flFL]?

/* char const */
\'([^'\\]|\\['\"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+|{UCN})+\'
/* string literal */
L?\"([^"\\]|\\['\"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+|{UCN})*\"

/* punctuators */
"{"|"<%"|";"                { defining = true; }
"["|"]""|""("|")"|"{"|"}"|"."|"->"
"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"
"/"|"%"|"<<"|">>"|"<"|">"|"<="|">"|"=="|"^"|"|"|"&&"|"||"
"?"|":"|";"|"..."
"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="
","|"#"|"##"
"<:"|":>"|"%>"|"%:"|"%:%:"
/* identifier */
([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*   { addref(yytext, yylineno); }
/* whitespace */
[ \t\n]+
\\$

/* preprocessor stuff */
"#"" "*if.*\n
"#"" "*else.*\n
"#"" "*endif.*\n
"#"" "*define.*\n
"#"" "*line.*\n

/* recognize an include */
^"#"[ \t]*include[ \t]*[\"<]            { BEGIN IFILE; }
<IFILE>[^>\"]+
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
            if (!file)
            {
                perror(argv[1]);
                return EXIT_FAILURE;
            }

            curfilename = argv[ii];
            yyrestart(file);
            yylineno = 1;
            yylex();
            fclose(file);
        }
    }
    printrefs();

    return EXIT_SUCCESS;

}
//***********************************************
// Add a reference to symbol_table
void addref(char* text, int lineno)
{
    if (const auto it = symbol_table.find(text); it != symbol_table.end())
    {
        //symbol& cursymbol = it->second;
        ref curref = ref { text, 0, lineno};
        it->second.reflist.push_back(curref);
    }
    else
    {
        /* doesn't exist in table */
        ref curref = ref { text, 0, lineno};
        symbol cursymbol = symbol { text};
        cursymbol.reflist.push_back(curref);
        symbol_table[text] = cursymbol;
    }

}
//***********************************************
// Prints each symbol in symbol_table
// Prints each line the symbol is on
void printrefs()
{
    for (const auto& [key, symb] : symbol_table)
    {
        std::cout << "For Key: " << key << std::endl;
        std::cout << "Symbol: " << symb.name << std::endl;
        for (const auto& x : symb.reflist)
        {
            std::cout << "Filename: " << x.filename <<
                " on line " << x.lineno << std::endl;
        }

    }
}
