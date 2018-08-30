#include <stdio.h>
#include <string.h>
#include "system.h"

void touch(NoArv **raiz, char filename[]){
	int flag = 0;
	insere(raiz,filename,&flag);
	//imprimeInOrdem(*raiz);
	//imprimePorLargura(*raiz);
}

void rm(NoArv **raiz,char expressao[]){
	//Sem prefixo = apagar todos os arquivos
	if(expressao[0] == '*'){
		destroiArvore(*raiz);
		return;
	}

	int existe = 0;
	removeIntervalo(raiz,expressao,&existe);

	if(!existe){
		printf("nao existem arquivos com essa expressao\n");
	}

	//imprimePorLargura(*raiz);
}

void ls(NoArv **raiz, char expressao[]){
	//Sem prefixo = listar todos os arquivos
	if(expressao[0] == '*'){
		imprimeInOrdem(*raiz);
		return;
	}


	int existe = 0; 
	imprimeIntervalo(*raiz,expressao,&existe);
	
	if(!existe){
		printf("nao existem arquivos com essa expressao\n");
	}
}

void central(char op[], char expressao[]){
	//Inicializa arvore com valor null
	static NoArv *arvore = NULL;

	if(strcmp(op,"touch") == 0)
		touch(&arvore,expressao);	
	else if(strcmp(op,"rm") == 0)
		rm(&arvore,expressao);	
	else if(strcmp(op,"ls") == 0)
		ls(&arvore,expressao);
	else if(strcmp(op,"shutdown") == 0)
		destroiArvore(arvore);
}

