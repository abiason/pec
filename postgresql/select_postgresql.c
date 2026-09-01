#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int main(void)
{
    PGconn *conexao;
    PGresult *resultado;
    int linhas;
    int colunas;

    conexao = PQconnectdb(
        "host=localhost "
        "port=5432 "
        "dbname=biblioteca "
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

    printf("Conexao realizada com sucesso!\n\n");

    resultado = PQexec(
        conexao,
        "SELECT * FROM public.tb_instituicao ORDER BY id_instituicao ASC;"
    );

    if (PQresultStatus(resultado) != PGRES_TUPLES_OK)
    {
        fprintf(stderr,
                "Erro ao executar SELECT:\n%s",
                PQerrorMessage(conexao));

        PQclear(resultado);
        PQfinish(conexao);

        return EXIT_FAILURE;
    }

    linhas = PQntuples(resultado);
    colunas = PQnfields(resultado);

    printf("Quantidade de registros: %d\n\n", linhas);

    int col_size[4] = {14, 30, 100, 50};

    for (int i = 0; i < colunas; i++)
    {
        char fmt[256] = "";
        snprintf(fmt, sizeof(fmt), "%%-%ds", col_size[i]);
        printf(fmt, PQfname(resultado, i));
    }

    printf("\n");

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            char fmt[256] = "";
            snprintf(fmt, sizeof(fmt), "%%-%ds", col_size[j]);
            printf(fmt, PQgetvalue(resultado, i, j));
        }

        printf("\n");
    }

    PQclear(resultado);
    PQfinish(conexao);

    return EXIT_SUCCESS;
}