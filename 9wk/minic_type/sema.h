#ifndef SEMA_H
#define SEMA_H
#include "ast.h"

extern int sema_errors;     /* 에러 수 */
void sema_run(Node *root);  /* 전역에서 호출 */

#endif