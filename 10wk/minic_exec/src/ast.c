#include <stdlib.h>
#include <string.h>
#include "ast.h"

AST* ast_int(int v) {
    AST* n = (AST*)malloc(sizeof(AST));
    n->type = AST_INT;
    n->value = v;
    n->name = NULL;
    n->left = n->right = NULL;
    return n;
}

AST* ast_bin(ASTType t, AST* l, AST* r) {
    AST* n = (AST*)malloc(sizeof(AST));
    n->type = t;
    n->left = l;
    n->right = r;
    n->value = 0;
    n->name = NULL;
    return n;
}

AST* ast_var(char* name) {
    AST* n = (AST*)malloc(sizeof(AST));
    n->type = AST_VAR;
    n->value = 0;
    n->left = n->right = NULL;
    // scanner에서 strdup 한 문자열을 그대로 넘겨받는다고 가정
    n->name = name;
    return n;
}
