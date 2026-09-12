#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenTypes {
    NOTHING,

    //TOKENS GERAIS
    VALUE,
    NAME,
    TYPE,
    OPERATOR,
    IDENTIFIER,
    PUNCTUATOR,
    DELIMITER,

    //TIPOS PRIMITIVOS
    TYPE_INT,
    TYPE_BOOL,
    TYPE_TEXT,
    TYPE_FLOAT,
    TYPE_NULL,

    //PONTUADORES
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    OPEN_BRACE,
    CLOSE_BRACE,

    //OPERADORES: 
    COMPARE,
    ASSIGNMENT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
} TokenTypes;

typedef struct Token {
    char *text;
    TokenTypes specificType;
    TokenTypes geralType;
    struct Token *nextNode;
} Token;

typedef struct TokenTypePair { //Para retornar dois tipos de token ao mesmo tempo
    TokenTypes generalType;
    TokenTypes specificType;
} TokenTypePair;

static inline const char *token_type_name(TokenTypes t) {
    switch (t) {
        case NOTHING:           return "NOTHING";
        case VALUE:             return "VALUE";
        case NAME:              return "NAME";
        case TYPE:              return "TYPE";
        case OPERATOR:          return "OPERATOR";
        case TYPE_INT:          return "TYPE_INT";
        case TYPE_BOOL:         return "TYPE_BOOL";
        case TYPE_TEXT:         return "TYPE_TEXT";
        case TYPE_FLOAT:        return "TYPE_FLOAT";
        case TYPE_NULL:         return "TYPE_NULL";
        case IDENTIFIER:        return "IDENTIFIER";
        case DELIMITER:         return "DELIMITER";
        case OPEN_PARENTHESIS:  return "OPEN_PARENTHESIS";
        case CLOSE_PARENTHESIS: return "CLOSE_PARENTHESIS";
        case OPEN_BRACE:        return "OPEN_BRACE";
        case CLOSE_BRACE:       return "CLOSE_BRACE";
        case COMPARE:           return "COMPARE";
        case ASSIGNMENT:        return "ASSIGNMENT";
        case PLUS:              return "PLUS";
        case MINUS:             return "MINUS";
        case MULTIPLY:          return "MULTIPLY";
        case DIVIDE:            return "DIVIDE";
        default:                return "UNKNOWN";
    }
}


#endif