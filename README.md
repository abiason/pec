Compilando Exemplos
-------------------


* Comando para compilar o programa de teste do ambiente de desenvolvimento:

        gcc teste.c -o teste.exe


* Comando para compilar os programas com a lib do PostgreSQL:

        gcc <NOME_ARQUIVO>.c -o <NOME_ARQUIVO>.exe -IC:\msys64\ucrt64\include -LC:\msys64\ucrt64\lib -lpq


* Comando para compilar os programas com a lib do MongoDB:

        gcc <NOME_ARQUIVO>.c -o <NOME_ARQUIVO>.exe -D__USE_MINGW_ANSI_STDIO=1 -DUTF8PROC_EXPORTS -LC:\msys64\ucrt64\lib -lmongoc2 -lbson2


* Comando para compilar a Calculadora:

        gcc main.c util.c operacao.c -o calculadora.exe
