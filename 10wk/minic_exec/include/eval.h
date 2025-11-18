#ifndef EVAL_H
#define EVAL_H

#include "ast.h"

// expr AST를 실제 int 값으로 평가
// ok != NULL 이면, *ok = 1 (성공) 또는 0 (에러: 미정의 변수, 0 나누기 등)
int eval_expr(AST* node, int* ok);

#endif
