#include <stdio.h>
#include <mongoc/mongoc.h>

int main()
{
    mongoc_client_t *cliente;
    bson_t comando = BSON_INITIALIZER;
    bson_t resposta;
    bson_error_t erro;

    /* Inicializa o MongoDB C Driver */
    mongoc_init();

    /* Cria conexão com o MongoDB local */
    cliente = mongoc_client_new("mongodb://localhost:27017");

    if (cliente == NULL)
    {
        printf("Erro ao criar o cliente MongoDB.\n");
        mongoc_cleanup();
        return 1;
    }

    /* Cria o comando { ping: 1 } */
    BSON_APPEND_INT32(&comando, "ping", 1);

    /* Envia o comando para o MongoDB */
    if (mongoc_client_command_simple(
            cliente,
            "admin",
            &comando,
            NULL,
            &resposta,
            &erro))
    {
        printf("Conexao com MongoDB realizada com sucesso!\n");
    }
    else
    {
        printf("Erro ao conectar ao MongoDB: %s\n", erro.message);
    }

    /* Libera os recursos */
    bson_destroy(&resposta);
    bson_destroy(&comando);
    mongoc_client_destroy(cliente);

    mongoc_cleanup();

    return 0;
}