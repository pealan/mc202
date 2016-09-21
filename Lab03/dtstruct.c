#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dtstruct.h"

void empilha(NoPilha **topo, int novo){
	NoPilha *n = malloc(sizeof(NoPilha));

	if(n == NULL){
		exit(1);
	}

	n->id = novo;
	n->azuis = 0;

	n->prox = *topo;
	*topo = n;
}

int desempilha(NoPilha **topo){
	int t = 0;
	if(*topo != NULL){
		NoPilha *aux;
		aux = *topo;
		t = aux->id;
		*topo = aux->prox;
		free(aux);
	}

	return t;
}

int addOrdLista(NoLista **inicioLista, int id, char cor[]){
	NoLista *novo;
	int situ = 1;
	novo = malloc(sizeof(NoLista));

	if(novo == NULL){//Checa se conseguiu alocar
		exit(1);
	}

	novo->id = id;
	strcpy(novo->cor,cor);

	if(*inicioLista == NULL){
		novo->antes = NULL;
		novo->prox = NULL;
		*inicioLista = novo;//Primeiro elemento eh o novo
	}else{//Guarda em ordem crescente
		NoLista *atual = *inicioLista;
		while(atual->prox != NULL && atual->id < novo->id){
			atual = atual->prox;
		}

		if(atual->id == novo->id){
			if(atual->cor[0] != novo->cor[0]){//basta a primeira letra
				situ = 0;//bonecas com id igual tem que ter cor igual
			}else{
				free(novo);//nao insere na lista valores repetidos
			}
		}else{
			if(atual->antes == NULL && atual->id > novo->id){//Poe no inicio
				novo->antes = NULL;
				novo->prox = atual;
				atual->antes = novo;
				*inicioLista = novo;
			}else if(atual->id > novo->id){//Poe no "meio"
				novo->prox = atual;
				novo->antes = atual->antes;
				atual->antes->prox = novo;
				atual->antes = novo;
			}else if(atual->prox == NULL){//Poe no final
				novo->prox = NULL;
				novo->antes = atual;
				atual->prox = novo;
			}
		}
	}

	return situ;
}

void imprimeLista(NoLista *inicioLista){
	NoLista *atual = inicioLista;
	while(atual != NULL){
		printf("%d: %s\n",atual->id,atual->cor);
		atual = atual->prox;
	}
}

void destroiLista(NoLista **inicioLista){
	NoLista *atual = *inicioLista, *aux;
	while(atual!=NULL){
		aux = atual;
		atual = atual->prox;
		free(aux);
	}
}
