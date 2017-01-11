#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "disp.h"
#include <assert.h>

#define INFILE1 "rects"
#define OUTFILE1 "output.ppm"




int render() {
	Display *display = new Display(512, 512);
	display->init();

	FILE *infile, *outfile;
	assert((infile = fopen(INFILE1, "r")) != NULL);
	assert((outfile = fopen(OUTFILE1, "wb")) != NULL);

	int	ulx, uly, lrx, lry, r, g, b;
	while (fscanf(infile, "%d %d %d %d %d %d %d",
		&ulx, &uly, &lrx, &lry, &r, &g, &b) == 7) {
		for (int y = uly; y <= lry; y++) {
			for (int x = ulx; x <= lrx; x++) {
				display->setPixel(x, y, Pixel(r, g, b, 1, 0));
			}
		}
	}

	display->flush2File(outfile);

	fclose(infile);
	fclose(outfile);
	delete display;
	return 0;
}


int main(int argc, char *argv[]) {
	/*
	printf("argc: %d\n", argc);
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] =  %s\n", i, argv[i]);
	}

	*/

	render();
	
}
