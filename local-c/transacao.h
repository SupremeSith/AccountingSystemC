#ifndef TRANSACAO_H
#define TRANSACAO_H

typedef struct {
    int id;
    char tipo[20];
    char categoria[50];
    float valor;
    char data[11];
} Transacao;

void cadastrarTransacao();
void listarTransacoes();
int obterProximoID();

#endif