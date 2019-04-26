#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { Terminal, Operadores, Statements, DecFuncoes, DecVariaveis, Raiz} nodeType;
typedef struct node *lista;
typedef struct node{//meta2 basicamete e a nossa arvore abstracta
    char *string;
    nodeType tipo;
    lista filho;
    lista irmao;
}nodeDefault;

typedef enum { integer, boolean, float32, string, none} type;



typedef struct nodeT *listaTipos;//lista de tipos para a tabela global definida em baixo
typedef struct nodeT{
    type tipo;
    struct nodeT *next;
}noTipo;
//“Name\t[ParamTypes]\tType[\tparam]”,
//como ficam as funçoes chamadas dentro de funçoes pelos vistos nao se mete nada okkkkkkk
typedef struct _tl{
    char name[32]; /* Nome da função/variável local*/
    int param; //se e parametro ou nao (pode se omitirrrr)
    type tipo;	/* Tipo de retorno da função ou tipo da variável */
    struct _tl *next;
}elemento_tabelal;
//fazer funçoes para inseir na tabela local etc e depois associar a global


typedef struct _tg{
    char name[32]; /* Nome da função/variável global*/
    listaTipos tipos; /* Lista ligada de tipos ( dos parâmetros da função) */
    type tipo;	/* Tipo de retorno da função ou tipo da variável */
    struct _tg *next; /* Ponteiro para o próximo elemento */
    elemento_tabelal *local;
}elemento_tabelag;




elemento_tabelag *insert_el(char *str, char* t);
elemento_tabelal *insert_elLocal(char *str, char* t,int param,elemento_tabelal * lista_local);

void imprime_tabelaGlobal();
void imprime_tabelaLocal(elemento_tabelal * lista_local,char* s);
void imprimeTipos(elemento_tabelag *tabela);
noTipo *insertTipo(noTipo *tipos,char *tipoo);
elemento_tabelag *insertParamTypes(char *nomefuncao, nodeDefault *no);
elemento_tabelag *insert_elNode(char *str, nodeDefault *no);
elemento_tabelag *search_el(char *str);
void insertTipos(char *funcNam, nodeDefault *no);
elemento_tabelag* insertFuncaoT(nodeDefault *no);
elemento_tabelag* insertVarD(nodeDefault *no);
int checkHasReturn(nodeDefault *no);
char * tiraId(char *str);
void criaLocal(nodeDefault *no,elemento_tabelag * elemento);


