#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h> // Biblioteca necessária para metadados
#include <time.h> 

//Enums e structs

typedef enum TokenTypes{
    NUMBER,
    SIMBOL,
    WORD
} TokenTypes;

typedef enum LexicalTypes{
    TYPE,
    NAME,
    VALUE
} LexicalTypes;

typedef struct Token{
    char *text;
    LexicalTypes lexicalType;
    TokenTypes charType;
    struct Token *nextNode;
} Token;

//pré-inicialização

FILE* getArchive(char *caminho);
void readArchive(FILE *file);


int main(int argc, char *argv[]){
    char* path = "./workspaces/Rune-Language/arch.rn";

    printf("%d \n", argc);
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

    size_t capacity = 256;
    char *buffer = malloc(capacity);
    
    int c;

    while((c = fgetc(file)) != EOF){
        printf("%c", c);
        // //Se for null é o primeiro nó
        // if(head == NULL){

        // }
        
        // if(isspace(c)){ //Espaço

        // }

        // if(isalpha(c)){ //Letras

        // }
        // else if(isdigit(c)){ //Numeros

        // }
        // else{ //Simbolos

        // }
    }

    fclose(file);
}