section .data
	name db "Miguel", 10
	dig db 0,10 

section .text
	global _start

%macro

_start:
	call _sayHello
	mov rax, 5
	call _displayRAX

	exit
	;mov rax, 60
	;mov rdi, 0
	;syscall 

_sayHello:
	mov rax, 1
	mov rdi, 1
	mov rsi, name
	mov rdx, 7
	syscall
	ret

_displayRAX:
	add rax, 48
	mov [dig], al
	mov rax, 1
	mov rdi, 1
	mov rsi, dig
	mov rdx, 2
	syscall
	ret
