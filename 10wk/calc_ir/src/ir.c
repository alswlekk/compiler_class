#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"

static IR* head = NULL;
static IR* tail = NULL;
static int temp_id = 0;

char* new_temp(void) {
    // 전역(static) 리스트 포인터 head, tail 로 IR를 저장.
    // 임시 변수 이름은 "t%d" 형식으로 순차 번호를 붙여서 생성.
    char* buf = (char*)malloc(32);
    sprintf(buf, "t%d", temp_id++);
    return buf;
}

void emit(IROp op, const char* dst, const char* s1, const char* s2)
{
    // 새로운 IR 노드를 생성해서 리스트 끝에 붙임.
    IR* n = (IR*)calloc(1, sizeof(IR));
    n->op = op;
    if (dst) strncpy(n->dst, dst, sizeof(n->dst) - 1);
    if (s1) strncpy(n->src1, s1, sizeof(n->src1) - 1);
    if (s2) strncpy(n->src2, s2, sizeof(n->src2) - 1);

    if (!head) head = n;
    else       tail->next = n;
    tail = n;
}

void print_ir(void)
{
    // IR 타입별로 적당한 포맷으로 출력 (SSA 비슷한 느낌의 3주소 코드)
    for (IR* p = head; p; p = p->next) {
        switch (p->op) {
            case IR_LOADI:
                printf("%s = %s\n", p->dst, p->src1);
                break;
            case IR_MOV:
                printf("%s = %s\n", p->dst, p->src1);
                break;
            case IR_ADD:
                printf("%s = %s + %s\n", p->dst, p->src1, p->src2);
                break;
            case IR_SUB:
                printf("%s = %s - %s\n", p->dst, p->src1, p->src2);
                break;
            case IR_MUL:
                printf("%s = %s * %s\n", p->dst, p->src1, p->src2);
                break;
            case IR_DIV:
                printf("%s = %s / %s\n", p->dst, p->src1, p->src2);
                break;
        }
    }
}

void free_ir(void)
{
    // IR 리스트와 임시변수 카운터를 초기화합니다.
    // 한 줄(line) 처리 끝날 때마다 깨끗하게 리셋하는 용도
    IR* p = head;
    while (p) {
        IR* next = p->next;
        free(p);
        p = next;
    }
    head = tail = NULL;
    temp_id = 0;
}
