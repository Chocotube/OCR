#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "color.h"


//Function that greyscales the image
SDL_Surface* greyScale(SDL_Surface *surf)
{
	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;

	long i = 0;
	int x = (surf -> w);
	int y = (surf -> h);

//We go around the image and greyscale the image that mean adding
//the RGB values and deviding it by 3
	while(i < x)
	{
		long j = 0;
		while(j < y)
		{
			Uint32 pxlsi = getpixel(surf,i,j);
			red = pxlsi >> 16;
			green = pxlsi >> 8;
			blue = pxlsi;

			Uint8 v = (red + green + blue)/3;

			Uint32 newcolor = v;
			newcolor <<= 8;
//We use the << operator to move the bits to insert easier
			newcolor |= v;
//Then we use the or operator to compare the 8 last bits and because that
//will be = 0 on the last 8 bits of the resulat will be equals to v
			newcolor <<= 8;
			newcolor |= v;
			putPixel(surf , i , j , (Uint32) newcolor);
			j++;

		}
		i++;
	}
	return surf;
}



//We use a simular technique that we used for greyscale but this
//time we set the values to the max for black or the fin to white
SDL_Surface* blackAndWhite(SDL_Surface *surf, float ratio)
{
	Uint8 red = 0;

	long i = 0;
	int x = (surf -> w);
	int y = (surf -> h);

	while(i < x)
	{
		long j = 0;
		while(j < y)
		{
			Uint32 pxlsi = getpixel(surf,i,j);
			red = pxlsi >> 16;

			Uint32 v;
//We have defined a ratio where we can ajust if the color is off to get better
//results
//we just compare red becaus the image has already mean through greyscale so
//the RGB are equal
			if(((int)red) > (255*ratio))
			{
				v = 255;
			}
			else
			{
				v = 0;
			}

			Uint32 newcolor = v;
			newcolor <<= 8;
			newcolor |= v;
			newcolor <<= 8;
			newcolor |= v;
			putPixel(surf , i , j , (Uint32) newcolor);
			j++;

		}
		i++;
	}
//we save the image at the end
	return surf;
}

