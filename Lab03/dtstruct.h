//Estrutura da pilha
typedef struct NoPilha{
	int id;
	int azuis;
	struct NoPilha *prox;
}NoPilha;

//Estrutura da lista duplamente encadeada
typedef struct NoLista{
	int id;
	char cor[8];
	struct NoLista *prox;
	struct NoLista *antes;
}NoLista;

void empilha(NoPilha **prim, int novo);

int desempilha(NoPilha **prim);

int addOrdLista(NoLista **inicio, int id, char cor[]);

void imprimeLista(NoLista *inicioLista);

void destroiLista(NoLista **inicioLista);
