#include <stdio.h>
#include <libpq-fe.h>

int main(void)
{
    printf("Versao da libpq: %d\n", PQlibVersion());

    return 0;
}