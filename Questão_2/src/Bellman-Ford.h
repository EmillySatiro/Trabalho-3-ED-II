#ifdef BELLMAN_FORD_H
#define BELLMAN_FORD_H



int movimento_valido(Grafo *config1, Grafo *config2);
// Função para gerar o grafo representando todos os estados possíveis e as transições válidas entre eles
void gerar_grafo(Grafo *grafo, int mat_adj[][MAX_STATES]);

// Algoritmo Bellman-Ford para encontrar o caminho mínimo em um grafo
void bellman_ford(int inicio, int fim, int prev[], int dist[], int mat_adj[][MAX_STATES]);

// Função para mostrar o caminho encontrado
void mostrar_caminho(int inicio, int fim, int prev[], int dist[]);

// Função para medir o tempo do algoritmo
void medir_tempo();


#endif