#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h> // Biblioteca necessária para metadados
#include <time.h> 
#include <string.h>

#include "lexer.h"
#include "token.h"

//pré-inicialização

FILE* getArchive(char *caminho);
void readArchive(FILE *file);

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Uso: %s <caminho_do_arquivo>\n", argv[0]);
        return 1;
    }

    char* path = argv[1];

    printf("%s %s \n", argv[0], argv[1]);
    
    FILE *file = getArchive(path);

    if(file != NULL){
        readArchive(file);
    }

    return 0;
}

//Funções

FILE* getArchive(char *caminho){
    FILE *file = fopen(caminho, "r");
    
    
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL; // Encerra o programa se o arquivo não existir
    }
    

    return file;
}

void readArchive(FILE* file){
    struct Token *head = NULL;
    struct Token *tail = NULL;

    lexer(file, &head, &tail);

    fclose(file);

    Token *current = head;
    while (current != NULL) {
        printf("%s (%s)\n", current->text, token_type_name(current->specificType));
        Token *temp = current;
        current = current->nextNode;
        free(temp->text);
        free(temp);
    }
}


