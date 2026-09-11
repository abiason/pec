#include <stdio.h>
#include <libpq-fe.h>

int main()
{
    printf("Versao da libpq: %d\n", PQlibVersion());

    return 0;
}