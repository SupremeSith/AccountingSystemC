#ifndef UTILS_H
#define UTILS_H




#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif



void limparTela();
void pausar();
void criarDiretorioData();
int validarData(char data[]);
void desenharLinha(int tamanho);
void desenharCabecalho(char *titulo);



#endif