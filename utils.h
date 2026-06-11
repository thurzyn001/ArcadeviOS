#ifndef UTILS_H
#define UTILS_H

void limparBuffer();
void linha(const char *cor, char caractere, int tamanho);
void apagarLinhas(int n);
void lerTexto(const char *mensagem, char *destino, int tamanho);
int lerInteiro(const char *mensagem);
void centralizar(const char *texto, int largura);
void centralizarRainbow(const char *texto, int largura);
void pausar();
void menuPrincipal();

#endif