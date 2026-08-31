#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main(void)
{
    PGconn *conexao;
    PGresult *resultado;

    const char *id_instituicao = "2";
    const char *codigo = "FEMA_IMESA";
    const char *nome = "FEMA - Instituto Municipal de Ensino Superior de Assis";
    const char *campus = "ASSIS";

    const char *parametros[4] = {
        id_instituicao,
        codigo,
        nome,
        campus
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
        "INSERT INTO public.tb_instituicao (id_instituicao, codigo, nome, campus) VALUES ($1, $2, $3, $4);",
        4,
        NULL,
        parametros,
        NULL,
        NULL,
        0
    );

    if (PQresultStatus(resultado) != PGRES_COMMAND_OK)
    {
        fprintf(stderr,
                "Erro no INSERT:\n%s",
                PQerrorMessage(conexao));

        PQclear(resultado);
        PQfinish(conexao);

        return EXIT_FAILURE;
    }

    printf("Instituição inserida com sucesso!\n");

    PQclear(resultado);
    PQfinish(conexao);

    return EXIT_SUCCESS;
}