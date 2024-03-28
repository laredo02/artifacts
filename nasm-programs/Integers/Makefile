
main.o: main.asm
	nasm -f elf64 -g -F dwarf main.asm -l main.lst

main: main.o
	gcc -ggdb -no-pie main.o -o main

run: main
	./main



debug: main
	gdb main

ddd_debug: main
	ddd main



clean:
	rm main.o main.lst

