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

typedef struct {
   Funcionario *funcionairo; 
   int colisoes; 
}Tabela_hashing;

#include "Hashing.h"

void gerar_matricula(char *matricula);

void gerar_dados(Funcionario *dados, int qtd);

Tabela_hashing* alocar_tabela(int tamanho_tabela);

void desalocar_tabela(Tabela_hashing* tabela, int tamanho_tabela);

Funcionario* alocar_funcionario(char* matricula,char* nome,char* funcao, float salario);

int hashing_rotacao(char *matricula, int tamanho_tabela);

int Fole_shift(char *matricula, int tamanho_tabela);

void inserir_na_tabela_hashing_rotacao_A(Tabela_hashing *tabela, Funcionario novo_funcionario, int tamanho_tabela) ;

void inserir_fole_shift_B(Tabela_hashing *tabela, Funcionario novo_funcionario, int tamanho_tabela);

void imprimir_estatisticas(Tabela_hashing* tabela, int tamanho_tabela);
#endif