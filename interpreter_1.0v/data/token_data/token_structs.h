#include "data/token_data/token_types.h"

typedef struct Token
{
    char *text; //TEXTO DIGITADO
    int line;
    TokenTypes type; //TIPO DE TEXTO IDENTIFICADO
    struct Token *next; //PROXIMO TOKEN
} Token;
