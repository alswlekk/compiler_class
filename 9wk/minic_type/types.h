#ifndef TYPES_H
#define TYPES_H

typedef enum {
  TY_INT, TY_FLOAT, TY_CHAR, TY_VOID,
  TY_ERROR /* 에러 전파용 */
} TypeKind;

#endif
