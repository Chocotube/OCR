#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "cut.h"
#include "color.h"
#include "neuralNet.h"

int main(int argc, char *argv[])
{
    int res = 0;
	if (argc != 3)
    {
        printf("main: usage: path black_and_white_ratio\n");
        res = 1;
    }
    SDL_Surface *surf = LoadImage(argv[1]);
	surf = greyScale(surf);
    float ratio = atof(argv[2]);
	surf = blackAndWhite(surf,0.5f);
	cut(surf);
    printf("Done cut\n");
	printf("Credits : marc.gayed, adrien.guell, frederico-jose.silva, jake.penney\n");
	return res;
}
