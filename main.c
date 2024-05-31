#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "unidade.h"
#include <ctype.h>
#include <math.h>

// Definição da função limparBufferEntrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para obter o valor de conversão apropriado com base no nome da unidade
double obterMultiplicador(Unidade unidades[], int numUnidades, const char nomeUnidade[]) {
    for (int i = 0; i < numUnidades; i++) {
        if (strcmp(unidades[i].nome, nomeUnidade) == 0) {
            return unidades[i].multiplicador;
        }
    }
    return -1; // Retorna -1 se a unidade não for encontrada
}

// Função para validar a entrada do usuário
bool validarEntrada(double valor, char categoria[])
{
    // Permite valores negativos apenas para a categoria de temperatura
    if (strcmp(categoria, "temperatura") == 0) {
        return true;
    }
    return valor >= 0; // Retorna true se o valor for não negativo
}

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

// Função para exibir os dados salvos em um arquivo
void visualizarDadosSalvos()
{
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("conversoes_salvas.txt", "r");
    if (arquivo == NULL)
    {
        printf("Nenhuma conversao foi salva ainda.\n");
        return;
    }
    printf("Dados salvos das conversoes:\n");
    while (fgets(linha, 100, arquivo) != NULL)
    {
        printf("%s", linha);
    }
    fclose(arquivo);
}

// Função para converter entre unidades
double converter(double valor, double multiplicadorEntrada, double multiplicadorSaida)
{
    return valor * multiplicadorEntrada / multiplicadorSaida;
}

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

// Função para realizar a conversão de acordo com a categoria escolhida
void realizarConversao(Unidade unidades[], int numUnidades, const char categoria[]) {
    char unidadeEntrada[30], unidadeSaida[30];
    char valorStr[30];
    double valorOriginal, valorConvertido;
    double multiplicadorEntrada, multiplicadorSaida;

    printf("Escolha a unidade de entrada:\n");
    for (int i = 0; i < numUnidades; i++) {
        printf("%d. %s\n", i + 1, unidades[i].nome);
    }
    int escolhaEntrada;
    scanf("%d", &escolhaEntrada);
    system("cls");
    limparBufferEntrada();

    if (escolhaEntrada < 1 || escolhaEntrada > numUnidades) {
        printf("\033[0;31m");
        printf("Escolha invalida.\n");
        printf("\033[0m");
        return;
    }
    strcpy(unidadeEntrada, unidades[escolhaEntrada - 1].nome);
    multiplicadorEntrada = unidades[escolhaEntrada - 1].multiplicador;

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
        return;
    }
    strcpy(unidadeSaida, unidades[escolhaSaida - 1].nome);
    multiplicadorSaida = unidades[escolhaSaida - 1].multiplicador;

    while (true) {
        printf("Digite o valor original: ");
        fflush(stdin);
        scanf("%s", valorStr);
        system("cls");
        limparBufferEntrada();

        if (!verificarNumero(valorStr)) {
            printf("\033[0;31m");
            printf("Valor invalido. Por favor, insira um valor numerico.\n");
            printf("\033[0m");
            continue; // Repete o loop até o usuário inserir um valor válido
        }

        valorOriginal = atof(valorStr);

        if (!validarEntrada(valorOriginal, categoria)) {
            printf("\033[0;31m");
            printf("Valor invalido para a categoria %s. Deseja voltar ao menu principal? (s/n): ", categoria);
            printf("\033[0m");
            char voltarMenu;
            fflush(stdin);
            scanf(" %c", &voltarMenu);
            system("cls");
            limparBufferEntrada();
            if (voltarMenu == 's' || voltarMenu == 'S') {
                return;
            } else {
                exit(1);
            }
        }
        break; // Sai do loop se o valor for válido
    }

    if (strcmp(categoria, "temperatura") == 0) {
        valorConvertido = converterTemperatura(valorOriginal, unidadeEntrada, unidadeSaida);
    } else {
        valorConvertido = converter(valorOriginal, multiplicadorEntrada, multiplicadorSaida);
    }
    printf("Valor convertido: %.6f %s\n", valorConvertido, unidadeSaida);

    FILE *arquivo = fopen("conversoes_salvas.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s: %.6f %s -> %.6f %s\n", unidadeEntrada, valorOriginal, unidadeEntrada, valorConvertido, unidadeSaida);
        fclose(arquivo);
    }
}

// Submenu de conversões por categoria
void submenuConversor(char categoria[])
{
    Unidade unidadesComprimento[] = {
            {"Metro", 1.0},
            {"Centimetro", 0.01},
            {"Milimetro", 0.001},
            {"Quilometro", 1000.0},
            {"Polegada", 0.0254},
            {"Milha", 1609.34},
            {"Pe", 0.3048}};
    int numUnidadesComprimento = sizeof(unidadesComprimento) / sizeof(Unidade);

    Unidade unidadesTempo[] = {
            {"Minuto", 60.0},
            {"Hora", 3600.0},
            {"Dia", 86400.0},
            {"Ano", 31536000.0}};
    int numUnidadesTempo = sizeof(unidadesTempo) / sizeof(Unidade);

    Unidade unidadesPeso[] = {
            {"Quilograma", 1.0},
            {"Grama", 0.001},
            {"Miligrama", 0.000001},
            {"Micrograma", 0.000000001},
            {"Tonelada", 1000.0}};
    int numUnidadesPeso = sizeof(unidadesPeso) / sizeof(Unidade);

    Unidade unidadesCorrente[] = {
            {"Ampere", 1.0},
            {"Miliampere", 0.001},
            {"Microampere", 0.000001},
            {"Nanoampere", 0.000000001},
            {"Picoampere", 0.000000000001}};
    int numUnidadesCorrente = sizeof(unidadesCorrente) / sizeof(Unidade);

    Unidade unidadesTemperatura[] = {
            {"Kelvin", 1.0},
            {"Celsius", 1.8},   // Converter com fórmula
            {"Fahrenheit", 1.0} // Converter com fórmula
    };
    int numUnidadesTemperatura = sizeof(unidadesTemperatura) / sizeof(Unidade);

    Unidade unidadesSubstancia[] = {
            {"Mol", 1.0},
            {"Milimol", 0.001},
            {"Micromol", 0.000001},
            {"Nanomol", 0.000000001},
            {"Picomol", 0.000000000001}};
    int numUnidadesSubstancia = sizeof(unidadesSubstancia) / sizeof(Unidade);

    Unidade unidadesMoeda[] = {
            {"USD", 1.0},
            {"EUR", 1.15},        // Valor aproximado
            {"GBP", 1.25},        // Valor aproximado
            {"JPY", 0.00909091},  // Valor aproximado
            {"BRL", 0.1851851851} // Valor aproximado
    };
    int numUnidadesMoeda = sizeof(unidadesMoeda) / sizeof(Unidade);

    Unidade unidadesVolume[] = {
            {"Litro", 1.0},
            {"Decalitro", 10.0},
            {"Hectolitro", 100.0},
            {"Quilolitro", 1000.0},
            {"Galao", 3.78541}};
    int numUnidadesVolume = sizeof(unidadesVolume) / sizeof(Unidade);

    Unidade unidadesPotencial[] = {
            {"Volt", 1.0},
            {"Milivolt", 0.001},
            {"Microvolt", 0.000001},
            {"Nanovolt", 0.000000001},
            {"Picovolt", 0.000000000001}};
    int numUnidadesPotencial = sizeof(unidadesPotencial) / sizeof(Unidade);

    Unidade unidadesDados[] = {
            {"Bit", 1.0},
            {"Byte", 8.0},
            {"Kilobyte", 8192.0},
            {"Megabyte", 8388608.0},
            {"Gigabyte", 8589934592.0},
            {"Terabyte", 8796093022208.0}};
    int numUnidadesDados = sizeof(unidadesDados) / sizeof(Unidade);

    if (strcmp(categoria, "comprimento") == 0) {
        realizarConversao(unidadesComprimento, numUnidadesComprimento, "comprimento");
    } else if (strcmp(categoria, "tempo") == 0) {
        realizarConversao(unidadesTempo, numUnidadesTempo, "tempo");
    } else if (strcmp(categoria, "peso") == 0) {
        realizarConversao(unidadesPeso, numUnidadesPeso, "peso");
    } else if (strcmp(categoria, "corrente") == 0) {
        realizarConversao(unidadesCorrente, numUnidadesCorrente, "corrente");
    } else if (strcmp(categoria, "temperatura") == 0) {
        realizarConversao(unidadesTemperatura, numUnidadesTemperatura, "temperatura");
    } else if (strcmp(categoria, "substancia") == 0) {
        realizarConversao(unidadesSubstancia, numUnidadesSubstancia, "substancia");
    } else if (strcmp(categoria, "moeda") == 0) {
        realizarConversao(unidadesMoeda, numUnidadesMoeda, "moeda");
    } else if (strcmp(categoria, "volume") == 0) {
        realizarConversao(unidadesVolume, numUnidadesVolume, "volume");
    } else if (strcmp(categoria, "potencial") == 0) {
        realizarConversao(unidadesPotencial, numUnidadesPotencial, "potencial");
    } else if (strcmp(categoria, "dados") == 0) {
        realizarConversao(unidadesDados, numUnidadesDados, "dados");
    } else {
        printf("\033[0;31m");
        printf("Categoria invalida.\n");
        printf("\033[0m");
    }
}

int main()
{
    char continuar = 's';
    while (continuar == 's' || continuar == 'S')
    {
        // Menu principal
        printf("Menu Principal\n");
        printf("1. Conversor de Medidas\n");
        printf("2. Historico de Conversoes\n");
        printf("3. Sair\n");
        printf("Digite a sua escolha: ");
        int escolha;
        scanf("%d", &escolha);
        system("cls");


        if (escolha == 1)
        {
            // Submenu do conversor de medidas
            printf("Conversor de Medidas\n");
            printf("1. Comprimento\n");
            printf("2. Tempo\n");
            printf("3. Peso\n");
            printf("4. Corrente Eletrica\n");
            printf("5. Temperatura\n");
            printf("6. Substancia no Sistema\n");
            printf("7. Moeda\n");
            printf("8. Volume\n");
            printf("9. Potencial Eletrico\n");
            printf("10. Dados\n");
            printf("Digite a sua escolha: ");
            int subEscolha;
            scanf("%d", &subEscolha);
            system("cls");


            switch (subEscolha)
            {
                case 1:
                    submenuConversor("comprimento");
                    break;
                case 2:
                    submenuConversor("tempo");
                    break;
                case 3:
                    submenuConversor("peso");
                    break;
                case 4:
                    submenuConversor("corrente");
                    break;
                case 5:
                    submenuConversor("temperatura");
                    break;
                case 6:
                    submenuConversor("substancia");
                    break;
                case 7:
                    submenuConversor("moeda");
                    break;
                case 8:
                    submenuConversor("volume");
                    break;
                case 9:
                    submenuConversor("potencial");
                    break;
                case 10:
                    submenuConversor("dados");
                    break;
                default:
                    printf("\033[0;31m");
                    printf("Escolha invalida.\n");
                    printf("\033[0m");
                    break;
            }
        }
        else if (escolha == 2)
        {
            visualizarDadosSalvos();
        }
        else if (escolha == 3)
        {
            printf("Saindo...\n");
            break;
        }
        else
        {
            printf("\033[0;31m");
            printf("Escolha invalida.\n");
            printf("\033[0m");
        }
// Loop para garantir entrada válida para continuar
        while (true) {
            printf("Deseja voltar ao menu principal? (s/n): ");
            fflush(stdin);
            scanf(" %c", &continuar);
            system("cls");
            limparBufferEntrada();
            if (continuar == 's' || continuar == 'S' || continuar == 'n' || continuar == 'N') {
                break; // Saia do loop se a entrada for válida
            } else {
                printf("\033[0;31m");
                printf("Entrada invalida. Por favor, digite 's' ou 'n'.\n");
                printf("\033[0m");
            }
        }
    }
    getchar();
    return 0;
    }
