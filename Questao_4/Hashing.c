#include "Hashing.h"

/**
 * @brief Gera uma matrícula aleatória.
 *
 * Esta função preenche a string fornecida com uma sequência de dígitos aleatórios,
 * representando uma matrícula. A string resultante será terminada com um caractere nulo.
 *
 * @param matricula Ponteiro para a string onde a matrícula será armazenada.
 */
void gerar_matricula(char *matricula){
    for (int i = 0; i < TAM_MATRICULA; i++){
        matricula[i] = '0' + rand() % 10;
    }
    matricula[TAM_MATRICULA] = '\0';
}

/**
 * @brief Gera dados aleatórios para um array de funcionários.
 *
 * Esta função preenche um array de estruturas Funcionario com dados aleatórios,
 * incluindo matrícula, nome, função e salário.
 *
 * @param dados Ponteiro para o array de estruturas Funcionario que será preenchido.
 * @param qtd Quantidade de funcionários a serem gerados.
 *
 * As funções possíveis são: "Analista", "Gerente", "Tecnico" e "Assistente".
 * O salário é gerado aleatoriamente entre 3000 e 15000.
 */
void gerar_dados(Funcionario *dados, int qtd){
    char *funcoes[] = {"Analista", "Gerente", "Tecnico", "Assistente"};
    int num_funcoes = sizeof(funcoes)/ sizeof(funcoes[0]);

     for (int i = 0; i < qtd; i++) {
        gerar_matricula(dados[i].matricula);
        snprintf(dados[i].nome, sizeof(dados[i].nome), "Funcionario_%s", dados[i].matricula);
        strcpy(dados[i].funcao, funcoes[rand() % num_funcoes]);
        dados[i].salario = 3000 + ((float)rand() / RAND_MAX) * (15000 - 3000);
    }

}

/**
 * @brief Aloca uma tabela de hashing com o tamanho especificado.
 *
 * Esta função aloca memória para uma tabela de hashing com o tamanho fornecido.
 * Se a alocação de memória falhar, a função imprime uma mensagem de erro e encerra o programa.
 * Caso contrário, imprime uma mensagem de sucesso com o tamanho da tabela alocada.
 *
 * @param tamanho_tabela O tamanho da tabela de hashing a ser alocada.
 * @return Um ponteiro para a tabela de hashing alocada.
 */
Tabela_hashing* alocar_tabela(int tamanho_tabela) {
 
    
    Tabela_hashing *tabela = (Tabela_hashing*)calloc(tamanho_tabela, sizeof(Tabela_hashing));
    if (!tabela) {
        
        fprintf(stderr, "Erro ao alocar memória para a tabela hash.\n");
        exit(EXIT_FAILURE);
    }

   
    printf("Tabela alocada com sucesso. Tamanho: %d\n", tamanho_tabela);
    return tabela;
}

/**
 * @brief Desaloca a memória utilizada pela tabela de hashing.
 *
 * Esta função percorre a tabela de hashing e libera a memória alocada
 * para cada elemento não nulo. Em seguida, libera a memória da própria
 * tabela.
 *
 * @param tabela Ponteiro para a tabela de hashing a ser desalocada.
 * @param tamanho_tabela Tamanho da tabela de hashing.
 */
void desalocar_tabela(Tabela_hashing* tabela, int tamanho_tabela) {
    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i].funcionairo != NULL) {
            free(tabela[i].funcionairo);
        }
    }
    free(tabela);
}

/**
 * @brief Aloca e inicializa um novo funcionário com os dados fornecidos.
 *
 * Esta função aloca memória para um novo funcionário e inicializa seus campos
 * com os valores fornecidos. Se a alocação de memória falhar, a função imprime
 * uma mensagem de erro e encerra o programa.
 *
 * @param matricula A matrícula do funcionário (string).
 * @param nome O nome do funcionário (string).
 * @param funcao A função do funcionário (string).
 * @param salario O salário do funcionário (float).
 * @return Um ponteiro para o novo funcionário alocado e inicializado.
 */
Funcionario* alocar_funcionario(char* matricula,char* nome,char* funcao, float salario) {
    Funcionario* novo_funcionario = (Funcionario*)malloc(sizeof(Funcionario));
    if (!novo_funcionario) {
        fprintf(stderr, "Erro ao alocar memória para o funcionário.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(novo_funcionario->matricula, matricula, TAM_MATRICULA);
    novo_funcionario->matricula[TAM_MATRICULA] = '\0';
    strncpy(novo_funcionario->nome, nome, sizeof(novo_funcionario->nome) - 1);
    novo_funcionario->nome[sizeof(novo_funcionario->nome) - 1] = '\0';
    strncpy(novo_funcionario->funcao, funcao, sizeof(novo_funcionario->funcao) - 1);
    novo_funcionario->funcao[sizeof(novo_funcionario->funcao) - 1] = '\0';
    novo_funcionario->salario = salario;
    return novo_funcionario;
}

/**
 * @brief Calcula o valor de hash de uma matrícula utilizando rotação de caracteres.
 *
 * Esta função realiza a rotação dos caracteres de uma matrícula, somando os dígitos
 * nas posições 2, 4 e 6 da matrícula rotacionada e calcula o valor de hash com base
 * no tamanho da tabela de hash fornecida.
 *
 * @param matricula A string contendo a matrícula a ser processada. Deve ter pelo menos 6 caracteres.
 * @param tamanho_tabela O tamanho da tabela de hash.
 * @return O valor de hash calculado se a matrícula for válida, ou -1 se a matrícula for inválida.
 */
int hashing_rotacao(char *matricula, int tamanho_tabela) {
    int resultado_final = 0;
    int valido = 1;

    int len = strlen(matricula);// só pra ver se ela ta no tamanho certinho 
    if (len < 6) {
        valido = 0;
    }

    if (valido) {
       char matricula_rotacionada[10]; 
       strcpy(matricula_rotacionada, matricula + 2);// aqui eu pego a matricula depois dos dois primerios numeros 
       strncat(matricula_rotacionada , matricula, 2);// aqui eu coloco eles no final 

       int digitos_2_4_6 = (matricula_rotacionada[1] - '0') + (matricula_rotacionada[3] - '0') + (matricula_rotacionada[5] - '0');

       resultado_final = digitos_2_4_6 % tamanho_tabela; 

    }
     
    return valido ? resultado_final : -1;
}

/**
 * @brief Calcula o índice de hash para uma matrícula utilizando a técnica de Fole Shift.
 *
 * Esta função recebe uma string de matrícula e o tamanho da tabela de hash, e calcula
 * um índice de hash baseado na soma de dígitos específicos da matrícula. Se a matrícula
 * tiver menos de 6 caracteres, a função retorna -1 indicando que a matrícula é inválida.
 *
 * @param matricula A string contendo a matrícula a ser processada. Deve ter pelo menos 6 caracteres.
 * @param tamanho_tabela O tamanho da tabela de hash.
 * @return O índice de hash calculado se a matrícula for válida, ou -1 se a matrícula for inválida.
 */
int Fole_shift(char *matricula, int tamanho_tabela) {
    int resultado_final = 0;
    int valido = 1;

    int len = strlen(matricula); // só conferindo dnv
    if (len < 6) {
        valido = 0;
    }

    if (valido) {
        int digitos1_3_6 = (matricula[0] - '0') + (matricula[2] - '0') + (matricula[5] - '0');
        int digitos2_4_5 = (matricula[1] - '0') + (matricula[3] - '0') + (matricula[4] - '0');
        int soma  = digitos1_3_6 + digitos2_4_5;
        resultado_final = soma % tamanho_tabela;
    }

    return valido ? resultado_final : -1;
}

/**
 * @brief Insere um novo funcionário na tabela de hashing utilizando o método de rotação A.
 *
 * @param tabela Ponteiro para a tabela de hashing.
 * @param novo_funcionario Estrutura contendo os dados do novo funcionário a ser inserido.
 * @param tamanho_tabela Tamanho da tabela de hashing.
 *
 * A função tenta inserir o novo funcionário na posição calculada pela função de hashing
 * e, em caso de colisão, utiliza a técnica de rotação A para encontrar uma nova posição.
 * Se a tabela estiver cheia, o funcionário na posição inicial será substituído pelo novo funcionário.
 */
void inserir_na_tabela_hashing_rotacao_A(Tabela_hashing *tabela, Funcionario novo_funcionario, int tamanho_tabela) {
    int posicao_inicial = hashing_rotacao(novo_funcionario.matricula, tamanho_tabela);
    int incremento = novo_funcionario.matricula[0] - '0';

    int inserido = 0;
    // inserção foi concluída ou nem 

    for (int tentativa = 0; tentativa < tamanho_tabela && !inserido; tentativa++) {
        int posicao = (posicao_inicial + tentativa * incremento) % tamanho_tabela;

        if (tabela[posicao].funcionairo == NULL) {
          
            tabela[posicao].funcionairo = alocar_funcionario(novo_funcionario.matricula, novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
            inserido = 1; //concluída
        } else {
            tabela[posicao].colisoes++;
        }
    }

    // Se a tabela estiver cheia
    if (!inserido) {
        if (tabela[posicao_inicial].funcionairo != NULL) {
            free(tabela[posicao_inicial].funcionairo); 
        }
        tabela[posicao_inicial].funcionairo = alocar_funcionario(novo_funcionario.matricula, novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
    }
}

/**
 * @brief Insere um novo funcionário na tabela de hashing utilizando a técnica de Fole Shift com passo 7.
 *
 * @param tabela Ponteiro para a tabela de hashing.
 * @param novo_funcionario Estrutura contendo os dados do novo funcionário a ser inserido.
 * @param tamanho_tabela Tamanho da tabela de hashing.
 *
 * A função tenta inserir o novo funcionário na posição calculada pela função Fole_shift.
 * Em caso de colisão, a função tenta inserir o funcionário na próxima posição disponível,
 * utilizando um passo de 7 posições. Se a tabela estiver cheia, o funcionário na posição
 * inicial é substituído pelo novo funcionário.
 */
void inserir_fole_shift_B(Tabela_hashing *tabela, Funcionario novo_funcionario, int tamanho_tabela) {
    int posicao_inicial = Fole_shift(novo_funcionario.matricula, tamanho_tabela);
    int inserido = 0;
    // inserção foi concluída ou nem 

    for (int tentativa = 0; tentativa < tamanho_tabela && !inserido; tentativa++) {
        int posicao = (posicao_inicial + tentativa * 7) % tamanho_tabela;

        if (tabela[posicao].funcionairo == NULL) {
          
            tabela[posicao].funcionairo = alocar_funcionario(novo_funcionario.matricula, novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
            inserido = 1; //concluída
        } else {
            tabela[posicao].colisoes++;
        }
    }

    // Se a tabela estiver cheia
    if (!inserido) {
        if (tabela[posicao_inicial].funcionairo != NULL) {
            free(tabela[posicao_inicial].funcionairo); 
        }
        tabela[posicao_inicial].funcionairo = alocar_funcionario(novo_funcionario.matricula, novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
    }
}

/**
 * @brief Imprime as estatísticas da tabela de hashing.
 *
 * Esta função percorre a tabela de hashing e calcula o número de entradas
 * ocupadas e o número total de colisões. Em seguida, imprime essas estatísticas.
 *
 * @param tabela Ponteiro para a tabela de hashing.
 * @param tamanho_tabela Tamanho da tabela de hashing.
 */
void imprimir_estatisticas(Tabela_hashing* tabela, int tamanho_tabela) {
    int num_entradas = 0;
    int num_colisoes = 0;

    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i].funcionairo != NULL) {
           num_entradas ++;
        }
        num_colisoes += tabela[i].colisoes;
    }

    printf("Estatísticas da Tabela Hash:\n");
    printf("Número de oculpação: %d\n", num_entradas);
    printf("Número de colisões: %d\n", num_colisoes);
   
}