#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
    
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		 return 0;
	}
}
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

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
void greyscale(imageData *img)
{
	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;

	long i = 0;
	int x = (img -> image -> w);
	int y = (img -> image -> h);
	//scanf("%s",new);
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
			newcolor |= v;
			newcolor <<= 8;
			newcolor |= v;
			putpixel(img -> image , i , j , (Uint32) newcolor);
			j++;

		}
		i++;
	}
	SDL_SaveBMP(img -> image,"greyvalues.bmp");
}

void BlackOrWhite(imageData *img,float ratio)
{
	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;

	long i = 0;
	int x = (img -> image -> w);
	int y = (img -> image -> h);
	//scanf("%s",new);
	while(i < x)
	{
		long j = 0;
		while(j < y)
		{
			Uint32 pxlsi = getpixel(img -> image,i,j);
			red = pxlsi >> 16;
			
			Uint32 v;

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
	SDL_SaveBMP(img -> image,"blackorwhite.bmp");
}

