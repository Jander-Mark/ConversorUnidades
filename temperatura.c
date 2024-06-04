#include "string.h"
#include "stdio.h"

// Função para converter entre unidades de temperatura
double converterTemperatura(double valor, const char unidadeEntrada[], const char unidadeSaida[]) {
    if (strcmp(unidadeEntrada, "Celsius") == 0 && strcmp(unidadeSaida, "Fahrenheit") == 0) {
        return valor * 9.0 / 5.0 + 32.0;
    } else if (strcmp(unidadeEntrada, "Fahrenheit") == 0 && strcmp(unidadeSaida, "Celsius") == 0) {
        return (valor - 32.0) * 5.0 / 9.0;
    } else if (strcmp(unidadeEntrada, "Celsius") == 0 && strcmp(unidadeSaida, "Kelvin") == 0) {
        return valor + 273.15;
    } else if (strcmp(unidadeEntrada, "Kelvin") == 0 && strcmp(unidadeSaida, "Celsius") == 0) {
        return valor - 273.15;
    } else if (strcmp(unidadeEntrada, "Kelvin") == 0 && strcmp(unidadeSaida, "Fahrenheit") == 0) {
        return (valor - 273.15) * 9.0 / 5.0 + 32.0;
    } else if (strcmp(unidadeEntrada, "Fahrenheit") == 0 && strcmp(unidadeSaida, "Kelvin") == 0) {
        return (valor - 32.0) * 5.0 / 9.0 + 273.15;
    } else {
        printf("\033[0;31m");
        printf("Erro: unidades de entrada ou saida invalidas.\n");
        printf("\033[0m");
        return -1;
    }
}