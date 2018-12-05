#include "drawgraph.h"
#include <stdio.h>

void drawGraph(SDL_Surface *surface, int *coefficients, int coeff_size){
	printf("Printing graph\n");
	int w = surface->w;
	int h = surface->h;

	char *bufc = (char *)surface->pixels;
	int *bufi = (int *)bufc;

	int A = coefficients[0];
	int B = coefficients[1];
	int C = coefficients[2];
	int D = coefficients[3];
	
	// Draw x line
	memset(bufc+w*h/2*4, 0xFF, w*4);

	// Draw y line
	for(int i = 0; i < h; i++){
		*(bufi + w/2 + i*w) = 0xFFFFFFFF;
	}

	// Draw pixels
	for(int i = 0; i < w; i++){
		float x = -1.0 + i*2.0/w;
		float y = A*x*x*x + B*x*x + C*x + D;
		int y_offset = (int)((y + 1.0)*h/2.0);
		printf("y_offset = %d\n", y_offset);
		int bufpos = i + y_offset*w;
		if(bufpos > 0 && bufpos < w*h){
			*(bufi + bufpos) = 0x00FF0000;
		}
	}

}
