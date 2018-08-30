#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(void){
	int c,n,a,*acessos,*cache;
	Heap *heap = NULL;
	scanf("%d %d %d",&c,&n,&a);

	acessos = malloc(a*sizeof(int));

	//Cria fila
	heap = malloc(sizeof(Heap));
	heap->v = malloc(c*sizeof(Item));

	//Cria cache
	cache = malloc(n*sizeof(int));

	//Le os acessos
	int i;
	for(i = 0; i < a; i++)
		scanf("%d", &acessos[i]);
	
	int itensCache = 0, itemAtual,j, prox;
	int solucao = 0;
	Item max,novo;
	for(i = 0; i<a; i++){
		itemAtual = acessos[i];
		prox = 200000;

		//Busca pelo proximo tempo de acesso
		for(j = i+1; j<a; j++){
			if(acessos[j] == itemAtual){
				prox = j;
				break;
			}
		}
			
		if(cache[itemAtual] == 0){
			novo.prox = prox;
			novo.id = itemAtual;
			//Se o cache esta cheio, retira o elemento com maior prioridade da fila e do cache
			if(itensCache >= c){
				max = removerMax(heap);
				cache[max.id] = 0;
			}else{
				//Caso não esteja, soma o contador do cache
				itensCache++;
			}
			inserir(heap,novo);
			cache[itemAtual] = 1;
			//Soma a solucao/acesso
			solucao++;
		}else{
			aumentaPrioridade(heap,heap->menor,prox);
		}
		//printf("MENOR: %d\n",heap->menor);
	}	
	
	printf("%d\n",solucao);
	return 0;
}
