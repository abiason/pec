#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main()
{
    PGconn *conexao;
    PGresult *resultado;

    const char *id_instituicao = "2";

    const char *parametros[1] = {
        id_instituicao
    };

    conexao = PQconnectdb(
        "host=localhost "
        "port=5432 "
        "dbname=biblioteca "
        "user=postgres "
        "password=123456"
    );

    if (PQstatus(conexao) != CONNECTION_OK)
    {
        fprintf(stderr, "Erro na conexao:\n%s",
                PQerrorMessage(conexao));

        PQfinish(conexao);
        return EXIT_FAILURE;
    }

    resultado = PQexecParams(
        conexao,
        "DELETE FROM public.tb_instituicao WHERE id_instituicao = $1;",
        1,
        NULL,
        parametros,
        NULL,
        NULL,
        0
    );

    if (PQresultStatus(resultado) != PGRES_COMMAND_OK)
    {
        fprintf(stderr,
                "Erro no DELETE:\n%s",
                PQerrorMessage(conexao));

        PQclear(resultado);
        PQfinish(conexao);

        return EXIT_FAILURE;
    }

    printf("Instituição excluída com sucesso!\n");

    PQclear(resultado);
    PQfinish(conexao);

    return EXIT_SUCCESS;
}