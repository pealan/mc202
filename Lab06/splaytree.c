#include "splaytree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void rodarDireita(NoArv **r){
	//"b" eh em torno de quem vamos rotacionar
	NoArv *a, *b, *paiB;
	b = *r;
	a = b->esq;
	paiB = b->pai;

	//Troca ponteiros
	if(a != NULL){
		b->esq = a->dir;
		if(a->dir != NULL){
			a->dir->pai = b;
		}
		a->pai = paiB;
	}
	
	if(paiB == NULL){
		//printf("OP\n");
		*r = a;
	}else if (b == paiB->esq){
		paiB->esq = a;
	}else{
		paiB->dir = a;
	}
	
	if(a != NULL){
		a->dir = b;
	}

	b->pai = a;
}

void rodarEsquerda(NoArv **r){
	//"a" eh em torno de quem vamos rotacionar
	NoArv *a, *b, *paiA;
	a = *r;
	b = a->dir;
	paiA = a->pai;

	//Troca ponteiros
	if(b != NULL){
		a->dir = b->esq;
		if(b->esq != NULL){
			b->esq->pai = a;
		}
		b->pai = paiA;
	}
	
	if(paiA == NULL){
		*r = b;
	}else if (a == paiA->esq){
		paiA->esq = b;
	}else{
		paiA->dir = b;
	}
	
	if(b != NULL){
		b->esq = a;
	}

	a->pai = b;
}

void afunilar(NoArv **r, NoArv *x){
	//static int l = 0;
	while(*r != x){//Enquanto nao for a raiz
		//l++;
		//if(l == 10) exit(1);
		if(x->pai == *r){//caso zig
			if((*r)->esq == x){//x eh filho esquerdo da raiz
				//printf("ZIG\n");
				//printf("  -%s %s %s\n",(*r)->chave,x->pai->chave,x->chave);
				rodarDireita(r);
			}else{
				//printf("ZAG\n");
				//printf("  -%s %s\n",(*r)->chave,x->chave);
				rodarEsquerda(r);
				//printf("  -%s %s\n",(*r)->chave,x->chave);
				//if(*r != *x)
			}
		}else{
			NoArv *pai = x->pai, *avo = pai->pai;
			int ehraiz = 0;
			//printf("%s %s\n",pai->chave,avo->chave);
			if(x == pai->esq && pai == avo->esq){//Pai e avo alinhados na esquerda
				//zig-zig
				//printf("ZIGZIG\n");
				//printf("  -%s %s\n",pai->chave,avo->chave);
				if(avo == *r){
					ehraiz = 1;
				}
				rodarDireita(&avo);
				//printf("  -%s %s\n",x->pai->chave,avo->chave);
				rodarDireita(&pai);
				//printf("  -%s %s\n",x->pai->chave,(*r)->chave);
				if(ehraiz)
					*r = x;
			}else if(x == pai->dir && pai == avo->dir){//Pai e avo alinhados na direita
				//printf("ZIGZIG2\n");
				if(avo == *r){
					ehraiz = 1;
				}
				rodarEsquerda(&avo);
				rodarEsquerda(&pai);
				if(ehraiz)
					*r = x;
			}else{
				//zig-zag
				if(x == pai->dir && pai == avo->esq){
					//printf("ZIGZAG\n");
					//printf("  -%s %s\n",x->pai->chave,x->chave);
					rodarEsquerda(&x->pai);
					//printf("  -%s %s %s\n",x->pai->chave,x->esq->chave,x->esq->pai->chave);
					NoArv *novoPai = x->pai;
					rodarDireita(&x->pai);
					if(novoPai == *r){
						x->pai = NULL;
						*r = x;
					}
					//x = avo;
					//printf("  -%s %s\n",x->pai->chave,(*r)->chave);
				}else{
					//printf("ZIGZAG2\n");
					rodarDireita(&x->pai);
					NoArv *novoPai = x->pai;
					rodarEsquerda(&x->pai);
					if(novoPai == *r){
						x->pai = NULL;
						*r = x;
					}
				}
			}
		}
	}
}

void insereNo(NoArv **r, char chave[]){
	//printf("A\n");
	NoArv **x = r, *pai = NULL;
	while(*x != NULL){
		if (strcmp((*x)->chave,chave)< 0){
			pai = *x;
			x = &((*x)->dir);
		}else if (strcmp((*x)->chave,chave) > 0){
			pai = *x;
			x = &((*x)->esq);
		}else{//Elemento ja foi inserido
			break;
		}
	}
	
	//Somente se no ainda nao foi inserido
	if(*x == NULL){
		*x = malloc(sizeof(NoArv));
		(*x)->pai = pai;
		(*x)->esq = (*x)->dir = NULL;
		strcpy((*x)->chave,chave);
		
		//Ingredientes que não foram usados desde a abertura ficaram 20min+ na mesa de preparo
		(*x)->cong = 0;
		(*x)->des = 20;
		(*x)->ultVez = 0;
		(*x)->jaServido = 1;
	}
	
	//printf("%s %s\n",(*r)->chave,(*x)->pai->chave);
	afunilar(r,*x);
	//printf("AFUNILEI\n");
}

/*void imprimePorLargura(NoArv *r){
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
}*/

void imprimeInOrdem(NoArv *r){
	if(r != NULL){
		imprimeInOrdem(r->esq);
		printf("%s\n",r->chave);
		imprimeInOrdem(r->dir);
	}
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

void inicializaFilaArv(NoFilaArv **f){
	*f = malloc(sizeof(NoFilaArv));

	if(*f == NULL){
		exit(1);
	}

	(*f)->frente = (*f)->traseira = NULL;
	(*f)->tam = 0;
}

void enfileirarArv(NoFilaArv **f, NoArv *no){
	NoFilaArv *n = malloc(sizeof(NoFilaArv));

	if(n == NULL){
		exit(1);
	}	

	n->no = no;
	n->prox = NULL;

	if((*f)->traseira != NULL && (*f)->frente != NULL){
		(*f)->traseira->prox = n;
		(*f)->traseira = n;
	}else{
		(*f)->frente = (*f)->traseira = n;
	}

	(*f)->tam++;
}

NoArv *desenfileirarArv(NoFilaArv **f){
	NoFilaArv *t;
	NoArv *temp = NULL;
	if((*f)->frente != NULL){
		t = (*f)->frente;

		if((*f)->frente == (*f)->traseira)
			(*f)->frente = (*f)->traseira = NULL;
		else
			(*f)->frente = t->prox;

		temp = t->no;
		free(t);
		(*f)->tam--;
	}
	
	return temp;
}

int estaVaziaArv(NoFilaArv *f){
	if(f->frente == NULL && f->traseira == NULL)
		return 1;

	return 0;
}

void destroiFilaArv(NoFilaArv **f){
	//TODO
}
