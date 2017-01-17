#include "renderer.h"
#include <assert.h>
#include "display.h"

namespace smallrd {

Renderer::Renderer(const int width, const int height) : width_(width), height_(height) {
}

void Renderer::RenderScene() {
	Display *display = new Display(width_, height_);
	display->Init();

	FILE *in_file, *out_file;
	assert((in_file = fopen(kInFileName, "r")) != NULL);
	assert((out_file = fopen(kOutFileName, "wb")) != NULL);

	int	ulx, uly, lrx, lry, r, g, b;
	while (fscanf(in_file, "%d %d %d %d %d %d %d",
		&ulx, &uly, &lrx, &lry, &r, &g, &b) == 7) {
		for (int y = uly; y <= lry; y++) {
			for (int x = ulx; x <= lrx; x++) {
				display->SetPixel(x, y, Pixel(r, g, b, 1, 0));
			}
		}
	}

	display->FlushToFile(out_file);

	fclose(in_file);
	fclose(out_file);
	delete display;
}

} // namespace smallrd


