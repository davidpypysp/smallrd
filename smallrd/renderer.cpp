#include "renderer.h"
#include <assert.h>
#include "display.h"
#include "render.h"
#include <vector>

namespace smallrd {

Renderer::Renderer(const int width, const int height) : width_(width), height_(height) {
}

void Renderer::RenderScene() {
	Display *display = new Display(width_, height_);
	Render *render = new Render(display);
	render->BeginRender();

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

void Renderer::RenderScene2() {
	Display *display = new Display(width_, height_);
	Render *render = new Render(display);
	render->BeginRender();

	FILE *in_file, *out_file;
	assert((in_file = fopen(kInFileName2, "r")) != NULL);
	assert((out_file = fopen(kOutFileName2, "wb")) != NULL);

	char dummy[256];
	Vector vertex_list[3], normal_list[3], uv_list[3];
	while (fscanf(in_file, "%s", dummy) == 1) { 	/* read in tri word */
		fscanf(in_file, "%lf %lf %lf %lf %lf %lf %lf %lf",
			&(vertex_list[0].x), &(vertex_list[0].y), &(vertex_list[0].z),
			&(normal_list[0].x), &(normal_list[0].y), &(normal_list[0].z),
			&(uv_list[0].x), &(uv_list[0].y));
		fscanf(in_file, "%lf %lf %lf %lf %lf %lf %lf %lf",
			&(vertex_list[1].x), &(vertex_list[1].y), &(vertex_list[1].z),
			&(normal_list[1].x), &(normal_list[1].y), &(normal_list[1].z),
			&(uv_list[1].x), &(uv_list[1].y));
		fscanf(in_file, "%lf %lf %lf %lf %lf %lf %lf %lf",
			&(vertex_list[2].x), &(vertex_list[2].y), &(vertex_list[2].z),
			&(normal_list[2].x), &(normal_list[2].y), &(normal_list[2].z),
			&(uv_list[2].x), &(uv_list[2].y));

		render->PutTriangle(vertex_list, normal_list);
	}

	display->FlushToFile(out_file);

	fclose(in_file);
	fclose(out_file);
	delete render;
}

void Renderer::RenderScene3() {
	Display *display = new Display(width_, height_);
	Render *render = new Render(display);
	render->BeginRender();
	render->PushMatrix({ // scale
		3.25,	0.0,	0.0,	0.0,
		0.0,	3.25,	0.0,	-3.25,
		0.0,	0.0,	3.25,	3.5,
		0.0,	0.0,	0.0,	1.0
	});
	render->PushMatrix({ // rotate y
		.866,	0.0,	-0.5,	0.0,
		0.0,	1.0,	0.0,	0.0,
		0.5,	0.0,	.866,	0.0,
		0.0,	0.0,	0.0,	1.0
	});
	render->PushMatrix({ // rotate x
		1.0,	0.0,	0.0,	0.0,
		0.0,	.7071,	.7071,	0.0,
		0.0,	-.7071,	.7071,	0.0,
		0.0,	0.0,	0.0,	1.0
	});






	FILE *in_file, *out_file;
	assert((in_file = fopen(kInFileName3, "r")) != NULL);
	assert((out_file = fopen(kOutFileName3, "wb")) != NULL);

	char dummy[256];
	Vector vertex_list[3], normal_list[3], uv_list[3];
	while (fscanf(in_file, "%s", dummy) == 1) { 	/* read in tri word */
		fscanf(in_file, "%lf %lf %lf %lf %lf %lf %lf %lf",
			&(vertex_list[0].x), &(vertex_list[0].y), &(vertex_list[0].z),
			&(normal_list[0].x), &(normal_list[0].y), &(normal_list[0].z),
			&(uv_list[0].x), &(uv_list[0].y));
		fscanf(in_file, "%lf %lf %lf %lf %lf %lf %lf %lf",
			&(vertex_list[1].x), &(vertex_list[1].y), &(vertex_list[1].z),
			&(normal_list[1].x), &(normal_list[1].y), &(normal_list[1].z),
			&(uv_list[1].x), &(uv_list[1].y));
		fscanf(in_file, "%lf %lf %lf %lf %lf %lf %lf %lf",
			&(vertex_list[2].x), &(vertex_list[2].y), &(vertex_list[2].z),
			&(normal_list[2].x), &(normal_list[2].y), &(normal_list[2].z),
			&(uv_list[2].x), &(uv_list[2].y));

		render->PutTriangle(vertex_list, normal_list);
	}

	display->FlushToFile(out_file);

	fclose(in_file);
	fclose(out_file);
	delete render;
}
	

} // namespace smallrd


