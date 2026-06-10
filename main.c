#include <stdio.h> //Biblioteca de entrada e saída
#include <stdlib.h> //Biblioteca de funções utilitárias
#include <locale.h> //Biblioteca para configuração de localidade
#include <windows.h> //Biblioteca para funções específicas do Windows
#include "processos.h" //Cabeçalho para gerenciamento de processos

int main() {
    //
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int op;

    do {
        
        system("cls");

        printf("\033[1;36m=====================================\033[0m\n");
        printf("             ");
        printf("\033[1;31mA\033[1;33mr\033[1;32mc\033[1;36ma\033[1;34md\033[1;35me\033[1;31mv\033[1;33mi\033[1;32mO\033[1;36mS\033[0m\n");
        printf("\033[1;36m=====================================\033[0m\n");

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