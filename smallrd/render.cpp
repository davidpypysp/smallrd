#include "render.h"

namespace smallrd {

Render::Render(Display *display) : display_(display) {
}

Render::~Render() {
	delete display_;
}

void Render::BeginRender() {
	display_->Init();
}

void Render::PutTriangle(Vector *vertex_list, Vector *normal_list, Vector *uv_list) {
	flat_color_ = Shade2(normal_list[0]);
	ScanLineAlgorithm(vertex_list);
}


Vector Render::Shade2(const Vector &normal) {
	Vector light(0.707, 0.5, 0.5);
	double coeffcient = light * normal;

	coeffcient = abs(coeffcient);
	if (coeffcient > 1.0) coeffcient = 1.0;

	Vector color = Vector(0.95, 0.65, 0.88) * coeffcient;
	return color;
}

void Render::ScanLineAlgorithm(Vector *vertex_list) {
	int max_index = 0, min_index = 0;
	for (int i = 1; i < 3; i++) {
		if (vertex_list[i].y < vertex_list[min_index].y ||
			(vertex_list[i].y == vertex_list[min_index].y && vertex_list[i].x < vertex_list[min_index].x)) {
			min_index = i;
		}
		if (vertex_list[i].y > vertex_list[max_index].y || 
			(vertex_list[i].y == vertex_list[max_index].y && vertex_list[i].x > vertex_list[max_index].x)) {
			max_index = i;
		}
	}

	// sorted 3 vertices
	Vector &min_vertex = vertex_list[min_index];
	Vector &mid_vertex = vertex_list[3 - max_index - min_index];
	Vector &max_vertex = vertex_list[max_index];

	// 3 vertices in same line case
	if (min_index == max_index) {
		if (min_vertex.y == ceil(min_vertex.y)) InterpolateByX(min_vertex, max_vertex);
		return;
	}

	// do interpolation along y
	Vector &line1_down_vertex = min_vertex, &line1_up_vertex = max_vertex;
	Vector &line2_down_vertex = min_vertex, &line2_up_vertex = mid_vertex;
	bool switch_line_flag = false;
	if (min_vertex.y == mid_vertex.y) { 
		line2_down_vertex = mid_vertex, line2_up_vertex = max_vertex;
		switch_line_flag = true;
	}
	Vector current_vertex1 = line1_down_vertex, current_vertex2 = line2_down_vertex;
	double line1_slope_x = (line1_up_vertex.x - line1_down_vertex.x) / (line1_up_vertex.y - line1_down_vertex.y);
	double line1_slope_z = (line1_up_vertex.z - line1_down_vertex.z) / (line1_up_vertex.y - line1_down_vertex.y);
	double line2_slope_x = (line2_up_vertex.x - line2_down_vertex.x) / (line2_up_vertex.y - line2_down_vertex.y);
	double line2_slope_z = (line2_up_vertex.z - line2_down_vertex.z) / (line2_up_vertex.y - line2_down_vertex.y);
	for (double y = ceil(min_vertex.y); y <= max_vertex.y; y += 1.0) {
		if (!switch_line_flag && y > mid_vertex.y) {
			line2_down_vertex = mid_vertex, line2_up_vertex = max_vertex;
			current_vertex2 = line2_down_vertex;
			line2_slope_x = (line2_up_vertex.x - line2_down_vertex.x) / (line2_up_vertex.y - line2_down_vertex.y);
			line2_slope_z = (line2_up_vertex.z - line2_down_vertex.z) / (line2_up_vertex.y - line2_down_vertex.y);
			switch_line_flag = true;
		}

		IncreaseByY(line1_slope_x, line1_slope_z, y, current_vertex1);
		IncreaseByY(line2_slope_x, line2_slope_z, y, current_vertex2);
		InterpolateByX(current_vertex1, current_vertex2);
	}


}

inline Vector& Render::IncreaseByY(const double slope_x, const double slope_z, const double y, Vector &vertex) {
	double delta_y = y - vertex.y;
	vertex.x += slope_x * delta_y;
	vertex.y = y;
	vertex.z += slope_z * delta_y;
	return vertex;
}

void Render::InterpolateByX(const Vector &vertex1, const Vector &vertex2) {
	if(vertex1.x > vertex2.x) { //keep left to right order
		InterpolateByX(vertex2, vertex1);
		return;
	} else if(vertex1.x == vertex2.x) {
		Vector vertex = (vertex1.z < vertex2.z ? vertex1 : vertex2);
		SetPixelZBuffer(vertex);
		return;
	}

	double slope_z = (vertex2.z - vertex1.z) / (vertex2.x - vertex1.x);
	Vector current_vertex = vertex1;
	for (double x = ceil(vertex1.x); x <= vertex2.x; x += 1.0) {
		current_vertex.z += slope_z * (x - current_vertex.x);
		current_vertex.x = x;
		SetPixelZBuffer(current_vertex);
	}
}

inline void Render::SetPixelZBuffer(const Vector &vertex) {
	Pixel pixel = display_->GetPixel(vertex.x, vertex.y);
	if (vertex.z <= (double)pixel.z) {
		pixel.z = vertex.z;
		pixel.r = ColorToShortType(flat_color_.r());
		pixel.g = ColorToShortType(flat_color_.g());
		pixel.b = ColorToShortType(flat_color_.b());
		display_->SetPixel(vertex.x, vertex.y, pixel);
	}
}







} // namespace smallrd
