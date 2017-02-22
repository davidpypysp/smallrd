#ifndef SMALLRD_TEXTURE_H_
#define SMALLRD_TEXTURE_H_

#include "math/vector.h"


namespace smallrd {

class Texture {
public:
	enum TextureMode {
		kImage,
		kProcedural
	};

	Texture(const int mode);
	~Texture();
	int GetColorByUV(const Vector &uv, Vector &color);

	






private:
	const char* kFileName = "texture";
	int (Texture::*texture_function_)(const Vector&, Vector&);
	int x_resolution_, y_resolution_;
	Vector *image_;
	bool reset_;

	int ImageTexture(const Vector &uv, Vector &color);
	int ProceduralTexture(const Vector &uv, Vector &color);

};

} // namespace smallrd

#endif // SMALLRD_TEXTURE_H_
