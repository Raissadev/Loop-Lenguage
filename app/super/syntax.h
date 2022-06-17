#ifndef SYNTAX_H
#define SYNTAX_H
#include <stdlib.h>

typedef struct SyntaxStruct
{
    enum {
        DEF_VARIABLE,
        DEF_FUNCTION,
        DEF_VARIABLE_NAME,
        DEF_FUNCTION_CALL,
        DEF_STRING,
        DEF_COMPOSE,
        DEF_NOOP
    } type;

    struct SCOPE_STRUCT* scope;

    char* def_variable_name;
    struct SyntaxStruct* def_value;

    struct SyntaxStruct* def_function_body;
    char* def_function_name;
    struct SyntaxStruct** def_function_args;
    size_t def_function_args_size;

    char* variable_name;

    char* def_call_name;
    struct SyntaxStruct** def_call_arguments;
    size_t def_arguments_size;

    char* string_value;

    struct SyntaxStruct** compose_value;
    size_t compose_size;
} syntax_T;

syntax_T* ___construct(int type);

#endif
