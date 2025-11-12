#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transacao.h"
#include "utils.h"

int obterProximoID() {
    FILE *file = fopen("data/registros.txt", "r");
    int maxID = 0;
    
    if (file) {
        char linha[200];
        while (fgets(linha, sizeof(linha), file)) {
            int id;
            sscanf(linha, "%d;", &id);
            if (id > maxID) maxID = id;
        }
        fclose(file);
    }
    
    return maxID + 1;
}

void cadastrarTransacao() {
    Transacao t;
    FILE *file = fopen("data/registros.txt", "a");
    
    if (!file) {
        printf("\n  >> ERRO: Nao foi possivel abrir o arquivo!\n");
        return;
    }
    
    limparTela();
    desenharCabecalho("CADASTRAR NOVA TRANSACAO");
    
    t.id = obterProximoID();
    
    printf("\n");
    
    int tipoValido = 0;
    while (!tipoValido) {
        printf("  Tipo [1-Receita / 2-Despesa]: ");
        int opcao;
        scanf("%d", &opcao);
        getchar();
        
        if (opcao == 1) {
            strcpy(t.tipo, "Receita");
            tipoValido = 1;
        } else if (opcao == 2) {
            strcpy(t.tipo, "Despesa");
            tipoValido = 1;
        } else {
            printf("  >> Opcao invalida! Tente novamente.\n");
        }
    }
    
    printf("\n  Categorias sugeridas:\n");
    if (strcmp(t.tipo, "Receita") == 0) {
        printf("    - Salario, Vendas, Servicos, Investimentos, Outros\n");
    } else {
        printf("    - Aluguel, Fornecedores, Salarios, Marketing, Impostos, Outros\n");
    }
    printf("\n  Categoria: ");
    fgets(t.categoria, sizeof(t.categoria), stdin);
    t.categoria[strcspn(t.categoria, "\n")] = 0;
    
    printf("  Valor (R$): ");
    scanf("%f", &t.valor);
    getchar();
    
    int dataValida = 0;
    while (!dataValida) {
        printf("  Data (DD/MM/AAAA): ");
        fgets(t.data, sizeof(t.data), stdin);
        t.data[strcspn(t.data, "\n")] = 0;
        
        if (validarData(t.data)) {
            dataValida = 1;
        } else {
            printf("  >> Data invalida! Use o formato DD/MM/AAAA.\n");
        }
    }
    
    fprintf(file, "%d;%s;%s;%.2f;%s\n", t.id, t.tipo, t.categoria, t.valor, t.data);
    fclose(file);
    
    printf("\n");
    desenharLinha(50);
    printf("  >> Transacao #%d cadastrada com sucesso!\n", t.id);
    desenharLinha(50);
}

void listarTransacoes() {
    FILE *file = fopen("data/registros.txt", "r");
    
    limparTela();
    desenharCabecalho("LISTA DE TRANSACOES");
    
    if (!file) {
        printf("\n  >> Nenhuma transacao encontrada.\n");
        return;
    }
    
    printf("\n");
    printf("+------+------------+----------------------+-----------------+------------+\n");
    printf("| %-4s | %-10s | %-20s | %-15s | %-10s |\n", "ID", "TIPO", "CATEGORIA", "VALOR", "DATA");
    printf("+------+------------+----------------------+-----------------+------------+\n");
    
    char linha[200];
    int count = 0;
    
    while (fgets(linha, sizeof(linha), file)) {
        Transacao t;
        sscanf(linha, "%d;%[^;];%[^;];%f;%s", &t.id, t.tipo, t.categoria, &t.valor, t.data);
        
        printf("| %-4d | %-10s | %-20s | R$ %12.2f | %-10s |\n", 
               t.id, t.tipo, t.categoria, t.valor, t.data);
        count++;
    }
    
    fclose(file);
    printf("+------+------------+----------------------+-----------------+------------+\n");
    printf("\n  Total de registros: %d\n", count);
}