#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { Terminal, Operadores, Statements, DecFuncoes, DecVariaveis, Raiz} nodeType;
typedef struct node{
    char *string;
    nodeType tipo;
    struct node **ponteiros;
    int nrFilhos;
}nodeDefault;


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

int main(int argc, const char * argv[]) {
    nodeDefault *raiz,*filho1,*filho2,*filho3;
    struct node **ponteirosRaiz,**ponteirosFilho1;
    ponteirosRaiz = (struct node**)malloc(sizeof(struct node)*2);
    ponteirosFilho1 = (struct node**)malloc(sizeof(struct node)*1);
    filho3 = criaNo(Terminal,"Filho3",0,NULL);
    ponteirosFilho1[0]=filho3;
    filho1 = criaNo(DecVariaveis,"Filho1",1,ponteirosFilho1);
    filho2 = criaNo(Terminal,"Filho2",0,NULL);
    ponteirosRaiz[0]=filho1;
    ponteirosRaiz[1]=filho2;
    raiz = criaNo(Raiz,"Program",2,ponteirosRaiz);
    imprimeTralha(raiz,0);
    limpaTralha(raiz);
    return 0;
}

