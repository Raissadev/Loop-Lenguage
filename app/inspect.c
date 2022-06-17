#include "super/inspect.h"
#include "super/scope.h"
#include <stdio.h>
#include <string.h>

static syntax_T* builtin_function_print(inspec_T* inspec, syntax_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++) {
        syntax_T* inspected = inspect(inspec, args[i]);

        switch (inspected->type) {
            case DEF_STRING:
                 printf("%s\n", inspected->string_value);
                 break;
            default:
                printf("%p\n", inspected);
                break;
        }
    }

    return ___construct(DEF_NOOP);
}

static syntax_T* builtin_function_exit(inspec_T* inspec, syntax_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++) {
        syntax_T* inspected = inspect(inspec, args[i]);

        switch (inspected->type) {
            case DEF_NOOP:
                printf("You exited\n");
                exit(0);
                break;
            default:
                printf("%p\n", inspected);
                break;
        }
    }

    return ___construct(DEF_NOOP);
}

static syntax_T* builtin_function_clear(inspec_T* inspec, syntax_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++) {
        syntax_T* inspected = inspect(inspec, args[i]);

        switch (inspected->type) {
            case DEF_NOOP:
                system("clear");
                break;
            default:
                printf("%p\n", inspected);
                break;
        }
    }

    return ___construct(DEF_NOOP);
}

inspec_T* ____construct()
{
    inspec_T* inspec = calloc(1, sizeof(struct InspectStruct));

    return inspec;
}

syntax_T* inspect(inspec_T* inspec, syntax_T* node)
{
    switch (node->type) {
        case DEF_VARIABLE:
            return inspect_def_variable(inspec, node);
            break;
        case DEF_FUNCTION:
            return inspect_def_function(inspec, node);
            break;
        case DEF_VARIABLE_NAME:
            return inspect_variable(inspec, node);
            break;
        case DEF_FUNCTION_CALL:
            return inspect_function_call(inspec, node);
            break;
        case DEF_STRING:
            return inspect_string(inspec, node);
            break;
        case DEF_COMPOSE:
            return inspect_compose(inspec, node);
            break;
        case DEF_NOOP:
            return node;
            break;
    }

    printf("Uncaught statement of type `%d`\n", node->type);
    exit(1);

    return ___construct(DEF_NOOP);
}

syntax_T* inspect_def_variable(inspec_T* inspec, syntax_T* node)
{
    addVariable(node->scope, node); 

    return node;
}

syntax_T* inspect_def_function(inspec_T* inspec, syntax_T* node)
{
    addFunction(node->scope, node);

    return node;
}

syntax_T* inspect_variable(inspec_T* inspec, syntax_T* node)
{
    syntax_T* def = getFunctionVariable(
        node->scope,
        node->def_variable_name
    );
    
    if (def != (void*) 0)
        return inspect(inspec, def->def_value);

    printf("Undefined variable `%s`\n", node->def_variable_name);
    exit(1);
}

syntax_T* inspect_function_call(inspec_T* inspec, syntax_T* node)
{
    if (strcmp(node->def_call_name, "print") == 0)
        return builtin_function_print(
            inspec,
            node->def_call_arguments,
            node->def_arguments_size
        );

    if (strcmp(node->def_call_name, "exit") == 0)
        return builtin_function_exit(
            inspec,
            node->def_call_arguments,
            node->def_arguments_size
        );

    if (strcmp(node->def_call_name, "clear") == 0)
        return builtin_function_clear(
            inspec,
            node->def_call_arguments,
            node->def_arguments_size
        );

    syntax_T* def = getFunction(
        node->scope,
        node->def_call_name
    );

    if (def == (void*)0) {
        printf("Undefined method `%s`\n", node->def_call_name);
        exit(1);
    }

    for (int i = 0; i < (int) node->def_arguments_size; i++) {
        syntax_T* def_syntax_variable = (syntax_T*) def->def_function_args[i];

        syntax_T* value = (syntax_T*) node->def_call_arguments[i];

        syntax_T* def_variable = ___construct(DEF_VARIABLE);
        def_variable->def_value = value;

        def_variable->def_variable_name = (char*) calloc(strlen(def_syntax_variable->def_variable_name) + 1, sizeof(char));
        strcpy(def_variable->def_variable_name, def_syntax_variable->def_variable_name);

        addVariable(def->def_function_body->scope, def_variable);
    }
    
    return inspect(inspec, def->def_function_body);
}

syntax_T* inspect_string(inspec_T* inspec, syntax_T* node)
{
    return node;
}

syntax_T* inspect_compose(inspec_T* inspec, syntax_T* node)
{
    for (int i = 0; i < node->compose_size; i++)
        inspect(inspec, node->compose_value[i]);

    return ___construct(DEF_NOOP);
}
