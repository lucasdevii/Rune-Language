#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../data/parser.h"

void printASTNode(ASTNode *node);

int parser(Token *head) {
    Token *current = head;

    ASTNode *root = calloc(1, sizeof(ASTNode)); //Ponteiro para o nó raiz da AST
    ASTNode *node = root;

    while (current != NULL) { //Passa por todos os comandos.
        node->ASTtype = getASTType(current); //Passa pelos tokens e filtra seu tipo

        if (node->ASTtype == NODE_NOTHING) {
            printf("ERRO DE SINTAXE: comando não suportado: %s\n", current->text);
            free(node);
            return 0;
        }

        //Passa pelos tokens, e monta a arvore de acordo com seu tipo
        //A função já move o ponteiro current para o inicio do proximo comando
        fillNodeWithNewTokens(&current, node); 

        printASTNode(node);
    }

    return 1; 
}

void printASTNode(ASTNode *node)
{
    printf("\n========== AST NODE ==========\n");

    printf("AST Type: ");

    switch (node->ASTtype) {
        case VARIABLE_DECLARATION:
            printf("VARIABLE_DECLARATION\n");
            break;

        default:
            printf("UNKNOWN\n");
            break;
    }

    printf("Variable Type: ");

    switch (node->varType) {
        case TYPE_INT:
            printf("int\n");
            break;

        case TYPE_TEXT:
            printf("text\n");
            break;

        case TYPE_BOOL:
            printf("bool\n");
            break;

        case TYPE_FLOAT:
            printf("float\n");
            break;

        default:
            printf("UNKNOWN\n");
            break;
    }

    printf("Identifier: %s\n", node->identifier);

    printf("Value: ");

    switch (node->varType) {
        case TYPE_INT:
            printf("%d\n", node->data.intValue);
            break;

        case TYPE_TEXT:
            printf("%s\n", node->data.text);
            break;

        default:
            printf("Unsupported value type\n");
            break;
    }

    printf("==============================\n");
}