
section .data
	num dq 5000000000

section .bss
section .text
	global main

main:
	push rbp
	mov rbp, rsp

	mov rcx, [num]
_loop:
	loop _loop

	mov rsp, rbp
	pop rbp

	mov rax, 60
	mov rdi, 0
	syscall

