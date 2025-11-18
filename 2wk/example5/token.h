#ifndef TOKEN_H
#define TOKEN_H
// 토큰 종류(enum)와 토큰 구조체 정의
typedef enum {
    T_EOF = 0,
    T_IDENT,     // [a-zA-Z_][a-zA-Z0-9_]*
    T_NUMBER,    // 0 | [1-9][0-9]*
    T_PLUS, T_MINUS, T_MUL, T_DIV,
    T_ASSIGN,    // =
    T_SEMI,      // ;
    T_LPAREN,    // (
    T_RPAREN     // )
} TokenType;

typedef struct {
    TokenType type;
    const char* lexeme; // pointer into source buffer (not owned)
    int length;
    long long ival;     // for numbers
} Token;

#endif
