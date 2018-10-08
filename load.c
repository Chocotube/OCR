#include <stdio.h>
#include <SDL2/SDL.h>

void Main()
{
    
}

void Loadimage()
{
	char path[300];
	scanf("%s",path);
	SDL_Surface *image = NULL;

	image = SDL_LoadBMP(path);
	if(image = NULL)
	{
		SDL_GetError();
	}
}
