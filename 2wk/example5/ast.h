#ifndef AST_H
#define AST_H
#include <stddef.h>

typedef enum {
    N_ASSIGN,
    N_ADD, N_SUB, N_MUL, N_DIV,
    N_IDENT, N_NUMBER
} NodeKind;

typedef struct AST {
    NodeKind kind;
    struct AST* lhs;
    struct AST* rhs;
    const char* name; // for ident
    long long ival;   // for number
} AST;

AST* ast_new(NodeKind k, AST* l, AST* r);
AST* ast_ident(const char* name);
AST* ast_number(long long v);
void  ast_free(AST* n);

// utilities
void ast_print_postfix(AST* n); // prints tokens in postfix order

#endif
