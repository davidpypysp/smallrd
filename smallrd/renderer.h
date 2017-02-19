#ifndef SMALLRD_RENDERER_H_
#define SMALLRD_RENDERER_H_

namespace smallrd {

class Renderer {
public:
    Renderer(const int width, const int height);

    void RenderScene();
    void RenderScene2();
    void RenderScene3();
    void RenderScene4();

private:
    const char *kInFileName = "rects", *kOutFileName = "output.ppm";
    const char *kInFileName2 = "pot4.screen.asc", *kOutFileName2 = "output2.ppm";
    const char *kInFileName3 = "pot4.asc", *kOutFileName3 = "output3.ppm";
    const char *kInFileName4 = "POT4.ASC", *kOutFileName4 = "output4.ppm";
    int width_, height_;
};

} //namespace smallrd



#endif // SMALLRD_RENDERER_H_

