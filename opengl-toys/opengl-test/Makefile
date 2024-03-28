CC = g++
LD_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

main: src/main.cpp OpenGLManager glad
	$(CC) bin/obj/* src/main.cpp -o bin/main $(LD_FLAGS)

OpenGLManager: src/OpenGL/OpenGLManager.cpp include/OpenGLManager.hpp
	mkdir -p bin/obj
	$(CC) -c src/OpenGL/OpenGLManager.cpp -o bin/obj/OpenGLManager.o $(LD_FLAGS)

glad: lib/glad.c
	mkdir -p bin/obj
	$(CC) -c lib/glad.c -o bin/obj/glad.o $(LD_FLAGS)

all: main
	./bin/main

clean:
	rm -fr bin
