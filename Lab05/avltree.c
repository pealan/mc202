#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avltree.h"
#include "fila.h"

int like(char chave[], char prefix[]){
	int i, ehProximo  = 1;
	for (i = 0; prefix[i] != '*' && chave[i] != '\0'; i++){
		if(prefix[i] != chave[i]){
			ehProximo = 0;
			break;
		}
	}

	return ehProximo;
}

void rodarDireita(NoArv **r){
	//"b" eh em torno de quem vamos rotacionar
	NoArv *a, *b;
	b = *r;
	a = b->esq;

	//Troca ponteiros
	*r = a;
	b->esq = a->dir;
	a->dir = b;
}

void rodarEsquerda(NoArv **r){
	//"a" eh em torno de quem vamos rotacionar
	NoArv *a, *b;
	a = *r;
	b = a->dir;

	//Troca ponteiros
	*r = b;
	a->dir = b->esq;
	b->esq = a;
}

int insere(NoArv **r, char novo[], int *flag){
	int ordem, aumentou, novoFb;
	//Quando insere em arvore vazia o fb eh 0
	if (*r == NULL){
		*r = malloc(sizeof(NoArv));
		strcpy((*r)->chave, novo);
		(*r)->qtd = 1;
		(*r)->fb = 0;
		return 1;
	}

	ordem = strcmp((*r)->chave, novo);

	if (ordem == 0){//Insere no mesmo no(aumenta quantidade)
		(*r)->qtd++;
		return 0;
	}else if (ordem<0){//insere na direita
		aumentou = insere(&((*r)->dir), novo,flag);

		if(!aumentou) return 0;

		if((*r)->fb == 1 && (*r)->dir->fb == 1){//Desbalanceada positivamente
			(*r)->fb = 0;
			(*r)->dir->fb = 0;
			rodarEsquerda(r);
			*flag = 0;
			return 0;
		}

		if((*r)->fb == -1 || (*r)->fb == 0){//Insere em subarvore menor ou da mesma altura
			(*r)->fb++;

			if((*r)->dir == NULL || (*r)->esq == NULL){//aumentou em 1 o nivel dessa arvore
				(*flag) = 1;
				return 1;
			}
				
			if((*r)->fb == 0){//Normalizou
				*flag = 0;
				return 0;
			}
				
			if((*flag))
				return 1; 

			return 0;
		}

		if ((*r)->fb == 1 && (*r)->dir->fb == -1){//Subarvore balanceada negativamente
			*flag = 0;
			novoFb = (*r)->dir->esq->fb;

			if (novoFb == 1){//No colocado a direita de C
				(*r)->fb = -1;
				(*r)->dir->fb = 0;
			}else if (novoFb == -1){//No colocado a esquerda de C
				(*r)->fb = 0;
				(*r)->dir->fb = 1;
			}
			
			//Roda B para a direita
			rodarDireita(&(*r)->dir);
			//Roda A para a esquerda
			rodarEsquerda(r);
			
			(*r)->fb = 0;//Raiz agora tem fb = 0
			return 0;
		}
	}else{//Insere na esquerda
		aumentou = insere(&((*r)->esq), novo,flag);

		if(!aumentou) return 0;

		//Operacoes simetricas a insercao a direita
		if((*r)->fb == -1 && (*r)->esq->fb == -1){
			(*r)->fb = 0;
			(*r)->esq->fb = 0;
			rodarDireita(r);
			*flag = 0;
			return 0;
		}else if((*r)->fb == 1 || (*r)->fb == 0){
			(*r)->fb--;

			if((*r)->dir == NULL || (*r)->esq == NULL){
				(*flag) = 1;
				return 1;
			}

			if((*r)->fb == 0){//Normalizou
				*flag = 0;
				return 0;
			}

			if((*flag))
				return 1;

			return 0;
		}else if ((*r)->fb == -1 && (*r)->esq->fb == 1){
			*flag = 0;
			novoFb = (*r)->esq->dir->fb;

			if (novoFb == -1){//No colocado a direita de C
				(*r)->fb = 1;
				(*r)->esq->fb = 0;
			}else if (novoFb == 1){//No colocado a esquerda de C
				(*r)->fb = 0;
				(*r)->esq->fb = -1;
			}
				
			//Roda B para a esquerda
			rodarEsquerda(&(*r)->esq);
			//Roda A para a esquerda
			rodarDireita(r);

			(*r)->fb = 0;//Raiz agora tem fb = 0
			return 0;
		}
	}
	
	return 0;
}

void buscaIntervalo(NoArv **r, NoPilha **pilha, char prefix[]){
	if (r == NULL) return;

	if(strcmp((*r)->chave,prefix)>0){
		buscaIntervalo(&(*r)->esq,pilha,prefix);
	}

	if(like((*r)->chave,prefix)){
		empilha(pilha, r);
	}
	
	if(strcmp((*r)->chave,prefix)<0){
		buscaIntervalo(&(*r)->dir,pilha,prefix);
	}	
}

void removeCaso1(NoArv **r){
	//rem aponta pra um no com uma subarvore vazia
	NoArv *rem;
	rem = *r;

	//
	if(rem->esq == NULL){
		*r = rem->dir;
	}else{
		*r = rem->esq;
	}

	free(rem);
}

void removeCaso2(NoArv *rem){
	NoArv **suc;
	
	//Procura sucessor
	suc = &(rem->dir);
	while ((*suc)->esq != NULL){
		suc = &((*suc)->esq);
	}

	strcpy(rem->chave,(*suc)->chave);

	removeCaso1(suc);
}

void removeIntervalo(NoArv **r, char prefix[], int *existe){
	if(r != NULL){
		//Verifica se a raiz da subarvore da esquerda contem o prefixo e a percorre
		if((*r)->esq != NULL && (strcmp((*r)->esq->chave,prefix)>0 || like((*r)->esq->chave,prefix))){
			removeIntervalo(&(*r)->esq,prefix,existe);
		}
	
		//Remove enquanto a chave da raiz tiver o prefixo
		while(like((*r)->chave,prefix)){
			*existe = 1;
			if(strcmp((*r)->chave, prefix) == 0){
				if((*r)->qtd>1)				
					(*r)->qtd--;
				else{
					if ((*r)->dir == NULL || (*r)->esq == NULL)
						removeCaso1(r);
					else
						removeCaso2(*r);
				}
				return;
			}

			if ((*r)->dir == NULL || (*r)->esq == NULL)
				removeCaso1(r);
			else
				removeCaso2(*r);
			
		}

		//Verifica se a raiz da subarvore da esquerda contem o prefixo e a percorre
		if((*r)->dir != NULL && (strcmp((*r)->esq->chave,prefix)>0 || like((*r)->esq->chave,prefix))){
			removeIntervalo(&(*r)->dir,prefix,existe);
		}
	}
}

void imprimeInOrdem(NoArv *r){
	int i;
	if(r != NULL){
		imprimeInOrdem(r->esq);
		for (i = 0; i< r->qtd; i++){
			printf("%s\n",r->chave);
		}
		imprimeInOrdem(r->dir);
	}
}

void imprimeIntervalo(NoArv *r, char prefix[], int *existe){
	int i;
	if(r != NULL){
		//Verifica se a raiz da subarvore da esquerda contem o prefixo e a percorre
		if(r->esq != NULL && (strcmp(r->esq->chave,prefix)>0 || like(r->esq->chave,prefix))){
			imprimeIntervalo(r->esq,prefix,existe);
		}

		//Imprime se a chave da raiz tiver o prefixo
		if(like(r->chave,prefix)){
			for (i = 0; i< r->qtd; i++){
				printf("%s\n",r->chave);
			}
			*existe = 1;
		}

		if(r->dir != NULL && (strcmp(r->dir->chave,prefix)>0 || like(r->esq->chave,prefix))){
			imprimeIntervalo(r->dir,prefix,existe);
		}
	}
}

void imprimePorLargura(NoArv *r){
	NoFila *f;
	NoArv *no;
	int nivelNo = 0;
	
	if(r == NULL)
		return;

	inicializaFila(&f);
	enfileirar(&f,r);
	
	while(!estaVazia(f)){
		nivelNo = f->tam;

		while(nivelNo > 0){
			no = desenfileirar(&f);
			printf("%s fb = %d, ",no->chave, no->fb);
			
			if(no->esq !=NULL)
				enfileirar(&f,no->esq);
			
			if(no->dir != NULL)
				enfileirar(&f,no->dir);
			
			nivelNo--;
		}
		printf("\n");
	}	

	//destruir_fila(&f);
}

void destroiArvore(NoArv *r){
	if(r != NULL){
		destroiArvore(r->esq);
		r->esq = NULL;
		destroiArvore(r->dir);
		r->dir = NULL;
		free(r);//Libera raiz do heap
	}
}

