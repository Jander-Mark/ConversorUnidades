// Estrutura de dados para armazenar informações sobre diferentes unidades e seus valores de conversão
typedef struct
{
    char nome[30];
    double multiplicador; // fator de multiplicação para conversão para a unidade base
} Unidade;