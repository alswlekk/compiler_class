#ifndef SYMTAB_H
#define SYMTAB_H

// 심볼 테이블: 간단한 이름 → int 값 매핑

void sym_init(void);
int sym_set(const char* name, int value); // 성공 시 1, 실패 시 0
int sym_get(const char* name, int* out);  // 찾고 초기화 되어 있으면 1, 아니면 0

#endif
