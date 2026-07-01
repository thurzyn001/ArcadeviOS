#include <stdio.h> //Biblioteca de entrada e saída
#include <stdlib.h> //Biblioteca de funções utilitárias
#include <locale.h> //Biblioteca para configuração de localidade
#include <windows.h> //Biblioteca para funções específicas do Windows
#include <conio.h> //Biblioteca para funções de console

#include "processos.h" //Cabeçalho de processos.c
#include "colors.h" //Cabeçalho de colors.c
#include "utils.h" //Cabeçalho de utils.c
#include "escalonador.h" //Cabeçalho de escalonador.c
#include "memoria.h" //Cabeçalho de memoria.c

//Função Principal do Código
int main() {

    system("title ArcadeviOS 1.0"); //Define o título da janela do console
    system("mode con: cols=120 lines=40");

    setlocale(LC_ALL, "pt_BR.UTF-8"); 
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleCP(CP_UTF8); //comandos para forçar o terminal a usar o padrão UTF-8

    inicializarMemoria(); // Inicializa a memória

    menuPrincipal(); // Chamada da Funcão do Menu principal

    return 0;
}
