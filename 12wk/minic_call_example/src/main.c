#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "ir.h"

int yyparse(void);
extern FILE *yyin;

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }

    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed.\n");
        return 1;
    }

    if (!g_program) {
        fprintf(stderr, "No program parsed.\n");
        return 1;
    }

    ir_print_program(g_program);
    return 0;
}
