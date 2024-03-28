
#ifndef _LAYER_HPP
#define _LAYER_HPP

#include <iostream>
#include <vector>

#include "../include/neuron.hpp"

class Layer {
	public:
		Layer(int size);
	private:
		int size;
		std::vector<Neuron *> neurons;
};

#endif

