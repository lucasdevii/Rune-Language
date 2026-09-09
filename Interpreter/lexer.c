#include <stdio.h>
#include <string.h>

#include "token.h"

void addToken(Token **head, Token **tail, const char *text, TokenTypes generalType, TokenTypes specificType) {
    Token *newToken = calloc(sizeof(Token));
    newToken->text = strdup(text);
    newToken->nextNode = NULL;
    newToken->geralType = generalType;
    newToken->specificType = specificType;

    if (*head == NULL) {
        *head = newToken;
        *tail = newToken;
    } else {
        (*tail)->nextNode = newToken;
        *tail = newToken;
    }
}


void lexer(FILE *file, Token **head, Token **tail){
    char *buffer = calloc(15, sizeof(char));
    
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == ';') {

            if (!buffer[0])
                continue;

            TokenTypes specificType = NOTHING;
            TokenTypes generalType = NOTHING;

            tokenTypeVerifications(buffer, &generalType, &specificType);

            addToken(head, tail, buffer, generalType, specificType);

            if (c == ';') {
                addToken(head, tail, ";", END, NOTHING);
            }

            buffer[0] = '\0';
            continue;
        }

        buffer[strlen(buffer)] = c;
        buffer[strlen(buffer) + 1] = '\0';
    }

    free(buffer);
}

void tokenTypeVerifications(char *buffer, TokenTypes *generalType, TokenTypes *specificType){ //PEga o token e faz verificações
    checkPrimitiveTypes(buffer, generalType, specificType); 
}

void checkPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
    if(strcmp(buffer, "int") == 0){
        *specificType = TYPE_INT;
    }
    else if(strcmp(buffer, "string") == 0){
        *specificType = TYPE_STRING;
    }
    else if(strcmp(buffer, "bool") == 0){
        *specificType = TYPE_BOOL;
    }

    if(*specificType != NOTHING){
        *generalType = TYPE;
    }
}

