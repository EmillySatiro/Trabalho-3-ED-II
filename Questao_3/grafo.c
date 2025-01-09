#include "grafo.h"

// Funções auxiliares para manipular MinHeap
void initMinHeap(MinHeap* minHeap) {
    minHeap->size = 0;
}

void swapHeapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->heap[left].reliability < minHeap->heap[smallest].reliability)
        smallest = left;
    if (right < minHeap->size && minHeap->heap[right].reliability < minHeap->heap[smallest].reliability)
        smallest = right;
    if (smallest != index) {
        swapHeapNode(&minHeap->heap[smallest], &minHeap->heap[index]);
        heapify(minHeap, smallest);
    }
}

HeapNode extractMin(MinHeap* minHeap) {
    HeapNode root = minHeap->heap[0];
    minHeap->heap[0] = minHeap->heap[minHeap->size - 1];
    --minHeap->size;
    heapify(minHeap, 0);
    return root;
}

void decreaseKey(MinHeap* minHeap, int vertex, double reliability) {
    int i;
    for (i = 0; i < minHeap->size; ++i) {
        if (minHeap->heap[i].vertex == vertex) {
            minHeap->heap[i].reliability = reliability;
            break;
        }
    }

    while (i != 0 && minHeap->heap[(i - 1) / 2].reliability > minHeap->heap[i].reliability) {
        swapHeapNode(&minHeap->heap[i], &minHeap->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insertMinHeap(MinHeap* minHeap, int vertex, double reliability) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    minHeap->heap[i].vertex = vertex;
    minHeap->heap[i].reliability = reliability;

    while (i != 0 && minHeap->heap[(i - 1) / 2].reliability > minHeap->heap[i].reliability) {
        swapHeapNode(&minHeap->heap[i], &minHeap->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Dijkstra para encontrar o caminho mais confiável
double dijkstra(Edge* graph[MAX], int vertices, int origem, int destino) {
    double dist[MAX];
    int visited[MAX];
    MinHeap minHeap;

    // Inicializar
    for (int i = 0; i < vertices; ++i) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[origem] = 0;
    initMinHeap(&minHeap);
    insertMinHeap(&minHeap, origem, 0);

    while (minHeap.size > 0) {
        HeapNode minNode = extractMin(&minHeap);
        int u = minNode.vertex;

        if (visited[u]) continue;
        visited[u] = 1;

        for (int i = 0; graph[u][i].v != -1; ++i) {
            int v = graph[u][i].v;
            double weight = -log(graph[u][i].weight);

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                insertMinHeap(&minHeap, v, dist[v]);
            }
        }
    }

    return exp(-dist[destino]); // Converter o log de volta para a confiabilidade
}
