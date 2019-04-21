#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"tabelas.h"

extern elemento_tabelag* tg;


//Insere um novo identificador na cauda de uma lista ligada de simbolo
elemento_tabelag *insert_el(char *str, type t)
{
	elemento_tabelag *newSymbol=(elemento_tabelag*) malloc(sizeof(elemento_tabelag));
	elemento_tabelag *aux;
	elemento_tabelag *previous;

	strcpy(newSymbol->name, str);
	newSymbol->tipo=t;
	newSymbol->next=NULL;	

	if(tg)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=tg; aux; previous=aux, aux=aux->next)
			if(strcmp(aux->name, str)==0)
				return NULL;
		
		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		tg=newSymbol;		
	
	return newSymbol; 
}


elemento_tabelag *insert_elNode(char *str, nodeDefault *no)
{
	elemento_tabelag *newSymbol=(elemento_tabelag*) malloc(sizeof(elemento_tabelag));
	elemento_tabelag *aux;
	elemento_tabelag *previous;

	strcpy(newSymbol->name, str);
	if(strcmp(no->string,"Int")==0){
		newSymbol->tipo=integer;
	}
	else if(strcmp(no->string,"Bool")==0){
		newSymbol->tipo=boolean;
	}
	else if(strcmp(no->string,"Float32")==0)
	{	
		newSymbol->tipo=float32;
	}
	else if(strcmp(no->string,"String")==0){
		newSymbol->tipo=string;
	}
	
	newSymbol->tipos=NULL;
	newSymbol->next=NULL;	

	if(tg)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=tg; aux; previous=aux, aux=aux->next)
			if(strcmp(aux->name, str)==0)
				return NULL;
		
		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		tg=newSymbol;		
	
	return newSymbol; 
}


// O no que vai receber vai ser o FuncParams, temos de aceder aos netos
// Depois temos de ter cuidado com os netos
void insertTipos(char *funcNam, nodeDefault *no){
	nodeDefault *auxP,*auxF;
	elemento_tabelag *auxt;
	auxP=no;
	auxP=auxP->filho; //ParamDecl, este vai ter irmãos ParamDecl
	auxF=auxP->filho; //Primeiro neto
	auxt = search_el(funcNam);
	auxt->tipos=insertTipo(auxt->tipos,auxF->string);
	while(auxP->irmao!=NULL){
		auxP=auxP->irmao;
		auxF=auxP->filho;
		auxt->tipos=insertTipo(auxt->tipos,auxF->string);
	}


}

/* Recebe a lista de tipos e insere um novo tipo na cauda*/
/* Passagem de parâmetros pode estar mal*/
noTipo *insertTipo(noTipo *tipos,char *tipoo){
	noTipo *iterador;
	noTipo *novo;
	
	
	novo=malloc(sizeof(noTipo));
	iterador=tipos;

	if(strcmp(tipoo,"Int")==0){
		novo->tipo=integer;
	}
	else if(strcmp(tipoo,"Bool")==0){
		novo->tipo=boolean;
	}
	else if(strcmp(tipoo,"Float32")==0)
	{	
		novo->tipo=float32;
	}
	else if(strcmp(tipoo,"String")==0){
		novo->tipo=string;
	}

	/* Se estiver vazia */
	if(tipos==NULL){
		tipos=novo;
	}
	else{
		while(iterador->next!=NULL){
			iterador=iterador->next;
		}
		iterador->next=novo;
	}
	return tipos;

}

void imprime_tabelaGlobal()
{
	printf("===== Global Symbol Table =====");
	elemento_tabelag *aux;
	printf("\n");
	for(aux=tg; aux; aux=aux->next){
		printf("%s\t",aux->name);
		printf("(");
		imprimeTipos(aux);
		printf(")");
		switch(aux->tipo){
		case none:
			printf("\tnone");
			break;
		case integer:
			printf("\tint");
			break;
		case string:
			printf("\tstring");
			break;
		case boolean:
			printf("\tbool");
			break;
		case float32:
			printf("\tfloat32");
			break;
		}
		printf("\n");
	}

	printf("\n");
}
void imprimeTipos(elemento_tabelag *tabela){
	noTipo *iterador;
	iterador=tabela->tipos;// Está a null...
	while(iterador!=NULL){
		switch(iterador->tipo){
		case none:
			printf("none");
			break;
		case integer:
			printf("int");
			break;
		case string:
			printf("string");
			break;
		case boolean:
			printf("bool");
			break;
		case float32:
			printf("float32");
			break;
		}
		if(iterador->next!=NULL){// Para não imprimir virgula no ultimo
			printf(", ");
		}
		iterador=iterador->next;
	}
}

/* Podemos ter de trocar o tipo da função */
elemento_tabelag *insertParamTypes(char *nomefuncao, nodeDefault *no){
	int i;
	nodeDefault *iterador;
	iterador=no;
	//Procura a função e recebe a entrada da tabela
	elemento_tabelag *aux = search_el(nomefuncao);

	aux->tipos=insertTipo(aux->tipos,iterador->string);
	// Percorrer os irmãos do nó e adicionar à lista de tipos da entrada da tabela
	while(iterador->irmao!=NULL){
		iterador=iterador->irmao;
		iterador=iterador->irmao;
		aux->tipos=insertTipo(aux->tipos,iterador->string);
	}
	return aux;

}





//Procura um identificador, devolve 0 caso nao exista

elemento_tabelag *search_el(char *str)
{
	elemento_tabelag *aux;
	for(aux=tg; aux; aux=aux->next)
		if(strcmp(aux->name, str)==0)
			return aux;
	return NULL;
}






