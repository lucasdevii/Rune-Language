#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <string.h>

#include "../../data/token.h"
#include "../../data/parser_datas/abstract_sintax_tree.h"

//FEITO PARA RETORNAR O TIPO DE AST QUE O PARSER TEM QUE UTILIZAR PARA O COMANDO

ASTNodeType getASTType(Token *current){
    return ifStartsWithType(current);
}

ASTNodeType ifStartsWithType(Token *current){
    if(current->geralType == TYPE){
        ASTNodeType astType = ifNextIsIdentifier(current->nextNode);
        
        if(astType != NOTHING){
             return astType;
        }
        else{
            printf("ERRO DE SINTAXE: %d não atribui o seu tipo a nada.");

            exit(EXIT_FAILURE);
        }
    }
    
    return NOTHING;
}

ASTNodeType ifHasIdentifier(Token *current){
    if(current->geralType == IDENTIFIER){

        if(ifEndsNow(current->nextNode) || ifHasAssignment(current->nextNode)){
            return VARIABLE_DECLARATION;
        }

        //PODE SER UMA FUNÇÃO TBM
        //if(ifEntryKeys){}
    }

    return 0;
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

