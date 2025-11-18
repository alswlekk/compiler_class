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

/* 함수 선언만 둔다 */
AST *new_num(double val);
AST *new_op(NodeType type, AST *left, AST *right);
void  print_ast(AST *node, int depth);
void  free_ast(AST *node);

int     check(AST *node);          // 오류 없으면 0, 있으면 1
double  eval(AST *node, int *err); // 간편 평가 래퍼
double eval_ast(AST *node, int *err);

#endif
