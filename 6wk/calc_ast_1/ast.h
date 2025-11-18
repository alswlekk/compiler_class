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

#endif
