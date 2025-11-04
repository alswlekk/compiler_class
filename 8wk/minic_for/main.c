#include <stdio.h>
#include "ast.h"

int yyparse(void);
extern Node *root;

int main(int argc, char **argv){
  if(yyparse()==0){
    printf("=== AST ===\n");
    print_ast(root, 0);
    free_ast(root);
    return 0;
  }
  return 1;
}
