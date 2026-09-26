#include "stdio.h"
#include "stdlib.h"

#include "data/token_data/token_structs.h"

FILE* GetArchive(char *caminho);
Token *ReadArchive(FILE* file);

int Main(int argc, char *argv[]){
    char *path = argv[1];

    FILE *file = GetArchive(path);

    if(file == NULL){
        printf("Arquivo não identificado.");

        exit(EXIT_FAILURE);
    }

    Token *tokenHead = ReadArchive(file);
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
    //FUNÇÃO LEXER RETORNA O TOKEN HEAD
    Token *head = Lexer();

    fclose(file);

    return head;
}