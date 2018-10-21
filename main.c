#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"
#include "Cutimage.h"

int main()
{
	
    printf("Bienvenue au OCR gros\n");
	imageData *img = NULL;
	img = (imageData *) malloc(sizeof(imageData));
	Loadimage(img);
	//printf("%d", img -> image -> w);
	greyscale(img);
	BlackOrWhite(img,0.5f);
	FindText(img);
	//Mettez vous fonctions ici pour 
	//Delimage(img);
	printf("fishedi\n");
	return 0;

}
