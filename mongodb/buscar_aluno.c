#include <stdio.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

int main()
{
    mongoc_client_t *cliente;
    mongoc_collection_t *colecao;
    mongoc_cursor_t *cursor;

    bson_t *filtro;
    const bson_t *documento;

    bson_iter_t campo;
    bson_error_t erro;

    int ra;

    mongoc_init();

    cliente = mongoc_client_new("mongodb://localhost:27017");

    if (cliente == NULL)
    {
        printf("Erro ao criar o cliente MongoDB.\n");
        mongoc_cleanup();
        return 1;
    }

    colecao = mongoc_client_get_collection(
        cliente,
        "faculdade",
        "alunos"
    );

    /* Solicita o RA */
    printf("Digite o RA do aluno: ");
    scanf("%d", &ra);

    /* Cria o filtro { "ra": valor } */
    filtro = bson_new();

    BSON_APPEND_INT32(
        filtro,
        "ra",
        ra
    );

    /* Executa a consulta */
    cursor = mongoc_collection_find_with_opts(
        colecao,
        filtro,
        NULL,
        NULL
    );

    printf("\nRESULTADO DA BUSCA\n");
    printf("================================\n");

    int encontrado = 0;

    while (mongoc_cursor_next(cursor, &documento))
    {
        encontrado = 1;

        if (bson_iter_init_find(&campo, documento, "ra"))
        {
            printf("RA:       %d\n",
                   bson_iter_int32(&campo));
        }

        if (bson_iter_init_find(&campo, documento, "nome"))
        {
            printf("Nome:     %s\n",
                   bson_iter_utf8(&campo, NULL));
        }

        if (bson_iter_init_find(&campo, documento, "curso"))
        {
            printf("Curso:    %s\n",
                   bson_iter_utf8(&campo, NULL));
        }

        if (bson_iter_init_find(&campo, documento, "semestre"))
        {
            printf("Semestre: %d\n",
                   bson_iter_int32(&campo));
        }

        printf("--------------------------------\n");
    }

    if (!encontrado)
    {
        printf("Aluno nao encontrado.\n");
    }

    if (mongoc_cursor_error(cursor, &erro))
    {
        printf("Erro na consulta: %s\n", erro.message);
    }

    bson_destroy(filtro);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(colecao);
    mongoc_client_destroy(cliente);

    mongoc_cleanup();

    return 0;
}