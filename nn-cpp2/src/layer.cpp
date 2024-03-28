
#include "../include/layer.hpp"

Layer::Layer (int size) {
	for(int i=0; i<size; i++) {
		Neuron *n = new Neuron(0.0);
		this->neurons.push_back(n);
	}
}

