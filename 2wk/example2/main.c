#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

static void print_token(Token t) {
//    printf("%-10s lexeme='", token_type_name(t.type));
    for (int i=0;i<t.length;i++) putchar(t.lexeme[i]);
//    printf("'");
    if (t.type == T_NUMBER) printf("  ival=%lld", t.ival);
    puts("");
}

int main(int argc, char** argv) {
    // 입력 방법:
    // 1) 인자로 전달:   ./scanner "int x = 10; // hi"
    // 2) 표준입력 전체 읽기: 파이프/리다이렉션
    static char buf[1<<16];
    if (argc >= 2) {
        strncpy(buf, argv[1], sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';
    } else {
        size_t n = fread(buf,1,sizeof(buf)-1,stdin);
        buf[n] = '\0';
    }

    Lexer lx; lexer_init(&lx, buf);

    for(;;){
        Token tk = lexer_next(&lx);
        print_token(tk);
        if (tk.type == T_EOF) break;
    }
    return 0;
}
