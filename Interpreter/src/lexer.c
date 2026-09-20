#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../data/token.h"

//PRÉ INICIALIZAÇÃO DE FUNÇÕES
void AddToken(Token **head, Token **tail, char *text, TokenTypes generalType, TokenTypes specificType);
void TokenTypeVerifications(char *buffer, TokenTypes *generalType, TokenTypes *specificType);

int CheckPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType);

int CheckVariablesComponent(char *buffer, TokenTypes *generalType, TokenTypes *specificType);

int CheckSpecialTokens(char character, char* buffer, FILE *file, TokenTypes *generalType, TokenTypes *specificType);
int CheckPunctuator(char character, TokenTypes *generalType, TokenTypes *specificType);
int CheckOperators(char character, FILE *file, TokenTypes *generalType, TokenTypes *specificType);

TokenTypePair GetType(char *buffer);

void Lexer(FILE *file, Token **head, Token **tail){
    char *buffer = calloc(15, sizeof(char));
    int length = 0;
    
    int c;

    while ((c = fgetc(file)) != EOF) {
        //Vai verificar se o caractere é um delimitador, se sim, vai adicionar o token do buffer e o token do delimitador
        TokenTypes specificSpecialTokenType = TOKEN_NOTHING;
        TokenTypes generalSpecialTokenType = TOKEN_NOTHING;

        int isSpecialToken = CheckSpecialTokens(c, buffer, file, &generalSpecialTokenType, &specificSpecialTokenType);
        
        if (isspace(c) || isSpecialToken) {

            if (buffer[0]) {
                TokenTypes specificType = TOKEN_NOTHING;
                TokenTypes generalType = TOKEN_NOTHING;

                TokenTypeVerifications(buffer, &generalType, &specificType);

                AddToken(head, tail, buffer, generalType, specificType);

                buffer[0] = '\0';
                length = 0;
            }

            if (isSpecialToken) {
                char SpecialTokenBuffer[2] = {c, '\0'};

                AddToken(
                    head,
                    tail,
                    SpecialTokenBuffer,
                    generalSpecialTokenType,
                    specificSpecialTokenType
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

void AddToken(Token **head, Token **tail, char *text, TokenTypes generalType, TokenTypes specificType) {
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


void TokenTypeVerifications(char *buffer, TokenTypes *generalType, TokenTypes *specificType){ //PEga o token e faz verificações
    int stopChecking = 0;

    stopChecking = CheckPrimitiveTypes(buffer, generalType, specificType); 

    if(!stopChecking) {
        stopChecking = CheckVariablesComponent(buffer, generalType, specificType);
    }
    if(!stopChecking) {
        printf("Erro: assinatura ('%s') desconhecida \n", buffer);
        
        exit(EXIT_FAILURE);
    }
}

int CheckVariablesComponent(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
    TokenTypePair pair = GetType(buffer);
    *generalType = pair.generalType;
    *specificType = pair.specificType;

    if(pair.generalType == TOKEN_NOTHING && pair.specificType == TOKEN_NOTHING){
        printf("Erro: Token desconhecido '%s'\n", buffer);

        exit(EXIT_FAILURE);
    }

    return 1;
}

int CheckPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType){
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

    if(*specificType != TOKEN_NOTHING){
        *generalType = TYPE;
        
        return 1;
    }
    return 0;
}

int CheckOperators(char character, FILE *file, TokenTypes *generalType, TokenTypes *specificType){
    char nextCharacter = fgetc(file); //Pega o proximo caracter para verificações

    if(character == '=' && nextCharacter == '='){
        *specificType = COMPARE;
    }
    else{
        if(nextCharacter != EOF) {
            ungetc(nextCharacter, file); //Coloca o caractere de volta no arquivo se não for um operador de comparação
        }

        if(character == '='){
            *specificType = ASSIGNMENT;
        }
        else if(character == '+'){
            *specificType = PLUS;
        }
        else if(character == '-'){
            *specificType = MINUS;
        }
        else if(character == '*'){
            *specificType = MULTIPLY;
        }
        else if(character == '/'){
            *specificType = DIVIDE;
        }

        if(*specificType != TOKEN_NOTHING){
            *generalType = OPERATOR;
            
            return 1;
        }
    }
    return 0;
}

int CheckPunctuator(char character, TokenTypes *generalType, TokenTypes *specificType){
    if(character == ';'){
        *specificType = SEMICOLON;
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

    if(*specificType != TOKEN_NOTHING){
        *generalType = PUNCTUATOR;
        
        return 1;
    }

    return 0;
}

int CheckSpecialTokens(char character, char* buffer, FILE *file, TokenTypes *generalType, TokenTypes *specificType){
    if(CheckOperators(character, file, generalType, specificType) || CheckPunctuator(character, generalType, specificType)){
        return 1;
    }

    return 0;
}

TokenTypePair GetType(char *buffer){
    TokenTypePair types;

    types.specificType = TOKEN_NOTHING;
    types.generalType = TOKEN_NOTHING;

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
