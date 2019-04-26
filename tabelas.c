#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"tabelas.h"

//lex gocompiler.l && yacc -d gocompiler.y && cc -o f5 lex.yy.c y.tab.c tabelas.c 

extern elemento_tabelag* tg;//aquela cena do mal noice

//o Monteiro a chamar cauda ao ultimo no da lista dame triggereeerer
//Insere um novo identificador na cauda de uma lista ligada de simbolo
elemento_tabelag *insert_el(char *str, char* t)//recebe o indetificador e o tipo
{
	elemento_tabelag *newSymbol=(elemento_tabelag*) malloc(sizeof(elemento_tabelag));//elemento da tabelo global
	elemento_tabelag *aux;
	elemento_tabelag *previous;

	strcpy(newSymbol->name, str);//mete o identificador do simbolo i guess
	if(strcmp(t,"Int")==0){//basicamete vai comparar todos os tipos para saber qual o tipo
		newSymbol->tipo=integer;
	}
	else if(strcmp(t,"Bool")==0){
		newSymbol->tipo=boolean;
	}
	else if(strcmp(t,"Float32")==0)
	{	
		newSymbol->tipo=float32;
	}
	else if(strcmp(t,"String")==0){
		newSymbol->tipo=string;
	}
	else if(strcmp(t,"none")==0){
		newSymbol->tipo=none;
	}
	//o tipo e aquela cena do mal do enum
	//ja metemos o indetificador e o tipo no no agora e so ligar i guess
        //newSymbol->local=insert_elLocal("teste", "int",1,NULL);//nao sao usados
        newSymbol->local=NULL;
	newSymbol->tipos=NULL;//nao sao usados
	newSymbol->next=NULL;	

	if(tg)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=tg; aux; previous=aux, aux=aux->next)//a condiçao de paragem e o aux ser null
			if(strcmp(aux->name, str)==0)
				return NULL;//ja existe um igual(identificador)
		
		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		tg=newSymbol;		
	
	return newSymbol; 
}

elemento_tabelal *insert_elLocal(char *str, char* t,int param,elemento_tabelal * lista_local){
	elemento_tabelal *newSymbol=(elemento_tabelal*) malloc(sizeof(elemento_tabelal));//elemento da tabelo global
	elemento_tabelal *aux;
	elemento_tabelal *previous;

	strcpy(newSymbol->name, str);//mete o identificador do simbolo i guess
	if(strcmp(t,"Int")==0){//basicamete vai comparar todos os tipos para saber qual o tipo
		newSymbol->tipo=integer;
	}
	else if(strcmp(t,"Bool")==0){
		newSymbol->tipo=boolean;
	}
	else if(strcmp(t,"Float32")==0)
	{	
		newSymbol->tipo=float32;
	}
	else if(strcmp(t,"String")==0){
		newSymbol->tipo=string;
	}
	else if(strcmp(t,"none")==0){
		newSymbol->tipo=none;
	}
	//o tipo e aquela cena do mal do enum
	//ja metemos o indetificador e o tipo no no agora e so ligar i guess
	newSymbol->param=param;//nao sao usados
	newSymbol->next=NULL;
	if(lista_local)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=lista_local; aux; previous=aux, aux=aux->next)//a condiçao de paragem e o aux ser null
			if(strcmp(aux->name, str)==0)
				return NULL;//ja existe um igual(identificador)
		
		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else	//symtab tem um elemento -> o novo simbolo
		lista_local=newSymbol;		
	
	return newSymbol;



}


//acho que nao importa
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


// O no(um ramo da arvore) que vai receber vai ser o FuncParams, temos de aceder aos netos
// Depois temos de ter cuidado com os netos
//e do genero funcparams->paramDecl->(Tipo e id) e pode ter varios paramDecl ou seja varios parametros
void insertTipos(char *funcNam, nodeDefault *no){
	nodeDefault *auxP,*auxF;
	elemento_tabelag *auxt;
	auxP=no;
	auxP=auxP->filho; //ParamDecl, este vai ter irmãos ParamDecl
	auxF=auxP->filho; //Primeiro neto javardice XD
	auxt = search_el(funcNam);//procura o elemento na tabela devolve null ou a propria entrada da tabel (elemento da lista)
	auxt->tipos=insertTipo(auxt->tipos,auxF->string);//insere o tipo do parametro na lista de tipos da tabela global
	while(auxP->irmao!=NULL){
		auxP=auxP->irmao;//repete o processo para os outros parametros
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
		if(aux->tipos!=NULL){
		printf("(");
		imprimeTipos(aux);
		printf(")");
		}
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
	for(aux=tg; aux; aux=aux->next){
	if(aux->local!=NULL){
		imprime_tabelaLocal(aux->local);
	}
	}
}
void imprime_tabelaLocal(elemento_tabelal * lista_local){
	printf("===== Local Symbol Table =====");//---------------------------->adicionar nome da funcao etc
	elemento_tabelal *aux;
	printf("\n");
	for(aux=lista_local; aux; aux=aux->next){
		printf("%s\t",aux->name);
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
		if(aux->param==1){
			printf("\tparam");
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

// Função que verifica se uma função tem tipo de retorno, devolve 1 se tiver
// Recebe o irmão mais da esquerda (nome da funcao)
// Assume-se que o FuncParams é o irmão logo há direita caso não tenha tipo de retorno
int checkHasReturn(nodeDefault *no){
	// Significa que não tem tipo
	if (strcmp(no->irmao->string,"FuncParams")==0)
		return 0;
	else
		return 1;
}


/*
Esta função vai receber o node do tipo FuncDecl e vai logo meter esta função na tabela global e criar a tabela local, com tudo lá dentro 
*/
// Para tirar o "id()" da string
char * tiraId(char *str){
	char *aux;
    aux = (char*)malloc(sizeof(char)*300);
    const char s[2] = "(";
    aux=strtok(str,s);
    aux= strtok(NULL,s);
    aux[strlen(aux)-1]='\0';
    //printf("Valor %s\n",aux);
    return aux;
}

void insertFuncaoT(nodeDefault *no){// FuncDecl
	// Insere o nome da função na tabela global
	// Se tiver tipo de retorno
	nodeDefault *aux;
	aux=no->filho->filho;//Nome da função
	char * nomeFunc;
	nomeFunc=(char*)malloc(sizeof(char)*50);
	//printf("Nome da funcao %s\n",aux->string);
	strcpy(nomeFunc,tiraId(aux->string));
	//printf("Nome da func %s\n",nomeFunc);
	if (checkHasReturn(aux)==1){
		elemento_tabelag* newel=insert_el(nomeFunc,aux->irmao->string);
		aux=aux->irmao;
		aux=aux->irmao;
	}
	else{
		elemento_tabelag* newel=insert_el(nomeFunc,"none");
		aux=aux->irmao;

	}
	if(aux->filho!=NULL){ // Se a função tiver parâmetros
		insertTipos(nomeFunc, aux);
	}

	

}

void insertVarD(nodeDefault *no){//VarDecl ta a entrar um funcdec wtf
	nodeDefault *aux=no;
        printf("teste %s\n",aux->string);
	printf("teste %s\n",aux->filho->string);
	printf("teste %s\n",aux->filho->irmao->string);
	//falta verificaçoes mas wahteveeeer
	elemento_tabelag* newel=insert_el(aux->filho->irmao->string,aux->filho->string);
	

}





