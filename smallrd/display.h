#ifndef SMALLRD_DISPLAY_H_
#define SMALLRD_DISPLAY_H_

#include <math.h>
#include <iostream>
#include "utility.h"

namespace smallrd {

struct Pixel {
	short r, g, b, a;
	int z;

	Pixel(const short r = 0.0, const short g = 0.0, const short b = 0.0, const short a = 0.0, const int z = 0);
};

class Display {
public:
	Display(const int xres, const int yres);

	void Init();

	void SetPixel(const int x, const int y, const Pixel &pixel);
	Pixel& GetPixel(const int x, const int y);
	void FlushToFile(FILE* out_file);

private:
	int xres_, yres_;
	Pixel *frame_buf_;
	const int kMaxXRes = 1024, kMaxYRes = 1024;

};

} // namespace smallrd





#endif // SMALLRD_DISPLAY_H_

