/*Shell usando a funçao _execv.
Comportamento esperado: quando o usuário digitar "notepad" ou "winver", a função _execv é usada
para executar os programas._execv substituirá o processo atual pelo processo do programa que está
sendo executado. Portanto, o programa shell não continuará a funcionar após a execução desses programas.
Desenvolvido por Juliana Apgaua Sant'Ana Vidigal
28/08/23*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>  // Adicionado para o _execv
#include "shell.h"

#define TAMANHO 256
#define TAMANHO_COMANDO 100

// Estrutura para armazenar comandos permitidos
typedef struct {
    const char *nomeComando;
} ComandoPermitido;

void retiraEnter(char *s){
    if (s[strlen(s)-1]=='\n');
        s[strlen(s)-1]='\0';
        }
// Função para verificar se um comando é permitido
int verificaComandoPermitido(const char *comando) {
    ComandoPermitido comandosPermitidos[] = {
        {"cls"}, {"date"}, {"time"}, {"dir"}, {"type"},
        {"cd"}, {"md"}, {"copy"}, {"rd"}, {"del"},
        {"vol"}, {"ver"}, {"path"}, {"set"}, {"exit"}, {"notepad"}, {"winver"}
    };

    // Verifica se o comando está na lista de comandos permitidos
    for (int i = 0; i < sizeof(comandosPermitidos) / sizeof(comandosPermitidos[0]); i++) {
        if (strcmp(comando, comandosPermitidos[i].nomeComando) == 0) {
            return 1; // Comando permitido
        }
    }

    return 0; // Comando não permitido
}

void obterComando(char *comando, int tamanho) {
    setbuf(stdin, NULL);
    fgets(comando, TAMANHO, stdin);
    retiraEnter(comando);
    setbuf(stdin, NULL);
}

// Função para executar comandos externos
void executaComandoExterno(const char *comando) {
    system(comando);
}

// Função para processar o comando
void processaComando(const char *comando, char *diretorioAtual) {
    if (verificaComandoPermitido(comando)) {
        char comandoComDiretorio[TAMANHO];

        // Processa comandos especiais
        if (strcmp(comando, "dir") == 0) {
            sprintf(comandoComDiretorio, "dir %s", diretorioAtual);
            executaComandoExterno(comandoComDiretorio);
        } else if (strcmp(comando, "cd") == 0) {
            char novoDir[TAMANHO];
            scanf("%s", novoDir);

            if (strcmp(novoDir, "..") == 0) {
                // Subir um nível no diretório
                char *ultimaBarra = strrchr(diretorioAtual, '\\');
                if (ultimaBarra != NULL) {
                    *ultimaBarra = '\0';
                }
            } else {
                // Entrar em um subdiretório
                strcat(diretorioAtual, "\\");
                strcat(diretorioAtual, novoDir);
            }
        // Processa o comando "notepad" usando _execv
        } else if (strcmp(comando, "notepad") == 0) {
            const char *programPath = "C:\\Windows\\System32\\notepad.exe";
            const char *argument1 = "";

            // Preparando o vetor de argumentos
            char *args[] = {(char *)programPath, (char *)argument1, NULL};

            // Executa o programa com argumentos usando _execv
            _execv(programPath, args);

        } else if (strcmp(comando, "winver") == 0) {
            const char *programPath = "C:\\Windows\\System32\\winver.exe";
            const char *argument1 = "";

            // Preparando o vetor de argumentos
            char *args[] = {(char *)programPath, (char *)argument1, NULL};

            // Executa o programa com argumentos usando _execv
            _execv(programPath, args);
            } else {
            // Executa outros comandos permitidos
            executaComandoExterno(comando);
        }
    }else {
        // Comando não permitido
        printf("Comando não permitido: %s\n", comando);
    }
}

int main() {
    char diretorioAtual[TAMANHO] = "\\";
    char comando[TAMANHO_COMANDO];

    // Loop principal
    do {
        // Mostra o prompt
        printf("shell:%s> ", diretorioAtual);

        // Lê o comando
        scanf("%s", comando);

        // Processa o comando
        processaComando(comando, diretorioAtual);
    }while(strcmp(comando, "exit") != 0);

    return 0;
}
