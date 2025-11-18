%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- 아주 단순한 심볼 테이블 --- */
typedef struct { char *name; double value; } binding_t;
static binding_t table[256];
static int tsize = 0;

static double getvar(const char *name) {
    for (int i = 0; i < tsize; ++i)
        if (strcmp(table[i].name, name) == 0) return table[i].value;
    return 0.0; /* 선언 없는 변수는 0으로 */
}

static void setvar(const char *name, double v) {
    for (int i = 0; i < tsize; ++i)
        if (strcmp(table[i].name, name) == 0) { table[i].value = v; return; }
    if (tsize < (int)(sizeof(table)/sizeof(table[0]))) {
        table[tsize].name = strdup(name);
        table[tsize].value = v;
        ++tsize;
    }
}

int yylex(void);
void yyerror(const char *s) { fprintf(stderr, "syntax error: %s\n", s); }
%}

/* --- yylval 타입 --- */
%union {
    double num;   /* NUMBER의 값 */
    char  *id;    /* IDENT의 문자열 */
}

/* --- 토큰(스캐너가 반환) --- */
%token <num> NUMBER
%token <id>  IDENT

/* --- 연산자 우선순위/결합성 --- */
%left '+' '-'
%left '*' '/'

/* --- 비단말 타입 --- */
%type <num> expr term factor

%%

input
    : /* empty */
    | input line
    ;

line
    : '\n'
    | expr '\n'          { printf("= %g\n", $1); }
    | IDENT '=' expr '\n'{
          setvar($1, $3);
          printf("%s = %g\n", $1, $3);
          free($1);
      }
    ;

expr
    : expr '+' term      { $$ = $1 + $3; }
    | expr '-' term      { $$ = $1 - $3; }
    | term
    ;

term
    : term '*' factor    { $$ = $1 * $3; }
    | term '/' factor    {
          if ($3 == 0) { fprintf(stderr, "division by zero\n"); $$ = 0.0; }
          else $$ = $1 / $3;
      }
    | factor
    ;

factor
    : NUMBER             { $$ = $1; }
    | IDENT              { $$ = getvar($1); free($1); }
    | '(' expr ')'       { $$ = $2; }
    ;

%%

int main(void) {
    printf("Mini calc: + - * /, variables (e.g., x=1+2).  Ctrl+D to quit.\n");
    return yyparse();
}

