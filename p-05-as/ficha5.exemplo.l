%{
#include "structures.h"
#include "symbol_table.h"
#include "semantics.h"
#include "y.tab.h"

table_element *symtab=NULL;

extern is_program* myprogram;

/*Adicionado por mim */
int numcolunas=1;

%}
%option yylineno
ID       [a-z][a-z0-9]*

%%
integer     {numcolunas+=yyleng;return INTEGER;}
double      {numcolunas+=yyleng;return DOUBLE;}
char        {numcolunas+=yyleng;return CHARACTER;}
let         {numcolunas+=yyleng;return LET;}
in          {numcolunas+=yyleng;return IN;}
end         {numcolunas+=yyleng;return END;}
write       {numcolunas+=yyleng;return WRITE;}
{ID}        {yylval.id = strdup(yytext);numcolunas+=yyleng;return IDENTIFIER;}
[ \t]+    {numcolunas+=yyleng;}/* ignorar espacos em branco e mudancas de linha, modifiquei cenas aqui*/
.           {numcolunas+=yyleng;return yytext[0];}
"\n"		{numcolunas=1;}
%%

int main(int argc, char **argv) {
    int errors;
    yyparse();
    errors=check_program(myprogram);
    if(errors>0)
        printf("The program has %d errors!\n", errors);
    show_table();
    yylex_destroy();
    return 0;
}



int yywrap(void){
    return 1;
}
/**************************
*****************************/
