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

void criarDiretorioData() {
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif
}

int validarData(char data[]) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;
    if (ano < 1900 || ano > 2100) return 0;
    return 1;
}