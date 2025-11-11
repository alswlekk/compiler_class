#include <stdio.h>
#include "ast.h"
#include "sema.h"

int yyparse(void);
extern Node *root;

int main(void){
  if(yyparse()==0){
    printf("=== AST ===\n");
    print_ast(root, 0);

    printf("\n=== SYMBOL CHECK ===\n");
    sema_run(root);
    if(sema_errors==0) puts("Symbols: OK");
    else               printf("Symbols: %d error(s)\n", sema_errors);

    free_ast(root);
    return sema_errors ? 1 : 0;
  }
  return 2;
}
