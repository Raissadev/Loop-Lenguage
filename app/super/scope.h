#ifndef SCOPE_H
#define SCOPE_H
#include "syntax.h"

typedef struct SCOPE_STRUCT
{
    syntax_T** def_functions;
    size_t def_functions_size;

    syntax_T** def_variables;
    size_t def_variables_size;
} scope_T;

scope_T* _____construct();

syntax_T* addFunction(scope_T* scope, syntax_T* def);

syntax_T* getFunction(scope_T* scope, const char* name);

syntax_T* addVariable(scope_T* scope, syntax_T* def);

syntax_T* getFunctionVariable(scope_T* scope, const char* name);

#endif
