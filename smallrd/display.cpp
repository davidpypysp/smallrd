#include "display.h"

namespace smallrd {

Pixel::Pixel(double r, double g, double b, double a, int z) : r(r), g(g), b(b), a(a), z(z) {
}

Display::Display(int xres, int yres) {
	xres_ = ClampValue(xres, 0, kMaxXRes);
	yres_ = ClampValue(yres, 0, kMaxYRes);
	frame_buf_ = new Pixel[yres_ * xres_];
}

void Display::Init() {
	memset(frame_buf_, 0, sizeof(Pixel) * yres_ * xres_);
}

void Display::SetPixel(const int x, const int y, const Pixel pixel) {
	if (InBound(x, 0, xres_) && InBound(y, 0, yres_)) frame_buf_[ArrayIndex(x, y, xres_)] = pixel;
}

Pixel Display::GetPixel(const int x, const int y) {
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


