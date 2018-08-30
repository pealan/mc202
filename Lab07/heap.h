#ifndef HEAP_H
#define HEAP_H
typedef struct{
	int prox;
	int id;
	int pos;
}Item;

typedef struct{
	Item *v;
	int tam;
	int menor;//Posicao do menor elemento
}Heap;

void inserir(Heap *fila, Item x);

void aumentaPrioridade(Heap *fila, int i, int x);

void diminuiPrioridade(Heap *fila, int i, int x);

Item removerMax(Heap *fila);

#endif
