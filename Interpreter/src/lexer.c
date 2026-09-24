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

