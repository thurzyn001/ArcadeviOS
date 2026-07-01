#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

#include "concorrencia.h"
#include "utils.h"
#include "colors.h"

pthread_mutex_t mutexImpressora;

typedef struct {
    int pid;
    char nome[30];
} ProcessoThread;

void *usarImpressora(void *arg) {

    ProcessoThread *p = (ProcessoThread *) arg;

    printf(yellow "PID %d (%s) aguardando impressora...\n" reset, p->pid, p->nome);

    pthread_mutex_lock(&mutexImpressora);

    printf(green "\nPID %d (%s) entrou na regiao critica.\n" reset, p->pid, p->nome);
    printf("PID %d usando impressora...\n", p->pid);

    Sleep(1500);

    printf(red "PID %d liberou impressora.\n\n" reset, p->pid);

    pthread_mutex_unlock(&mutexImpressora);

    return NULL;
}

void executarConcorrencia() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("CONTROLE DE CONCORRENCIA");
    linha(cyan, '=');

    pthread_t threads[3];

    ProcessoThread processos[3] = {
        {1, "Chrome"},
        {2, "Word"},
        {3, "Edge"}
    };

    pthread_mutex_init(&mutexImpressora, NULL);

    printf("\nSimulando 3 processos tentando acessar a impressora.\n");
    printf("Apenas um processo pode usar o recurso por vez.\n\n");

    for(int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, usarImpressora, &processos[i]);
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutexImpressora);

    linha(cyan, '=');
    printf(green "\nSimulacao finalizada sem condicao de corrida.\n" reset);
}

void menuConcorrencia() {

    int op;

    do {

        system("cls");

        linha(cyan, '=');
        centralizarRainbow("CONCORRENCIA E MUTEX");
        linha(cyan, '=');

        printf("1 - Simular acesso concorrente a impressora\n");
        printf("0 - Voltar\n");

        linha(cyan, '-');

        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:
                executarConcorrencia();
                pausar();
                break;

            case 0:
                printf("\nVoltando...\n");
                Sleep(700);
                break;

            default:
                printf(red "\nOpcao invalida!\n" reset);
                Sleep(700);
        }

    } while(op != 0);
}