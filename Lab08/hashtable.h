#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#define MAX 49

typedef struct{
   char chave[MAX];
   int flag;//Se estiver preenchido
   int *oc;//Vetor de ocorrencias dessa palavra no texto
   int ult;//Ultima posicao do vetor de ocorrencias
}No;

typedef struct{
   No *vet;
   int m;//Fator do modulo usado no hashing e tb o tamanho da tabela
}TabelaHash;

void iniciarTabela(TabelaHash **t, int tam);

void inserirNovo(TabelaHash *t, char *chave, int pos);

No *buscar(TabelaHash *t, char *chave);

#endif // HASH_H_INCLUDED
