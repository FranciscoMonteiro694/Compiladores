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
    noErro * erros=NULL;
    int contadorErros;
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
    struct nodeAuxiliar *p;
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
%token <string> INTLIT 
%token <string> REALLIT
%token <p> ID
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
        
        if(erros==NULL){
            imprime_tabelaGlobal();
            imprimeASTanotada($$,0,0);
        }


    //createFile();

    }
    //DeclaredNotUsed();
    imprimeListaErros(erros);
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
        $$=adicionaIrmaoInicio($2,criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha));
        $$=juntarCenas($$,$3->string);
        

    }
    else{
        $$=criaNoPai(DecVariaveis,"VarDecl");
        adicionaFilho2($$,$3);
       adicionaIrmao2($$->filho,criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha));
    }
    };
    ;

teste: teste COMMA ID {
    if($1!=NULL){
        $$=$1;
        adicionaIrmao2($$,criaNoPai2(Terminal,juntaStrings("Id(",$3->string,")"),$3->coluna,$3->linha));
    }
    else{
          $$=criaNoPai2(Terminal,juntaStrings("Id(",$3->string,")"),$3->coluna,$3->linha);
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
     aux2=criaNoPai2(Terminal,juntaStrings("Id(",$2->string,")"),$2->coluna,$2->linha);
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
        aux2=criaNoPai2(Terminal,juntaStrings("Id(",$2->string,")"),$2->coluna,$2->linha);
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
        aux2=criaNoPai2(Terminal,juntaStrings("Id(",$2->string,")"),$2->coluna,$2->linha);
        adicionaFilho2(aux,aux2);
        adicionaIrmao2(aux->filho,$6);
        adicionaIrmao2(aux->filho,$4);
        adicionaIrmao2($$->filho,$7);        
    }
    |   FUNC ID LPAR  RPAR Type FuncBody {
        nodeDefault *aux,*aux2; 
        $$=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2($$,aux);
        aux2=criaNoPai2(Terminal,juntaStrings("Id(",$2->string,")"),$2->coluna,$2->linha);
        adicionaFilho2(aux,aux2);
    
        adicionaIrmao2(aux->filho,$5);//dar double checkkkkk
    
        adicionaIrmao2($$->filho,$6);
        adicionaIrmao2(aux->filho,criaNoPai(DecFuncoes,"FuncParams"));  
    }
    ;
Parameters: ID Type AuxParameters {
    if ($3!=NULL){
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha);
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,$2);
        adicionaIrmao2(aux2->filho,aux1);
        adicionaIrmaoInicio($3,aux2);
        $$=criaNoPai(DecFuncoes,"FuncParams");
        adicionaFilho2($$,aux2);



    }
    else{
        nodeDefault *aux1,*aux2;
         aux1=criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha);
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
        aux1=criaNoPai2(Terminal,juntaStrings("Id(",$3->string,")"),$3->coluna,$3->linha);
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,$4);
        adicionaIrmao2(aux2->filho,aux1);
        adicionaIrmao2($$,aux2);
    }
    else{
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai2(Terminal,juntaStrings("Id(",$3->string,")"),$3->coluna,$3->linha);
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
            adicionaFilho2($$,criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha));
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
    adicionaFilho2($$,criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha));
    adicionaIrmao2($$->filho,$9);
}
    |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR {$$=NULL;}
    ;

FuncInvocation: ID LPAR error RPAR {$$=NULL;}
    |   ID LPAR RPAR {$$=criaNoPai(Statements,"Call");adicionaFilho2($$,criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha));} /* Não sabemos o Type a pôr aqui */ 
    |   ID LPAR Expr AuxFuncInvocation RPAR {
        if($4!=NULL){
            $$=criaNoPai(Statements,"Call");
            adicionaFilho2($$,criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha));
        adicionaIrmao2($3,$4);
            adicionaIrmao2($$->filho,$3);
    }
    else{
        nodeDefault *aux;
        aux=criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha);
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
    |   ID {$$=criaNoPai2(Terminal,juntaStrings("Id(",$1->string,")"),$1->coluna,$1->linha);}
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
        printf("Estoirou!\n");
    ponteiro->filho=NULL;
    ponteiro->irmao=NULL;
    ponteiro->string=str;
    ponteiro->tipo=tipo;
    ponteiro->tipos=NULL;
    ponteiro->linha=yylineno;
    ponteiro->coluna=numcolunas-yyleng;
    return ponteiro;
}

nodeDefault * criaNoPai2(nodeType tipo, char *str,int coluna,int linha){
    nodeDefault *ponteiro;
    if ((ponteiro=malloc(sizeof(nodeDefault)))== NULL)
        printf("Estoirou!\n");
    ponteiro->filho=NULL;
    ponteiro->irmao=NULL;
    ponteiro->string=str;
    ponteiro->tipo=tipo;
    ponteiro->tipos=NULL;
    ponteiro->linha=linha;
    ponteiro->coluna=coluna;
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
    //printf("%s %d %d\n",raiz->string,raiz->linha,raiz->coluna);
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
    adicionaIrmao2(final->filho,criaNoPai2(Terminal,alvo->string,alvo->coluna,alvo->linha));
    iterador=iterador->irmao;
    while(iterador!=NULL){
        aux=criaNoPai(DecVariaveis,"VarDecl");
        adicionaFilho2(aux,criaNoPai(Terminal,string));
        adicionaIrmao2(aux->filho,criaNoPai2(Terminal,iterador->string,iterador->coluna,iterador->linha));

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


int main(int argc, char **argv) {
    /*
    yydebug=1;
    */
    contadorErros=0;
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


