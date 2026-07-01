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
    int tempoRestante;

    int memoria;

    Estado estado;

    char dispositivo[30];

} Processo;

extern Processo processos[MAX_PROCESSOS];
extern int totalProcessos;
extern int proxPID;

void criarProcesso();
void encerrarProcesso(int pid);
void alterarEstado(int pid, Estado novoEstado);
void exibirProcessos();
void MenuProcessos();

char *nomeEstado(Estado e);

#endif
