#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int ehPrimo(int x){
   if (x < 2) return 0;

   int i,q;
   for(i = 2;;i++){
      q = x / i;
      if (q < i)
         return 1;
      if(x == q*i)
         return 0;
   }

   return 1;
}

int proxPrimo(int x){
   for(; !ehPrimo(x);x++);

   return x;
}


unsigned int hash(char *chave, int m){
   unsigned int h = 5381;
   int c;
   while (c = *chave++)
      h = ((h << 5) + h) + c;

   return h % m;
}

void iniciarTabela(TabelaHash **t, int tam){
   *t = malloc(sizeof(TabelaHash));

   if(*t == NULL){
      exit(1);//Heap cheio
   }

   //Para evitar muitas colisoes
   (*t)->m = proxPrimo(tam*2);
	(*t)->vet = malloc((*t)->m*sizeof(No));

	if((*t)->vet == NULL){
      exit(1);
   }

	int i;
	for(i = 0; i<(*t)->m; i++){
		(*t)->vet[i].ult = 0;
		(*t)->vet[i].flag = 0;
	}
}

void inserirNovo(TabelaHash *t, char *chave, int pos){
   unsigned int i = hash(chave,t->m);

   //Reespalhamento linear
   while (t->vet[i].flag && strcmp(chave,t->vet[i].chave) != 0){
      i++;
      if(i >= t->m){
         i = 0;
      }
   }

   if(!t->vet[i].flag){//Espaco livre
      strcpy(t->vet[i].chave,chave);
      t->vet[i].oc = malloc((t->m)*sizeof(int));
      t->vet[i].oc[t->vet[i].ult] = pos;
      t->vet[i].ult++;
      t->vet[i].flag = 1;
   }else if(strcmp(chave,t->vet[i].chave) == 0){//Palavra ja inserida na hash table
      t->vet[i].oc[t->vet[i].ult] = pos;
      t->vet[i].ult++;
   }
}

No *buscar(TabelaHash *t, char *chave){
   unsigned int i = hash(chave,t->m);
   while (strcmp(t->vet[i].chave,chave)!=0){
		i++;
		if(i >= t->m){
			i = 0;
		}
	}

   return &(t->vet[i]);
}

