#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "abstract_sintax_tree.h"

typedef enum {
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

SyntaxModels typesCandidates[] = {
    { FUNCTION_DECLARATION, &functionDeclarationRule },
    { FUNCTION_CALL,        &functionCallRule },
    { VARIABLE_DECLARATION, &variableDeclarationRule }
};
