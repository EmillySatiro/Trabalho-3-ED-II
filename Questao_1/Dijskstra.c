
#include "Dijskstra.h"

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
        valido = 0; //inválido
    } else {
        
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


void gerar_grafo(Grafo *grafo, int mat_adj[][MAX_STATES]) {
    for (int i = 0; i < MAX_STATES; i++) {
        int num = i;
        for (int disco = 0; disco < NUM_DISKS; disco++) {
            grafo[i].estado[disco] = num % NUM_PINS + 1;
            num /= NUM_PINS;
        }
    }

    //  matriz de adjacência
    for (int x = 0; x < MAX_STATES; x++) {
        for (int y = 0; y < MAX_STATES; y++) {
            if (movimento_valido(&grafo[x], &grafo[y])) {
                mat_adj[x][y] = 1;  // Movimento válido
            } else {
                mat_adj[x][y] = 0;  // Movimento inválido
            }
        }
    }
}


void dijkstra(int inicio, int fim, int prev[], int dist[], int mat_adj[][MAX_STATES]) {
    
    for (int i = 0; i < MAX_STATES; i++) {
        prev[i] = -1;
        dist[i] = INT_MAX;
    }

    dist[inicio] = 0;
    int atualizado = 1;


    while (atualizado) {
        atualizado = 0;
        for (int j = 0; j < MAX_STATES; j++) {
            if (dist[j] != INT_MAX) {
                for (int k = 0; k < MAX_STATES; k++) {
                    if (mat_adj[j][k] != 0 && dist[j] + mat_adj[j][k] < dist[k]) {
                        dist[k] = dist[j] + mat_adj[j][k];
                        prev[k] = j;
                        atualizado = 1;
                    }
                }
            }
        }
    }
}


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

        // Imprimir o caminho no formato de grafo
        printf("Caminho: \n");
        for (int i = ind - 1; i >= 0; i--) {
            if (i != ind - 1) {
                printf(" -> ");
            }
            printf("[%d]", caminho[i]);
        }
        printf("\n");

        // Opção de visualização como grafo com setas
        printf("\nVisualizando o caminho no formato de grafo:\n");
        for (int i = ind - 1; i > 0; i--) {
            printf("(%d) --[Aresta]--> (%d)\n", caminho[i], caminho[i - 1]);
        }
    }

}


void medir_tempo() {
    Grafo grafo[MAX_STATES];
    int mat_adj[MAX_STATES][MAX_STATES];

   
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

 
    dijkstra(inicio, fim, prev, dist, mat_adj);

    fim_tempo = clock();

    mostrar_caminho(inicio, fim, prev, dist);

    double tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
    printf("Tempo do algoritmo de Dijkstra: %f segundos\n", tempo);
}
