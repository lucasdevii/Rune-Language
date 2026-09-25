#include "stdio.h"
#include "stdlib.h"

#include "data/token_data/token_structs.h"

int Main(int argc, char *argv[]){
    char *path = argv[1];

    FILE *archive = GetArchive(path);

    Token tokenHead = ReadArchive(archive);
}

FILE* GetArchive(char *caminho){
    FILE *file = fopen(caminho, "r");
    
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL; // Encerra o programa se o arquivo não existir
    }
    
    return file;
}


Token *ReadArchive(FILE* file){
    if(file == NULL){
        printf("Arquivo não identificado.");

        exit(EXIT_FAILURE);
    }

    struct Token *tailTokensList = NULL;
    //FUNÇÃO LEXER RETORNA O TOKEN HEAD

    Token *head;

    fclose(file);

    return head;
}