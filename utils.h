#ifndef UTILS_H
#define UTILS_H

void limparBuffer();
void linha(const char *cor, char caractere);
void apagarLinhas(int n);
void lerString(const char *mensagem, char *destino, int tamanho);
int lerInteiro(const char *mensagem);
int larguraTerminal();
void centralizar(const char *texto);
void centralizarRainbow(const char *texto);
void pausar();
void menuPrincipal();

#endif
