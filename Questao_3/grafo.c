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
    if (origem < 0 || origem >= NUM_VERTICES) {
        printf("Erro: Vértice de origem inválido.\n");
        return;
    }

    bool visitado[NUM_VERTICES] = {false};
    
    // Inicializa distâncias e predecessores
    for (int i = 0; i < NUM_VERTICES; i++) {
        distancia[i] = INFINITO_NEGATIVO; // Menor valor possível para maximizar confiabilidade
        predecessor[i] = -1; // Nenhum predecessor inicialmente
    }

    distancia[origem] = 0.0; // Confiabilidade máxima no vértice de origem (log(1) = 0)
    
    for (int i = 0; i < NUM_VERTICES; i++) {
        int verticeAtual = -1;
        
        // Encontra o vértice não visitado com maior confiabilidade acumulada
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (!visitado[j] && (verticeAtual == -1 || distancia[j] > distancia[verticeAtual])) {
                verticeAtual = j;
            }
        }

        // Se não há vértices alcançáveis, sai do loop
        if (distancia[verticeAtual] == -INFINITY) {
            break;
        }

        visitado[verticeAtual] = true; // Marca como visitado
        
        // Atualiza as distâncias para os vizinhos do vértice atual
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (grafo->arestas[verticeAtual][j].confiabilidade > 0.0) { 
                // Usa logaritmo para somar confiabilidades acumuladas
                double novaDistancia = distancia[verticeAtual] + log(grafo->arestas[verticeAtual][j].confiabilidade);
                if (novaDistancia > distancia[j]) {
                    distancia[j] = novaDistancia; // Atualiza a maior confiabilidade
                    predecessor[j] = verticeAtual; // Define o predecessor
                }
            }
        }
    }
   
}

void exibir_Caminho(int *predecessor, int destino, double *des) {
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
    printf("\nConfiabilidade total (logarítmica): %f\n", des[destino]);
    

    double confiabilidade_total = exp(des[destino]);
    printf("Confiabilidade total (normal): %f\n", confiabilidade_total);
}
