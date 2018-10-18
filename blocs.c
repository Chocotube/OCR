#include "surf.h"
#include "blocs.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Rect* surfToBlocRect(int horBound[], int verBound[])             //Return the rectangle with the given boundaries
{
	SDL_Rect *res;
	res -> x = verBound[0];
	res -> y = horBound[0];
	res -> w = verBound[1]-verBound[0];
	res -> h = horBound[1]-horBound[0];
	return res;
}

SDL_Surface surfBlocer(SDL_Surface surf)
{
    arrayBound(surfToHorArray(surf));
    arrayBound(surfToVerArray(surf));
	return surfCropper(surf, surfToBlocRecr(, ));
}

SALUT JE SUIS BO
