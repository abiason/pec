#include <stdio.h>

#include "util.h"
#include "operacao.h"

void adicao(float pvalor1, float pvalor2) {
    printf("A Adicao dos Valores %.2f e %.2f eh %.2f.\n", pvalor1, pvalor2, (pvalor1 + pvalor2));
    aguardar_enter();
}