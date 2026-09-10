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
    TYPE_TEXT,
    TYPE_FLOAT,
    TYPE_NULL,

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


static inline const char *token_type_name(TokenTypes t) {
    switch (t) {
        case NOTHING:       return "NOTHING";
        case VALUE:         return "VALUE";
        case NAME:          return "NAME";
        case TYPE:          return "TYPE";
        case OPERATOR:      return "OPERATOR";
        case END:           return "END";
        case TYPE_INT:      return "TYPE_INT";
        case TYPE_BOOL:     return "TYPE_BOOL";
        case TYPE_TEXT:     return "TYPE_TEXT";
        case TYPE_FLOAT:    return "TYPE_FLOAT";
        case TYPE_NULL:     return "TYPE_NULL";
        case VARIABLE_NAME: return "VARIABLE_NAME";
        case COMPARE:       return "COMPARE";
        case ATTRIBUTION:   return "ATTRIBUTION";
        case SUM:           return "SUM";
        case SUBTRACT:      return "SUBTRACT";
        case MULTIPLY:      return "MULTIPLY";
        case DIVIDE:        return "DIVIDE";
        default:            return "UNKNOWN";
    }
}


#endif