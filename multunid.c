#include "string.h"
#include "unid.h"

double obterMultiplicador(Unidade unidades[], int numUnidades, const char nomeUnidade[]) {
    for (int i = 0; i < numUnidades; i++) {
        if (strcmp(unidades[i].nome, nomeUnidade) == 0) {
            return unidades[i].multiplicador;
        }
    }
    return -1; // Retorna -1 se a unidade não for encontrada
}