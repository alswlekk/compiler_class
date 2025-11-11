%{
  /* 파서에서 사용할 C 헤더 및 심볼 선언 */
  #include <stdio.h>    // fprintf 등 에러 출력용
  #include <stdlib.h>   // calloc/free 등 동적 메모리
  #include <string.h>
  #include "ast.h"      // AST 노드 타입/함수

  extern int yylex(void);     // Flex가 생성하는 렉서 함수
  extern int yylineno;        // Flex의 현재 소스 코드 라인 번호
  void yyerror(const char *s); // 에러 리포팅 함수 (아래에서 정의)

  Node *root = NULL;    // 전체 파싱 결과 AST 루트 저장용
%}

/* 파서 외부에서(헤더로) 노출해야 하는 선언을 넣는 섹션 */
%code requires {
  #include "ast.h"
}

/* Bison의 값 타입을 Node* 로 지정: 각 토큰/비단말의 semantic value가 AST 노드 포인터 */
%define api.value.type {Node*}
/* 자세한 에러 메시지(기대 토큰 등) 출력 */
%define parse.error verbose

/* -------------------------------------------------------
 * 토큰(단말 기호) 선언
 *  - lexer.l(lex)에서 반환하는 토큰명과 반드시 일치해야 함
 * ----------------------------------------------------- */
%token IDENT
%token INT_CONST FLOAT_CONST CHAR_CONST STRING_LITERAL

%token INT FLOAT CHAR VOID
%token IF ELSE WHILE RETURN

%token EQ  /* == */
%token NE  /* != */
%token LE  /* <= */
%token GE  /* >= */
%token AND /* && */
%token OR  /* || */

/* -------------------------------------------------------
 * 연산자 우선순위 및 결합 규칙
 *  - 아래에서 정의한 순서가 낮은 것부터 높은 순으로 평가됨
 *  - %left/%right: 결합성 (좌/우 결합)
 * ----------------------------------------------------- */
%left OR
%left AND
%left '|' '^' '&'
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!' '~' /* unary */
%right '='     /* assignment */

/* -------------------------------------------------------
 * dangling else 해결:
 *   IF (cond) stmt
 *   IF (cond) stmt ELSE stmt
 *   두 규칙 간의 shift/reduce 충돌을 해소하기 위해,
 *   ELSE보다 낮은 우선순위를 갖는 가상 토큰을 부여
 * ----------------------------------------------------- */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* ---- 시작 기호 ---- */
%start translation_unit

/* ===================== 문법 규칙(Grammar) 영역 시작 ===================== */
%%

/* 프로그램 전체(translation unit).
 * - 여러 개의 external_decl(함수 정의나 전역 선언)을 순차적으로 누적
 */
translation_unit
  : /* empty */                        { $$ = node(NK_TRANSLATION_UNIT, yylineno, NULL, 0); root = $$; }
  | translation_unit external_decl     {
        /* 누적된 노드 리스트 뒤에 새 external_decl 자식 추가 */
        Node **arr = (Node**)calloc($1->nchild+1, sizeof(Node*));
        for(int i=0;i<$1->nchild;i++) arr[i]=$1->child[i];
        arr[$1->nchild]=$2;

        /* nodev: 이미 구성된 배열을 자식으로 하는 새 노드 생성 */
        $$ = nodev(NK_TRANSLATION_UNIT, yylineno, NULL, $1->nchild+1, arr);

        /* 이전 wrapper 노드의 child 배열/자원 정리(중첩 래핑 방지) */
        free($1->child); $1->child=NULL; $1->nchild=0; free($1);

        root = $$;  /* 최신 루트를 전역에 갱신 */
    }
  ;

/* 최상위 선언: 함수 정의 또는 변수 선언 */
external_decl
  : function_definition
  | declaration
  ;

/* 함수 정의
 *   type_spec IDENT '(' param_list_opt ')' compound_stmt
 *   - op 필드로 함수명(식별자 문자열)을 보관
 *   - 자식: [0] 반환 타입, [1] 파라미터 목록, [2] 본문 블록
 */
function_definition
  : type_spec IDENT '(' param_list_opt ')' compound_stmt
    { $$ = node(NK_FUNC_DEF, yylineno, $2->op, 3, $1, $4, $6); free_ast($2); }
  ;

/* 파라미터 목록 (비어있을 수도 있음) */
param_list_opt
  : /* empty */       { $$ = node(NK_PARAM_LIST, yylineno, NULL, 0); }
  | param_list
  ;

/* 파라미터들의 시퀀스: 콤마로 확장 누적 */
param_list
  : param_decl
    { $$ = node(NK_PARAM_LIST, yylineno, NULL, 1, $1); }
  | param_list ',' param_decl
    {
      Node **arr = (Node**)calloc($1->nchild+1, sizeof(Node*));
      for(int i=0;i<$1->nchild;i++) arr[i]=$1->child[i];
      arr[$1->nchild] = $3;
      $$ = nodev(NK_PARAM_LIST, yylineno, NULL, $1->nchild+1, arr);
      free($1->child); $1->child=NULL; $1->nchild=0; free($1);
    }
  ;

/* 단일 파라미터: 타입 + 식별자 */
param_decl
  : type_spec IDENT { $$ = node(NK_PARAM, yylineno, $2->op, 1, $1); free_ast($2); }
  ;

/* 변수 선언문 (여러 개 초기화 선언을 ; 로 끝냄) */
declaration
  : type_spec init_declarator_list ';'
    { $$ = node(NK_DECL, yylineno, NULL, 2, $1, $2); }
  ;

/* 초기화 선언자들의 목록: 콤마로 확장 */
init_declarator_list
  : init_declarator
    { $$ = node(NK_INIT_DECL_LIST, yylineno, NULL, 1, $1); }
  | init_declarator_list ',' init_declarator
    {
      Node **arr = (Node**)calloc($1->nchild+1, sizeof(Node*));
      for(int i=0;i<$1->nchild;i++) arr[i]=$1->child[i];
      arr[$1->nchild] = $3;
      $$ = nodev(NK_INIT_DECL_LIST, yylineno, NULL, $1->nchild+1, arr);
      free($1->child); $1->child=NULL; $1->nchild=0; free($1);
    }
  ;

/* 단일 초기화 선언:
 *   IDENT
 *   IDENT '=' assignment
 *   - op 필드에 변수명 저장, 자식[0]에 초기화 식(있다면) 저장
 */
init_declarator
  : IDENT                { $$ = node(NK_INIT_DECL, yylineno, $1->op, 1, NULL); free_ast($1); }
  | IDENT '=' assignment { $$ = node(NK_INIT_DECL, yylineno, $1->op, 1, $3);   free_ast($1); }
  ;

/* 타입 지정자 */
type_spec
  : INT   { $$ = node(NK_TYPE, yylineno, "int", 0); }
  | FLOAT { $$ = node(NK_TYPE, yylineno, "float", 0); }
  | CHAR  { $$ = node(NK_TYPE, yylineno, "char", 0); }
  | VOID  { $$ = node(NK_TYPE, yylineno, "void", 0); }
  ;

/* 블록문 { ... } : 내부에 stmt/decl 리스트 하나를 자식으로 둔다 */
compound_stmt
  : '{' stmt_decl_list_opt '}' { $$ = node(NK_COMPOUND, yylineno, NULL, 1, $2); }
  ;

/* 블록 내부가 비어있을 수도 있음 */
stmt_decl_list_opt
  : /* empty */                   { $$ = node(NK_STMT_LIST, yylineno, NULL, 0); }
  | stmt_decl_list
  ;

/* 문/선언의 시퀀스를 누적 */
stmt_decl_list
  : stmt_or_decl
    { $$ = node(NK_STMT_LIST, yylineno, NULL, 1, $1); }
  | stmt_decl_list stmt_or_decl
    {
      Node **arr = (Node**)calloc($1->nchild+1, sizeof(Node*));
      for(int i=0;i<$1->nchild;i++) arr[i]=$1->child[i];
      arr[$1->nchild] = $2;
      $$ = nodev(NK_STMT_LIST, yylineno, NULL, $1->nchild+1, arr);
      free($1->child); $1->child=NULL; $1->nchild=0; free($1);
    }
  ;

/* 문(statement) 또는 선언(복합문 안에서 둘 다 허용) */
stmt_or_decl
  : statement
  | declaration
  ;

/* 단일 문(statement)들 */
statement
  : ';'                         { $$ = node(NK_EXPR_STMT, yylineno, NULL, 0); }               /* 빈문 */
  | expr ';'                    { $$ = node(NK_EXPR_STMT, yylineno, NULL, 1, $1); }           /* 표현식 문 */
  | RETURN ';'                  { $$ = node(NK_RETURN,    yylineno, NULL, 0); }
  | RETURN expr ';'             { $$ = node(NK_RETURN,    yylineno, NULL, 1, $2); }
  /* else가 없는 if: LOWER_THAN_ELSE 우선순위로 dangling else 방지 */
  | IF '(' expr ')' statement %prec LOWER_THAN_ELSE { $$ = node(NK_IF, yylineno, NULL, 2, $3, $5); }
  /* else가 있는 if */
  | IF '(' expr ')' statement ELSE statement
                                { $$ = node(NK_IF, yylineno, "else", 3, $3, $5, $7); }
  | WHILE '(' expr ')' statement{ $$ = node(NK_WHILE, yylineno, NULL, 2, $3, $5); }           /* while 문 */
  | compound_stmt               /* 중괄호 블록 자체가 하나의 문으로 취급 */
  ;

/* 최상위 expr 비단말 (필요시 확장 포인트) */
expr
  : assignment
  ;

/* 대입식: 우변은 assignment(우결합), 좌변은 IDENT만 허용(간단화) */
assignment
  : logical_or
  | IDENT '=' assignment { $$ = node(NK_ASSIGN, yylineno, $1->op, 1, $3); free_ast($1); }
  ;

/* 논리 OR (||) */
logical_or
  : logical_and
  | logical_or OR logical_and     { $$ = node(NK_BINOP, yylineno, "||", 2, $1, $3); }
  ;

/* 논리 AND (&&) */
logical_and
  : equality
  | logical_and AND equality      { $$ = node(NK_BINOP, yylineno, "&&", 2, $1, $3); }
  ;

/* ==, != */
equality
  : relational
  | equality EQ relational        { $$ = node(NK_BINOP, yylineno, "==", 2, $1, $3); }
  | equality NE relational        { $$ = node(NK_BINOP, yylineno, "!=", 2, $1, $3); }
  ;

/* <, >, <=, >= */
relational
  : additive
  | relational '<' additive       { $$ = node(NK_BINOP, yylineno, "<",  2, $1, $3); }
  | relational '>' additive       { $$ = node(NK_BINOP, yylineno, ">",  2, $1, $3); }
  | relational LE additive        { $$ = node(NK_BINOP, yylineno, "<=", 2, $1, $3); }
  | relational GE additive        { $$ = node(NK_BINOP, yylineno, ">=", 2, $1, $3); }
  ;

/* +, - */
additive
  : multiplicative
  | additive '+' multiplicative   { $$ = node(NK_BINOP, yylineno, "+", 2, $1, $3); }
  | additive '-' multiplicative   { $$ = node(NK_BINOP, yylineno, "-", 2, $1, $3); }
  ;

/* *, /, % */
multiplicative
  : unary
  | multiplicative '*' unary      { $$ = node(NK_BINOP, yylineno, "*", 2, $1, $3); }
  | multiplicative '/' unary      { $$ = node(NK_BINOP, yylineno, "/", 2, $1, $3); }
  | multiplicative '%' unary      { $$ = node(NK_BINOP, yylineno, "%", 2, $1, $3); }
  ;

/* 단항 연산 및 후위식으로의 연결 */
unary
  : postfix
  | '!' unary                     { $$ = node(NK_UNOP, yylineno, "!",   1, $2); }
  | '-' unary                     { $$ = node(NK_UNOP, yylineno, "neg", 1, $2); } /* 단항 음수 */
  | '+' unary                     { $$ = $2; }                                    /* +x 는 x */
  ;

/* 후위식: 기본 식(primary) 또는 함수 호출 */
postfix
  : primary
  | IDENT '(' arg_list_opt ')'    { $$ = node(NK_CALL, yylineno, $1->op, 1, $3); free_ast($1); }
  ;

/* 함수 인자 목록: 비어있을 수도 있음 */
arg_list_opt
  : /* empty */                   { $$ = node(NK_ARG_LIST, yylineno, NULL, 0); }
  | arg_list
  ;

/* 인자 목록 누적 */
arg_list
  : expr                          { $$ = node(NK_ARG_LIST, yylineno, NULL, 1, $1); }
  | arg_list ',' expr
    {
      Node **arr = (Node**)calloc($1->nchild+1, sizeof(Node*));
      for(int i=0;i<$1->nchild;i++) arr[i]=$1->child[i];
      arr[$1->nchild] = $3;
      $$ = nodev(NK_ARG_LIST, yylineno, NULL, $1->nchild+1, arr);
      free($1->child); $1->child=NULL; $1->nchild=0; free($1);
    }
  ;

/* 기본 식:
 *   - IDENT/상수 토큰은 렉서에서 이미 Node*를 만들어 yylval에 담아 반환했으므로 그대로 전달
 *   - 괄호식은 내부 expr 노드를 그대로 사용
 */
primary
  : IDENT         { $$ = $1; }
  | INT_CONST     { $$ = $1; }
  | FLOAT_CONST   { $$ = $1; }
  | CHAR_CONST    { $$ = $1; }
  | STRING_LITERAL{ $$ = $1; }
  | '(' expr ')'  { $$ = $2; }
  ;

%%  /* ===================== 문법 규칙(Grammar) 영역 끝 ===================== */

/* Bison이 구문 오류를 발견했을 때 호출하는 함수 */
void yyerror(const char *s){
  fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}