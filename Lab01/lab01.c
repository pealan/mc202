/**Nome:Pedro Alan Tapia Ramos
**RA:185531
*/

#include <stdio.h>
#include "lista.h"

No* leLista(No *inicioLista){
	//Le valores da lista até o fim da linha e os adiciona a lista
	char c;
	int n;
	do{	
		scanf("%d%c",&n,&c);
		inicioLista = addLista(inicioLista,n);
	}while(c!='\n' && c!='\r');

	return inicioLista;
}

void imprimeSubListas(No *inicioLista, int m, int n, int p){
	No *prim,*seg,*ter;
	//Busca "m" partindo do começo da lista
	prim = buscaNo(inicioLista,inicioLista,m);

	//Busca "n" partindo da posição de "m" na lista
	seg = buscaNo(inicioLista,prim,n);

	//Busca "p" partindo da posição de "n" na lista
	ter = buscaNo(inicioLista,seg,p);

	//Inicio da lista se torna o "m" caso esse nao exista
	if(prim == NULL){
		prim = inicioLista;
	}

	No *segAux = seg;
	if(seg == NULL){
		segAux = ter;//Passa o trabalho de "n" para o "p", sem alterar o fato de que "n" nao existe
	}
	
	//Imprime primeira sublista
	printf("primeira");
	imprimeSubLista(prim,segAux);

	if((seg == NULL && ter != NULL) || (seg == NULL && ter == NULL) ){
		seg = prim;//Se "n" não existe, a lista ira de "m" até "p"		
	}
	
	//Imprime segunda sublista
	printf("\nsegunda");
	imprimeSubLista(seg,ter);

	if((seg != NULL && ter == NULL) || (seg == NULL && ter == NULL)){
		ter = seg;
	}

	//Imprime terceira sublista
	printf("\nterceira");
	imprimeSubLista(ter,NULL);

	printf("\n");
}

int main(void){
	No *inicioLista = NULL;
	
	inicioLista = leLista(inicioLista);

	int m,n,p;
	scanf("%d %d %d",&m,&n,&p);
	
	//Saida
	printf("original");	
	imprimeLista(inicioLista);	
	printf("m=%d, n=%d, p=%d\n",m,n,p);
	imprimeSubListas(inicioLista,m,n,p);

	//Libera espaço utilizado pela lista do heap
	destroiLista(&inicioLista);

	return 0;
}
