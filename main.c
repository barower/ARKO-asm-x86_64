#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include "drawgraph.h"

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

enum {
	CURSOR_POSITION_A = 0,
	CURSOR_POSITION_B,
	CURSOR_POSITION_C,
	CURSOR_POSITION_D,
	CURSOR_POSITION_NO_ELEMENTS
};
int coefficients[] = { 0, 0, 0, 0 };
int cursorPosition = CURSOR_POSITION_A;

void sdlInit();
void sdlClose();

void drawText();

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
TTF_Font* Sans = NULL;

int main(int argc, char* args[])
{
	int quit = 0, draw = 0;
	SDL_Event e;

	sdlInit();

	while(!quit){

		while(SDL_PollEvent(&e) != 0){
		
			draw = 0;

			if(e.type == SDL_QUIT){
				quit = 1;
				continue;
			}
			else if(e.type == SDL_KEYDOWN){
				switch(e.key.keysym.sym){
				case SDLK_UP:
				case SDLK_k:
					printf("Key up\n");
					draw = 1;
					coefficients[cursorPosition] += 1;
					break;

				case SDLK_DOWN:
				case SDLK_j:
					printf("Key down\n");
					draw = 1;
					coefficients[cursorPosition] -= 1;
					break;

				case SDLK_LEFT:
				case SDLK_h:
					printf("Key left\n");
					draw = 1;
					cursorPosition -=  1;
					cursorPosition = (cursorPosition < 0) ? CURSOR_POSITION_NO_ELEMENTS - 1 : cursorPosition;
					break;

				case SDLK_RIGHT:
				case SDLK_l:
					printf("Key right\n");
					draw = 1;
					cursorPosition = (cursorPosition + 1)%CURSOR_POSITION_NO_ELEMENTS;
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

			if(draw){
				drawText();
				drawGraph();
				SDL_UpdateWindowSurface(window);
			}

		}

	}

	sdlClose();
	return 0;
}

void putString(char *text, SDL_Color color, float x_pos, float y_pos, int y_offset){

	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, color); 

	SDL_Rect srcrect = {
		.x = 0,
		.y = 0,
		.w = 32,
		.h = 32
	};

	SDL_Rect dstrect = {
		.x = (int)(screenSurface->w*x_pos),
		.y = (int)(screenSurface->h*y_pos) + y_offset,
		.w = 32,
		.h = 32
	};

	SDL_FillRect(screenSurface, &dstrect, 0);
	SDL_BlitSurface(surfaceMessage, &srcrect, screenSurface, &dstrect);
}

void drawText(){

	char string[20];

	// this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Color White = {255, 255, 255};

	snprintf(string, 19, "A=%d", coefficients[CURSOR_POSITION_A]);
	putString(string, White, 0.075, 0.95, 0);
	snprintf(string, 19, "B=%d", coefficients[CURSOR_POSITION_B]);
	putString(string, White, 0.15, 0.95, 0);
	snprintf(string, 19, "C=%d", coefficients[CURSOR_POSITION_C]);
	putString(string, White, 0.225, 0.95, 0);
	snprintf(string, 19, "D=%d", coefficients[CURSOR_POSITION_D]);
	putString(string, White, 0.3, 0.95, 0);

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

	drawText();
	drawGraph();
	SDL_UpdateWindowSurface(window);
}

void sdlClose(){

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}
