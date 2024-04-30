//funções da arvore rubro negra
typedef struct NO *arvoreLLRB;



typedef struct funcionario{

        int id;
        char nome[100];
        int idade;
        char empresa[100];
        char dpto[100];
        float salario;

}Fun;

arvoreLLRB *cria_arvoreLLRB();

void liberar_arvoreLLRB (arvoreLLRB *raiz); ;

int vazia_arvoreLLRB (arvoreLLRB *raiz);

int altura_arvoreLLRB (arvoreLLRB *raiz);

int totalNO_arvoreLLRB(arvoreLLRB *raiz);


int insere_arvoreLLRB(arvoreLLRB *raiz, Fun valor);

int remove_arvoreLLRB(arvoreLLRB *raiz, int valor);

int consulta_arvoreLLRB(arvoreLLRB *raiz, int valor);
void medirTempoInsercaoLLRB(void (*funcao_lerdados)(Fun *, int), Fun *vetor2, int tamanho, void (*funcao_inserir)(arvoreLLRB *, Fun), arvoreLLRB *raiz);


//funções da arvore AVL
typedef struct NO *ArvAVL;

void medirTempoInsercao_AVL(void (*funcao_lerdados)(Fun *, int), Fun *vetor, int tamanho, void (*funcao_inserir)(ArvAVL *, Fun), ArvAVL *raiz);

ArvAVL *cria_arvAVL();

int insere_arvAVL(ArvAVL *raiz, Fun valor);

//fun�ao responsavel pela busca do N� a ser removido
int remove_arvAVL(ArvAVL *raiz, int valor);

void liberar_ArvAVL(ArvAVL *raiz);

int vazia_arvAVL (ArvAVL *raiz);

int altura_arvAVL (ArvAVL *raiz);

int totalNO_arvAVL(ArvAVL *raiz);

struct NO *procuramenor(struct NO *atual);

void she11Sort(Fun *V, int N);

void liberarPonteiros(Fun *v, int tamanho);

int lerDadosCSV(Fun *v, int tamanho);
int lerDadosCSV_ORD(Fun *v, int tamanho);

