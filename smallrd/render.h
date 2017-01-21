#ifndef SMALLRD_RENDER_H_
#define SMALLRD_RENDER_H_

#include "my_math.h"
#include "display.h"


namespace smallrd {

class Render {
public:
	Render(Display *display);
	void BeginRender();
	void PutTriangle(Vector *vertex_list, Vector *normal_list = NULL, Vector *uv_list = NULL);
	
	inline void set_flat_color(const Vector color) { flat_color_ = color; }


private:
	static const int kMaxMatrixLevels = 10;
	Display *display_;
	// Todo: camera
	int matrix_level_;
	Matrix ximage_[kMaxMatrixLevels];
	Matrix xnorm_[kMaxMatrixLevels];
	Matrix xsp_;
	Vector flat_color_;
	int interpolation_mode_;
	int num_lights_;
	// Todo: lights[kMaxLights]
	// Todo: ambientlight;
	Vector ka_, kd_, ks_;
	float spec_;
	// Todo: tex_func




};

} // namespace smallrd

#endif // SMALLRD_RENDER_H_