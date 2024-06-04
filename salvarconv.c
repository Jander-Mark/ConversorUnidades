#include "stdio.h"

// Função para salvar a conversão em um arquivo
void salvarConversao(char categoria[], char unidadeEntrada[], double valorOriginal, char unidadeSaida[], double valorConvertido)
{
    FILE *arquivo;
    arquivo = fopen("conversoes_salvas.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao salvar conversao.\n");
        return;
    }
    fprintf(arquivo, "%s: %s %.2f %s -> %.2f\n", categoria, unidadeEntrada, valorOriginal, unidadeSaida, valorConvertido);
    fclose(arquivo);
}