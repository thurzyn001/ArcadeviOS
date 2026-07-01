#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#include "utils.h"
#include "colors.h"
#include "processos.h"
#include "escalonador.h"
#include "memoria.h"
#include "arquivos.h"
#include "dispositivos.h"
#include "estatisticas.h"
#include "concorrencia.h"

#define CARD_LARGURA 70
#define CARD_INTERNA (CARD_LARGURA - 2)

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void linha(const char *cor, char caractere) {

    int largura = larguraTerminal() - 1;

    printf("%s", cor);

    for(int i = 0; i < largura; i++) {
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

int larguraTerminal() {

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    return 80;
}

void centralizar(const char *texto) {

    int largura = larguraTerminal() - 1;
    int tamanho = strlen(texto);
    int espacos = (largura - tamanho) / 2;

    if(espacos < 0)
        espacos = 0;

    for(int i = 0; i < espacos; i++) {
        printf(" ");
    }

    printf("%s\n", texto);
}

void centralizarRainbow(const char *texto) {

    int largura = larguraTerminal() - 1;
    int tamanho = strlen(texto);
    int espacos = (largura - tamanho) / 2;

    if(espacos < 0)
        espacos = 0;

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

void barraProgresso(const char *titulo, int porcentagem) {

    int largura = 60;

    if(porcentagem < 0)
        porcentagem = 0;

    if(porcentagem > 100)
        porcentagem = 100;

    int preenchidos = (porcentagem * largura) / 100;

    const char *cor;

    if(porcentagem < 50)
        cor = green;
    else if(porcentagem < 80)
        cor = yellow;
    else
        cor = red;

    printf("%s: [", titulo);

    for(int i = 0; i < largura; i++) {

        if(i < preenchidos)
            printf("%s█" reset, cor);
        else
            printf(white "░" reset);
    }

    printf("] %d%%\n", porcentagem);
}

void cardInicio(const char *titulo) {

    int tamanho = strlen(titulo);
    int esquerda = (CARD_INTERNA - tamanho) / 2;
    int direita = CARD_INTERNA - tamanho - esquerda;

    printf("\n");

    printf(cyan "┌");
    for(int i = 0; i < CARD_INTERNA; i++) printf("─");
    printf("┐\n");

    printf("│");
    for(int i = 0; i < esquerda; i++) printf(" ");
    printf("%s", titulo);
    for(int i = 0; i < direita; i++) printf(" ");
    printf("│\n");

    printf("├");
    for(int i = 0; i < CARD_INTERNA; i++) printf("─");
    printf("┤\n" reset);
}

void cardFim() {

    printf(cyan "└");
    for(int i = 0; i < CARD_INTERNA; i++) printf("─");
    printf("┘\n" reset);
}

void cardLinha(const char *texto) {

    int tamanho = strlen(texto);
    int espacos = CARD_INTERNA - tamanho - 2;

    if(espacos < 0) espacos = 0;

    printf(cyan "│ " reset);
    printf("%s", texto);

    for(int i = 0; i < espacos; i++) printf(" ");

    printf(cyan " │\n" reset);
}

void cardTexto(const char *rotulo, const char *valor) {

    char texto[150];

    snprintf(texto, sizeof(texto),
             "%-24s: %s",
             rotulo,
             valor);

    cardLinha(texto);
}

void cardNumero(const char *rotulo, int valor) {

    char valorTexto[30];

    snprintf(valorTexto, sizeof(valorTexto), "%d", valor);

    cardTexto(rotulo, valorTexto);
}

void cardTextoCor(const char *rotulo, const char *valor, const char *cor) {

    int tamanhoVisivel = 1 + 24 + 2 + strlen(valor);
    int espacos = CARD_INTERNA - tamanhoVisivel - 1;

    if(espacos < 0) espacos = 0;

    printf(cyan "│ " reset);
    printf("%-24s: %s%s" reset, rotulo, cor, valor);

    for(int i = 0; i < espacos; i++) printf(" ");

    printf(cyan " │\n" reset);
}

void menuPrincipal(){

    int op;

    do {
        
        system("cls");

        linha(cyan, '=');
        centralizarRainbow("ArcadeviOS");
        linha(cyan, '=');

        printf("1 - Processos\n");
        printf("2 - Escalonador\n");
        printf("3 - Memória\n");
        printf("4 - Dispositivos\n");
        printf("5 - Arquivos\n");
        printf("6 - Estatisticas\n");
        printf("7 - Concorrencia\n");
        printf("0 - Sair\n");

        op = lerInteiro("Opcao: ");

        switch(op) {

            case 1:
                MenuProcessos();
                break;

            case 2:
                menuEscalonador();
                break;

            case 3:
                apagarLinhas(1);
                menuMemoria();
                Sleep(1000);
                break;

            case 4:
                apagarLinhas(1);
                menuDispositivos();
                Sleep(1000);
                break;

            case 5:
                apagarLinhas(1);
                menuArquivos();
                Sleep(1000);
                break;

            case 6:
                apagarLinhas(1);
                monitorSistema();
                pausar();
                break;

            case 7:
                apagarLinhas(1);
                menuConcorrencia();
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
