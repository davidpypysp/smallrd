// Entrance of smallrd

#include <stdlib.h>
#include <stdio.h>
#include "renderer.h"

#include "my_math.h"

void MyTest() {
	double m[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{8, 7, 6, 5},
		{4, 3, 2, 1}
	};
	smallrd::Matrix matrix(m);
	double m2[16] = { 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6 };
	smallrd::Matrix matrix2(m);
	printf("test!\n");

}



int main(int argc, char *argv[]) {

	MyTest();
	smallrd::Renderer renderer(256, 256);
	renderer.RenderScene();
	renderer.RenderScene2();
	system("pause");
	return 0;
}





