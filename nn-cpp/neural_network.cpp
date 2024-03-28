
#include <cmath>
#include <vector>
#include <functional>
#include <iostream>
#include <random>
#include <cassert>
#include <map>
#include <fstream>
#include <string>

class Matrix {
	public:
		Matrix (const unsigned int rows, const unsigned int cols) {
			this->rows = rows;
			this->cols = cols;
			this->init([]() { // breakpoint //////////////////////////////////////////////////////////////////////////////////////////////////
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_real_distribution<> dis(0.0f, 1.0f);
				return dis(gen);
			});
		}
		Matrix (const unsigned int rows, const unsigned int cols, const std::function<float()>& initFunction) {
			this->rows = rows;
			this->cols = cols;
			this->init(initFunction);
		}
		~Matrix() = default;
		Matrix *getTransposed () {
			Matrix *transposed = new Matrix(this->cols, this->rows);
			transposed->matrixWeights.reserve(cols);
			for (unsigned int i=0; i<this->cols; i++) {
				transposed->matrixWeights[i].reserve(rows);
				for (unsigned int j=0; j<this->rows; j++) {
					transposed->matrixWeights[i][j] = this->matrixWeights[j][i];
				}
			}
			return transposed;
		}
		static Matrix *multiplyMatrices (Matrix* matrix_one, Matrix* matrix_two) {
			assert(matrix_one->getCols() == matrix_two->getRows());
			Matrix *product = new Matrix(matrix_one->getRows(), matrix_two->getCols(), []() { return 0.0f; });
			for (unsigned int i=0; i<matrix_one->getRows(); i++) {
				for (unsigned int j=0; j<matrix_two->getCols(); j++) {
					for (unsigned int k=0; k<matrix_one->getCols(); k++) {
						product->setValue(i, j, product->getValue(i, j) + matrix_one->getValue(i, k) * matrix_two->getValue(k, j));
					}
				}
			}
			return product;
		}
		static Matrix *addMatrices (Matrix* matrix_one, Matrix* matrix_two) {
			assert(matrix_one->getRows() == matrix_two->getRows() && matrix_one->getCols() == matrix_two->getCols());
			Matrix *sum = new Matrix(matrix_one->getRows(), matrix_one->getCols(), []() { return 0.0; });
			for (unsigned int i=0; i<sum->getRows(); i++) {
				for (unsigned int j=0; j<sum->getCols(); j++) {
					sum->setValue(i, j, matrix_one->getValue(i, j) + matrix_two->getValue(i, j));
				}
			}
			return sum;
		}
		static std::vector<float> matrixToVector (Matrix* matrix) {
			std::vector<float> vector;
			for (unsigned int i=0; i<matrix->getRows(); i++) {
				for (unsigned int j=0; j<matrix->getCols(); j++) {
					vector.push_back(matrix->getValue(i, j));
				}
			}
			return vector;
		}
		void dumpContent () {
			for (unsigned int i=0; i<this->rows; i++) {
				for (unsigned int j=0; j<this->cols; j++) {
					printf("%1.6f\t", this->matrixWeights[i][j]);
				}
				std::cout << std::endl;
			}
		}
		void setValue (unsigned int row, unsigned int col, float value) {
			matrixWeights[row][col] = value;
		}
		float getValue (unsigned int row, unsigned int col) {
			return this->matrixWeights[row][col];
		}
		unsigned int getRows () {
			return this->rows;
		}
		unsigned int getCols () {
			return this->cols;
		}
	private:
		unsigned int rows, cols;
		std::vector<std::vector<float>> matrixWeights;
		void init (const std::function<float()>& initFunction) {
			this->matrixWeights.reserve(this->rows);
			for (unsigned int i=0; i<this->rows; i++) {
				this->matrixWeights[i].reserve(this->cols); // breakpoint ////////////////////////////////////////////////////////////////
				for (unsigned int j=0; j<this->cols; j++) {
					this->matrixWeights[i][j] = initFunction();
				}
			}
		}
};

class Neuron {
	public:
		Neuron (float value, const std::function<float(float)>& activationFunction, const std::function<float(float)>& derivationFunction) {
			this->value = value;
			this->activationFunction = activationFunction;
			this->derivationFunction = derivationFunction;
		}
		~Neuron() = default;
		void setValue (float value) {
			this->value = value;
			activationFunction(this->value);
			derivationFunction(this->value);
		}
		void activate () {
			this->activatedValue = activationFunction(this->value);
		}
		void derive () {
			this->derivedValue = derivationFunction(this->value);
		}
		float getValue () {
			return value;
		}
		float getActivatedValue () {
			return activatedValue;
		}
		float getDerivedValue () {
			return derivedValue;
		}
	private:
		float value, activatedValue, derivedValue;
		std::function<float(float)> activationFunction, derivationFunction; 
};

class Layer {
	public:
		Layer(const int size, const std::function<float(float)>& activationFunction, const std::function<float(float)>& derivationFunction) {
			this->size = size;
			for (int i=0; i<size; i++) {
				Neuron *neuron = new Neuron(0.0f, activationFunction, derivationFunction);
				this->neurons.push_back(neuron);
			}
		}
		~Layer() = default;
		void setValue (int neuronIndex, float value) {
			neurons[neuronIndex]->setValue(value);
		}
		void setNeuronValue (unsigned int neuronIndex, float value) {
			neurons[neuronIndex]->setValue(value);
		}
		Matrix *parseValuesToMatrix () {
			Matrix *matrix = new Matrix(1, this->neurons.size()); // breakpoint //////////////////////////////////////////////////////////////
			for (unsigned int i=0; i<neurons.size(); i++) {
				matrix->setValue(0, i, this->neurons[i]->getValue());
			}
			return matrix;
		}
		Matrix *parseActivatedValuesToMatrix () {
			Matrix *matrix = new Matrix(1, this->neurons.size());
			for (unsigned int i=0; i<neurons.size(); i++) {
				this->neurons[i]->activate();
				matrix->setValue(0, i, this->neurons[i]->getActivatedValue());
			}
			return matrix;
		}
		Matrix *parseDerivedValuesToMatrix () {
			Matrix *matrix = new Matrix(1, this->neurons.size());
			for (unsigned int i=0; i<neurons.size(); i++) {
				this->neurons[i]->derive();
				matrix->setValue(0, i, this->neurons[i]->getDerivedValue());
			}
			return matrix;
		}
		void printData () {
			std::cout << "size                = " << size << std::endl;
			std::cout << "neurons vector size = " << neurons.size() << std::endl;
			for (unsigned int i=0; i<size; i++) {
				std::cout << i << " neuron value = " << neurons.at(i)->getValue() << std::endl;
			}
		}
		unsigned int getSize () {
			return size;
		}
	private:
		unsigned int size;
		std::vector<Neuron *> neurons;
};

struct LayerTopology {
	unsigned int neuronNumber;
	std::function<float(float)> activationFunction, derivationFunction;
};

class NeuralNetwork {
	public:
		NeuralNetwork (std::vector<struct LayerTopology> networkTopology) {
			this->layerNumber = networkTopology.size();
			this->matrixNumber = this->layerNumber-1;
			this->networkTopology = networkTopology;
			for (int i=0; i<this->layerNumber; i++) {
				Layer *layer = new Layer(this->networkTopology[i].neuronNumber,
					       this->networkTopology[i].activationFunction,
					       this->networkTopology[i].derivationFunction);
				this->layers.push_back(layer);
			}
			for (int i=0; i<this->matrixNumber; i++) {
				Matrix *matrix = new Matrix(this->networkTopology[i].neuronNumber, this->networkTopology[i+1].neuronNumber);
				this->weightMatrices.push_back(matrix);
			}
		}
		~NeuralNetwork() = default;
		void setInputValues (std::vector<float> inputValues) {
			assert(inputValues.size() == this->layers[0]->getSize());
			for (unsigned int i=0; i<inputValues.size() ; i++) {
				this->layers[0]->setValue(i, inputValues[i]);
			}
		}
		void feedForward () {
			this->layers[0]->printData();
			this->layers[1]->printData();
			this->layers[2]->printData();
			this->layers[0]->parseValuesToMatrix(); // breakpoint ////////////////////////////////////////////////////////////////////////////
		}
	private:
		int layerNumber;
		int matrixNumber;
		std::vector<struct LayerTopology> networkTopology;
		std::vector<Layer *> layers;
		std::vector<Matrix *> weightMatrices;
};

int main () {

	std::cout << std::endl;

	std::function<float(float)> activationFunction = [](float value) { return (1 / ( 1 + exp(-value))); },
				    derivationFunction = [](float value) { return (1 / ( 1 + exp(-value)) * (1 - 1 / 1 + std::exp(-value))); }; 
	std::vector<struct LayerTopology> networkTopology = {{3, activationFunction, derivationFunction}, {2, activationFunction, derivationFunction}, {3, activationFunction, derivationFunction}};
	NeuralNetwork *nw= new NeuralNetwork(networkTopology);
	std::vector<float> inputValues {3, 5, 4};
	nw->setInputValues(inputValues);
	nw->feedForward(); // breakpoint /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete nw;

	std::cout << std::endl;

	return 0;
}















