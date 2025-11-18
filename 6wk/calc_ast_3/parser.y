%{
#include <stdio.h>
#include "ast.h"
int yylex(void);
void yyerror(const char *s);
AST *root;
%}

%code requires {  /* parser.tab.h에도 AST 타입 포함 */
  #include "ast.h"
}

%union {
    double num;
    AST *node;
}

%token <num> NUMBER
%type  <node> expr term factor

%right UPLUS UMINUS
%left '+' '-'
%left '*' '/'

%start input

%%

/* 여러 줄을 EOF까지 파싱 */
input
  : /* empty */
  | input line
  ;

line
  : expr ';' {
      /* AST 보기 (원하면 유지/제거) */
      print_ast($1, 0);

      /* 계산 */
      int err = 0;
      double result = eval($1, &err);   /* 내부에서 check() + eval_ast() 호출 */

      if (!err) {
        printf("= %.10g\n", result);
        fflush(stdout);
      }
      /* 메모리 해제 */
      free_ast($1);
    }
  | error ';' { yyerrok; }
  ;

/* 중위 표기 + 우선순위/결합규칙 */
expr
  : expr '+' term  { $$ = new_op(NODE_ADD, $1, $3); }
  | expr '-' term  { $$ = new_op(NODE_SUB, $1, $3); }
  | term
  ;

term
  : term '*' factor { $$ = new_op(NODE_MUL, $1, $3); }
  | term '/' factor { $$ = new_op(NODE_DIV, $1, $3); }
  | factor
  ;

factor
  : NUMBER                         { $$ = new_num($1); }
  | '(' expr ')'                   { $$ = $2; }
  | '-' factor   %prec UMINUS      { $$ = new_op(NODE_SUB, new_num(0), $2); }
  | '+' factor   %prec UPLUS       { $$ = $2; }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
