#include <stdio.h>
#include <SDL2/SDL.h>
#include "loadfile.h"
#include "grey.h"
#include "Cutimage.h"
#include "CutLetter.h"



int IsBlankColonne(SDL_Surface *image,int colonne)
{
	int index = 0;
	int height = image -> h;
	while(index <= height && getpixel(image,colonne,index) != 0)
	{

		index++;
		printf("colonne %d,%d color : %d\n",colonne,index,getpixel(image,colonne,index));
	}
	if(index == height)
	{
		return 1;
	}
	return 0;
}



int FindClosest2(SDL_Surface *image, int colonne)
{
	int index = 0;
	int height = image -> h;
	while(getpixel(image,colonne,index) != 0)
	{
		index++;
	}
	return index;
}



int FindFurthest2(SDL_Surface *image, int colonne)
{
	int height = image -> h;
	int index = height -1;
	while(getpixel(image,colonne,index) != 0)
	{
		index--;
	}
	return index + 1;
}



void SaveLetter(SDL_Surface * image, int startx, int starty, int width, int height,int letterId, int LineNumber)
{
	SDL_Surface *Result;
	char buf[200];

	Result = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
	SDL_Rect Startrectangle = MakeARectangle( startx, starty, width, height);
	SDL_Rect EndRectangle = MakeARectangle( 0, 0, width, height);
	SDL_BlitSurface(image, &Startrectangle, Result, &EndRectangle);
	sprintf(buf, "line_%d_%d.bmp", letterId, LineNumber);

	SDL_SaveBMP(Result,buf);
}



void FindLetter(SDL_Surface *image, int line)
{
	int colonne = 0;
	int maxcolonne = image -> w;
	int i = 0;
	while(colonne < maxcolonne)
	{
		int WeFoundIt = 0;
		int howlong = 0;
		int start = colonne;
		int deep = 0;
		int go = 0;
		printf("Checkpoint 1 : %d\n",colonne);
		while(IsBlankColonne(image,colonne) == 0 && colonne < maxcolonne)
		{
			printf("going up at %d\n",colonne);
			howlong++;
			colonne++;
			deep++;
			go = 1;
		}

		deep--;
		howlong--;
		colonne--;
		
		int oldfurthest = 0;
		int oldclosest = image -> h;
		int keep = howlong;

		while(howlong >= 0)
		{
			printf("goin down at %d\n",colonne);
			int closest = FindClosest2(image,colonne);
			if(closest < oldclosest)
			{
				oldclosest = closest;
			}

			int furthest = FindFurthest2(image,colonne);
			if(furthest > oldfurthest)
			{
				oldfurthest = furthest;
			}
			howlong--;
			colonne--;
			WeFoundIt = 1;
		}

		howlong++;
		colonne++;
		
		printf("Checkpoint2 : %d\n",colonne);
		if(WeFoundIt ==1)
		{
			
			i++;
			int newdimensionx = oldfurthest - oldclosest;
			int newdimensiony = keep - howlong;
			printf("oldclosest %d , newdimensionx %d, newdimensiony, %d\n",oldclosest,newdimensionx,newdimensiony);
			SaveLetter(image, start, oldfurthest, newdimensionx, newdimensiony, line, i);
			WeFoundIt = 0;
		}
		if(go == 0)
		{
			deep = 1;
		}
		colonne += deep;
	}
}

