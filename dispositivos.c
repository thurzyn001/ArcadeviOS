#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "dispositivos.h"
#include "processos.h"
#include "utils.h"
#include "colors.h"

Dispositivo impressora;
Dispositivo scanner;
Dispositivo disco;
Dispositivo rede;

void inicializarDispositivo(Dispositivo *d, const char *nome) {
    strcpy(d->nome, nome);
    d->status = LIVRE;
    d->pidAtual = -1;
    d->inicioFila = 0;
    d->fimFila = 0;
}

void inicializarDispositivos() {
    inicializarDispositivo(&impressora, "Impressora");
    inicializarDispositivo(&scanner, "Scanner");
    inicializarDispositivo(&disco, "Disco");
    inicializarDispositivo(&rede, "Rede");
}

int buscarIndiceProcesso(int pid) {
    for(int i = 0; i < totalProcessos; i++) {
        if(processos[i].pid == pid)
            return i;
    }
    return -1;
}

Processo *buscarProcessoPID(int pid) {

    for(int i = 0; i < totalProcessos; i++) {

        if(processos[i].pid == pid)
            return &processos[i];
    }

    return NULL;
}

int filaVazia(Dispositivo *d) {
    return d->inicioFila == d->fimFila;
}

void enfileirar(Dispositivo *d, int pid) {
    d->fila[d->fimFila] = pid;
    d->fimFila = (d->fimFila + 1) % MAX_FILA;
}

int desenfileirar(Dispositivo *d) {
    int pid = d->fila[d->inicioFila];
    d->inicioFila = (d->inicioFila + 1) % MAX_FILA;
    return pid;
}

void solicitarDispositivo(Dispositivo *d, int pid) {

    int indice = buscarIndiceProcesso(pid);

    if(indice == -1) {
        printf(red "\nPID nao encontrado.\n" reset);
        return;
    }

    if(processos[indice].estado == TERMINATED) {
        printf(red "\nProcesso finalizado nao pode solicitar dispositivo.\n" reset);
        return;
    }

    if(d->status == LIVRE) {
        d->status = OCUPADO;
        d->pidAtual = pid;
        processos[indice].estado = WAITING;
        strcpy(processos[indice].dispositivo, d->nome);

        printf(green "\n%s alocado para PID %d (%s).\n" reset,
               d->nome, pid, processos[indice].nome);
        printf("Estado do processo: WAITING\n");
    } else {
        enfileirar(d, pid);
        processos[indice].estado = WAITING;
        strcpy(processos[indice].dispositivo, d->nome);

        printf(yellow "\n%s ocupado. PID %d entrou na fila.\n" reset,
               d->nome, pid);
    }
}

void liberarDispositivo(Dispositivo *d) {

    if(d->status == LIVRE) {
        printf(yellow "\n%s ja esta livre.\n" reset, d->nome);
        return;
    }

    int pidLiberado = d->pidAtual;
    int indiceLiberado = buscarIndiceProcesso(pidLiberado);

    if(indiceLiberado != -1 && processos[indiceLiberado].estado != TERMINATED) {
        processos[indiceLiberado].estado = READY;
        strcpy(processos[indiceLiberado].dispositivo, "-");
    }

    printf(green "\n%s liberado do PID %d.\n" reset, d->nome, pidLiberado);

    if(!filaVazia(d)) {
        int proximoPID = desenfileirar(d);
        int indiceProximo = buscarIndiceProcesso(proximoPID);

        d->pidAtual = proximoPID;
        d->status = OCUPADO;

        if(indiceProximo != -1 && processos[indiceProximo].estado != TERMINATED) {
            processos[indiceProximo].estado = WAITING;
            strcpy(processos[indiceProximo].dispositivo, d->nome);
        }

        printf(yellow "Proximo da fila assumiu o dispositivo: PID %d.\n" reset,
               proximoPID);
    } else {
        d->pidAtual = -1;
        d->status = LIVRE;
    }
}

void mostrarUmDispositivo(Dispositivo *d) {

    Processo *p = NULL;

    if(d->status == OCUPADO) {
        p = buscarProcessoPID(d->pidAtual);
    }

    printf(cyan "┌──────────────────────────────────────────────┐\n" reset);
    printf(cyan "│ " reset "%-44s" cyan " │\n" reset, d->nome);
    printf(cyan "├──────────────────────────────────────────────┤\n" reset);

    if(d->status == LIVRE) {

        printf(cyan "│ " reset "Status.......: " green "● Livre\n" reset);
        printf(cyan "│ " reset "Fila.........: vazia\n" reset);

    } else {

        printf(cyan "│ " reset "Status.......: " red "● Ocupado\n" reset);
        printf(cyan "│ " reset "PID..........: %d\n", d->pidAtual);

        if(p != NULL) {
            printf(cyan "│ " reset "Processo.....: %-30s" cyan "│\n" reset, p->nome);
            printf(cyan "│ " reset "Estado.......: %-30s" cyan "│\n" reset, nomeEstado(p->estado));
        }

        if(filaVazia(d)) {

            printf(cyan "│ " reset "Fila.........: vazia%25s" cyan "│\n" reset, "");

        } else {

            printf(cyan "│ " reset "Fila.........:%30s" cyan "│\n" reset, "");

            int pos = d->inicioFila;
            int ordem = 1;

            while(pos != d->fimFila) {

                Processo *pf = buscarProcessoPID(d->fila[pos]);

                if(pf != NULL) {
                    printf(cyan "│ " reset "%2dº PID %-4d - %-22s" cyan "│\n" reset,
                           ordem,
                           d->fila[pos],
                           pf->nome);
                } else {
                    printf(cyan "│ " reset "%2dº PID %-4d - %-22s" cyan "│\n" reset,
                           ordem,
                           d->fila[pos],
                           "desconhecido");
                }

                ordem++;
                pos = (pos + 1) % MAX_FILA;
            }
        }
    }

    printf(cyan "└──────────────────────────────────────────────┘\n\n" reset);
}

void mostrarDispositivos() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("GERENCIADOR DE DISPOSITIVOS");
    linha(cyan, '=');

    mostrarUmDispositivo(&impressora);
    mostrarUmDispositivo(&scanner);
    mostrarUmDispositivo(&disco);
    mostrarUmDispositivo(&rede);
}

Dispositivo *escolherDispositivo(int op) {

    switch(op) {

        case 1: return &impressora;
        case 2: return &scanner;
        case 3: return &disco;
        case 4: return &rede;

        default: return NULL;
    }
}

void mostrarProcessosParaDispositivo() {

    linha(cyan, '=');
    centralizarRainbow("PROCESSOS DISPONIVEIS");
    linha(cyan, '=');

    int encontrou = 0;

    printf("%-6s %-25s %-15s\n", "PID", "Nome", "Estado");
    linha(cyan, '-');

    for(int i = 0; i < totalProcessos; i++) {

        if(processos[i].estado == READY || processos[i].estado == RUNNING) {

            printf("%-6d %-25s %-15s\n",
                   processos[i].pid,
                   processos[i].nome,
                   nomeEstado(processos[i].estado));

            encontrou = 1;
        }
    }

    if(!encontrou) {
        printf("\nNenhum processo disponivel para solicitar dispositivo.\n");
    }

    printf("\n");
}

void resetarDispositivos() {
    inicializarDispositivos();

    for(int i = 0; i < totalProcessos; i++) {
        strcpy(processos[i].dispositivo, "-");
    }
}

void menuDispositivos() {

    int op;
    int pid;

    do {

        system("cls");

        linha(cyan, '=');
        centralizarRainbow("GERENCIADOR DE DISPOSITIVOS");
        linha(cyan, '=');

        printf("1 - Solicitar Impressora\n");
        printf("2 - Solicitar Scanner\n");
        printf("3 - Solicitar Disco\n");
        printf("4 - Solicitar Rede\n");
        printf("\n");
        printf("5 - Liberar Impressora\n");
        printf("6 - Liberar Scanner\n");
        printf("7 - Liberar Disco\n");
        printf("8 - Liberar Rede\n");
        printf("\n");
        printf("9 - Mostrar Dispositivos\n");
        printf("0 - Voltar\n");

        linha(cyan, '-');

        op = lerInteiro("Opcao: ");

        Dispositivo *d = NULL;

        switch(op) {

            case 1:
            case 2:
            case 3:
            case 4:

                d = escolherDispositivo(op);

                system("cls");
                mostrarProcessosParaDispositivo();

                pid = lerInteiro("PID: ");

                solicitarDispositivo(d, pid);

                pausar();

                break;

            case 5:
            case 6:
            case 7:
            case 8:

                d = escolherDispositivo(op - 4);

                liberarDispositivo(d);

                pausar();

                break;

            case 9:

                mostrarDispositivos();

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
