#include <stdio.h>
#include "heap.h"

int esq(int i){
	return 2*i + 1;
}

int dir(int i){
	return 2*i+2;
}

int pai(int i){
	return (i-1)/2;
}

void troca(Heap *fila,Item *a, Item *b){
	int tempId = a->id, tempProx = a->prox, tempPos = a->pos;

	if(a->pos == fila->menor){
		fila->menor = b->pos; 
	}else if(b->pos == fila->menor){
		fila->menor = a->pos;
	}

	a->id = b->id;
	a->prox = b->prox;
	a->id = b->id;
	b->id = tempId;
	b->prox = tempProx;
	b->pos = tempPos;
}

void desce(Heap *fila, int i){
	int maior = i;
	int e = esq(i), d = dir(i);	

	
	if(d < fila->tam && fila->v[d].prox > fila->v[i].prox){
		maior = d;
	}

	if(e < fila->tam && fila->v[e].prox >= fila->v[maior].prox){
		maior = e;
	}
	
	if(i != maior){
		troca(fila,&fila->v[i], &fila->v[maior]);
		desce(fila, maior);
	}
}

int sobe(Heap *fila, int i){
	int p = pai(i);

	if(i != 0 && fila->v[i].prox > fila->v[p].prox){
		troca(fila,&fila->v[i], &fila->v[p]);
		return sobe(fila,p);
	}
	
	return fila->v[i].pos;
}

void inserir(Heap *fila, Item x){
	x.pos = fila->tam;	
	fila->v[fila->tam] = x;
	int posColocada = sobe(fila,fila->tam);

	if(fila->v[posColocada].prox < fila->v[fila->menor].prox){
		fila->menor = posColocada;
	}

	fila->tam++;
	
}

void aumentaPrioridade(Heap *fila, int i, int x){
	fila->v[i].prox = x;
	sobe(fila,i);
	int proxMenor = fila->v[fila->tam-1].prox;
	int j;
	for (j = fila->tam-1;esq(j) > fila->tam && dir(j)>fila->tam;j--){
		if(fila->v[j].prox < proxMenor){
			proxMenor = fila->v[j].prox;
		}
	}
	fila->menor = j;
}

void diminuiPrioridade(Heap *fila, int i, int x){
	fila->v[i].prox = x;
	desce(fila,i);
}

Item removerMax(Heap *fila){
	Item max = fila->v[0];
	fila->v[0].prox = fila->v[fila->tam-1].prox;
	fila->v[0].id = fila->v[fila->tam-1].id;
	fila->tam--;
	desce(fila, 0);
	
	return max;
}


