#include <stdlib.h>
#include "fila.h"

void inicializaFila(NoFila **f){
	*f = malloc(sizeof(NoFila));
	(*f)->frente = (*f)->traseira = NULL;
	(*f)->tam = 0;
}

void enfileirar(NoFila **f, NoArv *novo){
	NoFila *n = malloc(sizeof(NoFila));
	n->item = novo;
	n->prox = NULL;

	if((*f)->traseira != NULL && (*f)->frente != NULL){
		(*f)->traseira->prox = n;
		(*f)->traseira = n;
	}else{
		(*f)->frente = (*f)->traseira = n;
	}

	(*f)->tam++;
}

NoArv *desenfileirar(NoFila **f){
	NoFila *t;
	NoArv *temp = NULL;
	if((*f)->frente != NULL){
		t = (*f)->frente;

		if((*f)->frente == (*f)->traseira)
			(*f)->frente = (*f)->traseira = NULL;
		else
			(*f)->frente = t->prox;

		temp = t->item;
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

