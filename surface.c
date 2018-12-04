#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "color.h"

SDL_Surface* LoadImage(char path[])     //Returns the sdl surface of the BMP given in the path
{
    SDL_Surface *res =  SDL_LoadBMP(path);
    if (res == NULL)
    {
        printf("The file either does not exist or is not a correct bitmap\n");
    }
    return res;
}

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
void putPixel(SDL_Surface *surface,int x, int y, Uint32 pixel)
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

int getPixelRed(SDL_Surface *surf, int x, int y)                            //Returns the value of the red color of the pixel in position x y of the surf
{
    int res = 1;
    if (getpixel(surf, x, y) >> 16 != 0)
        res = 0;
    return res;
}

void binVerArray(SDL_Surface *surf, int array[])                   //Put the addition of red values of each line in array
{
    for (int i = 0; i < surf->h; i++)
    {
        array[i] = 0;
        for (int j = 0; j < surf->w; j++)
        {
            array[i] += getPixelRed(surf, j, i);
        }
    }
}

void binHorArray(SDL_Surface *surf, int array[])                   //Put the addition of red values of each colone in array
{
    for (int i = 0; i < surf->w; i++)
    {
        array[i] = 0;
        for (int j = 0; j < surf->h; j++)
        {
            array[i] += getPixelRed(surf, i, j);
        }
    }
}

SDL_Rect makeRectangle(int x ,int y, int w, int h)                  //Returns an SDL_Rect with the given parametres
{
    SDL_Rect res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;
    return res;
}

SDL_Surface* cropSurf(SDL_Surface *surf, SDL_Rect crop)              //Return the surface cropped with the given rectangle
{
    SDL_Surface *res = SDL_CreateRGBSurface( 0, crop.w, crop.h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(surf, &crop, res, NULL);
    return res;
}

void saveSurfaceAsBMP(SDL_Surface *surf, int name, int type)       //Saves the surface as a BMP named name.bmp
{
    char strName[sizeof(int) + 26 * sizeof(char)];
    if (type == 1)
        sprintf(strName, "./Letters/%010d_s.bmp", name);
    else if (type == 2)
        sprintf(strName, "./Letters/%010d_r.bmp", name);
    else if (type == 3)
        sprintf(strName, "./Letters/%010d_b.bmp", name);
    else
        sprintf(strName, "./Letters/%010d_l.bmp", name);
    SDL_SaveBMP(surf, strName);
}

void surfToArr(SDL_Surface *surf, double array[])
{
    surf = blackAndWhite(greyScale(surf), 0.5);
    for (int i = 0; i < surf->h; i++)
    {
        for (int j = 0; j < surf->w; j++)
        {
            array[i * 30 + j] = !getPixelRed(surf, j, i);
        }
    }
}
