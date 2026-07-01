#ifndef DISPOSITIVOS_H
#define DISPOSITIVOS_H

#define MAX_FILA 100

typedef enum {
    LIVRE,
    OCUPADO
} StatusDispositivo;

typedef struct {

    char nome[30];

    StatusDispositivo status;

    int pidAtual;

    int fila[MAX_FILA];

    int inicioFila;
    int fimFila;

} Dispositivo;

extern Dispositivo impressora;
extern Dispositivo scanner;
extern Dispositivo disco;
extern Dispositivo rede;

void inicializarDispositivos();

void mostrarUmDispositivo(Dispositivo *d);
void inicializarDispositivo(Dispositivo *d, const char *nome);

void enfileirar(Dispositivo *d, int pid);
int desenfileirar(Dispositivo *d);
int filaVazia(Dispositivo *d);

void solicitarDispositivo(Dispositivo *d, int pid);
void liberarDispositivo(Dispositivo *d);

void mostrarDispositivos();

void mostrarProcessosParaDispositivo();

void resetarDispositivos();

void menuDispositivos();

#endif
