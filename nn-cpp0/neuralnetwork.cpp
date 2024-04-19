
#include "include/matrix.hpp"

class Neuron {
	public:
		Neuron (float value) {
			this->value = value;
		}
		void setValue (float value) {
			this->value = value;
		}
		float getValue () {
			return this->value;
		}
	private:
		float value;
};

class Layer {
	public:
		Layer (unsigned int size) {
			this->size = size;
			for (unsigned int i=0; i<this->size; i++) {
				Neuron *neuron = new Neuron(0.0);
				neurons.push_back(neuron);
			}
		}
		void setNeuronValue (int neuronIndex, float value) {
			neurons[neuronIndex]->setValue(value);
		}
		Matrix *getValuesMatrix () {
			Matrix *matrix = new Matrix(1, this->size);
			for (unsigned int i=0; i<this->size; i++) {
				matrix->setValue(0, i, neurons[i]->getValue());
			}
			return matrix;
		}
	private:
		unsigned int size;
		std::vector<Neuron *> neurons;
};

class NeuralNetwork {
	public:
		NeuralNetwork (std::vector<unsigned int> topology) {
			this->layerNumber = topology.size();
			this->topology = topology;
			for (unsigned int i=0; i<layerNumber; i++) {
				Layer *layer = new Layer(topology[i]);
				layers.push_back(layer);
			}
			for (unsigned int i=0; i<layerNumber-1; i++) {
				Matrix *matrix = new Matrix(this->topology[i], this->topology[i+1]);
				matrices.push_back(matrix);
			}
		}
		void setInputValues (std::vector<float> inputValues) {
			assert(this->topology[0] == inputValues.size());
			for (unsigned int i=0; i<this->topology[0]; i++) {
				layers[0]->setNeuronValue(i, inputValues[i]);
			}
		}
		void feedForward () {
			Matrix *values = layers[0]->getValuesMatrix();
			//values->printRowsCols();
			//values->dumpContent();
			
			std::cout << std::endl;

			Matrix *weights = matrices[0];
			//weights->printRowsCols();
			//weights->dumpContent();

			std::cout << std::endl;

			Matrix *mul = Matrix::multiplyMatrices(values, weights);
			mul->printRowsCols();
			mul->dumpContent();
			
			delete weights;
			delete values;
		}
	private:
		unsigned int layerNumber;
		std::vector<unsigned int> topology;
		std::vector<Layer *> layers;
		std::vector<Matrix *> matrices;
};

int main () {

	NeuralNetwork *ann = new NeuralNetwork({3, 2, 3});
	ann->setInputValues({2, 3, 2});
	ann->feedForward();

	return 0;
}

