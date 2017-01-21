#include "render.h"
#include "display.h"

namespace smallrd {

Render::Render(Display *display) : display_(display) {
}

void Render::BeginRender() {
	display_->Init();
}


} // namespace smallrd
