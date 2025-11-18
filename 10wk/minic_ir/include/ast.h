#ifndef AST_H
#define AST_H

typedef enum {
    AST_INT,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_VAR
} ASTType;  // 노드의 종류를 나타내는 열거형

typedef struct AST {
    ASTType type;           // 이 노드가 어떤 종류인지(AST_*)
    int value;              // 정수 리터럴일 때만 사용
    char* name;             // 변수 이름일 때 사용
    struct AST* left;       // 이항연산 왼쪽
    struct AST* right;      // 이항연산 오른쪽
} AST;

AST* ast_int(int v);        // 정수 리터럴 노드 생성
AST* ast_bin(ASTType t, AST* l, AST* r);    // 이항 연산 노드 생성
AST* ast_var(const char* name);

#endif
