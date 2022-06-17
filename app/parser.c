#include "super/parser.h"
#include "super/scope.h"
#include "super/token.h"
#include <stdio.h>
#include <string.h>


parser_T* __construct(lexer_T* lexer)
{
    parser_T* parser = calloc(1, sizeof(struct ParserStruct));
    parser->lexer = lexer;
    parser->current = nextToken(lexer);
    parser->prev = parser->current;

    parser->scope = _____construct();

    return parser;
}

void think(parser_T* parser, int type)
{
    if (!parser->current->type == type) {
        printf("Unexpected token `%s`, with type %d", parser->current->value, parser->current->type);
        exit(1);
    }

    parser->prev = parser->current;
    parser->current = nextToken(parser->lexer);
}

syntax_T* parse(parser_T* parser, scope_T* scope)
{
    return statements(parser, scope);
}

syntax_T* statement(parser_T* parser, scope_T* scope)
{
    switch (parser->current->type) {
        case TOKEN_ID:
            return parseId(parser, scope);
    }

    return ___construct(DEF_NOOP);
}

syntax_T* statements(parser_T* parser, scope_T* scope)
{
    syntax_T* compose = ___construct(DEF_COMPOSE);
    
    compose->scope = scope;
    compose->compose_value = calloc(1, sizeof(struct SyntaxStruct*));

    syntax_T* dock = statement(parser, scope);
    dock->scope = scope;
    compose->compose_value[0] = dock;
    compose->compose_size += 1;

    while (parser->current->type == TOKEN_SEMI) {
        think(parser, TOKEN_SEMI);

        syntax_T* dock = statement(parser, scope);

        if (dock) {
            compose->compose_size += 1;
            compose->compose_value = realloc(
                compose->compose_value,
                compose->compose_size * sizeof(struct SyntaxStruct*)
            );
            compose->compose_value[compose->compose_size-1] = dock;
        }
    }

    return compose;
}

syntax_T* expression(parser_T* parser, scope_T* scope)
{
    switch (parser->current->type) {
        case TOKEN_STRING:
            return parseString(parser, scope);
        case TOKEN_ID:
            return parseId(parser, scope);
    }

    return ___construct(DEF_NOOP);
}

syntax_T* factor(parser_T* parser, scope_T* scope)
{
}

syntax_T* term(parser_T* parser, scope_T* scope)
{
}

syntax_T* functionCall(parser_T* parser, scope_T* scope)
{
    syntax_T* function = ___construct(DEF_FUNCTION_CALL);

    function->def_call_name = parser->prev->value;
    think(parser, TOKEN_LPAREN); 

    function->def_call_arguments = calloc(1, sizeof(struct SyntaxStruct*));

    syntax_T* syntax = expression(parser, scope);
    function->def_call_arguments[0] = syntax;
    function->def_arguments_size += 1;

    while (parser->current->type == TOKEN_COMMA) {
        think(parser, TOKEN_COMMA);

        syntax_T* syntax = expression(parser, scope);
        function->def_arguments_size += 1;
        function->def_call_arguments = realloc(
            function->def_call_arguments,
            function->def_arguments_size * sizeof(struct SyntaxStruct*)
        );
        function->def_call_arguments[function->def_arguments_size-1] = syntax;
    }

    think(parser, TOKEN_RPAREN);

    function->scope = scope;

    return function;
}

syntax_T* variable(parser_T* parser, scope_T* scope)
{
    think(parser, TOKEN_ID);
    char* variable = parser->current->value;
    
    think(parser, TOKEN_ID);
    think(parser, TOKEN_EQUALS);
    syntax_T* def_value = expression(parser, scope);

    syntax_T* def_variable = ___construct(DEF_VARIABLE);
    def_variable->def_variable_name = variable;
    def_variable->def_value = def_value;

    def_variable->scope = scope;

    return def_variable;
}

syntax_T* function_(parser_T* parser, scope_T* scope)
{
    syntax_T* syntax = ___construct(DEF_FUNCTION);
    think(parser, TOKEN_ID);

    char* def_function_name = parser->current->value;
    syntax->def_function_name = calloc(
            strlen(def_function_name) + 1, sizeof(char)
    );

    strcpy(syntax->def_function_name, def_function_name);

    think(parser, TOKEN_ID);

    think(parser, TOKEN_LPAREN);

    syntax->def_function_args = calloc(1, sizeof(struct SyntaxStruct*));

    syntax_T* arg = parseVariable(parser, scope);
    syntax->def_function_args_size += 1;
    syntax->def_function_args[syntax->def_function_args_size-1] = arg;

    while (parser->current->type == TOKEN_COMMA) {
        think(parser, TOKEN_COMMA);

        syntax->def_function_args_size += 1;

        syntax->def_function_args =
            realloc(
                    syntax->def_function_args,
                    syntax->def_function_args_size * sizeof(struct SyntaxStruct*)
                   );

        syntax_T* arg = parseVariable(parser, scope);
        syntax->def_function_args[syntax->def_function_args_size-1] = arg;
    }

    think(parser, TOKEN_RPAREN);
    
    think(parser, TOKEN_LBRACE);
    
    syntax->def_function_body = statements(parser, scope);

    think(parser, TOKEN_RBRACE);

    syntax->scope = scope;

    return syntax;
}

syntax_T* parseVariable(parser_T* parser, scope_T* scope)
{
    char* token = parser->current->value;
    think(parser, TOKEN_ID);

    if (parser->current->type == TOKEN_LPAREN)
        return functionCall(parser, scope);

    syntax_T* variable = ___construct(DEF_VARIABLE_NAME);
    variable->def_variable_name = token;

    variable->scope = scope;

    return variable;
}

syntax_T* parseString(parser_T* parser, scope_T* scope)
{
    syntax_T* string = ___construct(DEF_STRING);
    string->string_value = parser->current->value;

    think(parser, TOKEN_STRING);

    string->scope = scope;

    return string;
}

syntax_T* parseId(parser_T* parser, scope_T* scope)
{
    if (strcmp(parser->current->value, "var") == 0)
        return variable(parser, scope);

    if (strcmp(parser->current->value, "function") == 0)
        return function_(parser, scope);
    
    return parseVariable(parser, scope);
}
