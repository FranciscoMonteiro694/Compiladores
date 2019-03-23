%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yylex(void);
    void yyerror ();
    /*void yyerror (const char *s);*/
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

%token <string> RSQ
%token <string> FOR
%token <string> CMDARGS
%token <cval> BLANKID
%token <string> FUNC
%token <cval> RBRACE
%token <cval> LSQ
%token <cval> ASSIGN
%token <string> IF
%token <string> RETURN
%token <cval> LBRACE
%token <string> PARSEINT
%token <cval> COMMA
%token <string> STRLIT
%token <string> ELSE
%token <string> PRINT
%token <string> FLOAT32
%token <string> STRING
%token <string> BOOL
%token <string> INT
%token <string> PACKAGE
%token <string> VAR


%type <string> Expr
%type <string> FuncInvocation




/* Se usarmos dois lefts, ou rights, o de baixo tem prioridade sobre o de cima */
%left OR
%left AND
%left EQ NE
%nonassoc GE GT LE LT 
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
%left LPAR RPAR


%%


/*
inicio: inicio Expr
        | 
        ;
*/
Program: PACKAGE ID SEMICOLON Declarations {printf("Program\n");} /* Entra aqui */
    ;

/*
Estava este antes e dava 6 e 4 erros
Declarations: VarDeclaration SEMICOLON
    |FuncDeclaration SEMICOLON
    |Declarations Declarations
    |
    ;
*/

Declarations: Declarations VarDeclaration SEMICOLON {printf("Declarations");}
    |   Declarations FuncDeclaration SEMICOLON {printf("Declarations");}
    |   {printf("Encontrei");}
    ;

VarDeclaration: VAR VarSpec {printf("VarDeclaration\n");}
    |VAR LPAR VarSpec SEMICOLON RPAR {printf("VarDeclaration\n");}
    ;

VarSpec: ID teste Type {printf("Varspec\n");}
    ;

teste: teste COMMA ID  {printf("Aux");}
    |   {printf("Aux");}
    ;

Type: INT {printf("Type---->Int\n");}
    |BOOL   {printf("Type---->BOOL\n");}
    |STRING {printf("Type---->STRING\n");}
    |FLOAT32    {printf("Type---->FLOAT32\n");} 
    ;

FuncDeclaration: FUNC ID LPAR RPAR FuncBody {printf("FuncDeclaration");} 
    |   FUNC ID LPAR Parameters RPAR FuncBody {printf("FuncDeclaration");} 
    |   FUNC ID LPAR RPAR Type FuncBody {printf("FuncDeclaration");} 
    |   FUNC ID LPAR Parameters RPAR Type FuncBody {printf("FuncDeclaration");} 
    ;

Parameters: ID Type AuxParameters {printf("Parameters");} 
    ;

AuxParameters: AuxParameters COMMA ID Type {printf("Aux");}
    |   {printf("Aux");}
    ;

FuncBody: LBRACE VarsAndStatements RBRACE {printf("FuncBody");} 
        ;

VarsAndStatements: VarsAndStatements SEMICOLON {printf("VarsAndStatements");} 
    |   VarsAndStatements VarDeclaration SEMICOLON {printf("VarsAndStatements");}
    |   VarsAndStatements Statement SEMICOLON {printf("VarsAndStatements");}
    |   {printf("VarsAndStatements");}
    ;

Statement: PRINT LPAR Expr RPAR {printf("Statement");}
    |   PRINT LPAR STRLIT RPAR {printf("Statement");}
    |   error {printf("errorrrrrr");}
    |   FuncInvocation {printf("Statement");}
    |   ParseArgs {printf("Statement");}
    |   RETURN {printf("Statement");}
    |   RETURN Expr {printf("Statement");}
    |   FOR Expr LBRACE AuxStatement1 RBRACE {printf("Statement");}
    |   FOR LBRACE AuxStatement1 RBRACE {printf("Statement");}
    |   ID ASSIGN Expr {printf("Statement");}
    |   IF Expr LBRACE AuxStatement1 RBRACE AuxStatement2 {printf("Statement");}
    |   LBRACE AuxStatement1 RBRACE {printf("Statement");}
    ;

AuxStatement1: AuxStatement1 Statement SEMICOLON {printf("Aux");}
    |   {printf("Aux");}
    ;
AuxStatement2: ELSE LBRACE AuxStatement1 RBRACE {printf("Aux");}
    |   {printf("Aux");}
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR {printf("ParseArgs");}
    |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR {printf("errrrrrrs");}
    ;

FuncInvocation: ID LPAR error RPAR {printf("FuncInvocation");}
    |   ID LPAR RPAR {printf("FuncInvocation");}
    |   ID LPAR Expr AuxFuncInvocation RPAR {printf("FuncInvocation");}
    ;

AuxFuncInvocation: AuxFuncInvocation COMMA Expr {printf("Aux");}
    | {printf("Aux");}
    ;

Expr: ID {$$=$1;printf("Expr = ID!\n");}
    |   REALLIT {$$=$1;printf("Expr = REALLIT!\n");}
    |   INTLIT {$$=$1;printf("Expr = INTLIT!\n");}
    |   Expr AND Expr {$$=$1;printf("Expr = Expr AND expr!\n");}
    |   Expr PLUS Expr {$$=$1;printf("Expr = Expr PLUS expr!\n");}
    |   Expr LT Expr {$$=$1;printf("Expr = Expr LT expr!\n");}
    |   Expr MINUS Expr {$$=$1;printf("Expr = Expr MINUS expr!\n");}
    |   Expr GT Expr {$$=$1;printf("Expr = Expr GT expr!\n");}
    |   Expr NOT Expr {$$=$1;printf("Expr = Expr NOT expr!\n");}
    |   Expr MOD Expr {$$=$1;printf("Expr = Expr MOD expr!\n");}
    |   Expr DIV Expr {$$=$1;printf("Expr = Expr DIV expr!\n");}
    |   Expr GE Expr {$$=$1;printf("Expr = Expr GE expr!\n");}
    |   Expr STAR Expr {$$=$1;printf("Expr = Expr STAR expr!\n");}
    |   Expr EQ Expr {$$=$1;printf("Expr = Expr EQ expr!\n");}
    |   Expr NE Expr {$$=$1;printf("Expr = Expr NE expr!\n");}
    |   Expr LE Expr {$$=$1;printf("Expr = Expr LE expr!\n");}
    |   Expr OR Expr {$$=$1;printf("Expr = Expr OR expr!\n");}
    |   LPAR Expr RPAR {$$=$2;printf("Expr = LPAR Expr RPAR!\n");}
    |   FuncInvocation {printf("Aux");}
/*    |   LPAR error RPAR No enunciado está "Expression: LPAR error RPAR" será que foi engano? */
    ;



%%

int main() {
    yyparse();
    return 0;
}

void yyerror () {
    /*
    void yyerror (char *s)
    
    printf ("Line %d, column %d: %s: %s\n", <num linha >, <num coluna>, s, yytext);
    */
    
    printf ("BOOOOOOOOOOM! ESTOIROU, ERRO SINTÁTICO!\n");
}
