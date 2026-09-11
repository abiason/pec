#include <stdio.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

int main()
{
    mongoc_client_t *cliente;
    mongoc_collection_t *colecao;
    mongoc_cursor_t *cursor;

    bson_t *filtro;
    bson_t resposta;

    const bson_t *documento;

    bson_iter_t campo;
    bson_error_t erro;

    int ra;
    int encontrado = 0;

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

    printf("Digite o RA do aluno: ");
    scanf("%d", &ra);

    /* Cria o filtro { "ra": valor } */
    filtro = bson_new();

    BSON_APPEND_INT32(
        filtro,
        "ra",
        ra
    );

    /* Busca o aluno antes de excluir */
    cursor = mongoc_collection_find_with_opts(
        colecao,
        filtro,
        NULL,
        NULL
    );

    if (mongoc_cursor_next(cursor, &documento))
    {
        encontrado = 1;

        printf("\nAluno encontrado:\n");
        printf("-----------------------------\n");

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

        printf("-----------------------------\n");
    }

    /* Verifica erro na consulta */
    if (mongoc_cursor_error(cursor, &erro))
    {
        printf("Erro na consulta: %s\n", erro.message);

        mongoc_cursor_destroy(cursor);
        bson_destroy(filtro);
        mongoc_collection_destroy(colecao);
        mongoc_client_destroy(cliente);
        mongoc_cleanup();

        return 1;
    }

    mongoc_cursor_destroy(cursor);

    /* Se não encontrou, não tenta excluir */
    if (!encontrado)
    {
        printf("\nAluno nao encontrado.\n");

        bson_destroy(filtro);
        mongoc_collection_destroy(colecao);
        mongoc_client_destroy(cliente);
        mongoc_cleanup();

        return 0;
    }

    /* Exclui o documento encontrado */
    if (mongoc_collection_delete_one(
            colecao,
            filtro,
            NULL,
            &resposta,
            &erro))
    {
        printf("\nAluno excluido com sucesso!\n");
    }
    else
    {
        printf("\nErro ao excluir aluno: %s\n",
               erro.message);
    }

    /* Libera os recursos */
    bson_destroy(&resposta);
    bson_destroy(filtro);

    mongoc_collection_destroy(colecao);
    mongoc_client_destroy(cliente);

    mongoc_cleanup();

    return 0;
}