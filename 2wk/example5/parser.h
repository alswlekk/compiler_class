#ifndef PARSER_H
#define PARSER_H
#include "ast.h"
#include "lexer.h"
#include "token.h"

typedef struct {
    Lexer lx;
    Token cur;
} Parser;

void parser_init(Parser* ps, const char* src);
AST* parse_assign(Parser* ps); // assign-st: ident '=' exp ';'

#endif
