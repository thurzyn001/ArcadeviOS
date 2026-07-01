#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "escalonador.h"
#include "processos.h"
#include "utils.h"
#include "colors.h"
#include "memoria.h"
#include "dispositivos.h"

#define TEMPO_CPU 400

void mostrarFilaFCFS() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("FILA DE EXECUCAO");
    linha(cyan, '=');

    printf("%-5s %-25s %-10s\n",
           "PID",
           "PROCESSO",
           "TEMPO");

    linha(cyan, '-');

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

    linha(cyan, '-');

    if(!encontrou)
        printf("\nNao ha processos prontos.\n");
}

void executarFCFS() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("ESCALONADOR FCFS");
    linha(cyan, '=');

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

        linha(green, '=');
        centralizarRainbow("EXECUTANDO FCFS");
        linha(green, '=');

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
        liberarMemoria(processos[i].pid);

        printf(green "\n\nProcesso finalizado!\n" reset);

        executados++;
        tempoTotal += processos[i].tempoExecucao;

        Sleep(1200);
    }

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("RESUMO FCFS");
    linha(cyan, '=');

    printf("Processos executados.: %d\n", executados);
    printf("Tempo total.........: %d\n", tempoTotal);

    linha(cyan, '=');
}

void executarRoundRobin() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("ESCALONADOR ROUND ROBIN");
    linha(cyan, '=');

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

                linha(magenta, '=');
                centralizarRainbow("EXECUTANDO ROUND ROBIN");
                linha(magenta, '=');

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
                    liberarMemoria(processos[i].pid);
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

    linha(cyan, '=');
    centralizarRainbow("RESUMO ROUND ROBIN");
    linha(cyan, '=');

    printf("Quantum usado.......: %d\n", quantum);
    printf("Ciclos executados...: %d\n", ciclos);
    printf("Processos finalizados: %d\n", executados);

    linha(cyan, '=');
}

void executarPrioridade() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("ESCALONADOR POR PRIORIDADE");
    linha(cyan, '=');

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

        linha(yellow, '=');
        centralizarRainbow("EXECUTANDO PRIORIDADE");
        linha(yellow, '=');

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
        liberarMemoria(processos[i].pid);
        printf(green "\n\nProcesso finalizado!\n" reset);

        executados++;
        tempoTotal += processos[i].tempoExecucao;

        Sleep(1000);
    }

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("RESUMO PRIORIDADE");
    linha(cyan, '=');

    printf("Processos executados.: %d\n", executados);
    printf("Tempo total..........: %d\n", tempoTotal);

    linha(cyan, '=');
}

void resetarProcessos() {

    system("cls");

    linha(yellow, '=');
    centralizarRainbow("RESETAR PROCESSOS");
    linha(yellow, '=');

    if(totalProcessos == 0) {
        printf("\nNenhum processo cadastrado.\n");
        return;
    }

    inicializarMemoria();
    resetarDispositivos();
    int realocados = 0;
    int falhas = 0;

    for(int i = 0; i < totalProcessos; i++) {

        processos[i].estado = READY;
        processos[i].tempoRestante = processos[i].tempoExecucao;

        if(alocarMemoria(processos[i].pid, processos[i].nome, processos[i].memoria)) {
            realocados++;
        } else {
            processos[i].estado = TERMINATED;
            falhas++;
        }
    }

    printf("\nProcessos resetados para READY.\n");
    printf("Memoria reconstruida com base nos processos cadastrados.\n");
    printf("Realocados: %d\n", realocados);

    if(falhas > 0) {
        printf(red "Falhas de realocacao: %d\n" reset, falhas);
    }

    linha(yellow, '=');
}

void menuEscalonador() {

    int op;

    do {

        system("cls");

        linha(cyan, '=');
        centralizarRainbow("ESCALONADOR");
        linha(cyan, '=');

        printf("1 - Executar FCFS\n");
        printf("2 - Executar Round Robin\n");
        printf("3 - Executar Prioridade\n");
        printf("4 - Exibir Fila\n");
        printf("5 - Resetar Processos\n");
        printf("0 - Voltar\n");

        linha(cyan, '-');

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
