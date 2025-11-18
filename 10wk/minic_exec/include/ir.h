#ifndef IR_H
#define IR_H

typedef enum {
    IR_ADD,
    IR_SUB,
    IR_MUL,
    IR_DIV,
    IR_LOADI,   // 상수 로드: dst = immediate
    IR_MOV,     // 대입:      dst = src1
    IR_PRINT    // 출력:      print src1
} IROp;

typedef struct IR {
    IROp op;
    char dst[32];
    char src1[32];
    char src2[32];      // 필요 없으면 빈 문자열 ""
    struct IR* next;
} IR;

void emit(IROp op, const char* dst, const char* s1, const char* s2);
void print_ir(void);
char* new_temp(void);
void free_ir(void);

#endif
