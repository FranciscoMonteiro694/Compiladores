#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { integer, boolean, float32, string, none} type;



typedef struct nodeT *listaTipos;//lista de tipos para a tabela global definida em baixo
typedef struct nodeT{
    type tipo;
    struct nodeT *next;
}noTipo;
typedef enum { Terminal, Operadores, Statements, DecFuncoes, DecVariaveis, Raiz} nodeType;
typedef struct node *lista;
typedef struct node{//meta2 basicamete e a nossa arvore abstracta
    char *string;
    nodeType tipo;
    lista filho;
    lista irmao;
    listaTipos tipos;
}nodeDefault;


//“Name\t[ParamTypes]\tType[\tparam]”,
//como ficam as funçoes chamadas dentro de funçoes pelos vistos nao se mete nada okkkkkkk
typedef struct _tl{
    char name[32]; /* Nome da função/variável local*/
    int param; //se e parametro ou nao (pode se omitirrrr)
    type tipo;  /* Tipo de retorno da função ou tipo da variável */
    struct _tl *next;
}elemento_tabelal;
//fazer funçoes para inseir na tabela local etc e depois associar a global


typedef struct _tg{
    char name[32]; /* Nome da função/variável global*/
    listaTipos tipos; /* Lista ligada de tipos ( dos parâmetros da função) */
    type tipo;  /* Tipo de retorno da função ou tipo da variável */
    int funcao;
    struct _tg *next; /* Ponteiro para o próximo elemento */
    elemento_tabelal *local;
}elemento_tabelag;



elemento_tabelag *insert_el(char *str, char* t,int func);
elemento_tabelal *insert_elLocal(char *str, char* t,int param,elemento_tabelal * lista_local);
void imprime_tabelaGlobal();
void imprime_tabelaLocal(elemento_tabelal * lista_local,char* s);
void imprimeTipos(elemento_tabelag *tabela);
noTipo *insertTipo(noTipo *tipos,char *tipoo);
elemento_tabelag *search_el(char *str);
void insertTipos(char *funcNam, nodeDefault *no);
elemento_tabelag* insertFuncaoT(nodeDefault *no);
elemento_tabelag* insertVarD(nodeDefault *no);
int checkHasReturn(nodeDefault *no);
char * tiraId(char *str);
void criaLocal(nodeDefault *no,elemento_tabelag * elemento);
char * estupido(type c);
void imprimeTiposAST(noTipo *tipos, int flag);
noTipo *insertTipo2(noTipo *tipos,type tipo);
noTipo* percorreTabelaGlobal(char* str);
type percorreTabelaGlobal2(char* str);
/**/
int imprimeASTanotada(nodeDefault *raiz,int flag,int depth);
int imprimeTralha(nodeDefault *raiz,int depth);
int limpaTralha(nodeDefault *raiz);
nodeDefault * criaNoPai(nodeType tipo, char *str);
nodeDefault * adicionaFilho(nodeDefault * pai,nodeType tipo, char *str);
nodeDefault * adicionaIrmao(nodeDefault * atual,nodeType tipo, char *str);
int imprimeTralha(nodeDefault *raiz,int depth);
nodeDefault * adicionaIrmao2(nodeDefault * atual,nodeDefault *novo);
nodeDefault * adicionaFilho2(nodeDefault * pai,nodeDefault *novo);
nodeDefault * adicionaIrmaoInicio(nodeDefault * atual,nodeDefault *novo);
nodeDefault * juntarCenas(nodeDefault * alvo,char* string);
char * juntaStrings(char *tipo,char *valor, char *parenteses);
int contaIrmao(nodeDefault * alvo);
int criaTabelas(nodeDefault *raiz);
int anota(nodeDefault *raiz);
void checkaTerminais(nodeDefault *no,elemento_tabelag * elemento,int flag);
int recursiva(nodeDefault *no,elemento_tabelag * elemento);
type percorreTabela(char* str,elemento_tabelag * elemento);
elemento_tabelag* percorreTabelaGlobal3(char* str);




