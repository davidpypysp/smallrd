#ifndef SMALLRD_RENDER_H_
#define SMALLRD_RENDER_H_


#include "display.h"
#include "camera.h"
#include "light.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "texture.h"

namespace smallrd {


class Render {
public:
	enum InterpolationMode {
		kFlat,
		kColor,
		kNormals,
	};

	Render();
	Render(Display *display);
	~Render();
	void BeginRender();
	void PutTriangle(Vector *vertex_list, Vector *normal_list, Vector *uv_list);
	bool PushMatrix(const Matrix &matrix);
	bool PopMatrix();
	void AddLight(const Light &light);
	void BeginAASampling();
	void AASampling();


	inline void set_display(Display *display) { display_ = display; }
	inline Display* display() const { return display_; }
	inline void set_camera(const Camera &camera) { camera_ = camera; }
	inline void set_ambient_light(const Light &light) { ambient_light_ = light; }
	inline void set_ka(const Vector &ka) { ka_ = ka; }
	inline void set_kd(const Vector &kd) { kd_ = kd; }
	inline void set_ks(const Vector &ks) { ks_ = ks; }
	inline void set_spec(const double spec) { spec_ = spec; }
	inline void set_interpolation_mode(const int mode) { interpolation_mode_ = mode; }
	inline void set_texture(Texture *texture) { texture_ = texture; }
	inline void set_x_offset(const double x_offset) { x_offset_ = x_offset; }
	inline void set_y_offset(const double y_offset) { y_offset_ = y_offset; }
	inline void set_weight(const double weight) { weight_ = weight; }
	inline bool aa_flag() const { return aa_flag_; }
	inline void set_aa_flag(const double aa_flag) { aa_flag_ = aa_flag; }
	inline void set_sample_render_flag(const double sample_render_flag) { sample_render_flag_ = sample_render_flag; }
	
private:
	static const int kMaxMatrixLevels = 10;
	static const int kMaxLights = 20;
	static const int kSamplingNum = 6;
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
	Texture *texture_;
	bool aa_flag_;
	Render *sample_renders_;
	bool sample_render_flag_;
	double x_offset_, y_offset_;
	double weight_;

	Vector Shade2(const Vector &normal);
	void ScanLineAlgorithm(Vector *vertex_list, Vector *normal_list, Vector *uv_list);
	void IncreaseByY(const Vector &slope, const double y, Vector &vertex);
	void InterpolateByX(const Vector &vertex1, const Vector &vertex2, Quaternion *plane_list);
	void SetPixelZBuffer(const Vector &vertex, Quaternion *plane_list);
	Vector ShadeEquation(const Vector &normal, const Vector &kt);
	Quaternion InterpolateValuePlane(Vector *point_list);
	double GetValueByPlane(const double x, const double y, const Quaternion &coefficient);
	



};

} // namespace smallrd

#endif // SMALLRD_RENDER_H_