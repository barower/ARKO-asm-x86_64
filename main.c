#include <SDL.h>
#include <SDL_ttf.h>
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

void sdlInit();
void sdlClose();

void drawText();

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
TTF_Font* Sans = NULL;

int main(int argc, char* args[])
{
	int quit = 0;
	SDL_Event e;

	sdlInit();

	while(!quit){

		while(SDL_PollEvent(&e) != 0){

			if(e.type == SDL_QUIT){
				quit = 1;
				continue;
			}
			else if(e.type == SDL_KEYDOWN){
				switch(e.key.keysym.sym){
				case SDLK_UP:
					printf("Key up\n");
					//Increment value under cursor
					break;

				case SDLK_DOWN:
					printf("Key down\n");
					//Decrement value under cursor
					break;

				case SDLK_LEFT:
					printf("Key left\n");
					//Shift cursor left
					break;

				case SDLK_RIGHT:
					printf("Key right\n");
					//Shift cursor right
					break;

				case SDLK_q:
					printf("Exiting\n");
					exit(EXIT_SUCCESS);
					break;

				default:
					printf("Other key\n");
					//Do nothing with cursor
					break;
				}
			}

			//Parse cursor change

			//Run drawing function
			drawText();

			SDL_UpdateWindowSurface(window);

		}

	}

	sdlClose();
	return 0;
}

void drawText(){

	// this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Color White = {255, 255, 255};

	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "A=10", White); 

	SDL_Rect srcrect = {
		.x = 0,
		.y = 0,
		.w = 32,
		.h = 32
	};

	SDL_Rect dstrect = {
		.x = (screenSurface->w)*1/5,
		.y = (screenSurface->h)*9/10,
		.w = 32,
		.h = 32
	};

	SDL_BlitSurface(surfaceMessage, &srcrect, screenSurface, &dstrect);
}

void sdlInit(){

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL Init fail: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(TTF_Init() < 0){
		printf("TTF Init fail: %s\n", SDL_GetError());
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

	//this opens a font style and sets a size
	Sans = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-B.ttf", 12);
	if(Sans == NULL){
		printf("Couldn't get font: %s\n", SDL_GetError());
	}
}

void sdlClose(){

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}