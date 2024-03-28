
#ifndef _MATRIX
#define _MATRIX

#include <memory>
#include <vector>

class Matrix {
public:
	Matrix(unsigned int rows, unsigned int cols, bool randomInit);
	void zeroInit();
	void randomInit();

	std::shared_ptr<Matrix> transpose();
	static std::shared_ptr<Matrix> multiply(Matrix *m1, Matrix *m2);
	static std::shared_ptr<Matrix> add(Matrix *m1, Matrix *m2);

	void dumpData();
	unsigned int getCols();
	unsigned int getRows();
	void setValue(const unsigned int row, const unsigned int col, const float value);
	float getValue(const unsigned int row, const unsigned int col);
private:
	unsigned int rows, cols;
	std::vector<std::vector<float>> matrixData;
};

#endif

