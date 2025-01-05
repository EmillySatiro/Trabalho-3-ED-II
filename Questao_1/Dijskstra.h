#ifndef DIJSKSTRA_H
#define DIJSKSTRA_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>  
#include <stdbool.h> 


#define NUM_PINS 3      
#define NUM_DISKS 4       
#define MAX_STATES 81     //  (3^4 para 4 discos e 3 pinos)


typedef struct {
    int estado[NUM_DISKS]; 
} Grafo;

int movimento_valido(Grafo *config_incial, Grafo *config_final);

void gerar_grafo(Grafo *grafo, int matriz[][MAX_STATES]);

void dijkstra(int inicio, int fim, int prev[], int dist[], int matriz[][MAX_STATES]);

void mostrar_estado(int estado[]);

void mostrar_caminho(int inicio, int fim, int prev[], int dist[], Grafo *grafo);

void medir_tempo();

void imprimir_matriz(int matriz[][MAX_STATES]);

#endif