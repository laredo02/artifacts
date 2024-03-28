
#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <functional>
#include <iostream>
#include <vector>

class Matrix {
	public:
		Matrix(int rows, int cols);
		void init(const std::function<float()>& randFunc);
		Matrix *traspose();
		void dump();
		float getValue(int row, int col);
		void setValue(int row, int col, float val);
	private:
		int rows, cols;
		std::vector<std::vector<float>> values;
};

#endif
