#include <stdio.h>
#include <mongoc/mongoc.h>

int main()
{
    mongoc_init();

    printf("MongoDB C Driver funcionando!\n");

    mongoc_cleanup();

    return 0;
}