#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splaytree.h"
#include "list.h"

void imprimeNo(NoArv *no){
	printf("%s: %d %d %d\n",no->chave,no->cong,no->des,no->ultVez);
}

int verificaIngredientes(NoPilha **pilha, int tempoTotal){
	static NoArv *raiz = NULL;
	int prontos = 1;
	//Tempo desde o ultimo acesso
	int tps;
	
	//String auxiliar
	char t[50];
	while(*pilha != NULL){
		desempilha(pilha,t);
		insereNo(&raiz,t);
		imprimeNo(raiz);
		tps = tempoTotal- raiz->ultVez;
		raiz->des+=tps;
		if(raiz->ultVez == 0){//Primeira vez que o ingrediente eh acessado
			if(raiz->des > 50){
				raiz->des = 0;//O mesmo que pegar uma nova porcao do congelador
				prontos = 0;//ingrediente indisponivel no momento
			}
		}
	
		if(raiz->ultVez>0){
			raiz->cong+=tps;
			//Troca parte congelada que descongelou por parte que voltou ao congelador
			if(raiz->cong >= 20 && raiz->des > 50){
				raiz->des = raiz->cong;
				raiz->cong = 0;
			}else if (raiz->cong < 20 && raiz->des > 50){
				raiz->des = 0;
				prontos = 0;
			}
		}		
		if(raiz->jaServido && raiz->ultVez == 0)
			raiz->ultVez += tempoTotal;
		else
			raiz->ultVez += tps;
		imprimeNo(raiz);
	}	

	return prontos;
}

Pizza *preparaPizza(int nPedido){
	Pizza *novaPizza = malloc(sizeof(Pizza));

	if (novaPizza == NULL){
		exit(1);
	}
	
	novaPizza->ingredientes = NULL;
	novaPizza->nPedido = nPedido;

	return novaPizza;
}

void entregaPizza(Pizza *pizza){
	printf("%d ",pizza->nPedido);
	//destroiPilha(&(pizza->ingredientes));
	//free(pizza);
	//pizza = NULL;
}

int main(void){
	//Tempo de chegada do cliente, tempo total passado, numero do pedido atual
	int tempo, tempoTotal = 0, nPedido = 0;
	char ingrediente[50];
	Pizza *pizza = NULL;
	NoPilha *lista = NULL;//Lista de ingredientes
	NoFila *filaEspera = NULL;//Fila de espera
	inicializaFila(&filaEspera);

	while(scanf("%d",&tempo) == 1){
		nPedido++;
		tempo *= 10;
		if(tempoTotal == 0){
			tempoTotal += tempo;
		}else if(tempo > tempoTotal){//Proximo cliente demorou mais um pouco para chegar
			tempoTotal += (tempo-tempoTotal);
		}

		pizza = preparaPizza(nPedido);
		while(scanf("%*[ ]%[^ \r\n]", ingrediente) == 1){
			empilha(&(pizza->ingredientes),ingrediente);
			empilha(&lista,ingrediente);
		}

		if(verificaIngredientes(&lista,tempoTotal)){
			//printf("PIZZA SAINDO..\n");
			entregaPizza(pizza);
			lista = NULL;//desempilhou todos os ingredientes da pilha
			tempoTotal+=10;
		}else{
			//printf("F\n");
			enfileirar(&filaEspera,pizza);
		}
		//printf("TT: %d\n",tempoTotal);
	}

	while(!estaVazia(filaEspera)){
		pizza = desenfileirar(&filaEspera);
		if(verificaIngredientes(&(pizza->ingredientes),tempoTotal)){
			entregaPizza(pizza);
			tempoTotal+=10;
		}else{
			enfileirar(&filaEspera,pizza);
		}
	}

	printf("\n");
	return 0;
}
