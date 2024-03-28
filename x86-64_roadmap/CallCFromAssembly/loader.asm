
extern print_hello

section .text
	global _start

%macro exit 0
	mov rax, 60
	mov rdi, 0
	syscall
%endmacro

_start:
	call print_hello

	exit




