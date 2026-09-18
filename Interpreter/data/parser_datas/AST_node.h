#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../token.h"

typedef enum {
    AST_NOTHING,
    AST_VARIABLE,
    AST_FUNCTION,
    AST_BINARY,
    AST_CALL,
    AST_LITERAL
} ASTNodeType;

typedef struct ASTNode ASTNode;

struct ASTNode {
    ASTNodeType type;

    union {
        struct {
            TokenTypes varType;
            char *identifier;

            union {
                int intValue;
                char *text;
            } value;

        } variable;

        struct {
            char *name;
            ASTNode *body;
        } function;

        struct {
            ASTNode *left;
            ASTNode *right;
            TokenTypes operator;
        } binary;

        struct {
            char *name;
            ASTNode *arguments;
        } call;

        struct {
            TokenTypes type;

            union {
                int intValue;
                char *text;
            } value;

        } literal;
    };
};

