#ifndef SMALLRD_RENDER_H_
#define SMALLRD_RENDER_H_

#include "my_math.h"
#include "display.h"


namespace smallrd {

class Render {
public:
	Render(Display *display);
	void BeginRender();
	void PutTriangle(Vector *vertex_list, Vector *normal_list, Vector *uv_list = NULL);
	
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

	Vector Shade2(const Vector normal);
	void ScanLineAlgorithm(Vector *vertex_list);
	inline Vector IncreaseByY(const Vector vertex, const double slope_x, const double slope_z, const double y);
	void InterpolateByX(const Vector vertex1, const Vector vertex2);
	inline void SetPixelZBuffer(const Vector vertex);
	



};

} // namespace smallrd

#endif // SMALLRD_RENDER_H_