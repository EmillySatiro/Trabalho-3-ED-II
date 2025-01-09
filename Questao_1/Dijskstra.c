#include "Dijskstra.h"


/**
 * @brief Verifica se o movimento entre duas configurações de um grafo é válido.
 *
 * Esta função compara duas configurações de um grafo e determina se a transição
 * entre elas é válida. Um movimento é considerado válido se houver no máximo
 * uma diferença entre os estados das duas configurações e se essa diferença
 * não violar as regras de movimentação dos discos entre os pinos.
 *
 * @param config1 Ponteiro para a primeira configuração do grafo.
 * @param config2 Ponteiro para a segunda configuração do grafo.
 * @return int Retorna 1 se o movimento for válido, 0 caso contrário.
 */
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

/**
 * @brief Gera o grafo e a matriz de adjacência.
 *
 * Esta função gera o grafo representando os estados possíveis e a matriz de adjacência
 * que indica se um movimento entre dois estados é válido ou não.
 *
 * @param grafo Ponteiro para o grafo que será gerado.
 * @param matriz Matriz de adjacência que será preenchida com 1 para movimentos válidos e 0 para movimentos inválidos.
 *
 * A função primeiro gera os estados possíveis do grafo, determinando o pino de cada disco.
 * Em seguida, preenche a matriz de adjacência verificando se o movimento entre dois estados é válido.
 */
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

/**
 * @brief Executa o algoritmo de Dijkstra para encontrar o caminho mais curto entre dois nós em um grafo.
 *
 * @param inicio O nó inicial de onde o algoritmo começa.
 * @param fim O nó final onde o algoritmo termina.
 * @param prev Vetor que armazena o nó anterior no caminho mais curto para cada nó.
 * @param dist Vetor que armazena a menor distância do nó inicial para cada nó.
 * @param matriz Matriz de adjacência que representa o grafo, onde matriz[i][j] é a distância entre os nós i e j.
 *
 * O algoritmo de Dijkstra encontra o caminho mais curto de um nó inicial para todos os outros nós em um grafo
 * com pesos não negativos. Ele utiliza uma abordagem gulosa para selecionar o nó com a menor distância não visitado
 * e atualiza as distâncias dos seus vizinhos. O processo continua até que todos os nós tenham sido visitados ou
 * que a menor distância restante seja infinita, indicando que os nós restantes são inacessíveis a partir do nó inicial.
 */
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

/**
 * @brief Mostra o estado atual dos discos e seus respectivos pinos.
 *
 * Esta função imprime no console o estado atual de cada disco, indicando
 * em qual pino cada disco está localizado. A função assume que o array
 * `estado` contém a posição de cada disco, onde o índice do array representa
 * o disco e o valor no índice representa o pino.
 *
 * @param estado Array de inteiros que representa o estado atual dos discos.
 */
void mostrar_estado(int estado[]) {
    for (int i = 0; i < NUM_DISKS; i++) {
        printf("Disco %d -> Pino %d\n", i + 1, estado[i]);
    }
}

/**
 * @brief Imprime uma matriz de inteiros.
 *
 * Esta função recebe uma matriz de inteiros e imprime seus elementos
 * no console, organizados em formato de matriz.
 *
 * @param matriz A matriz de inteiros a ser impressa.
 */
void imprimir_matriz(int matriz[][MAX_STATES]) {
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Mostra o menor caminho de um vértice inicial para um vértice final em um grafo, 
 *        bem como as configurações dos discos ao longo do caminho.
 * 
 * @param inicio O vértice inicial.
 * @param fim O vértice final.
 * @param prev Vetor que armazena o vértice anterior para cada vértice no caminho mais curto.
 * @param dist Vetor que armazena a distância mínima de cada vértice a partir do vértice inicial.
 * @param grafo Ponteiro para a estrutura do grafo.
 * 
 * Esta função verifica se existe um caminho acessível do vértice inicial para o vértice final.
 * Se existir, imprime a distância mínima e o caminho do vértice inicial ao vértice final.
 * Além disso, exibe as configurações dos discos em cada estado ao longo do caminho.
 */
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

/**
 * @brief Função para medir o tempo de execução do algoritmo de Dijkstra e interagir com o usuário.
 *
 * Esta função gera um grafo e uma matriz de adjacência, e então apresenta um menu para o usuário
 * escolher entre mostrar o caminho mais curto entre duas configurações, mostrar a matriz de adjacência,
 * ou sair do programa. O tempo de execução do algoritmo de Dijkstra é medido e exibido ao usuário.
 *
 * O menu possui as seguintes opções:
 * 1. Mostrar Caminho: Solicita ao usuário os índices das configurações inicial e final, executa o algoritmo
 *    de Dijkstra para encontrar o caminho mais curto entre essas configurações, e exibe o caminho e o tempo
 *    de execução do algoritmo.
 * 2. Mostrar Matriz de Adjacência: Exibe a matriz de adjacência do grafo.
 * 3. Sair: Encerra o programa.
 *
 * A função continua exibindo o menu até que o usuário escolha a opção de sair.
 */
void medir_tempo() {
    Grafo grafo[MAX_STATES];
    int matriz[MAX_STATES][MAX_STATES];
    gerar_grafo(grafo, matriz);
    int inicio, fim,opcao;
    clock_t inicio_tempo, fim_tempo;
    int dist[MAX_STATES];
    int prev[MAX_STATES];
  
    printf("\n=============================\n");
    printf("    Bem-vindo ao Jogo da Torre de Hanói!\n");
    printf("=============================\n");
    do {
        printf("1. Mostrar Caminho\n");
        printf("2. Mostrar Matriz de Adjacência\n");
        printf("3. Sair\n");
        printf("=============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                printf("Digite o indice da configuracao Inicial (0 a %d): ", MAX_STATES - 1);
                scanf("%d", &inicio);
                printf("Digite o indice da configuracao Final (0 a %d): ", MAX_STATES - 1);
                scanf("%d", &fim);
                inicio_tempo = clock();
                dijkstra(inicio, fim, prev, dist, matriz);
                fim_tempo = clock();
                mostrar_caminho(inicio, fim, prev, dist,grafo);
                double tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
                printf("Tempo do algoritmo de Dijkstra: %f segundos\n", tempo);
                break;
            case 2:
                imprimir_matriz(matriz);
                break;
            case 3:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);
}
