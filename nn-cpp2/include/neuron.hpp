
#ifndef _NEURON_HPP
#define _NEURON_HPP

#include <iostream>
#include <functional>

class Neuron {
	public:
		Neuron(float val);
		void activate(std::functional<float>& func); // fast sigmoid function f(x) = x / (1 + |x|);
		void setVal(float val);
		void derive(); // f'(x) = f(x) * (1 - f(x))
		float getVal() { return this->val; }
		float getActivatedVal() { return this->activatedVal; }
		float getDerivedVal() { return this->derivedVal; }

	private:
		std::functional<float> activationFunction;
		float val; // value
		float activatedValue; // activation function value
		float derivedVal; // derived value
};

#endif

