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

		render->PutTriangle(vertex_list, normal_list, uv_list);
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
		0.866,	0.0,	-0.5,	0.0,
		0.0,	1.0,	0.0,	0.0,
		0.5,	0.0,	0.866,	0.0,
		0.0,	0.0,	0.0,	1.0
	});
	render->PushMatrix({ // rotate x
		1.0,	0.0,	0.0,	0.0,
		0.0,	0.7071,	0.7071,	0.0,
		0.0,   -0.7071, 0.7071,	0.0,
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

		render->PutTriangle(vertex_list, normal_list, uv_list);
	}

	display->FlushToFile(out_file);

	fclose(in_file);
	fclose(out_file);
	delete render;
}

void Renderer::RenderScene4() {
	Display *display = new Display(width_, height_);
	Render *render = new Render(display);

	render->set_camera(Camera(Vector(13.2, -8.7, -14.8), Vector(0.8, 0.7, 4.5), Vector(-0.2, 1.0, 0.0), 53.7));
	render->AddLight({ { -0.7071, 0.7071, 0 },{ 0.5, 0.5, 0.9 } });
	render->AddLight({ { 0, -0.7071, -0.7071 },{ 0.9, 0.2, 0.3 } });
	render->AddLight({ { 0.7071, 0.0, -0.7071 },{ 0.2, 0.7, 0.3 } });
	render->set_ambient_light({ { 0, 0, 0 },{ 0.3, 0.3, 0.3 } });

	render->set_interpolation_mode(Render::kNormals);
	render->set_ks(Vector(0.3, 0.3, 0.3));
	render->set_ka(Vector(0.1, 0.1, 0.1));
	render->set_kd(Vector(0.7, 0.7, 0.7));
	render->set_spec(32.0);

	render->BeginRender();

	render->PushMatrix({ // scale
		3.25,	0.0,	0.0,	0.0,
		0.0,	3.25,	0.0,	-3.25,
		0.0,	0.0,	3.25,	3.5,
		0.0,	0.0,	0.0,	1.0
	});
	render->PushMatrix({ // rotate y
		0.866,	0.0,	-0.5,	0.0,
		0.0,	1.0,	0.0,	0.0,
		0.5,	0.0,	0.866,	0.0,
		0.0,	0.0,	0.0,	1.0
	});
	render->PushMatrix({ // rotate x
		1.0,	0.0,	0.0,	0.0,
		0.0,	0.7071,	0.7071,	0.0,
		0.0,   -0.7071, 0.7071,	0.0,
		0.0,	0.0,	0.0,	1.0
	});

	FILE *in_file, *out_file;
	assert((in_file = fopen(kInFileName4, "r")) != NULL);
	assert((out_file = fopen(kOutFileName4, "wb")) != NULL);

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

		render->PutTriangle(vertex_list, normal_list, uv_list);
	}

	display->FlushToFile(out_file);

	fclose(in_file);
	fclose(out_file);
	delete render;

}

void Renderer::RenderScene5() {
	Display *display = new Display(width_, height_);
	Render *render = new Render(display);

	render->set_camera(Camera(Vector(-3.0, -25.0, -4.0), Vector(7.8, 0.7, 6.5), Vector(-0.2, 1.0, 0.0), 63.7));
	render->AddLight({ { -0.7071, 0.7071, 0 },{ 0.5, 0.5, 0.9 } });
	render->AddLight({ { 0, -0.7071, -0.7071 },{ 0.9, 0.2, 0.3 } });
	render->AddLight({ { 0.7071, 0.0, -0.7071 },{ 0.2, 0.7, 0.3 } });
	render->set_ambient_light({ { 0, 0, 0 },{ 0.3, 0.3, 0.3 } });

	render->set_interpolation_mode(Render::kColor);
	render->set_ks(Vector(0.3, 0.3, 0.3));
	render->set_ka(Vector(0.1, 0.1, 0.1));
	render->set_kd(Vector(0.7, 0.7, 0.7));
	render->set_spec(32.0);
	render->set_texture(new Texture(Texture::kImage));

	render->BeginRender();

	render->PushMatrix({ // scale
		3.25,	0.0,	0.0,	0.0,
		0.0,	3.25,	0.0,	-3.25,
		0.0,	0.0,	3.25,	3.5,
		0.0,	0.0,	0.0,	1.0
	});
	render->PushMatrix({ // rotate y
		0.866,	0.0,	-0.5,	0.0,
		0.0,	1.0,	0.0,	0.0,
		0.5,	0.0,	0.866,	0.0,
		0.0,	0.0,	0.0,	1.0
	});
	render->PushMatrix({ // rotate x
		1.0,	0.0,	0.0,	0.0,
		0.0,	0.7071,	0.7071,	0.0,
		0.0,   -0.7071, 0.7071,	0.0,
		0.0,	0.0,	0.0,	1.0
	});

	render->BeginAASampling();  //anti-aliasing

	FILE *in_file, *out_file;
	assert((in_file = fopen(kInFileName5, "r")) != NULL);
	assert((out_file = fopen(kOutFileName5, "wb")) != NULL);

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

		render->PutTriangle(vertex_list, normal_list, uv_list);
	}
	if (render->aa_flag()) render->AASampling();

	display->FlushToFile(out_file);

	fclose(in_file);
	fclose(out_file);
	delete render;
}
	

} // namespace smallrd


