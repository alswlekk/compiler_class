    .section .rodata
fmt_print_int:
    .string "%d\n"
fmt_scanf_int:
    .string "%d"
    .text
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    leaq -4(%rbp), %rsi
    leaq fmt_scanf_int(%rip), %rdi
    movl $0, %eax
    call scanf
    leaq -8(%rbp), %rsi
    leaq fmt_scanf_int(%rip), %rdi
    movl $0, %eax
    call scanf
    movl -4(%rbp), %eax
    movl %eax, %edi
    movl -8(%rbp), %eax
    movl %eax, %esi
    call add
    movl %eax, -12(%rbp)
    movl -12(%rbp), %eax
    movl %eax, %esi
    leaq fmt_print_int(%rip), %rdi
    movl $0, %eax
    call printf
    movl $0, %eax
    leave
    ret
