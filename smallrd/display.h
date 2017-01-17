#ifndef SMALLRD_DISPLAY_H_
#define SMALLRD_DISPLAY_H_

#include <math.h>
#include <iostream>
#include "utility.h"

namespace smallrd {

struct Pixel {
	double r, g, b, a;
	int z;

	Pixel(double r = 0.0, double g = 0.0, double b = 0.0, double a = 0.0, int z = 0);
};

class Display {
public:
	Display(int xres = 0, int yres = 0);

	void Init();

	void SetPixel(const int x, const int y, const Pixel pixel);
	Pixel GetPixel(const int x, const int y);
	void FlushToFile(FILE* out_file);

private:
	int xres_, yres_;
	Pixel *frame_buf_;
	const int kMaxXRes = 1024, kMaxYRes = 1024;

};

} // namespace smallrd





#endif // SMALLRD_DISPLAY_H_

