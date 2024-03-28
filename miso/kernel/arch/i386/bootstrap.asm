
[bits 32]
global start
extern kernel_main

section .mbHeader

align 0x4
 
MODULEALIGN equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MODULEALIGN
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)
 
MultiBootHeader:
   dd MAGIC
   dd FLAGS
   dd CHECKSUM
 
start:
push ebx
call kernel_main

