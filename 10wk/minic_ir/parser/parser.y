%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"
#include "ir.h"

extern int yylex(void);
void yyerror(const char* s);
%}

%union {
    int    ival;
    AST*   node;
    char*  sval;
}

%token <ival> NUMBER
%token <sval> IDENT
%token INT_KW PRINT_KW

%type  <node> expr

%left '+' '-'
%left '*' '/'

%%

program:
      /* empty */
    | program stmt
    ;

stmt:
      expr ';' {
          char* r = gen($1);
          printf("expr result in %s\n", r);
          print_ir();
          printf("----\n");
          free_ir();
      }
    | INT_KW IDENT ';' {
          printf("declare %s\n", $2);
      }
    | IDENT '=' expr ';' {
          char* rhs = gen($3);
          emit(IR_MOV, $1, rhs, "");
          print_ir();
          printf("----\n");
          free_ir();
      }
    | PRINT_KW '(' IDENT ')' ';' {
          emit(IR_PRINT, "", $3, "");
          print_ir();
          printf("----\n");
          free_ir();
      }
    ;

expr:
      expr '+' expr { $$ = ast_bin(AST_ADD, $1, $3); }
    | expr '-' expr { $$ = ast_bin(AST_SUB, $1, $3); }
    | expr '*' expr { $$ = ast_bin(AST_MUL, $1, $3); }
    | expr '/' expr { $$ = ast_bin(AST_DIV, $1, $3); }
    | NUMBER        { $$ = ast_int($1); }
    | IDENT         { $$ = ast_var($1); }
    | '(' expr ')'  { $$ = $2; }
    ;

%%

void yyerror(const char* s)
{
    fprintf(stderr, "parse error: %s\n", s);
}
