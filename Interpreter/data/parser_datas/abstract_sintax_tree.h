#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "AST_node_types.h"

typedef struct ASTNode {
    ASTNodeType type; // Tipo do nó 
    char *name; // Nome do nó 
    char *value; // Valor do nó 

    struct ASTNode **children; // Array de ponteiros para os filhos do nó
    int numChildren; // Número de filhos do nó
} ASTNode;

