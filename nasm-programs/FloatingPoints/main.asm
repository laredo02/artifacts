
extern printf

section .data
	num0 dq 9.0
	num1 dq 8.6
	fmt db "%.2f %s %.2f = %.2f", 0xa, 0
	plus db "+", 0
	minus db "-", 0
	fmt_sqrt db "sqrt(%.2f) = %.2f", 0xa, 0

section .bss
	result resq 1

section .text
	global main

main:
	
	push rbp
	mov rbp, rsp

	movsd xmm0, [num0]
	movsd xmm1, [num1]
	movsd xmm2, [num0]
	addsd xmm2, [num1]
	mov rdi, fmt
	mov rsi, plus
	mov rax, 3
	call printf

	movsd xmm0, [num0]
	movsd xmm1, [num1]
	movsd xmm2, [num0]
	subsd xmm2, [num1]
	mov rdi, fmt
	mov rsi, minus
	mov rax, 3
	call printf

	movsd xmm0, [num0]
	sqrtsd xmm1, [num0]
	mov rdi, fmt_sqrt
	mov rax, 2
	call printf

	xor rax, rax
	leave

terminate:
	mov rax, 60
	xor rdi, rdi
	syscall

