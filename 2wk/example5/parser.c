#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

// forward decl
static AST* parse_exp(Parser* ps);
static AST* parse_term(Parser* ps);
static AST* parse_factor(Parser* ps);

static void advance(Parser* ps) { ps->cur = lexer_next(&ps->lx); }
static int  match(Parser* ps, TokenType t) {
    if (ps->cur.type == t) { advance(ps); return 1; } return 0;
}
static void expect(Parser* ps, TokenType t, const char* msg) {
    if (!match(ps, t)) {
        fprintf(stderr, "[SyntaxError] %s\n", msg);
        exit(1);
    }
}

void parser_init(Parser* ps, const char* src) {
    lexer_init(&ps->lx, src);
    advance(ps);
}

static AST* binop(Parser* ps, AST* (*lower)(Parser*), int(*is_op)(TokenType), NodeKind(*to_kind)(TokenType)) {
    AST* node = lower(ps);
    while (is_op(ps->cur.type)) {
        TokenType op = ps->cur.type; advance(ps);
        AST* rhs = lower(ps);
        node = ast_new(to_kind(op), node, rhs);
    }
    return node;
}

static int is_addop(TokenType t) { return t == T_PLUS || t == T_MINUS; }
static int is_mulop(TokenType t) { return t == T_MUL || t == T_DIV; }

static NodeKind to_addkind(TokenType t) { return t == T_PLUS ? N_ADD : N_SUB; }
static NodeKind to_mulkind(TokenType t) { return t == T_MUL ? N_MUL : N_DIV; }

static AST* parse_ident_token(Token tk) {
    char* name = (char*)malloc(tk.length + 1);
    memcpy(name, tk.lexeme, tk.length); name[tk.length] = '\0';
    return ast_ident(name);
}

static AST* parse_number_token(Token tk) {
    return ast_number(tk.ival);
}

static AST* parse_factor(Parser* ps) {
    if (ps->cur.type == T_LPAREN) {
        advance(ps);
        AST* e = parse_exp(ps);
        expect(ps, T_RPAREN, "�ݴ� ��ȣ ')'�� �ʿ��մϴ�.");
        return e;
    }
    if (ps->cur.type == T_IDENT) {
        Token t = ps->cur; advance(ps);
        return parse_ident_token(t);
    }
    if (ps->cur.type == T_NUMBER) {
        Token t = ps->cur; advance(ps);
        return parse_number_token(t);
    }
    fprintf(stderr, "[SyntaxError] factor�� ��������� ��ū Ÿ��=%d\n", ps->cur.type);
    exit(1);
}

static AST* parse_term(Parser* ps) {
    return binop(ps, parse_factor, is_mulop, to_mulkind);
}
static AST* parse_exp(Parser* ps) {
    return binop(ps, parse_term, is_addop, to_addkind);
}

AST* parse_assign(Parser* ps) {
    // ident '=' exp ';'
    if (ps->cur.type != T_IDENT) {
        fprintf(stderr, "[SyntaxError] ���Թ��� �º� �ĺ��ڰ� �ʿ��մϴ�.\n");
        exit(1);
    }
    Token id = ps->cur; advance(ps);
    char* lhs_name = (char*)malloc(id.length + 1);
    memcpy(lhs_name, id.lexeme, id.length); lhs_name[id.length] = '\0';

    expect(ps, T_ASSIGN, "'='�� �ʿ��մϴ�.");

    AST* rhs = parse_exp(ps);
    expect(ps, T_SEMI, "';'�� �ʿ��մϴ�.");

    AST* assign = ast_new(N_ASSIGN, NULL, rhs);
    assign->name = lhs_name; // �º� �̸�
    return assign;
}
