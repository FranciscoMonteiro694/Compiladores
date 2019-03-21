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

%left PLUS AND LT MINUS GT NOT MOD DIV GE STAR EQ NE LE OR
%%



statement: expr                        ;
/*
expr: 
    |   INTLIT
    |   REALLIT
    |   funcInvocation
    |   LPAR expr RPAR
    ;
*/
expr: ID {$$=$1;printf("expr = ID\n");}
    |   expr AND expr {$$=$1;printf(" expr = expr AND expr!\n");}
    |   expr PLUS expr {$$=$1;printf(" expr = expr PLUS expr!\n");}
    |   expr LT expr {$$=$1;printf(" expr = expr LT expr!\n");}
    |   expr MINUS expr {$$=$1;printf(" expr = expr MINUS expr!\n");}
    |   expr GT expr {$$=$1;printf(" expr = expr GT expr!\n");}
    |   expr NOT expr {$$=$1;printf(" expr = expr NOT expr!\n");}
    |   expr MOD expr {$$=$1;printf(" expr = expr MOD expr!\n");}
    |   expr DIV expr {$$=$1;printf(" expr = expr DIV expr!\n");}
    |   expr GE expr {$$=$1;printf(" expr = expr GE expr!\n");}
    |   expr STAR expr {$$=$1;printf(" expr = expr STAR expr!\n");}
    |   expr EQ expr {$$=$1;printf(" expr = expr EQ expr!\n");}
    |   expr NE expr {$$=$1;printf(" expr = expr NE expr!\n");}
    |   expr LE expr {$$=$1;printf(" expr = expr LE expr!\n");}
    |   expr OR expr {$$=$1;printf(" expr = expr OR expr!\n");}
    ;
%%

int main() {
    yyparse();
    return 0;
}

