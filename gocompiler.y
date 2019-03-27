%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define YYDEBUG 1
    extern int yydebug;
    extern int numcolunas;
    extern int yylineno;
    extern int flagString;
    extern char s[500];
    extern char* yytext;
    int yylex(void);
    void yyerror (char *st);
    int flagLex=0;
    int flagArvore=0;
    typedef enum { Terminal, Operadores, Statements, DecFuncoes, DecVariaveis, Raiz} nodeType;
    typedef struct node{
        char *string;
        nodeType tipo;
        struct node **ponteiros;
        int nrFilhos;
    }nodeDefault;
    nodeDefault * criaNo(nodeType tipo, char* str, int nrNosfilhos, nodeDefault** arrayPonteiros);
    int imprimeTralha(nodeDefault *raiz,int depth);
    int limpaTralha(nodeDefault *raiz);

%}
%union{
    char cval;
    int intval;
    char *string;
    double d;
    nodeDefault *ponteiro;
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
%token <string> RESERVED
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


/*
vai ser preciso quase de certeza



%type <ponteiro> Program Declarations VarDeclaration VarSpec teste Type FuncDeclaration Parameters AuxParameters FuncBody VarsAndStatements Statement AuxStatement1 AuxStatement2 ParseArgs FuncInvocation AuxFuncInvocation Expr
*/
%type <ponteiro> Expr


/* Se usarmos dois lefts, ou rights, o de baixo tem prioridade sobre o de cima */
/* Estávamos a usar estes 
%left OR
%left AND
%left EQ NE
%nonassoc GE GT LE LT 
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
%left LPAR RPAR

*/
%left COMMA
%right ASSIGN
%left OR
%left AND
%left EQ NE 
%left GE GT LE LT 
%left PLUS MINUS
%left STAR DIV MOD
%left NOT
%left LPAR RPAR LBRACE RBRACE


%%


/*
inicio: inicio Expr
        | 
        ;
*/
Program: PACKAGE ID SEMICOLON Declarations /*{printf("Program\n");} imprimir a árvore aqui*/
    ;



Declarations: Declarations VarDeclaration SEMICOLON /*{printf("Declarations\n");} */
    |   Declarations FuncDeclaration SEMICOLON /*{printf("Declarations\n");} */
    |    /* empty */
    ;

VarDeclaration: VAR VarSpec /*{printf("VarDeclaration\n");} */
    |   VAR LPAR VarSpec SEMICOLON RPAR /*{printf("VarDeclaration\n");}*/
    ;

VarSpec: ID teste Type /*{printf("Varspec\n");}*/
    ;

teste: teste COMMA ID 
    |   /* empty */
    ;

Type:   INT /*{printf("Type---->Int\n");}*/
    |   BOOL   /*{printf("Type---->BOOL\n");}*/
    |   STRING /*{printf("Type---->STRING\n");}*/
    |   FLOAT32   /* {printf("Type---->FLOAT32\n");} */
    ;

FuncDeclaration: FUNC ID LPAR RPAR FuncBody /*{printf("FuncDeclaration\n");} */
    |   FUNC ID LPAR Parameters RPAR FuncBody /*{printf("FuncDeclaration\n");} */
    |   FUNC ID LPAR RPAR Type FuncBody /*{printf("FuncDeclaration\n");} */
    |   FUNC ID LPAR Parameters RPAR Type FuncBody /*{printf("FuncDeclaration\n");} */
    ;

Parameters: ID Type AuxParameters /*{printf("Parameters\n");} */
    ;

AuxParameters: AuxParameters COMMA ID Type 
    |   /* empty */
    ;

FuncBody: LBRACE VarsAndStatements RBRACE /*{printf("FuncBody\n");} */
        ;

VarsAndStatements: VarsAndStatements SEMICOLON /*{printf("VarsAndStatements\n");} */
    |   VarsAndStatements VarDeclaration SEMICOLON /*{printf("VarsAndStatements\n");}*/
    |   VarsAndStatements Statement SEMICOLON /*{printf("VarsAndStatements\n");}*/
    |   /* empty */
    ;

Statement: PRINT LPAR Expr RPAR /*{printf("Statement\n");}*/
    |   PRINT LPAR STRLIT RPAR /*{printf("Statement\n");}*/
    |   error /*{printf("errorrrrrr");}*/
    |   FuncInvocation /*{printf("Statement\n");}*/
    |   ParseArgs /*{printf("Statement\n");}*/
    |   RETURN /*{printf("Statement\n");}*/
    |   RETURN Expr /*{printf("Statement\n");}*/
    |   FOR Expr LBRACE AuxStatement1 RBRACE /*{printf("Statement\n");}*/
    |   FOR LBRACE AuxStatement1 RBRACE /*{printf("Statement\n");}*/
    |   ID ASSIGN Expr /*{printf("Statement\n");}*/
    |   IF Expr LBRACE AuxStatement1 RBRACE AuxStatement2 /*{printf("Statement\n");}*/
    |   LBRACE AuxStatement1 RBRACE /*{printf("Statement\n");}*/
    ;

AuxStatement1: AuxStatement1 Statement SEMICOLON
    |   /* empty */
    ;
AuxStatement2: ELSE LBRACE AuxStatement1 RBRACE 
    |   /* empty */
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR /*{printf("ParseArgs\n");}*/
    |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR /*{printf("errrrrrrs");}*/
    ;

FuncInvocation: ID LPAR error RPAR /*{printf("FuncInvocation\n");}*/
    |   ID LPAR RPAR /*{printf("FuncInvocation\n");}*/
    |   ID LPAR Expr AuxFuncInvocation RPAR /*{printf("FuncInvocation\n");}*/
    ;

AuxFuncInvocation: AuxFuncInvocation COMMA Expr
    | /* empty */
    ;

Expr: ID {$$ = criaNo(Terminal, $1, 0, NULL);}
    |   REALLIT {$$ = criaNo(Terminal, $1, 0, NULL);}/*{printf("Expr = REALLIT!\n");}*/
    |   INTLIT {$$ = criaNo(Terminal, $1, 0, NULL);}/*{printf("Expr = INTLIT!\n");}*/
    |   Expr AND Expr {$$ = criaNo(Operadores, $2, 2, NULL);}/*{printf("Expr = Expr AND expr!\n");}*/
    |   Expr PLUS Expr /*{printf("Expr = Expr PLUS expr!\n");}*/
    |   Expr LT Expr /*{printf("Expr = Expr LT expr!\n");}*/
    |   Expr MINUS Expr /*{printf("Expr = Expr MINUS expr!\n");}*/
    |   Expr GT Expr /*{printf("Expr = Expr GT expr!\n");}*/
    |   Expr NOT Expr /*{printf("Expr = Expr NOT expr!\n");}*/
    |   Expr MOD Expr /*{printf("Expr = Expr MOD expr!\n");}*/
    |   Expr DIV Expr /*{printf("Expr = Expr DIV expr!\n");}*/
    |   Expr GE Expr /*{printf("Expr = Expr GE expr!\n");}*/
    |   Expr STAR Expr /*{printf("Expr = Expr STAR expr!\n");}*/
    |   Expr EQ Expr /*{printf("Expr = Expr EQ expr!\n");}*/
    |   Expr NE Expr /*{printf("Expr = Expr NE expr!\n");}*/
    |   Expr LE Expr /*{printf("Expr = Expr LE expr!\n");}*/
    |   Expr OR Expr /*{printf("Expr = Expr OR expr!\n");}*/
    |   LPAR Expr RPAR /*{printf("Expr = LPAR Expr RPAR!\n");}*/
    |   MINUS Expr  /*{printf("Expr = MINUS Expr!\n");}*/
    |   PLUS Expr/*{printf("Expr = PLUS Expr!\n");}*/
    |   NOT Expr /*{printf("Expr = NOT Expr!\n");}*/
    |   FuncInvocation /*{printf("FuncInvocation\n");}*/
    |   LPAR error RPAR /*{printf("error\n");}*/
    ;



%%



void yyerror (char *st) {

    if(flagString==0){

        printf ("Line %d, column %d: %s: %s\n", yylineno, numcolunas-(int)strlen(yytext), st, yytext);

    }
    else{

        printf ("Line %d, column %d: %s: \"%s\"\n", yylineno, numcolunas-(int)strlen(s), st, s);
        flagString=0;
    }

}

nodeDefault * criaNo(nodeType tipo, char* str, int nrNosfilhos, nodeDefault** arrayPonteiros){
    nodeDefault *ponteiro;
    int i;
    // Reservar espaço para o nó
    if ((ponteiro=malloc(sizeof(nodeDefault)))== NULL)
        printf("Estoirou!\n");
    ponteiro->tipo=tipo;
    ponteiro->string=str;
    ponteiro->nrFilhos=nrNosfilhos;
    
    // Vai reservar espaço para os filhos do nó criado
     if(nrNosfilhos>0){
         if ((ponteiro->ponteiros=malloc(nrNosfilhos*sizeof(nodeDefault)))==NULL)
            printf("BOOM SHAKA LAKA!\n");
         for(i=0;i<nrNosfilhos;i++){
             ponteiro->ponteiros[i]=arrayPonteiros[i];
         }
     }
    return ponteiro;
    
}
int imprimeTralha(nodeDefault *raiz,int depth){
    int iterador;
    int i;
    for(i=0;i<depth;i++){
        printf("..");
    }
    printf("%s\n",raiz->string);
    if (raiz->tipo==Terminal){
        return 0;
    }
    for (iterador=0;iterador<raiz->nrFilhos;iterador++){
        imprimeTralha(raiz->ponteiros[iterador],depth+1);
    }
    return 0;

}
int limpaTralha(nodeDefault *raiz){
    int iterador;
    if (raiz->tipo==Terminal){
        free(raiz);
        return 0;
    }
    
    
    for (iterador=0;iterador<raiz->nrFilhos;iterador++){
        limpaTralha(raiz->ponteiros[iterador]);
    }
    free(raiz->ponteiros);
    free(raiz);

    return 0;
    
}

int main(int argc, char **argv) {
    /*
    yydebug=1;
    */
    /* Se a flag -l for passada, deve pôr a flag a 1 para o lex fazer a análise lexical */
    if(argc>1){
        if (strcmp(argv[1],"-l")==0){
            flagLex=1;
        }
        if (strcmp(argv[1],"-t")==0){
            flagArvore=0;
        }
    }
    yyparse();
    return 0;
}
