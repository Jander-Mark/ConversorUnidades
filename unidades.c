#include "unid.h"
#include "string.h"
#include "stdio.h"

Unidade unidadesComprimento[] = {
    {"Metro", 1.0},
    {"Centimetro", 0.01},
    {"Milimetro", 0.001},
    {"Quilometro", 1000.0},
    {"Polegada", 0.0254},
    {"Milha", 1609.34},
    {"Pe", 0.3048}};

Unidade unidadesTempo[] = {
    {"Minuto", 60.0},
    {"Hora", 3600.0},
    {"Dia", 86400.0},
    {"Ano", 31536000.0}};

Unidade unidadesPeso[] = {
    {"Quilograma", 1.0},
    {"Grama", 0.001},
    {"Miligrama", 0.000001},
    {"Micrograma", 0.000000001},
    {"Tonelada", 1000.0}};

Unidade unidadesCorrente[] = {
    {"Ampere", 1.0},
    {"Miliampere", 0.001},
    {"Microampere", 0.000001},
    {"Nanoampere", 0.000000001},
    {"Picoampere", 0.000000000001}};

Unidade unidadesTemperatura[] = {
    {"Kelvin", 1.0},
    {"Celsius", 1.8},
    {"Fahrenheit", 1.0}};

Unidade unidadesSubstancia[] = {
    {"Mol", 1.0},
    {"Milimol", 0.001},
    {"Micromol", 0.000001},
    {"Nanomol", 0.000000001},
    {"Picomol", 0.000000000001}};

Unidade unidadesMoeda[] = {
    {"USD", 1.0},
    {"EUR", 1.15},
    {"GBP", 1.25},
    {"JPY", 0.00909091},
    {"BRL", 0.1851851851}};

Unidade unidadesVolume[] = {
    {"Litro", 1.0},
    {"Decalitro", 10.0},
    {"Hectolitro", 100.0},
    {"Quilolitro", 1000.0},
    {"Galao", 3.78541}};

Unidade unidadesPotencial[] = {
    {"Volt", 1.0},
    {"Milivolt", 0.001},
    {"Microvolt", 0.000001},
    {"Nanovolt", 0.000000001},
    {"Picovolt", 0.000000000001}};

Unidade unidadesDados[] = {
    {"Bit", 1.0},
    {"Byte", 8.0},
    {"Kilobyte", 8192.0},
    {"Megabyte", 8388608.0},
    {"Gigabyte", 8589934592.0},
    {"Terabyte", 8796093022208.0}};

// Função para obter a lista de unidades de acordo com a categoria
Unidade *obterUnidades(char categoria[])
{
    if (strcmp(categoria, "comprimento") == 0)
    {
        return unidadesComprimento;
    }
    else if (strcmp(categoria, "tempo") == 0)
    {
        return unidadesTempo;
    }
    else if (strcmp(categoria, "peso") == 0)
    {
        return unidadesPeso;
    }
    else if (strcmp(categoria, "corrente") == 0)
    {
        return unidadesCorrente;
    }
    else if (strcmp(categoria, "temperatura") == 0)
    {
        return unidadesTemperatura;
    }
    else if (strcmp(categoria, "substancia") == 0)
    {
        return unidadesSubstancia;
    }
    else if (strcmp(categoria, "moeda") == 0)
    {
        return unidadesMoeda;
    }
    else if (strcmp(categoria, "volume") == 0)
    {
        return unidadesVolume;
    }
    else if (strcmp(categoria, "potencial") == 0)
    {
        return unidadesPotencial;
    }
    else if (strcmp(categoria, "dados") == 0)
    {
        return unidadesDados;
    }
    else
    {
        printf("\033[0;31m");
        printf("Categoria invalida.\n");
        printf("\033[0m");
        return NULL;
    }
}