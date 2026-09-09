#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenTypes {
    //TOKENS GERAIS
    VARIABLE,
    TYPE,
    OPERATOR,
    END,

    //TIPOS PRIMITIVOS
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,

    //DECLARATIONS
    VARIABLE_NAME,
    VARIABLE_VALUE,

    //OPERADORES: 
    COMPARE,
    IGUALS,

    NOTHING = 0
} TokenTypes;

typedef struct Token {
    char *text;
    TokenTypes specificType;
    TokenTypes geralType;
    struct Token *nextNode;
} Token;

#endif