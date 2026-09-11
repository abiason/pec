#include <stdio.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

int main()
{
    mongoc_client_t *cliente;
    mongoc_collection_t *colecao;
    bson_t *documento;
    bson_error_t erro;

    /* Inicializa o MongoDB C Driver */
    mongoc_init();

    /* Conecta ao servidor MongoDB */
    cliente = mongoc_client_new("mongodb://localhost:27017");

    if (cliente == NULL)
    {
        printf("Erro ao criar o cliente MongoDB.\n");
        mongoc_cleanup();
        return 1;
    }

    /*
     * Seleciona:
     * Banco: faculdade
     * Collection: alunos
     */
    colecao = mongoc_client_get_collection(
        cliente,
        "faculdade",
        "alunos"
    );

    /* Cria um documento BSON */
    documento = bson_new();

    BSON_APPEND_INT32(documento, "ra", 1001);
    BSON_APPEND_UTF8(documento, "nome", "Joao");
    BSON_APPEND_UTF8(documento, "curso", "ADS");
    BSON_APPEND_INT32(documento, "semestre", 2);

    /* Insere o documento */
    if (mongoc_collection_insert_one(
            colecao,
            documento,
            NULL,
            NULL,
            &erro))
    {
        printf("Aluno cadastrado com sucesso!\n");
    }
    else
    {
        printf("Erro ao cadastrar aluno: %s\n", erro.message);
    }

    /* Libera os recursos */
    bson_destroy(documento);
    mongoc_collection_destroy(colecao);
    mongoc_client_destroy(cliente);

    mongoc_cleanup();

    return 0;
}