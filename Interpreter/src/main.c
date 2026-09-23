#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <string.h>

#include "../data/lexer.h"
#include "../data/token.h"
#include "../data/parser.h"
#include "../data/parser_datas/AST_node.h"
#include "../data/interpreter.h"
#include "../data/rune_functions/function_definition.h"

//pré-inicialização

FILE* GetArchive(char *caminho);
void ReadArchive(FILE *file, Token **headTokensList);

int main(int argc, char *argv[]){
    //Inicializa as funções padrão da linguagem
    FunctionsMap *map = FunctionsMapInit();
    RegisterRuneFunctions(map);
    
    ASTList *headASTList = malloc(sizeof(ASTList));
    headASTList->next = NULL;
    headASTList->current = NULL;

    if (argc < 2) {
        printf("Uso: %s <caminho_do_arquivo>\n", argv[0]);
        return 1;
    }

    char* path = argv[1];

    printf("%s %s \n", argv[0], argv[1]);
    
    FILE *file = GetArchive(path);

    if(file != NULL){
        Token *headTokensList = NULL;

        ReadArchive(file, &headTokensList);
        Parser(headTokensList, headASTList);

        Token *current = headTokensList;
        while (current != NULL) {
            printf("%s (%s)\n", current->text, TokenTypeName(current->specificType));
            Token *temp = current;
            current = current->nextNode;
            free(temp->text);
            free(temp);
        }
    }
    else{
        printf("ERRO: arquivo não encontrado");

        exit(EXIT_FAILURE);
    }

    Interpreter(headASTList);

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

void ReadArchive(FILE* file, Token **headTokensList){
    struct Token *tailTokensList = NULL;

    Lexer(file, headTokensList, &tailTokensList);

    fclose(file);
}


