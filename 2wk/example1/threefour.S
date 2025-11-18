.section .text
.intel_syntax noprefix
.globl main
.extern printf

main:
    # Windows x64: 호출 전 32바이트 shadow space + 16바이트 정렬 맞춤
    sub     rsp, 40                # 32B shadow + 8B alignment

    # r = 3 + 4;
    mov     eax, 3
    add     eax, 4                 # eax = 7

    # printf("%d\n", r);
    mov     edx, eax               # 2번째 인자: r  -> RDX
    lea     rcx, [rip + fmt]       # 1번째 인자: 포맷 -> RCX
    xor     eax, eax               # AL=0 (가변인자 호출 규약)
    call    printf

    # return 0;
    add     rsp, 40
    xor     eax, eax               # eax = 0
    ret

.section .rodata
fmt:
    .asciz "%d\n"
    