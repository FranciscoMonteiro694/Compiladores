%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yylex(void);
    /*void yyerror (const char *s);*/
    void yyerror(const char* msg) {
      printf("%s\n", msg);
   }
%}
%union{
    char cval;
    int intval;
    char *string;
    double d;
}


%token <cval> OR
%token <string> AND
%token <cval> LT
%token <cval> GT
%token <cval> EQ
%token <string> NE
%token <string> LE
%token <string> GE
%token <cval> PLUS
%token <cval> MINUS
%token <cval> STAR
%token <cval> DIV
%token <cval> MOD
%token <cval> NOT
%token <string> INTLIT /*Vamos ter de mudar para número */
%token <string> REALLIT
%token <string> ID
%token <cval> LPAR
%token <cval> RPAR
%token <cval> SEMICOLON

/*para testes*/
%type <string> expr

/* Se usarmos dois lefts, ou rights, o de baixo tem prioridade sobre o de cima */
%left OR
%left AND
%left EQ NE
%nonassoc GE GT LE LT
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
%left LPAR RPAR



/*
com isto tudo left funciona *mindblown*
%left PLUS AND LT MINUS GT NOT MOD DIV GE STAR EQ NE LE OR ID
*/

%%



inicio: inicio expr
        | 
        ;


expr: ID {$$=$1;}
    |   REALLIT {$$=$1;printf("expr = REALLIT!\n");}
    |   INTLIT {$$=$1;printf("expr = INTLIT!\n");}
    |   expr AND expr {$$=$1;printf("expr = expr AND expr!\n");}
    |   expr PLUS expr {$$=$1;printf("expr = expr PLUS expr!\n");}
    |   expr LT expr {$$=$1;printf("expr = expr LT expr!\n");}
    |   expr MINUS expr {$$=$1;printf("expr = expr MINUS expr!\n");}
    |   expr GT expr {$$=$1;printf("expr = expr GT expr!\n");}
    |   expr NOT expr {$$=$1;printf("expr = expr NOT expr!\n");}
    |   expr MOD expr {$$=$1;printf("expr = expr MOD expr!\n");}
    |   expr DIV expr {$$=$1;printf("expr = expr DIV expr!\n");}
    |   expr GE expr {$$=$1;printf("expr = expr GE expr!\n");}
    |   expr STAR expr {$$=$1;printf("expr = expr STAR expr!\n");}
    |   expr EQ expr {$$=$1;printf("expr = expr EQ expr!\n");}
    |   expr NE expr {$$=$1;printf("expr = expr NE expr!\n");}
    |   expr LE expr {$$=$1;printf("expr = expr LE expr!\n");}
    |   expr OR expr {$$=$1;printf("expr = expr OR expr!\n");}
    |   LPAR expr RPAR {$$=$2;printf("expr = LPAR expr RPAR!\n");}
    |   funcInvocation 
    ;

/*
Statement: error;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR;

FuncInovcation: ID LPAR error RPAR;

Expression: LPAR error RPAR;

error: {yyeror()}
    ;
*/

%%

int main() {
    yyparse();
    return 0;
}
void yyerror () {
    /*
    void yyerror (char *s)
    */
    printf ("Line %d, column %d: %s: %s\n", <num linha >, <num coluna>, s, yytext);
    */
    printf ("BOOOOOOOOOOM! ESTOIROU, ERRO SINTÁTICO!\n");
}

