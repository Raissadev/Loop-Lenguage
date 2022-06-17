#include "super/syntax.h"
#include <stdlib.h>

syntax_T* ___construct(int type)
{
    syntax_T* syntax = calloc(1, sizeof(struct SyntaxStruct));
    syntax->type = type;

    syntax->scope = (void*) 0;

    syntax->def_variable_name = (void*) 0;
    syntax->def_value = (void*) 0;

    syntax->def_function_body = (void*) 0;
    syntax->def_function_name = (void*) 0;
    syntax->def_function_args = (void*) 0;
    syntax->def_function_args_size = 0;

    syntax->def_variable_name = (void*) 0;

    syntax->def_call_name = (void*) 0;
    syntax->def_call_arguments = (void*) 0;
    syntax->def_arguments_size = 0;

    syntax->string_value = (void*) 0;

    syntax->compose_value = (void*) 0;
    syntax->compose_size = 0;

    return syntax;
}
