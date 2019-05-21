%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tabelas.h"
    #define YYDEBUG 1
    extern int yydebug;
    extern int numcolunas;
    extern int yylineno;
    extern int yyleng;
    extern int flagString;
    extern char s[500];
    extern char* yytext;
    int yylex(void);
    void yyerror (char *st);
    int flagLex=0;
    int flagArvore=0;
    int flagErro=0;
    int flagSemantica=0;
    /* Inicializa tabela de símbolos global */
    elemento_tabelag *tg = NULL;

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

%token IFELSE
/*
vai ser preciso quase de certeza



%type <ponteiro> Program Declarations VarDeclaration VarSpec teste Type FuncDeclaration Parameters AuxParameters FuncBody VarsAndStatements Statement AuxStatement1 AuxStatement2 ParseArgs FuncInvocation AuxFuncInvocation Expr
*/

%type <ponteiro> Program Declarations VarDeclaration VarSpec teste Type FuncDeclaration Parameters AuxParameters FuncBody VarsAndStatements Statement AuxStatement1 ParseArgs FuncInvocation AuxFuncInvocation Expr




%left COMMA
%right ASSIGN
%left OR
%left AND 
%left GE GT LE LT EQ NE
%left PLUS MINUS
%left STAR DIV MOD
%left NOT
%left LPAR RPAR LBRACE RBRACE
%nonassoc IFELSE


%%


Program: PACKAGE ID SEMICOLON Declarations {
    if($4!=NULL){
        $$=criaNoPai(Raiz,"Program");
        adicionaFilho2($$,$4);
    if(flagErro!=1&&flagArvore!=0){
    
        imprimeTralha($$,0);


    }
        
    }
    else{
        $$=criaNoPai(Raiz,"Program");
    if(flagErro!=1&&flagArvore!=0){
    
        imprimeTralha($$,0);

    }
        
    }
    criaTabelas($$);
    //anota
    if(flagSemantica==1){
        imprime_tabelaGlobal();
       // imprimeTralha($$,0);
        //teste1($$);
        imprimeASTanotada($$,0,0);
    }
    
}
    ;

Declarations: Declarations VarDeclaration SEMICOLON {
        if($1!=NULL){
            $$=$1;
            adicionaIrmao2($$,$2);
        }
        else{
            $$=$2;
        }

        }
    |   Declarations FuncDeclaration SEMICOLON {

        if($1!=NULL){
            $$=$1;
            adicionaIrmao2($$,$2);
        }
        else{
            $$=$2;
        }


}
    |    /* empty */ {$$=NULL;}
    ;

VarDeclaration: VAR VarSpec {
        $$=$2;
}
    |   VAR LPAR VarSpec SEMICOLON RPAR {
        $$=$3;
    }
    ;

VarSpec: ID teste Type { 
    if($2!=NULL){
        $$=adicionaIrmaoInicio($2,criaNoPai(Terminal,juntaStrings("Id(",$1,")")));
        $$=juntarCenas($$,$3->string);
        

    }
    else{
        $$=criaNoPai(DecVariaveis,"VarDecl");
        adicionaFilho2($$,$3);
       adicionaIrmao2($$->filho,criaNoPai(Terminal,juntaStrings("Id(",$1,")")));
    }
    };
    ;

teste: teste COMMA ID {
    if($1!=NULL){
        $$=$1;
        adicionaIrmao2($$,criaNoPai(Terminal,juntaStrings("Id(",$3,")")));
    }
    else{
          $$=criaNoPai(Terminal,juntaStrings("Id(",$3,")"));
    }
}
    |   /* empty */ {$$=NULL;}
    ;

Type:   INT {$$=criaNoPai(Terminal,"Int");}
    |   BOOL   {$$=criaNoPai(Terminal,"Bool");}
    |   STRING {$$=criaNoPai(Terminal,"String");}
    |   FLOAT32   {$$=criaNoPai(Terminal,"Float32");}
    ;

FuncDeclaration: FUNC ID LPAR RPAR FuncBody {
    nodeDefault *aux,*aux2,*aux3; 
    $$=criaNoPai(DecFuncoes,"FuncDecl");
    aux=criaNoPai(DecFuncoes,"FuncHeader");
    adicionaFilho2($$,aux);
     aux2=criaNoPai(Terminal,juntaStrings("Id(",$2,")"));
    adicionaFilho2(aux,aux2);
    aux3=criaNoPai(DecFuncoes,"FuncParams");
    adicionaIrmao2(aux->filho,aux3);
    adicionaIrmao2($$->filho,$5);

    //elemento_tabelag* newel=insert_el($2, none);
}
    |   FUNC ID LPAR Parameters RPAR FuncBody {
        nodeDefault *aux,*aux2; 
        $$=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2($$,aux);
        aux2=criaNoPai(Terminal,juntaStrings("Id(",$2,")"));
        adicionaFilho2(aux,aux2);
        adicionaIrmao2(aux->filho,$4);
        adicionaIrmao2($$->filho,$6);

        //elemento_tabelag* newel=insert_el($2, none);
        //insertTipos($2, $4);
    }
    |   FUNC ID LPAR Parameters RPAR Type FuncBody {
        nodeDefault *aux,*aux2; 
        $$=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2($$,aux);
        aux2=criaNoPai(Terminal,juntaStrings("Id(",$2,")"));
        adicionaFilho2(aux,aux2);
        adicionaIrmao2(aux->filho,$6);
        adicionaIrmao2(aux->filho,$4);
        adicionaIrmao2($$->filho,$7);

        //elemento_tabelag* newel=insert_elNode($2, $6);

        //insertTipos($2, $4);

        
    }
    |   FUNC ID LPAR  RPAR Type FuncBody {
        nodeDefault *aux,*aux2; 
        $$=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2($$,aux);
        aux2=criaNoPai(Terminal,juntaStrings("Id(",$2,")"));
        adicionaFilho2(aux,aux2);
    
        adicionaIrmao2(aux->filho,$5);//dar double checkkkkk
    
        adicionaIrmao2($$->filho,$6);
    adicionaIrmao2(aux->filho,criaNoPai(DecFuncoes,"FuncParams"));
        //elemento_tabelag* newel=insert_elNode($2, $6);

        //insertTipos($2, $4);

        
    }
    ;
Parameters: ID Type AuxParameters {
    if ($3!=NULL){
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai(Terminal,juntaStrings("Id(",$1,")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,$2);
        adicionaIrmao2(aux2->filho,aux1);
        adicionaIrmaoInicio($3,aux2);
        $$=criaNoPai(DecFuncoes,"FuncParams");
        adicionaFilho2($$,aux2);



    }
    else{
        nodeDefault *aux1,*aux2;
         aux1=criaNoPai(Terminal,juntaStrings("Id(",$1,")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,$2);
        adicionaIrmao2(aux2->filho,aux1);
        $$=criaNoPai(DecFuncoes,"FuncParams");
        adicionaFilho2($$,aux2);
    }
    }
    ;

AuxParameters: AuxParameters COMMA ID Type {
    if($1!=NULL){
        $$=$1;
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai(Terminal,juntaStrings("Id(",$3,")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,$4);
        adicionaIrmao2(aux2->filho,aux1);
        adicionaIrmao2($$,aux2);
    }
    else{
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai(Terminal,juntaStrings("Id(",$3,")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,$4);
        adicionaIrmao2(aux2->filho,aux1);
        $$=aux2;
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

Statement: PRINT LPAR Expr RPAR {$$=criaNoPai(Statements,"Print");adicionaFilho2($$,$3);}
    |   PRINT LPAR STRLIT RPAR {$$=criaNoPai(Statements,"Print");adicionaFilho2($$,criaNoPai(Terminal,juntaStrings("StrLit(\"",$3,"\")")));}
    |   error {$$=NULL;}
    |   FuncInvocation {$$=$1;}
    |   ParseArgs {$$=$1;}
    |   RETURN {$$=criaNoPai(Statements,"Return");}
    |   RETURN Expr {$$=criaNoPai(Statements,"Return");adicionaFilho2($$,$2);}
    |   FOR Expr LBRACE AuxStatement1 RBRACE {

        if($4!=NULL){
            nodeDefault *aux;
            $$=criaNoPai(Statements,"For");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$4);
            adicionaIrmao2($$->filho,aux);
        }
        else{
            nodeDefault *aux;
            $$=criaNoPai(Statements,"For");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux);
        }

    }
    |   FOR LBRACE AuxStatement1 RBRACE {
        if($3!=NULL){
            nodeDefault *aux;
            $$=criaNoPai(Statements,"For");
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$3);
            adicionaFilho2($$,aux);
        }
        else{
            nodeDefault *aux;
            $$=criaNoPai(Statements,"For");
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2($$,aux);  
        }
    }
    |   ID ASSIGN Expr {
            $$=criaNoPai(Operadores,"Assign");
            adicionaFilho2($$,criaNoPai(Terminal,juntaStrings("Id(",$1,")")));
            adicionaIrmao2($$->filho,$3);
}
    |   IF Expr LBRACE AuxStatement1 RBRACE {
        if($4!=NULL){
            nodeDefault *aux;
            $$=criaNoPai(Statements,"If");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$4);
            adicionaIrmao2($$->filho,aux);
            adicionaIrmao2($$->filho,criaNoPai(Statements,"Block"));
        }
        else{
            nodeDefault *aux;
            $$=criaNoPai(Statements,"If");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux);
            adicionaIrmao2($$->filho,criaNoPai(Statements,"Block"));
        }
    }
    |   IF Expr LBRACE AuxStatement1 RBRACE ELSE LBRACE AuxStatement1 RBRACE %prec IFELSE{
        //NENHUM NULL
        if($4!=NULL && $8!=NULL){
            nodeDefault *aux,*aux2;
            $$=criaNoPai(Statements,"If");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$4);
            adicionaIrmao2($$->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux2);
            adicionaFilho2(aux2,$8);
        }
        // $4 NULL E $8 NÃO NULL
        if($4==NULL && $8!=NULL){
            nodeDefault *aux,*aux2;
            $$=criaNoPai(Statements,"If");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux2);
            adicionaFilho2(aux2,$8);
        }
        // $4 NÃO NULL E $8 NULL
        if($4!=NULL && $8==NULL){
            nodeDefault *aux,*aux2;
            $$=criaNoPai(Statements,"If");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,$4);
            adicionaIrmao2($$->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux2);
        }
        // $4 NULL E $8 NULL
        if($4==NULL && $8==NULL){
            nodeDefault *aux,*aux2;
            $$=criaNoPai(Statements,"If");
            adicionaFilho2($$,$2);
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2($$->filho,aux2);
        }

    }
    |   LBRACE AuxStatement1 RBRACE { /* Dúvida */
        if($2!=NULL){
            if(contaIrmao($2)>1){ // Se for maior ou igual a 2 cria Block
                $$=criaNoPai(Statements,"Block");
                adicionaFilho2($$,$2);

            }
            else{ // Caso contrário não cria, mas não é preciso adicionar também?
                $$=$2;
            }
        }
        else{
            $$=NULL;
        }
    }
    ;

AuxStatement1: AuxStatement1 Statement SEMICOLON {
    if($1!=NULL){
        $$=adicionaIrmao2($1,$2);// vai receber o irmao à esquerda do novo
    }
    else{
        $$=$2;
    }
}
    |   /* empty */ {$$=NULL;}
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR {
    $$=criaNoPai(Statements,"ParseArgs");
    adicionaFilho2($$,criaNoPai(Terminal,juntaStrings("Id(",$1,")")));
    adicionaIrmao2($$->filho,$9);
}
    |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR {$$=NULL;}
    ;

FuncInvocation: ID LPAR error RPAR {$$=NULL;}
    |   ID LPAR RPAR {$$=criaNoPai(Statements,"Call");adicionaFilho2($$,criaNoPai(Terminal,juntaStrings("Id(",$1,")")));} /* Não sabemos o Type a pôr aqui */ 
    |   ID LPAR Expr AuxFuncInvocation RPAR {
        if($4!=NULL){
            $$=criaNoPai(Statements,"Call");
            adicionaFilho2($$,criaNoPai(Terminal,juntaStrings("Id(",$1,")")));
        adicionaIrmao2($3,$4);
            adicionaIrmao2($$->filho,$3);
    }
    else{
        nodeDefault *aux;
        aux=criaNoPai(Terminal,juntaStrings("Id(",$1,")"));
        $$=criaNoPai(Statements,"Call");
        adicionaIrmao2(aux,$3);
        adicionaFilho2($$,aux);
    }
    }
    ;


AuxFuncInvocation: AuxFuncInvocation COMMA Expr {if($1!=NULL){$$=$1;adicionaIrmao2($1,$3);}else{$$=$3;}}
    | /* empty */ {$$=NULL;}
    ;

Expr: Expr OR Expr {$$=criaNoPai(Operadores,"Or");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   ID {$$=criaNoPai(Terminal,juntaStrings("Id(",$1,")"));}
    |   REALLIT {$$=criaNoPai(Terminal,juntaStrings("RealLit(",$1,")"));}
    |   INTLIT {$$=criaNoPai(Terminal,juntaStrings("IntLit(",$1,")"));}
    |   Expr AND Expr {$$=criaNoPai(Operadores,"And");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr PLUS Expr  {$$=criaNoPai(Operadores,"Add");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr LT Expr {$$=criaNoPai(Operadores,"Lt");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr MINUS Expr {$$=criaNoPai(Operadores,"Sub");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr GT Expr {$$=criaNoPai(Operadores,"Gt");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr MOD Expr {$$=criaNoPai(Operadores,"Mod");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr DIV Expr {$$=criaNoPai(Operadores,"Div");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr GE Expr {$$=criaNoPai(Operadores,"Ge");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr STAR Expr {$$=criaNoPai(Operadores,"Mul");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr EQ Expr {$$=criaNoPai(Operadores,"Eq");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr NE Expr {$$=criaNoPai(Operadores,"Ne");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   Expr LE Expr {$$=criaNoPai(Operadores,"Le");adicionaFilho2($$,$1);adicionaIrmao2($$->filho,$3);}
    |   LPAR Expr RPAR {$$=$2;}
    |   MINUS Expr %prec STAR {$$=criaNoPai(Operadores,"Minus");adicionaFilho2($$,$2);}
    |   PLUS Expr %prec STAR {$$=criaNoPai(Operadores,"Plus");adicionaFilho2($$,$2);}
    |   NOT Expr %prec STAR {$$=criaNoPai(Operadores,"Not");adicionaFilho2($$,$2);}
    |   FuncInvocation {$$=$1;}
    |   LPAR error RPAR {$$=NULL;}
    ;



%%



void yyerror (char *st) {
    flagErro=1;
    if(flagString==0){

        printf ("Line %d, column %d: %s: %s\n", yylineno, numcolunas-(int)strlen(yytext), st, yytext);

    }
    else{

        printf ("Line %d, column %d: %s: \"%s\"\n", yylineno, numcolunas-(int)strlen(s)-2, st, s);
        flagString=0;
    }

}

char * juntaStrings(char *tipo,char *valor, char *parenteses){
    char *aux;
    aux = (char*)malloc(sizeof(char)*300);
    strcpy(aux,tipo);
    strcat(aux,valor);
    strcat(aux, parenteses);
    
    return aux;
}
nodeDefault * criaNoPai(nodeType tipo, char *str){
    nodeDefault *ponteiro;
    if ((ponteiro=malloc(sizeof(nodeDefault)))== NULL)
        printf("Estoirou no criaNoPai!\n");
    ponteiro->filho=NULL;
    ponteiro->irmao=NULL;
    ponteiro->string=str;
    ponteiro->tipo=tipo;
    ponteiro->tipos=NULL;
    ponteiro->linha=yylineno;
    ponteiro->coluna=numcolunas-yyleng;

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
    nodeDefault *iterador;
    iterador=atual;
    while(iterador->irmao!=NULL){
        iterador=iterador->irmao;
    }
    iterador->irmao=novo;


    return atual;
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
nodeDefault * juntarCenas(nodeDefault * alvo,char* string){
    //Temos de adicionar no inicios
    nodeDefault *final,*iterador,*aux;
    iterador=alvo;
    final=criaNoPai(DecVariaveis,"VarDecl");
    adicionaFilho2(final,criaNoPai(Terminal,string));
    adicionaIrmao2(final->filho,criaNoPai(Terminal,alvo->string));
    iterador=iterador->irmao;
    while(iterador!=NULL){
        aux=criaNoPai(DecVariaveis,"VarDecl");
        adicionaFilho2(aux,criaNoPai(Terminal,string));
        adicionaIrmao2(aux->filho,criaNoPai(Terminal,iterador->string));

        adicionaIrmao2(final,aux);
        iterador=iterador->irmao;

    }
    

    return final;
}


 int contaIrmao(nodeDefault * alvo){
    nodeDefault * iterador;
    int sum=1;
    iterador=alvo;
    while(iterador->irmao!=NULL){
        sum++;
        iterador=iterador->irmao;
    
    }
    return sum;

    }


int criaTabelas(nodeDefault *raiz){
    nodeDefault *iterador;
    elemento_tabelag * aux;
    iterador=raiz->filho;
    while(iterador!=NULL){
    if(strcmp(iterador->string,"FuncDecl")==0){
        aux=insertFuncaoT(iterador);
        criaLocal(iterador,aux);
        //imprime_tabelaLocal(aux->local);
        }
    if(strcmp(iterador->string,"VarDecl")==0){
            /* Tentativa de verificar se já está declarada, mas só para as globais(?) */
            insertVarD(iterador);
        }


    iterador=iterador->irmao;
    }
/*
    //printf("%s\n",raiz->string);
    if(raiz->filho!=NULL){

        if(strcmp(raiz->filho->string,"FuncDecl")==0){
            insertFuncaoT(raiz->filho);
        }
    if(strcmp(raiz->filho->string,"VarDecl")==0){
        printf("heheheheh\n");
            insertVarD(raiz->filho);
        }
        criaTabelas(raiz->filho);
        iterador=raiz->filho->irmao;
        while(iterador!=NULL){
            if(strcmp(iterador->string,"FuncDecl")==0){
                insertFuncaoT(iterador);
            }
        if(strcmp(iterador->string,"VarDecl")==0){
        printf("heheheheh2\n");
                insertVarD(iterador);
             }
            criaTabelas(iterador);
            iterador=iterador->irmao;
        }
    //varDecl
    }*/
   
    return 0;

}
/*
int criaTabelas(nodeDefault *raiz){
    nodeDefault *iterador;


    //printf("%s\n",raiz->string);
    if(raiz->filho!=NULL){

        if(strcmp(raiz->filho->string,"FuncDecl")==0){
            insertFuncaoT(raiz->filho);
        }
    if(strcmp(raiz->filho->string,"VarDecl")==0){
        printf("heheheheh\n");
            insertVarD(raiz->filho);
        }
        criaTabelas(raiz->filho);
        iterador=raiz->filho->irmao;
        while(iterador!=NULL){
            if(strcmp(iterador->string,"FuncDecl")==0){
                insertFuncaoT(iterador);
            }
        if(strcmp(iterador->string,"VarDecl")==0){
        printf("heheheheh2\n");
                insertVarD(iterador);
             }
            criaTabelas(iterador);
            iterador=iterador->irmao;
        }
    //varDecl
    }
   
    return 0;

}*/
/*
int anota(nodeDefault *raiz){

    if(no==expressoes){
        if(no nao for equal)
        recursiva();
    }


}
 recursiva(){
    no->filho;
    if(eu sou x&& meiu irmao for x){
        return; 
    }
    se o meu irmao nao tiver tipo recursiva
    se eu nao tiver tipo ir ver
    while(no!=NULL) {
        if(){
        }
        no=no->irmao;
    }

}*/
//so o body e que iporta ir a cada body de cada funcao

void teste1(nodeDefault *raiz){
    //cada func decla
    elemento_tabelag * aux2;
    nodeDefault *aux;
    int x=0;
    aux2=tg;
    aux=raiz->filho;
    while(aux!=NULL){
        recursiva(aux->filho->irmao,aux2);//passamos apenas o body
        aux=aux->irmao;
    aux2=aux2->next;
        x++;
    }
    
    }
int recursiva(nodeDefault *no,elemento_tabelag * elemento){
    //teoria so no body e que importa
    nodeDefault *aux;
    int flag=0;
    if(strcmp(no->string,"Call")==0){
        flag=1;
    }
    aux=no->filho; 
    if(aux==NULL){
        return 0;   
    }
    if(strcmp(aux->string,"VarDecl")==0){
    while(strcmp(aux->string,"VarDecl")==0){
        aux=aux->irmao;
    }
        
    }
    while(aux!=NULL){
        //acho que precisamos de um array para saber erros e tal do genero string*int
    if(strcmp(aux->string,"VarDecl")!=0){
        checkaTerminais(aux,elemento,flag);
        recursiva(aux,elemento);
    }
        aux=aux->irmao;
    
    
        flag=0;
    }
    if(strcmp(no->string,"Eq")==0){
    //printf("EQ percorrer filho ja com o tipo e depois meter o tipo\n");
    makeUsed(tiraId(no->filho->string),elemento);
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
        
    }
    if(strcmp(no->string,"Or")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("OR percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
    }
    if(strcmp(no->string,"And")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    // printf("AND percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
       
    }
    if(strcmp(no->string,"Ne")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("NE percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
        
    }
    if(strcmp(no->string,"Lt")==0){
        makeUsed(tiraId(no->filho->string),elemento);
     //printf("LT percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
       
    }
    /*if do mal para saber se e multi divi etccccc acho que seria aqui Or(2) And(2) Eq(2) Ne(2) Lt(2) Gt(2) Le(2) Ge(2) Add(2) Sub(2) Mul(2) Div(2) Mod(2)
Not(1) Minus(1) Plus(1) Assign(2) Call(>=1) parseArgs call*/
    if(strcmp(no->string,"Gt")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("GT percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
        
    }
    if(strcmp(no->string,"Le")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("LE percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
        
    }
    if(strcmp(no->string,"Ge")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("GE percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,boolean);
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Add")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("ADD percorrer filho ja com o tipo e depois meter o tipo\n");
        if( procuraElemento(no->filho->string,elemento) == 1){
            no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        }
        else{
            printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
        }
    }
    if(strcmp(no->string,"Sub")==0){
        makeUsed(tiraId(no->filho->string),elemento);
     //printf("SUB percorrer filho ja com o tipo e depois meter o tipo\n");
        if( procuraElemento(no->filho->string,elemento) == 1){
    no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
    }
        //percorrer filho ja com o tipo e depois meter o tipo
    else{
            printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
       
    }
    if(strcmp(no->string,"Mul")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("MUL percorrer filho ja com o tipo e depois meter o tipo\n");
        if( procuraElemento(no->filho->string,elemento) == 1){
    no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
}
        //percorrer filho ja com o tipo e depois meter o tipo
else{
            printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
        }
        
    }
    if(strcmp(no->string,"Div")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("DIV percorrer filho ja com o tipo e depois meter o tipo\n");
        if( procuraElemento(no->filho->string,elemento) == 1){
    no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
}
else{
            printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
        }
        
    }
    if(strcmp(no->string,"Mod")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("MOD percorrer filho ja com o tipo e depois meter o tipo\n");
        if( procuraElemento(no->filho->string,elemento) == 1){
    no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
}
        //percorrer filho ja com o tipo e depois meter o tipo
        else{
            printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
        }
    }
    if(strcmp(no->string,"Not")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("NOT percorrer filho ja com o tipo e depois meter o tipo\n");
        if( procuraElemento(no->filho->string,elemento) == 1){
    no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
}
        //percorrer filho ja com o tipo e depois meter o tipo
        else{
            printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
        }
    }
    if(strcmp(no->string,"Minus")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("MINUS percorrer filho ja com o tipo e depois meter o tipo\n");
        if( procuraElemento(no->filho->string,elemento) == 1){
            no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
    }
else{
            printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
        }

        //percorrer filho ja com o tipo e depois meter o tipo
     
    }
    if(strcmp(no->string,"Plus")==0){
        makeUsed(tiraId(no->filho->string),elemento);
    //printf("PLUS percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
    }
    if(strcmp(no->string,"Assign")==0){
        //Verificação do octal
    if(verificaOctal(no->filho->irmao->string)==-1){
        printf("Line %d, column %d: Invalid octal constant: %s\n",no->filho->irmao->linha,no->filho->irmao->coluna,tiraId(no->filho->irmao->string));
    }
    makeUsed(tiraId(no->filho->string),elemento);

    //printf("ASSIGN percorrer filho ja com o tipo e depois meter o tipo\n");
    if( procuraElemento(no->filho->string,elemento) == 1){
        no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
    }
    else{
        printf("Line %d, column %d: Cannot find symbol %s\n",no->filho->linha,no->filho->coluna,tiraId(no->filho->string));
    }
    }
    //rever---------------------------------------------------------------
    if(strcmp(no->string,"Call")==0){
    //printf("CALL percorrer filho ja com o tipo e depois meter o tipo\n");
    if(no->filho->tipos!=NULL){
        //printf("testeeeeee%s\n",estupido(percorreTabelaGlobal2(no->filho->string)));
        no->tipos=insertTipo2(no->tipos,percorreTabelaGlobal2(no->filho->string));
    }
    else{
    no->tipos=insertTipo2(no->tipos,percorreTabelaGlobal2(no->filho->string));
    }
        //percorrer filho ja com o tipo e depois meter o tipo
    }
    if(strcmp(no->string,"ParseArgs")==0){
    //printf("PARSE ARGS percorrer filho ja com o tipo e depois meter o tipo\n");
    no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    //secalahr aqui em baixo duno
    return 0;

    }
void checkaTerminais(nodeDefault *no,elemento_tabelag * elemento,int flag){
    char* aux;
    aux=no->string;
    if(strncmp("Id",aux,strlen("Id"))==0){
        //printf("id-->%s\n",aux);
        if(flag==1){
                //temos funcao percorrer tabelas da maneira x   
         no->tipos=percorreTabelaGlobal(aux);
                //printf("encotramos um id depois de um call\n"); 
        
        }
        else{
           // printf("encotramos um id normal\n");
         no->tipos=insertTipo2(no->tipos,percorreTabela(aux,elemento));
//printf("plssss----->%s\n",estupido(no->tipos->tipo));
            //temos uma variavel percorrer da outra maneira
        }
        //quando temos o id temos de ir sempre as tabelas acho eu
        //temos de ir ver as tabelas e adicionar a lista de tipos
        
    }
    if(strncmp("IntLit",aux,strlen("IntLit"))==0){
        //printf("intlit\n");
    no->tipos=insertTipo(no->tipos,"Int");
        //temos de adicionar ao no o tipo int
    }
    if(strncmp("RealLit",aux,strlen("RealLit"))==0){
    no->tipos=insertTipo(no->tipos,"Float32");
        //printf("realit\n");
        //temos de adicionar ao no o tipo float32
    }
    if(strncmp("StrLit",aux,strlen("StrLit"))==0){
        //printf("strlit\n");
    no->tipos=insertTipo(no->tipos,"String");
        //temos de adicionar ao no o tipo string
    }

    }
noTipo* percorreTabelaGlobal(char* str){
    elemento_tabelag * aux;
    char* auxS;
    aux=tg;
    noTipo* hmmm;
    hmmm=NULL;
    auxS=(char*)malloc(sizeof(char)*100);
    auxS=tiraId(str);
    //printf("tabela Global\n");
    while(aux){
        //printf("-%s\n",aux->name);
        if(strcmp(aux->name,auxS)==0){
            //printf("encontramos Global %s\n",estupido(aux->tipos->tipo)); 
            return aux->tipos;
        }
        aux=aux->next;     
    }
   return hmmm;
}

type percorreTabelaGlobal2(char* str){
    elemento_tabelag * aux;
    char* auxS;
    aux=tg;
    auxS=(char*)malloc(sizeof(char)*100);
    auxS=tiraId(str);
    //printf("tabela Global\n");
    while(aux){
        //printf("-%s\n",aux->name);
        if(strcmp(aux->name,auxS)==0){
            //printf("encontramos Global%s\n",estupido(aux->tipo)); 
            return aux->tipo;
        }
        aux=aux->next;     
    }
    return none;
}
type percorreTabela(char* str,elemento_tabelag * elemento){
    elemento_tabelag * aux;
    elemento_tabelal * aux2;
    char* auxS;
    aux=tg;
    auxS=(char*)malloc(sizeof(char)*100);
    auxS=tiraId(str);
    //printf("tabela Global\n");
    //na ta na global ver local
    aux=tg;
    aux2=elemento->local;
    //printf("tabela local\n");
    while(aux2){    
        //printf("--%s\n",aux2->name);
        if(strcmp(aux2->name,auxS)==0){
            //printf("encontramos local %s\n",estupido(aux2->tipo));
            return aux2->tipo;
        }
        aux2=aux2->next;    
    }
        while(aux){
        //printf("-%s\n",aux->name);
        if(strcmp(aux->name,auxS)==0){
            //printf("encontramos Global%s\n",estupido(aux->tipo)); 
            return aux->tipo;
        }
        aux=aux->next;  
        
    }
    return none;
    //nao encontramos nada
}

int imprimeASTanotada(nodeDefault *raiz,int flag,int depth){
    nodeDefault *iterador;
    int i;
    for(i=0;i<depth;i++){
        printf("..");
    }
    printf("%s",raiz->string);
    // Quer dizer que tem notas, logo tem de as imprimir
    if(raiz->tipos!=NULL){
    if(strcmp(raiz->string,"Call")==0 && raiz->tipos->tipo==none){

    }
    else{
        printf(" - ");
        imprimeTiposAST(raiz->tipos,flag);
    }
        
    }
    else{
    if(flag==1){
    printf(" - ");
        imprimeTiposAST(raiz->tipos,flag);
    }

    }
    flag=0;
    if(strcmp(raiz->string,"Call")==0){/*quando ha um call a impressao dos tipos e diferente,pois ficam entre parentises*/
        flag=1;
    }
    printf("\n");
    if(raiz->filho!=NULL){
    imprimeASTanotada(raiz->filho,flag,depth+1);
        iterador=raiz->filho->irmao;
    flag=0;/*a funçao a ser chamada no call e sempre o filho o irmao ja nao e preciso*/
        while(iterador!=NULL){
            imprimeASTanotada(iterador,flag,depth+1);
            iterador=iterador->irmao;
        }
    }
   
    return 0;

}
void imprimeDeclaredNotUsed(){
    elemento_tabelag *aux;
    elemento_tabelal *aux2;
    aux=tg;
    while(aux!=NULL){
        aux2=aux->local;
        while(aux2!=NULL){
            if(strcmp(aux2->name,"return")!=0 && aux2->used==0 && aux2->param!=1){
                printf("Variavel declarada mas não usada %s \n",aux2->name);
            }
            aux2=aux2->next;

        }
        aux=aux->next;
    }
}

int main(int argc, char **argv) {
    /*
    yydebug=1;
    */
    if(argc>1){
        if (strcmp(argv[1],"-l")==0){
    flagArvore=0;
            flagLex=1;
        while(yylex()){
    
        }
        }
    else{
    if (strcmp(argv[1],"-t")==0){
            flagArvore=1;
     flagLex=0;
        yyparse();
        }
    if (strcmp(argv[1],"-s")==0){
         flagArvore=0;
            flagLex=0;
            flagSemantica=1;
        yyparse();
        }
    }   
        
    }
    else{
        yyparse();
        flagArvore=0;
        //imprime_tabelaGlobal();
    }
    return 0;
}

