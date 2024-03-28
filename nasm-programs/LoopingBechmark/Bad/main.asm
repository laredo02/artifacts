
section .data
	num dq 1000000000

section .bss
section .text
	global main

main:
	push rbp
	mov rbp, rsp

	mov rax, [num]
	mov rbx, 0
_loop:
	inc rbx
	cmp rbx, rax
	jl _loop

	mov rsp, rbp
	pop rbp

	mov rax, 60
	mov rdi, 0
	syscall

