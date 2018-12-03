#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *helloWorld = NULL;

void init();

void loadMedia();

void sdlClose();

int main(int argc, char* args[])
{
	init();
	loadMedia();
	SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	sdlClose();
	return 0;
}

void init(){

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL Init fail: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Projekt ARKO", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN );

	if(window == NULL){
		printf("Failed to init window: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//Get window surface
	screenSurface = SDL_GetWindowSurface(window);
}

void loadMedia(){
	helloWorld = SDL_LoadBMP("output.bmp");

	if(helloWorld == NULL){
		printf("Unable to get file: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void sdlClose(){
	SDL_FreeSurface(helloWorld);
	helloWorld = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}
