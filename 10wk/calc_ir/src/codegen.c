#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "ir.h"
#include "codegen.h"

char* gen(AST* node)
{
    if (!node) return NULL;

    // 리터럴(AST_INT)이면
    // 새 임시변수 t를 만들고
    // IR_LOADI t, 상수값 IR를 emit.
    // 결과가 들어있는 변수 이름 t를 리턴.
    if (node->type == AST_INT) {
        char* t = new_temp();
        char buf[32];
        sprintf(buf, "%d", node->value);
        emit(IR_LOADI, t, buf, "");
        return t;
    }

    // 이항 연산: 왼쪽, 오른쪽 먼저 코드 생성
    // 이항 연산자면
    // 왼쪽 자식에 대해 gen → 결과가 left 임시변수에
    // 오른쪽 자식에 대해 gen → 결과가 right 임시변수에
    // 다시 새 임시변수 t를 만들고, 연산 종류에 따라 IR_ADD/SUB/MUL/DIV emit.
    // 최종 결과를 담고 있는 t를 리턴.
    char* left = gen(node->left);
    char* right = gen(node->right);
    char* t = new_temp();

    switch (node->type) {
        case AST_ADD:
            emit(IR_ADD, t, left, right);
            break;
        case AST_SUB:
            emit(IR_SUB, t, left, right);
            break;
        case AST_MUL:
            emit(IR_MUL, t, left, right);
            break;
        case AST_DIV:
            emit(IR_DIV, t, left, right);
            break;
        default:
            fprintf(stderr, "Unknown AST node type: %d\n", node->type);
            break;
    }

    return t;
}
