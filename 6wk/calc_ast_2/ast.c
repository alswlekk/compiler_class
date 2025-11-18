// ast.c
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *new_num(double val) {
    AST *node = (AST *)malloc(sizeof(AST));
    node->type = NODE_NUM;
    node->value = val;
    node->left = node->right = NULL;
    return node;
}

AST *new_op(NodeType type, AST *left, AST *right) {
    AST *node = (AST *)malloc(sizeof(AST));
    node->type = type;
    node->value = 0.0;
    node->left = left;
    node->right = right;
    return node;
}

void print_ast(AST *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    switch (node->type) {
        case NODE_NUM: printf("NUM(%.2f)\n", node->value); break;
        case NODE_ADD: printf("ADD\n"); break;
        case NODE_SUB: printf("SUB\n"); break;
        case NODE_MUL: printf("MUL\n"); break;
        case NODE_DIV: printf("DIV\n"); break;
    }
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}

void free_ast(AST *node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

/* ➜ 추가: AST 평가 */
double eval_ast(AST *node, int *err) {
    if (!node) { if (err) *err = 1; return 0.0; }

    switch (node->type) {
        case NODE_NUM:
            return node->value;

        case NODE_ADD: {
            double l = eval_ast(node->left, err);
            if (err && *err) return 0.0;
            double r = eval_ast(node->right, err);
            if (err && *err) return 0.0;
            return l + r;
        }

        case NODE_SUB: {
            double l = eval_ast(node->left, err);
            if (err && *err) return 0.0;
            double r = eval_ast(node->right, err);
            if (err && *err) return 0.0;
            return l - r;
        }

        case NODE_MUL: {
            double l = eval_ast(node->left, err);
            if (err && *err) return 0.0;
            double r = eval_ast(node->right, err);
            if (err && *err) return 0.0;
            return l * r;
        }

        case NODE_DIV: {
            double l = eval_ast(node->left, err);
            if (err && *err) return 0.0;
            double r = eval_ast(node->right, err);
            if (err && *err) return 0.0;
            if (r == 0.0) {
                fprintf(stderr, "[sem] 0으로 나눌 수 없습니다\n");
                if (err) *err = 1;
                return 0.0;
            }
            return l / r;
        }
    }

    if (err) *err = 1;
    return 0.0;
}
