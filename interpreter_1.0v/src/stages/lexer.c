#include "stdio.h"
#include "stdlib.h"

#include "data/token_data/token_structs.h"

Token Lexer(FILE *file){
    char *word = NULL;

    do{
        char *word = ReadAllWord(file);

        //Tokenizer(word);
    }
    while(word != NULL);
}

char *ReadAllWord(FILE *file){
    char *buffer = malloc(15 * sizeof(char));
    int bufferLength = 0;

    int character;
    
    //Dá para a variavel character o proximo caracter 
    while((character = fgetc(file)) != EOF){
        //Se for um caracter de quebra de comando.
        if( NextCharacterIsBreakLine(character, buffer, bufferLength, file) ) continue;
        
        if( CharacterIsOperator(character) ) continue;
        
        //Prepara o array para o proximo char
        bufferLength++;
        buffer[bufferLength] = character;
    }
}

int NextCharacterIsBreakLine(int *character, char *buffer, int *bufferLength, FILE *file){
    int next = fgetc(file);

    if(next == '\n'){
        
        
        //Reseta o buffer
        buffer = malloc(15 * sizeof(char));
        bufferLength = 0;

        return 1;
    }

    ungetc(next, file);
}