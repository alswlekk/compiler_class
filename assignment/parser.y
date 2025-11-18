%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* lexer / error */
int yylex(void);
void yyerror(const char *s);

/* --- 심볼테이블(실수형 버전) --- */
typedef struct Sym {
  char *name;
  double   value;
  struct Sym *next;
} Sym;

static Sym *symtab = NULL;

/* show문 여부 플래그 */
int show_mode = 0;

static Sym* lookup(const char *name){
  for (Sym *p = symtab; p; p = p->next)
    if (strcmp(p->name, name) == 0) return p;
  return NULL;
}
static double getval(const char *name){
  Sym *s = lookup(name);
  if (!s) {
    fprintf(stderr, "undefined variable: %s\n", name);
    return 0;
  }
  return s->value;
}

static void setval(const char *name, double v){
  Sym *s = lookup(name);
  if (!s) {
    s = (Sym*)malloc(sizeof(Sym));
    s->name = strdup(name);
    s->next = symtab;
    symtab = s;
  }
  s->value = v;
}
%}

/* --- 토큰/타입 --- */
%union { double dval; char *sval; }

%token <dval> T_NUMBER
%token <sval> T_ID
%token        T_SHOW 
%token        T_END 

%left '+' '-'
%left '*' '/' '%'
%right UMINUS
%nonassoc '(' ')' 

%type <dval> expr stmt
%start input

%%

/* 줄 단위로 즉시 reduce → 출력 */
input
  : /* empty */
  | input line
  ;

line
  : stmt T_END              {
     if (!show_mode)           /* show문이 아닐 때만 출력 */
        printf("%g\n", $1);
      show_mode = 0;            /* 다음 문장 위해 초기화 */
     }
  | T_END                   { /* 빈 줄 무시 */ }
  | error T_END             { yyerrok; /* 에러 줄 스킵 */ }
  ;

stmt
  : expr                   { $$ = $1; }
  | T_ID '=' expr          { setval($1, $3); $$ = $3; free($1); }
  | T_SHOW expr { 
    extern char current_expr[];   /* scanner.l에 선언된 전역 변수 사용 */
    show_mode = 1;
    printf("%s = %g\n", current_expr, $2); 
    $$ = $2; 
  }
  ;

expr
  : expr '+' expr          { $$ = $1 + $3; }
  | expr '-' expr          { $$ = $1 - $3; }
  | expr '*' expr          { $$ = $1 * $3; }
  | expr '/' expr            { if ($3 == 0) { yyerror("division by zero"); $$ = 0; } else $$ = $1 / $3; } // 나눗셈 기능 추가
  | expr '%' expr { 
    if ((int)$3 == 0) { yyerror("mod by zero"); $$ = 0; } 
    else $$ = (int)$1 % (int)$3; 
}
  | '-' expr %prec UMINUS  { $$ = -$2; }
  | '(' expr ')'           { $$ = $2; }
  | T_NUMBER               { $$ = $1; }
  | T_ID                   { $$ = getval($1); free($1); }
  ;

%%

void yyerror(const char *s){ fprintf(stderr, "parse error: %s\n", s); }

int main(void){
  return yyparse();
}
