#include <stdio.h> //Biblioteca de entrada e saída
#include <stdlib.h> //Biblioteca de funções utilitárias
#include <string.h> //Biblioteca para manipulação de strings
#include <conio.h> //Biblioteca para funções de console

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

    system("cls");

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

    int op;
    int pid;
    int estado;

    do {

        system("cls");

        printf(cyan "==================================================" reset "\n");
        centralizarRainbow("Gerenciador de Processos", 50);
        printf(cyan "\n==================================================" reset "\n");

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
                printf("\nPressione qualquer tecla para continuar...");
                getch();
                system("cls");
                break;
        }

    }while(op != 0);

}
