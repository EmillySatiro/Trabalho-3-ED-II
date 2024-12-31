#ifndef DIJSKSTRA_H
#define DIJSKSTRA_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>


#define NUM_PINS 3        // Número de pinos
#define NUM_DISKS 4       // Número de discos
#define MAX_STATES 81     // Total de configurações possíveis (3^4 para 4 discos e 3 pinos)

// Estrutura para armazenar as configurações
typedef struct {
    int estado[NUM_DISKS];  // Pinos onde cada disco está
} Grafo;


int movimento_valido(Grafo *config1, Grafo *config2);
// Função para gerar o grafo de movimentos
void gerar_grafo(Grafo *grafo, int mat_adj[][MAX_STATES]);
// Função de Dijkstra para encontrar o caminho mais curto
void dijkstra(int inicio, int fim, int prev[], int dist[], int mat_adj[][MAX_STATES]);

// Função para mostrar o caminho encontrado por Dijkstra
void mostrar_caminho(int inicio, int fim, int prev[], int dist[]);
// Função para medir o tempo de execução
void medir_tempo();
#endif