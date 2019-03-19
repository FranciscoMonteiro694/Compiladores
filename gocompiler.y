%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror (const char *s);
%}
%union{
    char cval;
    int intval;
    char string[100];
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
%token <intval> INTLIT
%token <intval> REALLIT
%token <string> ID
%token <cval> LPAR
%token <cval> RPAR


%%



calc: expression                        {printf("%d\n", $1);}

expr: expr OR expr   {$$=$1+$3;}
    |   expr AND expr    
    |   expr LT expr 
    |   expr GT expr 
    |   expr EQ expr 
    |   expr NE expr 
    |   expr LE expr
    |   expr GE expr 
    |   expr PLUS expr
    |   expr MINUS expr
    |   expr STAR expr
    |   expr DIV expr
    |   expr MOD expr
    |   expr NOT expr
    |   expr MINUS expr
    |   expr PLUS expr
    |   INTLIT
    |   REALLIT
    |   ID
    |   funcInvocation
    |   LPAR expr RPAR


    ;
%%

int main() {
    yyparse();
    return 0;
}

