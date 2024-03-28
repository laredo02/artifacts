
#include <random>
#include <vector>

#include "../include/neural_network.hpp"

NeuralNetwork::NeuralNetwork (std::vector<int> topology) {
	this->topology = topology;
	this->size = topology.size();
	for (int i=0; i<this->size; i++) {
		Layer *layer = new Layer(topology[i]);
		this->layers.push_back(layer);
	}
	for (int i=0; i<(this->size-1); i++) {
		Matrix *matrix = new Matrix(topology[i], topology[i+1]);
		matrix->init([](){
			// random normal distribution
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0.0, 0.1);
			return dis(gen);
		});
		this->wMatrices.push_back(matrix);
	}
}

