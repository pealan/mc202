#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

void inicializaFila(NoFila **f){
	*f = malloc(sizeof(NoFila));

	if(*f == NULL){
		exit(1);
	}

	(*f)->frente = (*f)->traseira = NULL;
	(*f)->tam = 0;
}

void enfileirar(NoFila **f, Pizza *pizza){
	NoFila *n = malloc(sizeof(NoFila));

	if(n == NULL){
		exit(1);
	}	

	n->pizza = pizza;
	n->prox = NULL;

	if((*f)->traseira != NULL && (*f)->frente != NULL){
		(*f)->traseira->prox = n;
		(*f)->traseira = n;
	}else{
		(*f)->frente = (*f)->traseira = n;
	}

	(*f)->tam++;
}

Pizza *desenfileirar(NoFila **f){
	NoFila *t;
	Pizza *temp = NULL;
	if((*f)->frente != NULL){
		t = (*f)->frente;

		if((*f)->frente == (*f)->traseira)
			(*f)->frente = (*f)->traseira = NULL;
		else
			(*f)->frente = t->prox;

		temp = t->pizza;
		free(t);
		(*f)->tam--;
	}
	
	return temp;
}

int estaVazia(NoFila *f){
	if(f->frente == NULL && f->traseira == NULL)
		return 1;

	return 0;
}

void destroiFila(NoFila **f){
	//TODO
}

void empilha(NoPilha **topo, char novo[]){
	NoPilha *n = malloc(sizeof(NoPilha));
	//printf("%s\n",novo);
	if(n == NULL){
		exit(1);
	}

	strcpy(n->nome,novo);

	n->prox = *topo;
	*topo = n;
}

void desempilha(NoPilha **topo, char destino[]){
	if(*topo != NULL){
		NoPilha *aux;
		aux = *topo;
		strcpy(destino,aux->nome);
		*topo = aux->prox;
		free(aux);
		aux = NULL;
	}
}

void destroiPilha(NoPilha **topo){
	char c[50];
	while(*topo != NULL){
		desempilha(topo,c);
	}
	topo = NULL;
}
