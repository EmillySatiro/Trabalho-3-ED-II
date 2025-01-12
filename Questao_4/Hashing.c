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
 * Inicializa cada entrada da tabela com valores padrão.
 *
 * @param tamanho_tabela O tamanho da tabela de hashing a ser alocada.
 * @return Um ponteiro para a tabela de hashing alocada. Retorna NULL se a alocação falhar.
 */
Tabela_hashing* alocar_tabela(int tamanho_tabela) {
    Tabela_hashing *tabela = (Tabela_hashing*)malloc(tamanho_tabela* sizeof(Tabela_hashing));
    if (tabela == NULL) {
      printf("erro na alocação da tabela!!");
       
    }else{
        for (int i = 0; i < tamanho_tabela; i++){
        tabela[i].funcionairo = NULL;
        tabela[i].colisoes = 0;
       }
        
    }
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
    if (novo_funcionario == NULL) {
        printf("Erro ao alocar memória para o funcionário.\n");
        
    }else{
            strncpy(novo_funcionario->matricula, matricula, TAM_MATRICULA);
            novo_funcionario->matricula[TAM_MATRICULA] = '\0';
            strncpy(novo_funcionario->nome, nome, sizeof(novo_funcionario->nome) - 1);
            novo_funcionario->nome[sizeof(novo_funcionario->nome) - 1] = '\0';
            strncpy(novo_funcionario->funcao, funcao, sizeof(novo_funcionario->funcao) - 1);
            novo_funcionario->funcao[sizeof(novo_funcionario->funcao) - 1] = '\0';
            novo_funcionario->salario = salario;
    }
    
  
    return novo_funcionario;
}

/**
 * Função: hashing_rotacao
 * Calcula um valor de hash baseado na rotação de caracteres de uma matrícula.
 *
 * Parâmetros:
 *  - matricula: uma string representando a matrícula a ser processada.
 *  - tamanho_tabela: o tamanho da tabela de hash.
 *
 * Retorna:
 *  - Um valor inteiro representando o índice na tabela de hash.
 *  - Retorna -1 se ocorrer algum erro no processamento.
 *
 * Descrição:
 *  A função realiza uma rotação nos caracteres da matrícula, concatenando os dois últimos caracteres
 *  com os quatro primeiros. Em seguida, calcula a soma dos caracteres nas posições 2, 4 e 6 da nova
 *  string rotacionada, subtrai o valor ASCII do caractere '0' para obter os valores numéricos e calcula
 *  o módulo dessa soma pelo tamanho da tabela de hash. O resultado é o índice na tabela de hash.
 */
int hashing_rotacao(char *matricula, int tamanho_tabela) {
    int resultado_final = -1;
   
    char matricula_rotacionada[TAM_MATRICULA + 1]; 
    strncpy(matricula_rotacionada, matricula + 4, 2); 
    strncpy(matricula_rotacionada + 2, matricula, 4); 
    matricula_rotacionada[6] = '\0';

       
        if (strlen(matricula_rotacionada) >= 6) {
            int digitos_2_4_6 = (matricula_rotacionada[1] - '0') + (matricula_rotacionada[3] - '0') + (matricula_rotacionada[5] - '0');
            resultado_final = digitos_2_4_6 % tamanho_tabela;
        } 
    return resultado_final; 
}

/**
 * @brief Calcula o índice de hash para uma matrícula utilizando a técnica de Fole Shift.
 *
 * Esta função recebe uma string de matrícula e o tamanho da tabela de hash, e calcula
 * um índice de hash baseado em uma combinação específica de dígitos da matrícula.
 *
 * @param matricula Uma string representando a matrícula. Espera-se que a string tenha pelo menos 6 caracteres.
 * @param tamanho_tabela O tamanho da tabela de hash.
 * @return O índice de hash calculado.
 */
int Fole_shift(char *matricula, int tamanho_tabela) {
    int resultado_final = 0; 

    int digitos1_3_6 = (matricula[0] - '0') * 100 + (matricula[2] - '0')* 10 + (matricula[5] - '0');
    int digitos2_4_5 = (matricula[1] - '0') * 100 + (matricula[3] - '0') * 10  + (matricula[4] - '0');
    int soma  = digitos1_3_6 + digitos2_4_5;
    resultado_final = soma % tamanho_tabela;
    

    return resultado_final;
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

    int posicao_inicial = hashing_rotacao(novo_funcionario.matricula, tamanho_tabela ) % tamanho_tabela;
    int inserido = 0;


    int posicao = posicao_inicial;
    int incremento = novo_funcionario.matricula[0] - '0';  
        if (incremento == 0) {
            incremento = 1;
        }
       
       do{
       
        if (tabela[posicao].funcionairo == NULL)
        {
            inserido = 1; 
            tabela[posicao].funcionairo = alocar_funcionario(novo_funcionario.matricula,  novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
        }else{
            tabela[posicao].colisoes ++;
            posicao = ((posicao % tamanho_tabela) + incremento +1 );
        }
        
       } while (!inserido && posicao != posicao_inicial && posicao < tamanho_tabela);
       
       if (!inserido){
        free(tabela[posicao_inicial].funcionairo); 
        tabela[posicao_inicial].funcionairo = alocar_funcionario(novo_funcionario.matricula,  novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
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
    int posicao_inicial = Fole_shift(novo_funcionario.matricula, tamanho_tabela) % tamanho_tabela;
    int inserido = 0;
    int posicao = posicao_inicial;
    
    do{

        if (tabela[posicao].funcionairo == NULL)
        {
            inserido = 1; 
            tabela[posicao].funcionairo = alocar_funcionario(novo_funcionario.matricula,  novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
        }else{
            tabela[posicao].colisoes++; 

            posicao = ((posicao % tamanho_tabela) +7 +1); 

        }
        
       
    } while (!inserido && posicao != posicao_inicial && posicao < tamanho_tabela);
    if (!inserido){
        free(tabela[posicao_inicial].funcionairo); 
        tabela[posicao_inicial].funcionairo = alocar_funcionario(novo_funcionario.matricula,  novo_funcionario.nome, novo_funcionario.funcao, novo_funcionario.salario);
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
           num_entradas++;
        }
        num_colisoes += tabela[i].colisoes;
    }

    printf("Estatísticas da Tabela Hash:\n");
    printf("Número de oculpação: %d\n", num_entradas);
    printf("Número de colisões: %d\n", num_colisoes);
   
}