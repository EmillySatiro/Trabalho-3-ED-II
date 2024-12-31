#include <stdio.h>
#include <stdlib.h>

#define N 4        // Número de discos
#define P 3        // Número de pinos
#define V 81       // Número total de configurações (3^4 = 81)
#define INF 9999   // Valor de infinito

// Função para verificar se o movimento entre duas configurações é legal
int movimentoLegal(int* config1, int* config2) {
    int i;
    for (i = 0; i < N; i++) {
        if (config1[i] != config2[i]) {
            // Verifica se o movimento é legal: um disco não pode ser colocado em um menor
            int discoMovido = i;
            int pinoDestino = config2[i];
            
            for (int j = 0; j < N; j++) {
                if (config2[j] == pinoDestino && j != discoMovido && j < discoMovido) {
                    return 0; // Disco maior sendo movido para cima de um menor
                }
            }
            return 1;
        }
    }
    return 0; // Nenhum movimento feito, configuração não mudou
}

// Função para imprimir a matriz de adjacência
void imprimirMatrizAdjacencia(int adj[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

// Função para implementar o Algoritmo Bellman-Ford
void bellmanFord(int adj[V][V], int origem, int dist[V], int pred[V]) {
    // Inicializa os vetores de distância e predecessor
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;  // A distância para a configuração de origem é 0

    // Relaxação das arestas V-1 vezes
    for (int k = 1; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (adj[i][j] == 1 && dist[i] != INF && dist[i] + 1 < dist[j]) {
                    dist[j] = dist[i] + 1;
                    pred[j] = i;
                }
            }
        }
    }
}

// Função para imprimir o caminho (se houver) a partir de um vetor de predecessores
void imprimirCaminho(int pred[V], int destino) {
    if (pred[destino] == -1) {
        printf("%d ", destino);
        return;
    }
    imprimirCaminho(pred, pred[destino]);
    printf("%d ", destino);
}

int main() {
    int adj[V][V] = {0};  // Inicializa a matriz de adjacência com zeros
    int configuracoes[V][N]; // Representação das configurações dos discos
    
    int idx = 0;
    // Geração de todas as configurações possíveis (3^4 = 81)
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < P; k++) {
                for (int l = 0; l < P; l++) {
                    configuracoes[idx][0] = i;
                    configuracoes[idx][1] = j;
                    configuracoes[idx][2] = k;
                    configuracoes[idx][3] = l;
                    idx++;
                }
            }
        }
    }

    // Construir a matriz de adjacência com base nos movimentos legais
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (movimentoLegal(configuracoes[i], configuracoes[j])) {
                adj[i][j] = 1;
            }
        }
    }
    
    // Inicialização do algoritmo Bellman-Ford
    int origem = 0;  // A configuração inicial (todos os discos no pino 0)
    int destino = V - 1;  // A configuração final (todos os discos no pino 2)
    int dist[V], pred[V];

    // Executa o Bellman-Ford para encontrar o caminho mais curto
    bellmanFord(adj, origem, dist, pred);

    // Imprime o caminho mínimo
    printf("Menor caminho de configuração inicial para configuração final:\n");
    imprimirCaminho(pred, destino);
    printf("\n");

    printf("Número mínimo de movimentos: %d\n", dist[destino]);

    return 0;
}
