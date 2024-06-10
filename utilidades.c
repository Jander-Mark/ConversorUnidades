#include <stdio.h>
#include "utilidades.h"

/**
 * Utilidades do programa
 * Limpar Buffle e Salvar/visualizar dados.
 */

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * Funcao para visualizacao dos dados salvos e para salvar
 */

void visualizarDadosSalvos() {
    FILE *file = fopen("dados_salvos.txt", "r");
    if (file != NULL) {
        char linha[100];
        while (fgets(linha, sizeof(linha), file) != NULL) {
            printf("%s", linha);
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de dados salvos.\n");
    }
}
