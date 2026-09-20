#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <string.h>

#include "../data/lexer.h"
#include "../data/token.h"
#include "../data/parser.h"

//pré-inicialização

FILE* GetArchive(char *caminho);
void ReadArchive(FILE *file);

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Uso: %s <caminho_do_arquivo>\n", argv[0]);
        return 1;
    }

    char* path = argv[1];

    printf("%s %s \n", argv[0], argv[1]);
    
    FILE *file = GetArchive(path);

    if(file != NULL){
        ReadArchive(file);
    }

    return 0;
}

//Funções

FILE* GetArchive(char *caminho){
    FILE *file = fopen(caminho, "r");
    
    
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL; // Encerra o programa se o arquivo não existir
    }
    
    return file;
}

void ReadArchive(FILE* file){
    struct Token *head = NULL;
    struct Token *tail = NULL;

    Lexer(file, &head, &tail);

    fclose(file);

    Parser(head);

    Token *current = head;
    while (current != NULL) {
        printf("%s (%s)\n", current->text, TokenTypeName(current->specificType));
        Token *temp = current;
        current = current->nextNode;
        free(temp->text);
        free(temp);
    }
}


