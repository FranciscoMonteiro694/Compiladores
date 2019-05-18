#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"tabelas.h"

//To do
//1.Ver melhor a diferença entre as variaveis e funcoes quando se encontram ids e tamos a fazer a AST



//lex gocompiler.l && yacc -d gocompiler.y && cc -o f5 lex.yy.c y.tab.c tabelas.c 

extern elemento_tabelag* tg;//tabela global

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
//funcao que dada  a tabela local insere um elemento nessa mesma lista
//recebe os atributos de cada elemento da lista e a propria "lista"
//retorna o ponteiro para o inicio da lista
elemento_tabelal *insert_elLocal(char *str, char* t,int param,elemento_tabelal * lista_local){
	elemento_tabelal *newSymbol=(elemento_tabelal*) malloc(sizeof(elemento_tabelal));//alocaçao do elemento da lista local
	elemento_tabelal *aux;
	elemento_tabelal *previous;
	
	strcpy(newSymbol->name, str);//inserir o id no novo elemento da lista local
	if(strcmp(t,"Int")==0){//atribuiçao do tipo ao elemento a inserir na lista
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
	newSymbol->param=param;//atribuir o param,que quando a 0 quer dizer que nao é um parametro de uma fuçao/tabela local
	newSymbol->next=NULL;
	if(lista_local)	//Se table ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe
		for(aux=lista_local; aux; previous=aux, aux=aux->next)//a condiçao de paragem é o aux ser null
			if(strcmp(aux->name, str)==0)
				return NULL;//ja existe um igual(identificador) erro<--------------------------------------
		previous->next=newSymbol;	//adiciona ao final da lista
	}
	else//a lista encontra-se vazia
		lista_local=newSymbol;	
	//retorna um ponteiro para o inicio da lista	
	return lista_local;
}

//O no(ou ramo da arvore) que vai receber vai ser o FuncParams, temos de aceder aos netos
//É do genero funcparams->paramDecl->(Tipo e id) e pode ter varios paramDecl ou seja varios parametros
void insertTipos(char *funcNam, nodeDefault *no){
	nodeDefault *auxP,*auxF;
	elemento_tabelag *auxt;
	auxP=no;
	auxP=auxP->filho; //ParamDecl, cujo os irmao sao tambem ParamDecl
	auxF=auxP->filho; //Primeiro tipo do primeirp parametro da funcao
	auxt = search_el(funcNam);//procura o elemento na tabela devolve null ou a propria entrada da tabel (elemento da lista)
	auxt->tipos=insertTipo(auxt->tipos,auxF->string);//insere o tipo do parametro na lista de tipos da tabela global
	while(auxP->irmao!=NULL){//repete o processo para os outros parametros
		auxP=auxP->irmao;
		auxF=auxP->filho;
		auxt->tipos=insertTipo(auxt->tipos,auxF->string);
	}
}

/* Recebe a lista de tipos e insere um novo tipo na cauda*/
//Retorna um ponteiro para o inicio da lista de tipos
noTipo *insertTipo2(noTipo *tipos,type tipo){
	noTipo *iterador;
	noTipo *novo;
	novo=malloc(sizeof(noTipo));
	iterador=tipos;
	novo->tipo=tipo;
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

/* Recebe a lista de tipos e insere um novo tipo na cauda,so que desta vez o tipo e convertido de string para type*/
noTipo *insertTipo(noTipo *tipos,char *tipoo){
	noTipo *iterador;
	noTipo *novo;
	novo=malloc(sizeof(noTipo));
	iterador=tipos;
	//converçao de string para type
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
//funçao que impime a tabela global e locais
void imprime_tabelaGlobal()
{
	printf("===== Global Symbol Table =====");
	elemento_tabelag *aux;
	printf("\n");
	//vamos percorrer todos os elementos da tabela global usando um ponteiro auxiliar
	for(aux=tg; aux; aux=aux->next){
		printf("%s\t",aux->name);
		if(aux->funcao==1){//caso seja uma funçao e necessarios por entre parentises os tipos de parametros
			printf("(");
			imprimeTipos(aux);
			printf(")");
		}
		//impressao do tipo de retorno de uma funçao ou o tipo de uma variavel(So ha esa duas hipotses visto que as tabelas contem apenas variveis e funçoes)
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
		printf("\n");//acho que é inutil XD
	}
	printf("\n");
	//percorrer outra vez a tabela global para aceder ao ponteiro de cada funcao a sua repetiva tabela local
	for(aux=tg; aux; aux=aux->next){
		if(aux->local!=NULL){//so acontecera no caso das funcoes
			imprime_tabelaLocal(aux->local,aux->name);
		}
	}
}
//converçao do type para uma string
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
//funcao que com o ponteiro para a tabela local e o nome da funçao, imprime a tabela no formato respetivo
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
//impriem os tipos de um dos elementos da tabela global(variavel ou funçao)
void imprimeTipos(elemento_tabelag *tabela){
	noTipo *iterador;
	iterador=tabela->tipos;
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



//Procura um identificador, devolve 0 caso nao exista(Para os erros)
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

// Para tirar o "id()" da string
//Ex:id(ola)---> ola
char * tiraId(char *str){
    char *aux,*aux2;
    aux2 = (char*)malloc(sizeof(char)*300);
    strcpy(aux2,str);
    aux = (char*)malloc(sizeof(char)*300);
    const char s[2] = "(";
    aux=strtok(aux2,s);
    aux= strtok(NULL,s);
    aux[strlen(aux)-1]='\0';
    return aux;
}
//Dado um no do tipo FuncDecl adiciona a tabela global uma nova entrada para esta funcao com os seus tipos parametros e tipo de retorno
//retorna o ponteiro para o inicio da tabela global 
elemento_tabelag* insertFuncaoT(nodeDefault *no){// FuncDecl
	// Insere o nome da função na tabela global
	// Se tiver tipo de retorno
	elemento_tabelag* newel;
	nodeDefault *aux;
	aux=no->filho->filho;//Nome da função
	char * nomeFunc;
	nomeFunc=(char*)malloc(sizeof(char)*50);
	strcpy(nomeFunc,tiraId(aux->string));
	if (checkHasReturn(aux)==1){//funcao que ve se a funcDecl retorna algum tipo de valor
		newel=insert_el(nomeFunc,aux->irmao->string,1);
		aux=aux->irmao;
		aux=aux->irmao;
	}
	else{//caso nao retorne nada
		newel=insert_el(nomeFunc,"none",1);
		aux=aux->irmao;

	}
	if(aux->filho!=NULL){ // Se a função tiver parâmetros
		insertTipos(nomeFunc, aux);
	}
	return newel;
}
//Recebe um no do tipo VarDecl(Global) e insere-o na tabela global
//retorna o ponteiro para o inicio da tabela global 
elemento_tabelag* insertVarD(nodeDefault *no){
	nodeDefault *aux=no;
	elemento_tabelag* newel;
	char*nomeFunc;
	nomeFunc=(char*)malloc(sizeof(char)*50);
	strcpy(nomeFunc,tiraId(aux->filho->irmao->string));//nome da variavel
	newel=insert_el(nomeFunc,aux->filho->string,0);//aux->filho é o tipo da variavel
	return newel;
}
//recebe um no do tipo FuncDec e a sua entrada na tabela global
//funcao que dado o ponteiro para um elemento da tabela global,cria a tabela Local para esta funcao,e adiciona para os nos desta funcao os tipos á AST
void criaLocal(nodeDefault *no,elemento_tabelag * elemento){
    nodeDefault *iterador,*iterador2,*iterador3;
    iterador=no->filho;
    while(iterador!=NULL){
	//vai ver o header da funcao se tem parametros
	if(strcmp(iterador->string,"FuncHeader")==0){
		if(strcmp(iterador->filho->irmao->string,"FuncParams")!=0){//esta funcao retorna algo do tipo iterador->filho->irmao->string
			//adicionar o tipo de retorno
			elemento->local=insert_elLocal("return",iterador->filho->irmao->string,0,elemento->local);
			iterador3=iterador->filho->irmao->irmao->filho;
			while(iterador3!=NULL){//meter os parametos da funcao
				char*nomeFunc;
				nomeFunc=(char*)malloc(sizeof(char)*50);
				strcpy(nomeFunc,tiraId(iterador3->filho->irmao->string));
				elemento->local=insert_elLocal(nomeFunc,iterador3->filho->string,1,elemento->local);
				iterador3=iterador3->irmao;
			}
		}
		else{//Nao existe tipo de return
			elemento->local=insert_elLocal("return","none",0,elemento->local);
			iterador3=iterador->filho->irmao->filho;
			while(iterador3!=NULL){//adicionar os tipos dos parametros
				char*nomeFunc;
				nomeFunc=(char*)malloc(sizeof(char)*50);
				strcpy(nomeFunc,tiraId(iterador3->filho->irmao->string));
				elemento->local=insert_elLocal(nomeFunc,iterador3->filho->string,1,elemento->local);
				iterador3=iterador3->irmao;
				}
			}
        }
	if(strcmp(iterador->string,"FuncBody")==0){
		//Procurar no body por VarDecl
		iterador2=iterador->filho;
		while(iterador2!=NULL){
			if(strcmp(iterador2->string,"VarDecl")==0){
				//adicionar a tabela local da funcao uma variavel
				char*nomeFunc;
				nomeFunc=(char*)malloc(sizeof(char)*50);
				strcpy(nomeFunc,tiraId(iterador2->filho->irmao->string));
				elemento->local=insert_elLocal(nomeFunc,iterador2->filho->string,0,elemento->local);
			
			}
			else{
				//Tando no Body da funcao ir a procura de nos terminais e ids e atribuir-lhes tipos para fazer a AST
				recursiva(iterador2,elemento);
			}
			iterador2=iterador2->irmao;
		}
        }
	iterador=iterador->irmao;
	}
}

/*-------------------------------------------------------------------------------------------*/


//Recebe a raiz da Arvore,Program e com auxilio de varias funcoes "intermedias",forma todas as tabelas,locais e global,assim como a AST
int criaTabelas(nodeDefault *raiz){
    nodeDefault *iterador;
    elemento_tabelag * aux;
    iterador=raiz->filho;
    while(iterador!=NULL){
    //Um programa resume-se a Funcoes e Variaveis
    if(strcmp(iterador->string,"FuncDecl")==0){
	//Inserir a funcao na tabela global e criar a sua tabela local
        aux=insertFuncaoT(iterador);
        criaLocal(iterador,aux);
        }
    if(strcmp(iterador->string,"VarDecl")==0){
	//Variaveis sao mais simples(Nao ha ca tabelas locais)
        insertVarD(iterador);
        }
    iterador=iterador->irmao;
    }
    return 0;

}

//Recebe um no da arvore
//Funcao que percorre recursivamente uma arvore conforme certos nos atribui-lhes certos tipos
int recursiva(nodeDefault *no,elemento_tabelag * elemento){
    nodeDefault *aux;
    int flag=0;
    if(strcmp(no->string,"Call")==0){//chamada de funçoes e um caso especial
        flag=1;
    }
    aux=no->filho; 
    if(aux==NULL){
        return 0;   
    }
    //VarDecl nao importam para nada nas AST------>acho que nao é preciso, melhorar AQUI
    if(strcmp(aux->string,"VarDecl")==0){
	while(strcmp(aux->string,"VarDecl")==0){
		aux=aux->irmao;
	}
        
    }
    //percorrer os irmaos do no atual de maneira recursiva
    while(aux!=NULL){
	if(strcmp(aux->string,"VarDecl")!=0){
		checkaTerminais(aux,elemento,flag);
		recursiva(aux,elemento);
	}
        aux=aux->irmao;
        flag=0;
    }

    //ao subir na arvore atraves da recursividade ver se o no é de um tipo especial para deteçao de erros etc
    if(strcmp(no->string,"Eq")==0){
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Or")==0){
	//printf("OR percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"And")==0){
	// printf("AND percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
       
    }
    if(strcmp(no->string,"Ne")==0){
	//printf("NE percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Lt")==0){
	 //printf("LT percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
       
    }
    if(strcmp(no->string,"Gt")==0){
	//printf("GT percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Le")==0){
	//printf("LE percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Ge")==0){
	//printf("GE percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,boolean);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Add")==0){
	//printf("ADD percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Sub")==0){
	 //printf("SUB percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
       
    }
    if(strcmp(no->string,"Mul")==0){
	//printf("MUL percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Div")==0){
	//printf("DIV percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Mod")==0){
	//printf("MOD percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Not")==0){
	//printf("NOT percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Minus")==0){
	//printf("MINUS percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
     
    }
    if(strcmp(no->string,"Plus")==0){
	//printf("PLUS percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    if(strcmp(no->string,"Assign")==0){
	//printf("ASSIGN percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
    }
	//rever---------------------------------------------------------------
    if(strcmp(no->string,"Call")==0){
	//printf("CALL percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,percorreTabelaGlobal2(no->filho->string));
	/*if(no->filho->tipos!=NULL){
		no->tipos=insertTipo2(no->tipos,percorreTabelaGlobal2(no->filho->string));
	}
	else{
	no->tipos=insertTipo2(no->tipos,percorreTabelaGlobal2(no->filho->string));
	}*/
        //percorrer filho ja com o tipo e depois meter o tipo
    }
    if(strcmp(no->string,"ParseArgs")==0){
	//printf("PARSE ARGS percorrer filho ja com o tipo e depois meter o tipo\n");
	no->tipos=insertTipo2(no->tipos,no->filho->tipos->tipo);
        //percorrer filho ja com o tipo e depois meter o tipo
        
    }
    return 0;
    }
//Funcao que atribui tipos aos nos "Terminais" na AST
//A flag apenas indica se o nó anterio,ou melhor dizendo pai,for um no do tipo call que nesto caso sera tratado de maneira diferente
//elemento é um pinteiro para o elemento da tabela global que tamos a analisar
void checkaTerminais(nodeDefault *no,elemento_tabelag * elemento,int flag){
    char* aux;
    aux=no->string;
    if(strncmp("Id",aux,strlen("Id"))==0){
        if(flag==1){//Se o id que encontramos tiver como pai uma call,quer dizer que é o nome de uma funcao, e que os seus tipos de parametros teram na tabela global
		 no->tipos=percorreTabelaGlobal(aux);
		 //erros de funcoes nao declaradas
        }
        else{
	     //apenas um id de uma variavel
	     no->tipos=insertTipo2(no->tipos,percorreTabela(aux,elemento));//percorrer primeiro a tabela local, e em seguida a global
	     //erro de variavel nao declarada
        }
    }
    //terminais
    if(strncmp("IntLit",aux,strlen("IntLit"))==0){
	no->tipos=insertTipo(no->tipos,"Int");
    }
    if(strncmp("RealLit",aux,strlen("RealLit"))==0){
	no->tipos=insertTipo(no->tipos,"Float32");
    }
    if(strncmp("StrLit",aux,strlen("StrLit"))==0){
	no->tipos=insertTipo(no->tipos,"String");
    }
    }
//retorna os tipos dos parametros de um elemento (Funcao) da tabela global com id str, ou entao null caso nao encontre
noTipo* percorreTabelaGlobal(char* str){
    elemento_tabelag * aux;
    char* auxS;
    aux=tg;
    noTipo* hmmm;
    hmmm=NULL;
    auxS=(char*)malloc(sizeof(char)*100);
    auxS=tiraId(str);
    while(aux){
        if(strcmp(aux->name,auxS)==0){
            return aux->tipos;
        }
        aux=aux->next;     
    }
   return hmmm;
}
//retorna os tipo de retorno de um elemento (Funcao) da tabela global com id str, ou entao null caso nao encontre
type percorreTabelaGlobal2(char* str){
    elemento_tabelag * aux;
    char* auxS;
    aux=tg;
    auxS=(char*)malloc(sizeof(char)*100);
    auxS=tiraId(str);
    while(aux){
        if(strcmp(aux->name,auxS)==0){
            return aux->tipo;
        }
        aux=aux->next;     
    }
	return none;
}
//funcao que vai procurar uma variavel na tabela local e caso nao encotre procura na tabela global
//retorna o tipo da variavel
type percorreTabela(char* str,elemento_tabelag * elemento){
    elemento_tabelag * aux;
    elemento_tabelal * aux2;
    char* auxS;
    aux=tg;
    auxS=(char*)malloc(sizeof(char)*100);
    auxS=tiraId(str);
    aux=tg;
    aux2=elemento->local;
    while(aux2){    
        if(strcmp(aux2->name,auxS)==0){
            return aux2->tipo;
        }
        aux2=aux2->next;    
    }
        while(aux){
        if(strcmp(aux->name,auxS)==0){
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
	//dar double check-------------------------------------------------------------------------AQUI
	if(strcmp(raiz->string,"Call")==0&&raiz->tipos->tipo==none){
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





