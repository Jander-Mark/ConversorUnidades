#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "conversor.h"
#include "utilidades.h"
#include "unidade.h"

/**
 * Funcao das conversoes do programa.
 * @param unidades
 * @param numUnidades
 * @param nomeUnidade
 * @return
 */

double obterMultiplicador(Unidade unidades[], int numUnidades, const char nomeUnidade[]) {
    for (int i = 0; i < numUnidades; i++) {
        if (strcmp(unidades[i].nome, nomeUnidade) == 0) {
            return unidades[i].multiplicador;
        }
    }
    return -1; // Retorna -1 se a unidade não for encontrada
}

/**
 * Validacao de entrado
 * @param valor
 * @param categoria
 * @return
 */

bool validarEntrada(double valor, char categoria[]) {
    if (strcmp(categoria, "temperatura") == 0) {
        return true;
    }
    return valor >= 0; // Retorna true se o valor for não negativo
}

/**
 * Verifica o numero se positivo ou negativo
 * @param str
 * @return
 */

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

/**
 * funcao de conversao
 * @param valor
 * @param multiplicadorEntrada
 * @param multiplicadorSaida
 * @return
 */

double converter(double valor, double multiplicadorEntrada, double multiplicadorSaida) {
    return valor * multiplicadorEntrada / multiplicadorSaida;
}

/**
 * Funcao especifica para as unidades de temperatura
 * @param valor
 * @param unidadeEntrada
 * @param unidadeSaida
 * @return
 */

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

/**
 * realiza a conversao da categoria selecionada
 * @param unidades
 * @param numUnidades
 * @param categoria
 */

void realizarConversao(Unidade unidades[], int numUnidades, const char categoria[]) {
    char unidadeEntrada[30], unidadeSaida[30];
    char valorStr[30];
    double valorOriginal, valorConvertido;
    double multiplicadorEntrada, multiplicadorSaida;

    while (true) {
        printf("Escolha a unidade de entrada:\n");
        for (int i = 0; i < numUnidades; i++) {
            printf("%d. %s\n", i + 1, unidades[i].nome);
        }
        int escolhaEntrada;
        fflush(stdin);
        scanf("%d", &escolhaEntrada);
        system("cls");
        limparBufferEntrada();

        if (escolhaEntrada < 1 || escolhaEntrada > numUnidades) {
            printf("\033[0;31m");
            printf("Escolha invalida.\n");
            printf("\033[0m");
            continue;
        }
        strcpy(unidadeEntrada, unidades[escolhaEntrada - 1].nome);
        multiplicadorEntrada = unidades[escolhaEntrada - 1].multiplicador;
        break;
    }

    while (true) {
        printf("Escolha a unidade de saida:\n");
        for (int i = 0; i < numUnidades; i++) {
            printf("%d. %s\n", i + 1, unidades[i].nome);
        }
        int escolhaSaida;
        fflush(stdin);
        scanf("%d", &escolhaSaida);
        system("cls");
        limparBufferEntrada();

        if (escolhaSaida < 1 || escolhaSaida > numUnidades) {
            printf("\033[0;31m");
            printf("Escolha invalida.\n");
            printf("\033[0m");
            continue;
        }
        strcpy(unidadeSaida, unidades[escolhaSaida - 1].nome);
        multiplicadorSaida = unidades[escolhaSaida - 1].multiplicador;
        break;
    }

    while (true) {
        printf("Digite o valor original: ");
        fflush(stdin);
        scanf("%s", valorStr);
        system("cls");
        limparBufferEntrada();

        if (!verificarNumero(valorStr)) {
            printf("\033[0;31m");
            printf("Valor invalido. Por favor, insira um numero valido.\n");
            printf("\033[0m");
            continue;
        }

        valorOriginal = atof(valorStr);

        if (!validarEntrada(valorOriginal, categoria)) {
            printf("\033[0;31m");
            printf("Valor invalido para a categoria %s. Por favor, insira um valor nao negativo.\n", categoria);
            printf("\033[0m");
            continue;
        }

        break;
    }

    if (strcmp(categoria, "temperatura") == 0) {
        valorConvertido = converterTemperatura(valorOriginal, unidadeEntrada, unidadeSaida);
    } else {
        valorConvertido = converter(valorOriginal, multiplicadorEntrada, multiplicadorSaida);
    }

    if (valorConvertido != -1) {
        printf("\033[0;32m");
        printf("Valor convertido: %.2f %s\n", valorConvertido, unidadeSaida);
        printf("\033[0m");

        FILE *file = fopen("dados_salvos.txt", "a");
        if (file != NULL) {
            fprintf(file, "Conversao de %s: %.2f %s -> %.2f %s\n", categoria, valorOriginal, unidadeEntrada, valorConvertido, unidadeSaida);
            fclose(file);
        } else {
            printf("Erro ao abrir o arquivo para salvar os dados.\n");
        }
    }

    // Perguntar ao usuário se deseja fazer outra conversão ou voltar ao menu principal
    while (true) {
        char escolha;
        printf("Deseja fazer outra conversao na mesma categoria? (s/n): ");
        fflush(stdin);
        scanf(" %c", &escolha);
        system("cls");
        limparBufferEntrada();
        if (escolha == 's' || escolha == 'S') {
            realizarConversao(unidades, numUnidades, categoria);
            return; // Retorna para evitar perguntar novamente
        } else if (escolha == 'n' || escolha == 'N') {
            break; // Sai do loop e volta ao menu principal
        } else {
            printf("\033[0;31m");
            printf("Entrada invalida. Por favor, digite 's' ou 'n'.\n");
            printf("\033[0m");
        }
    }
}

/**
 * Submenu das categorias principais
 * @param categoria
 */

void submenuConversor(const char categoria[]) {
    Unidade unidades[10];
    int numUnidades = 0;

    if (strcmp(categoria, "comprimento") == 0) {
        Unidade unidadesComprimento[] = {
                {"Metro", 1.0},
                {"Quilometro", 1000.0},
                {"Centimetro", 0.01},
                {"Milimetro", 0.001},
                {"Micrometro", 0.000001},
                {"Nanometro", 0.000000001},
                {"Milha", 1609.34},
                {"Jarda", 0.9144},
                {"Pe", 0.3048},
                {"Polegada", 0.0254}
        };
        memcpy(unidades, unidadesComprimento, sizeof(unidadesComprimento));
        numUnidades = sizeof(unidadesComprimento) / sizeof(Unidade);
    } else if (strcmp(categoria, "tempo") == 0) {
        Unidade unidadesTempo[] = {
                {"Segundo", 1.0},
                {"Minuto", 60.0},
                {"Hora", 3600.0},
                {"Dia", 86400.0},
                {"Semana", 604800.0},
                {"Mes", 2628000.0},
                {"Ano", 31536000.0}
        };
        memcpy(unidades, unidadesTempo, sizeof(unidadesTempo));
        numUnidades = sizeof(unidadesTempo) / sizeof(Unidade);
    } else if (strcmp(categoria, "peso") == 0) {
        Unidade unidadesPeso[] = {
                {"Quilograma", 1.0},
                {"Grama", 0.001},
                {"Miligrama", 0.000001},
                {"Libra", 0.453592},
                {"Onca", 0.0283495},
                {"Tonelada", 1000.0}
        };
        memcpy(unidades, unidadesPeso, sizeof(unidadesPeso));
        numUnidades = sizeof(unidadesPeso) / sizeof(Unidade);
    } else if (strcmp(categoria, "corrente") == 0) {
        Unidade unidadesCorrente[] = {
                {"Ampere", 1.0},
                {"Miliampere", 0.001},
                {"Microampere", 0.000001}
        };
        memcpy(unidades, unidadesCorrente, sizeof(unidadesCorrente));
        numUnidades = sizeof(unidadesCorrente) / sizeof(Unidade);
    } else if (strcmp(categoria, "temperatura") == 0) {
        Unidade unidadesTemperatura[] = {
                {"Celsius", 1.0},
                {"Fahrenheit", 1.0},
                {"Kelvin", 1.0}
        };
        memcpy(unidades, unidadesTemperatura, sizeof(unidadesTemperatura));
        numUnidades = sizeof(unidadesTemperatura) / sizeof(Unidade);
    } else if (strcmp(categoria, "substancia") == 0) {
        Unidade unidadesSubstancia[] = {
                {"Mol", 1.0},
                {"Milimol", 0.001},
                {"Micromol", 0.000001}
        };
        memcpy(unidades, unidadesSubstancia, sizeof(unidadesSubstancia));
        numUnidades = sizeof(unidadesSubstancia) / sizeof(Unidade);
    } else if (strcmp(categoria, "moeda") == 0) {
        Unidade unidadesMoeda[] = {
                {"Real", 1.0},      //Valor aproximado
                {"Dolar", 4.9},     //Valor aproximado
                {"Euro", 5.4},     //Valor aproximado
                {"Libra Esterlina", 6.2},   //Valor aproximado
                {"Iene", 0.036}             //Valor aproximado
        };
        memcpy(unidades, unidadesMoeda, sizeof(unidadesMoeda));
        numUnidades = sizeof(unidadesMoeda) / sizeof(Unidade);
    } else if (strcmp(categoria, "volume") == 0) {
        Unidade unidadesVolume[] = {
                {"Litro", 1.0},
                {"Mililitro", 0.001},
                {"Metro cubico", 1000.0},
                {"Centimetro cubico", 0.001},
                {"Milimetro cubico", 0.000001},
                {"Galao", 3.78541},
                {"Quarto", 0.946353},
                {"Pinta", 0.473176},
                {"Xicara", 0.24},
                {"Onca fluida", 0.0295735}
        };
        memcpy(unidades, unidadesVolume, sizeof(unidadesVolume));
        numUnidades = sizeof(unidadesVolume) / sizeof(Unidade);
    } else if (strcmp(categoria, "potencial") == 0) {
        Unidade unidadesPotencial[] = {
                {"Volt", 1.0},
                {"Milivolt", 0.001},
                {"Microvolt", 0.000001},
                {"Quilovolt", 1000.0}
        };
        memcpy(unidades, unidadesPotencial, sizeof(unidadesPotencial));
        numUnidades = sizeof(unidadesPotencial) / sizeof(Unidade);
    } else if (strcmp(categoria, "dados") == 0) {
        Unidade unidadesDados[] = {
                {"Bit", 1.0},
                {"Byte", 8.0},
                {"Kilobit", 1000.0},
                {"Kilobyte", 8000.0},
                {"Megabit", 1000000.0},
                {"Megabyte", 8000000.0},
                {"Gigabit", 1000000000.0},
                {"Gigabyte", 8000000000.0},
                {"Terabit", 1000000000000.0},
                {"Terabyte", 8000000000000.0}
        };
        memcpy(unidades, unidadesDados, sizeof(unidadesDados));
        numUnidades = sizeof(unidadesDados) / sizeof(Unidade);
    } else {
        printf("\033[0;31m");
        printf("Categoria invalida.\n");
        printf("\033[0m");
        return;
    }

    realizarConversao(unidades, numUnidades, categoria);
}
