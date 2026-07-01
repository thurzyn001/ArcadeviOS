#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "processos.h"
#include "colors.h"
#include "utils.h"
#include "memoria.h"

#define LARGURA_MENU 75

Processo processos[MAX_PROCESSOS];
int totalProcessos = 0;
int proxPID = 1;

char *nomeEstado(Estado e) {

    switch(e) {

        case NEW:
            return "NEW";

        case READY:
            return "READY";

        case RUNNING:
            return "RUNNING";

        case WAITING:
            return "WAITING";

        case TERMINATED:
            return "TERMINATED";

        default:
            return "DESCONHECIDO";
    }
}

void criarProcesso() {

    system("cls");

    if(totalProcessos >= MAX_PROCESSOS) {

        printf(red "Limite maximo de processos atingido!\n" reset);
        return;
    }

    Processo p;

    p.pid = proxPID++;

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("CRIAR PROCESSO", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    lerString("Nome...............: ", p.nome, sizeof(p.nome));

    do {
        p.prioridade = lerInteiro("Prioridade (0-10)..: ");

        if(p.prioridade < 0 || p.prioridade > 10) {

            printf(red "A prioridade deve estar entre 0 e 10.\n" reset);
            Sleep(800);
        }

    } while(p.prioridade < 0 || p.prioridade > 10);

    do {

        p.tempoExecucao = lerInteiro("Tempo de Execucao..: ");

        p.tempoRestante = p.tempoExecucao;

        do {

    p.memoria = lerInteiro("Memoria (MB).......: ");

    if(p.memoria <= 0){

        printf(red "Valor invalido.\n" reset);
        Sleep(700);

    }

    }while(p.memoria <= 0);

        if(p.tempoExecucao <= 0) {

            printf(red "O tempo deve ser maior que zero.\n" reset);
            Sleep(800);
        }

    } while(p.tempoExecucao <= 0);

    p.estado = READY;

    if(!alocarMemoria(p.pid, p.nome, p.memoria)){

    printf(red "\nNao ha memoria suficiente.\n" reset);

    return;
    
    }

    processos[totalProcessos++] = p;

    printf("\n");

    linha(green, '=', LARGURA_MENU);
    centralizarRainbow("PROCESSO CRIADO", LARGURA_MENU);
    linha(green, '=', LARGURA_MENU);

    printf("PID.............: %d\n", p.pid);
    printf("Nome............: %s\n", p.nome);
    printf("Prioridade......: %d\n", p.prioridade);
    printf("Tempo...........: %d\n", p.tempoExecucao);
    printf("Memoria.........: %dMB\n", p.memoria);
    printf("Estado..........: %s\n", nomeEstado(p.estado));

    linha(green, '=', LARGURA_MENU);
}

void encerrarProcesso(int pid) {

    system("cls");

    linha(red, '=', LARGURA_MENU);
    centralizarRainbow("ENCERRAR PROCESSO", LARGURA_MENU);
    linha(red, '=', LARGURA_MENU);

    for(int i = 0; i < totalProcessos; i++) {

        if(processos[i].pid == pid) {

            if(processos[i].estado == TERMINATED) {

                printf("\nEsse processo ja esta encerrado!\n");
                return;
            }

            Estado estadoAnterior = processos[i].estado;

            processos[i].estado = TERMINATED;
            liberarMemoria(pid);

            printf("\nPID.............: %d\n", processos[i].pid);
            printf("Nome............: %s\n", processos[i].nome);
            printf("Estado..........: %s -> %s\n",
                   nomeEstado(estadoAnterior),
                   nomeEstado(processos[i].estado));

            printf("\nProcesso encerrado com sucesso!\n");
            printf("Memoria liberada automaticamente.\n");
            return;
        }
    }

    printf("\nPID nao encontrado!\n");
}

void alterarEstado(int pid, Estado novoEstado) {

    system("cls");

    linha(yellow, '=', LARGURA_MENU);
    centralizarRainbow("ALTERAR ESTADO", LARGURA_MENU);
    linha(yellow, '=', LARGURA_MENU);

    if(novoEstado < NEW || novoEstado > TERMINATED) {

        printf("\nEstado invalido!\n");
        return;
    }

    for(int i = 0; i < totalProcessos; i++) {

        if(processos[i].pid == pid) {

            Estado antigo = processos[i].estado;

            processos[i].estado = novoEstado;

            printf("\nPID.............: %d\n", processos[i].pid);
            printf("Nome............: %s\n", processos[i].nome);
            printf("Estado..........: %s -> %s\n",
                   nomeEstado(antigo),
                   nomeEstado(novoEstado));

            printf("\nEstado alterado com sucesso!\n");
            return;
        }
    }

    printf("\nPID nao encontrado!\n");
}

void exibirProcessos() {

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("LISTA DE PROCESSOS", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    if(totalProcessos == 0) {

        printf("\nNenhum processo cadastrado.\n");
        return;
    }

    printf("%-5s %-22s %-10s %-10s %-10s %-15s\n",
       "PID",
       "Nome",
       "Prior.",
       "Tempo",
       "RAM(MB)",
       "Estado");

    linha(cyan, '-', LARGURA_MENU);

    for(int i = 0; i < totalProcessos; i++) {

        printf("%-5d %-22s %-10d %-10d %-10d %-15s\n",
            processos[i].pid,
            processos[i].nome,
            processos[i].prioridade,
            processos[i].tempoExecucao,
            processos[i].memoria,
            nomeEstado(processos[i].estado));
    }

    linha(cyan, '-', LARGURA_MENU);

    printf("\nTotal de processos: %d\n", totalProcessos);
}

void MenuProcessos() {

    int op;
    int pid;
    int estado;

    do {

        system("cls");

        linha(cyan, '=', LARGURA_MENU);
        centralizarRainbow("GERENCIADOR DE PROCESSOS", LARGURA_MENU);
        linha(cyan, '=', LARGURA_MENU);

        printf("1 - Criar Processo\n");
        printf("2 - Encerrar Processo\n");
        printf("3 - Alterar Estado\n");
        printf("4 - Exibir Processos\n");
        printf("0 - Voltar ao Menu Principal\n");

        linha(cyan, '-', LARGURA_MENU);

        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:

                criarProcesso();
                pausar();
                break;

            case 2:

                pid = lerInteiro("PID: ");

                encerrarProcesso(pid);

                pausar();
                break;

            case 3:

                pid = lerInteiro("PID: ");

                printf("\n");
                printf("0 - NEW\n");
                printf("1 - READY\n");
                printf("2 - RUNNING\n");
                printf("3 - WAITING\n");
                printf("4 - TERMINATED\n\n");

                estado = lerInteiro("Novo Estado: ");

                alterarEstado(pid, (Estado)estado);

                pausar();
                break;

            case 4:

                exibirProcessos();

                pausar();
                break;

            case 0:

                printf("\nVoltando ao menu principal...");
                Sleep(700);
                break;

            default:

                printf(red "\nOpcao invalida!\n" reset);
                Sleep(700);
                break;
        }

    } while(op != 0);
}
