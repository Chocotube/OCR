#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"

int main(int argc, char* argv[])
{
	
    printf("Bienvenue au OCR gros\n");
	imageData *img = NULL;
	img = (imageData *) malloc(sizeof(imageData));
	Loadimage(img);
	//Mettez vous fonctions ici pour 
	Delimage(img);

	return 0;

}
