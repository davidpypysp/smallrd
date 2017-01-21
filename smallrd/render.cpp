#include "render.h"

namespace smallrd {

Render::Render(Display *display) : display_(display) {
}

void Render::BeginRender() {
	display_->Init();
}

void Render::PutTriangle(Vector *vertex_list, Vector *normal_list, Vector *uv_list) {

}



} // namespace smallrd
