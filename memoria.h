#ifndef MEMORIA_H
#define MEMORIA_H

#define MEMORIA_TOTAL 1024
#define MAX_BLOCOS 100

typedef struct {
    int inicio;
    int tamanho;
    int livre;
    int pid;
    char nomeProcesso[50];
} BlocoMemoria;

extern BlocoMemoria memoria[MAX_BLOCOS];
extern int totalBlocos;

void inicializarMemoria();

int alocarMemoria(int pid, const char *nomeProcesso, int tamanho);
void liberarMemoria(int pid);

void unirBlocosLivres();

void exibirMapaMemoria();
void menuMemoria();

#endif
