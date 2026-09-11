#include <stdio.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

int main()
{
    mongoc_client_t *cliente;
    mongoc_collection_t *colecao;
    mongoc_cursor_t *cursor;

    bson_t *filtro;
    bson_t *update;
    bson_t set;
    bson_t resposta;

    const bson_t *documento;

    bson_iter_t campo;
    bson_error_t erro;

    int ra;
    int semestre;

    char nome[100];
    char curso[100];

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

    /* Cria o filtro */
    filtro = bson_new();

    BSON_APPEND_INT32(
        filtro,
        "ra",
        ra
    );

    /* Busca o aluno antes de alterar */
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

    /* Se não encontrou, encerra */
    if (!encontrado)
    {
        printf("\nAluno nao encontrado.\n");

        bson_destroy(filtro);
        mongoc_collection_destroy(colecao);
        mongoc_client_destroy(cliente);
        mongoc_cleanup();

        return 0;
    }

    /* Só pede novos dados se encontrou */
    printf("\nDigite o novo nome: ");
    scanf(" %99[^\n]", nome);

    printf("Digite o novo curso: ");
    scanf(" %99[^\n]", curso);

    printf("Digite o novo semestre: ");
    scanf("%d", &semestre);

    /* Monta o UPDATE */
    update = bson_new();

    BSON_APPEND_DOCUMENT_BEGIN(
        update,
        "$set",
        &set
    );

    BSON_APPEND_UTF8(
        &set,
        "nome",
        nome
    );

    BSON_APPEND_UTF8(
        &set,
        "curso",
        curso
    );

    BSON_APPEND_INT32(
        &set,
        "semestre",
        semestre
    );

    bson_append_document_end(
        update,
        &set
    );

    /* Executa a atualização */
    if (mongoc_collection_update_one(
            colecao,
            filtro,
            update,
            NULL,
            &resposta,
            &erro))
    {
        printf("\nAluno atualizado com sucesso!\n");
    }
    else
    {
        printf("\nErro ao atualizar aluno: %s\n",
               erro.message);
    }

    bson_destroy(&resposta);
    bson_destroy(update);
    bson_destroy(filtro);

    mongoc_collection_destroy(colecao);
    mongoc_client_destroy(cliente);

    mongoc_cleanup();

    return 0;
}