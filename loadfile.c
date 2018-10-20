#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"


void Loadimage(imageData *img) //This function opens an image and gives an sdl surface in the image data struct
{
/*	int end = 0;
	SDL_Init(SDL_INIT_VIDEO);
	printf("%s","Bonjour mettez le nom du fichier que vous voulez ouvrir : "); //We ask the user for the path
	scanf("%s",img -> path);

	img -> window = SDL_CreateWindow(img -> path, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,640,480,0);//Creates the window
	img -> renderer = SDL_CreateRenderer(img -> window, -1, 0); //Creates the renderer for the image
*/
	img -> image = SDL_LoadBMP("blackorwhite.bmp"/*img -> path*/); //Loads the image
	/*img -> texture = SDL_CreateTextureFromSurface(img -> renderer, img -> image);//Puts the texture in the window
	if(img -> image = NULL) //If we can't find the image sdl will give an Error
	{
		printf("%s\n","Error :");
		SDL_GetError();
	}*/
}

void Delimage(imageData *img) //This is the idle function and waits for the user to shut the image
{
	int end = 0;
	SDL_Event event;

	while (end == 0) //Waiting for user to do something
	{
		SDL_WaitEvent(&event);

		if(event.type == SDL_QUIT) //If the user wants to quit we destroy everything
		{
			end = 1;
		}
		SDL_RenderCopy(img -> renderer,img -> texture, NULL, NULL);
		SDL_RenderPresent(img -> renderer);
	}
	SDL_DestroyTexture(img -> texture);
	SDL_FreeSurface(img -> image);
	SDL_DestroyRenderer(img -> renderer);
	SDL_DestroyWindow(img -> window);

	SDL_Quit;
}
/*
int main(int argc, char* argv[])
{
	imageData *img = NULL;
	img = (imageData *) malloc(sizeof(imageData));
	Loadimage(img);
	Delimage(img);
	return 0;
}*/
