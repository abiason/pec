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

// Função para ler uma string do teclado
void lerString(const char *mensagem, char *destino, size_t tamanho) {

    printf("%s", mensagem);

    if (fgets(destino, tamanho, stdin) != NULL) {

        // Remove o caractere de nova linha
        destino[strcspn(destino, "\n")] = '\0';

        // Limpa o restante da entrada, se necessário
        if (strlen(destino) == tamanho - 1) {
            int c;

            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// Função para criar o arquivo de configuração
int criarConfig(const char *arquivo, const Config *config) {

    FILE *fp = fopen(arquivo, "w");

    if (fp == NULL) {
        printf("Erro ao criar o arquivo \"%s\" de configuracao!\n", arquivo);
        return 0;
    }

    fprintf(fp, "hostname=%s\n", config->hostname);
    fprintf(fp, "port=%s\n", config->port);
    fprintf(fp, "database=%s\n", config->database);
    fprintf(fp, "username=%s\n", config->username);
    fprintf(fp, "password=%s\n", config->password);

    if (fclose(fp) != 0) {
        printf("Erro ao fechar o arquivo \"%s\"!\n", arquivo);
        return 0;
    }

    return 1;
}

int main() {
    Config config = {0};

    printf("\n");

    printf("CONFIGURACAO POSTGRESQL\n");
    printf("----------------------\n\n");

    // Leitura dos dados fornecidos pelo usuario
    lerString("Hostname: ", config.hostname, sizeof(config.hostname));
    lerString("Port....: ", config.port, sizeof(config.port));
    lerString("Database: ", config.database, sizeof(config.database));
    lerString("Username: ", config.username, sizeof(config.username));
    lerString("Password: ", config.password, sizeof(config.password));

    printf("\n");

    // Cria o arquivo de configuracao
    if (criarConfig("postgresql.cfg", &config)) {
        printf("O arquivo \"postgresql.cfg\" foi criado com sucesso!\n");
    }

    return 0;
}