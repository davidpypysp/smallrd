#ifndef SMALLRD_RENDERER_H_
#define SMALLRD_RENDERER_H_

namespace smallrd {

class Renderer {
public:
    Renderer(const int width, const int height);

    void RenderScene();
    void RenderScene2();

private:
    const char *kInFileName = "rects", *kOutFileName = "output.ppm";
    const char *kInFileName2 = "pot4.screen.asc", *kOutFileName2 = "output2.ppm";
    int width_, height_;
};

} //namespace smallrd



#endif // SMALLRD_RENDERER_H_

