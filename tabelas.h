#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { Terminal, Operadores, Statements, DecFuncoes, DecVariaveis, Raiz} nodeType;
typedef struct node *lista;
typedef struct node{
    char *string;
    nodeType tipo;
   	lista filho;
    lista irmao;
}nodeDefault;

typedef enum { integer, boolean, float32, string, none} type;



typedef struct nodeT *listaTipos;
typedef struct nodeT{
    type tipo;
    struct nodeT *next;
}noTipo;



typedef struct _tg{
    char name[32]; /* Nome da função/variável global*/
    listaTipos tipos; /* Lista ligada de tipos ( dos parâmetros da função) */
    type tipo;	/* Tipo de retorno da função ou tipo da variável */
    struct _tg *next; /* Ponteiro para o próximo elemento */
}elemento_tabelag;



elemento_tabelag *insert_el(char *str, type t);
void imprime_tabelaGlobal();
void imprimeTipos(elemento_tabelag *tabela);
noTipo *insertTipo(noTipo *tipos,char *tipoo);
elemento_tabelag *insertParamTypes(char *nomefuncao, nodeDefault *no);
elemento_tabelag *insert_elNode(char *str, nodeDefault *no);
elemento_tabelag *search_el(char *str);
void insertTipos(char *funcNam, nodeDefault *no);

