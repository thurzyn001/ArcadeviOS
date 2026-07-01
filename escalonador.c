#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "escalonador.h"
#include "processos.h"
#include "utils.h"
#include "colors.h"

#define LARGURA_MENU 75
#define TEMPO_CPU 400

void mostrarFilaFCFS() {

    printf("\n");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("FILA DE EXECUCAO", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    printf("%-5s %-25s %-10s\n",
           "PID",
           "PROCESSO",
           "TEMPO");

    linha(cyan, '-', LARGURA_MENU);

    int encontrou = 0;

    for(int i = 0; i < totalProcessos; i++) {

        if(processos[i].estado == READY) {

            encontrou = 1;

            printf("%-5d %-25s %-10d\n",
                   processos[i].pid,
                   processos[i].nome,
                   processos[i].tempoRestante);

        }
    }

    linha(cyan, '-', LARGURA_MENU);

    if(!encontrou)
        printf("\nNao ha processos prontos.\n");
}

void executarFCFS() {

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("ESCALONADOR FCFS", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    mostrarFilaFCFS();

    printf("\n");
    pausar();

    int executados = 0;
    int tempoTotal = 0;

    for(int i = 0; i < totalProcessos; i++) {

        if(processos[i].estado != READY)
            continue;

        system("cls");

        processos[i].estado = RUNNING;
        processos[i].tempoRestante = processos[i].tempoExecucao;

        linha(green, '=', LARGURA_MENU);
        centralizarRainbow("CPU EXECUTANDO", LARGURA_MENU);
        linha(green, '=', LARGURA_MENU);

        printf("PID.............: %d\n", processos[i].pid);
        printf("Nome............: %s\n", processos[i].nome);
        printf("Prioridade......: %d\n", processos[i].prioridade);
        printf("Tempo...........: %d\n\n", processos[i].tempoExecucao);

        while(processos[i].tempoRestante > 0) {

            printf("\rTempo restante: %2d ", processos[i].tempoRestante);
            fflush(stdout);

            Sleep(TEMPO_CPU);

            processos[i].tempoRestante--;
        }

        processos[i].estado = TERMINATED;

        printf("\n\nProcesso finalizado!\n");

        executados++;
        tempoTotal += processos[i].tempoExecucao;

        Sleep(1200);
    }

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("RESUMO FCFS", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    printf("Processos executados.: %d\n", executados);
    printf("Tempo total.........: %d\n", tempoTotal);

    linha(cyan, '=', LARGURA_MENU);
}

void executarRoundRobin() {

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("ESCALONADOR ROUND ROBIN", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    if(totalProcessos == 0) {
        printf("\nNenhum processo cadastrado.\n");
        return;
    }

    int quantum;

    do {
        quantum = lerInteiro("Quantum: ");

        if(quantum <= 0) {
            printf(red "\nO quantum deve ser maior que zero.\n" reset);
            Sleep(800);
            apagarLinhas(2);
        }

    } while(quantum <= 0);

    int existemProntos;
    int executados = 0;
    int ciclos = 0;

    do {

        existemProntos = 0;

        for(int i = 0; i < totalProcessos; i++) {

            if(processos[i].estado == READY && processos[i].tempoRestante > 0) {

                existemProntos = 1;
                ciclos++;

                system("cls");

                linha(magenta, '=', LARGURA_MENU);
                centralizarRainbow("CPU - ROUND ROBIN", LARGURA_MENU);
                linha(magenta, '=', LARGURA_MENU);

                processos[i].estado = RUNNING;

                printf("Ciclo...........: %d\n", ciclos);
                printf("PID.............: %d\n", processos[i].pid);
                printf("Nome............: %s\n", processos[i].nome);
                printf("Quantum.........: %d\n", quantum);
                printf("Tempo restante..: %d\n\n", processos[i].tempoRestante);

                int tempoExecutado = 0;

                while(tempoExecutado < quantum && processos[i].tempoRestante > 0) {

                    printf("\rExecutando... tempo restante: %2d ",
                           processos[i].tempoRestante);

                    fflush(stdout);

                    Sleep(TEMPO_CPU);

                    processos[i].tempoRestante--;
                    tempoExecutado++;
                }

                if(processos[i].tempoRestante == 0) {

                    processos[i].estado = TERMINATED;
                    executados++;

                    printf(green "\n\nProcesso finalizado!\n" reset);

                } else {

                    processos[i].estado = READY;

                    printf(yellow "\n\nQuantum encerrado. Processo voltou para READY.\n" reset);
                    printf("Tempo restante agora: %d\n", processos[i].tempoRestante);
                }

                Sleep(1200);
            }
        }

    } while(existemProntos);

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("RESUMO ROUND ROBIN", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    printf("Quantum usado.......: %d\n", quantum);
    printf("Ciclos executados...: %d\n", ciclos);
    printf("Processos finalizados: %d\n", executados);

    linha(cyan, '=', LARGURA_MENU);
}

void executarPrioridade() {

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("ESCALONADOR POR PRIORIDADE", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    if(totalProcessos == 0) {
        printf("\nNenhum processo cadastrado.\n");
        return;
    }

    int executados = 0;
    int tempoTotal = 0;

    while(1) {

        int indiceMaiorPrioridade = -1;

        for(int i = 0; i < totalProcessos; i++) {

            if(processos[i].estado == READY) {

                if(indiceMaiorPrioridade == -1 ||
                   processos[i].prioridade > processos[indiceMaiorPrioridade].prioridade) {

                    indiceMaiorPrioridade = i;
                }
            }
        }

        if(indiceMaiorPrioridade == -1)
            break;

        int i = indiceMaiorPrioridade;

        system("cls");

        processos[i].estado = RUNNING;
        processos[i].tempoRestante = processos[i].tempoExecucao;

        linha(yellow, '=', LARGURA_MENU);
        centralizarRainbow("CPU - PRIORIDADE", LARGURA_MENU);
        linha(yellow, '=', LARGURA_MENU);

        printf("PID.............: %d\n", processos[i].pid);
        printf("Nome............: %s\n", processos[i].nome);
        printf("Prioridade......: %d\n", processos[i].prioridade);
        printf("Tempo...........: %d\n\n", processos[i].tempoExecucao);

        while(processos[i].tempoRestante > 0) {

            printf("\rExecutando... tempo restante: %2d ",
                   processos[i].tempoRestante);

            fflush(stdout);

            Sleep(TEMPO_CPU);

            processos[i].tempoRestante--;
        }

        processos[i].estado = TERMINATED;

        printf(green "\n\nProcesso finalizado!\n" reset);

        executados++;
        tempoTotal += processos[i].tempoExecucao;

        Sleep(1000);
    }

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("RESUMO PRIORIDADE", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    printf("Processos executados.: %d\n", executados);
    printf("Tempo total..........: %d\n", tempoTotal);

    linha(cyan, '=', LARGURA_MENU);
}

void resetarProcessos() {

    system("cls");

    linha(yellow, '=', LARGURA_MENU);
    centralizarRainbow("RESETAR PROCESSOS", LARGURA_MENU);
    linha(yellow, '=', LARGURA_MENU);

    if(totalProcessos == 0) {
        printf("\nNenhum processo cadastrado.\n");
        return;
    }

    for(int i = 0; i < totalProcessos; i++) {
        processos[i].estado = READY;
        processos[i].tempoRestante = processos[i].tempoExecucao;
    }

    printf("\nTodos os processos foram resetados para READY.\n");
    printf("Tempo restante restaurado com sucesso.\n");

    linha(yellow, '=', LARGURA_MENU);
}

void menuEscalonador() {

    int op;

    do {

        system("cls");

        linha(cyan, '=', LARGURA_MENU);
        centralizarRainbow("ESCALONADOR", LARGURA_MENU);
        linha(cyan, '=', LARGURA_MENU);

        printf("1 - Executar FCFS\n");
        printf("2 - Executar Round Robin\n");
        printf("3 - Executar Prioridade\n");
        printf("4 - Exibir Fila\n");
        printf("5 - Resetar Processos\n");
        printf("0 - Voltar\n");

        linha(cyan, '-', LARGURA_MENU);

        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:

                executarFCFS();
                pausar();
                break;

            case 2:

                executarRoundRobin();
                pausar();
                break;

            case 3:

                executarPrioridade();
                pausar();
                break;

            case 4:
                system("cls");
                mostrarFilaFCFS();
                pausar();
                break;

            case 5:

                resetarProcessos();
                pausar();
                break;

            case 0:

                printf("\nVoltando...\n");
                Sleep(700);
                break;

            default:

                printf("\nOpcao invalida!\n");
                Sleep(700);
        }

    } while(op != 0);
}
