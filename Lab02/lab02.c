/*Nome: Pedro Alan Tapia Ramos
 *RA:185531
 *Turma: 
*/
#include <stdio.h>
#include "lista.h"

int main(void){
	No *listaMTF = NULL, *listaTR = NULL;
	int n,r;
	scanf("%d %d", &n, &r);

	//Adiciona elementos na lista
	int i,v;
	for(i = 0; i<n; i++){
		scanf("%d",&v);
		addLista(&listaMTF,v,1);
	}

	listaTR = copiaLista(listaMTF);//Copia lista

	char op;
	int custoMTF = 0, custoTR = 0;
	for (i = 0; i<r; i++){
		scanf(" %c %d",&op,&v);
		switch(op){
			case 'a':
				custoMTF += acessaNo(&listaMTF,v,1);
				custoTR += acessaNo(&listaTR,v,2);
				break;
			case 'i':
				custoMTF += addLista(&listaMTF,v,1);
				custoTR += addLista(&listaTR,v,2);
				break;
			case 'r':
				custoMTF += removeNo(&listaMTF,v);
				custoTR += removeNo(&listaTR,v);
				break;
		}
	}

	//Saida esperada
	printf("%d\n",custoMTF);
	imprimeLista(listaMTF);
	printf("%d\n",custoTR);
	imprimeLista(listaTR);

	destroiLista(&listaMTF);
	destroiLista(&listaTR);
}
