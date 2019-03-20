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

/*para testes*/
%type <string> expr

%left PLUS
%%



statement: expr                        ;
/*
expr: expr OR expr   {$$=$1+$3;}
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
    |   INTLIT
    |   REALLIT
    |   ID {$$=$1;printf("Encontrei um ID\n");}
    |   funcInvocation
    |   LPAR expr RPAR
    ;
*/
    expr: ID {$$=$1;printf("expr = ID\n");}
    |   expr AND expr {$$=$1;printf(" expr = expr AND expr!\n");}
    |   expr PLUS expr {$$=$1;printf(" expr = expr PLUS expr!\n");}
    ;
%%

int main() {
    yyparse();
    return 0;
}

