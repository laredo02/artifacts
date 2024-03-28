section .data
	ask db "Name "
	ans db "You are "

section .bss
	name resb 64

section .text
	global _start

_start:
	call _getName
	call _printName

	mov rax, 60
	mov rdi, 0
	syscall

_getName:
	mov rax, 1
	mov rdi, 1
	mov rsi, ask
	mov rdx, 5 
	syscall
	mov rax, 0
	mov rdi, 0
	mov rsi, name
	mov rdx, 64
	syscall
	ret

_printName:
	mov rax, 1
	mov rdi, 1
	mov rsi, ans
	mov rdx, 8
	syscall
	mov rax, 1
	mov rdi, 1
	mov rsi, name
	mov rdx, 64
	syscall
	ret

