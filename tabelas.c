#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"tabelas.h"

//lex gocompiler.l && yacc -d gocompiler.y && cc -o f5 lex.yy.c y.tab.c tabelas.c 

extern elemento_tabelag* tg;//aquela cena do mal noice

//o Monteiro a chamar cauda ao ultimo no da lista dame triggereeerer
//Insere um novo identificador na cauda de uma lista ligada de simbolo
elemento_tabelag *insert_el(char *str, char* t,int func)//recebe o indetificador e o tipo
{
	elemento_tabelag *newSymbol=(elemento_tabelag*) malloc(sizeof(elemento_tabelag));//elemento da tabelo global
	elemento_tabelag *aux;
	elemento_tabelag *previous;

	strcpy(newSymbol->name, str);//mete o identificador do simbolo i guess
	newSymbol->funcao=func;
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
	// Se não for return e a flag de parametros estiver a 0 quer dizer que é a declaração de uma variavel
	if (strcmp(str,"return")!=0 && param==0){
		newSymbol->used=0;
	}
	else{
		newSymbol->used=2;// so para nao estoirar quando se for ver os erros
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
	//imprime_tabelaLocal(lista_local);
	return lista_local;



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
noTipo *insertTipo2(noTipo *tipos,type tipo){
	noTipo *iterador;
	noTipo *novo;
	
	
	novo=malloc(sizeof(noTipo));
	iterador=tipos;
	novo->tipo=tipo;
	/* Se estiver vazia */
	if(tipos==NULL){
		/*printf("olaaaaa\n");*/
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

noTipo *insertTipo(noTipo *tipos,char *tipoo){
	noTipo *iterador;
	noTipo *novo;
	
	
	novo=malloc(sizeof(noTipo));
	iterador=tipos;

	if(strcmp(tipoo,"Int")==0){
		/*printf("noiceeee\n");*/
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
		/*printf("olaaaaa\n");*/
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
		if(aux->funcao==1){
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
		imprime_tabelaLocal(aux->local,aux->name);
		/*if(aux->next!=NULL){
			printf("\n");
		}*/
	}
	}
}
char * estupido(type c){
	switch(c){
		case none:
			return("none,");
			break;
		case integer:
			return("int,");
			break;
		case string:
			return("string,");
			break;
		case boolean:
			return("bool,");
			break;
		case float32:
			return("float32,");
			break;
		}
	}
void imprime_tabelaLocal(elemento_tabelal * lista_local,char* s){
	char auxS [100] ;
	elemento_tabelal *aux,*aux2;
	aux2=lista_local->next;
	strcpy(auxS,"");
	while(aux2!=NULL){
		if(aux2->param==1){
		strcat(auxS,estupido(aux2->tipo));
		
		}
		aux2=aux2->next;
	}
	auxS[strlen(auxS)-1]='\0';
	printf("===== Function %s(%s) Symbol Table =====\n",s,auxS);//---------------------------->adicionar nome da funcao etc
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
		if(iterador->next!=NULL){
			printf(",");
		}
		iterador=iterador->next;
	}
}

// Vai imprimir as notas da AST, se estiver a 1 quer dizer que é uma call de uma função e tem de pôr parenteses
void imprimeTiposAST(noTipo *tipos, int flag){
	noTipo *iterador;
	iterador=tipos;
	// Se for call tem de pôr parenteses
	if(flag==1){
		/*if(iterador!=NULL){
			if(iterador->tipo==none){
			}
			else{
				printf("(");
			}
		}*/
			printf("(");
			}
	while(iterador!=NULL){
		switch(iterador->tipo){
		case none:
			//printf("none");
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
			printf(",");
		}
		iterador=iterador->next;
	}
	if (flag==1)
		printf(")");
}

/* Podemos ter de trocar o tipo da função */
elemento_tabelag *insertParamTypes(char *nomefuncao, nodeDefault *no){
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

// Procura um elemento na tabela local, e depois na global
// Para fazer os erros
// Devolve 1 se encontrar, 0 caso contrário

int procuraElemento(char *str,elemento_tabelag * elemento){
	//printf("Elemento a ser procurado %s \n",str);
	if (strncmp(str, "Id(", 3)==0){
		elemento_tabelag *aux;
		elemento_tabelal * aux2;
		/* Procura na local */
		aux2=elemento->local;
		while(aux2!=NULL){
			if(strcmp(tiraId(str),aux2->name)==0)
				return 1;
			aux2=aux2->next;
		}

		aux=tg;
		while(aux!=NULL){
			if(strcmp(tiraId(str),aux->name)==0)
				return 1;
			aux=aux->next;
		}

		return 0;
	}
	else{
		return 1;
	}
}
// Funcao que recebe um IntLit e caso ele comece por 0, verifica se é um octal correcto
// Devolve 1 se for, 0 caso não seja octal , -1 caso esteja incorrecto
int verificaOctal(char *numero){
	int iterador;
	iterador=7;
	//Se for Octal
	if(strncmp(numero, "IntLit(0", 8)==0){
		
		// Enquanto não chegar ao fim da string
		while(numero[iterador]!='\0'){
			if(numero[iterador]=='8' || numero[iterador]=='9'){
				//printf("%s é octal incorrecto\n",numero);
				return -1;
			}
			iterador++;
		}
		//printf("%s é octal \n",numero);
		return 1;
	}
	else{
		return 0;
	}
}
// int procuraElemento(nodeDefault *no,elemento_tabelag * elemento){
// 	//printf("Elemento a ser procurado %s \n",str);

// 	elemento_tabelag *aux;
// 	elemento_tabelal * aux2;
// 	/* Procura na local */
// 	aux2=elemento->local;
// 	while(aux2!=NULL){
// 		if(strcmp(str,aux2->name)==0)
// 			return 1;
// 		aux2=aux2->next;
// 	}

// 	aux=tg;
// 	while(aux!=NULL){
// 		if(strcmp(str,aux->name)==0)
// 			return 1;
// 		aux=aux->next;
// 	}
// 	return 0;


// }
//Procura um identificador, devolve 0 caso nao exista

elemento_tabelag *search_el(char *str)
{
	elemento_tabelag *aux;
	for(aux=tg; aux; aux=aux->next)
		if(strcmp(aux->name, str)==0)
			return aux;
	return NULL;
}


// Procura um elemento na tabela local, 

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
// Para tirar o "id()" da string<
char * tiraId(char *str){
	char *aux,*aux2;
	aux2 = (char*)malloc(sizeof(char)*300);
	strcpy(aux2,str);
    aux = (char*)malloc(sizeof(char)*300);
    const char s[2] = "(";
    aux=strtok(aux2,s);
    aux= strtok(NULL,s);
    aux[strlen(aux)-1]='\0';
    //printf("Valor %s\n",aux);
    return aux;
}


elemento_tabelag* insertFuncaoT(nodeDefault *no){// FuncDecl
	// Insere o nome da função na tabela global
	// Se tiver tipo de retorno
	elemento_tabelag* newel;
	nodeDefault *aux;
	aux=no->filho->filho;//Nome da função
	char * nomeFunc;
	nomeFunc=(char*)malloc(sizeof(char)*50);
	//printf("Nome da funcao %s\n",aux->string);
	strcpy(nomeFunc,tiraId(aux->string));
	//printf("Nome da func %s\n",nomeFunc);
	if (checkHasReturn(aux)==1){
		newel=insert_el(nomeFunc,aux->irmao->string,1);
		aux=aux->irmao;
		aux=aux->irmao;
	}
	else{
		newel=insert_el(nomeFunc,"none",1);
		aux=aux->irmao;

	}
	if(aux->filho!=NULL){ // Se a função tiver parâmetros
		insertTipos(nomeFunc, aux);
	}

	
	return newel;
}
// Função que recebe uma variavel local e mete a flag used a 1
void makeUsed(char *nomeVariavel,elemento_tabelag * elemento){
	elemento_tabelal *aux;
	aux=elemento->local;
	while(aux!=NULL){
		// Se encontrou
		if(strcmp(nomeVariavel,aux->name)==0){
			if(aux->used==0){
				aux->used=1;
				break;
			}
		}
		aux=aux->next;
	}
}

elemento_tabelag* insertVarD(nodeDefault *no){//VarDecl ta a entrar um funcdec wtf
	nodeDefault *aux=no;
	elemento_tabelag* newel;
	char*nomeFunc;
	nomeFunc=(char*)malloc(sizeof(char)*50);
	//printf("Nome da funcao %s\n",aux->string);
	strcpy(nomeFunc,tiraId(aux->filho->irmao->string));
        /*printf("teste %s\n",aux->string);
	printf("teste %s\n",aux->filho->string);
	printf("teste %s\n",aux->filho->irmao->string);*/
	//falta verificaçoes mas wahteveeeer
	 newel=insert_el(nomeFunc,aux->filho->string,0);
	 if(newel==NULL){
	 	printf("Line %d, column %d: Symbol %s already defined\n",aux->filho->irmao->linha,aux->filho->irmao->coluna,tiraId(aux->filho->irmao->string));
	 	printf("Valor %s \n",aux->filho->irmao->string);
	 }
	return newel;
	

}
// Função que procura o VarDecl de uma variavel
// Primeiro localmente e depois globalmente
// Se retornar 1 é suposto imprimir o erro depois
int procuraEl(char *nomeVariavel,char* tipo,elemento_tabelal * local){
	elemento_tabelal *aux;
	elemento_tabelag *aux2;
	aux=local;
	// Percorre local
	while(aux!=NULL){
		// Se encontrou
		if(strcmp(nomeVariavel,aux->name)==0){
			return 1;
		}
		aux=aux->next;
	}
	// Percorre global
	aux2=tg;
	while(aux2!=NULL){
		// se encontrou
		if(strcmp(nomeVariavel,aux2->name)==0){
			if(strcmp(tipo,"Int")==0 && aux2->tipo==integer ){
				return 1;
			}
			if(strcmp(tipo,"Bool")==0 && aux2->tipo==boolean ){
				return 1;
			}
			if(strcmp(tipo,"Float32")==0 && aux2->tipo==float32 ){
				return 1;
			}
			if(strcmp(tipo,"String")==0 && aux2->tipo==string ){
				return 1;
			}
			return 0;
		}
		aux2=aux2->next;
	}
	return 0;
	
}
void criaLocal(nodeDefault *no,elemento_tabelag * elemento){
    //recebe o func dec
    nodeDefault *iterador,*iterador2,*iterador3;
    iterador=no->filho;
    while(iterador!=NULL){
	//vai ver o header da funcao se tem parametros e inutl acho eu este if
	if(strcmp(iterador->string,"FuncHeader")==0){
		if(strcmp(iterador->filho->irmao->string,"FuncParams")!=0){//o irmao do nome da funcao nao for fucparams que dizer que esta funçao retorna algo
			elemento->local=insert_elLocal("return",iterador->filho->irmao->string,0,elemento->local);
			iterador3=iterador->filho->irmao->irmao->filho;
			while(iterador3!=NULL){//meter os parametos
			//printf("a percored o iterador3 %s \n",iterador3->string);
			char*nomeFunc;
			nomeFunc=(char*)malloc(sizeof(char)*50);
			//printf("Nome da funcao %s\n",aux->string);
			strcpy(nomeFunc,tiraId(iterador3->filho->irmao->string));
			elemento->local=insert_elLocal(nomeFunc,iterador3->filho->string,1,elemento->local);
			iterador3=iterador3->irmao;
			}
			

		}
		else{
		//nao retorna nada
		elemento->local=insert_elLocal("return","none",0,elemento->local);
		iterador3=iterador->filho->irmao->filho;
		while(iterador3!=NULL){
			//printf("a percored o iterador3 %s \n",iterador3->string);
			char*nomeFunc;
			nomeFunc=(char*)malloc(sizeof(char)*50);
			//printf("Nome da funcao %s\n",aux->string);
			strcpy(nomeFunc,tiraId(iterador3->filho->irmao->string));
			elemento->local=insert_elLocal(nomeFunc,iterador3->filho->string,1,elemento->local);
			iterador3=iterador3->irmao;
			}
			
		}
		
	    //fazer local
        }
	if(strcmp(iterador->string,"FuncBody")==0){
		iterador2=iterador->filho;
		while(iterador2!=NULL){
			//printf("a percored o iterador2 %s \n",iterador2->string);
			if(strcmp(iterador2->string,"VarDecl")==0){
				//printf("asdasdads\n");
				char*nomeFunc;
				nomeFunc=(char*)malloc(sizeof(char)*50);
				//printf("Nome da funcao %s\n",aux->string);
				strcpy(nomeFunc,tiraId(iterador2->filho->irmao->string));
				//se não existir nenhuma
				//printf("Tipo da variavel %s\n",iterador2->filho->string);
				if(procuraEl(nomeFunc,iterador2->filho->string,elemento->local)==1){
					printf("Line %d, column %d: Symbol %s already defined\n",iterador2->filho->irmao->linha,iterador2->filho->irmao->coluna,nomeFunc);

				}
					else{
				
				elemento->local=insert_elLocal(nomeFunc,iterador2->filho->string,0,elemento->local);
				}
			
			}
			else{
				recursiva(iterador2,elemento);
			}
			iterador2=iterador2->irmao;

		}
		
	
        }


	iterador=iterador->irmao;
	}
}

void adicionaTipo(char* tipo,nodeDefault *no){
	insertTipo(no->tipos,tipo);


}








