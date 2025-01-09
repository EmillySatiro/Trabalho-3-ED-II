#include <stdio.h>
#include "grafo.h"

int main() {
    Grafo grafo;
    int predecessor[NUM_VERTICES];
    double distancia[NUM_VERTICES];
    int opcao;

    inicializar_Grafo(&grafo);
    
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
                dijkstra(&grafo, 0, predecessor, distancia);
                exibir_Caminho(predecessor, 2);
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
