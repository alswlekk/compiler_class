#include <stdio.h>
#include "ast.h"
#include "symtab.h"
#include "eval.h"

int eval_expr(AST* node, int* ok)
{
    if (!node) {
        if (ok) *ok = 0;
        return 0;
    }

    switch (node->type) {
        case AST_INT:
            if (ok) *ok = 1;
            return node->value;

        case AST_VAR: {
            int v;
            if (!sym_get(node->name, &v)) {
                fprintf(stderr, "runtime error: variable '%s' not initialized\n", node->name);
                if (ok) *ok = 0;
                return 0;
            }
            if (ok) *ok = 1;
            return v;
        }

        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV: {
            int ok1 = 0, ok2 = 0;
            int l = eval_expr(node->left, &ok1);
            int r = eval_expr(node->right, &ok2);
            if (!ok1 || !ok2) {
                if (ok) *ok = 0;
                return 0;
            }
            if (node->type == AST_ADD) {
                if (ok) *ok = 1;
                return l + r;
            } else if (node->type == AST_SUB) {
                if (ok) *ok = 1;
                return l - r;
            } else if (node->type == AST_MUL) {
                if (ok) *ok = 1;
                return l * r;
            } else { // DIV
                if (r == 0) {
                    fprintf(stderr, "runtime error: division by zero\n");
                    if (ok) *ok = 0;
                    return 0;
                }
                if (ok) *ok = 1;
                return l / r;
            }
        }

        default:
            if (ok) *ok = 0;
            return 0;
    }
}
