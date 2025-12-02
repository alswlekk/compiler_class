#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen_x86.h"

int yyparse(void);
extern FILE *yyin;

int main(int argc, char **argv) {
    /* 입력 파일: 첫 번째 인자 (없으면 stdin 사용) */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }

    /* 출력 파일: 무조건 out.s 로 */
    if (!freopen("out.s", "w", stdout)) {
        perror("out.s");
        return 1;
    }

    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed.\n");
        return 1;
    }

    if (!g_program) {
        fprintf(stderr, "No program parsed.\n");
        return 1;
    }

    gen_x86_program(g_program);
    return 0;
}
