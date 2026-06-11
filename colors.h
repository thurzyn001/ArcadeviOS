#ifndef COLORS_H 
#define COLORS_H

#define reset        "\033[0m"

#define black        "\033[1;30m"
#define red          "\033[1;31m"
#define green        "\033[1;32m"
#define yellow       "\033[1;33m"
#define blue         "\033[1;34m"
#define magenta      "\033[1;35m"
#define cyan         "\033[1;36m"
#define white        "\033[1;37m"

void rainbow(const char *texto);

#endif

//Este arquivo é um cabeçalho onde está armazenada uma pequena biblioteca de cores e a função rainbow