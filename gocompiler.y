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
    nodeDefault * adicionaIrmaoInicio(nodeDefault * atual,nodeDefault *novo);

%}
%union{
    char cval;
    int intval;
    char *string;
    double d;
    struct node *ponteiro;
}


%token <string> OR
%token <string> AND
%token <string> LT
%token <string> GT
%token <string> EQ
%token <string> NE
%token <string> LE
%token <string> GE
%token <string> PLUS
%token <string> MINUS
%token <string> STAR
%token <string> DIV
%token <string> MOD
%token <string> NOT
%token <string> INTLIT /*Vamos ter de mudar para número */
%token <string> REALLIT
%token <string> ID
%token <string> RESERVED
%token <string> LPAR
%token <string> RPAR
%token <string> SEMICOLON

%token <string> RSQ
%token <string> FOR
%token <string> CMDARGS
%token <string> BLANKID
%token <string> FUNC
%token <string> RBRACE
%token <string> LSQ
%token <string> ASSIGN
%token <string> IF
%token <string> RETURN
%token <string> LBRACE
%token <string> PARSEINT
%token <string> COMMA
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

%type <ponteiro> Program Declarations VarDeclaration VarSpec teste Type FuncDeclaration Parameters AuxParameters FuncBody VarsAndStatements Statement AuxStatement1 ParseArgs FuncInvocation AuxFuncInvocation Expr


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


Program: PACKAGE ID SEMICOLON Declarations {
    if($4!=NULL){
        $$=criaNoPai(Raiz,"Program");
        adicionaFilho2($$,$4);
        imprimeTralha($$,0);
    }
    else{
        $$=criaNoPai(Raiz,"Program");
        imprimeTralha($$,0);
    }
}
    ;

Declarations: Declarations VarDeclaration SEMICOLON {if($1!=NULL){
            $$=$1;
            adicionaIrmao2($$,$1);
        }
        else{
            $$=$2;
        }$$=$1;adicionaIrmao2($$,$1);}
    |   Declarations FuncDeclaration SEMICOLON {
        if($1!=NULL){
            $$=$1;
            adicionaIrmao2($$,$1);
        }
        else{
            $$=$2;
        }


}
    |    /* empty */ {$$=NULL;}
    ;

VarDeclaration: VAR VarSpec {$$=criaNoPai(DecVariaveis,"VarDecl");adicionaFilho2($$,$2);}
    |   VAR LPAR VarSpec SEMICOLON RPAR {$$=criaNoPai(DecVariaveis,"VarDecl");adicionaFilho2($$,$3);}
    ;

VarSpec: ID teste Type { 
    if($2!=NULL){
        $$=$2;
        adicionaIrmaoInicio($$,criaNoPai(Terminal,$1));
    }
    else{
        $$=criaNoPai(Terminal,$1);
    }
    };
    ;

teste: teste COMMA ID {
    if($1!=NULL){
        $$=$1;
        adicionaIrmao2($$,criaNoPai(Terminal,$3));
    }
    else{
        $$=criaNoPai(Terminal,$3);
    }
}
    |   /* empty */ {$$=NULL;}
    ;

Type:   INT {$$=criaNoPai(Terminal,$1);}
    |   BOOL   {$$=criaNoPai(Terminal,$1);}
    |   STRING {$$=criaNoPai(Terminal,$1);}
    |   FLOAT32   {$$=criaNoPai(Terminal,$1);}
    ;

FuncDeclaration: FUNC ID LPAR RPAR FuncBody {
    nodeDefault *aux,*aux2,*aux3; 
    $$=criaNoPai(DecFuncoes,"FuncDecl");
    aux=criaNoPai(DecFuncoes,"FuncHeader");
    adicionaFilho2($$,aux);
    aux2=criaNoPai(Terminal,$2);
    adicionaFilho2(aux,aux2);
    aux3=criaNoPai(DecFuncoes,"FuncParams");
    adicionaIrmao2(aux->filho,aux3);
    adicionaIrmao2($$->filho,$5);
}
    |   FUNC ID LPAR Parameters RPAR FuncBody {
        nodeDefault *aux,*aux2,*aux3; 
        $$=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2($$,aux);
        aux2=criaNoPai(Terminal,$2);
        adicionaFilho2(aux,aux2);
        adicionaIrmao2(aux->filho,$4);
        adicionaIrmao2($$->filho,$6);
    }
    |   FUNC ID LPAR Parameters RPAR Type FuncBody {
        nodeDefault *aux,*aux2,*aux3,*aux4; 
        $$=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2($$,aux);
        aux2=criaNoPai(Terminal,$2);
        adicionaFilho2(aux,aux2);
        adicionaIrmao2(aux->filho,$4);

        adicionaIrmao2(aux->filho,$6);
        adicionaIrmao2($$->filho,$7);
    }
    ;
Parameters: ID Type AuxParameters {
    if ($3!=NULL){
        adicionaIrmaoInicio(criaNoPai(Terminal,$1),$3);
    }
    else{
        $$=criaNoPai(Terminal,$1);
    }
    }
    ;

AuxParameters: AuxParameters COMMA ID Type {
    if($1!=NULL){
        $$=$1;
        adicionaIrmao2($1,criaNoPai(Terminal,$3));
    }
    else{
        $$=criaNoPai(Terminal,$3);
    }
}
    |   /* empty */ {$$=NULL;}
    ;

FuncBody: LBRACE VarsAndStatements RBRACE {
    if($2!=NULL){

        $$=criaNoPai(DecFuncoes,"FuncBody");
        adicionaFilho2($$,$2);
    }
    else{
        $$=criaNoPai(DecFuncoes,"FuncBody");
    }
}
        ;

VarsAndStatements: VarsAndStatements SEMICOLON {
    if ($1!=NULL){
        $$=$1;
    } 
    else{
        $$=NULL;
    }
}
    |   VarsAndStatements VarDeclaration SEMICOLON {
        if($1!=NULL){
            $$=$1;
            adicionaIrmao2($1,$2);
        }
        else{
            $$=$2;
        }
    }
    |   VarsAndStatements Statement SEMICOLON {
        if($1!=NULL){
            $$=$1;
            adicionaIrmao2($1,$2);
        }
        else{
            $$=$2;
        }
    }
    |   /* empty */ {$$=NULL;}
    ;

Statement: PRINT LPAR Expr RPAR {$$=criaNoPai(Statements,$1);adicionaFilho2($$,$3);}
    |   PRINT LPAR STRLIT RPAR {$$=criaNoPai(Statements,$1);adicionaFilho2($$,criaNoPai(Terminal,$3));}
    |   error {$$=NULL;}
    |   FuncInvocation {$$=$1;}
    |   ParseArgs {$$=$1;}
    |   RETURN {$$=criaNoPai(Statements,$1);}
    |   RETURN Expr {$$=criaNoPai(Statements,$1);adicionaFilho2($$,$2);}
    |   FOR Expr LBRACE AuxStatement1 RBRACE {

        if($4!=NULL){
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$4);
            adicionaIrmao2($$->filho,aux);
        }
        else{
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux);
        }

    }
    |   FOR LBRACE AuxStatement1 RBRACE {
        if($3!=NULL){
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$3);
            adicionaFilho2($$,aux);
        }
        else{
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2($$,aux);  
        }
    }
    |   ID ASSIGN Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,criaNoPai(Terminal,$1));adicionaIrmao2($$->filho,$3);}
    |   IF Expr LBRACE AuxStatement1 RBRACE{
        if($4!=NULL){
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$4);
            adicionaIrmao2($$->filho,aux);
            adicionaIrmao2($$->filho,criaNoPai(Statements,"Block"));
        }
        else{
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux);
            adicionaIrmao2($$->filho,criaNoPai(Statements,"Block"));
        }
    }
    |   IF Expr LBRACE AuxStatement1 RBRACE ELSE LBRACE AuxStatement1 RBRACE {
        if($4!=NULL){
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$4);
            adicionaIrmao2($$->filho,aux);
            adicionaIrmao2($$->filho,criaNoPai(Statements,"Block"));
        }
        else{
            nodeDefault *aux;
            $$=criaNoPai(Statements,$1);
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux);
            adicionaIrmao2($$->filho,criaNoPai(Statements,"Block"));
        }

    }
    |   LBRACE AuxStatement1 RBRACE { /* Dúvida */
        if($2!=NULL){
            $$=$2;
        }
        else{

        }
    }
    ;

AuxStatement1: AuxStatement1 Statement SEMICOLON {
    if($1!=NULL){
        $$=adicionaIrmao2($1,$2);
    }
    else{
        $$=$2;
    }
}
    |   /* empty */ {$$=NULL;}
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR {
    $$=criaNoPai(Statements,"ParseArgs");
    adicionaFilho2($$,criaNoPai(Terminal,$1));
    adicionaIrmao2($$->filho,$9);
}
    |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR {$$=NULL;}
    ;

FuncInvocation: ID LPAR error RPAR {$$=NULL;}
    |   ID LPAR RPAR {$$=criaNoPai(Statements,"Call");adicionaFilho2($$,criaNoPai(Terminal,$1));} /* Não sabemos o Type a pôr aqui */ 
    |   ID LPAR Expr AuxFuncInvocation RPAR {
        if($4!=NULL){
            $$=criaNoPai(Statements,"Call");
            adicionaFilho2($$,criaNoPai(Terminal,$1));
            adicionaIrmao2($$->filho,$3);adicionaIrmao2($$->filho,$4);
    }
    else{
        nodeDefault *aux;
        aux=criaNoPai(Terminal,$1);
        $$=criaNoPai(Statements,"Call");
        adicionaIrmao2(aux,$3);
        adicionaFilho2($$,aux);
    }
    }
    ;


AuxFuncInvocation: AuxFuncInvocation COMMA Expr {if($1!=NULL){$$=adicionaIrmao2($1,$3);}else{$$=$3;}}
    | /* empty */ {$$=NULL;}
    ;

Expr: Expr OR Expr 
    |   ID {$$=criaNoPai(Terminal,$1);}
    |   REALLIT {$$=criaNoPai(Terminal,$1);}
    |   INTLIT {$$=criaNoPai(Terminal,$1);}
    |   Expr AND Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr PLUS Expr  {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr LT Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr MINUS Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr GT Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr MOD Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr DIV Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr GE Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr STAR Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr EQ Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr NE Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr LE Expr {$$=criaNoPai(Operadores,$2);adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   LPAR Expr RPAR {$$=$2;}
    |   MINUS Expr %prec STAR {$$=criaNoPai(Operadores,$1);adicionaFilho2($$,$2);}
    |   PLUS Expr %prec STAR {$$=criaNoPai(Operadores,$1);adicionaFilho2($$,$2);}
    |   NOT Expr %prec STAR {$$=criaNoPai(Operadores,$1);adicionaFilho2($$,$2);}
    |   FuncInvocation {$$=$1;}
    |   LPAR error RPAR {$$=NULL;}
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
nodeDefault * adicionaIrmaoInicio(nodeDefault * atual,nodeDefault *novo){
    //Temos de adicionar no inicio
    novo->irmao=atual;
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
            flagArvore=1;
        }
    }
    yyparse();
    return 0;
}