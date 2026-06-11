#include <stdio.h> //Biblioteca de entrada e saída
#include <stdlib.h> //Biblioteca de funções utilitárias
#include <locale.h> //Biblioteca para configuração de localidade
#include <windows.h> //Biblioteca para funções específicas do Windows
#include <conio.h> //Biblioteca para funções de console

#include "processos.h" //Cabeçalho de processos.c
#include "colors.h" //Cabeçalho de colors.c
#include "utils.h" //Cabeçalho de utils.c

/*Função Principal do Código, onde está o menu principal do ArcadeviOS*/

int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8"); //comando para forçar o terminal a usar o padrão UTF-8, de encoding, evitando problemas com acentos.

    int op;

    do {
        
        system("cls");

        printf(cyan "==================================================" reset "\n");
        centralizar("ArcadeviOS", 50);
        printf(cyan "\n==================================================" reset "\n");

        printf("1 - Processos\n");
        printf("2 - Escalonador\n");
        printf("3 - Memória\n");
        printf("4 - Dispositivos\n");
        printf("5 - Arquivos\n");
        printf("6 - Estatisticas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

    switch(op) {

        case 1:
            MenuProcessos();
            break;

        case 2:
            printf("WIP\n");
            Sleep(1000);
            break;

        case 3:
            printf("WIP\n");
            Sleep(1000);
            break;

        case 4:
            printf("WIP\n");
            Sleep(1000);
            break;

        case 5:
            printf("WIP\n");
            Sleep(1000);
            break;

        case 6:
            printf("WIP\n");
            Sleep(1000);
            break;

        case 0:
            printf("Saindo...\n");
            break;


        default:
            printf("Opcao invalida!\n");
            Sleep(1000);
            break;
        }


    }while(op != 0);

    return 0;
}