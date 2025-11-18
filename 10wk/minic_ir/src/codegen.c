#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ir.h"
#include "codegen.h"

// expr 전용 코드 생성
char* gen(AST* node)
{
    if (!node) return NULL;

    switch (node->type) {
        case AST_INT: {
            char* t = new_temp();
            char buf[32];
            sprintf(buf, "%d", node->value);
            emit(IR_LOADI, t, buf, "");
            return t;
        }
        case AST_VAR:
            // 변수 참조: 그냥 변수 이름을 그대로 사용
            return node->name ? strdup(node->name) : NULL;

        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV: {
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
                    break;
            }
            return t;
        }

        default:
            fprintf(stderr, "Unknown AST node type: %d\n", node->type);
            return NULL;
    }
}
