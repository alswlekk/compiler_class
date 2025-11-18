#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"

static IR* head = NULL;
static IR* tail = NULL;
static int temp_id = 0;

char* new_temp(void) {
    char* buf = (char*)malloc(32);
    sprintf(buf, "t%d", temp_id++);
    return buf;
}

void emit(IROp op, const char* dst, const char* s1, const char* s2)
{
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
            case IR_PRINT:
                printf("print %s\n", p->src1);
                break;
        }
    }
}

void free_ir(void)
{
    IR* p = head;
    while (p) {
        IR* next = p->next;
        free(p);
        p = next;
    }
    head = tail = NULL;
    temp_id = 0;
}
