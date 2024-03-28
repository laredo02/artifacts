all: neuralnetwork

CC = g++
FLAGS = -std=c++11
WARNINGS = -Wall
DEBUG = -g
OPTIMIZE = -O2

BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj

MATRIX_DEPS = src/magic/math/matrix.cpp
NEURON_DEPS = src/magic/neuralnetwork/neuron.cpp
LAYER_DEPS = src/magic/neuralnetwork/layer.cpp
NEURAL_NETWORK_DEPS = src/magic/neuralnetwork/neuralnetwork.cpp

matrix.o: Makefile $(MATRIX_DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) $(MATRIX_DEPS) $(WARNINGS) $(DEBUG) $(OPTIMIZE) -c -o $(OBJ_DIR)/$@

neuron.o: Makefile $(NEURON_DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) $(NEURON_DEPS) $(WARNINGS) $(DEBUG) $(OPTIMIZE) -c -o $(OBJ_DIR)/$@

layer.o: Makefile $(LAYER_DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) $(LAYER_DEPS) $(WARNINGS) $(DEBUG) $(OPTIMIZE) -c -o $(OBJ_DIR)/$@

neuralnetwork.o: Makefile $(NEURAL_NETWORK_DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) $(NEURAL_NETWORK_DEPS) $(WARNINGS) $(DEBUG) $(OPTIMIZE) -c -o $(OBJ_DIR)/$@

main.o: Makefile src/main.cpp
	$(CC) src/main.cpp $(WARNINGS) $(DEBUG) $(OPTIMIZE) -c -o $(OBJ_DIR)/$@

neuralnetwork: Makefile matrix.o neuron.o layer.o neuralnetwork.o main.o
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DIR)/*.o $(WARNINGS) $(DEBUG) $(OPTIMIZE) -o $(BIN_DIR)/$@

run: neuralnetwork
	./$(BIN_DIR)/neuralnetwork

clean:
	rm -rf $(BUILD_DIR)

install:
	echo "Install will soon be supported supported"

