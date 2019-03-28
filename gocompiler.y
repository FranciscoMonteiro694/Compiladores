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
    typedef struct node *lista;
    typedef struct node{
        char *string;
        nodeType tipo;
        lista filho;
        lista irmao;
    }nodeDefault;
    int imprimeTralha(nodeDefault *raiz,int depth);
    int limpaTralha(nodeDefault *raiz);
    nodeDefault * criaNoPai(nodeType tipo, char *str);
    nodeDefault * adicionaFilho(nodeDefault * pai,nodeType tipo, char *str);
    nodeDefault * adicionaIrmao(nodeDefault * atual,nodeType tipo, char *str);
    int imprimeTralha(nodeDefault *raiz,int depth);
    nodeDefault * adicionaIrmao2(nodeDefault * atual,nodeDefault *novo);
    nodeDefault * adicionaFilho2(nodeDefault * pai,nodeDefault *novo);

%}
%union{
    char cval;
    int intval;
    char *string;
    double d;
    struct node *ponteiro;
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

%type <ponteiro> Expr FuncInvocation AuxFuncInvocation

/* Se usarmos dois lefts, ou rights, o de baixo tem prioridade sobre o de cima */


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

Statement: PRINT LPAR Expr RPAR {}
    |   PRINT LPAR STRLIT RPAR 
    |   error 
    |   FuncInvocation 
    |   ParseArgs 
    |   RETURN 
    |   RETURN Expr 
    |   FOR Expr LBRACE AuxStatement1 RBRACE 
    |   FOR LBRACE AuxStatement1 RBRACE 
    |   ID ASSIGN Expr 
    |   IF Expr LBRACE AuxStatement1 RBRACE AuxStatement2 
    |   LBRACE AuxStatement1 RBRACE 
    ;

AuxStatement1: AuxStatement1 Statement SEMICOLON
    |   /* empty */
    ;
AuxStatement2: ELSE LBRACE AuxStatement1 RBRACE 
    |   /* empty */
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR {$$=criaNoPai(Statements,"ParseArgs");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$9);}
    |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR 
    ;

FuncInvocation: ID LPAR error RPAR 
    |   ID LPAR RPAR {$$=criaNoPai(Statements,"Call");adicionaFilho2($$,criaNoPai(Terminal,$1));} /* Não sabemos o Type a pôr aqui */ 
    |   ID LPAR Expr AuxFuncInvocation RPAR {$$=criaNoPai(Statements,"Call");adicionaFilho2($$,criaNoPai(Terminal,$1));adicionaIrmao2($$->filho,$3);adicionaIrmao2($$->filho,$4);}
    ;


AuxFuncInvocation: AuxFuncInvocation COMMA Expr {if($$!=NULL){$$=adicionaIrmao2($1,$3);}else{$$=$3;}}
    | /* empty */ {$$=NULL;}
    ;

Expr: Expr OR Expr 
    |   ID {$$=criaNoPai(Terminal,$1);}
    |   REALLIT {$$=criaNoPai(Terminal,$1);}
    |   INTLIT {$$=criaNoPai(Terminal,$1);}
    |   Expr AND Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr PLUS Expr  {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr LT Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr MINUS Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr GT Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr MOD Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr DIV Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr GE Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr STAR Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr EQ Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr NE Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   Expr LE Expr {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   LPAR Expr RPAR {$$=criaNoPai(Operador,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3)}
    |   MINUS Expr %prec STAR {$$=criaNoPai(Operador,$1);adicionaFilho2($$,$2);}
    |   PLUS Expr %prec STAR {$$=criaNoPai(Operador,$1);adicionaFilho2($$,$2);}
    |   NOT Expr %prec STAR {$$=criaNoPai(Operador,$1);adicionaFilho2($$,$2);}
    |   FuncInvocation {$$=$1;}
    |   LPAR error RPAR /*{printf("error\n");}*/
    ;



%%



void yyerror (char *st) {

    if(flagString==0){

        printf ("Line %d, column %d: %s: %s\n", yylineno, numcolunas-(int)strlen(yytext), st, yytext);

    }
    else{

        printf ("Line %d, column %d: %s: \"%s\"\n", yylineno, numcolunas-(int)strlen(s)-2, st, s);
        flagString=0;
    }

}

nodeDefault * criaNoPai(nodeType tipo, char *str){
    nodeDefault *ponteiro;
    if ((ponteiro=malloc(sizeof(nodeDefault)))== NULL)
        printf("Estoirou!\n");
    ponteiro->filho=NULL;
    ponteiro->irmao=NULL;
    ponteiro->string=str;
    ponteiro->tipo=tipo;
    return ponteiro;
}
nodeDefault * adicionaFilho(nodeDefault * pai,nodeType tipo, char *str){
    nodeDefault *novo;
    novo=criaNoPai(tipo, str);
    pai->filho=novo;
    return novo;
}

nodeDefault * adicionaIrmao(nodeDefault * atual,nodeType tipo, char *str){
    //Temos de adicionar no mais à direita
    nodeDefault *novo;
    nodeDefault *iterador;
    iterador=atual;
    while(iterador->irmao!=NULL){
        iterador=iterador->irmao;
    }
    novo=criaNoPai(tipo, str);
    iterador->irmao=novo;
    return novo;
}


int imprimeTralha(nodeDefault *raiz,int depth){
    nodeDefault *iterador;
    int i;
    for(i=0;i<depth;i++){
        printf("..");
    }
    printf("%s\n",raiz->string);
    if(raiz->filho!=NULL){
    imprimeTralha(raiz->filho,depth+1);
        iterador=raiz->filho->irmao;
        while(iterador!=NULL){
            imprimeTralha(iterador,depth+1);
            iterador=iterador->irmao;
        }
    }
   
    return 0;

}
nodeDefault * adicionaIrmao2(nodeDefault * atual,nodeDefault *novo){
    //Temos de adicionar no mais à direita
    nodeDefault *iterador;
    iterador=atual;
    while(iterador->irmao!=NULL){
        iterador=iterador->irmao;
    }
    iterador->irmao=novo;
    return novo;
}
nodeDefault * adicionaFilho2(nodeDefault * pai,nodeDefault *novo){
    pai->filho=novo;
    return novo;
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