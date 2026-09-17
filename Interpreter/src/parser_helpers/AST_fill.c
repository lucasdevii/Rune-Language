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
    ASTNodeType type = node->type;

    if(type == AST_VARIABLE){
        checkVariableDeclaration(current, node);
    }
}

void checkVariableDeclaration(Token **current, ASTNode *node)
{
    Token *token = *current;

    if(node->type == AST_VARIABLE){
        // TYPE
        node->variable.varType = token->specificType;

        // IDENTIFIER
        token = token->nextNode;
        node->variable.identifier = strdup(token->text);

        // ASSIGNMENT
        token = token->nextNode;

        if(token->specificType == SEMICOLON){ //É uma variavel instanciada mas nn inicializada
            *current = token->nextNode;

            return;
        }

        // VALUE
        token = token->nextNode;

        if (node->variable.varType == TYPE_INT) {
            node->variable.value.intValue = atoi(token->text);
        }

        else if (node->variable.varType == TYPE_TEXT) {
            node->variable.value.text = strdup(token->text);
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

void checkFunctionCall(){
    
}