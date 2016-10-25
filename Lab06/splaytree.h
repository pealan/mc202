#ifndef SPLAYTREE_H
#define SPLAYTREE_H

//Estrutura da splay tree
typedef struct NoArv{
	char chave[50];//Nome do ingrediente
	int cong;//Tempo que a porcao congelada passou na mesa de preparo
	int des;//Tempo que a porcao descongelada passou na mesa de preparo
	int ultVez;//Ultimo tempo(turno) que o no foi acessado
	int jaServido;
	
	struct NoArv *dir;
	struct NoArv *esq;
	struct NoArv *pai;
}NoArv;

typedef struct NoFilaArv{
	NoArv *no;
	struct NoFilaArv *prox;
	struct NoFilaArv *frente;
	struct NoFilaArv *traseira;
	int tam;
}NoFilaArv;

//Insere No na arvore caso nao exista e o afunila. Caso exista, somente afunila o no 
void insereNo(NoArv **r, char chave[]);

void imprimeInOrder(NoArv *r);

void imprimePorLargura(NoArv *r);

void destroiArvore(NoArv *r);

//Metodos da fila de nos de arvore
void inicializaFilaArv(NoFilaArv **f);

void enfileirarArv(NoFilaArv **f, NoArv *no);

NoArv *desenfileirarArv(NoFilaArv **f);

int estaVaziaArv(NoFilaArv *f);

void destroiFilaArv(NoFilaArv **f);

#endif
