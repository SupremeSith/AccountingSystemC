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

void menuRelatorios() {
    int opcao;
    
    limparTela();
    desenharCabecalho("RELATORIOS E ANALISES");
    
    printf("\n");
    printf("  1. Relatorio por mes/ano\n");
    printf("  2. Relatorio por categoria\n");
    printf("  0. Voltar\n\n");
    
    printf("  Escolha: ");
    scanf("%d", &opcao);
    getchar();
    
    if (opcao == 1) {
        int mes, ano;
        printf("\n  Mes (1-12): ");
        scanf("%d", &mes);
        printf("  Ano: ");
        scanf("%d", &ano);
        getchar();
        
        limparTela();
        gerarRelatorioPorMes(mes, ano);
    } else if (opcao == 2) {
        limparTela();
        gerarRelatorioPorCategoria();
    }
}

void gerarRelatorioPorMes(int mes, int ano) {
    FILE *file = fopen("data/registros.txt", "r");
    
    char titulo[50];
    sprintf(titulo, "RELATORIO MENSAL %02d/%d", mes, ano);
    desenharCabecalho(titulo);
    
    if (!file) {
        printf("\n  >> Nenhum dado encontrado.\n");
        return;
    }
    
    char linha[200];
    float totalReceita = 0, totalDespesa = 0;
    int count = 0;
    
    printf("\n");
    printf("+------------+----------------------+-----------------+------------+\n");
    printf("| %-10s | %-20s | %-15s | %-10s |\n", "TIPO", "CATEGORIA", "VALOR", "DATA");
    printf("+------------+----------------------+-----------------+------------+\n");
    
    while (fgets(linha, sizeof(linha), file)) {
        Transacao t;
        sscanf(linha, "%*d;%[^;];%[^;];%f;%s", t.tipo, t.categoria, &t.valor, t.data);
        
        int m, a;
        sscanf(t.data, "%*d/%d/%d", &m, &a);
        
        if (m == mes && a == ano) {
            printf("| %-10s | %-20s | R$ %12.2f | %-10s |\n", 
                   t.tipo, t.categoria, t.valor, t.data);
            
            if (strcmp(t.tipo, "Receita") == 0)
                totalReceita += t.valor;
            else
                totalDespesa += t.valor;
            
            count++;
        }
    }
    
    fclose(file);
    
    printf("+------------+----------------------+-----------------+------------+\n");
    printf("\n");
    desenharLinha(50);
    printf("  RESUMO FINANCEIRO:\n");
    desenharLinha(50);
    printf("  Receitas:      R$ %12.2f\n", totalReceita);
    printf("  Despesas:      R$ %12.2f\n", totalDespesa);
    printf("  ---------------------------------\n");
    printf("  Lucro liquido: R$ %12.2f\n", totalReceita - totalDespesa);
    printf("  Transacoes:    %15d\n", count);
    desenharLinha(50);
}

void gerarRelatorioPorCategoria() {
    FILE *file = fopen("data/registros.txt", "r");
    
    desenharCabecalho("RELATORIO POR CATEGORIA");
    
    if (!file) {
        printf("\n  >> Nenhum dado encontrado.\n");
        return;
    }
    
    char categorias[100][50];
    float valores[100] = {0};
    int count = 0;
    
    char linha[200];
    while (fgets(linha, sizeof(linha), file)) {
        Transacao t;
        sscanf(linha, "%*d;%*[^;];%[^;];%f;", t.categoria, &t.valor);
        
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(categorias[i], t.categoria) == 0) {
                valores[i] += t.valor;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(categorias[count], t.categoria);
            valores[count] = t.valor;
            count++;
        }
    }
    
    fclose(file);
    
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += valores[i];
    }
    
    printf("\n");
    printf("+---------------------------+-----------------+------------+\n");
    printf("| %-25s | %-15s | %-10s |\n", "CATEGORIA", "VALOR", "PERCENTUAL");
    printf("+---------------------------+-----------------+------------+\n");
    
    for (int i = 0; i < count; i++) {
        float percentual = (valores[i] / total) * 100;
        printf("| %-25s | R$ %12.2f | %8.1f%% |\n", categorias[i], valores[i], percentual);
    }
    
    printf("+---------------------------+-----------------+------------+\n");
    printf("| %-25s | R$ %12.2f | %8.0f%% |\n", "TOTAL", total, 100.0);
    printf("+---------------------------+-----------------+------------+\n");
}

void exibirDashboard() {
    limparTela();
    desenharCabecalho("DASHBOARD FINANCEIRO");
    
    float totalReceitas = calcularTotal("Receita");
    float totalDespesas = calcularTotal("Despesa");
    float saldo = totalReceitas - totalDespesas;
    
    printf("\n");
    desenharLinha(50);
    printf("  RECEITAS TOTAIS:  R$ %18.2f\n", totalReceitas);
    printf("  DESPESAS TOTAIS:  R$ %18.2f\n", totalDespesas);
    desenharLinha(50);
    
    if (saldo >= 0) {
        printf("  SALDO POSITIVO:   R$ %18.2f\n", saldo);
    } else {
        printf("  SALDO NEGATIVO:   R$ %18.2f\n", saldo);
    }
    desenharLinha(50);
}

void exportarCSV() {
    FILE *entrada = fopen("data/registros.txt", "r");
    FILE *saida = fopen("data/relatorio.csv", "w");
    
    limparTela();
    desenharCabecalho("EXPORTAR PARA CSV");
    
    if (!entrada) {
        printf("\n  >> ERRO: Nenhum dado para exportar!\n");
        if (saida) fclose(saida);
        return;
    }
    
    if (!saida) {
        printf("\n  >> ERRO: Nao foi possivel criar o arquivo CSV!\n");
        fclose(entrada);
        return;
    }
    
    fprintf(saida, "ID,TIPO,CATEGORIA,VALOR,DATA\n");
    
    char linha[200];
    int count = 0;
    
    while (fgets(linha, sizeof(linha), entrada)) {
        Transacao t;
        sscanf(linha, "%d;%[^;];%[^;];%f;%s", &t.id, t.tipo, t.categoria, &t.valor, t.data);
        fprintf(saida, "%d,%s,%s,%.2f,%s\n", t.id, t.tipo, t.categoria, t.valor, t.data);
        count++;
    }
    
    fclose(entrada);
    fclose(saida);
    
    printf("\n");
    desenharLinha(50);
    printf("  >> Arquivo CSV gerado com sucesso!\n");
    printf("  >> Localizacao: data/relatorio.csv\n");
    printf("  >> Registros exportados: %d\n", count);
    desenharLinha(50);
    printf("\n  Voce pode abrir este arquivo no Excel!\n");
}