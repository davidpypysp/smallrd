#ifndef SMALLRD_MATH_VECTOR_H_
#define SMALLRD_MATH_VECTOR_H_

#include <assert.h>
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
	inline Vector operator / (const double b) const { return Vector(x / b, y / b, z / b); }
	inline Vector& operator = (const Vector &b) { x = b.x; y = b.y; z = b.z; return *this; }
	inline Vector& Normalize() { return *this = *this * (1.0 / sqrt(x*x + y*y + z*z)); }
	inline Vector Multiply(const Vector &b) const { return Vector(x*b.x, y*b.y, z*b.z); }

	inline double& operator [] (const int index) {
		switch (index) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: assert("Vector index out of range!");
		}
	}

};


} // namespace smallrd


#endif // SMALLRD_MATH_VECTOR_H_