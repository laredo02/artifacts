
extern printf

section .data
	number1 dq 128
	number2 dq 3
	number3 dq -12
	fmt db "number1 = %ld number2 = %ld", 0xA, 0
	fmtadd db "number1 + number2 = %ld", 0xa, 0
	fmtsub db "number1 - number2 = %ld", 0xa, 0
	fmtinc db "number1++ = %ld", 0xa, 0
	fmtdec db "number1-- = %ld", 0xa, 0
	fmtsal db "number1 << 2 %ld", 0xa, 0
	fmtsar db "number1 >> 2 = %ld", 0xa, 0
	fmtsalneg db "number3 << 2 = %ld", 0xa, 0
	fmtimul db "number1 * number2 =  %ld", 0xa, 0
	fmtidiv db "number1 / number2 =  %ld", 0xa, 0
	fmtmod db "number1 % number2 =  %ld", 0xa, 0

section .bss
	result resq 1
	module resq 1

section .text
	global main

main:
prolog:
	push rbp
	mov rbp, rsp

integers:
	mov rdi, fmt	
	mov rsi, [number1]
	mov rdx, [number2]
	xor rax, rax
	call printf

; add
	mov rax, [number1]
	add rax, [number2]
	mov [result], rax
	; add sum
	mov rdi, fmtadd
	mov rsi, [result]
	xor rax, rax
	call printf
; sub
	mov rax, [number1]
	sub rax, [number2]
	mov [result], rax
	; print sub
	mov rdi, fmtsub
	mov rsi, [result]
	xor rax, rax
	call printf
; inc
	mov rax, [number1]
	inc rax
	mov [result], rax
	; print inc
	mov rdi, fmtinc
	mov rsi, [result]
	xor rax, rax
	call printf
; dec
	mov rax, [number1]
	dec rax
	mov [result], rax
	; print dec
	mov rdi, fmtdec
	mov rsi, [result]
	xor rax, rax
	call printf
; sal
	mov rax, [number1]
	sal rax, 2
	mov [result], rax
	; print sal
	mov rdi, fmtsal
	mov rsi, [result]
	xor rax, rax
	call printf
; sar
	mov rax, [number1]
	sar rax, 2
	mov [result], rax
	; print sar
	mov rdi, fmtsar
	mov rsi, [result]
	xor rax, rax
	call printf

; sal
	mov rax, [number3]
	sal rax, 2
	mov [result], rax
	; print sal
	mov rdi, fmtsalneg
	mov rsi, [result]
	xor rax, rax
	call printf
; imul
	mov rax, [number1]
	imul qword [number2]
	mov [result], rax
	; print imul
	mov rdi, fmtimul
	mov rsi, [result]
	xor rax, rax
	call printf
; idiv
	mov rax, [number1]
	mov rdx, 0
	idiv qword [number2]
	mov [result], rax
	mov [module], rdx
	; print idiv
	mov rdi, fmtidiv
	mov rsi, [result]
	mov rax, 0
	call printf
; mod
mod:
	; print mod
	mov rdi, fmtmod
	mov rsi, [module]
	mov rax, 0
	call printf

epilog:
	mov rsp, rbp
	pop rbp

terminate:
	mov rax, 60
	xor rdi, rdi
	syscall

