
#ifndef _LAYER
#define _LAYER

#include "neuron.hpp"
#include "../math/matrix.hpp"

class Layer {
public:
	Layer(const float neuronNumber);

	void setNeuronValues(std::vector<float> neuronValues);
	Matrix *getNeuronValues();
private:
	int neuronNumber;
	std::vector<Neuron *> neurons;
};

#endif

