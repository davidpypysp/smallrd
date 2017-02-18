#ifndef SMALLRD_MATH_QUATERNION_H_
#define SMALLRD_MATH_QUATERNION_H_

#include <assert.h>

#include "math/vector.h"

namespace smallrd {


struct Quaternion {
	double x, y, z, w;

	explicit Quaternion() : x(0.0), y(0.0), z(0.0), w(0.0) {}
	explicit Quaternion(const double x, const double y, const double z, const double w) : x(x), y(y), z(z), w(w) {}
	explicit Quaternion(const Vector &vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0) {}

	inline Quaternion operator + (const Quaternion &b) const { return Quaternion(x + b.x, y + b.y, z + b.z, w + b.w); }
	inline Quaternion operator - (const Quaternion &b) const { return Quaternion(x - b.x, y - b.y, z - b.z, w - b.w); }
	inline Quaternion operator * (const double b) const { return Quaternion(x*b, y*b, z*b, w*b); }
	inline Quaternion& Homogenize() { x /= w; y /= w; z /= w; w = 1.0; return *this; }
	inline Vector ToVector() { return Vector(x/w, y/w, z/w); }

	inline double& operator [] (const int index) {
		switch (index) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: assert("Quaternion index out of range!");
		}
	}
};


} // namespace smallrd

#endif // SMALLRD_MATH_QUATERNION_H_
