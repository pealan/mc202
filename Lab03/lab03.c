/*Nome: Pedro Alan Tapia Ramos
* RA:185531
*/
#include <stdio.h>
#include "dtstruct.h"

int main(void){
	NoPilha *bonecas = NULL;
	NoLista *listaBonecas = NULL;

	int total;
	scanf("%d",&total);

	int i,n;
	int primeiro = 1, valido = 1;
	for (i = 0; i < total; i++){
		scanf("%d",&n);
		if(valido && primeiro){
			if(n<0){//nova boneca
				empilha(&bonecas,n);
			}else if(-bonecas->id == n){//Fechando boneca
				if((n+ bonecas->azuis) % 2 == 0){
					valido = addOrdLista(&listaBonecas,-desempilha(&bonecas),"azul");

					if(bonecas != NULL){
						bonecas->azuis++;//boneca anterior possui pelo menos uma azul
					}

				}else{
					valido = addOrdLista(&listaBonecas,-desempilha(&bonecas),"vermelho");
				}

				if(bonecas == NULL){
					primeiro = 0;//Caso abra outra não sera uma sequencia valida
				}

			}else{//fechando uma boneca com uma ainda aberta dentro
				valido = 0;
			}
		}else if (!primeiro){
			valido = 0;
		}
	}

	if(valido && bonecas == NULL){
		printf("sequencia valida pode ser colorida\n");
		imprimeLista(listaBonecas);
	}else{
		printf("sequencia invalida ou nao pode colorir\n");
	}

	destroiLista(&listaBonecas);
	return 0;
}
