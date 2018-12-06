#include "drawgraph.h"
#include <stdio.h>
#include <math.h>

void drawGraph(SDL_Surface *surface, double *coefficients){
	printf("Printing graph\n");
	int w = surface->w;
	int h = surface->h;

	char *bufc = (char *)surface->pixels;
	int *bufi = (int *)bufc;

	int A = (int)coefficients[0];
	int B = (int)coefficients[1];
	int C = (int)coefficients[2];
	int D = (int)coefficients[3];
	double S = coefficients[4];
	
	// Draw x line
	memset(bufc+w*h/2*4, 0xFF, w*4);

	// Draw y line
	for(int i = 0; i < h; i++){
		*(bufi + w/2 + i*w) = 0xFFFFFFFF;
	}

	// Draw pixels
	double x = -1.0;
	unsigned int x_offset = 0;
	while(x_offset < w){
		// 1. Put pixel on screen
		double y = A*x*x*x + B*x*x + C*x + D;
		unsigned int y_offset = (unsigned int)((y + 1.0)*h/2.0);
		int bufpos = x_offset + y_offset*w;
		if(bufpos > 0 && bufpos < w*h){
			*(bufi + bufpos) = 0x00FF0000;
		}

		// 2. Calculate dx/dy
		double derivative = 3*A*x*x + 2*B*x + C;

		// 3. Calculate x step
		double step = S / sqrt(1 + derivative*derivative);
		x += step;
		x_offset = (unsigned int)((x + 1.0)*w/2.0);
	}

}
