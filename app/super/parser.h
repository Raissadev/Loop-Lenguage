#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "scope.h"
#include "syntax.h"

typedef struct ParserStruct
{
    lexer_T* lexer;
    token_T* current;
    token_T* prev;
    scope_T* scope;
} parser_T;

parser_T* __construct(lexer_T* lexer);

void think(parser_T* parser, int token_type);

syntax_T* parse(parser_T* parser, scope_T* scope);

syntax_T* statement(parser_T* parser, scope_T* scope);

syntax_T* statements(parser_T* parser, scope_T* scope);

syntax_T* expression(parser_T* parser, scope_T* scope);

syntax_T* factor(parser_T* parser, scope_T* scope);

syntax_T* term(parser_T* parser, scope_T* scope);

syntax_T* functionCall(parser_T* parser, scope_T* scope);
        
syntax_T* variable(parser_T* parser, scope_T* scope);

syntax_T* function_(parser_T* parser, scope_T* scope);

syntax_T* parseVariable(parser_T* parser, scope_T* scope);

syntax_T* parseString(parser_T* parser, scope_T* scope);

syntax_T* parseId(parser_T* parser, scope_T* scope);

#endif
