#include <stdio.h>
#include <string.h>
#include "super/run.h"
#include "super/lexer.h"
#include "super/parser.h"
#include "super/inspect.h"
#include "super/io.h"
#include "super/help.h"

void runStream(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++) {
        
        int len = strlen(argv[i]);
        char* last = &argv[i][len-6];
        
        // if(strcmp(last,".loop") != 0) printHelp();

        lexer_T* lexer = _construct(stream(argv[i]));
        parser_T* parser = __construct(lexer);
        syntax_T* root = parse(parser, parser->scope);
        inspec_T* inspec = ____construct();

        inspect(inspec, root);
    }

    return;
}

void runTerminal(int max)
{
    char input[max];

    while (1) {
        printf("Welcome to the loop language v. 0.0.1!\nCreated by raissadev :)\n>>> ");
        fgets(input, max, stdin);
        lexer_T* lexer = _construct(input);
        parser_T* parser = __construct(lexer);
        syntax_T* root = parse(parser, parser->scope);
        inspec_T* inspec = ____construct();
        inspect(inspec, root);
    }

    return;
}