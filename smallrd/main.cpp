// Entrance of smallrd

#include <stdlib.h>
#include <stdio.h>
#include "renderer.h"

#include "math/matrix.h"
#include "math/vector.h"
#include "math/quaternion.h"

using namespace smallrd;

void MyTest() {
	smallrd::Matrix matrix = { 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6 };

	smallrd::Matrix matrix2 = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 8, 7, 6, 5 },
		{ 4, 3, 2, 1 }
	};

	



	printf("test!\n");

}



int main(int argc, char *argv[]) {

	MyTest();
	smallrd::Renderer renderer(256, 256);
	//renderer.RenderScene();
	//renderer.RenderScene2();
	//renderer.RenderScene3();
	//renderer.RenderScene4();
	renderer.RenderScene5();
	system("pause");
	return 0;
}





