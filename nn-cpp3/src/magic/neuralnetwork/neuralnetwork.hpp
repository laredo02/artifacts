
#ifndef _NEURAL_NETWORK
#define _NEURAL_NETWORK

#include <vector>

#include "../math/matrix.hpp"
#include "layer.hpp"

struct NetworkTopology {
	std::vector<int> topology;
};

class NeuralNetwork {
public:
	NeuralNetwork(struct NetworkTopology networkTopology);

	void setInputValues(std::vector<float> inputValues);
	void feedForward();
private:
	unsigned int layerNumber, weightMatrixNumber;
	struct NetworkTopology networkTopology;
	std::vector<Layer *> layers;
	std::vector<Matrix *> weights;
};

#endif

