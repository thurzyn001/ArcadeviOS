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
void barraProgresso(const char *titulo, int porcentagem);
void cardInicio(const char *titulo);
void cardFim();

void cardLinha(const char *texto);
void cardTexto(const char *rotulo, const char *valor);
void cardTextoCor(const char *rotulo, const char *valor, const char *cor);
void cardNumero(const char *rotulo, int valor);
void menuPrincipal();

#endif
