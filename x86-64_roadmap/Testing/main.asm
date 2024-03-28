section .data
	text db "Hello, World!", 10
	break db "="
	newLine db 0, 10
	val db 0, 10

section .bss
	argc resb 8 

section .text
	global _start

%macro printRaxValue 0
	add rax, 48
	mov [val], al 
	mov rax, 1
	mov rdi, 1
	mov rsi, val
	mov rdx, 2 
	syscall
%endmacro

%macro printNewLine 0
	mov rax, 1
	mov rdi, 1
	mov rsi, newLine
	mov rdx, 1
	syscall
%endmacro

%macro br 0
	mov rcx, 0
%%_loop:
	mov rax, 1
	mov rdi, 1
	mov rsi, break
	mov rdx, 2
	syscall
	add rcx, 1
	cmp rsx, 10
	jl %%_loop

%endmacro 

%macro exit 0
	mov rax, 60
	mov rdi, 0
	syscall
%endmacro

_start:
	pop rax
	mov [argc], rax
	call _printArgc
	printRaxValue
	br

	exit

_printArgc:
	mov rax, 1
	mov rdi, 1
	mov rsi, [argc]
	mov rdx, 1
	syscall

	printNewLine
	ret



