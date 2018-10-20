/*#include "pixel.h"
#include "surf.h"
#include "loadfile.h"
#include <stdio.h>
#include <SDL2/SDL.h>

int surfToHorArray(SDL_Surface *surf)					//Return the addition of all RGB of the horizontal pixels
{
	int res[surf->h] = {0};
	for (int i = 0; i < surf->h; i++)
	{
		for (int j = 0; j < surf->w; j++)
		{
			pixel = getPixel32(surf, i, j);
			res[i] +=  getRGBSum(pixel);
		}
	}
	return res;
}

int surfToVerArray(SDL_Surface *surf)					//Return the addition of all RGB of the vertical pixels
{
	int res[surf->w] = {0};
	for (int i = 0; i < surf->w; i++)
	{
		for (int j = 0; j < surf->h; j++)
		{
			pixel = getPixel32(surf, j, i);
			res[i] +=  getRGBSum(pixel);
		}
	}
	return res;
}

void arrayBound(int *arr, int *first, int *last)							//Return the boundaries of where the text is in an array
{
	int len = sizeof(*arr)/sizeof(*arr[0]);
	int first = 0;
	int last = len;
	while (i < len && *arr[i] == 0)
	{
		i++;
	}
	int *first = i;
	while (j < len)
	{
		if *arr[j] != 0
			*last = j;
		j++;
	}
	int res[2] = {first, last};
    return res;
}



SDL_Surface surfCropper(SDL_Surface surf, SDL_Rect crop)		//Return the surface cropped by the given rectangle
{
	SDL_Surface res;
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_BlitSurface(surf, &crop, rect, res);
	return res;
}
*/



