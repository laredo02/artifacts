
global _start:

_start:
	sub esp, 6
	mov [esp], byte 'H'
	mov [esp+1], byte 'e'
	mov [esp+2], byte 'l'
	mov [esp+3], byte 'l'
	mov [esp+4], byte 'o'
	mov [esp+5], byte 0x0A
	
	mov eax, 4
	mov ebx, 1
	mov ecx, esp
	mov edx, 6
	int 0x80
	

