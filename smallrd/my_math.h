#ifndef SMALLRD_MY_MATH_H_
#define SMALLRD_MY_MATH_H_

#include <math.h>

namespace smallrd {

struct Vector {
	double x, y, z;

	Vector(const double x = 0.0, const double y = 0.0, const double z = 0.0) : x(x), y(y), z(z) {};

	inline double r() const { return x; }
	inline void set_r(const double r) { x = r; }
	inline double g() const { return y; }
	inline void set_g(const double g) { y = g; }
	inline double b() const { return z; }
	inline void set_b(const double b) { z = b; }

	inline Vector operator + (const Vector &b) const { return Vector(x + b.x, y + b.y, z + b.z); }
	inline Vector operator - (const Vector &b) const { return Vector(x - b.x, y - b.y, z - b.z); }
	inline Vector operator * (const double b) const { return Vector(x*b, y*b, z*b); }
	inline double operator * (const Vector &b) const { return x*b.x + y*b.y + z*b.z; } // dot product
	inline Vector operator % (const Vector &b) const { return Vector(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x); } // cross product
	inline Vector& Normalize() { return *this = *this * (1.0 / sqrt(x*x + y*y + z*z)); }
	inline Vector Multiply(const Vector &b) const { return Vector(x*b.x, y*b.y, z*b.z); }


};

struct Matrix {
	double value[4][4];

	explicit Matrix();
	explicit Matrix(const double value[16]);
	explicit Matrix(const double value[4][4]);

};

} // namespace smallrd


#endif // SMALLRD_MY_MATH_H_
