/*Nome: Pedro Alan Tapia Ramos
 *RA:185531
 *PS: Tentei ler o tabuleiro com scanf(" %c"...) 
 *porem por alguma razao o programa esperava mais entrada
*/

#include <stdio.h>
#include <stdlib.h>

//Estrutura de uma dama do xadrez
typedef struct{
	int pos;//da peca
	char id;
}Peca;

int valido(Peca *vet,char *tab, int n,int m,char ultimo){
	int i, lin;
	lin = vet[m-1].pos;//Posicao do ultimo no prefixo

	for(i = 0; i< m-1; i++){

		//Caso ja tenha uma peca igual
		if(vet[i].id == ultimo){
			return 0;
		}

		//Na mesma linha
		if((vet[i].pos == lin)){
			return 0;
		}
	
		//Na diagonal
		if(((m-1)-i == abs(lin-vet[i].pos))){
			return 0;
		}
	}

	return 1;
}

int existeSol(Peca *vet,char *tab, int n, int m, char ultimo){
	//Chegou ao fim do tabuleiro	
	if(m == n){
		//Verifica se toda essa combinacao eh valida
		if (valido(vet,tab,n,m,ultimo)){
			return 1;
		}else{
			return 0;
		}
	}

	//Todas as pecas colocadas na primeira coluna sao validas
	if(m != 0){
		if(!valido(vet,tab,n,m,ultimo)){
			return 0;
		}
	}
	
	//Gera valores para onde colocar a proxima rainha
	int i;
	for (i = 0; i< n; i++){
		vet[m].pos = i;
		vet[m].id = tab[i*n+m];
		
		//Verifica se existe solucao para onde essa rinha foi colocada
		if(existeSol(vet,tab,n,m+1,vet[m].id)){
			return 1;
		}
	}

	return 0;
}

int main(void){
	int n;
	char *tabuleiro;
	char *linha;

	scanf("%d",&n);

	//Matriz vetorizada requer menos acesso a memoria, gasta menos tempo
	tabuleiro = malloc(n*n*sizeof(char));

	//Cada linha eh uma string de tamanho n+1('\0' no fim)
	linha = malloc(n*sizeof(char)+sizeof(char));

	//Cada letra da string eh um elemento do tabuleiro
	int i,j;
	for (i = 0; i<n; i++){
		scanf("%s",linha);
		for (j = 0; j<=n; j++){
			tabuleiro[i*n + j] = linha[j];
		}
	}
	
	//O vetor de prefixos esta teoricamente correto até m
	int m = 0;

	//Ultima peça colocada
	char ultimo = 0;

	//Vetor que guarda a posicao das rainhas e suas "id's"
	Peca *vet = malloc(n*sizeof(Peca));

	if(existeSol(vet,tabuleiro, n,m,ultimo)){
		printf("Tem solucao.\n");
	}else{
		printf("Sem solucao.\n");
	}

	free(tabuleiro);
	free(linha);
	free(vet);

	return 0;
}
