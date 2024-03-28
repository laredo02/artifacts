
section .data
	num dw 0xFFAA

section .bss

section .text
	global _start

_start:
	push rbp
	mov rbp, rsp

	mov rax, 0
	mov rax, [num]
	
	mov rsp, rbp
	pop rbp

	mov rax, 60
	mov rdi, 0
	syscall

