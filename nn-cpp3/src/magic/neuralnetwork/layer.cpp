
#include <iostream>
#include <cassert>

#include "layer.hpp"

Layer::Layer (const float neuronNumber) {
	this->neuronNumber = neuronNumber;
	for (int i=0; i<this->neuronNumber; i++) {
		neurons.push_back(new Neuron(0.0f));
	}
}

void Layer::setNeuronValues (std::vector<float> neuronValues) {
	assert(neuronValues.size() == neurons.size());
	for (unsigned int i=0; i<neuronValues.size(); i++) {
		this->neurons[i]->setValue(neuronValues[i]);
	}
}

Matrix *Layer::getNeuronValues () {
	Matrix *values = new Matrix(1, this->neuronNumber, false);
	for (int i=0; i<this->neuronNumber; i++) {
	values->setValue(0, i, this->neurons[i]->getValue());
	}
	return values;
}

