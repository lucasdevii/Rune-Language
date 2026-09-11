#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../data/token.h"

typedef struct TokenTypePair { //Para retornar dois tipos de token ao mesmo tempo
    TokenTypes generalType;
    TokenTypes specificType;
} TokenTypePair;

//PRÉ INICIALIZAÇÃO DE FUNÇÕES
void addToken(Token **head, Token **tail, char *text, TokenTypes generalType, TokenTypes specificType);
void tokenTypeVerifications(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int checkPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int checkOperators(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int checkVariablesComponet(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int checkDelimiters(char character, TokenTypes *generalType, TokenTypes *specificType);
TokenTypePair getType(char *buffer);

void lexer(FILE *file, Token **head, Token **tail){
    char *buffer = calloc(15, sizeof(char));
    int length = 0;
    
    int c;

    while ((c = fgetc(file)) != EOF) {
        //Vai verificar se o caractere é um delimitador, se sim, vai adicionar o token do buffer e o token do delimitador
        TokenTypes specificDelimiterType = NOTHING;
        TokenTypes generalDelimiterType = NOTHING;

        int isDelimiter = checkDelimiters(c, &generalDelimiterType, &specificDelimiterType);
        
        if (isspace(c) || isDelimiter) {

            if (buffer[0]) {
                TokenTypes specificType = NOTHING;
                TokenTypes generalType = NOTHING;

                tokenTypeVerifications(buffer, &generalType, &specificType);

                addToken(head, tail, buffer, generalType, specificType);

                buffer[0] = '\0';
                length = 0;
            }

            if (isDelimiter) {
                char delimiterBuffer[2] = {c, '\0'};

                addToken(
                    head,
                    tail,
                    delimiterBuffer,
                    generalDelimiterType,
                    specificDelimiterType
                );
            }

            continue;
        }
        
        buffer[length] = c;
        buffer[length + 1] = '\0';

        length++;
    }

    Token *currentTail = *head;

    free(buffer);
}

void addToken(Token **head, Token **tail, char *text, TokenTypes generalType, TokenTypes specificType) {
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
    if(!stopChecking) {
        printf("Erro: assinatura ('%s') desconhecida \n", buffer);
    }
}

int checkPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
    if(strcmp(buffer, "int") == 0){
        *specificType = TYPE_INT;
    }
    else if(strcmp(buffer, "string") == 0){
        *specificType = TYPE_TEXT;
    }
    else if(strcmp(buffer, "bool") == 0){
        *specificType = TYPE_BOOL;
    }
    else if(strcmp(buffer, "float") == 0){
        *specificType = TYPE_FLOAT;
    }

    if(*specificType != NOTHING){
        *generalType = TYPE;
        
        return 1;
    }
    return 0;
}

int checkOperators(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
    if(strcmp(buffer, "=") == 0){
        *specificType = ASSIGNMENT;
    }
    else if(strcmp(buffer, "==") == 0){
        *specificType = COMPARE;
    }
    else if(strcmp(buffer, "+") == 0){
        *specificType = PLUS;
    }
    else if(strcmp(buffer, "-") == 0){
        *specificType = MINUS;
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
    TokenTypePair pair = getType(buffer);
    *generalType = pair.generalType;
    *specificType = pair.specificType;

    if(getType(buffer).generalType == NOTHING && getType(buffer).specificType == NOTHING){
        printf("Erro: Token desconhecido '%s'\n", buffer);

        return 0;
    }

    return 1;
}

int checkDelimiters(char character, TokenTypes *generalType, TokenTypes *specificType){
    if(character == ';'){
        *specificType = END;
    }
    else if(character == '('){
        *specificType = OPEN_PARENTHESIS;
    }
    else if(character == ')'){
        *specificType = CLOSE_PARENTHESIS;
    }
    else if(character == '{'){
        *specificType = OPEN_BRACE;
    }
    else if(character == '}'){
        *specificType = CLOSE_BRACE;
    }

    if(*specificType != NOTHING){
        *generalType = DELIMITER;
        
        return 1;
    }

    return 0;
}

TokenTypePair getType(char *buffer){
    TokenTypePair types;

    types.specificType = NOTHING;
    types.generalType = NOTHING;

    if(strcmp(buffer, "true") == 0 || strcmp(buffer, "false") == 0){ //Booleano
        types.specificType = TYPE_BOOL;
        types.generalType = VALUE;

        return types;
    }
    else if(strcmp(buffer, "null") == 0){ //Null
        types.specificType = TYPE_NULL;
        types.generalType = VALUE;

        return types;
    }
    else if(buffer[0] == '\"' || buffer[0] == '\''){ //String
        types.specificType = TYPE_TEXT;
        types.generalType = VALUE;

        return types;
    }
    else if(isdigit(buffer[0])){ //Numero
        types.specificType = TYPE_INT;
        types.generalType = VALUE;

        return types;
    }
    else if( //Se não for um tipo primitivo, operador ou valor, então é uma variável name
        isalpha(buffer[0]) || 
        buffer[0] == '_' || 
        buffer[0] == '$'
    ){
        types.specificType = IDENTIFIER;
        types.generalType = NAME;
    
        return types;
    }

    return types;
}
