#ifndef UTILS_H
#define UTILS_H

// Define comando de limpeza de tela conforme o sistema operacional
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Declaração de funções utilitárias do sistema
void limparTela();                  // Limpa o terminal
void pausar();                      // Pausa até o usuário pressionar ENTER
void criarDiretorioData();          // Cria o diretório "data" se não existir
int validarData(char data[]);       // Valida formato de data (DD/MM/AAAA)
void desenharLinha(int tamanho);    // Desenha linha horizontal de tamanho definido
void desenharCabecalho(char *titulo); // Exibe cabeçalho centralizado com bordas

#endif
