#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum KeyPressSurfaces{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

void init();

void loadMedia();

void sdlClose();

SDL_Surface *loadSurface(char *path);

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *currentSurface = NULL;

int main(int argc, char* args[])
{
	int quit = 0;
	SDL_Event e;

	init();
	loadMedia();

	currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	while(!quit){

		while(SDL_PollEvent(&e) != 0){

			if(e.type == SDL_QUIT){
				quit = 1;
				continue;
			}
			else if(e.type == SDL_KEYDOWN){
				switch(e.key.keysym.sym){
				case SDLK_UP:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;

				case SDLK_DOWN:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;

				case SDLK_LEFT:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

				case SDLK_RIGHT:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;

				default:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}

			SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);

		}

	}

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
	keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("bmpki/output.bmp");
	if(keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
		printf("Failed to load image: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("bmpki/untitled.bmp");
	if(keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL){
		printf("Failed to load image: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("bmpki/untitled2.bmp");
	if(keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL){
		printf("Failed to load image: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("bmpki/untitled3.bmp");
	if(keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
		printf("Failed to load image: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("bmpki/untitled4.bmp");
	if(keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL){
		printf("Failed to load image: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void sdlClose(){

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

SDL_Surface *loadSurface(char *path){
	SDL_Surface *loadedSurface = SDL_LoadBMP(path);
	if(loadedSurface == NULL){
		printf("Unable to load image: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return loadedSurface;
}