
#include "neuron.hpp"

Neuron::Neuron (float value) {
    this->value = value;
}

float Neuron::getValue () {
    return this->value;
}

void Neuron::setValue (float value) {
    this->value = value;
}

