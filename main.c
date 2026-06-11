#include <stdio.h> //Biblioteca de entrada e saída
#include <stdlib.h> //Biblioteca de funções utilitárias
#include <locale.h> //Biblioteca para configuração de localidade
#include <windows.h> //Biblioteca para funções específicas do Windows
#include <conio.h> //Biblioteca para funções de console

#include "processos.h" //Cabeçalho de processos.c
#include "colors.h" //Cabeçalho de colors.c
#include "utils.h" //Cabeçalho de utils.c

//Função Principal do Código

int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8"); //comando para forçar o terminal a usar o padrão UTF-8

    menuPrincipal(); // Chamada da Funcão do Menu principal

    return 0;
}