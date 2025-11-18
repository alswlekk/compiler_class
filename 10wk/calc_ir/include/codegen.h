#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

// node를 계산하고, 결과가 들어있는 임시 변수 이름을 리턴
char* gen(AST* node);

#endif
