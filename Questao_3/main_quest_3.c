#include <stdio.h>
#include "grafo.h"

int main() {
    int vertices = 5;
    Edge* graph[MAX];
    for (int i = 0; i < MAX; ++i) {
        graph[i] = (Edge*)malloc(MAX * sizeof(Edge));
        for (int j = 0; j < MAX; ++j) {
            graph[i][j].v = -1; // Inicializar o grafo
        }
    }

    // Arestas (u -> v, confiabilidade)
    graph[0][0] = (Edge){1, 0.9};
    graph[0][1] = (Edge){2, 0.5};
    graph[1][0] = (Edge){3, 0.7};
    graph[2][0] = (Edge){3, 0.8};
    graph[3][0] = (Edge){4, 0.6};
    graph[4][0] = (Edge){-1, 0};

    int origem = 0, destino = 10;
    double confiabilidade = dijkstra(graph, vertices, origem, destino);
    printf("Caminho mais confiável de %d para %d tem confiabilidade %.6f\n", origem, destino, confiabilidade);

    return 0;
}
