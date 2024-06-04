#include "ctype.h"
#include "stdbool.h"

// Função para verificar se uma string representa um número válido
bool verificarNumero(const char *str) {
    if (*str == '-' || *str == '+') str++; // Permitir sinal negativo ou positivo
    if (*str == '\0') return false; // Evitar strings vazias

    bool pontoDecimal = false;

    while (*str) {
        if (*str == '.') {
            if (pontoDecimal) return false; // Mais de um ponto decimal não é permitido
            pontoDecimal = true;
        } else if (!isdigit(*str)) {
            return false; // Se não for dígito, retorna falso
        }
        str++;
    }
    return true;
}