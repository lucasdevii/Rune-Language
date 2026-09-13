#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <string.h>

#include "../../data/token.h"
#include "../../data/parser_datas/abstract_sintax_tree.h"
#include "../../data/parser_datas/AST_node_types.h"

ASTNodeType ifStartWithType(Token *current);
ASTNodeType ifHasIdentifier(Token *current);

int ifEndsNow(Token *current);
int ifHasAssignment(Token *current);
int ifHasValue(Token *current);



//FEITO PARA RETORNAR O TIPO DE AST QUE O PARSER TEM QUE UTILIZAR PARA O COMANDO

ASTNodeType getASTType(Token *current){
    return ifStartWithType(current);
}

ASTNodeType ifStartWithType(Token *current){
    if(current->geralType == TYPE){ 
        ASTNodeType astType = ifHasIdentifier(current->nextNode);
        
        if(astType != NODE_NOTHING){
             return astType;
        }
        else{
            printf("ERRO DE SINTAXE: %s não atribui o seu tipo a nada.", current->text);

            exit(EXIT_FAILURE);
        }
    }
    
    return NODE_NOTHING;
}

ASTNodeType ifHasIdentifier(Token *current){
    if(current->geralType == IDENTIFIER){

        if(ifEndsNow(current->nextNode) || ifHasAssignment(current->nextNode)){
            return VARIABLE_DECLARATION;
        }

        //PODE SER UMA FUNÇÃO TBM
        //if(ifEntryKeys){}
    }

    return NODE_NOTHING;
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

int ifEndsNow(Token *current){
    if(current->specificType == SEMICOLON){
        return 1;
    }

    return 0;
}

