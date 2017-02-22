#include "render.h"

namespace smallrd {

Render::Render(Display *display)
	: display_(display),
	  camera_(Vector(-10.0, 5.0, -10.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), 35.0),
	  texture_(NULL) {
	double kHalfXs = display_->x_resolution() / 2.0, kHalfYs = display_->y_resolution() / 2.0;
	x_sp_ = {
		{ kHalfXs, 0.0, 0.0, kHalfXs },
		{ 0.0, -kHalfYs, 0.0, kHalfYs },
		{ 0.0, 0.0, INT_MAX, 0.0 },
		{ 0.0, 0.0, 0.0, 1.0 }
	};

	interpolation_mode_ = kFlat;
	num_lights_ = 0;
	ka_ = { 0.1, 0.1, 0.1 };
	kd_ = { 0.7, 0.6, 0.5 };
	ks_ = { 0.2, 0.3, 0.4 };
	spec_ = 32.0;
}

Render::~Render() {
	delete display_;
}

void Render::BeginRender() {
	display_->Init();

	matrix_level_ = 0;
	x_image_[0].Identify();
	x_norm_[0].Identify();

	PushMatrix(x_sp_);
	PushMatrix(camera_.x_pi);
	PushMatrix(camera_.x_iw);


}

void Render::PutTriangle(Vector *vertex_list, Vector *normal_list, Vector *uv_list) {
	if(interpolation_mode_ == kFlat) flat_color_ = Shade2(normal_list[0]);

	Vector screen_vertex_list[3], image_normal_list[3], image_uv_list[3];
	for (int i = 0; i < 3; ++i) {
		screen_vertex_list[i] = (x_image_[matrix_level_] * Quaternion(vertex_list[i])).ToVector();
		if (screen_vertex_list[i].z < 0) return; // Skip any triangle with a negative screen-z vertex
		image_normal_list[i] = (x_norm_[matrix_level_] * Quaternion(normal_list[i])).ToVector();
		image_uv_list[i] = uv_list[i] / (screen_vertex_list[i].z / (double)(INT_MAX - screen_vertex_list[i].z) + 1.0);
	}

	ScanLineAlgorithm(screen_vertex_list, image_normal_list, image_uv_list);
}

bool Render::PushMatrix(const Matrix &matrix) {
	if (matrix_level_ >= kMaxMatrixLevels) return false;
	x_image_[matrix_level_ + 1] = x_image_[matrix_level_] * matrix;

	//x_norm_ setting
	if (matrix_level_ < 2) {
		x_norm_[matrix_level_ + 1].Identify();
	} else {
		Matrix rotation_only = matrix;
		rotation_only[0][3] = rotation_only[1][3] = rotation_only[2][3] = 0.0; // skip traslation matrix
		double scale_factor = sqrt(rotation_only[0][0] * rotation_only[0][0] + rotation_only[1][0] * rotation_only[1][0] + rotation_only[2][0] * rotation_only[2][0]);
		assert(scale_factor != 0.0);
		// skip uniform scaling matrix
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) 
				rotation_only[i][j] /= scale_factor;
		}
		x_norm_[matrix_level_ + 1] = x_norm_[matrix_level_] * rotation_only;
	}
	++matrix_level_;
	return true;
}

bool Render::PopMatrix() {
	if (matrix_level_ <= 0) return false;
	--matrix_level_;
	return true;
}

void Render::AddLight(const Light &light) {
	if (num_lights_ < kMaxLights) 
		lights_[num_lights_++] = light;
}

Vector Render::Shade2(const Vector &normal) {
	Vector light(0.707, 0.5, 0.5);
	double coefficient = abs(light * normal);
	if (coefficient > 1.0) coefficient = 1.0;
	Vector color = Vector(0.95, 0.65, 0.88) * coefficient;
	return color;
}

void Render::ScanLineAlgorithm(Vector *vertex_list, Vector *normal_list, Vector *uv_list) {
	Vector interpolate_value_list[3];
	Quaternion plane_coefficient_list[5];
	if (interpolation_mode_ == kColor) {
		Vector vertex_color_list[3];
		for (int i = 0; i < 3; ++i)
			vertex_color_list[i] = ShadeEquation(normal_list[i], Vector()); // get each vertex's color by shading equation with its normal
		for (int index = 0; index < 3; ++index) {
			for (int i = 0; i < 3; ++i) 
				interpolate_value_list[i] = { vertex_list[i].x, vertex_list[i].y, vertex_color_list[i][index] }; // { {x, y, r}, {x, y, g}, {x, y, b}
			plane_coefficient_list[index] = InterpolateValuePlane(interpolate_value_list); // coefficient for getting color value on plane
		}
	} else if (interpolation_mode_ == kNormals) {
		for (int index = 0; index < 3; ++index) {
			for (int i = 0; i < 3; ++i)
				interpolate_value_list[i] = { vertex_list[i].x, vertex_list[i].y, normal_list[i][index] };
			plane_coefficient_list[index] = InterpolateValuePlane(interpolate_value_list); //coefficient for getting normal value on plane
		}
	}
	if (texture_ != NULL) {
		for (int index = 3; index < 5; ++index) {
			for (int i = 0; i < 3; ++i)
				interpolate_value_list[i] = { vertex_list[i].x, vertex_list[i].y, uv_list[i][index - 3] };
			plane_coefficient_list[index] = InterpolateValuePlane(interpolate_value_list); //coefficient for u, v value on plane
		}
	}



	// sorted 3 vertices
	int max_index = 0, min_index = 0;
	for (int i = 1; i < 3; i++) {
		if ( vertex_list[i].y < vertex_list[min_index].y ||
			(vertex_list[i].y == vertex_list[min_index].y && vertex_list[i].x < vertex_list[min_index].x) ) 
			min_index = i;
		if ( vertex_list[i].y > vertex_list[max_index].y || 
			(vertex_list[i].y == vertex_list[max_index].y && vertex_list[i].x > vertex_list[max_index].x) ) 
			max_index = i;
	}
	Vector &min_vertex = vertex_list[min_index];
	Vector &mid_vertex = vertex_list[3 - max_index - min_index];
	Vector &max_vertex = vertex_list[max_index];

	// 3 vertices in same line case
	if (min_index == max_index) {
		if (min_vertex.y == ceil(min_vertex.y)) InterpolateByX(min_vertex, max_vertex, plane_coefficient_list);
		return;
	}

	// do interpolation along y
	Vector edge1[2] = { min_vertex, max_vertex }, edge2[2] = { min_vertex, mid_vertex };
	bool switch_edge_flag = false;
	if (min_vertex.y == mid_vertex.y) { // special case
		edge2[0] = mid_vertex, edge2[1] = max_vertex;
		switch_edge_flag = true;
	}
	Vector current_vertex1 = edge1[0], current_vertex2 = edge2[0];
	Vector slope1 = Vector((edge1[1].x - edge1[0].x) / (edge1[1].y - edge1[0].y), 1.0, (edge1[1].z - edge1[0].z) / (edge1[1].y - edge1[0].y));
	Vector slope2 = Vector((edge2[1].x - edge2[0].x) / (edge2[1].y - edge2[0].y), 1.0, (edge2[1].z - edge2[0].z) / (edge2[1].y - edge2[0].y));
	for (double y = ceil(min_vertex.y); y <= max_vertex.y; y += 1.0) {
		if (!switch_edge_flag && y > mid_vertex.y) {
			edge2[0] = mid_vertex, edge2[1] = max_vertex;
			current_vertex2 = edge2[0];
			slope2.x = (edge2[1].x - edge2[0].x) / (edge2[1].y - edge2[0].y);
			slope2.z = (edge2[1].z - edge2[0].z) / (edge2[1].y - edge2[0].y);
			switch_edge_flag = true;
		}
		IncreaseByY(slope1, y, current_vertex1);
		IncreaseByY(slope2, y, current_vertex2);
		InterpolateByX(current_vertex1, current_vertex2, plane_coefficient_list);
	}


}

inline void Render::IncreaseByY(const Vector &slope, const double y, Vector &vertex) {
	double dy = y - vertex.y;
	vertex.x += slope.x * dy;
	vertex.y = y;
	vertex.z += slope.z * dy;
}

void Render::InterpolateByX(const Vector &vertex1, const Vector &vertex2, Quaternion *plane_coefficient_list) {
	if(vertex1.x == vertex2.x) {
		Vector vertex = (vertex1.z < vertex2.z ? vertex1 : vertex2);
		SetPixelZBuffer(vertex, plane_coefficient_list);
		return;
	}
	if (vertex1.x > vertex2.x) { //keep left to right order
		InterpolateByX(vertex2, vertex1, plane_coefficient_list);
		return;
	}

	double slope_z = (vertex2.z - vertex1.z) / (vertex2.x - vertex1.x);
	Vector current_vertex = vertex1;
	for (double x = ceil(vertex1.x); x <= vertex2.x; x += 1.0) {
		current_vertex.z += slope_z * (x - current_vertex.x);
		current_vertex.x = x;
		SetPixelZBuffer(current_vertex, plane_coefficient_list);
	}
}

void Render::SetPixelZBuffer(const Vector &vertex, Quaternion *plane_coefficient_list) {
	Pixel pixel = display_->GetPixel(vertex.x, vertex.y); 
	if (vertex.z <= (double)pixel.z) {
		Vector color, kt(1.0, 1.0, 1.0);
		if (texture_ != NULL) {
			Vector uv = Vector(
				GetValueByPlane(vertex.x, vertex.y, plane_coefficient_list[3]),
				GetValueByPlane(vertex.x, vertex.y, plane_coefficient_list[4]),
				0
				);
			uv = uv * (vertex.z / (double)(INT_MAX - vertex.z) + 1.0);
			texture_->GetColorByUV(uv, kt);
		}

		if (interpolation_mode_ == kFlat) {
			color = flat_color_;
		} else if (interpolation_mode_ == kColor) {
			for (int i = 0; i < 3; ++i) {
				color[i] = GetValueByPlane(vertex.x, vertex.y, plane_coefficient_list[i]);
				color[i] = ClampValue(color[i], 0.0, 1.0);
			}
			color = kt.Multiply(color);
		} else if (interpolation_mode_ == kNormals) {
			Vector normal;
			for(int i = 0; i < 3; ++i)
				normal[i] = GetValueByPlane(vertex.x, vertex.y, plane_coefficient_list[i]);
			normal.Normalize();
			color = ShadeEquation(normal, kt);
		}
		pixel.r = ColorToShortType(ClampValue(color.r(), 0.0, 1.0));
		pixel.g = ColorToShortType(ClampValue(color.g(), 0.0, 1.0));
		pixel.b = ColorToShortType(ClampValue(color.b(), 0.0, 1.0));
		pixel.z = vertex.z; //remove hidden surface
		display_->SetPixel(vertex.x, vertex.y, pixel);
	}
}

Vector Render::ShadeEquation(const Vector &normal, const Vector &kt) { // the shading equation 
	Vector e(0.0, 0.0, -1.0), s, d;
	double n_dot_e = normal * e;
	for (int i = 0; i < num_lights_; ++i) {
		Light &light = lights_[i];
		double n_dot_l = normal * light.direction;
		if (n_dot_l * n_dot_e <= 0.0) continue; // special case
		Vector n = normal;
		if(n_dot_l < 0.0 && n_dot_e < 0.0) n = n * -1, n_dot_l *= -1; // special case

		Vector r = (n * 2 * n_dot_l - light.direction).Normalize();
		double r_dot_e = r * e;
		if (r_dot_e < 0.0) r_dot_e = 0.0;

		s = s + light.color * pow(r_dot_e, spec_);
		d = d + light.color * n_dot_l;
	}
	if (texture_ == NULL) {
		return ks_.Multiply(s) + kd_.Multiply(d) + ka_.Multiply(ambient_light_.color);
	} else { // with texture
		if (interpolation_mode_ == kColor) { // no kt here, it's delaying to product in the end;
			return s + d + ambient_light_.color; 
		} else if (interpolation_mode_ == kNormals) {
			return ks_.Multiply(s) + kt.Multiply(d) + kt.Multiply(ambient_light_.color);
		}
	}
}

inline Quaternion Render::InterpolateValuePlane(Vector *point_list) {
	Vector vector1 = point_list[1] - point_list[0], vector2 = point_list[2] - point_list[1];
	Vector normal = vector1 % vector2;
	//quaternion coefficient: A = x B = y C = z D = w
	return Quaternion(normal.x, normal.y, normal.z, -(point_list[0].x * normal.x + point_list[0].y * normal.y + point_list[0].z * normal.z));

}

inline double Render::GetValueByPlane(const double x, const double y, const Quaternion &coefficient) {
	//quaternion coefficient: A = x B = y C = z D = w
	return -(coefficient.w + coefficient.x * x + coefficient.y * y) / coefficient.z;
}







} // namespace smallrd
