
#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <functional>

class Matrix {
	public:
		Matrix (const unsigned int rows, const unsigned int cols) {
			this->rows = rows;
			this->cols = cols;
			this->init([]() {
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
		void printRowsCols () {
			std::cout << "rows = " << this->rows << "\tcols = " << this->cols << std::endl;
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
			std::cout << "cols = " << this->cols << " rows = " << this->rows << std::endl;			
			this->matrixWeights.reserve(this->rows);
			for (unsigned int i=0; i<this->rows; i++) {
				this->matrixWeights[i].reserve(this->cols);
				for (unsigned int j=0; j<this->cols; j++) {
					this->matrixWeights[i][j] = initFunction();
				}
			}
		}
};

#endif

