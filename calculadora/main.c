#include <stdio.h>
#include <ctype.h>

#include "util.h"
#include "operacao.h"

void exibir_menu();
void solicitar_valores(float *pvalor1, float *pvalor2);

int main() {
    float valor1, valor2;
    char opcao;

    do {
        exibir_menu();

        printf("Informe uma opcao: ");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        if (opcao == '1' || opcao == '2' || opcao == '3' || opcao == '4') {
            solicitar_valores(&valor1, &valor2);
        }

        switch(opcao) {
            case '1':
                adicao(valor1, valor2);
                break;
            case 'S': 
                printf("\nSaindo do programa...");
                break;
            default: 
                printf("Opcao invalida!\n");
                aguardar_enter();
        }
    } while (opcao != 'S');

    return 0;
}

void exibir_menu() {
    limpar_tela();

    printf("::: Calculadora - Menu :::\n");
    printf("==========================\n\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao\n\n");
    printf("S - Sair\n\n");
}

void solicitar_valores(float *pvalor1, float *pvalor2) {
    printf("\nInformando os valores de entrada:\n");

    printf("- o primeiro valor: ");
    scanf("%f", pvalor1);

    printf("- o segundo valor.: ");
    scanf("%f", pvalor2);
    
    printf("\n");
}