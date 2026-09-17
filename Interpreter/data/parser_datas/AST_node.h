#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_NOTHING,
    
    VARIABLE_DECLARATION,
    FUNCTION_DECLARATION,
    FUNCTION_CALL,
    BINARY_EXPRESSION
} ASTNodeType;

typedef struct{
    ASTNodeType ASTtype;
    
    TokenTypes varType;
    char *identifier;

    union{
        int intValue;
        char *text;
    } data;
} ASTNode; 

