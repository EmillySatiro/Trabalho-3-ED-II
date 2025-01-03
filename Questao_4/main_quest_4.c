#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Hashing.h"

int main() {
    srand(time(NULL)); 

    
    Funcionario funcionarios[QTD_FUNCIONARIOS];
    gerar_dados(funcionarios, QTD_FUNCIONARIOS);  

    int tamanhos[] = {101, 150};

    for (int t = 0; t < 2; t++) {
        int tamanho_tabela = tamanhos[t];

        printf("\nTabela Hash com %d posições:\n", tamanho_tabela);

        Tabela_hashing* tabela_a = alocar_tabela(tamanho_tabela); 
        for (int i = 0; i < QTD_FUNCIONARIOS; i++) {
            inserir_na_tabela_hashing_rotacao_A(tabela_a, funcionarios[i], tamanho_tabela);  
        }
        printf("Hashing (a):\n");
        imprimir_estatisticas(tabela_a, tamanho_tabela);  
        desalocar_tabela(tabela_a, tamanho_tabela); 

      
        Tabela_hashing* tabela_b = alocar_tabela(tamanho_tabela);  
        for (int i = 0; i < QTD_FUNCIONARIOS; i++) {
            inserir_fole_shift_B(tabela_b, funcionarios[i], tamanho_tabela);  
        }
        printf("Hashing (b):\n");
        imprimir_estatisticas(tabela_b, tamanho_tabela);  
        desalocar_tabela(tabela_b, tamanho_tabela);  
    }

    return 0;
}
