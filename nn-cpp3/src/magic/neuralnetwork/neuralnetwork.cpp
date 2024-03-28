
#include <memory>
#include <iostream>

#include "layer.hpp"
#include "neuralnetwork.hpp"

NeuralNetwork::NeuralNetwork (struct NetworkTopology networkTopology) {
	this->networkTopology = networkTopology;
	this->layerNumber = networkTopology.topology.size();
	this->weightMatrixNumber = this->layerNumber - 1;
	for (unsigned int i=0; i<this->layerNumber; i++) {
		Layer *layer = new Layer(this->networkTopology.topology[i]);
		this->layers.push_back(layer);
	}
	for (unsigned int i=0; i<this->weightMatrixNumber; i++) {
		Matrix *matrix = new Matrix(this->networkTopology.topology[i], this->networkTopology.topology[i+1], true);
		this->weights.push_back(matrix);
	}
}

void NeuralNetwork::setInputValues (std::vector<float> values) {
	this->layers[0]->setNeuronValues(values);
}

void NeuralNetwork::feedForward () {
	std::cout << "Feed Forward" << std::endl;
}
























