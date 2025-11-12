#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void limparTela() {
    system(CLEAR);
}

void pausar() {
    printf("\n  Pressione ENTER para continuar...");
    getchar();
}

void desenharLinha(int tamanho) {
    for (int i = 0; i < tamanho; i++) printf("-");
    printf("\n");
}

void desenharCabecalho(char *titulo) {
    int tam = strlen(titulo);
    int total = 50;
    int espacos = (total - tam) / 2;
    
    printf("\n");
    desenharLinha(total);
    for (int i = 0; i < espacos; i++) printf(" ");
    printf("%s\n", titulo);
    desenharLinha(total);
}


