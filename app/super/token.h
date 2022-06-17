#ifndef TOKEN_H
#define TOKEN_H

typedef struct TokenStruct
{
    enum
    {
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_STRING,
        TOKEN_SEMI,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_RBRACE,
        TOKEN_LBRACE,
        TOKEN_COMMA,
        TOKEN_EOF
    } type;

    char* value;
} token_T;

token_T* construct(int type, char* value);

#endif
