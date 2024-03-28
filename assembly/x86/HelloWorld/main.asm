
global _start 	; linker entry point

section .data
	msg db "Hello, World", 0x0A 	; 10 = ' '
	len equ $ - msg

section .text

_start:
	mov ebx, 104
	mov ecx, 344
	mov eax, 1
	cmp ecx, ebx
	jg skip
	
	mov ebx, 13

skip:
	int 0x80



