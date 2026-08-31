#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main(void)
{
    PGconn *conexao;
    PGresult *resultado;

    const char *id_instituicao = "2";
    const char *nome = "FEMA - INSTITUTO MUNICIPAL DE ENSINO SUPERIOR DE ASSIS";

    const char *parametros[2] = {
        nome,
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
        "UPDATE public.tb_instituicao SET nome = $1 WHERE id_instituicao = $2;",
        2,
        NULL,
        parametros,
        NULL,
        NULL,
        0
    );

    if (PQresultStatus(resultado) != PGRES_COMMAND_OK)
    {
        fprintf(stderr,
                "Erro no UPDATE:\n%s",
                PQerrorMessage(conexao));

        PQclear(resultado);
        PQfinish(conexao);

        return EXIT_FAILURE;
    }

    printf("Instituição atualizada com sucesso!\n");

    PQclear(resultado);
    PQfinish(conexao);

    return EXIT_SUCCESS;
}