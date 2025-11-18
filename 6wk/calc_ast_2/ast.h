// ast.h
#ifndef AST_H
#define AST_H

#include <stdio.h>

typedef enum {
    NODE_NUM,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV
} NodeType;

typedef struct AST {
    NodeType type;
    double value;
    struct AST *left;
    struct AST *right;
} AST;

AST *new_num(double val);
AST *new_op(NodeType type, AST *left, AST *right);
void  print_ast(AST *node, int depth);
void  free_ast(AST *node);

/* ➜ 추가: AST 평가 함수 (에러면 *err = 1 세팅) */
double eval_ast(AST *node, int *err);

#endif
