#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"

static int temp_id = 0;

static char *new_temp(void) {
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", temp_id++);
    char *s = (char *)malloc(strlen(buf) + 1);
    if (!s) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(s, buf);
    return s;
}

/* Forward declarations */
static char *gen_expr(Expr *e);
static void gen_stmt(Stmt *s);
static void gen_stmt_list(StmtList *sl);
static const char *binop_to_str(BinOpKind op);

static const char *binop_to_str(BinOpKind op) {
    switch (op) {
    case BIN_ADD: return "+";
    case BIN_SUB: return "-";
    case BIN_MUL: return "*";
    case BIN_DIV: return "/";
    default: return "?";
    }
}

static char *gen_expr(Expr *e) {
    if (!e) return NULL;

    switch (e->kind) {
    case EXPR_INT: {
        char *t = new_temp();
        printf("  %s = %d\n", t, e->u.int_value);
        return t;
    }
    case EXPR_VAR: {
        /* Variable itself acts as a 'location'; no IR needed */
        return e->u.var_name;
    }
    case EXPR_BINOP: {
        char *lhs = gen_expr(e->u.binop.lhs);
        char *rhs = gen_expr(e->u.binop.rhs);
        char *t = new_temp();
        printf("  %s = %s %s %s\n", t, lhs, binop_to_str(e->u.binop.op), rhs);
        return t;
    }
    case EXPR_CALL: {
        /* Evaluate args left to right, emit param for each */
        ExprList *arg = e->u.call.args;
        int argc = 0;
        while (arg) {
            char *val = gen_expr(arg->expr);
            printf("  param %s\n", val);
            argc++;
            arg = arg->next;
        }
        char *t = new_temp();
        printf("  %s = call %s, %d\n", t, e->u.call.func_name, argc);
        return t;
    }
    default:
        return NULL;
    }
}

static void gen_stmt(Stmt *s) {
    if (!s) return;

    switch (s->kind) {
    case STMT_VARDECL:
        printf("  ; var %s\n", s->u.vardecl.var_name);
        break;
    case STMT_ASSIGN: {
        char *val = gen_expr(s->u.assign.value);
        printf("  %s = %s\n", s->u.assign.var_name, val);
        break;
    }
    case STMT_EXPR:
        gen_expr(s->u.expr);
        break;
    case STMT_RETURN: {
        char *val = gen_expr(s->u.expr);
        printf("  return %s\n", val);
        break;
    }
    default:
        break;
    }
}

static void gen_stmt_list(StmtList *sl) {
    if (!sl) return;
    Stmt *cur = sl->head;
    while (cur) {
        gen_stmt(cur);
        cur = cur->next;
    }
}

void ir_print_program(FunctionList *prog) {
    if (!prog) {
        fprintf(stderr, "No program to print.\n");
        return;
    }

    Function *f = prog->head;
    while (f) {
        printf("func %s(", f->name);
        Param *p = f->params ? f->params->head : NULL;
        int first = 1;
        while (p) {
            if (!first) printf(", ");
            printf("%s", p->name);
            first = 0;
            p = p->next;
        }
        printf(")\n");
        printf("{\n");
        gen_stmt_list(f->body);
        printf("}\n\n");
        f = f->next;
    }
}
