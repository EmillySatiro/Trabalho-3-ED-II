#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void inicializar_Grafo(Grafo *grafo) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        grafo->vertices[i].id = i;
    }
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            grafo->arestas[i][j].confiabilidade = 0.0;
        }
    }
}


void exibir_Grafo(const Grafo *grafo) {
    printf("Grafo atual:\n");
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            printf("Vértice %d -> Vértice %d: Confiabilidade = %.2f\n", 
                   grafo->vertices[i].id, grafo->vertices[j].id, 
                   grafo->arestas[i][j].confiabilidade);
        }
    }
}

void preencher_Arestas_Aleatoriamente(Grafo *grafo) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = i + 1; j < NUM_VERTICES; j++) {
            double confiabilidade = ((double) rand() / RAND_MAX) * CONFIABILIDADE_MAX;
            grafo->arestas[i][j].confiabilidade = confiabilidade;
            grafo->arestas[j][i].confiabilidade = confiabilidade;
        }
    }
}


void dijkstra(Grafo *grafo, int origem, int *predecessor, double *distancia) {
    bool visitado[NUM_VERTICES] = {false};
    
    for (int i = 0; i < NUM_VERTICES; i++) {
        distancia[i] = -INFINITY; 
        predecessor[i] = -1;
    }

    distancia[origem] = 0.0;  
    for (int i = 0; i < NUM_VERTICES; i++) {
        int verticeAtual = -1;
        
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (!visitado[j] && (verticeAtual == -1 || distancia[j] > distancia[verticeAtual])) {
                verticeAtual = j;
            }
        }

        if (distancia[verticeAtual] == -INFINITY) {
            break;  
        }

        visitado[verticeAtual] = true;  
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (grafo->arestas[verticeAtual][j].confiabilidade > 0.0) {
                double novaDistancia = distancia[verticeAtual] + log(grafo->arestas[verticeAtual][j].confiabilidade);
                if (novaDistancia > distancia[j] ) {
                    distancia[j] = novaDistancia;
                    predecessor[j] = verticeAtual;
                }
            }
        }
    }
}

void exibir_Caminho(int *predecessor, int destino) {
    if (predecessor[destino] == -1) {
        printf("Não há caminho para o vértice %d\n", destino);
        return;
    }

    printf("Caminho: ");
    int caminho[NUM_VERTICES];
    int idx = 0;
    for (int v = destino; v != -1; v = predecessor[v]) {
        caminho[idx++] = v;
    }

    for (int i = idx - 1; i >= 0; i--) {
        printf("%d ", caminho[i]);
    }
    printf("\n");
}
