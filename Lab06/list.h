#include "splaytree.h"

#ifndef FILA_H
#define FILA_H

//Pilha com os ingredientes
typedef struct NoPilha{
	char nome[50];
	struct NoPilha *prox;
}NoPilha;

typedef struct{
	NoPilha *ingredientes;
	int nPedido;
}Pizza;

typedef struct NoFila{
	Pizza *pizza;
	struct NoFila *prox;
	struct NoFila *frente;
	struct NoFila *traseira;
	int tam;
}NoFila;

//Funcoes da fila
void inicializaFila(NoFila **f);

void enfileirar(NoFila **f, Pizza *pizza);

Pizza *desenfileirar(NoFila **f);

int estaVazia(NoFila *f);

void destroiFila(NoFila **f);

//Funcoes da pilha
void empilha(NoPilha **topo, char novo[]);

void desempilha(NoPilha **topo, char destino[]);

void destroiPilha(NoPilha **topo);


#endif
