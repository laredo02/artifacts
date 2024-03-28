
#include <iostream>
#include <random>

#include "../include/matrix.hpp"
#include "../include/neuron.hpp"

int main () {

    Matrix *mat = new Matrix(4, 16);
    mat->init([]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        return dis(gen);
    });
    mat->dump();

    Matrix *tras = mat->traspose();
    tras->dump();

    delete(mat);
    delete(tras);

	return 0;

}

