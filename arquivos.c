#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "arquivos.h"
#include "utils.h"
#include "colors.h"

Arquivo arquivos[MAX_ARQUIVOS];
int totalArquivos = 0;

void criarArquivo() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("CRIAR ARQUIVO");
    linha(cyan, '=');

    if(totalArquivos >= MAX_ARQUIVOS) {
        printf(red "\nLimite de arquivos atingido.\n" reset);
        return;
    }

    Arquivo a;

    lerString("Nome do arquivo...: ", a.nome, sizeof(a.nome));

    do {
        a.tamanho = lerInteiro("Tamanho (KB).....: ");

        if(a.tamanho <= 0) {
            printf(red "\nO tamanho deve ser maior que zero.\n" reset);
            Sleep(700);
        }

    } while(a.tamanho <= 0);

    arquivos[totalArquivos++] = a;

    printf(green "\nArquivo criado com sucesso!\n" reset);
    printf("Nome....: %s\n", a.nome);
    printf("Tamanho.: %d KB\n", a.tamanho);
}

void removerArquivo() {

    system("cls");

    linha(red, '=');
    centralizarRainbow("REMOVER ARQUIVO");
    linha(red, '=');

    if(totalArquivos == 0) {
        printf("\nNenhum arquivo cadastrado.\n");
        return;
    }

    char nome[50];

    lerString("Nome do arquivo: ", nome, sizeof(nome));

    for(int i = 0; i < totalArquivos; i++) {

        if(strcmp(arquivos[i].nome, nome) == 0) {

            for(int j = i; j < totalArquivos - 1; j++) {
                arquivos[j] = arquivos[j + 1];
            }

            totalArquivos--;

            printf(green "\nArquivo removido com sucesso.\n" reset);
            return;
        }
    }

    printf(red "\nArquivo nao encontrado.\n" reset);
}

void listarArquivos() {

    system("cls");

    linha(cyan, '=');
    centralizarRainbow("SISTEMA DE ARQUIVOS");
    linha(cyan, '=');

    if(totalArquivos == 0) {
        printf("\nNenhum arquivo cadastrado.\n");
        return;
    }

    printf(cyan "┌──────┬────────────────────────────────┬──────────────┐\n" reset);
    printf(cyan "│ %-4s │ %-30s │ %-12s │\n" reset,
           "ID",
           "Arquivo",
           "Tamanho");
    printf(cyan "├──────┼────────────────────────────────┼──────────────┤\n" reset);

    for(int i = 0; i < totalArquivos; i++) {

        printf(cyan "│ " reset "%-4d" cyan " │ " reset "%-30s" cyan " │ " reset green "%8d KB" reset cyan "  │\n" reset,
               i + 1,
               arquivos[i].nome,
               arquivos[i].tamanho);
    }

    printf(cyan "└──────┴────────────────────────────────┴──────────────┘\n" reset);

    int total = 0;

    for(int i = 0; i < totalArquivos; i++) {
        total += arquivos[i].tamanho;
    }

    printf("\nTotal de arquivos.: %d\n", totalArquivos);
    printf("Espaco ocupado....: %d KB\n", total);
}

void buscarArquivo() {

    system("cls");

    linha(yellow, '=');
    centralizarRainbow("BUSCAR ARQUIVO");
    linha(yellow, '=');

    if(totalArquivos == 0) {
        printf("\nNenhum arquivo cadastrado.\n");
        return;
    }

    char nome[50];

    lerString("Nome do arquivo: ", nome, sizeof(nome));

    for(int i = 0; i < totalArquivos; i++) {

        if(strcmp(arquivos[i].nome, nome) == 0) {

            printf(green "\nArquivo encontrado!\n" reset);
            printf("ID......: %d\n", i + 1);
            printf("Nome....: %s\n", arquivos[i].nome);
            printf("Tamanho.: %d KB\n", arquivos[i].tamanho);
            return;
        }
    }

    printf(red "\nArquivo nao encontrado.\n" reset);
}

void menuArquivos() {

    int op;

    do {

        system("cls");

        linha(cyan, '=');
        centralizarRainbow("SISTEMA DE ARQUIVOS");
        linha(cyan, '=');

        printf("1 - Criar Arquivo\n");
        printf("2 - Remover Arquivo\n");
        printf("3 - Listar Arquivos\n");
        printf("4 - Buscar Arquivo\n");
        printf("0 - Voltar\n");

        linha(cyan, '-');

        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:
                criarArquivo();
                pausar();
                break;

            case 2:
                removerArquivo();
                pausar();
                break;

            case 3:
                listarArquivos();
                pausar();
                break;

            case 4:
                buscarArquivo();
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
