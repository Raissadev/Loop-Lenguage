#include "super/lexer.h"
#include "super/token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

lexer_T* _construct(char* contents)
{
    lexer_T* lexer = calloc(1, sizeof(struct LexerStruct));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void advance(lexer_T* lexer)
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

void skip(lexer_T* lexer)
{
    while (lexer->c == ' ' || lexer->c == 10) {
        advance(lexer);
    }
}

token_T* nextToken(lexer_T* lexer)
{
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {

        if (lexer->c == ' ' || lexer->c == 10) skip(lexer);

        if (isalnum(lexer->c)) return collectId(lexer);

        if (lexer->c == '"') return collectString(lexer);

        switch (lexer->c) {
            case '=':
                return advanceToken(lexer, construct(TOKEN_EQUALS, currentChar(lexer)));
                break;
            case ';':
                return advanceToken(lexer, construct(TOKEN_SEMI, currentChar(lexer)));
                break;
            case '(':
                return advanceToken(lexer, construct(TOKEN_LPAREN, currentChar(lexer)));
                break;
            case ')':
                return advanceToken(lexer, construct(TOKEN_RPAREN, currentChar(lexer)));
                break;
            case '{':
                return advanceToken(lexer, construct(TOKEN_LBRACE, currentChar(lexer)));
                break;
            case '}':
                return advanceToken(lexer, construct(TOKEN_RBRACE, currentChar(lexer)));
                break;
            case ',':
                return advanceToken(lexer, construct(TOKEN_COMMA, currentChar(lexer)));
                break;
        }
    }

    return construct(TOKEN_EOF, "\0");
}

token_T* collectString(lexer_T* lexer)
{
    advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '"') {
        char* _char = currentChar(lexer);
        value = realloc(value, (strlen(value) + strlen(_char) + 1) * sizeof(char));
        strcat(value, _char);

        advance(lexer);
    }

    advance(lexer);

    return construct(TOKEN_STRING, value);
}

token_T* collectId(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c)) {
        char* _char = currentChar(lexer);
        value = realloc(value, (strlen(value) + strlen(_char) + 1) * sizeof(char));
        strcat(value, _char);

        advance(lexer);
    }

    return construct(TOKEN_ID, value);
}

token_T* advanceToken(lexer_T* lexer, token_T* token)
{
    advance(lexer);

    return token;
}

char* currentChar(lexer_T* lexer)
{
    char* index = calloc(2, sizeof(char));
    index[0] = lexer->c;
    index[1] = '\0';

    return index;
}
