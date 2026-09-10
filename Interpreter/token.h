#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenTypes {
    NOTHING,

    //TOKENS GERAIS
    VALUE,
    NAME,
    TYPE,
    OPERATOR,
    END,

    //TIPOS PRIMITIVOS
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,

    //DECLARATIONS
    VARIABLE_NAME,

    //OPERADORES: 
    COMPARE,
    ATTRIBUTION,
    SUM,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
} TokenTypes;

typedef struct Token {
    char *text;
    TokenTypes specificType;
    TokenTypes geralType;
    struct Token *nextNode;
} Token;


#endif