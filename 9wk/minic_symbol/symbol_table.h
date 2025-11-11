#ifndef SYMTAB_H
#define SYMTAB_H
#include <stdbool.h>

typedef enum { SYM_VAR, SYM_PARAM, SYM_FUNC } SymKind;

typedef struct Sym {
  const char *name;     /* 심볼 이름 */
  SymKind     kind;     /* 변수/파라미터/함수 */
  int         arity;    /* 함수 파라미터 수, 그 외 0 */
  int         level;    /* 스코프 레벨(디버깅용) */
  struct Sym *next;     /* 해시 체인 */
} Sym;

void  symtab_init(void);
void  symtab_fini(void);
void  scope_push(void);
void  scope_pop(void);

bool  sym_put(const char *name, SymKind kind, int arity); /* 현재 스코프에 추가 (중복이면 false) */
Sym*  sym_get(const char *name);                          /* 가장 가까운 스코프부터 조회 */
void  symtab_dump(void);                                  /* 디버깅용 */

#endif
