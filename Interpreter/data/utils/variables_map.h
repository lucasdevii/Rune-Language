#pragma once

#include "../parser_datas/AST_node.h"

typedef struct EntryASTS {
    char *identifier;
    ASTNode *node;
    struct EntryASTS *next;
} EntryASTS;

typedef struct {
    EntryASTS *nodes[50];
} VariablesMap;

VariablesMap *VariablesMapInit(void);
void VariablesMapAdd(VariablesMap *map, ASTNode *value);
ASTNode *VariablesMapGet(VariablesMap *map, const char *identifier);
int VariablesMapRemove(VariablesMap *map, const char *identifier);
char *GetIdentifierVariable(ASTNode *ast);