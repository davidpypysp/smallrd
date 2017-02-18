#ifndef SMALLRD_LIGHT_H_
#define SMALLRD_LIGHT_H_

#include "math/vector.h"

namespace smallrd {

struct Light {
	Vector direction;
	Vector color;

	Light() : direction(), color() {}
	Light(const Vector &direction, const Vector &color) : direction(direction), color(color) {}
};

}



#endif // SMALLRD_LIGHT_H_

