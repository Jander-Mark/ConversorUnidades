#include "string.h"
#include "stdbool.h"

// Função para validar a entrada do usuário
bool validarEntrada(double valor, char categoria[]) {
    // Permite valores negativos apenas para a categoria de temperatura
    if (strcmp(categoria, "temperatura") == 0) {
        return true;
    }
    return valor >= 0; // Retorna true se o valor for não negativo
}