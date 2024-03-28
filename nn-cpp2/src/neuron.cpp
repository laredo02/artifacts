
#include <functional>
#include <cmath>

#include "../include/neuron.hpp"

Neuron::Neuron (float val) {
	this->val = val;
	activate();
	derive();
}

void Neuron::setVal (float val) {
	this->val = val;
	activate();
	derive();
}

void Neuron::activate (std::functional<float()>& activationFunction) {
	this->activationFunction = activationFunction;
	this->activatedVal = 
	this->activatedVal = this->val / (1 + std::abs(this->val));
}

void Neuron::derive () {
	this->derivedVal = this->activatedVal * (1 - this->activatedVal);
}

