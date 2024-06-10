#ifndef CONVERSOR_H
#define CONVERSOR_H

/**
 * Prototipo da funcao das coversoes do programa
 */

#include <stdbool.h>
#include "unidade.h"

void submenuConversor(const char categoria[]);
void realizarConversao(Unidade unidades[], int numUnidades, const char categoria[]);
double converter(double valor, double multiplicadorEntrada, double multiplicadorSaida);
double converterTemperatura(double valor, const char unidadeEntrada[], const char unidadeSaida[]);
double obterMultiplicador(Unidade unidades[], int numUnidades, const char nomeUnidade[]);
bool validarEntrada(double valor, char categoria[]);
bool verificarNumero(const char *str);

#endif