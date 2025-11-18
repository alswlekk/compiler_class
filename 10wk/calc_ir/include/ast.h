#ifndef AST_H
#define AST_H

typedef enum {
    AST_INT,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV
} ASTType; // 노드의 종류를 나타내는 열거형

typedef struct AST {
    ASTType type;           // 이 노드가 어떤 종류인지(AST_*)
    int value;              // 정수 리터럴일 때만 사용
    struct AST* left;       // 이항연산 왼쪽 노드 포인터
    struct AST* right;      // 이항연산 오른쪽 노드 포인터
} AST;

AST* ast_int(int v);        // 정수 리터럴 노드 생성
AST* ast_bin(ASTType t, AST* l, AST* r);    // 이항 연산 노드 생성

#endif
