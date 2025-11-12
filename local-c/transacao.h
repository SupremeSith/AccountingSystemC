#ifndef TRANSACAO_H
#define TRANSACAO_H

// Estrutura que representa uma transação financeira
typedef struct {
    int id;              // Identificador único da transação
    char tipo[20];       // Tipo da transação (Receita ou Despesa)
    char categoria[50];  // Categoria associada (ex: Salário, Aluguel)
    float valor;         // Valor monetário da transação
    char data[11];       // Data no formato DD/MM/AAAA
} Transacao;

// Declaração das funções relacionadas às transações
void cadastrarTransacao();   // Cadastra uma nova transação
void listarTransacoes();     // Lista todas as transações registradas
int obterProximoID();        // Retorna o próximo ID disponível

#endif
