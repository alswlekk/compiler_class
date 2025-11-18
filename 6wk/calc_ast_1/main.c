// main.c
#include <stdio.h>

int yyparse(void);

int main(void) {
    if (yyparse() == 0) {
        return 0;
    } else {
        fprintf(stderr, "Parse failed\n");
        return 1;
    }
}
