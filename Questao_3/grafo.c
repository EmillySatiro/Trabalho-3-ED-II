#include "grafo.h"


/**
 * @brief Inicializa o grafo com vértices e arestas.
 *
 * Esta função inicializa um grafo, atribuindo um ID a cada vértice e
 * configurando a confiabilidade das arestas para 0.0.
 *
 * @param grafo Ponteiro para o grafo a ser inicializado.
 */
void inicializar_Grafo(Grafo *grafo) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        grafo->vertices[i].id = i;
    }
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            grafo->arestas[i][j].confiabilidade = 0.0;
        }
    }
}

/**
 * @brief Exibe a matriz de confiabilidade do grafo.
 *
 * Esta função imprime a matriz de confiabilidade do grafo no console.
 * A matriz de confiabilidade é representada por uma matriz de adjacência
 * onde cada elemento indica a confiabilidade da aresta entre dois vértices.
 *
 * @param grafo Ponteiro para o grafo a ser exibido.
 */
void exibir_Grafo(const Grafo *grafo) {
    printf("\n===============================\n");
    printf("Matriz de Confiabilidade do Grafo\n");
    printf("===============================\n");
    printf("      ");
    for (int i = 0; i < NUM_VERTICES; i++) {
        printf("V%-2d  ", i);  
    }
    printf("\n");

    for (int i = 0; i < NUM_VERTICES; i++) {
        printf("V%-2d | ", i);  
        for (int j = 0; j < NUM_VERTICES; j++) {
            printf("%.2f ", grafo->arestas[i][j]);  
        }
        printf("\n");
    }
    printf("\n===============================\n");
}

/**
 * @brief Preenche as arestas do grafo com valores de confiabilidade aleatórios.
 *
 * Esta função inicializa o gerador de números aleatórios com a semente baseada no tempo atual
 * e percorre todas as arestas do grafo, atribuindo a cada uma delas um valor de confiabilidade
 * aleatório entre 0.1 e CONFIABILIDADE_MAX.
 *
 * @param grafo Ponteiro para a estrutura do grafo que terá suas arestas preenchidas.
 */
void preencher_Arestas_Aleatoriamente(Grafo *grafo) {
    srand(time(NULL)); 
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = i + 1; j < NUM_VERTICES; j++) {
            double confiabilidade = 0.1 + ((double)rand() / RAND_MAX) * (CONFIABILIDADE_MAX - 0.1);
            grafo->arestas[i][j].confiabilidade = confiabilidade;
            grafo->arestas[j][i].confiabilidade = confiabilidade;
        }
    }
}

/**
 * @brief Executa o algoritmo de Dijkstra para encontrar o caminho mais confiável em um grafo.
 *
 * Esta função calcula o caminho mais confiável a partir de um vértice de origem para todos os outros vértices
 * em um grafo, utilizando o algoritmo de Dijkstra. A confiabilidade de um caminho é definida como o produto
 * das confiabilidades das arestas ao longo do caminho.
 *
 * @param grafo Ponteiro para a estrutura do grafo.
 * @param origem Índice do vértice de origem.
 * @param predecessor Vetor que armazenará o predecessor de cada vértice no caminho mais confiável.
 * @param distancia Vetor que armazenará a confiabilidade do caminho mais confiável para cada vértice.
 *
 * @note A função assume que o grafo é representado por uma matriz de adjacência onde cada entrada contém
 *       a confiabilidade da aresta entre dois vértices. A confiabilidade é um valor entre 0.0 e 1.0.
 * @note O número de vértices no grafo é definido pela constante NUM_VERTICES.
 * @note Se o vértice de origem for inválido (menor que 0 ou maior ou igual a NUM_VERTICES), a função
 *       imprimirá uma mensagem de erro e não executará o algoritmo.
 */
void dijkstra(Grafo *grafo, int origem, int *predecessor, double *distancia) {
    if (origem < 0 || origem >= NUM_VERTICES) {
        printf("Erro: Vértice de origem inválido.\n");
    }else{
        bool visitado[NUM_VERTICES] = {false};

  
        for (int i = 0; i < NUM_VERTICES; i++) {
            distancia[i] = -1.0; 
            predecessor[i] = -1;
        }

        distancia[origem] = 1.0; 

        for (int i = 0; i < NUM_VERTICES; i++) {
            int verticeAtual = -1;

            for (int j = 0; j < NUM_VERTICES; j++) {
                if (!visitado[j] && (verticeAtual == -1 || distancia[j] > distancia[verticeAtual])) {
                    verticeAtual = j;
                }
            }

            if (verticeAtual != -1 || distancia[verticeAtual] != 0.0) {
                visitado[verticeAtual] = true; 

                for (int j = 0; j < NUM_VERTICES; j++) {
                    if (grafo->arestas[verticeAtual][j].confiabilidade > 0.0) {

                        double novaDistancia = distancia[verticeAtual] * grafo->arestas[verticeAtual][j].confiabilidade;
                
                        if (novaDistancia > distancia[j]) {
                            distancia[j] = novaDistancia; 
                            predecessor[j] = verticeAtual; 
                        }
                    }
                }
            }

        }
    }
    
}

/**
 * @brief Exibe o caminho mais confiável de um vértice de origem até um vértice de destino em um grafo.
 *
 * Esta função imprime o caminho mais confiável de um vértice de origem até um vértice de destino,
 * bem como a confiabilidade total desse caminho. Se não houver caminho para o vértice de destino,
 * uma mensagem informando isso será exibida.
 *
 * @param predecessor Vetor de predecessores que indica o caminho mais confiável para cada vértice.
 * @param destino O vértice de destino para o qual o caminho será exibido.
 * @param grafo Ponteiro para a estrutura do grafo que contém as arestas e suas confiabilidades.
 */
void exibir_Caminho(int *predecessor, int destino, Grafo *grafo) {
    if (predecessor[destino] == -1) {
        printf("Não há caminho para o vértice %d\n", destino);
    }else{
        printf("\nCaminho Mais Confiável:\n");
        int caminho[NUM_VERTICES];
        int idx = 0;
        for (int v = destino; v != -1; v = predecessor[v]) {
            caminho[idx++] = v;
        }

        for (int i = idx - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
            if (i > 0) printf("-> ");
        }

        double confiabilidade_total = 1.0;
        for (int i = 1; i < idx; i++) {
            int u = caminho[i - 1];
            int v = caminho[i];
            confiabilidade_total *= grafo->arestas[u][v].confiabilidade;
        }

        printf("\nConfiabilidade Total : %.5f\n", confiabilidade_total);
    }
}
