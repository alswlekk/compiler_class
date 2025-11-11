#ifndef AST_H
#define AST_H

#include <stdio.h>   // 표준 입출력 라이브러리: printf(), fprintf(), FILE 입출력 등 사용
#include <stdlib.h>  // 표준 라이브러리: malloc(), free(), exit(), calloc() 등 메모리/프로세스 관련 함수
#include <stdarg.h>  // 가변 인자 함수 처리용 헤더: va_list, va_start(), va_arg(), va_end() 사용

/**
 * NodeKind 열거형
 * -------------------------------
 * AST 노드의 종류를 정의.
 * 각 노드는 프로그램의 구문 요소(함수, 변수, 연산식 등)를 나타냄.
 */
typedef enum {
  NK_TRANSLATION_UNIT,   // 프로그램 전체(translation unit, 즉 전체 소스 파일의 루트)
  NK_FUNC_DEF,           // 함수 정의 노드 (예: int main() { ... })
  NK_PARAM_LIST,         // 함수의 매개변수 목록 (예: (int a, int b))
  NK_PARAM,              // 단일 매개변수 (예: int a)
  NK_DECL,               // 변수 선언문 (예: int x;)
  NK_INIT_DECL_LIST,     // 여러 변수 선언 묶음 (예: int x=1, y=2;)
  NK_INIT_DECL,          // 단일 변수 초기화 선언 (예: x=1)
  NK_TYPE,               // 자료형 노드 (예: int, float, char)
  NK_COMPOUND,           // 블록 문 (예: { ... })
  NK_STMT_LIST,          // 문(statement)들의 리스트
  NK_IF,                 // if 문 (예: if (cond) stmt [else stmt])
  NK_WHILE,              // while 문 (예: while (cond) stmt)
  NK_FOR,        // for 문 노드
  NK_RETURN,             // return 문 (예: return expr;)
  NK_EXPR_STMT,          // 단독 표현식 문장 (예: a = b + c;)
  NK_ASSIGN,             // 대입식 (예: a = b;)
  NK_BINOP,              // 이항 연산 (예: a + b, x < y, etc.)
  NK_UNOP,               // 단항 연산 (예: -x, !flag)
  NK_CALL,               // 함수 호출 (예: sum(a, b))
  NK_ARG_LIST,           // 함수 호출 인자 목록 (예: (a, b))
  NK_VAR,                // 변수 참조 (예: x)
  NK_INT,                // 정수 상수 (예: 42)
  NK_FLOAT,              // 실수 상수 (예: 3.14)
  NK_CHAR,               // 문자 상수 (예: 'a')
  NK_STRING              // 문자열 상수 (예: "hello")
} NodeKind;

/**
 * AST 노드 구조체
 * -------------------------------
 * - 하나의 Node는 프로그램의 구문 요소(함수, 변수, 연산식 등)를 나타냄.
 * - 트리 구조로 연결되어 AST(Abstract Syntax Tree)를 구성함.
 */
typedef struct Node Node;

struct Node {
  NodeKind kind;        // 노드 종류 (NodeKind 열거형 참조: 예, NK_FUNC_DEF, NK_IF 등)
  const char *op;       // 연산자/타입/식별자/상수 문자열 저장 (예: "+", "int", "x", "42")
  Node **child;         // 하위 노드(자식 노드)들의 포인터 배열
  int nchild;           // 자식 노드 개수
  int line;             // 소스 코드 상의 행 번호 (디버깅/에러 메시지용)
};

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
Node *node(NodeKind kind, int line, const char *op, int nchild, ...);

/**
 * nodev()
 * ----------------------------------
 * - node()와 동일하지만, 가변 인자 대신 Node* 배열을 직접 전달.
 * - 이미 배열로 구성된 자식 노드 리스트를 사용할 때 유용.
 *
 * @param kind   노드 종류 (NodeKind)
 * @param line   소스 코드 라인 번호
 * @param op     연산자 또는 심볼 이름 문자열 (NULL 가능)
 * @param nchild 자식 노드 개수
 * @param arr    자식 노드 배열 (Node*[])
 * @return       생성된 Node* 포인터
 */
Node *nodev(NodeKind kind, int line, const char *op, int nchild, Node **arr);

/**
 * print_ast()
 * ----------------------------------
 * - AST 트리를 들여쓰기 기반으로 계층적으로 출력.
 * - 각 노드의 종류(kind), 연산자(op), 라인(line) 정보를 계층적으로 보여줌.
 * - 디버깅 및 시각화용.
 *
 * @param n       출력할 루트 노드
 * @param indent  현재 들여쓰기 수준 (보통 0에서 시작)
 */
void print_ast(Node *n, int indent);

/**
 * free_ast()
 * ----------------------------------
 * - AST 전체 트리를 재귀적으로 순회하면서 동적 메모리 해제.
 * - node(), nodev()로 생성된 모든 노드를 안전하게 해제해야 메모리 누수 방지 가능.
 *
 * @param n  해제할 루트 노드 (NULL이면 무시)
 */
void free_ast(Node *n);

#endif