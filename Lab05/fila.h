#ifndef FILA_H
#define FILA_H

#include "avltree.h"

typedef struct NoFila{
	NoArv *item;
	struct NoFila *prox;
	struct NoFila *frente;
	struct NoFila *traseira;
	int tam;
}NoFila;

void inicializaFila(NoFila **f);

void enfileirar(NoFila **f, NoArv *novo);

NoArv *desenfileirar(NoFila **f);

int estaVazia(NoFila *f);

#endif
