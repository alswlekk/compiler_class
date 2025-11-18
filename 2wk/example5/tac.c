#include <stdio.h>
#include "tac.h"

static int temp_id = 0;
static int is_leaf(NodeKind k) { return k == N_IDENT || k == N_NUMBER; }

static const char* op_str(NodeKind k) {
    switch (k) {
    case N_ADD: return "+";
    case N_SUB: return "-";
    case N_MUL: return "*";
    case N_DIV: return "/";
    default: return "?";
    }
}

// returns name of result (either ident, number literal, or temp)
static const char* gen_expr(AST* n) {
    static char buf[64];
    if (n->kind == N_IDENT) return n->name;
    if (n->kind == N_NUMBER) { snprintf(buf, sizeof(buf), "%lld", n->ival); return buf; }

    const char* a = gen_expr(n->lhs);
    const char* b = gen_expr(n->rhs);
    static char tname[64];
    snprintf(tname, sizeof(tname), "t%d", ++temp_id);
    printf("%s = %s %s %s\n", tname, a, op_str(n->kind), b);
    return tname;
}

void gen_tac(AST* n, const char* assign_lhs) {
    if (n->kind != N_ASSIGN) return;
    const char* res = gen_expr(n->rhs);
    printf("%s = %s\n", assign_lhs, res);
}
