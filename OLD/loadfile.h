
#ifndef LOADFILE_H
#define LOADFILE_H

//void load();
//void Loadimage(imageData *img);

//def struct imageData imageData;
typedef struct
{
	
	SDL_Surface *image;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Window *window;
	char path[];
}imageData;

void Loadimage(imageData *img);
void Delimage(imageData *img);
#endif
