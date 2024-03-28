
all: run

main.o: main.asm
	nasm -f elf64 -g -F dwarf main.asm -l main.lst

main: main.o
	gcc -ggdb -no-pie main.o -o main

run: main
	./main

debug: main
	gdb main

clean:
	rm main main.o main.lst
