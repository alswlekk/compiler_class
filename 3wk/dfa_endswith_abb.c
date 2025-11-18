#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 알파벳: { 'a', 'b' } -> 인덱스 {0, 1}
static int sym_to_idx(int c) {
    if (c == 'a') return 0;
    if (c == 'b') return 1;
    return -1; // 알파벳 이외
}

/*
상태 인덱스 정의
q0: 시작 상태 (아무 것도 안 맞음)
q1: ...a
q2: ...ab
q3: ...abb (수용)
*/
enum { Q0=0, Q1, Q2, Q3, NUM_STATES };

// 전이 테이블: next_state[current_state][symbol_index]
static const int next_state[NUM_STATES][2] = {
    /* from Q0 */ { Q1, Q0 }, // 'a'->Q1, 'b'->Q0
    /* from Q1 */ { Q1, Q2 }, // 'a'->Q1, 'b'->Q2
    /* from Q2 */ { Q1, Q3 }, // 'a'->Q1, 'b'->Q3
    /* from Q3 */ { Q1, Q0 }, // 'a'->Q1, 'b'->Q0  (끝이 abb였는데 추가 입력에 따라 이동)
};

static int is_accept_state(int q) {
    return q == Q3;
}

int main(void) {
    char buf[1024];

    printf("Enter strings over {a,b}. Ctrl+D/Ctrl+Z to end.\n");
    while (fgets(buf, sizeof(buf), stdin)) {
        // 개행 제거
        size_t n = strlen(buf);
        while (n && (buf[n-1] == '\n' || buf[n-1] == '\r')) buf[--n] = '\0';

        int state = Q0;
        int ok = 1;

        for (size_t i = 0; i < n; ++i) {
            int idx = sym_to_idx(buf[i]);
            if (idx < 0) { // 유효하지 않은 문자
                ok = 0;
                break;
            }
            state = next_state[state][idx];
        }

        if (!ok) {
            printf("input=\"%s\" => REJECT (invalid symbol)\n", buf);
        } else if (is_accept_state(state)) {
            printf("input=\"%s\" => ACCEPT\n", buf);
        } else {
            printf("input=\"%s\" => REJECT\n", buf);
        }
    }
    return 0;
}

