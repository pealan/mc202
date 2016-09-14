//Estrutura da lista duplamente encadeada
typedef struct No{
	int valor;
	struct No *prox;
	struct No *antes;
}No;

int addLista(No **inicioLista, int valor, int tipo);

No *copiaLista(No *original);

int acessaNo(No **inicioLista,int valor, int tipo);

int removeNo(No **inicioLista,int valor);

void imprimeLista(No *inicioLista);

void destroiLista(No **inicioLista);
