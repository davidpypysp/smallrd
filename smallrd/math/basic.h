#ifndef SMALLRD_MATH_BASIC_H_
#define SMALLRD_MATH_BASIC_H_

#define _USE_MATH_DEFINES

#include <math.h>

namespace smallrd {

inline double DegreeToRadian(const double angle) { return angle * M_PI / 180.0; }


} // namespace smallrd


#endif // SMALLRD_MATH_BASIC_H_
