#include <stdio.h>
#include <windows.h>

#include "estatisticas.h"
#include "processos.h"
#include "memoria.h"
#include "dispositivos.h"
#include "arquivos.h"
#include "utils.h"
#include "colors.h"

void contarProcessos(int *ready, int *running, int *waiting, int *terminated) {

    *ready = 0;
    *running = 0;
    *waiting = 0;
    *terminated = 0;

    for(int i = 0; i < totalProcessos; i++) {

        switch(processos[i].estado) {

            case READY:
                (*ready)++;
                break;

            case RUNNING:
                (*running)++;
                break;

            case WAITING:
                (*waiting)++;
                break;

            case TERMINATED:
                (*terminated)++;
                break;

            default:
                break;
        }
    }
}

int memoriaUsadaAtual() {

    int usada = 0;

    for(int i = 0; i < totalBlocos; i++) {
        if(!memoria[i].livre) {
            usada += memoria[i].tamanho;
        }
    }

    return usada;
}

int espacoArquivosAtual() {

    int total = 0;

    for(int i = 0; i < totalArquivos; i++) {
        total += arquivos[i].tamanho;
    }

    return total;
}

void monitorSistema() {

    system("cls");

    int ready, running, waiting, terminated;
    int ramUsada = memoriaUsadaAtual();
    int espacoArquivos = espacoArquivosAtual();

    contarProcessos(&ready, &running, &waiting, &terminated);

    int porcentagemRAM = (ramUsada * 100) / MEMORIA_TOTAL;
    int porcentagemCPU;

    if(totalProcessos == 0) {
        porcentagemCPU = 0;
    } else {
        porcentagemCPU = (running * 70 + waiting * 20 + ready * 10) / totalProcessos;

        if(porcentagemCPU > 100) {
            porcentagemCPU = 100;
        }
    }

    linha(cyan, '=');
    centralizarRainbow("ARCADEVI MONITOR");
    linha(cyan, '=');

    printf("\n");
    barraProgresso("CPU", porcentagemCPU);
    printf("\n");
    barraProgresso("RAM", porcentagemRAM);
    printf("\n");

    if(totalProcessos == 0) {
        printf(green "Status do sistema: OCIOSO\n\n" reset);
    } else if(waiting > running) {
        printf(yellow "Status do sistema: AGUARDANDO DISPOSITIVOS\n\n" reset);
    } else {
        printf(green "Status do sistema: OPERACIONAL\n\n" reset);
    }

    cardInicio("PROCESSOS");
    char valor[50];

    snprintf(valor, sizeof(valor), "%d", ready);
    cardTextoCor("READY", valor, green);

    snprintf(valor, sizeof(valor), "%d", running);
    cardTextoCor("RUNNING", valor, yellow);

    snprintf(valor, sizeof(valor), "%d", waiting);
    cardTextoCor("WAITING", valor, magenta);

    snprintf(valor, sizeof(valor), "%d", terminated);
    cardTextoCor("TERMINATED", valor, red);

    snprintf(valor, sizeof(valor), "%d", totalProcessos);
    cardTexto("TOTAL", valor);
    cardFim();

    cardInicio("MEMORIA");
    cardTexto("RAM total", "1024 MB");

    snprintf(valor, sizeof(valor), "%d MB", ramUsada);
    cardTexto("RAM usada", valor);

    snprintf(valor, sizeof(valor), "%d MB", MEMORIA_TOTAL - ramUsada);
    cardTexto("RAM livre", valor);
    cardFim();

    cardInicio("DISPOSITIVOS");

    cardTextoCor("Impressora",
                 impressora.status == LIVRE ? "Livre" : "Ocupada",
                 impressora.status == LIVRE ? green : red);

    cardTextoCor("Scanner",
                 scanner.status == LIVRE ? "Livre" : "Ocupado",
                 scanner.status == LIVRE ? green : red);

    cardTextoCor("Disco",
                 disco.status == LIVRE ? "Livre" : "Ocupado",
                 disco.status == LIVRE ? green : red);

    cardTextoCor("Rede",
                 rede.status == LIVRE ? "Livre" : "Ocupada",
                 rede.status == LIVRE ? green : red);

    cardFim();

    cardInicio("ARQUIVOS");

    snprintf(valor, sizeof(valor), "%d", totalArquivos);
    cardTexto("Total de arquivos", valor);

    snprintf(valor, sizeof(valor), "%d KB", espacoArquivos);
    cardTexto("Espaco ocupado", valor);

    cardFim();

    linha(cyan, '=');
}