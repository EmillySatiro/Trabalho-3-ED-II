#include <stdio.h>
#include "grafo.h"

int main() {
    Grafo grafo;
   
    int opcao;
    do {
        printf("\n=======Menu de Operações========:\n");
        printf("1. Inicializar Grafo\n");
        printf("2. Exibir Grafo\n");
        printf("3. Preencher Grafo com Arestas Aleatórias\n");
        printf("4. Encontrar Caminho com Dijkstra\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inicializar_Grafo(&grafo);
                printf("Grafo inicializado.\n");
                break;
            case 2:
                exibir_Grafo(&grafo);
                break;
            case 3:
                preencher_Arestas_Aleatoriamente(&grafo);
                printf("Arestas preenchidas aleatoriamente.\n");
                break;
            case 4:
                int origem, destino;
                printf("Digite o vértice de origem (0 a %d): ", NUM_VERTICES - 1);
                scanf("%d", &origem);
                printf("Digite o vértice de destino (0 a %d): ", NUM_VERTICES - 1);
                scanf("%d", &destino);

                if (origem < 0 || origem >= NUM_VERTICES || destino < 0 || destino >= NUM_VERTICES) {
                    printf("Erro: Vértices inválidos. Tente novamente.\n");
                }else{
                    int predecessor[NUM_VERTICES];
                    double distancia[NUM_VERTICES];

                    dijkstra(&grafo, origem, predecessor, distancia);

                    if (distancia[destino] == -INFINITY) {
                        printf("Não há caminho confiável entre os vértices %d e %d.\n", origem, destino);
                    } else {
                        exibir_Caminho(predecessor, destino,&grafo);
                    }
                }
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
