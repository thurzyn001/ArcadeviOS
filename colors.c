#include <stdio.h> //Biblioteca de entrada e saída
#include "colors.h" //Cabeçalho de colors.c

/*void rainbow é uma função q colore as letras de um texto na seguinte ordem, vermelho amarelo, verde, ciano, azul e magenta*/

void rainbow(const char *texto) {

    const char *cores[] = {
        red,
        yellow,
        green,
        cyan,
        blue,
        magenta
    };

    int i = 0;

    while(*texto) {
        printf("%s%c", cores[i % 6], *texto);
        texto++;
        i++;
    }

    printf(reset);
}

//Colors.c é um arquivo onde está armazenado a função rainbow.