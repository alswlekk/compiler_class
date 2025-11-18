%{
#include <stdio.h>
#include <stdlib.h>

/* yylex/yyerror 전방선언 */
int yylex(void);
void yyerror(const char *s);
%}

/* === 토큰/타입 정의 === */
%union {
  int ival;      /* 정수 값 보관 */
}

/* lexer가 넘겨줄 토큰들 */
%token <ival> T_NUMBER
%left '+'          /* + 는 좌결합, 낮은 우선순위 */
%left '*'          /* * 는 좌결합, 높은 우선순위 */

/* 비단말의 타입 */
%type  <ival> expr

/* 시작 기호 지정 (선택: 기본은 첫 규칙의 LHS) */
%start input

%%

/* === 문법 규칙 & 의미동작 === */

/* 여러 줄 입력을 처리: 한 줄(또는 하나의 식)마다 결과 출력 */
input
    : /* empty */
    | input expr              { printf("%d\n", $2); }
    ;

expr
    : expr '+' expr           { $$ = $1 + $3; }
    | expr '*' expr           { $$ = $1 * $3; }
    | '(' expr ')'            { $$ = $2; }
    | T_NUMBER                { $$ = $1; }
    ;

%%

/* === 에러 처리 === */
void yyerror(const char *s) {
    fprintf(stderr, "parse error: %s\n", s);
}

int main(void) {
    /* 표준입력에서 계속 읽어 계산 결과를 줄단위로 출력 */
    return yyparse();
}
