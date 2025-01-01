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

Funcionario** alocar_tabela(int tamanho_tabela) {
 
    Funcionario** tabela = (Funcionario**)malloc(tamanho_tabela * sizeof(Funcionario*));
    if (!tabela) {
        
        fprintf(stderr, "Erro ao alocar memória para a tabela hash.\n");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < tamanho_tabela; i++) {
        tabela[i] = NULL;
    }

   
    printf("Tabela alocada com sucesso. Tamanho: %d\n", tamanho_tabela);
    
    return tabela;
}

void desalocar_tabela(Funcionario** tabela, int tamanho_tabela) {
    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i]) {
            free(tabela[i]);
        }
    }
    free(tabela);
}

Funcionario* alocar_funcionario(const char* matricula, const char* nome, const char* funcao, float salario) {
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

void liberar_funcionario(Funcionario* funcionario) {
    if (funcionario) {
        free(funcionario);
    }
}


int hashing_rotacao(int matricula, int tamanho_vetor) {
    int resultado_final = 0;
    int valido = 1;
    char matricula_str[10];
    sprintf(matricula_str, "%d", matricula);

    int len = strlen(matricula_str);
    if (len < 6) {
        valido = 0;
    }

    if (valido) {
        char matricula_rotacionada[10];
        strcpy(matricula_rotacionada, matricula_str + 2);
        strncat(matricula_rotacionada, matricula_str, 2);
        int digitos_extraidos = (matricula_rotacionada[1] - '0') + (matricula_rotacionada[3] - '0') + (matricula_rotacionada[5] - '0');
        int resto = digitos_extraidos % tamanho_vetor;
        int primeiro_digito = matricula_str[0] - '0';
        resultado_final = (resto + primeiro_digito) % tamanho_vetor;
    }

    return valido ? resultado_final : -1;
}

int hashing_fole_shift(int matricula, int tamanho_vetor) {
    int resultado_final = 0;
    int valido = 1;
    char matricula_str[10];
    sprintf(matricula_str, "%d", matricula);

    int len = strlen(matricula_str);
    if (len < 6) {
        valido = 0;
    }

    if (valido) {
        int grupo1 = (matricula_str[0] - '0') + (matricula_str[2] - '0') + (matricula_str[5] - '0');
        int grupo2 = (matricula_str[1] - '0') + (matricula_str[3] - '0') + (matricula_str[4] - '0');
        int resultado = grupo1 + grupo2;
        int resto = resultado % tamanho_vetor;
        resultado_final = resto + 7;
    }

    return valido ? resultado_final : -1;
}

void inserir_na_tabela_a(Funcionario** tabela, Funcionario* novo_funcionario, int tamanho_tabela) {
    int matricula_int = atoi(novo_funcionario->matricula); 
    int indice = hashing_rotacao(matricula_int, tamanho_tabela);  

    
    while (tabela[indice] != NULL) {
      
        indice = (indice + 1) % tamanho_tabela;
    }

   
    tabela[indice] = novo_funcionario;
}

void inserir_na_tabela_b(Funcionario** tabela, Funcionario* novo_funcionario, int tamanho_tabela) {
    int matricula_int = atoi(novo_funcionario->matricula);  
    int indice = hashing_fole_shift(matricula_int, tamanho_tabela); 

   
    while (tabela[indice] != NULL) {
        
        indice = (indice + 1) % tamanho_tabela;
    }

  
    tabela[indice] = novo_funcionario;
}

void imprimir_estatisticas(Funcionario** tabela, int tamanho_tabela) {
    int num_entradas = 0;
    int num_colisoes = 0;
    int indice_primeiro_ocupado = -1;
    int indice_ultimo_ocupado = -1;

    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i] != NULL) {
            num_entradas++;
            if (indice_primeiro_ocupado == -1) {
                indice_primeiro_ocupado = i;
            }
            indice_ultimo_ocupado = i;

          
            if (i > 0 && tabela[i - 1] != NULL) {
                num_colisoes++;
            }
        }
    }

    printf("Estatísticas da Tabela Hash:\n");
    printf("Número de entradas: %d\n", num_entradas);
    printf("Número de colisões: %d\n", num_colisoes);
    printf("Carga (percentual de ocupação): %.2f%%\n", (float)num_entradas / tamanho_tabela * 100);
    printf("Índice do primeiro item ocupado: %d\n", indice_primeiro_ocupado);
    printf("Índice do último item ocupado: %d\n", indice_ultimo_ocupado);
}