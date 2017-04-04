#include "texture.h"

#include <stdio.h>
#include <stdlib.h>

#include "utility.h"

namespace smallrd {


Texture::Texture(const int mode)
	: x_resolution_(0),
	  y_resolution_(0),
	  image_(NULL), 
	  reset_(true) {
	if (mode == kImage) texture_function_ = &Texture::ImageTexture;
	else if (mode == kProcedural) texture_function_ = &Texture::ProceduralTexture;
}

Texture::~Texture() {
	delete[] image_;
}

int Texture::GetColorByUV(const Vector &uv, Vector &color) {
	return (this->*(this->texture_function_))(uv, color);
}

int Texture::ImageTexture(const Vector &uv, Vector &color) {
	if (reset_) {          /* open and load texture file */
		FILE *in_file;
		fopen_s(&in_file, "texture", "rb");
		if (in_file == NULL) {
			fprintf(stderr, "texture file not found\n");
			exit(-1);
		}
		unsigned char foo[8], dummy;
		fscanf_s(in_file, "%s %d %d %c", foo, &x_resolution_, &y_resolution_, &dummy);
		//image_ = (Vector*)malloc(sizeof(Vector) * (x_resolution_ + 1) * (y_resolution_ + 1));
		image_ = new Vector[(x_resolution_ + 1) * (y_resolution_ + 1)];
		if (image_ == NULL) {
			fprintf(stderr, "malloc for texture image failed\n");
			exit(-1);
		}

		unsigned char pixel[3];
		for (int i = 0; i < x_resolution_ * y_resolution_; ++i) {	/* create array of GzColor values */
			fread(pixel, sizeof(pixel), 1, in_file);
			for (int j = 0; j < 3; ++j) 
				image_[i][j] = (double)((int)pixel[j]) * (1.0 / 255.0);
		}

		reset_ = false;          /* init is done */
		fclose(in_file);
	}

	/* bounds-test u,v to make sure nothing will overflow image array bounds */
	/* determine texture cell corner values and perform bilinear interpolation */
	/* set color to interpolated GzColor value and return */
	double u = ClampValue(uv.x, 0.0, 1.0) * (x_resolution_ - 1);
	double v = ClampValue(uv.y, 0.0, 1.0) * (y_resolution_ - 1);

	int left = floor(u), right = ceil(u), up = floor(v), down = floor(v);
	double s = u - left, t = v - up;

	Vector &lu = image_[ArrayIndex(left, up, x_resolution_)];
	Vector &ru = image_[ArrayIndex(right, up, x_resolution_)];
	Vector &rd = image_[ArrayIndex(right, down, x_resolution_)];
	Vector &ld = image_[ArrayIndex(left, down, x_resolution_)];

	color = rd * s * t + ld * (1 - s) * t + ru * s * (1 - t) + lu * (1 - s) * (1 - t);
	return 1;
}

int Texture::ProceduralTexture(const Vector &uv, Vector &color) {
	return 0;
}

} // namespace smallrd


