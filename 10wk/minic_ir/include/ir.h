#ifndef IR_H
#define IR_H

typedef enum {
    IR_ADD,     // 이항 연산
    IR_SUB,     // 이항 연산
    IR_MUL,     // 이항 연산
    IR_DIV,     // 이항 연산
    IR_LOADI,   // 상수 로드
    IR_MOV,      // 단순 대입
    IR_PRINT
} IROp;

typedef struct IR {
    IROp op;            // 어떤 연산인지
    char dst[32];       // 대입 대상 / 피연산자 문자열(임시변수 이름, 상수 등)
    char src1[32];      // 대입 대상 / 피연산자 문자열(임시변수 이름, 상수 등)
    char src2[32];      // 필요 없으면 빈 문자열 ""
    struct IR* next;    // 단일 연결 리스트로 IR들을 연결하기 위한 포인터
} IR;

void emit(IROp op, const char* dst, const char* s1, const char* s2);    // 새 IR 노드를 만들어 리스트에 추가
void print_ir(void);    // IR 리스트 전체를 사람이 읽을 수 있는 형태로 출력
char* new_temp(void);   // 새 임시 변수 이름 t0, t1, … 생성
void free_ir(void);     // 리스트 전체 free 및 상태 초기화

#endif
