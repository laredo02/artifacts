
CC=g++
CC_FLAGS=-std=c++11 -g -O2 -Wall

HPPDIR=include
HPP=$(HPPDIR)/*.hpp
SRCDIR=src
SRC=$(SRCDIR)/*.cpp
BINDIR=bin

main: $(SRC) $(HPP)
	$(CC) $(SRC) $(CC_FLAGS) -o $(BINDIR)/main

test: main
	./bin/main
