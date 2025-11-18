#include <stdio.h>

int yyparse(void);  // parser.y에서 생성
int yydebug;        // 필요하면 디버깅

int main(void)
{
    printf("Enter expressions (Ctrl+D to end):\n");
    yydebug = 0;    // 1로 바꾸면 bison 디버그 출력
    yyparse();
    return 0;
}
