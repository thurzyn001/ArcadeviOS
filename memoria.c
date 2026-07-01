#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "memoria.h"
#include "utils.h"
#include "colors.h"

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

            printf(green "\nMemoria liberada com sucesso." reset);
            return;
        }
    }

    printf(yellow "\nNenhuma memoria encontrada para esse PID." reset);
}

void exibirBarraMemoria(int usada) {

    int largura = 60;
    int ocupados = (usada * largura) / MEMORIA_TOTAL;
    int porcentagem = (usada * 100) / MEMORIA_TOTAL;

    const char *cor;

    if(porcentagem < 50)
        cor = green;
    else if(porcentagem < 80)
        cor = yellow;
    else
        cor = red;

    printf("\nRAM: [");

    for(int i = 0; i < largura; i++) {

        if(i < ocupados)
            printf("%s█" reset, cor);
        else
            printf(white "░" reset);
    }

    printf("] %d%%\n", porcentagem);
}

void calcularBlocos(int *ocupados, int *livres) {

    *ocupados = 0;
    *livres = 0;

    for(int i = 0; i < totalBlocos; i++) {

        if(memoria[i].livre)
            (*livres)++;
        else
            (*ocupados)++;
    }
}

void exibirMapaMemoria() {

    system("cls");

    int usada = 0;
    int blocosOcupados = 0;
    int blocosLivres = 0;

    for(int i = 0; i < totalBlocos; i++) {
        if(!memoria[i].livre) {
            usada += memoria[i].tamanho;
        }
    }

    calcularBlocos(&blocosOcupados, &blocosLivres);

    linha(cyan, '=');
    centralizarRainbow("MAPA DE MEMORIA");
    linha(cyan, '=');

    exibirBarraMemoria(usada);

    printf("\n");

    linha(cyan, '-');

    printf("| %-14s : " green "%-8d" reset " MB | %-14s : " yellow "%-8d" reset " MB | %-14s : " green "%-8d" reset " MB |\n",
           "Total", MEMORIA_TOTAL,
           "Usada", usada,
           "Livre", MEMORIA_TOTAL - usada);

    linha(cyan, '-');

    printf("| %-25s : " red "%-5d" reset " | %-25s : " green "%-5d" reset " |\n",
           "Blocos utilizados", blocosOcupados,
           "Blocos livres", blocosLivres);

    linha(cyan, '-');

    printf("\n");

    printf(cyan "┌────────────┬────────────┬──────────────────────┬────────┬────────────────┐\n" reset);
printf(cyan "│ %-10s │ %-10s │ %-20s │ %-6s │ %-14s │\n" reset,
       "Inicio",
       "Tamanho",
       "Processo",
       "PID",
       "Status");
printf(cyan "├────────────┼────────────┼──────────────────────┼────────┼────────────────┤\n" reset);

for(int i = 0; i < totalBlocos; i++) {

    printf(cyan "│ " reset "%-10d" cyan " │ " reset,
           memoria[i].inicio);

    printf(green "%4d MB" reset, memoria[i].tamanho);
    printf("%3s", "");
    printf(cyan " │ " reset);

    if(memoria[i].livre)
        printf("%-20s", "-");
    else
        printf("%-20s", memoria[i].nomeProcesso);

    printf(cyan " │ " reset);

    if(memoria[i].livre)
        printf("%-6s", "-");
    else
        printf("%-6d", memoria[i].pid);

    printf(cyan " │ " reset);

    if(memoria[i].livre) {
        printf(green "● Livre" reset);
        printf("%7s", "");
    } else {
        printf(red "● Ocupado" reset);
        printf("%5s", "");
    }

    printf(cyan " │\n" reset);
}

printf(cyan "└────────────┴────────────┴──────────────────────┴────────┴────────────────┘\n" reset);
}

void menuMemoria() {

    int op;

    do {

        system("cls");

        linha(cyan, '=');
        centralizarRainbow("GERENCIADOR DE MEMORIA");
        linha(cyan, '=');

        printf("1 - Exibir Mapa de Memoria\n");
        printf("0 - Voltar\n");

        linha(cyan, '-');

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
