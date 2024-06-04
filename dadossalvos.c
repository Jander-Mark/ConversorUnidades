#include "stdio.h"

// Função para exibir os dados salvos em um arquivo
void visualizarDadosSalvos() {
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("conversoes_salvas.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhuma conversao foi salva ainda.\n");
        return;
    }
    printf("Dados salvos das conversoes:\n");
    while (fgets(linha, 100, arquivo) != NULL) {
        printf("%s", linha);
    }
    fclose(arquivo);
}