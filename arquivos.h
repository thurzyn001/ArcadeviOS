#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#define MAX_ARQUIVOS 100

typedef struct {
    char nome[50];
    int tamanho;
} Arquivo;

extern Arquivo arquivos[MAX_ARQUIVOS];
extern int totalArquivos;

void criarArquivo();
void removerArquivo();
void listarArquivos();
void buscarArquivo();
void menuArquivos();

#endif
