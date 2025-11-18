#include <ctype.h>
#include <string.h>
#include "lexer.h"

static Token make(TokenType t, const char* s, int len, long long v) {
    Token tk = { t, s, len, v };
    return tk;
}

static int is_ident_start(int c) { return isalpha(c) || c == '_'; }
static int is_ident_rest (int c) { return isalnum(c) || c == '_'; }

static void advance_one(Lexer* lx) {
    if (lx->src[lx->pos] != '\0') {
        lx->pos += 1;
    }
}

static void skip_ws_and_comments(Lexer* lx) {
    for (;;) {
        // 공백류 스킵
        while (lx->src[lx->pos] && isspace((unsigned char)lx->src[lx->pos])) {
            advance_one(lx);
        }
        // 줄 주석 //
        if (lx->src[lx->pos] == '/' && lx->src[lx->pos + 1] == '/') {
            advance_one(lx); // '/'
            advance_one(lx); // '/'
            while (lx->src[lx->pos] && lx->src[lx->pos] != '\n') {
                advance_one(lx);
            }
            continue; // 다음 라운드에서 공백 재스킵
        }
        // 블록 주석 /* ... */
        if (lx->src[lx->pos] == '/' && lx->src[lx->pos + 1] == '*') {
            advance_one(lx); // '/'
            advance_one(lx); // '*'
            while (lx->src[lx->pos]) {
                if (lx->src[lx->pos] == '*' && lx->src[lx->pos + 1] == '/') {
                    advance_one(lx); // '*'
                    advance_one(lx); // '/'
                    break;
                }
                advance_one(lx);
            }
            continue;
        }
        break;
    }
}

void lexer_init(Lexer* lx, const char* src) {
    lx->src = src;
    lx->pos = 0;
}

Token lexer_peek(Lexer* lx) {
    int saved_pos = lx->pos;

    skip_ws_and_comments(lx);

    const char* s = lx->src + lx->pos;
    char c = *s;
    if (!c) {
        lx->pos = saved_pos;
        return make(T_EOF, s, 0, 0);
    }

    // 식별자
    if (is_ident_start((unsigned char)c)) {
        int start = lx->pos;
        advance_one(lx);
        while (is_ident_rest((unsigned char)lx->src[lx->pos])) advance_one(lx);
        int len = lx->pos - start;
        Token t = make(T_IDENT, lx->src + start, len, 0);
        lx->pos = saved_pos;
        return t;
    }

    // 숫자
    if (isdigit((unsigned char)c)) {
        int start = lx->pos;
        advance_one(lx);
        while (isdigit((unsigned char)lx->src[lx->pos])) advance_one(lx);
        int len = lx->pos - start;
        long long v = 0;
        for (int i = 0; i < len; i++) {
            v = v * 10 + (long long)(lx->src[start + i] - '0');
        }
        Token t = make(T_NUMBER, lx->src + start, len, v);
        lx->pos = saved_pos;
        return t;
    }

    // 단일문자 기호
    TokenType tt = T_EOF;
    switch (c) {
    case '+': tt = T_PLUS;   break;
    case '-': tt = T_MINUS;  break;
    case '*': tt = T_MUL;    break;
    case '/': tt = T_DIV;    break;
    case '=': tt = T_ASSIGN; break;
    case ';': tt = T_SEMI;   break;
    case '(': tt = T_LPAREN; break;
    case ')': tt = T_RPAREN; break;
    default:  tt = T_EOF;    break;
    }

    Token t = make(tt, s, 1, 0);
    lx->pos = saved_pos;
    return t;
}

Token lexer_next(Lexer* lx) {
    skip_ws_and_comments(lx);

    const char* s = lx->src + lx->pos;
    char c = *s;
    if (!c) return make(T_EOF, s, 0, 0);

    // 식별자
    if (is_ident_start((unsigned char)c)) {
        int start = lx->pos;
        advance_one(lx);
        while (is_ident_rest((unsigned char)lx->src[lx->pos])) advance_one(lx);
        int len = lx->pos - start;
        return make(T_IDENT, lx->src + start, len, 0);
    }

    // 숫자
    if (isdigit((unsigned char)c)) {
        int start = lx->pos;
        advance_one(lx);
        while (isdigit((unsigned char)lx->src[lx->pos])) advance_one(lx);
        int len = lx->pos - start;
        long long v = 0;
        for (int i = 0; i < len; i++) {
            v = v * 10 + (long long)(lx->src[start + i] - '0');
        }
        return make(T_NUMBER, lx->src + start, len, v);
    }

    // 단일문자 기호
    advance_one(lx);
    switch (c) {
    case '+': return make(T_PLUS,   s, 1, 0);
    case '-': return make(T_MINUS,  s, 1, 0);
    case '*': return make(T_MUL,    s, 1, 0);
    case '/': return make(T_DIV,    s, 1, 0);
    case '=': return make(T_ASSIGN, s, 1, 0);
    case ';': return make(T_SEMI,   s, 1, 0);
    case '(': return make(T_LPAREN, s, 1, 0);
    case ')': return make(T_RPAREN, s, 1, 0);
    default:  return make(T_EOF,    s, 1, 0);
    }
}
