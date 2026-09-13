#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "abstract_sintax_tree.h"

typedef enum {
    NODE_NOTHING,
    
    VARIABLE_DECLARATION,
    FUNCTION_DECLARATION,
    FUNCTION_CALL,
    BINARY_EXPRESSION
} ASTNodeType;

typedef int (*ParserRule)(Token *current);

typedef struct {
    ASTNodeType type;
    ParserRule *rule;
} SyntaxModels;
