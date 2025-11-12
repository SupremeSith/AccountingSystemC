#include <stdio.h>
#include <stdlib.h>
#include "transacao.h"
#include "relatorios.h"
#include "utils.h"

int main() {
    int opcao;
    
    criarDiretorioData();
    
    do {
        limparTela();
        desenharCabecalho("SISTEMA CONTABIL EMPRESARIAL");
        
        printf("\n");
        printf("  +----------------------------------------+\n");
        printf("  |  1. Cadastrar transacao                |\n");
        printf("  |  2. Listar todas as transacoes         |\n");
        printf("  |  3. Relatorios e analises              |\n");
        printf("  |  4. Dashboard resumido                 |\n");
        printf("  |  5. Exportar para CSV                  |\n");
        printf("  |  0. Sair                               |\n");
        printf("  +----------------------------------------+\n\n");
        
        printf("  Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1: cadastrarTransacao(); break;
            case 2: listarTransacoes(); break;
            case 3: menuRelatorios(); break;
            case 4: exibirDashboard(); break;
            case 5: exportarCSV(); break;
            case 0: 
                printf("\n  >> Encerrando sistema... Ate logo!\n");
                break;
            default: 
                printf("\n  >> ERRO: Opcao invalida!\n");
        }
        
        if (opcao != 0) pausar();
        
    } while(opcao != 0);
    
    return 0;
}