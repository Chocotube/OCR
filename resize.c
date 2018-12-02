#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "surface.h"
//#include "color.h"

SDL_Surface* resize(SDL_Surface* before,int maxX , int maxY)
{
	SDL_Surface* after = SDL_CreateRGBSurface(0,maxX,maxY,8,0,0,0,0);
	int oldX = before -> w;
	int oldY = before -> h;
	int ratioX = maxX / oldX;
	int ratioY = maxY / oldY;
	printf("no problems yet\n");
	if(oldX == maxX && oldY == maxY)
	{
		after = before;
	}
	else
	{
		if(oldX > oldY) //When its a fat letter
		{
			//int y = 0;
			int y = (maxY - (ratioX*oldY)) / 2;
			printf("Y : %d\n",y);
			int ymax = maxY - y;
			while(y < ymax)
			{
				int x = 0;
				while(x < maxX)
				{
					int getx = x * ratioX;
					int gety = y * ratioX;
					printf("current X : %d, current y : %d, max x : %d, max y: %d\n",getx , gety , maxX , maxY);
					putPixel(after, x, y, getpixel(before, getx, gety));
					++x;
				}
				++y;
			}
		}
		else if(oldY > oldX)//when it's a tall one
		{
			int y = 0;
			while(y < maxY)
			{
				int x = (maxX - (ratioY*oldX)) / 2;
				int xmax = maxX - x;
				printf("X : %d\n",x);
				while(x < xmax)
				{
					int getx = x * ratioY;
					int gety = y * ratioY;
					printf("current X : %d, current y : %d, max x : %d, max y: %d\n",getx , gety , maxX , maxY);
					putPixel(after, x, y, getpixel(before, getx, gety));
					++x;
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
					int getx = x * ratioX;
					int gety = y * ratioX;
					printf("current X : %d, current y : %d, max x : %d, max y: %d\n",getx , gety , maxX , maxY);
					putPixel(after, x, y, getpixel(before, getx, gety));
					++x;
				}
			++y;
			}
		}
	}
	return after;
}
