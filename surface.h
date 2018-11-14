#ifndef SURFACE_H
#define SURFACE_H

typedef struct
{
	
	SDL_Surface *image;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Window *window;
	char path[];
}imageData;

int getPixelRed(SDL_Surface *surf, x, y);
void binVerArray(SDL_Surface *surf, int[] array);
void binHorArray(SDL_Surface *surf, int[] array);
SDL_Rect makeRectangle(int x ,int y, int w, int h);
SDL_Surface* cropSurf(SDL_Surface surf, SDL_Rect crop);
void saveSurfaceAsBMP(SDL_Surface *surf, int name);

#endif
