
extern printf

section .data

    msg0 db "Bad Loop", 10, 0
    msg1 db "Good Loop", 10, 0

    num dq 100000000
    fmt db "Sum from 0 to %ld is %ld", 10, 0

    c1 dq 1
    c2 dq 2

section .bss

section .text
    global main

main:
    push rbp
    mov rbp, rsp ; prologue

    mov rax, [c1]
    mov rbx, [c2]
    cmp rax, rbx
    je good

    mov rbx, 0 ; counter
    mov rax, 0 ; sum
    mov rdi, msg0
    call printf

bloop:
    add rax, rbx
    inc rbx
    cmp rbx, [num]
    jl bloop

    mov rdi, fmt
    mov rsi, [num]
    mov rdx, rax
    mov rax, 0
    call printf

    mov rsp, rbp ; epilogue
    pop rbp

    mov rax, 60 ; exit
    mov rdi, 0 ; exit code
    syscall

good:
    mov rax, 0 ; sum
    mov rdi, msg1
    call printf
    mov rcx, [num] ; counter
    mov rax, 0
gloop:
    add rax, rcx
    loop gloop ; loop until rcx=0 (rcx-=1)

    mov rdi, fmt
    mov rsi, [num]
    mov rdx, rax
    mov rax, 0
    call printf

    mov rsp, rbp ; epilogue
    pop rbp

    mov rax, 60 ; exit
    mov rdi, 0 ; exit code
    syscall
