#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "abstract_sintax_tree.h"
#include "../../src/parser_helpers/AST_type_rules.c"

typedef enum {
    NOTHING,
    
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
