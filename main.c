#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"

int main(int argc, char* argv[])
{
	
    printf("Bienvenue au OCR gros\n");
	imageData *img = NULL;
	img = (imageData *) malloc(sizeof(imageData));
	Loadimage(img);
	printf("%d", img -> image -> w);
	greyscale(img);
	BlackOrWhite(img,0.5f);
	//Mettez vous fonctions ici pour 
	//Delimage(img);
	printf("fished");
	return 0;

}
