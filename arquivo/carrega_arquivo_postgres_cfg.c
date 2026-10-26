#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados de conexão
typedef struct {
    char hostname[256];
    char port[6];
    char database[64];
    char username[64];
    char password[256];
} Config;

// Função para carregar o arquivo de configuração
int carregarConfig(const char *arquivo, Config *config) {

    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo \"%s\"de configuracao!\n", arquivo);
        return 0;
    }

    char linha[514];
    char chave[256];
    char valor[256];

    while (fgets(linha, sizeof(linha), fp) != NULL) {

        if (sscanf(linha, "%255[^=]=%255[^\n]", chave, valor) == 2) {
            char *destino = NULL;
            size_t tamanho = 0;

            if (strcmp(chave, "hostname") == 0) {
                destino = config->hostname;
                tamanho = sizeof(config->hostname);
            } else if (strcmp(chave, "port") == 0) {
                destino = config->port;
                tamanho = sizeof(config->port);
            } else if (strcmp(chave, "database") == 0) {
                destino = config->database;
                tamanho = sizeof(config->database);
            } else if (strcmp(chave, "username") == 0) {
                destino = config->username;
                tamanho = sizeof(config->username);
            } else if (strcmp(chave, "password") == 0) {
                destino = config->password;
                tamanho = sizeof(config->password);
            }

            if (destino != NULL) {
                if (strlen(valor) >= tamanho) {
                    printf("Erro: valor muito longo para %s!\n", chave);
                    fclose(fp);
                    return 0;
                }

                strcpy(destino, valor);
            }
        }
    }

    fclose(fp);

    return 1;
}

int main() {
    Config config = {0};

    if (carregarConfig("postgresql.cfg", &config)) {
        printf("\n");
        
        printf("CONFIGURACAO POSTGRESQL\n");
        printf("----------------------\n");

        printf("Hostname: %s\n", config.hostname);
        printf("Port....: %s\n", config.port);
        printf("Database: %s\n", config.database);
        printf("Username: %s\n", config.username);
        printf("Password: %s\n", config.password);

        printf("\n");
    }

    return 0;
}