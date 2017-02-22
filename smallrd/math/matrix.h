#ifndef SMALLRD_MATH_MATRIX_H_
#define SMALLRD_MATH_MATRIX_H_

#include <iostream>
#include "math/quaternion.h"

namespace smallrd {

struct Matrix {
	double value[4][4];

	explicit Matrix() { memset(value, 0, sizeof(value)); }

	Matrix(const std::initializer_list<double> &list) {
		assert(list.size() == 16);
		int i = 0;
		for (double v : list) {
			this->value[i / 4][i % 4] = v;
			i++;
		}
	}

	Matrix(const std::initializer_list<std::initializer_list<double>> &lists) {
		assert(lists.size() == 4);
		int i = 0;
		for (std::initializer_list<double> list : lists) {
			assert(list.size() == 4);
			for (double v : list) {
				this->value[i / 4][i % 4] = v;
				i++;
			}
		}
	}

	inline double* operator [] (const int index) {
		return value[index];
	}

	inline void Identify() {
		memset(value, 0, sizeof(value));
		value[0][0] = value[1][1] = value[2][2] = value[3][3] = 1.0;
	}

	inline Matrix Matrix::operator + (const Matrix &b) {
		Matrix result;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.value[i][j] = value[i][j] + b.value[i][j];
		return result;
	}

	inline Matrix Matrix::operator * (const Matrix &b) {
		Matrix result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) result.value[i][j] += value[i][k] * b.value[k][j];
			}
		}
		return result;
	}

	inline Matrix Matrix::operator * (const double k) {
		Matrix result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) result.value[i][j] = value[i][j] * k;
		}
		return result;
	}

	inline Quaternion operator * (const Quaternion &b) {
		Quaternion result(
			value[0][0] * b.x + value[0][1] * b.y + value[0][2] * b.z + value[0][3] * b.w,
			value[1][0] * b.x + value[1][1] * b.y + value[1][2] * b.z + value[1][3] * b.w,
			value[2][0] * b.x + value[2][1] * b.y + value[2][2] * b.z + value[2][3] * b.w,
			value[3][0] * b.x + value[3][1] * b.y + value[3][2] * b.z + value[3][3] * b.w
		);
		return result;
	}

};

} // namespace smallrd


#endif // SMALLRD_MATH_MATRIX_H_

