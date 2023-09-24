#ifndef SHELL_H
#define SHELL_H

#define TAMANHO 256
#define TAMANHO_COMANDO 100

// Remove o caractere de nova linha do final da string
void retiraEnter(char *s);

// Função para verificar se um comando é permitido
int verificaComandoPermitido(const char *comando);

// Obtém o comando do usuário
void obterComando(char *comando, int tamanho);

// Função para executar comandos
void executaComandoExterno(const char *comando);

// Função para processar o comando
void processaComando(const char *comando, char *diretorioAtual);

#endif // SHELL_H
