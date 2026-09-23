#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../../data/parser.h"
#include "../../data/token.h"
#include "../../data/lexer.h"
#include "../../data/parser_datas/AST_node.h"

void IfVariableDeclaration(Token **current, ASTNode *node);
void IfFunctionCall(Token **current, ASTNode *node);

void FillNodeWithNewTokens(Token **current, ASTNode *node){
    ASTNodeType type = node->type;

    if(type == AST_VARIABLE){
        IfVariableDeclaration(current, node);
    }
    else if(type == AST_CALL){
        IfFunctionCall(current, node);
    }
}

void IfVariableDeclaration(Token **current, ASTNode *node)
{
    Token *token = *current;

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
}

void IfFunctionCall(Token **current, ASTNode *node)
{
    Token *token = *current;

    // Identificador
    if(token->specificType == IDENTIFIER){
        node->call.name = strdup(token->text);
    }
    else{
        printf("ERRO DE SINTAXE: identificador esperado na chamada de função\n");
        exit(EXIT_FAILURE);
    }

    token = token->nextNode;

    if(token == NULL || token->specificType != OPEN_PARENTHESIS){
        printf(
            "ERRO DE SINTAXE: sintaxe na chamada de '%s' errada\n", node->call.name
        );

        exit(EXIT_FAILURE);
    }

    token = token->nextNode;

    if(token != NULL && (token->specificType == IDENTIFIER || token->geralType == VALUE)){
        node->call.arguments = strdup(token->text);

        while(
            token != NULL && 
            (token->specificType == IDENTIFIER || token->geralType == VALUE)
        ){
            printf("PARAMETRO: %s\n", token->text);
                 
            token = token->nextNode;
        }
    }

    if(token->specificType != CLOSE_PARENTHESIS){
        printf(
            "ERRO DE SINTAXE: parêntesis em aberto em '%s'\n", node->call.name
        );

        exit(EXIT_FAILURE);
    }

    token = token->nextNode;

    if(token->specificType == SEMICOLON){
        *current = token->nextNode;
    }
    else{
        printf("ERRO DE SINTAXE: esperado ';' após chamada de '%s'\n", node->call.name);

        exit(EXIT_FAILURE);
    }
}