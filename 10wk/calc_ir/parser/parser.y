%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"
#include "ir.h"

extern int yylex(void);
void yyerror(const char* s);
%}

// yylval에 들어갈 수 있는 타입을 정의:
// 정수 토큰은 ival
// expr 비단말은 AST* node
%union {
    int    ival;
    AST*   node;
}

%token <ival> NUMBER
%type  <node> expr

%left '+' '-'
%left '*' '/'

%%

input:
      /* empty */
    | input line
    ;

line:
      expr '\n' {
          char* r = gen($1);
          printf("Result in %s\n", r);
          print_ir();
          printf("----\n");
          free_ir();
      }
    | '\n'
    ;

expr:
      expr '+' expr { $$ = ast_bin(AST_ADD, $1, $3); }
    | expr '-' expr { $$ = ast_bin(AST_SUB, $1, $3); }
    | expr '*' expr { $$ = ast_bin(AST_MUL, $1, $3); }
    | expr '/' expr { $$ = ast_bin(AST_DIV, $1, $3); }
    | NUMBER        { $$ = ast_int($1); }
    | '(' expr ')'  { $$ = $2; }
    ;

%%

void yyerror(const char* s)
{
    fprintf(stderr, "parse error: %s\n", s);
}
