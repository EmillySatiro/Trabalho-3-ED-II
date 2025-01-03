#include "Hashing.h"

void gerar_matricula(char *matricula){
    for (int i = 0; i < TAM_MATRICULA; i++){
        matricula[i] = '0' + rand() % 10;
    }
    matricula[TAM_MATRICULA] = '\0';
}

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

Tabela_hashing* alocar_tabela(int tamanho_tabela) {
 
    
    Tabela_hashing *tabela = (Tabela_hashing*)calloc(tamanho_tabela, sizeof(Tabela_hashing));
    if (!tabela) {
        
        fprintf(stderr, "Erro ao alocar memória para a tabela hash.\n");
        exit(EXIT_FAILURE);
    }

   
    printf("Tabela alocada com sucesso. Tamanho: %d\n", tamanho_tabela);
    return tabela;
}

void desalocar_tabela(Tabela_hashing* tabela, int tamanho_tabela) {
    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i].funcionairo != NULL) {
            free(tabela[i].funcionairo);
        }
    }
    free(tabela);
}

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


/*Função Hashing: rotação de 2 dígitos para a esquerda depois extrai o 2,
 4 6 dígitos e obtenha o resto da divisão pelo tamanho do vetor destino. 
As colisões devem ser tratadas somando ao resto da divisão o 
primeiro dígito da matrícula.*/
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

/*(b) Função Hashing: fole shift com 3 dígitos da seguinte forma: o 1, 3 e  6; 2, 4 e 5, 
depois obtenha o resto da divisão do resultado pelo tamanho do vetor destino. 
As colisões devem ser realizadas somando 7 ao valor obtido. */
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
void inserir_ashing_fole_shift_B(Tabela_hashing *tabela, Funcionario novo_funcionario, int tamanho_tabela) {
    int posicao_inicial = hashing_fole_shift(novo_funcionario.matricula, tamanho_tabela);
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