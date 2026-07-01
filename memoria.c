#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "memoria.h"
#include "utils.h"
#include "colors.h"

#define LARGURA_MENU 75

BlocoMemoria memoria[MAX_BLOCOS];
int totalBlocos = 0;

void inicializarMemoria() {

    totalBlocos = 1;

    memoria[0].inicio = 0;
    memoria[0].tamanho = MEMORIA_TOTAL;
    memoria[0].livre = 1;
    memoria[0].pid = -1;
    strcpy(memoria[0].nomeProcesso, "Livre");
}

int alocarMemoria(int pid, const char *nomeProcesso, int tamanho) {

    for(int i = 0; i < totalBlocos; i++) {

        if(memoria[i].livre && memoria[i].tamanho >= tamanho) {

            int sobra = memoria[i].tamanho - tamanho;

            memoria[i].livre = 0;
            memoria[i].pid = pid;
            memoria[i].tamanho = tamanho;
            strcpy(memoria[i].nomeProcesso, nomeProcesso);

            if(sobra > 0 && totalBlocos < MAX_BLOCOS) {

                for(int j = totalBlocos; j > i + 1; j--) {
                    memoria[j] = memoria[j - 1];
                }

                memoria[i + 1].inicio = memoria[i].inicio + tamanho;
                memoria[i + 1].tamanho = sobra;
                memoria[i + 1].livre = 1;
                memoria[i + 1].pid = -1;
                strcpy(memoria[i + 1].nomeProcesso, "Livre");

                totalBlocos++;
            }

            return 1;
        }
    }

    return 0;
}

void unirBlocosLivres() {

    for(int i = 0; i < totalBlocos - 1; i++) {

        if(memoria[i].livre && memoria[i + 1].livre) {

            memoria[i].tamanho += memoria[i + 1].tamanho;

            for(int j = i + 1; j < totalBlocos - 1; j++) {
                memoria[j] = memoria[j + 1];
            }

            totalBlocos--;
            i--;
        }
    }
}

void liberarMemoria(int pid) {

    for(int i = 0; i < totalBlocos; i++) {

        if(!memoria[i].livre && memoria[i].pid == pid) {

            memoria[i].livre = 1;
            memoria[i].pid = -1;
            strcpy(memoria[i].nomeProcesso, "Livre");

            unirBlocosLivres();

            printf(green "\nMemoria liberada com sucesso.\n" reset);
            return;
        }
    }

    printf(yellow "\nNenhuma memoria encontrada para esse PID.\n" reset);
}

void exibirMapaMemoria() {

    system("cls");

    linha(cyan, '=', LARGURA_MENU);
    centralizarRainbow("MAPA DE MEMORIA", LARGURA_MENU);
    linha(cyan, '=', LARGURA_MENU);

    int usada = 0;

    for(int i = 0; i < totalBlocos; i++) {
        if(!memoria[i].livre) {
            usada += memoria[i].tamanho;
        }
    }

    printf("Memoria total....: %d MB\n", MEMORIA_TOTAL);
    printf("Memoria usada....: %d MB\n", usada);
    printf("Memoria livre....: %d MB\n\n", MEMORIA_TOTAL - usada);

    printf("%-10s %-10s %-10s %-25s\n",
           "Inicio",
           "Tamanho",
           "Status",
           "Processo");

    linha(cyan, '-', LARGURA_MENU);

    for(int i = 0; i < totalBlocos; i++) {

        printf("%-10d %-10d %-10s %-25s\n",
               memoria[i].inicio,
               memoria[i].tamanho,
               memoria[i].livre ? "Livre" : "Ocupado",
               memoria[i].nomeProcesso);
    }

    linha(cyan, '-', LARGURA_MENU);
}

void menuMemoria() {

    int op;

    do {

        system("cls");

        linha(cyan, '=', LARGURA_MENU);
        centralizarRainbow("GERENCIADOR DE MEMORIA", LARGURA_MENU);
        linha(cyan, '=', LARGURA_MENU);

        printf("1 - Exibir Mapa de Memoria\n");
        printf("0 - Voltar\n");

        linha(cyan, '-', LARGURA_MENU);

        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:
                exibirMapaMemoria();
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
