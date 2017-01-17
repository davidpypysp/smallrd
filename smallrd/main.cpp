// Entrance of smallrd

#include<stdlib.h>
#include "renderer.h"


int main(int argc, char *argv[]) {
    smallrd::Renderer renderer(512, 512);
    renderer.RenderScene();
    system("pause");
    return 0;
}
