#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#include "utils.h"
#include "colors.h"
#include "processos.h"

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void linha(const char *cor, char caractere, int tamanho) {

    printf("%s", cor);

    for(int i = 0; i < tamanho; i++) {
        printf("%c", caractere);
    }

    printf("%s\n", reset);
}

void apagarLinhas(int n) {
    for(int i = 0; i < n; i++) {
        printf("\033[A");   // sobe
        printf("\033[2K");  // limpa
    }
}

void lerString(const char *mensagem, char *destino, int tamanho) {

    int valido;

    while(1) {

        valido = 1;

        printf("%s", mensagem);

        fgets(destino, tamanho, stdin);

        destino[strcspn(destino, "\n")] = '\0';

        if(strlen(destino) == 0) {
            printf("Entrada vazia!\n");
            Sleep(500);
            apagarLinhas(2);
            continue;
        }

        for(int i = 0; destino[i] != '\0'; i++) {

            if(
                !isalnum(destino[i]) &&
                destino[i] != ' ' &&
                destino[i] != '_' &&
                destino[i] != '-' &&
                destino[i] != '.'
            ) {
                valido = 0;
                break;
            }
        }

        if(valido) {
            return;
        }

        printf("Entrada Inválida!\n");
        Sleep(500);
        apagarLinhas(2);
    }
}

int lerInteiro(const char *mensagem) {

    char entrada[50];
    char *fim;
    long valor;

    while(1) {

        printf("%s", mensagem);

        fgets(entrada, sizeof(entrada), stdin);

        if(entrada[0] == '\n') {
            printf("Entrada vazia!\n");
            Sleep(500);
            apagarLinhas(2);
            continue;
        }

        valor = strtol(entrada, &fim, 10);

        if(*fim == '\n') {
            return (int)valor;
        }

        printf("Entrda invalida!\n");
        Sleep(500);
        apagarLinhas(2);
    }
}

void centralizar(const char *texto, int largura) {

    int tamanho = strlen(texto);
    int espacos = (largura - tamanho) / 2;

    for(int i = 0; i < espacos; i++) {
        printf(" ");
    }

    printf("%s\n", texto);
}

void centralizarRainbow(const char *texto, int largura) {

    int tamanho = strlen(texto);
    int espacos = (largura - tamanho) / 2;

    for(int i = 0; i < espacos; i++) {
        printf(" ");
    }

    rainbow(texto);
    printf("\n");
}

void pausar() {

    int tecla;

    printf("\nPressione ENTER para continuar...");

    do {
        tecla = getch();
    } while(tecla != 13); // Enter
}

void menuPrincipal(){

    int op;

    do {
        
        system("cls");

        linha(cyan, '=', 50);
        centralizarRainbow("ArcadeviOS", 50);
        linha(cyan, '=', 50);

        printf("1 - Processos\n");
        printf("2 - Escalonador\n");
        printf("3 - Memória\n");
        printf("4 - Dispositivos\n");
        printf("5 - Arquivos\n");
        printf("6 - Estatisticas\n");
        printf("0 - Sair\n");

        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:
                MenuProcessos();
                break;

            case 2:
                apagarLinhas(1);
                printf("WIP");
                Sleep(1000);
                break;

            case 3:
                apagarLinhas(1);
                printf("WIP");
                Sleep(1000);
                break;

            case 4:
                apagarLinhas(1);
                printf("WIP");
                Sleep(1000);
                break;

            case 5:
                apagarLinhas(1);
                printf("WIP");
                Sleep(1000);
                break;

            case 6:
                apagarLinhas(1);
                printf("WIP");
                Sleep(1000);
                break;

            case 0:
                apagarLinhas(1);
                printf("Saindo...");
                Sleep(1000);
                break;


            default:
                apagarLinhas(1);
                printf("Opcao invalida!");
                Sleep(1000);
                break;
            }


    }while(op != 0);
}
