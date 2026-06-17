#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "escalonador.h"
#include "processos.h"

void executarFCFS() {

    if(totalProcessos == 0) {
        printf("\nNenhum processo cadastrado!\n");
        system("pause");
        return;
    }

    printf("\n=====================================\n");
    printf("      ESCALONADOR FCFS\n");
    printf("=====================================\n");

    for(int i = 0; i < totalProcessos; i++) {

        if(processos[i].estado == TERMINATED)
            continue;

        processos[i].estado = RUNNING;

        printf("\nExecutando PID %d - %s\n",
               processos[i].pid,
               processos[i].nome);

        printf("Tempo de execucao: %d\n",
               processos[i].tempoExecucao);

        Sleep(1000);

        processos[i].estado = TERMINATED;

        printf("Processo finalizado!\n");
    }

    printf("\nTodos os processos foram executados.\n");

    system("pause");
}

void menuEscalonador() {

    int op;

    do {

        system("cls");

        printf("=====================================\n");
        printf("         ESCALONADOR\n");
        printf("=====================================\n");

        printf("1 - Executar FCFS\n");
        printf("2 - Exibir Processos\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        scanf("%d", &op);

        switch(op) {

            case 1:
                executarFCFS();
                break;

            case 2:
                exibirProcessos();
                system("pause");
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
                Sleep(1000);
        }

    } while(op != 0);
}