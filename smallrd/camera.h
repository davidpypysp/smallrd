#ifndef SMALLRD_CAMERA_H_
#define SMALLRD_CAMERA_H_

#include "math/vector.h"
#include "math/matrix.h"

namespace smallrd {

struct Camera {
	Matrix x_iw;
	Matrix x_pi;
	Vector position;
	Vector look_at;
	Vector world_up;
	double fov;

	Camera(const Vector &position, const Vector &look_at, const Vector &world_up, const double fov);

};


} //namespace smallrd





#endif // SMALLRD_CAMERA_H_
