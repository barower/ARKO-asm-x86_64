#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main( int argc, char* args[] )
{
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL Init fail: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Projekt ARKO", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN );

	if(window == NULL){
		printf("Failed to init window: %s\n", SDL_GetError());
	}

	SDL_Delay(2000);

	return 0;
}
