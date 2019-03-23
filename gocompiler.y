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
%token <string> STRING
%token <string> BOOL
%token <string> INT
%token <string> FLOAT32
%token <string> COMMA
%token <string> VAR
%token <string> SEMICOLON
/*para testes*/

%right ID 
%left  PLUS AND
%%

Program:
	PACKAGE ID SEMICOLON Declarations {printf("Program\n");}
	;
Declarations:
	VarDeclaration SEMICOLON
	|FuncDeclaration SEMICOLON
	|Declarations Declarations
	|
	;

VarDeclaration:
	VAR VarSpec {printf("VarDeclaration\n");}
	|VAR LPAR VarSpec SEMICOLON RPAR {printf("VarDeclaration\n");}
	;


VarSpec:
	|ID teste Type {printf("Varspec\n");}
	;
teste:
	COMMA ID teste 
	|
	;


Type:
	INT	{printf("Type---->Int\n");}
	|BOOL	{printf("Type---->BOOL\n");}
	|STRING	{printf("Type---->STRING\n");}
	|FLOAT32	{printf("Type---->FLOAT32\n");}	
	;







%%

int main() {
    yyparse();
    return 0;
}


