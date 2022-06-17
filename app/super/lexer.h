#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct LexerStruct
{
    char c;
    unsigned int i;
    char* contents;
} lexer_T;

lexer_T* _construct(char* contents);

void advance(lexer_T* lexer);

void skip(lexer_T* lexer);

token_T* nextToken(lexer_T* lexer);

token_T* collectString(lexer_T* lexer);

token_T* collectId(lexer_T* lexer);

token_T* advanceToken(lexer_T* lexer, token_T* token);

char* currentChar(lexer_T* lexer);

#endif
