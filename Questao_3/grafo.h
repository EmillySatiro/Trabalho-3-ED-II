#ifndef GRAFO_H
#define GRAFO_H


#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>


#define NUM_VERTICES 10
#define CONFIABILIDADE_MAX 1.0


typedef struct {
    int id;
} Vertice;

typedef struct {
    double confiabilidade;
} Aresta;

typedef struct {
    Vertice vertices[NUM_VERTICES];
    Aresta arestas[NUM_VERTICES][NUM_VERTICES];
} Grafo;


void inicializar_Grafo(Grafo *grafo);
void exibir_Grafo(const Grafo *grafo);
void preencher_Arestas_Aleatoriamente(Grafo *grafo);
void dijkstra(Grafo *grafo, int origem, int *predecessor, double *distancia);
void exibir_Caminho(int *predecessor, int destino, Grafo *Grafo);

#endif
