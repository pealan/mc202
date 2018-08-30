#ifndef AVLTREE_H
#define AVLTREE_H

//Estrutura do no da arvore
typedef struct NoArv{
	char chave[21];
	int qtd;//Quantidade de arquivos com esse nome
	int fb;//Fator de balanceamento
	int h;//Altura do no
	struct NoArv *esq;
	struct NoArv *dir;
}NoArv;

int insere(NoArv **r, char chave[], int *flag);

void removeIntervalo(NoArv **r, char prefixo[], int *existe);

void imprimeIntervalo(NoArv *r, char prefix[], int *existe);

void imprimeInOrdem(NoArv *r);

void imprimePorLargura(NoArv *r);

void destroiArvore(NoArv *r);
#endif
