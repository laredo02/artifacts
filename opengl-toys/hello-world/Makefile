CC = g++
LD_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

main: main.cpp
	mkdir -p build
	$(CC) main.cpp glad.c -o build/main $(LD_FLAGS)

run: main
	./build/main

clean:
	rm -r build
.PHONY: run
