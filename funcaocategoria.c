#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "stdbool.h"
#include "salvarconv.c"
#include "convunit.c"
#include "validarentrada.c"
#include "verifstring.c"
#include "unidades.c"


void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função para realizar a conversão de acordo com a categoria
void realizarConversao(char categoria[])
{
    Unidade *unidades = obterUnidades(categoria);
    if (unidades == NULL)
    {
        return;
    }

    int numUnidades = sizeof(unidades);
    char unidadeEntrada[30], unidadeSaida[30];
    char valorStr[30];
    double valorOriginal, valorConvertido;
    double multiplicadorEntrada, multiplicadorSaida;

    printf("Escolha a unidade de entrada:\n");
    for (int i = 0; i < numUnidades; i++)
    {
        printf("%d. %s\n", i + 1, unidades[i].nome);
    }
    int escolhaEntrada;
    scanf("%d", &escolhaEntrada);
    system("cls");
    limparBufferEntrada();

    if (escolhaEntrada < 1 || escolhaEntrada > numUnidades)
    {
        printf("\033[0;31m");
        printf("Escolha invalida.\n");
        printf("\033[0m");
        return;
    }
    strcpy(unidadeEntrada, unidades[escolhaEntrada - 1].nome);
    multiplicadorEntrada = unidades[escolhaEntrada - 1].multiplicador;

    printf("Escolha a unidade de saida:\n");
    for (int i = 0; i < numUnidades; i++)
    {
        printf("%d. %s\n", i + 1, unidades[i].nome);
    }
    int escolhaSaida;
    fflush(stdin);
    scanf("%d", &escolhaSaida);
    system("cls");
    limparBufferEntrada();

    if (escolhaSaida < 1 || escolhaSaida > numUnidades)
    {
        printf("\033[0;31m");
        printf("Escolha invalida.\n");
        printf("\033[0m");
        return;
    }
    strcpy(unidadeSaida, unidades[escolhaSaida - 1].nome);
    multiplicadorSaida = unidades[escolhaSaida - 1].multiplicador;

    while (true)
    {
        printf("Digite o valor original: ");
        fflush(stdin);
        scanf("%s", valorStr);
        system("cls");
        limparBufferEntrada();

        if (!verificarNumero(valorStr))
        {
            printf("\033[0;31m");
            printf("Valor invalido. Por favor, insira um valor numerico.\n");
            printf("\033[0m");
            continue; // Repete o loop até o usuário inserir um valor válido
        }

        valorOriginal = atof(valorStr);

        if (!validarEntrada(valorOriginal, categoria))
        {
            printf("\033[0;31m");
            printf("Valor invalido para a categoria %s. Deseja voltar ao menu principal? (s/n): ", categoria);
            printf("\033[0m");
            char resposta;
            scanf("%c", &resposta);
            system("cls");
            limparBufferEntrada();

            if (tolower(resposta) == 's')
            {
                return; // Retorna ao menu principal
            }
            else
            {
                break; // Sai do loop while se o usuário não quiser voltar ao menu
            }
        }

        valorConvertido = converter(valorOriginal, multiplicadorEntrada, multiplicadorSaida);
        if (valorConvertido == -1)
        {
            return; // Erro de conversão
        }

        printf("Valor original: %s %s\n", valorStr, unidadeEntrada);
        printf("Valor convertido: %.2f %s\n", valorConvertido, unidadeSaida);

        salvarConversao(categoria, unidadeEntrada, valorOriginal, unidadeSaida, valorConvertido);

        printf("\033[0;32m");
        printf("Conversao realizada com sucesso!\n");
        printf("\033[0m");

        printf("Deseja realizar outra conversao? (s/n): ");
        char respostaMenu;
        scanf("%c", &respostaMenu);
        system("cls");
        limparBufferEntrada();

        if (tolower(respostaMenu) == 'n')
        {
            return;
        }
    }
}