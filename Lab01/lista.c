#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

No *addLista(No *inicioLista, int valor){
	No *novo;
	novo = malloc(sizeof(No));
	novo->valor = valor;
	novo->prox = NULL;//Ultimo/novo elemento da lista aponta para null

	if(inicioLista == NULL){
		inicioLista = novo;//Primeiro elemento eh o novo
	}else{
		No *atual = inicioLista;
		while(atual->prox != NULL){
			atual = atual->prox;
		}
		atual->prox = novo;//Insere no final
	}
	
	return inicioLista;
}

No *buscaNo(No *inicioLista, No *partida, int valor){
	No *atual;

	//Verifica se o ponto de partida desejado existe na lista
	if(partida == NULL){
		atual = inicioLista;//Caso nao exista a busca iniciara do começo da lista original
	}else{
		atual = partida;
	}

	while(atual!=NULL && atual->valor != valor){
		atual = atual->prox;
	}

	return atual;
}

void imprimeLista(No *inicioLista){
	//Imprime uma lista encadeada simples
	No *atual = inicioLista;
	while(atual != NULL){
		printf(" %d",atual->valor);
		atual = atual->prox;
	}
	printf("\n");
}

void imprimeSubLista(No *ini, No *fim){
	//Imprime uma sublista de uma lista encadeada simples dados seu nós de inicio e fim
	No *atual;
	if(fim != NULL){
		atual = ini;
		while(atual->valor != fim->valor){
			printf(" %d",atual->valor);
			atual = atual->prox;
		}
		printf(" %d",atual->valor);
	} 
	else{
		atual = ini;
		while(atual != NULL){
			printf(" %d",atual->valor);
			atual = atual->prox;
		}
	}

}

void destroiLista(No **inicioLista){
	No *atual = *inicioLista, *aux;
	while(atual!=NULL){
		aux = atual;
		atual = atual->prox;
		free(aux);
	}
}

