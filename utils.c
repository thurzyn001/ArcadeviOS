#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "colors.h"

void centralizar(const char *texto, int largura) {

    int tamanho = strlen(texto);
    int espacos = (largura - tamanho) / 2;

    for(int i = 0; i < espacos; i++) {
        printf(" ");
    }

    printf("%s", texto);
}

void centralizarRainbow(const char *texto, int largura) {

    int tamanho = strlen(texto);
    int espacos = (largura - tamanho) / 2;

    for(int i = 0; i < espacos; i++) {
        printf(" ");
    }

    rainbow(texto);
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    while(getchar() != '\n');
    getchar();
}