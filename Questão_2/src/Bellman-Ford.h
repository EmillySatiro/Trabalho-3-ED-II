#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_DISKS 3
#define NUM_PINS  3
#define MAX_STATES 81  // Um exemplo de tamanho máximo para os estados

// Estrutura para representar o Grafo (Estado das Torres de Hanoi)
typedef struct Grafo {
    int estado[NUM_DISKS];  // Estado de cada disco em cada pino
} Grafo;

// Funções principais
int movimento_valido(Grafo *config1, Grafo *config2);   // Verifica se o movimento entre dois estados é válido
void gerar_grafo(Grafo *grafo, int mat_adj[][MAX_STATES]);  // Gera o grafo de todas as configurações válidas
void bellman_ford(int inicio, int prev[], int dist[], int mat_adj[][MAX_STATES]);
void mostrar_caminho(int inicio, int fim, int prev[], int dist[]);  // Mostra o caminho de menor custo encontrado
void medir_tempo();  // Mede o tempo de execução do algoritmo

#endif // BELLMAN_FORD_H
