#include <stdlib.h>
#include <string.h>
#include "ast.h"

AST* ast_int(int v) {
    // malloc으로 AST 노드를 하나 만들고, type=AST_INT, value=v, 자식은 NULL로 설정
    AST* n = (AST*)malloc(sizeof(AST));
    n->type = AST_INT;
    n->value = v;
    n->name = NULL;
    n->left = n->right = NULL;
    return n;
}

AST* ast_bin(ASTType t, AST* l, AST* r) {
    // type=t로 설정하고, 왼쪽/오른쪽 자식에 l/r을 연결.
    // 이항 연산이므로 value는 의미 없어서 0으로 초기화.
    AST* n = (AST*)malloc(sizeof(AST));
    n->type = t;
    n->left = l;
    n->right = r;
    n->value = 0;
    n->name = NULL;
    return n;
}

AST* ast_var(const char* name) {
    AST* n = (AST*)malloc(sizeof(AST));
    n->type = AST_VAR;
    n->value = 0;
    n->left = n->right = NULL;
    n->name = name ? strdup(name) : NULL;
    return n;
}
