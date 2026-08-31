#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main(void)
{
    PGconn *conexao;

    conexao = PQconnectdb(
        "host=localhost "
        "port=5432 "
        "dbname=postgres "
        "user=postgres "
        "password=123456"
    );

    if (PQstatus(conexao) != CONNECTION_OK)
    {
        fprintf(stderr,
                "Erro ao conectar ao PostgreSQL:\n%s",
                PQerrorMessage(conexao));

        PQfinish(conexao);

        return EXIT_FAILURE;
    }

    printf("Conexao com o PostgreSQL realizada com sucesso!\n");

    PQfinish(conexao);

    return EXIT_SUCCESS;
}