#include "../../data/rune_functions/functions/show.h"

#include <stdio.h>

void show(ASTNode *node, VariablesMap *variablesMap){
    if (node == NULL || node->call.arguments == NULL) {
        return;
    }

    ASTNode *argumentNode = VariablesMapGet(variablesMap, node->call.arguments);

    if (argumentNode == NULL) {
        printf("%s\n", node->call.arguments);
        return;
    }

    if (argumentNode->type == AST_VARIABLE) {
        switch (argumentNode->variable.varType) {
            case TYPE_INT:
                printf("%d\n", argumentNode->variable.value.intValue);
                break;
            case TYPE_TEXT:
                printf("%s\n", argumentNode->variable.value.text);
                break;
            case TYPE_BOOL:
                printf("%s\n", argumentNode->variable.value.intValue ? "true" : "false");
                break;
        }
    } else {
        printf("%s\n", node->call.arguments);
    }
}