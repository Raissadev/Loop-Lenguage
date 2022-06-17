#include "super/scope.h"
#include <string.h>

scope_T* _____construct()
{
    scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT));

    scope->def_functions = (void*) 0;
    scope->def_functions_size = 0;

    scope->def_variables = (void*) 0;
    scope->def_variables_size = 0;

    return scope;
}

syntax_T* addFunction(scope_T* scope, syntax_T* def)
{
    scope->def_functions_size += 1;

    if (scope->def_functions == (void*)0) {
        scope->def_functions = calloc(1, sizeof(struct SyntaxStruct*));
    } else {
        scope->def_functions =
            realloc(
                scope->def_functions,
                scope->def_functions_size * sizeof(struct SyntaxStruct**)
            );
    }

    scope->def_functions[scope->def_functions_size-1] = def;

    return def;
}

syntax_T* getFunction(scope_T* scope, const char* name)
{
    for (int i = 0; i < scope->def_functions_size; i++) {
        syntax_T* def = scope->def_functions[i];

        if (strcmp(def->def_function_name, name) == 0)
            return def;
    }

    return (void*)0;
}

syntax_T* addVariable(scope_T* scope, syntax_T* def)
{
    if (scope->def_variables == (void*) 0) {
        scope->def_variables = calloc(1, sizeof(struct SyntaxStruct*));
        scope->def_variables[0] = def;
        scope->def_variables_size += 1;
    } else {
        scope->def_variables_size += 1;
        scope->def_variables = realloc(
            scope->def_variables,
            scope->def_variables_size * sizeof(struct SyntaxStruct*)  
        );
        scope->def_variables[scope->def_variables_size-1] = def;
    }

    return def;
}

syntax_T* getFunctionVariable(scope_T* scope, const char* name)
{
    for (int i = 0; i < scope->def_variables_size; i++) {
        syntax_T* def = scope->def_variables[i];

        if (strcmp(def->def_variable_name, name) == 0)
            return def;
    }

    return (void*)0;
}
