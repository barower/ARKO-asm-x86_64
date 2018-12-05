#include "drawgraph.h"
#include <stdio.h>

void drawGraph(SDL_Surface *surface, float *coefficients){
	printf("Printing graph\n");
	int w = surface->w;
	int h = surface->h;

	char *bufc = (char *)surface->pixels;
	int *bufi = (int *)bufc;

	int A = (int)coefficients[0];
	int B = (int)coefficients[1];
	int C = (int)coefficients[2];
	int D = (int)coefficients[3];
	float S = coefficients[4];
	
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
		int bufpos = i + y_offset*w;
		if(bufpos > 0 && bufpos < w*h){
			*(bufi + bufpos) = 0x00FF0000;
		}
	}

}
