#include "drawgraph.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void drawGraph_body(unsigned char *pPixelBuffer, int width, int height, double A, double B, double C, double D, double S){
	int *bufi = (int *)pPixelBuffer;

	// Draw x line
	memset(pPixelBuffer+width*height/2*4, 0xFF, width*4);

	// Draw y line
	for(int i = 0; i < height; i++){
		*(bufi + width/2 + i*width) = 0xFFFFFFFF;
	}

	// Draw pixels
	double x = -1.0;
	unsigned int x_offset = 0;
	while(x_offset < width){
		// 1. Put pixel on screen
		double y = A*x*x*x + B*x*x + C*x + D;
		unsigned int y_offset = (unsigned int)((y + 1.0)*height/2.0);
		int bufpos = x_offset + (height - y_offset)*width;
		if(bufpos > 0 && bufpos < width*height){
			*(bufi + bufpos) = 0x00FF0000;
		}

		// 2. Calculate dx/dy
		double derivative = 3*A*x*x + 2*B*x + C;

		// 3. Calculate x step
		double step = S / sqrt(1 + derivative*derivative);
		x += step;
		x_offset = (unsigned int)((x + 1.0)*width/2.0);
	}

}
