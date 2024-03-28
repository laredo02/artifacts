section .data
	raxVal db 0, 10

section .bss
	argc resb 1

section .text
	global _start

%macro exit 0
	mov rax, 60
	mov rdi, 0
	syscall
%endmacro

_start:
	mov rax, 5
	call _printRAXValue
	
	exit

_printRAXValue:
	add rax, 48
	mov [raxVal], al
	mov rax, 1
	mov rdi, 1
	mov rsi, raxVal
	mov rdx, 2
	syscall
	ret


