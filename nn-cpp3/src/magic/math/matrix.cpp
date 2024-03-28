
#include <cassert>
#include <iostream>
#include <memory>
#include <random>

#include "matrix.hpp"

Matrix::Matrix (unsigned int rows, unsigned int cols, bool randomInit) {
	this->rows = rows;
	this->cols = cols;
	if (randomInit) {
		this->randomInit();
	} else zeroInit();
}

void Matrix::zeroInit () {
	std::cout << "rows = " << this->rows << std::endl;
	std::cout << "cols = " << this->cols << std::endl;
	this->matrixData.reserve(this->rows);
	for (unsigned int i=0; i<this->rows; i++) {
		this->matrixData[i].reserve(this->cols);
		for (unsigned int j=0; j<this->cols; j++) {
			printf("i=%d j=%d\n", i, j);
			this->matrixData[i][j] = 0.0f; 					// i=0; j=1
		}
	}
}

void Matrix::randomInit () {
	this->matrixData.reserve(this->rows);
	for (unsigned int i=0; i<this->rows; i++) {
		this->matrixData[i].reserve(this->cols);
		for (unsigned int j=0; j<this->cols; j++) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0.0f, 1.0f);
			this->matrixData[i][j] = dis(gen);
		}
	}
}

std::shared_ptr<Matrix> Matrix::transpose () {
    std::shared_ptr<Matrix> pTransposed;
    pTransposed->zeroInit();
	for (unsigned int i=0; i<pTransposed->rows; i++) {
		for (unsigned int j=0; j<pTransposed->cols; i++) {
            		pTransposed->setValue(j, i, this->getValue(i, j));
		}
	}
	return pTransposed;
}

std::shared_ptr<Matrix> Matrix::multiply (Matrix *m1, Matrix *m2) {
	assert(m1->getCols() == m2->getRows());
	std::shared_ptr<Matrix> pProduct = std::make_shared<Matrix>(m1->getRows(), m2->getCols(), false);
	for (unsigned int i=0; i<m1->getRows(); i++) {
		for (unsigned int j=0; j<m2->getCols(); j++) {
			for (unsigned int k=0; k<m1->getRows(); k++) { // = for (unsigned int k=0; k<m2.getCols(); k++) {
				float value = pProduct->getValue(i, j) + m1->getValue(i, k) * m2->getValue(k, j);
				pProduct->setValue(i, j, value);
			}
		}
	}
	return pProduct;
}

std::shared_ptr<Matrix> Matrix::add (Matrix *m1, Matrix *m2) {
    assert(m1->getRows() == m2->getRows() && m1->getCols() == m2->getRows());
    std::shared_ptr<Matrix> pSum = std::make_shared<Matrix>(m1->getRows(), m1->getCols(), false);
    for (unsigned int i=0; i<pSum->getRows(); i++) {
        for (unsigned int j=0; j<pSum->getCols(); j++) {
            float value = m1->getValue(i, j) + m2->getValue(i, j);
            pSum->setValue(i, j, value);
        }
    }
    return pSum;
}

void Matrix::dumpData () {
	for (unsigned int i=0; i<this->rows; i++) {
		for (unsigned int j=0; j<this->cols; j++) {
			printf("%1.6f\t", this->matrixData[i][j]);
		}
		std::cout << std::endl;
	}
}

unsigned int Matrix::getRows () {
	return this->rows;
}

unsigned int Matrix::getCols () {
	return this->cols;
}

void Matrix::setValue (const unsigned int row, const unsigned int col, const float value) {
	this->matrixData[row][col] = value;
}

float Matrix::getValue (const unsigned int row, const unsigned int col) {
	return this->matrixData[row][col];
}

