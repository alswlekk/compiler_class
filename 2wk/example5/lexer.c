#include <ctype.h>
#include <string.h>
#include "lexer.h"

// laxer_next()가 한 글자씩 읽으면서 DFA 규칙대로 토큰 만듦
static Token make(TokenType t, const char* s, int len, long long v) {
    Token tk = { t, s, len, v }; return tk;
}

void lexer_init(Lexer* lx, const char* src) {
    lx->src = src; lx->pos = 0;
}

static void skip_ws(Lexer* lx) {
    while (lx->src[lx->pos] && isspace((unsigned char)lx->src[lx->pos])) lx->pos++;
}

static int is_ident_start(int c) { return isalpha(c) || c == '_'; }
static int is_ident_rest(int c) { return isalnum(c) || c == '_'; }

Token lexer_peek(Lexer* lx) {
    int p = lx->pos;
    skip_ws(lx);
    const char* s = lx->src + lx->pos;
    char c = *s;
    if (!c) { lx->pos = p; return make(T_EOF, s, 0, 0); }

    if (is_ident_start((unsigned char)c)) {
        int start = lx->pos++;
        while (is_ident_rest((unsigned char)lx->src[lx->pos])) lx->pos++;
        int len = lx->pos - start;
        Token t = make(T_IDENT, lx->src + start, len, 0);
        lx->pos = p; return t;
    }
    if (isdigit((unsigned char)c)) {
        int start = lx->pos++;
        while (isdigit((unsigned char)lx->src[lx->pos])) lx->pos++;
        int len = lx->pos - start;
        long long v = 0;
        for (int i = 0; i < len; i++) v = v * 10 + (lx->src[start + i] - '0');
        Token t = make(T_NUMBER, lx->src + start, len, v);
        lx->pos = p; return t;
    }
    TokenType tt = T_EOF;
    int len = 1;
    switch (c) {
    case '+': tt = T_PLUS; break;
    case '-': tt = T_MINUS; break;
    case '*': tt = T_MUL; break;
    case '/': tt = T_DIV; break;
    case '=': tt = T_ASSIGN; break;
    case ';': tt = T_SEMI; break;
    case '(': tt = T_LPAREN; break;
    case ')': tt = T_RPAREN; break;
    default:  tt = T_EOF;   break;
    }
    Token t = make(tt, s, len, 0);
    lx->pos = p; return t;
}

Token lexer_next(Lexer* lx) {
    skip_ws(lx);
    const char* s = lx->src + lx->pos;
    char c = *s;
    if (!c) return make(T_EOF, s, 0, 0);

    if (is_ident_start((unsigned char)c)) {
        int start = lx->pos++;
        while (is_ident_rest((unsigned char)lx->src[lx->pos])) lx->pos++;
        int len = lx->pos - start;
        return make(T_IDENT, lx->src + start, len, 0);
    }
    if (isdigit((unsigned char)c)) {
        int start = lx->pos++;
        while (isdigit((unsigned char)lx->src[lx->pos])) lx->pos++;
        int len = lx->pos - start;
        long long v = 0;
        for (int i = 0; i < len; i++) v = v * 10 + (lx->src[start + i] - '0');
        return make(T_NUMBER, lx->src + start, len, v);
    }
    lx->pos++;
    switch (c) {
    case '+': return make(T_PLUS, s, 1, 0);
    case '-': return make(T_MINUS, s, 1, 0);
    case '*': return make(T_MUL, s, 1, 0);
    case '/': return make(T_DIV, s, 1, 0);
    case '=': return make(T_ASSIGN, s, 1, 0);
    case ';': return make(T_SEMI, s, 1, 0);
    case '(': return make(T_LPAREN, s, 1, 0);
    case ')': return make(T_RPAREN, s, 1, 0);
    default:  return make(T_EOF, s, 1, 0); // �ܼ� ���� ó��
    }
}
