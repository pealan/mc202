#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

int addLista(No **inicioLista, int valor, int tipo){
	No *novo;
	novo = malloc(sizeof(No));
	int c = 1;

	if(novo == NULL){
		exit(0);
	}

	novo->valor = valor;	

	if(*inicioLista == NULL){
		novo->antes = NULL;
		novo->prox = NULL;
		*inicioLista = novo;//Primeiro elemento eh o novo
	}else{
		No *atual = *inicioLista;
		while(atual->prox != NULL){
			atual = atual->prox;
			c++;
		}

		if (tipo == 1){//MTF		
			atual->prox = novo;//Insere no final
			novo->antes = atual;
			novo->prox = NULL;
		}else if (tipo == 2){//TR
			if(atual->antes == NULL){//Lista com um elemento
				novo->prox = atual;
				novo->antes = NULL;
				atual->prox = NULL;
				atual->antes = novo;
				*inicioLista = novo;//Primeiro elemento eh o novo
			}else{
				//Antepenultimo aponta para o novo elemento
				atual->antes->prox = novo;

				//Novo elemento eh o penultimo			
				novo->prox = atual;
				novo->antes = atual->antes;

				//Penultimo agora eh o ultimo
				atual->antes = novo;
				atual->prox = NULL;
			}
		}
		c++;
	}
	
	return c;
}

No *copiaLista(No *original){
	No *atual = original, *novo, *copia = NULL,*ant = NULL;

	while(atual != NULL){
		novo = malloc(sizeof(No));

		if(novo == NULL){
			exit(0);
		}

		novo->valor = atual->valor;
		novo->prox = NULL;
		
		if(ant != NULL){
			novo->antes = ant;//Novo elemento aponta para o ultimo salvo
			ant->prox = novo;//Ultimo elemento salvo aponta para o novo
		}else{
			novo->antes = NULL;
			copia = novo;//primeiro elemento da lista
		}

		ant = novo;//Guarda ultimo elemento salvo
		atual = atual->prox;		
	}

	return copia;	
}

int acessaNo(No **inicioLista, int valor, int tipo){
	No *atual = *inicioLista;
	int c = 1;

	while(atual!=NULL && atual->valor != valor){
		atual = atual->prox;
		c++;
	}

	if(atual == NULL){
		//Mensagem?
		return c;//Custo de nao achar o valor eh percorrer toda a lista
	}
	
	int aux;
	if(atual->antes != NULL){//Nao eh o primeiro elemento da lista
		if(tipo == 1){//MTF
			atual->antes->prox = atual->prox;
			
			if(atual->prox != NULL)
				atual->prox->antes = atual->antes;

			(*inicioLista)->antes = atual;
			atual->prox = (*inicioLista);
			atual->antes = NULL;
			(*inicioLista) = atual;
		}else if(tipo == 2){//TR
			aux = atual->valor;
			atual->valor = atual->antes->valor;
			atual->antes->valor = aux;
		}
	}
			
	return c;
}

int removeNo(No **inicioLista,int valor){
	No *atual = *inicioLista;
	int c = 1;

	while(atual!=NULL && atual->valor != valor){
		atual = atual->prox;
		c++;
	}

	if(atual == NULL){
		//Mensagem?
		return c;
	}

	if(atual->antes !=NULL && atual->prox != NULL){//Esta no meio da lista
		atual->antes->prox = atual->prox;
		atual->prox->antes = atual->antes;
	}else if (atual->antes == NULL && atual->prox!=NULL){//Cabeca da lista
		atual->prox->antes = NULL;
		*inicioLista = atual->prox;
	}else if(atual->antes !=NULL && atual->prox == NULL){//fim de lista com mais de um
		atual->antes->prox = NULL; 
	}else{//Lista com um elemento
		*inicioLista = NULL;
	}
	
	free(atual);

	return c;
}

void imprimeLista(No *inicioLista){
	//Imprime uma lista encadeada simples
	No *atual = inicioLista;
	while(atual != NULL){
		printf("%d ",atual->valor);
		atual = atual->prox;
	}

	printf("\n");
}

void destroiLista(No **inicioLista){
	No *atual = *inicioLista, *aux;
	while(atual!=NULL){
		aux = atual;
		atual = atual->prox;
		free(aux);
	}
}

