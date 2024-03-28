
#ifndef _NEURAL_NETWORK
#define _NEURAL_NETWORK

#include <vector>

#include "../include/layer.hpp"
#include "../include/matrix.hpp"

class NeuralNetwork {
	public:
		NeuralNetwork(std::vector<int> topology);
	private:
		int size;
		std::vector<int> topology;
		std::vector<Layer *> layers;
		std::vector<Matrix *> wMatrices;
};

#endif

