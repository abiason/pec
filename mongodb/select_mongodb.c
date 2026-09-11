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

    char *json;

    /* Inicializa o MongoDB C Driver */
    mongoc_init();

    /* Conecta ao MongoDB */
    cliente = mongoc_client_new("mongodb://localhost:27017");

    if (cliente == NULL)
    {
        printf("Erro ao criar o cliente MongoDB.\n");
        mongoc_cleanup();
        return 1;
    }

    /* Banco: faculdade
       Collection: alunos */
    colecao = mongoc_client_get_collection(
        cliente,
        "faculdade",
        "alunos"
    );

    /* Filtro vazio = buscar todos */
    filtro = bson_new();

    /* Executa a consulta */
    cursor = mongoc_collection_find_with_opts(
        colecao,
        filtro,
        NULL,
        NULL
    );

    printf("\nALUNOS CADASTRADOS\n");
    printf("------------------------------\n");

    /* Percorre os documentos encontrados */
    while (mongoc_cursor_next(cursor, &documento))
    {
        json = bson_as_canonical_extended_json(
            documento,
            NULL
        );

        printf("%s\n", json);

        bson_free(json);
    }

    /* Libera os recursos */
    bson_destroy(filtro);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(colecao);
    mongoc_client_destroy(cliente);

    mongoc_cleanup();

    return 0;
}