#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "surface.h"
//#include "color.h"

void printsdlsurface(SDL_Surface * surface)
{
	int width =  surface -> w;
	int height = surface -> h;
	int j = 0;
	while(j < height)
	{
		int i = 0;
		while(i <  width)
		{
			printf("%d ",(int) getpixel(surface,i,j));
			++i;
		}
		printf("\n");
		++j;
	}

}


SDL_Surface* resize(SDL_Surface* before,int maxX , int maxY)
{
	SDL_Surface* after = SDL_CreateRGBSurface(0,maxX,maxY,32,0,0,0,0);
	int jndex = 0;
	int oldX = before -> w;
	int oldY = before -> h;
	float ratioX = ((float)maxX) / ((float)oldX);
	float ratioY = ((float)maxY) / ((float)oldY);
	float XY = ((float)oldX) / ((float)oldY);

	while(jndex < maxY)
	{
		int index = 0;
		while(index < maxX)
		{
			putPixel(after,index,jndex,16777215);
			++index;
		}
		++jndex;
	}


	if(oldX == maxX && oldY == maxY)
	{
		after = before;
	}
	else
	{
		if(XY > 1) //When its a fat letter
		{
			float y = 0;
			int y0 = maxY/2 - (1/XY) *  maxX / 2;
			int ymax = maxY/2 + (1 / XY) *  maxX / 2;
			int lg = ymax - y0;
			float iteration = (float)oldY / (float)lg;
			while(y0 < ymax)
			{
				int x = 0;
				while(x < maxX)
				{
					int getx = x /  ratioX;
					putPixel(after, x, y0, getpixel(before, getx,(int) y));
					++x;
				}
				y += iteration;
				++y0;
			}
		}
		else if(XY < 1)//when it's a tall one
		{
			int y = 0;
			int x0 = maxX/2 - XY * maxY / 2 ;
			int xmax = maxX/2 + XY * maxY / 2;
			int lg = xmax - x0;
			float iteration = (float)oldX / (float)lg;
			while(y < maxY)
			{
				int x = x0;
				float x2 = 0;
				while(x < xmax)
				{
					int gety = y / ratioY;
					putPixel(after, x, y, getpixel(before,(int) x2, gety));
					++x;
					x2 += iteration;
				}
				++y;
			}
		}
		else//just need to englarge it
		{
			int y = 0;
			while(y < maxX)
			{
				int x = 0;
				while(x < maxX)
				{
					int getx = x / ratioX;
					int gety = y / ratioX;
					putPixel(after, x, y, getpixel(before, getx, gety));
					++x;
				}
			++y;
			}
		}
	}
	return after;
}


