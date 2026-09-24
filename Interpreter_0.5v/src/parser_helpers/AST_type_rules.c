#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <string.h>

#include "../../data/token.h"
#include "../../data/parser_datas/AST_node.h"

ASTNodeType IfStartWithType(Token *current);

ASTNodeType IfHasIdentifier(Token *current);

int IfEnds(Token *current);
int IfHasAssignment(Token *current);
int IfHasValue(Token *current);
int IfHasEntryAndCloseKeys(Token *current);

//FEITO PARA RETORNAR O TIPO DE AST QUE O PARSER TEM QUE UTILIZAR PARA O COMANDO
ASTNodeType GetASTType(Token *current){
    ASTNodeType type = IfStartWithType(current);

    if(type == AST_NOTHING){
        type = IfHasIdentifier(current);
    }

    return type;
}

ASTNodeType IfStartWithType(Token *current){
    if(current->geralType == TYPE){ 
        ASTNodeType astType = IfHasIdentifier(current->nextNode);
        
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

ASTNodeType IfHasIdentifier(Token *current){
    if(current->specificType == IDENTIFIER){

        if(IfHasEntryAndCloseKeys(current->nextNode)){
            return AST_CALL;
        }

        if(IfEnds(current->nextNode) || IfHasAssignment(current->nextNode)){
            return AST_VARIABLE;
        }

        //PODE SER A DECLARAÇÃO DE UMA FUNÇÃO TBM
        //if(ifEntryKeys){}
    }

    return AST_NOTHING;
}

int IfHasAssignment(Token *current){
    if(current->specificType == ASSIGNMENT){
        if(IfHasValue(current->nextNode)){
            return 1;
        }
        else{
            printf("ERRO DE SINTAXE: falta de atribuição");

            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

int IfHasValue(Token *current){
    if(current->geralType == VALUE){
        return 1;
    }

    return 0;
}

int IfHasEntryAndCloseKeys(Token *current){
    if(current->specificType == OPEN_PARENTHESIS){
        return 1;
    }

    return 0;
}

int IfEnds(Token *current){
    if(current->specificType == SEMICOLON){
        return 1;
    }

    return 0;
}


//RETORNA ONDE O VALOR DO TOKEN DEVE SE ENCAIXAR NA AST

// -------  MACRO 
#define SignInAST(node, value) _Generic((value), \
    int: SignInASTInt, \
    float: SignInASTFloat, \
    char*: SignInASTText \
)(node, value)

void SignInASTInt(ASTNode *node, int value){
    node->variable.value.intValue = value;
}

void SignInASTFloat(ASTNode *node, float value){

}

void SignInASTText(ASTNode *node, char *value){
    node->variable.value.text = value;
}