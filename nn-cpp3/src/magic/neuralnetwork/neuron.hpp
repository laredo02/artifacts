
#ifndef _NEURON
#define _NEURON

class Neuron {
public:
	Neuron(float value);

	float getValue();
	void setValue(float value);
private:
	float value;
};

#endif

