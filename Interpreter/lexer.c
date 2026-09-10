#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "token.h"

//PRÉ INICIALIZAÇÃO DE FUNÇÕES
void addToken(Token **head, Token **tail, const char *text, TokenTypes generalType, TokenTypes specificType);
void tokenTypeVerifications(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int checkPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int checkOperators(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int checkVariablesComponet(char *buffer, TokenTypes *generalType, TokenTypes *specificType);

void lexer(FILE *file, Token **head, Token **tail){
    char *buffer = calloc(15, sizeof(char));
    int length = 0;
    
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
                addToken(head, tail, ";", END, END);
            }

            buffer[0] = '\0';
            length = 0;
            continue;
        }
        
        buffer[length] = c;
        buffer[length + 1] = '\0';

        length++;
    }

    Token *currentTail = *head;

    free(buffer);
}

void addToken(Token **head, Token **tail, const char *text, TokenTypes generalType, TokenTypes specificType) {
    Token *newToken = malloc(sizeof(Token));
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


void tokenTypeVerifications(char *buffer, TokenTypes *generalType, TokenTypes *specificType){ //PEga o token e faz verificações
    int stopChecking = 0;

    stopChecking = checkPrimitiveTypes(buffer, generalType, specificType); 

    if(!stopChecking) {
        stopChecking = checkOperators(buffer, generalType, specificType);
    }
    if(!stopChecking) {
        stopChecking = checkVariablesComponet(buffer, generalType, specificType);
    }

}

int checkPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
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
        return 1;
    }
    return 0;
}

int checkOperators(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
    if(strcmp(buffer, "=") == 0){
        *specificType = ATTRIBUTION;
    }
    else if(strcmp(buffer, "==") == 0){
        *specificType = COMPARE;
    }
    else if(strcmp(buffer, "+") == 0){
        *specificType = SUM;
    }
    else if(strcmp(buffer, "-") == 0){
        *specificType = SUBTRACT;
    }
    else if(strcmp(buffer, "*") == 0){
        *specificType = MULTIPLY;
    }
    else if(strcmp(buffer, "/") == 0){
        *specificType = DIVIDE;
    }

    if(*specificType != NOTHING){
        *generalType = OPERATOR;
        return 1;
    }
    return 0;
}

int checkVariablesComponet(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
    if(
        isalpha(buffer[0]) || 
        buffer[0] == '_' || 
        buffer[0] == '$'
    ){
        *specificType = VARIABLE_NAME;
        *generalType = NAME;
    
        return 1;
    }
    else if(
        isdigit(buffer[0]) ||
        buffer[0] == '\"' ||
        buffer[0] == '\''
    ){
        //É BOM QUE SPECIFICTYPE SAIBA IDENTIFICAR TIPO DA VARIAVEL FUTURAMENTE A PARTIR DE UMA FUNÇÃO 
        *specificType = VALUE;
        *generalType = VALUE;

        return 1;
    }

    return 0;
}
