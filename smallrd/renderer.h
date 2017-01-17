#ifndef SMALLRD_RENDERER_H_
#define SMALLRD_RENDERER_H_

namespace smallrd {

class Renderer {
public:
    Renderer(const int width, const int height);

    void RenderScene();

private:
    const char *kInFileName = "rects", *kOutFileName = "output.ppm";
    int width_, height_;
};

} //namespace smallrd



#endif // SMALLRD_RENDERER_H_

