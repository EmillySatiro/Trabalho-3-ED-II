#ifndef HASHING_H
#define HASHING_H
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define QTD_FUNCIONARIOS 1000
#define TAM_MATRICULA 6

typedef struct {
   char matricula[TAM_MATRICULA + 1];
   char nome[50];
   char funcao[20];
   float salario;
}Funcionario;


void gerar_matricula(char *matricula);
void gerar_dados(Funcionario *dados, int qtd);
Funcionario** alocar_tabela(int tamanho_tabela);
void desalocar_tabela(Funcionario** tabela, int tamanho_tabela);
Funcionario* alocar_funcionario(const char* matricula, const char* nome, const char* funcao, float salario);
void liberar_funcionario(Funcionario* funcionario);
int hashing_rotacao(int matricula, int tamanho_vetor);
int hashing_fole_shift(int matricula, int tamanho_vetor);
void inserir_na_tabela_a(Funcionario** tabela, Funcionario* novo_funcionario, int tamanho_tabela);
void inserir_na_tabela_b(Funcionario** tabela, Funcionario* novo_funcionario, int tamanho_tabela);
void imprimir_estatisticas(Funcionario** tabela, int tamanho_tabela);

#endif