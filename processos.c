#include <stdio.h> //Biblioteca de entrada e saída
#include <stdlib.h> //Biblioteca de funções utilitárias
#include <string.h> //Biblioteca para manipulação de strings
#include <conio.h> //Biblioteca para funções de console
#include <windows.h> //Biblioteca para funções específicas do Windows

#include "processos.h" //Cabeçalho para gerenciamento de processos
#include "colors.h"
#include "utils.h"

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

    system("cls");

    if(totalProcessos >= MAX_PROCESSOS) {
        printf("Limite de processos atingido!\n");
        return;
    }

    Processo p;

    p.pid = proxPID++;

    lerString("Nome: ", p.nome, sizeof(p.nome));

    p.prioridade = lerInteiro("Prioridade: ");

    p.tempoExecucao = lerInteiro("Tempo de Execução: ");

    p.estado = NEW;

    processos[totalProcessos++] = p;

    printf("Processo criado com PID: %d\n", p.pid);
}

void encerrarProcesso(int pid) {

    system("cls");

    for(int i = 0; i < totalProcessos; i++) {
        if(processos[i].pid == pid) {
            processos[i].estado = TERMINATED;
            printf("Processo %s de Pid: %d encerrado.\n", processos[i].nome, processos[i].pid);
            return;
        }
    }

    printf("PID nao encontrado.\n");
}

void alterarEstado(int pid, Estado novoEstado) {

    system("cls");

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

    system("cls");

    printf("\n-------------------------------------\n");
    printf("PID\tNome\t\tEstado\n");
    printf("-------------------------------------\n");

    for(int i = 0; i < totalProcessos; i++) {
        printf("%d\t%s\t\t%s\n",
               processos[i].pid,
               processos[i].nome,
               nomeEstado(processos[i].estado));
    }

    printf("-------------------------------------\n");
}

void MenuProcessos(){

    int op;
    int pid;
    int estado;

    do {

        system("cls");

        linha(cyan, '=', 50);
        centralizarRainbow("Gerenciador de Processos", 50);
        linha(cyan, '=', 50);


        printf("1 - Criar Processo\n");
        printf("2 - Encerrar Processo\n");
        printf("3 - Alterar Estado\n");
        printf("4 - Exibir Processos\n");
        printf("0 - Voltar ao Menu Principal\n");
        
        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:
                criarProcesso();
                pausar();
                break;

            case 2:
                printf("PID: ");
                scanf("%d", &pid);
                encerrarProcesso(pid);
                pausar();
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
                pausar();
                break;

            case 4:
                exibirProcessos();
                pausar();
                break;

            case 0:
                apagarLinhas(2);
                printf("\nVoltando ao Menu principal...\n");
                Sleep(750);
                break;

            default:
                printf("Opcao invalida!\n");
                Sleep(750);
                break;
        }

    }while(op != 0);

}
