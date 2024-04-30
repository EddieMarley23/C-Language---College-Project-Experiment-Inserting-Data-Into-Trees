#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "arvores.h"
#include <time.h>
#define RED 1
#define BLACK 0


int main() {

        //setlocale(LC_ALL, "Portuguese"); Professor, o setlocale não está funcionando, poderia me explicar o porque? com um e-mail ou mensagem pelo moodle?

        int i,n,x,j;
        int tamanho = 15000;
        Fun *v,*v2,*aux,*v_ordenado;

        Fun p;


        char linha2[400];
        Fun func;
        i=0;
        j=0;

        v = (Fun *)calloc(tamanho, sizeof(Fun));
        lerDadosCSV(v,tamanho);



      //Alocação de memória para a variável auxiliar
        int a = 0;

        aux = (Fun *)calloc(tamanho, sizeof(Fun));
        //atribuindo o valor de V para a variável auxiliar
        for(i = 0; i < tamanho; i++){

            aux[i] = v[i];
        }









    she11Sort(aux,tamanho);
    printf("Gerando arquivos CSV\n");
    printf("\nCarregando .");
    printf(" .");
    FILE *dados_ordenados = fopen("saida.csv", "w");
    printf(" .");
    if (dados_ordenados == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }
    printf(" .");

    for (int i = 0; i < tamanho; i++) {
        // Escrevendo no arquivo CSV
        fprintf(dados_ordenados, "%d;%s;%d;%s;%s;%.2f\n", aux[i].id, aux[i].nome, aux[i].idade, aux[i].empresa, aux[i].dpto, aux[i].salario);
    }

    printf(" .");
    // Fechar o arquivo
    fclose(dados_ordenados);
    printf(" .");
    free(v);
    printf(" .");

    printf("\n\nArquivos gerados com sucesso!\n\n");

    system("pause");

    system("cls");





while(1){
            printf("\n\n\t\t\tMenu\n\n\n1.Inserir massa de dados DESORDENADOS.\n2.Inserir massa de dados ORDENADOS.\n3.Encerrar programa.\n\n\nEscolha a Massa de dados a serem inseridas:");

            scanf("%d",&n);

            if(n == 1){

            system("cls");
            printf("\t\t\t\t\nInsercao de dados Desordenados\n\n");
            printf("\n\n\t\tARVORE AVL\n\n");

            ArvAVL *raiz;

            raiz = cria_arvAVL();

            v = (Fun *)calloc(tamanho, sizeof(Fun));

            medirTempoInsercao_AVL(lerDadosCSV, v, tamanho, insere_arvAVL, raiz);



            liberar_ArvAVL(raiz);

            free(v);

            printf("\n\n\n\n\n\n\t\t\tARVORE RUBRO NEGRA\n\n\n");



            arvoreLLRB *raiz2;
            raiz2 = cria_arvoreLLRB();


            if (raiz2 == NULL) {
                printf("Falha ao criar a árvore rubro-negra\n");
                return 1;
            }


            v2 = (Fun *)calloc(tamanho, sizeof(Fun));
            medirTempoInsercaoLLRB(lerDadosCSV, v2, tamanho, insere_arvoreLLRB, raiz2);


            liberar_arvoreLLRB(raiz2);
            free(v2);

            system("pause");
        }


        if(n == 2){

            system("cls");
            printf("\t\t\n\n Insercao de dados ORDENADOS\n\n");
            printf("\n\n\t\tARVORE AVL\n\n");

            ArvAVL *raiz;

            raiz = cria_arvAVL();

            v = (Fun *)calloc(tamanho, sizeof(Fun));

            medirTempoInsercao_AVL(lerDadosCSV_ORD, v, tamanho, insere_arvAVL, raiz);


            liberar_ArvAVL(raiz);

            free(v);

            printf("\n\n\n\n\n\n\t\t\tARVORE RUBRO NEGRA\n\n\n");



            arvoreLLRB *raiz2;
            raiz2 = cria_arvoreLLRB();


            if (raiz2 == NULL) {
                printf("Falha ao criar a árvore rubro-negra\n");
                return 1;
            }


            v2 = (Fun *)calloc(tamanho, sizeof(Fun));
            medirTempoInsercaoLLRB(lerDadosCSV_ORD, v2, tamanho, insere_arvoreLLRB, raiz2);





            liberar_arvoreLLRB(raiz2);
            free(v2);
            system("pause");
        }

            if(n ==3){
            system("cls");
            printf("\nPrograma encerrado com sucesso!\n\n\n");
                break;
            }

system("cls");
    }
    return 0;
}
