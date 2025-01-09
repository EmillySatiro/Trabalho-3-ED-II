#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


#define INF 1e9
#define MAX 100

typedef struct {
    int v; // Vértice de destino
    double weight; // Confiabilidade (r(u, v))
} Edge;

typedef struct {
    int u, v; // Aresta (u -> v)
    double weight; // Confiabilidade
} Node;

typedef struct {
    int vertex;
    double reliability; // Log da confiabilidade acumulada
} HeapNode;

typedef struct {
    HeapNode heap[MAX];
    int size;
} MinHeap;


// Funções auxiliares para manipular MinHeap
void initMinHeap(MinHeap* minHeap);
void swapHeapNode(HeapNode* a, HeapNode* b);
void heapify(MinHeap* minHeap, int index);
HeapNode extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int vertex, double reliability);
void insertMinHeap(MinHeap* minHeap, int vertex, double reliability);
// Dijkstra para encontrar o caminho mais confiável
double dijkstra(Edge* graph[MAX], int vertices, int origem, int destino);



#endif