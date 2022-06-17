#include "super/token.h"
#include <stdlib.h>

token_T* construct(int type, char* value)
{
    token_T* token = calloc(1, sizeof(struct TokenStruct));
    token->type = type;
    token->value = value;

    return token;
}
