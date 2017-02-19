#ifndef SMALLRD_RENDER_H_
#define SMALLRD_RENDER_H_


#include "display.h"
#include "camera.h"
#include "light.h"
#include "math/vector.h"
#include "math/matrix.h"

namespace smallrd {


class Render {
public:
	enum InterpolationMode {
		kFlat,
		kColor,
		kNormals,
	};

	Render(Display *display);
	~Render();
	void BeginRender();
	void PutTriangle(Vector *vertex_list, Vector *normal_list, Vector *uv_list = NULL);
	bool PushMatrix(const Matrix &matrix);
	bool PopMatrix();
	void AddLight(const Light &light);
	inline void set_camera(const Camera &camera) { camera_ = camera; }
	inline void set_ambient_light(const Light &light) { ambient_light_ = light; }
	inline void set_ka(const Vector &ka) { ka_ = ka; }
	inline void set_kd(const Vector &kd) { kd_ = kd; }
	inline void set_ks(const Vector &ks) { ks_ = ks; }
	inline void set_spec(const double spec) { spec_ = spec; }
	inline void set_interpolation_mode(const int mode) { interpolation_mode_ = mode; }
	
private:
	static const int kMaxMatrixLevels = 10;
	static const int kMaxLights = 20;
	Display *display_;
	Camera camera_;
	int matrix_level_;
	Matrix x_image_[kMaxMatrixLevels];
	Matrix x_norm_[kMaxMatrixLevels];
	Matrix x_sp_;
	Vector flat_color_;
	int interpolation_mode_;
	int num_lights_;
	Light lights_[kMaxLights];
	Light ambient_light_;
	Vector ka_, kd_, ks_;
	double spec_;
	// Todo: tex_func

	Vector Shade2(const Vector &normal);
	void ScanLineAlgorithm(Vector *vertex_list, Vector *normal_list);
	inline Vector& IncreaseByY(const double slope_x, const double slope_z, const double y, Vector &vertex);
	void InterpolateByX(const Vector &vertex1, const Vector &vertex2, Quaternion *plane_list);
	void SetPixelZBuffer(const Vector &vertex, Quaternion *plane_list);
	Vector ShadeEquation(const Vector &normal);
	Quaternion InterpolateValuePlane(Vector *point_list);
	Vector GetValueByPlane(const double x, const double y, Quaternion *plane_list);
	



};

} // namespace smallrd

#endif // SMALLRD_RENDER_H_