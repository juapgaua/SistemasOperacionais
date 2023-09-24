/*
Desenvolvido por Juliana Apgaua Sant'Ana Vidigal
22.09.23
*/
#include "filesystem.h"
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 256

static Arquivo arquivos[MAX_FILES];
static int proximoID = 1;

int abrir(char* nomeArquivo) {
    if (proximoID < MAX_FILES) {
        Arquivo* novoArquivo = &arquivos[proximoID];
        novoArquivo->ID = proximoID++;
        strncpy(novoArquivo->nome, nomeArquivo, TAMANHO_NOME);
        novoArquivo->tamanho = 0;
        novoArquivo->conteudo = NULL;
        novoArquivo->arquivo = fopen(nomeArquivo, "w+");

        if (novoArquivo->arquivo != NULL) {
            return novoArquivo->ID;
        }
    }
    return ERRO;
}

void* ler(int ID, unsigned tamanho, unsigned quantidade) {
    if (ID < 1 || ID >= proximoID) {
        return NULL; // ID inválido
    }

    Arquivo* arquivo = &arquivos[ID];
    if (arquivo->arquivo == NULL) {
        return NULL; // Arquivo não aberto
    }

    // Aloca memória para armazenar o conteúdo lido
    void* conteudoLido = malloc(tamanho * quantidade + 1); // +1 para o caractere nulo
    if (conteudoLido == NULL) {
        return NULL; // Falha na alocação de memória
    }

    // Lê os dados do arquivo
    fseek(arquivo->arquivo, arquivo->tamanho, SEEK_SET);
    fread(conteudoLido, tamanho, quantidade, arquivo->arquivo);
    arquivo->tamanho += tamanho * quantidade;

    // Adiciona um caractere nulo para garantir que seja uma string válida
    ((char*)conteudoLido)[tamanho * quantidade] = '\0';

    return conteudoLido;
}

int escrever(int ID, const void *buffer, unsigned tamanho, unsigned quantidade) {
    if (ID < 1 || ID >= proximoID) {
        return ERRO; // ID inválido
    }

    Arquivo* arquivo = &arquivos[ID];
    if (arquivo->arquivo == NULL) {
        return ERRO; // Arquivo não aberto
    }

    // Escreve os dados no arquivo
    size_t bytesEscritos = fwrite(buffer, tamanho, quantidade, arquivo->arquivo);

    if (bytesEscritos == tamanho * quantidade) {
        arquivo->tamanho += bytesEscritos;
        return bytesEscritos;
    } else {
        return ERRO; // Falha na escrita
    }
}

int fechar(int ID) {
    if (ID < 1 || ID >= proximoID) {
        return ERRO; // ID inválido
    }

    Arquivo* arquivo = &arquivos[ID];
    if (arquivo->arquivo == NULL) {
        return ERRO; // Arquivo não aberto
    }

    fclose(arquivo->arquivo);
    arquivo->arquivo = NULL;
    free(arquivo->conteudo);
    arquivo->conteudo = NULL;

    return 1; // Sucesso
}

