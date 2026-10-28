#include <stdio.h>

// Funcao recursiva que resolve a Torre de Hanoi
void torreHanoi(int discos, char origem, char auxiliar, char destino) {
    // Condicao de parada da recursividade
    if (discos == 1) {

        printf("Mover disco 1 de %c para %c\n",
               origem, destino);

        return;
    }

    // Passo 1:
    // Mover n-1 discos da origem para o auxiliar
    torreHanoi(discos - 1, origem, destino, auxiliar);

    // Passo 2:
    // Mover o maior disco da origem para o destino
    printf("Mover disco %d de %c para %c\n",
           discos, origem, destino);

    // Passo 3:
    // Mover n-1 discos do auxiliar para o destino
    torreHanoi(discos - 1, auxiliar, origem, destino);
}

int main() {
    int discos;

    printf("================================\n");
    printf("        TORRE DE HANOI          \n");
    printf("================================\n");

    printf("\nInforme a quantidade de discos: ");
    if (scanf("%d", &discos) != 1) {
        printf("\nEntrada invalida!\n");
        return 1;
    }

    if (discos < 1 || discos > 10) {
        printf("\nInforme entre 1 e 10 discos!\n");
        return 1;
    }

    printf("\nSequencia de movimentos:\n\n");

    torreHanoi(discos, 'A', 'B', 'C');

    printf("\nProblema resolvido!\n");

    return 0;
}