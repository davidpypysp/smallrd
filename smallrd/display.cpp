#include "display.h"

namespace smallrd {

Pixel::Pixel(const short r, const short g, const short b, const short a, const int z) : r(r), g(g), b(b), a(a), z(z) {
}

Display::Display(const int xres, const int yres) {
	xres_ = ClampValue(xres, 0, kMaxXRes);
	yres_ = ClampValue(yres, 0, kMaxYRes);
	frame_buf_ = new Pixel[yres_ * xres_];
}

void Display::Init() {
	// background color: steel blue 2
	short r = ColorToShortType(92.0 / 255.0), g = ColorToShortType(172.0 / 255.0), b = ColorToShortType(238.0 / 255.0);
	//short r = 0, g = 0, b = 0;
	for (int i = 0; i < xres_ * yres_; ++i) {
		frame_buf_[i].r = r;
		frame_buf_[i].g = g;
		frame_buf_[i].b = b;
		frame_buf_[i].a = 1;
		frame_buf_[i].z = INT_MAX;
	}
}

void Display::SetPixel(const int x, const int y, const Pixel &pixel) {
	if (InBound(x, 0, xres_) && InBound(y, 0, yres_)) frame_buf_[ArrayIndex(x, y, xres_)] = pixel;
}

Pixel& Display::GetPixel(const int x, const int y) {
	if (InBound(x, 0, xres_) && InBound(y, 0, yres_)) return frame_buf_[ArrayIndex(x, y, xres_)];
	return Pixel(0.0, 0.0, 0.0, 0.0, 0);
}

void Display::FlushToFile(FILE* out_file) {
	fprintf(out_file, "P6 %d %d 255\r", xres_, yres_);
	for (int i = 0; i < xres_ * yres_; i++) {
		Pixel pixel = frame_buf_[i];
		short r = (int)pixel.r >> 4, g = (int)pixel.g >> 4, b = (int)pixel.b >> 4;
		fprintf(out_file, "%c%c%c", r, g, b);
	}
}

} // namespace smallrd


