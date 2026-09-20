#include "../../data/parser_datas/AST_node.h"

typedef struct Entry{
    char *identifier;
    ASTNode *node;
    Entry *next;
} Entry;

typedef struct {
    Entry *nodes[50];
} HashMap;

HashMap *hashMap(){ //Inicializa o hashMap
    HashMap *map = calloc(1, sizeof(HashMap));

    return map;
}

void hashMapAdd(HashMap *map, ASTNode *value)
{
    char *text = getIdentifierVariable(value);

    int bucketLocation = hash(text);

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

int hash(const char *identifier){
    unsigned long hash = 0;

    while(*identifier){
        hash = hash * 31 + (unsigned char)*identifier;
        identifier++;
    }

    return hash % 50;
}

char *getIdentifierVariable(ASTNode *ast){
    if(ast->type == AST_VARIABLE){
        return ast->variable.identifier;
    }
    else{
        printf("ERRO DE ALOCAÇÃO: Tipo de AST não identificado");

        exit(EXIT_FAILURE);
    }
}



