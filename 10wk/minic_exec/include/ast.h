#ifndef AST_H
#define AST_H

typedef enum {
    AST_INT,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_VAR
} ASTType;

typedef struct AST {
    ASTType type;
    int value;              // 정수 리터럴일 때만 사용
    char* name;             // 변수 이름일 때 사용 (AST_VAR)
    struct AST* left;       // 이항연산 왼쪽
    struct AST* right;      // 이항연산 오른쪽
} AST;

AST* ast_int(int v);
AST* ast_bin(ASTType t, AST* l, AST* r);
AST* ast_var(char* name);   // name 포인터 소유권을 그대로 넘긴다고 가정

#endif
