
section .data
    fmtint db "num = %d", 0xA, 0
    num dd 123
    fmtflt db "flt = %f", 0xa, 0
    flt dq 3.14

section .text
    extern printf
    global main

main:
    push rbp
    mov rbp, rsp ; prologue

    mov rax, 0
    mov rdi, fmtint
    mov rsi, [num]
    call printf

    mov rax, 1
    movq xmm0, [flt]
    mov rdi, fmtflt
    call printf

    mov rsp, rbp ; epilogue
    pop rbp

    mov rax, 60 ; exit
    mov rdi, 0 ; exit code
    syscall
