#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST* ast_new(NodeKind k, AST* l, AST* r) {
    AST* n = (AST*)calloc(1, sizeof(AST));
    n->kind = k; n->lhs = l; n->rhs = r;
    return n;
}
AST* ast_ident(const char* name) {
    AST* n = ast_new(N_IDENT, NULL, NULL);
    n->name = name; return n;
}
AST* ast_number(long long v) {
    AST* n = ast_new(N_NUMBER, NULL, NULL);
    n->ival = v; return n;
}
void ast_free(AST* n) {
    if (!n) return;
    ast_free(n->lhs);
    ast_free(n->rhs);
    free(n);
}

static void print_op(NodeKind k) {
    switch (k) {
    case N_ADD: printf("+ "); break;
    case N_SUB: printf("- "); break;
    case N_MUL: printf("* "); break;
    case N_DIV: printf("/ "); break;
    default: break;
    }
}
void ast_print_postfix(AST* n) {
    if (!n) return;
    if (n->kind == N_IDENT) { printf("%.*s ", 0, ""); printf("%s ", n->name); return; }
    if (n->kind == N_NUMBER) { printf("%lld ", n->ival); return; }
    if (n->kind == N_ASSIGN) {
        // assignment: print RHS then LHS name then '='?
        // 여기서는 RHS만 후위로, 대입은 후위표기 출력에서 제외(별도 TAC 생성)
        ast_print_postfix(n->rhs);
        return;
    }
    ast_print_postfix(n->lhs);
    ast_print_postfix(n->rhs);
    print_op(n->kind);
}
