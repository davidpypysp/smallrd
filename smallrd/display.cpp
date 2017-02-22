#include "display.h"

namespace smallrd {

Pixel::Pixel(const short r, const short g, const short b, const short a, const int z) : r(r), g(g), b(b), a(a), z(z) {
}

Display::Display(const int xres, const int yres) {
	x_resolution_ = ClampValue(xres, 0, kMaxXRes);
	y_resolution_ = ClampValue(yres, 0, kMaxYRes);
	frame_buf_ = new Pixel[y_resolution_ * x_resolution_];
}

Display::~Display() {
	if(frame_buf_ != NULL) delete[] frame_buf_;
}

void Display::Init() {
	// background color: steel blue 2
	short r = ColorToShortType(92.0 / 255.0), g = ColorToShortType(172.0 / 255.0), b = ColorToShortType(238.0 / 255.0);
	//short r = 0, g = 0, b = 0;
	for (int i = 0; i < x_resolution_ * y_resolution_; ++i) {
		frame_buf_[i].r = r;
		frame_buf_[i].g = g;
		frame_buf_[i].b = b;
		frame_buf_[i].a = 1;
		frame_buf_[i].z = INT_MAX;
	}
}

void Display::SetPixel(const int x, const int y, const Pixel &pixel) {
	if (InBound(x, 0, x_resolution_) && InBound(y, 0, y_resolution_)) frame_buf_[ArrayIndex(x, y, x_resolution_)] = pixel;
}

Pixel& Display::GetPixel(const int x, const int y) {
	if (InBound(x, 0, x_resolution_) && InBound(y, 0, y_resolution_)) return frame_buf_[ArrayIndex(x, y, x_resolution_)];
	return Pixel(0.0, 0.0, 0.0, 0.0, 0);
}

void Display::FlushToFile(FILE* out_file) {
	fprintf(out_file, "P6 %d %d 255\r", x_resolution_, y_resolution_);
	for (int i = 0; i < x_resolution_ * y_resolution_; ++i) {
		Pixel pixel = frame_buf_[i];
		short r = (int)pixel.r >> 4, g = (int)pixel.g >> 4, b = (int)pixel.b >> 4;
		fprintf(out_file, "%c%c%c", r, g, b);
	}
}

} // namespace smallrd


