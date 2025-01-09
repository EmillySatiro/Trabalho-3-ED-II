#include <stdio.h>
#include "Dijskstra.h"

int main() {

    Grafo grafo[MAX_STATES];
    int matriz[MAX_STATES][MAX_STATES];
    gerar_grafo(grafo, matriz);
    int inicio, fim,opcao;
    clock_t inicio_tempo, fim_tempo;
    int dist[MAX_STATES];
    int prev[MAX_STATES];
  
    printf("\n=============================\n");
    printf("    Bem-vindo ao Jogo da Torre de Hanói!\n");
    printf("=============================\n");
    do {
        printf("1. Mostrar Caminho Dijskstra\n");
        printf("2. Mostrar Caminho Bellman Ford\n");
        printf("4. Mostrar Matriz de Adjacência\n");
        printf("3. Sair\n");
        printf("=============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                printf("Digite o indice da configuracao Inicial (0 a %d): ", MAX_STATES - 1);
                scanf("%d", &inicio);
                printf("Digite o indice da configuracao Final (0 a %d): ", MAX_STATES - 1);
                scanf("%d", &fim);
                inicio_tempo = clock();
                dijkstra(inicio,fim,prev,dist,matriz);
                fim_tempo = clock();
                mostrar_caminho(inicio, fim, prev, dist,grafo);
                double tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
                printf("Tempo do algoritmo de Dijkstra: %f segundos\n", tempo);
                break;
            case 2: 
                printf("Digite o indice da configuracao Inicial (0 a %d): ", MAX_STATES - 1);
                scanf("%d", &inicio);
                printf("Digite o indice da configuracao Final (0 a %d): ", MAX_STATES - 1);
                scanf("%d", &fim);
                inicio_tempo = clock();
                bellman_ford(inicio,prev,dist,matriz);
                fim_tempo = clock();
                mostrar_caminho(inicio, fim, prev, dist,grafo);
                double tempo_1 = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
                printf("Tempo do algoritmo de Bellman_ford : %f segundos\n", tempo_1);
                break;
            case 3:
                imprimir_matriz(matriz);
                break;
            case 4:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);
    return 0;
}
