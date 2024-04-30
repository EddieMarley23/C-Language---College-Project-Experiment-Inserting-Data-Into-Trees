#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"
#include <locale.h>
#include <time.h>
#define RED 1
#define BLACK 0

struct NO{
    Fun info;
    int alt; //inclui altura
    struct NO *esq;
    struct NO *dir;
};

struct NORB{
    Fun info;
    int alt;
    struct NORB *esq;
    struct NORB *dir;
    int cor;
};

arvoreLLRB *cria_arvoreLLRB () {
arvoreLLRB *raiz = (arvoreLLRB*) malloc(sizeof (arvoreLLRB));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void liberar_arvoreLLRB (arvoreLLRB *raiz){
     if (raiz == NULL){
         return;
     }
     libera_NO (*raiz);
     free (raiz);
}

void libera_NO(struct NO *no) {
    if (no != NULL) {
        libera_NO(no->esq);
        libera_NO(no->dir);
        free(no);
    }
}

int vazia_arvoreLLRB(arvoreLLRB *raiz) {
    if(raiz == NULL) {
    return 1;
    }
    if(*raiz == NULL) {
    return 1;
    }
return 0;
}

int altura_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = altura_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvoreLLRB(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    }else{
        return(alt_dir + 1);
}

}

int totalNO_arvoreLLRB(arvoreLLRB *raiz) {
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = totalNO_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = totalNO_arvoreLLRB(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}


int insere_arvoreLLRB(arvoreLLRB *raiz, Fun valor){
    int res;
    if(*raiz == NULL) {
        struct NORB *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            return 0;
        }
        novo->info.id = valor.id;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
struct NORB *atual = *raiz;
if(valor.id < atual->info.id){
    if((res = insere_arvoreLLRB(&(atual->esq), valor)) == 1){
        if(fatorBalanceamento_NO(atual) >= 2){
            if(valor.id < (*raiz)->esq->info.id){
                rotacaoLL(raiz);
            }else{
                rotacaoLR(raiz);
            }
        }
    }
}else{
    if(valor.id > atual->info.id){
        if((res = insere_arvoreLLRB(&(atual->dir), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >=  2){
                if((*raiz)->dir->info.id < valor.id){
                    rotacaoRR(raiz);
                }else{
                    rotacaoRL(raiz);
                }
            }
        }
    }else{
        printf("Valor duplicado!\n");
        return 0;
    }
}
atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
return res;
}

struct NO *procuramenor(struct NO *atual){
    struct NO *no1 = atual;
    struct NO *no2  = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
};




//Calcula a altura de um n6
int alt_no(struct NO *no) {
    if (no == NULL){
    return -1;
    }else{
        return no->alt;
}
}

//Calcula o Fator de Balanceamento de um no
int fatorBalanceamento_NO(struct NO *no){
    return labs(alt_no(no->esq) - alt_no(no->dir));
}


//calcula maior valor
int maior(int x, int y){
    if(x > y){
        return (x);
    }else{
        return(y) ;
    }
}

void rotacaoLL(arvoreLLRB *raiz){
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->esq), (*raiz)->alt + 1);
    *raiz = no;
}

void rotacaoRR(arvoreLLRB *raiz) {
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->dir), (*raiz)->alt) + 1;
    (*raiz) = no;
}

void rotacaoLR(arvoreLLRB *raiz) {
    rotacaoRR (&(*raiz)->esq);
    rotacaoLL (raiz);
}

void rotacaoRL(arvoreLLRB *raiz) {
rotacaoLL (&(*raiz)->dir);
rotacaoRR (raiz);
}


int cor(struct NORB *H){
    if(H == NULL){
        return BLACK;
    }else{
        return H->cor;
    }
}

void trocaCor(struct NORB *H){
    H->cor = !H->cor;
    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NORB *rotacionaEsquerda(struct NORB *A){
    struct NORB *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NORB *rotacionaDireita(struct NORB *A){
    struct NORB *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NORB *move2EsqRED(struct NORB *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
};

struct NORB *move2DirRED(struct NORB *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
};

struct NORB *balancear(struct NORB *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
};

void medirTempoInsercaoLLRB(void (*funcao_lerdados)(Fun *, int), Fun *vetor2, int tamanho, void (*funcao_inserir)(arvoreLLRB *, Fun), arvoreLLRB *raiz) {

    clock_t start_time2 = clock();

    // Chama a função que lê os dados
    funcao_lerdados(vetor2, tamanho);

    // Insere os dados na árvore LLRB
    for (int i = 0; i < tamanho; i++) {
        funcao_inserir(raiz, vetor2[i]);
    }


    clock_t end_time2 = clock();

    // Cálculo do tempo decorrido
    double elapsed_time2 = ((double)(end_time2 - start_time2)) / CLOCKS_PER_SEC;

    printf("Tempo decorrido: %.6f segundos\n", elapsed_time2);
}


//Arvore AVL*******************************************************************************************************


void medirTempoInsercao_AVL(void (*funcao_lerdados)(Fun *, int), Fun *vetor, int tamanho, void (*funcao_inserir)(ArvAVL *, Fun), ArvAVL *raiz) {

    clock_t start_time = clock();

    // Chama a função que lê os dados
    funcao_lerdados(vetor, tamanho);

    // Insere os dados na árvore AVL
    for (int i = 0; i < tamanho; i++) {
        funcao_inserir(raiz, vetor[i]);
    }

    clock_t end_time = clock();

    // Cálculo do tempo decorrido
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Tempo decorrido: %.6f segundos\n", elapsed_time);
}


ArvAVL *cria_arvAVL () {
ArvAVL *raiz = (ArvAVL*) malloc(sizeof (ArvAVL));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void liberar_ArvAVL(ArvAVL *raiz){

    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}



int vazia_arvAVL(ArvAVL *raiz) {
    if(raiz == NULL) {
    return 1;
    }
    if(*raiz == NULL) {
    return 1;
    }
return 0;
}

int altura_arvAVL(ArvAVL *raiz){
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    }else{
        return(alt_dir + 1);
}

}

int totalNO_arvAVL(ArvAVL *raiz) {
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = totalNO_arvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_arvAVL(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

void preOrdem_arvAVL(ArvAVL *raiz){
    if(raiz == NULL) {
        return;
}

if(*raiz != NULL) {
    printf ("%d\n", (*raiz)->info) ;
    preOrdem_arvAVL(&((*raiz)->esq));
    preOrdem_arvAVL(&((*raiz)->dir));
}
}

void emOrdem_arvAVL(ArvAVL *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
        emOrdem_arvAVL(&((*raiz) ->esq));
        printf("%d\n", (*raiz)->info) ;
        emOrdem_arvAVL(&((*raiz)->dir));
    }
}

void posOrdem_arvAVL(ArvAVL *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
        posOrdem_arvAVL (&((*raiz)->esq));
        posOrdem_arvAVL(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}







int insere_arvAVL(ArvAVL *raiz, Fun valor){
            int res;
        if(*raiz == NULL){
            struct NO *novo;
            novo = (struct NO*) malloc(sizeof(struct NO));
            if(novo == NULL){
                return 0;
            }
            novo->info = valor;
            novo->alt = 0;
            novo->esq = NULL;
            novo->dir = NULL;
            *raiz = novo;
            return 1;
        }
        struct NO *atual = *raiz;
        if(valor.id < atual-> info.id){
            if((res = insere_arvAVL(&(atual->esq), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(valor.id < (*raiz)->esq->info.id){
                        rotacaoLL(raiz);
                    }else{
                        rotacaoLR(raiz);
                    }
                }
            }
        }else{
            if(valor.id > atual->info.id){
                if((res = insere_arvAVL(&(atual->dir), valor)) == 1){
                   if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info.id < valor.id){
                        rotacaoRR(raiz);
                    }else{
                        rotacaoRL(raiz);
                    }
                   }
                }
            }else{
                printf("Valor duplicado!\n");
                return 0;
            }
        }
    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res;
    }


//Algoritmo de ordenação Shellsort

void she11Sort(Fun *V, int N) {
    int i, j, h;
    Fun aux;


    h = 1;
    while (h < N/3)
        h = 3 * h + 1;


    while (h > 0) {

        for (i = h; i < N; i++) {
            aux.id = V[i].id;
            j = i;


            while (j >= h && aux.id < V[j - h].id) {
                V[j].id = V[j - h].id;
                j = j - h;
            }
            V[j].id = aux.id;
        }


        h = (h - 1) / 3;
    }
}



int lerDadosCSV(Fun *v, int tamanho) {

    FILE *fp = fopen("massaDados.csv", "r");

    if (fp == NULL) {
        printf("Falha ao abrir o arquivo");
        return 1;
    }

    char linha[400];
    int i = 0;

    while (fgets(linha, 400, fp) && i < tamanho) {
        Fun func;

        func.id = atoi(strtok(linha, ";"));
        strcpy(func.nome, strtok(NULL, ";"));
        func.idade = atoi(strtok(NULL, ";"));
        strcpy(func.empresa, strtok(NULL, ";"));
        strcpy(func.dpto, strtok(NULL, ";"));
        func.salario = atof(strtok(NULL, ";"));

        v[i] = func;
        i++;
    }

    fclose(fp);
    return 0;
}


int lerDadosCSV_ORD(Fun *v, int tamanho) {

    FILE *fp = fopen("dadosOrdenados.csv", "r");

    if (fp == NULL) {
        printf("Falha ao abrir o arquivo");
        return 1;
    }

    char linha[400];
    int i = 0;

    while (fgets(linha, 400, fp) && i < tamanho) {
        Fun func;

        func.id = atoi(strtok(linha, ";"));
        strcpy(func.nome, strtok(NULL, ";"));
        func.idade = atoi(strtok(NULL, ";"));
        strcpy(func.empresa, strtok(NULL, ";"));
        strcpy(func.dpto, strtok(NULL, ";"));
        func.salario = atof(strtok(NULL, ";"));

        v[i] = func;
        i++;
    }

    fclose(fp);
    return 0;
}


