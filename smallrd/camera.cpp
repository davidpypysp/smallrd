#include "camera.h"

#include <math.h>

#include "math/basic.h"


namespace smallrd {

Camera::Camera(const Vector &position, const Vector &look_at, const Vector &world_up, const double fov)
	: position(position),
	  look_at(look_at),
	  world_up(world_up),
	  fov(fov) {
	double one_d = tan(DegreeToRadian(fov / 2.0));
	x_pi = {
		{ 1.0, 0.0, 0.0,   0.0 },
		{ 0.0, 1.0, 0.0,   0.0 },
		{ 0.0, 0.0, one_d, 0.0 },
		{ 0.0, 0.0, one_d, 1.0 }
	};

	Vector row_z = (look_at - position).Normalize();
	Vector row_y = (world_up - row_z * (world_up * row_z));
	Vector row_x = row_y % row_z;
	x_iw = {
		{ row_x.x, row_x.y, row_x.z, -(row_x * position) },
		{ row_y.x, row_y.y, row_y.z, -(row_y * position) },
		{ row_z.x, row_z.y, row_z.z, -(row_z * position) },
		{ 0.0,     0.0,     0.0,     1.0 }
	};

}

} // namespace smallrd


