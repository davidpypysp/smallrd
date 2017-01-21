#ifndef SMALLRD_MY_MATH_H_
#define SMALLRD_MY_MATH_H_

namespace smallrd {

struct Vector {
	double x, y, z;

	Vector(const double x = 0.0, const double y = 0.0, const double z = 0.0);

	inline double r() const { return x; }
	inline void set_r(const double r) { x = r; }
	inline double g() const { return y; }
	inline void set_g(const double g) { y = g; }
	inline double b() const { return z; }
	inline void set_b(const double b) { z = b; }


};

struct Matrix {
	double value[4][4];

	explicit Matrix();
	explicit Matrix(const double value[16]);
	explicit Matrix(const double value[4][4]);

};

} // namespace smallrd


#endif // SMALLRD_MY_MATH_H_
