#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "conversor.h"
#include "utilidades.h"

/**
 * Funcao principal do programa, onde temos o menu principal e o submenu.
 * @return
 */

int main() {
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        // Menu principal
        printf("Menu Principal\n");
        printf("1. Conversor de Medidas\n");
        printf("2. Historico de Conversoes\n");
        printf("3. Sair\n");
        printf("Digite a sua escolha: ");
        int escolha;
        scanf("%d", &escolha);
        system("cls");

        if (escolha == 1) {
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

            switch (subEscolha) {
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
        } else if (escolha == 2) {
            visualizarDadosSalvos();
        } else if (escolha == 3) {
            printf("Saindo...\n");
            break;
        } else {
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
