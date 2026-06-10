#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

Processo processos[MAX_PROCESSOS];
int totalProcessos = 0;
int proxPID = 1;

char* nomeEstado(Estado e) {
    switch(e) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "DESCONHECIDO";
    }
}

void criarProcesso() {
    if(totalProcessos >= MAX_PROCESSOS) {
        printf("Limite de processos atingido!\n");
        return;
    }

    Processo p;

    p.pid = proxPID++;

    printf("Nome: ");
    scanf(" %49[^\n]", p.nome);

    printf("Prioridade: ");
    scanf("%d", &p.prioridade);

    printf("Tempo de execucao: ");
    scanf("%d", &p.tempoExecucao);

    p.estado = NEW;

    processos[totalProcessos++] = p;

    printf("Processo criado com PID %d\n", p.pid);
}

void encerrarProcesso(int pid) {
    for(int i = 0; i < totalProcessos; i++) {
        if(processos[i].pid == pid) {
            processos[i].estado = TERMINATED;
            printf("Processo encerrado.\n");
            return;
        }
    }

    printf("PID nao encontrado.\n");
}

void alterarEstado(int pid, Estado novoEstado) {
    for(int i = 0; i < totalProcessos; i++) {
        if(processos[i].pid == pid) {
            processos[i].estado = novoEstado;
            printf("Estado alterado.\n");
            return;
        }
    }

    printf("PID nao encontrado.\n");
}

void exibirProcessos() {
    printf("\n-------------------------------------\n");
    printf("PID\tNome\tEstado\n");
    printf("-------------------------------------\n");

    for(int i = 0; i < totalProcessos; i++) {
        printf("%d\t%s\t%s\n",
               processos[i].pid,
               processos[i].nome,
               nomeEstado(processos[i].estado));
    }

    printf("-------------------------------------\n");
}

void MenuProcessos(){

    system("cls");

    int op;
    int pid;
    int estado;

    do {

        printf("\033[1;36m=====================================\033[0m\n");
        printf("             ");
        printf("\033[1;31mA\033[1;33mr\033[1;32mc\033[1;36ma\033[1;34md\033[1;35me\033[1;31mv\033[1;33mi\033[1;32mO\033[1;36mS\033[0m\n");
        printf("\033[1;36m=====================================\033[0m\n");

        printf("1 - Criar Processo\n");
        printf("2 - Encerrar Processo\n");
        printf("3 - Alterar Estado\n");
        printf("4 - Exibir Processos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch(op) {

            case 1:
                criarProcesso();
                break;

            case 2:
                printf("PID: ");
                scanf("%d", &pid);
                encerrarProcesso(pid);
                break;

            case 3:
                printf("PID: ");
                scanf("%d", &pid);

                printf("0-NEW\n");
                printf("1-READY\n");
                printf("2-RUNNING\n");
                printf("3-WAITING\n");
                printf("4-TERMINATED\n");

                scanf("%d", &estado);

                alterarEstado(pid, (Estado)estado);
                break;

            case 4:
                exibirProcessos();
                break;
        }

    }while(op != 0);

}
