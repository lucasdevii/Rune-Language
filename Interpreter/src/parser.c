#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../data/parser.h"
#include "../data/parser_datas/AST_node.h"

void PrintASTNode(ASTNode *node);

int Parser(Token *headTokenList, ASTList *headASTList) {
    Token *current = headTokenList;

    ASTNode *root = calloc(1, sizeof(ASTNode)); //Ponteiro para o nó raiz da AST
    ASTNode *node = root;

    while (current != NULL) { //Passa por todos os comandos.
        node->type = GetASTType(current); //Passa pelos tokens e filtra seu tipo

        if (node->type == AST_NOTHING) {
            printf("ERRO DE SINTAXE: comando não suportado: %s\n", current->text);
            
            exit(EXIT_FAILURE);
        }

        //Passa pelos tokens, e monta a arvore de acordo com seu tipo
        //A função já move o ponteiro current para o inicio do proximo comando
        FillNodeWithNewTokens(&current, node); 

        PrintASTNode(node);
    }

    return 1; 
}

void PrintASTNode(ASTNode *node)
{
    printf("\n========== AST NODE ==========\n");

    printf("AST Type: ");

    switch (node->type) {

        case AST_VARIABLE:
            printf("VARIABLE_DECLARATION\n");

            printf("Variable Type: ");

            switch (node->variable.varType) {
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

            printf("Identifier: %s\n", node->variable.identifier);

            printf("Value: ");

            switch (node->variable.varType) {
                case TYPE_INT:
                    printf("%d\n", node->variable.value.intValue);
                    break;

                case TYPE_TEXT:
                    printf("%s\n", node->variable.value.text);
                    break;

                default:
                    printf("Unsupported value type\n");
                    break;
            }

            break;


        case AST_CALL:
            printf("FUNCTION_CALL\n");

            printf("Function Name: %s\n", node->call.name);

            // Futuramente:
            // printf("Parameters: %d\n", node->call.parameterCount);

            break;


        default:
            printf("UNKNOWN\n");
            break;
    }

    printf("==============================\n");
}