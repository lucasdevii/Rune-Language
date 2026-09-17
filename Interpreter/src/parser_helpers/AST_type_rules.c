#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <string.h>

#include "../../data/token.h"
#include "../../data/parser_datas/AST_node.h"

ASTNodeType ifStartWithType(Token *current);

ASTNodeType ifHasIdentifier(Token *current);

int ifEnds(Token *current);
int ifHasAssignment(Token *current);
int ifHasValue(Token *current);
int ifHasEntryAndCloseKeys(Token *current);

//FEITO PARA RETORNAR O TIPO DE AST QUE O PARSER TEM QUE UTILIZAR PARA O COMANDO
ASTNodeType getASTType(Token *current){
    ASTNodeType type = ifStartWithType(current);

    if(type == AST_NOTHING){
        type = ifHasIdentifier(current);
    }
    else{
        printf("ERRO DE SINTAXE: tipo de AST não conhecida");
    }

    return type;
}

ASTNodeType ifStartWithType(Token *current){
    if(current->geralType == TYPE){ 
        ASTNodeType astType = ifHasIdentifier(current->nextNode);
        
        if(astType != AST_NOTHING){
             return astType;
        }
        else{
            printf("ERRO DE SINTAXE: %s não atribui o seu tipo a nada.", current->text);

            exit(EXIT_FAILURE);
        }
    }
    
    return AST_NOTHING;
}

ASTNodeType ifHasIdentifier(Token *current){
    if(current->specificType == IDENTIFIER){

        if(ifHasEntryAndCloseKeys(current->nextNode)){
            return AST_CALL;
        }

        if(ifEnds(current->nextNode) || ifHasAssignment(current->nextNode)){
            return AST_VARIABLE;
        }

        //PODE SER A DECLARAÇÃO DE UMA FUNÇÃO TBM
        //if(ifEntryKeys){}
    }

    return AST_NOTHING;
}

int ifHasAssignment(Token *current){
    if(current->specificType == ASSIGNMENT){
        if(ifHasValue(current->nextNode)){
            return 1;
        }
        else{
            printf("ERRO DE SINTAXE: falta de atribuição");

            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

int ifHasValue(Token *current){
    if(current->geralType == VALUE){
        return 1;
    }

    return 0;
}

int ifHasEntryAndCloseKeys(Token *current){
    if(current->specificType == OPEN_PARENTHESIS){
        return 1;
    }

    return 0;
}

int ifEnds(Token *current){
    if(current->specificType == SEMICOLON){
        return 1;
    }

    return 0;
}


//RETORNA ONDE O VALOR DO TOKEN DEVE SE ENCAIXAR NA AST

// -------  MACRO 
#define signInAST(node, value) _Generic((value), \
    int: signInASTInt, \
    float: signInASTFloat, \
    char*: signInASTText \
)(node, value)

void signInASTInt(ASTNode *node, int value){
    node->variable.value.intValue = value;
}

void signInASTFloat(ASTNode *node, float value){

}

void signInASTText(ASTNode *node, char *value){
    node->variable.value.text = value;
}