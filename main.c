#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "cut.h"
#include "color.h"
#include "NeuralNet.h"
#include "text.h"
#include "resize.h"
#include "app.h"

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
	surf = blackAndWhite(surf, ratio);
    saveSurfaceAsBMP(surf, 0, 0);
	int n = cut(surf);
    char *str = malloc(sizeof(char) * n);
    int tab[] = {900,100,63};
	network *net = network_init(tab, 3);
    str = rebuild(n, str, net);
    puts(str);
	printf("Credits : marc.gayed, adrien.guell, frederico-jose.silva, jake.penney\n");
	return res;
    free(str);
}
