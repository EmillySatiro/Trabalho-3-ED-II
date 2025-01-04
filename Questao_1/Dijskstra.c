
#include "Dijskstra.h"

int movimento_valido(Grafo *config_incial, Grafo *config_final) {
    int diferencas = 0;
    int indice_diferenca = -1;
    int valido = 1; // valido 

   
    //contar o numero de diferenças no bagulho 
    for (int i = 0; i < NUM_PINS; i++){
        if(config_incial->estado[i] !=  config_final->estado[i]) {
            diferencas++;
            indice_diferenca = i;
        }
    }
    // conferindo se tem mais de uma diferença 
    if (diferencas > 1){
        valido = 0; 
    }
    
    // verificar se os movimentos valem baseado na posição da diferença 
     for (int i = 0; i < NUM_PINS; ++i) {
        if (movimento_valido && i != indice_diferenca) {
            int pino_inicial = (config_incial->estado[i] == config_incial->estado[indice_diferenca]);
            int pino_final = (config_final->estado[i] == config_final->estado[indice_diferenca]);
            
            if ((pino_inicial || pino_final) && i < indice_diferenca) {
                valido = 0; // conflito com outro disco
            }
        }
    }
    return valido; 
}


void gerar_grafo(Grafo *grafo, int matriz[][MAX_STATES]) {
    // gerando o estado do bagulho
    for (int i = 0; i < MAX_STATES; i++) {
        int num = i;
        for (int disco = 0; disco < NUM_DISKS; disco++) {
            grafo[i].estado[disco] = num % NUM_PINS + 1; //determina o pino do disco
            num /= NUM_PINS;// move o disco
        }
    }

    //  matriz de adjacência
    for (int x = 0; x < MAX_STATES; x++) {
        for (int y = 0; y < MAX_STATES; y++) {
            if (movimento_valido(&grafo[x], &grafo[y])) {
                matriz[x][y] = 1;  // válido
            } else {
                matriz[x][y] = 0;  // inválido
            }
        }
    }
}


void dijkstra(int inicio, int fim, int prev[], int dist[], int matriz[][MAX_STATES]) {
    // Inicializa as distancias
    for (int i = 0; i < MAX_STATES; i++) {
        prev[i] = -1;
        dist[i] = INT_MAX; // infinito
    }

    dist[inicio] = 0; 
    bool visitado[MAX_STATES] = {false}; // já foram visitados

    // Laço principal para o algoritmo de Dijkstra
    for (int i = 0; i < MAX_STATES; i++) {
        // Encontra o nó n visitado com a menor distância
        int u = -1;
        for (int j = 0; j < MAX_STATES; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        // Se a distância mínima for infinita n tem caminho para o restante dos nós
        if (dist[u] == INT_MAX) {
            break; // Não precisa mais buscar caminhos
        }

        visitado[u] = true; //  visitado

        // Atualiza as distancias dos vizinhos de u
        for (int k = 0; k < MAX_STATES; k++) {
            // Se uma aresta u -> k e k ainda n foi visitado
            if (matriz[u][k] != 0 && !visitado[k]) {
                int alt = dist[u] + matriz[u][k];
                // Se a distancia alternativa for menoratualiza
                if (alt < dist[k]) {
                    dist[k] = alt;
                    prev[k] = u;
                }
            }
        }
    }
}


void mostrar_estado(int estado[]) {
    for (int i = 0; i < NUM_DISKS; i++) {
        printf("Disco %d -> Pino %d\n", i + 1, estado[i]);
    }
}
void imprimir_matriz(int matriz[][MAX_STATES]) {
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}
void mostrar_caminho(int inicio, int fim, int prev[], int dist[], Grafo *grafo) {
    if (dist[fim] == INT_MAX) {
        printf("Nao ha caminho acessivel de %d para %d.\n", inicio, fim);
    } else {
        printf("Menor caminho de %d para %d: %d\n", inicio, fim, dist[fim]);

        int caminho[MAX_STATES], ind = 0, atual = fim;
        while (atual != -1) {
            caminho[ind++] = atual;
            atual = prev[atual];
        }
        // mostrar da origem para o destino
        printf("Caminho: ");
        for (int i = ind - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
            if (i != 0) {
                printf("-> ");
            }
        }
        printf("\n");

        // discos ao longo do caminho
        printf("Configuracoes dos discos ao longo do caminho:\n");
        for (int i = 0; i < ind; i++) {
            printf("Estado %d:\n", caminho[i]);
            mostrar_estado(grafo[caminho[i]].estado);  // Exibe discos em cada estado
        }
    
    }

}


void medir_tempo() {
    Grafo grafo[MAX_STATES];
    int matriz[MAX_STATES][MAX_STATES];

   
    gerar_grafo(grafo, matriz);

    int inicio, fim;
    printf("Digite o indice da configuracao Inicial (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &inicio);
    printf("Digite o indice da configuracao Final (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &fim);

    int dist[MAX_STATES];
    int prev[MAX_STATES];

    clock_t inicio_tempo, fim_tempo;
    inicio_tempo = clock();

 
    dijkstra(inicio, fim, prev, dist, matriz);

    fim_tempo = clock();

    mostrar_caminho(inicio, fim, prev, dist,grafo);

    double tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
    printf("Tempo do algoritmo de Dijkstra: %f segundos\n", tempo);
}
