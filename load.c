#include <stdio.h>
#include <SDL2/SDL.h>


void Loadimage()
{
	char path[300];
	scanf("%s",path);
	SDL_Surface * image = NULL;
	int end = 0;
	SDL_Event event;


	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow(path, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,640,480,0);

	SDL_Renderer *  renderer = SDL_CreateRenderer(window, -1, 0);

	image = SDL_LoadBMP(path);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	if(image = NULL)
	{
		printf("wesh");
		SDL_GetError();
	}
	while (end == 0)
	{
		SDL_WaitEvent(&event);

		if(event.type == SDL_QUIT)
		{
			end = 1;
		}
		SDL_RenderCopy(renderer,texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit;

}
int main(int argc, char* argv[])
{
	Loadimage();
	return 0;
}
