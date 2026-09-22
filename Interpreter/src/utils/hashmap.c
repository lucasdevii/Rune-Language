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

    return NULL;

    // printf("ERRO: variavel \'%s\' não encontrada no HashMap\n", identifier);
    // exit(EXIT_FAILURE);
}

int HashMapRemove(HashMap *map, const char* identifier){
    int bucketIndex = Hash(identifier);

    Entry *currentEntry = map->nodes[bucketIndex];
    Entry *beforeEntry = NULL;

    while(currentEntry != NULL){
        if(strcmp(currentEntry->identifier, identifier) == 0){
            if(beforeEntry != NULL){
                //Se tiver algum entry antes, o anterior aponta para o proximo do removido
                beforeEntry->next = currentEntry->next;
            }
            else{
                //Se não tiver nenhum antes, ele é o primeiro, ent apenas faz o inicio apontar para o proximo do removido
                map->nodes[bucketIndex] = currentEntry->next;
            }

            ASTNodeFree(currentEntry->node);
            free(currentEntry);

            return 1;
        }

        beforeEntry = currentEntry;
        currentEntry = currentEntry->next;
    }
    
    return 0;
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

void ASTNodeFree(ASTNode *node)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_VARIABLE:
            free(node->variable.identifier);

            if (node->variable.varType == TYPE_TEXT)
                free(node->variable.value.text);

            break;


        case AST_FUNCTION:
            free(node->function.name);

            // Se body for uma árvore
            ASTNodeFree(node->function.body);

            break;


        case AST_BINARY:
            // Primeiro libera os filhos
            ASTNodeFree(node->binary.left);
            ASTNodeFree(node->binary.right);

            break;


        case AST_CALL:
            free(node->call.name);

            // Argumentos
            // Não lembro se é uma ast ou se é uma lista, dependendo do que seja é interessante aplicar uma abordagem diferente
            ASTNodeFree(node->call.arguments);

            break;

        case AST_LITERAL:
            if (node->literal.type == TYPE_TEXT)
                free(node->literal.value.text);

            break;


        default:
            break;
    }

    // libera o próprio node
    free(node);
}


