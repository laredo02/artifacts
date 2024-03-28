
#include <functional>
#include <iostream>
#include <vector>

#include "../include/matrix.hpp"

Matrix::Matrix (int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
}

/* Uniform Random Distribution:
 * std::random_device rd;
 * std::mt19937 gen(rd());
 * std::uniform_real_distribution<> dis(0.0, 1.0);
 * return dis(gen); */
void Matrix::init (const std::function<float()>& randFunc) {
	values.reserve(this->rows);
	for (int i=0; i<this->rows; i++) {
		values[i].reserve(this->cols);
		for (int j=0; j<this->cols; j++) {
			values[i][j] = randFunc();
		}
	}
}

Matrix *Matrix::traspose () {
	Matrix *trasposedMatrix = new Matrix(this->cols, this-> rows);
	trasposedMatrix->values.reserve(cols);
	for (int i=0; i<this->cols; i++) {
		trasposedMatrix->values[i].reserve(this->rows);
		for (int j=0; j<this->rows; j++) {
			trasposedMatrix->values[i][j] = values[j][i];
		}
	}
	return trasposedMatrix;
}

void Matrix::dump () {
	printf("rows = %d, cols = %d\n", this->rows, this->cols);
	for (int i=0; i<this->rows; i++) {
		for (int j=0; j<this->cols; j++) {
			printf("%1.6f\t", values[i][j]);
		}
		std::cout << std::endl;
	}

}

float Matrix::getValue (int row, int col) {
	return values[row][col];
}

void Matrix::setValue (int row, int col, float val) {
	values[row][col] = val;
}

