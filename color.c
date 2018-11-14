#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "color.h"


//This is a function using SDL to return the pixel at a certin xy
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{

//This line checks the form of the pixel
	int bpp = surface->format->BytesPerPixel;

//This line gets the pixel
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp)
	{

//8 bit
	case 1:
		return *p;
		break;


//16 bit
	case 2:
		return *(Uint16 *)p;
		break;

//Case for 24 bit pixels
	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

//32 bit
	case 4:
		return *(Uint32 *)p;
		break;

	default:
		 return 0;
	}
}


//Function that puts a pixel in a certain spot on the SDL surface
void putpixel(SDL_Surface *surface,int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
//Here p is the address to the pixel we want to set
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

//A case for each how many bytes the pixels have
	switch(bpp){
	case 1:
		*p = pixel;
		break;
	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
			}
			else
			{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
			}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

//Function that greyscales the image
void greyscale(imageData *img)
{
	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;

	long i = 0;
	int x = (img -> image -> w);
	int y = (img -> image -> h);

//We go around the image and greyscale the image that mean adding
//the RGB values and deviding it by 3
	while(i < x)
	{
		long j = 0;
		while(j < y)
		{
			Uint32 pxlsi = getpixel(img -> image,i,j);
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
			putpixel(img -> image , i , j , (Uint32) newcolor);
			j++;

		}
		i++;
	}
	SDL_SaveBMP(img -> image,"greyvalues.bmp");
}



//We use a simular technique that we used for greyscale but this
//time we set the values to the max for black or the fin to white
void BlackOrWhite(imageData *img,float ratio)
{
	Uint8 red = 0;

	long i = 0;
	int x = (img -> image -> w);
	int y = (img -> image -> h);

	while(i < x)
	{
		long j = 0;
		while(j < y)
		{
			Uint32 pxlsi = getpixel(img -> image,i,j);
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
			putpixel(img -> image , i , j , (Uint32) newcolor);
			j++;

		}
		i++;
	}
//we save the image at the end
	SDL_SaveBMP(img -> image,"blackorwhite.bmp");
}

