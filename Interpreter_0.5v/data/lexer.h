#include "token.h"

void Lexer(FILE *file, Token **head, Token **tail);

void TokenTypeVerifications(char *buffer, TokenTypes *generalType, TokenTypes *specificType);

int CheckVariablesComponent(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int CheckPrimitiveTypes(char *buffer, TokenTypes *generalType, TokenTypes *specificType);
int CheckOperators(char character, FILE *file, TokenTypes *generalType, TokenTypes *specificType);
int CheckPunctuator(char character, TokenTypes *generalType, TokenTypes *specificType);
int CheckSpecialTokens(char character, char* buffer, FILE *file, TokenTypes *generalType, TokenTypes *specificType);

TokenTypePair GetType(char *buffer);