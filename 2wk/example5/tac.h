#ifndef TAC_H
#define TAC_H
#include "ast.h"

void gen_tac(AST* n, const char* assign_lhs);
// prints 3-address code for the assignment

#endif
