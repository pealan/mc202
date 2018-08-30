//Estrutura da lista encadeada
typedef struct No{
	int valor;
	struct No *prox;
}No;

No	*addLista(No *inicioLista, int valor);

No *buscaNo(No *inicioLista,No *partida, int valor);

void imprimeLista(No *inicioLista);

void imprimeSubLista(No *ini, No *fim);

void destroiLista(No **inicioLista);
