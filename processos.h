#ifndef PROCESSOS_H
#define PROCESSOS_H

#define MAX_PROCESSOS 100

typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} Estado;

typedef struct {
    int pid;
    char nome[50];
    int prioridade;
    int tempoExecucao;
    Estado estado;
} Processo;

extern Processo processos[MAX_PROCESSOS];
extern int totalProcessos;

void criarProcesso();
void encerrarProcesso(int pid);
void alterarEstado(int pid, Estado novoEstado);
void exibirProcessos();
void MenuProcessos();

#endif