#include <stdio.h>
#include <stdlib.h>

#include "util.h"

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void aguardar_enter() {
    int c;

    printf("\nPressione ENTER para continuar...");

    while ((c = getchar()) != '\n' && c != EOF) {
        // Descarta caracteres pendentes
    }

    getchar();
}