#include "my_math.h"
#include <iostream>
#include <vector>
#include <iterator>

using std::begin;

namespace smallrd {

Vector::Vector(const double x, const double y, const double z) : x(x), y(y), z(z) {
}

Matrix::Matrix() {
	memset(this->value, 0, sizeof(this->value));
}

Matrix::Matrix(const double value[16]) {
	memcpy(this->value, value, sizeof(this->value));
}

Matrix::Matrix(const double value[4][4]) {
	memcpy(this->value, value, sizeof(this->value));
}

} // namespace smallrd


