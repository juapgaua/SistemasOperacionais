/*
Implemente as funções abaixo e crie um programa de teste chamado
		   FileSystemTest que mostre o funcionamento correto dessas funções.
		   Logo, você terá que desenvolver os três arquivos abaixo.

		   filesystem.h 	// Interface do sistema de arquivos.
		   filesystem.c 	// Implementação do sistema de arquivos.
		   filesystemtest.c // Programa de teste do sistema de arquivos.
		   Desenvolvido por Juliana Apgaua Sant'Ana Vidigal
		   22.09.23
*/
#pragma once
#include <stdio.h>

#define ERRO -1
#define TAMANHO_NOME 13
#define TAMANHO_DATA 11
#define TAMANHO_HORA 6
#define NUMERO_MAXIMO_AQUIVOS 256

// Representa o conteúdo e os atributos do arquivo.
typedef struct {
	    int ID;
		char nome[TAMANHO_NOME], data[TAMANHO_DATA], hora[TAMANHO_HORA];
        unsigned tamanho;

		void *conteudo;
		FILE *arquivo;
} Arquivo;

/*  Abre o arquivo com o nome especificado.
    Retorna o ID (descritor) do arquivo em caso de sucesso ou ERRO se ocorrer um erro.
*/
int abrir(char* nomeArquivo);

/* Lê o arquivo identificado por ID.
   Faz a leitura de n (tamanho) bytes do arquivo com a quantidade indicada.
   Retorna o conteúdo lido do arquivo em caso de sucesso ou NULL se ocorrer um erro.
*/
void* ler(int ID, unsigned tamanho, unsigned quantidade);

/* Escreve o conteúdo do buffer no arquivo identificado por ID.
   Faz a escrita de n (tamanho) bytes no arquivo com a quantidade indicada.
   Retorna o número de bytes escritos no arquivo em caso de sucesso ou ERRO se
   ocorrer um erro.
*/
int escrever(int ID,const void *buffer, unsigned tamanho, unsigned quantidade);

/* Fecha o arquivo com o ID especificado.
   Retorna 1 em caso de sucesso ou ERRO se ocorrer um erro.
*/
int fechar(int ID);
