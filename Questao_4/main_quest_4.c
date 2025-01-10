#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Hashing.h"

int main() {
    srand(time(NULL));

    
    Funcionario funcionarios[QTD_FUNCIONARIOS];
    gerar_dados(funcionarios, QTD_FUNCIONARIOS);

 
    int tamanhos[] = {101, 150};

   
    int opcao;

    do {
    
        printf("\n=========================================\n");
        printf("            MENU DE OPÇÕES\n");
        printf("=========================================\n");
        printf("1. Ver resultados do Hashing (a): Rotação A\n");
        printf("2. Ver resultados do Hashing (b): Fole Shift B\n");
        printf("3. Ver resultados de ambos os métodos\n");
        printf("4. Sair do programa\n");
        printf("=========================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1: {
                printf("\n==== Hashing: rotação (A)====\n");
                clock_t tempo_total = 0;
                for (int t = 0; t < 2; t++) {
                    
                    int tamanho_tabela = tamanhos[t];
                    printf("\nTabela Hash com %d posições:\n", tamanho_tabela);

                    Tabela_hashing* tabela_a = alocar_tabela(tamanho_tabela);
                    clock_t inicio = clock();
                    for (int i = 0; i < QTD_FUNCIONARIOS; i++) {
                        inserir_na_tabela_hashing_rotacao_A(tabela_a, funcionarios[i], tamanho_tabela);
                    }
                    clock_t fim = clock();
                    tempo_total += (fim - inicio);
                    imprimir_estatisticas(tabela_a, tamanho_tabela);
                    printf("Tempo para inserção: %f segundos\n", ((double)tempo_total / CLOCKS_PER_SEC));
                    desalocar_tabela(tabela_a, tamanho_tabela);
                }
                break;
            }
            case 2: {
                printf("\n====Hashing: fole shift (B)====\n");
                clock_t tempo_total = 0;
                for (int t = 0; t < 2; t++){

                    int tamanho_tabela = tamanhos[t];
                    printf("\nTabela Hash com %d posições:\n", tamanho_tabela);
                    Tabela_hashing* tabela_b = alocar_tabela(tamanho_tabela);
                    clock_t inicio = clock();

                    for (int i = 0; i < QTD_FUNCIONARIOS; i++) {
                        inserir_fole_shift_B(tabela_b, funcionarios[i], tamanho_tabela);
                    }

                    clock_t fim = clock();
                    tempo_total += (fim - inicio);

                    imprimir_estatisticas(tabela_b, tamanho_tabela);
                    printf("Tempo para inserção: %f segundos\n", ((double)tempo_total / CLOCKS_PER_SEC));

                    desalocar_tabela(tabela_b, tamanho_tabela);
                }
                break;
            }
            case 3: {
                printf("\n==== Resultados de ambos os métodos====\n");
                clock_t tempo_total = 0;

                for (int t = 0; t < 2; t++) {

                    int tamanho_tabela = tamanhos[t];
                    printf("\nTabela Hash com %d posições:\n", tamanho_tabela);
                    printf("\n==== Hashing: rotação (A)====\n");

                    Tabela_hashing* tabela_a = alocar_tabela(tamanho_tabela);
                    clock_t inicio = clock();

                    for (int i = 0; i < QTD_FUNCIONARIOS; i++) {
                        inserir_na_tabela_hashing_rotacao_A(tabela_a, funcionarios[i], tamanho_tabela);
                    }

                    clock_t fim = clock();
                    tempo_total += (fim - inicio);

                    imprimir_estatisticas(tabela_a, tamanho_tabela);
                    printf("Tempo para inserção: %f segundos\n", ((double)tempo_total / CLOCKS_PER_SEC));

                    desalocar_tabela(tabela_a, tamanho_tabela);

                    printf("\n====Hashing: fole shift (B)====\n");

                    clock_t tempo_total = 0;
                    Tabela_hashing* tabela_b = alocar_tabela(tamanho_tabela);
                    clock_t inicio = clock();

                    for (int i = 0; i < QTD_FUNCIONARIOS; i++) {
                        inserir_fole_shift_B(tabela_b, funcionarios[i], tamanho_tabela);
                    }

                    clock_t fim = clock();
                    tempo_total += (fim - inicio);

                    imprimir_estatisticas(tabela_b, tamanho_tabela);
                    printf("Tempo para inserção: %f segundos\n", ((double)tempo_total / CLOCKS_PER_SEC));
                    
                    desalocar_tabela(tabela_b, tamanho_tabela);
                }
                break;
            }
            case 4:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida. Por favor, escolha novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}