
section .data
    bNum db 123
    wNum dw 1234
    dNum dd 12345
    qNum1 dq 123456
    qNum2 dq 3.141592654
    warray times 5 dw 0
    text1 db "abc", 0
    text2 db "def", 0

section .bss
    bvar resb 1
    dvar resd 1
    wvar resw 10
    qvar resq 3

section .text
	global main

main:
prolog:
    push rbp
    mov rbp, rsp

memory:
    lea rax, [bNum]
    mov rax, bNum
    mov rax, [bNum]
    mov [bvar], rax
    lea rax, [bvar]
    lea rax, [wNum]
    mov rax, [wNum]
    lea rax, [text1]
    mov rax, text1
    mov rax, text1+1
    lea rax, [text1+1]
    lea rax, [text1]
    mov rax, [text1+1]

epilog:
    mov rsp, rbp
    pop rbp

terminate:
    mov rax, 60
    xor rdi, rdi
    syscall
