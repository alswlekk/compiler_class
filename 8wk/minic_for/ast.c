#include "ast.h"
#include <string.h>

/**
 * dupstr()
 * ----------------------------------
 * - 문자열 s를 복제하여 새로운 메모리를 반환.
 * - strdup() 대신 직접 구현하여 플랫폼 독립성 확보.
 *
 * @param s  복제할 문자열 (NULL일 수 있음)
 * @return   새로 할당된 문자열 복사본 (free 필요)
 */
static char *dupstr(const char *s){
  if(!s) return NULL;                        // NULL 문자열은 그대로 NULL 반환
  size_t len = strlen(s);                    // 문자열 길이 계산
  char *p = (char*)malloc(len + 1);          // 복제용 메모리 할당
  memcpy(p, s, len + 1);                     // 문자열 내용 복사 (NULL 문자 포함)
  return p;
}

/**
 * node()
 * ----------------------------------
 * - 새로운 AST 노드를 생성하고 자식 노드를 가변 인자로 전달받음.
 * - 예: node(NK_BINOP, yylineno, "+", 2, left, right);
 *
 * @param kind   노드 종류 (NodeKind)
 * @param line   소스 코드 라인 번호
 * @param op     연산자 또는 심볼 이름 문자열 (NULL 가능)
 * @param nchild 자식 노드 개수
 * @param ...    자식 노드 포인터들 (가변 인자)
 * @return       생성된 Node* 포인터
 */
Node *node(NodeKind kind, int line, const char *op, int nchild, ...){
  Node *n = (Node*)calloc(1, sizeof(Node));      // 노드 본체 메모리 할당 및 0 초기화
  n->kind = kind;                                // 노드 종류 저장
  n->op = op ? dupstr(op) : NULL;                // 연산자나 심볼 문자열 복제
  n->nchild = nchild;                            // 자식 개수 저장
  n->line = line;                                // 코드 라인 번호 저장

  // 자식 노드 배열이 존재하는 경우
  if(nchild > 0){
    n->child = (Node**)calloc(nchild, sizeof(Node*)); // 자식 포인터 배열 생성
    va_list ap; va_start(ap, nchild);                 // 가변 인자 목록 시작
    for(int i = 0; i < nchild; i++)
      n->child[i] = va_arg(ap, Node*);                // 인자로 전달된 자식 노드 저장
    va_end(ap);                                       // 가변 인자 종료
  }
  return n;
}

/**
 * nodev()
 * ----------------------------------
* - node()와 동일하지만, 가변 인자 대신 Node* 배열을 직접 전달.
 * - 이미 배열로 구성된 자식 노드 리스트(Node** arr)를 사용할 때 유용.
 *
 * 예시:
 *   Node* children[2] = {left, right};
 *   Node *add = nodev(NK_BINOP, yylineno, "+", 2, children);
 *
 * @param kind   노드 종류 (NodeKind)
 * @param line   소스 코드 라인 번호
 * @param op     연산자 또는 심볼 이름 문자열 (NULL 가능)
 * @param nchild 자식 노드 개수
 * @param arr    자식 노드 배열 (Node*[])
 * @return       생성된 Node* 포인터
 */
Node *nodev(NodeKind kind, int line, const char *op, int nchild, Node **arr){
  Node *n = (Node*)calloc(1, sizeof(Node));      // 노드 본체 메모리 할당
  n->kind = kind;
  n->op = op ? dupstr(op) : NULL;
  n->nchild = nchild;
  n->line = line;

  if(nchild > 0){
    n->child = (Node**)calloc(nchild, sizeof(Node*));
    for(int i = 0; i < nchild; i++)
      n->child[i] = arr[i];
  }
  return n;
}

/**
 * kind_str()
 * ----------------------------------
 * - NodeKind 열거형 값을 문자열 이름으로 변환.
 * - AST 출력 시 가독성을 높이기 위해 사용됨
 *
 * @param k  NodeKind 값
 * @return   해당 노드 종류의 문자열
 */
static const char* kind_str(NodeKind k){
  switch(k){
    case NK_TRANSLATION_UNIT: return "TRANSLATION_UNIT";
    case NK_FUNC_DEF: return "FUNC_DEF";
    case NK_PARAM_LIST: return "PARAM_LIST";
    case NK_PARAM: return "PARAM";
    case NK_DECL: return "DECL";
    case NK_INIT_DECL_LIST: return "INIT_DECL_LIST";
    case NK_INIT_DECL: return "INIT_DECL";
    case NK_TYPE: return "TYPE";
    case NK_COMPOUND: return "COMPOUND";
    case NK_STMT_LIST: return "STMT_LIST";
    case NK_IF: return "IF";
    case NK_WHILE: return "WHILE";
    case NK_FOR: return "FOR";
    case NK_RETURN: return "RETURN";
    case NK_EXPR_STMT: return "EXPR_STMT";
    case NK_ASSIGN: return "ASSIGN";
    case NK_BINOP: return "BINOP";
    case NK_UNOP: return "UNOP";
    case NK_CALL: return "CALL";
    case NK_ARG_LIST: return "ARG_LIST";
    case NK_VAR: return "VAR";
    case NK_INT: return "INT";
    case NK_FLOAT: return "FLOAT";
    case NK_CHAR: return "CHAR";
    case NK_STRING: return "STRING";
    default: return "UNKNOWN";
  }
}

/**
 * print_ast()
 * ----------------------------------
 * - AST 트리를 들여쓰기 기반으로 계층적으로 출력.
 * - 각 노드의 종류(kind), 연산자(op), 라인(line) 정보를 계층적으로 보여줌.
 *
 * @param n       출력할 루트 노드
 * @param indent  현재 들여쓰기 수준 (보통 0에서 시작)
 */
void print_ast(Node *n, int indent){
  if(!n) return;

  // 들여쓰기 공백 출력
  for(int i = 0; i < indent; i++)
    putchar(' ');

  // 노드 종류 및 심볼 출력
  printf("(%s", kind_str(n->kind));
  if(n->op)
    printf(" : %s", n->op);
  printf(") @%d\n", n->line);

  // 자식 노드를 재귀적으로 출력
  for(int i = 0; i < n->nchild; i++)
    print_ast(n->child[i], indent + 2);
}

/**
 * free_ast()
 * ----------------------------------
 * - AST 전체 트리를 재귀적으로 순회하면서 동적 메모리 해제.
 * - node(), nodev()로 생성된 모든 노드를 안전하게 해제해야 메모리 누수 방지 가능.
 *
 * @param n  해제할 루트 노드 (NULL이면 무시)
 */
void free_ast(Node *n){
  if(!n) return;

  // 모든 자식 노드부터 해제 (후위 순회)
  for(int i = 0; i < n->nchild; i++)
    free_ast(n->child[i]);

  // 자식 포인터 배열 해제
  free(n->child);

  // op 문자열(dupstr로 복제된 메모리) 해제
  free((char*)n->op);

  // 노드 자체 해제
  free(n);
}