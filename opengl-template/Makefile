all: holamundo

CC = gcc
WARNINGS = -Wall -g
DEPENDENCIES = -lGL -lglfw -lGLEW
OPTIMIZE = -O2

HEADERS = src/headers/openglutils.h
CFILES = main.c src/createwindow.c src/readshader.c src/printglslerrors.c

holamundo: $(HEADERS) $(CFILES)
	$(CC) -o bin/$@ $(CFILES) $(WARNINGS) $(DEPENDENCIES) $(OPTIMIZE)

run:
	./bin/holamundo

install:
