%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"
#include "ir.h"
#include "eval.h"
#include "symtab.h"

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
          int ok = 0;
          int v = eval_expr($1, &ok);
          if (ok) {
              printf("= %d\n", v);
          }
          char* r = gen($1);
          (void)r; // 사용 안 해도 IR은 생성됨
          print_ir();
          printf("----\n");
          free_ir();
      }
    | INT_KW IDENT ';' {
          // 간단히 0으로 초기화
          sym_set($2, 0);
          printf("declare %s (init 0)\n", $2);
      }
    | IDENT '=' expr ';' {
          int ok = 0;
          int v = eval_expr($3, &ok);
          if (ok) {
              sym_set($1, v);
              printf("%s = %d\n", $1, v);
          }
          char* rhs = gen($3);
          emit(IR_MOV, $1, rhs, "");
          print_ir();
          printf("----\n");
          free_ir();
      }
    | PRINT_KW '(' IDENT ')' ';' {
          int v = 0;
          if (sym_get($3, &v)) {
              printf("%d\n", v);   // 실제 값 출력
          } else {
              fprintf(stderr, "runtime error: variable '%s' not initialized\n", $3);
          }
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
