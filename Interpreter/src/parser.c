#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../data/parser.h"
#include "../data/token.h"
#include "../data/lexer.h"
#include "../data/parser_datas/abstract_sintax_tree.h"

int parser(Token *head) {
    Token *current = head;

    ASTNode *root = malloc(sizeof(ASTNode)); //Ponteiro para o nó raiz da AST
    ASTNode *node = root;

    while (current != NULL) { //Enquanto tiver tokens, vai percorrer a lista de tokens
        while(current->specificType != SEMICOLON){ //Reseta o estado do parser até encontrar um ponto e vírgula
            current = current->nextNode;
        }
    }

    return 1; 
}