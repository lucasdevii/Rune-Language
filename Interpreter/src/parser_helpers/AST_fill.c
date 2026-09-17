#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../../data/parser.h"
#include "../../data/token.h"
#include "../../data/lexer.h"
#include "../../data/parser_datas/AST_node.h"

void checkVariableDeclaration(Token **current, ASTNode *node);

void fillNodeWithNewTokens(Token **current, ASTNode *node){
    ASTNodeType type = node->ASTtype;

    if(type == VARIABLE_DECLARATION){
        checkVariableDeclaration(current, node);
    }
}

void checkVariableDeclaration(Token **current, ASTNode *node)
{
    Token *token = *current;

    if(node->ASTtype == VARIABLE_DECLARATION){
        // TYPE
        node->varType = token->specificType;

        // IDENTIFIER
        token = token->nextNode;
        node->identifier = strdup(token->text);

        // ASSIGNMENT
        token = token->nextNode;

        if(token->specificType == SEMICOLON){ //É uma variavel instanciada mas nn inicializada
            *current = token->nextNode;

            return;
        }

        // VALUE
        token = token->nextNode;

        if (node->varType == TYPE_INT) {
            node->data.intValue = atoi(token->text);
        }

        else if (node->varType == TYPE_TEXT) {
            node->data.text = strdup(token->text);
        }

        else {
            printf("ERRO DE SINTAXE: tipo não suportado.\n");

            exit(EXIT_FAILURE);
        }

        // SEMICOLON
        if(token->nextNode->specificType == SEMICOLON){
            *current = token->nextNode->nextNode; //Aponta para o inicio do proximo comando.
        }
        else{
            printf("ERRO DE SINTAXE: declaração extendida");

            exit(EXIT_FAILURE);
        }

        return;
    }
}