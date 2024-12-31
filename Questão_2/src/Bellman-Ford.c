#include "Bellman-Ford.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_STATES 81  // Substitua com o número de estados que seu sistema tiver
#define NUM_PINS 3  // Definindo número de pinos
// #define NUM_DISKS 4  // Definindo número de discos

// Estrutura Grafo - aqui você define como cada estado é representado


// Função que calcula a validade de uma movimentação entre dois estados
int movimento_valido(Grafo *config1, Grafo *config2) {
    int var_count = 0, diff_idx = -1;
    int valido = 1;
    
    for (int i = 0; i < NUM_DISKS && var_count <= 1; ++i) {
        if (config1->estado[i] != config2->estado[i]) {
            var_count++;
            diff_idx = i;
        }
    }

    if (var_count > 1) {
        valido = 0; // Não válido se houver mais de 1 diferença
    } else {
        // Se a mudança for válida entre os pinos
        for (int i = 0; i < NUM_PINS; i++) {
            if (i != diff_idx && 
                ((config1->estado[i] == config1->estado[diff_idx] && i < diff_idx) ||
                (config2->estado[i] == config2->estado[diff_idx] && i < diff_idx))) {
                valido = 0;
            }
        }
    }

    return valido;
}

// Função para gerar o grafo, representando o estado dos discos nos pinos
void gerar_grafo(Grafo *grafo, int mat_adj[][MAX_STATES]) {
    for (int i = 0; i < MAX_STATES; i++) {
        int num = i;
        for (int disco = 0; disco < NUM_DISKS; disco++) {
            grafo[i].estado[disco] = num % NUM_PINS + 1;
            num /= NUM_PINS;
        }
    }

    // Preencher a matriz de adjacência com as movimentações válidas
    for (int x = 0; x < MAX_STATES; x++) {
        for (int y = 0; y < MAX_STATES; y++) {
            if (movimento_valido(&grafo[x], &grafo[y])) {
                mat_adj[x][y] = 1; // Movimento válido
            } else {
                mat_adj[x][y] = 0; // Movimento inválido
            }
        }
    }
}

// Algoritmo de Bellman-Ford para encontrar o menor caminho
void bellman_ford(int inicio, int prev[], int dist[], int mat_adj[][MAX_STATES]) {
    // Inicializar distâncias e predecessores
    for (int i = 0; i < MAX_STATES; i++) {
        prev[i] = -1;
        dist[i] = INT_MAX;  // Inicialize as distâncias com INT_MAX
    }
    dist[inicio] = 0;  // A distância inicial é 0 para o nó de início

    // Relaxação das arestas para MAX_STATES - 1 vezes
    for (int i = 1; i < MAX_STATES; i++) {
        // Flag para verificar se houve atualização nas distâncias
        int atualizado = 0;
        
        for (int u = 0; u < MAX_STATES; u++) {
            for (int v = 0; v < MAX_STATES; v++) {
                // Se existe aresta e a distância pode ser atualizada
                if (mat_adj[u][v] != 0 && dist[u] != INT_MAX && dist[u] + mat_adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + mat_adj[u][v];
                    prev[v] = u;
                    atualizado = 1;  // Houve atualização
                }
            }
        }
        
        // Se não houve atualização nas distâncias, o loop pode ser interrompido antecipadamente
        if (!atualizado) {
            break;
        }
    }

    // Verifique se existe caminho negativo em ciclos (opcional, só para Bellman-Ford)
    for (int u = 0; u < MAX_STATES; u++) {
        for (int v = 0; v < MAX_STATES; v++) {
            if (mat_adj[u][v] != 0 && dist[u] != INT_MAX && dist[u] + mat_adj[u][v] < dist[v]) {
                printf("Há um ciclo de peso negativo no grafo.\n");
                return;  // Se encontrar um ciclo negativo, termine a execução
            }
        }
    }

    // Após o fim do algoritmo, dist[] contém a menor distância de cada vértice ao nó inicial
}



// Função para exibir o caminho do menor caminho encontrado
void mostrar_caminho(int inicio, int fim, int prev[], int dist[]) {
    if (dist[fim] == INT_MAX) {
        printf("Nao ha caminho acessivel de %d para %d.\n", inicio, fim);
    } else {
        printf("Menor caminho de %d para %d: %d\n", inicio, fim, dist[fim]);

        int caminho[MAX_STATES], ind = 0, atual = fim;
        while (atual != -1) {
            caminho[ind++] = atual;
            atual = prev[atual];
        }

        // Imprimir o caminho
        printf("Caminho: \n");
        for (int i = ind - 1; i >= 0; i--) {
            if (i != ind - 1) {
                printf(" -> ");
            }
            printf("[%d]", caminho[i]);
        }
        printf("\n");
    }
}

// Função para medir o tempo da execução
void medir_tempo() {
    Grafo grafo[MAX_STATES];
    int mat_adj[MAX_STATES][MAX_STATES];

    // Gerar o grafo e a matriz de adjacência
    gerar_grafo(grafo, mat_adj);

    int inicio, fim;
    printf("Digite o indice da configuracao Inicial (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &inicio);
    printf("Digite o indice da configuracao Final (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &fim);

    int dist[MAX_STATES];
    int prev[MAX_STATES];

    clock_t inicio_tempo, fim_tempo;
    inicio_tempo = clock();

    // Executar o algoritmo Bellman-Ford (sem precisar de 'fim' aqui)
    bellman_ford(inicio, prev, dist, mat_adj);

    fim_tempo = clock();

    // Exibir o caminho encontrado
    mostrar_caminho(inicio, fim, prev, dist);

    double tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
    printf("Tempo do algoritmo de Bellman-Ford: %f segundos\n", tempo);
}


int main() {
    medir_tempo();
    return 0;
}


