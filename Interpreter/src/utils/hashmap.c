#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../data/parser_datas/AST_node.h"

typedef struct Entry {
    char *identifier;
    ASTNode *node;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *nodes[50];
} HashMap;

int Hash(const char *identifier);
char *GetIdentifierVariable(ASTNode *ast);

HashMap *HashMapInit(){ //Inicializa o hashMap
    HashMap *map = calloc(1, sizeof(HashMap));

    return map;
}

void HashMapAdd(HashMap *map, ASTNode *value)
{
    char *text = GetIdentifierVariable(value);

    int bucketLocation = Hash(text);

    Entry *informations = malloc(sizeof(Entry));

    informations->identifier = text;
    informations->node = value;
    informations->next = NULL;

    //Bucket vazio
    if(map->nodes[bucketLocation] == NULL){
        map->nodes[bucketLocation] = informations;
        return;
    }

    //nova Entry aponta para a antiga primeira Entry
    informations->next = map->nodes[bucketLocation];

    //nova Entry vira a primeira do bucket
    map->nodes[bucketLocation] = informations;
}

ASTNode *HashMapGet(HashMap *map, const char* identifier){
    int bucketIndex = Hash(identifier);

    Entry *currentEntry = map->nodes[bucketIndex];

    while(currentEntry != NULL){
        if(strcmp(currentEntry->identifier, identifier) == 0){
            return currentEntry->node;
        }

        currentEntry = currentEntry->next;
    }

    printf("ERRO: variavel \'%s\' não encontrada no HashMap\n", identifier);
    exit(EXIT_FAILURE);
}

int Hash(const char *identifier){
    unsigned long hash = 0;

    while(*identifier){
        hash = hash * 31 + (unsigned char)*identifier;
        identifier++;
    }

    return hash % 50;
}

char *GetIdentifierVariable(ASTNode *ast){
    if(ast->type == AST_VARIABLE){
        return ast->variable.identifier;
    }
    else{
        printf("ERRO DE ALOCAÇÃO: Tipo de AST não identificado");

        exit(EXIT_FAILURE);
    }
}



