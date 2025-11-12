#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios.h"
#include "transacao.h"
#include "utils.h"

float calcularTotal(char tipo[]) {
    FILE *file = fopen("data/registros.txt", "r");
    if (!file) return 0.0;
    
    char linha[200];
    float total = 0.0;
    
    while (fgets(linha, sizeof(linha), file)) {
        Transacao t;
        sscanf(linha, "%*d;%[^;];%*[^;];%f;", t.tipo, &t.valor);
        
        if (strcmp(t.tipo, tipo) == 0) {
            total += t.valor;
        }
    }
    
    fclose(file);
    return total;
}
